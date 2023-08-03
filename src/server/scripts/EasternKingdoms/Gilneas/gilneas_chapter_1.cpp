/*
* This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU Affero General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
* more details.
*
* You should have received a copy of the GNU Affero General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gilneas.h"
#include "ScriptMgr.h"
#include "CombatAI.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "PassiveAI.h"
#include "PhasingHandler.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "Vehicle.h"

/*######
## Quest 14098 - Evacuate the Merchant Square
######*/

enum FrightenedCitizen
{
    SAY_FRIGHTENED_CITIZEN_RESCUE   = 0,

    NPC_EVACUATION_STALKER_FIRST    = 35830,
    NPC_EVACUATION_STALKER_NEAR     = 35010,
    NPC_EVACUATION_STALKER_FAR      = 35011,
    NPC_RAMPAGING_WORGEN            = 35660,

    CREDIT_35830                    = 35830,

    POINT_STALKER_FIRST             = 1,
    POINT_STALKER_NEAR              = 2,
    POINT_STALKER_FAR               = 3,

    EVENT_TALK_FRIGHTENED           = 1,
    EVENT_MOVE_TO_NEAR_STALKER      = 2,
    EVENT_MOVE_TO_FAR_STALKER       = 3,
    EVENT_DESPAWN                   = 4
};

struct npc_frightened_citizen : public PassiveAI
{
    npc_frightened_citizen(Creature* creature) : PassiveAI(creature) { }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        if (Creature* stalkerNear = me->FindNearestCreature(NPC_EVACUATION_STALKER_FIRST, 20.0f))
            me->GetMotionMaster()->MovePoint(POINT_STALKER_FIRST, stalkerNear->GetPosition(), true);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        switch (id)
        {
            case POINT_STALKER_FIRST:
                _events.ScheduleEvent(EVENT_TALK_FRIGHTENED, 1s);
                break;
            case POINT_STALKER_NEAR:
                _events.ScheduleEvent(EVENT_MOVE_TO_FAR_STALKER, 1ms);
                break;
            case POINT_STALKER_FAR:
                _events.ScheduleEvent(EVENT_DESPAWN, 1ms);
                break;
            default:
                break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_TALK_FRIGHTENED:
                    if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    {
                        if (Player* player = summoner->ToPlayer())
                        {
                            player->KilledMonsterCredit(CREDIT_35830);
                            Talk(SAY_FRIGHTENED_CITIZEN_RESCUE, summoner);
                        }
                    }
                    _events.ScheduleEvent(EVENT_MOVE_TO_NEAR_STALKER, 2s);
                    break;
                case EVENT_MOVE_TO_NEAR_STALKER:
                    if (Creature* stalker = me->FindNearestCreature(NPC_EVACUATION_STALKER_FAR, 50.0f))
                        me->GetMotionMaster()->MovePoint(POINT_STALKER_FAR, stalker->GetPosition(), true);
                    else if (Creature* stalker = me->FindNearestCreature(NPC_EVACUATION_STALKER_NEAR, 100.0f))
                        me->GetMotionMaster()->MovePoint(POINT_STALKER_NEAR, stalker->GetPosition(), true);
                    break;
                case EVENT_MOVE_TO_FAR_STALKER:
                    if (Creature* stalker = me->FindNearestCreature(NPC_EVACUATION_STALKER_FAR, 500.0f))
                        me->GetMotionMaster()->MovePoint(POINT_STALKER_FAR, stalker->GetPosition(), true);
                    break;
                case EVENT_DESPAWN:
                    me->DespawnOrUnsummon();
                    break;
                default:
                    break;
            }
        }
    }
private:
    EventMap _events;
};

/*######
## Quest 14154 - By the Skin of his Teeth
######*/

enum WorgenRunt
{
    EVENT_JUMP_TO_PRISON            = 1,
    EVENT_AGGRO_PLAYER              = 2,
    EVENT_FORCE_DESPAWN             = 3,

    PHASE_ROOF                      = 0,
    PHASE_COMBAT                    = 1,

    WORGEN_ID_ROOF_1                = 0,
    WORGEN_ID_ROOF_2                = 1,
    WORGEN_ID_ROOF_3                = 2,
    WORGEN_ID_ROOF_4                = 3,
    WORGEN_ID_ROOF_5                = 4,
    WORGEN_ID_ROOF_6                = 5,
    WORGEN_ID_ROOF_7                = 6,

    WORGEN_ID_CATHEDRAL_1           = 7,
    WORGEN_ID_CATHEDRAL_2           = 8,
    WORGEN_ID_CATHEDRAL_3           = 9,
    WORGEN_ID_CATHEDRAL_4           = 10,
    WORGEN_ID_CATHEDRAL_5           = 11,
    WORGEN_ID_CATHEDRAL_6           = 12,
    WORGEN_ID_CATHEDRAL_7           = 13,
    WORGEN_ID_CATHEDRAL_8           = 14,
    WORGEN_ID_CATHEDRAL_9           = 15,

    NPC_WORGEN_RUNT_SPELL           = 35188,
};

static Position const RuntSpellSummonJumpPos = { -1671.915f, 1446.734f, 52.28712f };

struct npc_worgen_runt : public ScriptedAI
{
    npc_worgen_runt(Creature* creature) : ScriptedAI(creature), _worgenID(0), _wayPointCounter(0), _jumped(false) { }

    void JustEngagedWith(Unit* /*who*/) override
    {
        _events.SetPhase(PHASE_COMBAT);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        me->setActive(true); // we are in a phased and cut off map so we're fine to use that here
        _events.SetPhase(PHASE_ROOF);
        _events.ScheduleEvent(EVENT_FORCE_DESPAWN, 70s, 0, PHASE_ROOF);
        _playerGuid = summoner->GetGUID();
        if (me->GetEntry() == NPC_WORGEN_RUNT_SPELL)
            me->GetMotionMaster()->MoveJump(RuntSpellSummonJumpPos, 16.0f, 4.371286f);
    }

    void DoAction(int32 action) override
    {
        _worgenID = action;
        switch (_worgenID) // ugly as fuck but needed for individual controls
        {
            // House roof cases
            case WORGEN_ID_ROOF_1:
                _wayPointCounter = runtHousePathSize1;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize1, worgenRuntHousePath1, runtHousePathSize1);
                break;
            case WORGEN_ID_ROOF_2:
                _wayPointCounter = runtHousePathSize2;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize2, worgenRuntHousePath2, runtHousePathSize2);
                break;
            case WORGEN_ID_ROOF_3:
                _wayPointCounter = runtHousePathSize3;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize3, worgenRuntHousePath3, runtHousePathSize3);
                break;
            case WORGEN_ID_ROOF_4:
                _wayPointCounter = runtHousePathSize4;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize4, worgenRuntHousePath4, runtHousePathSize4);
                break;
            case WORGEN_ID_ROOF_5:
                _wayPointCounter = runtHousePathSize5;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize5, worgenRuntHousePath5, runtHousePathSize5);
                break;
            case WORGEN_ID_ROOF_6:
                _wayPointCounter = runtHousePathSize6;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize6, worgenRuntHousePath6, runtHousePathSize6);
                break;
            case WORGEN_ID_ROOF_7:
                _wayPointCounter = runtHousePathSize7;
                me->GetMotionMaster()->MoveSmoothPath(runtHousePathSize7, worgenRuntHousePath7, runtHousePathSize7);
                break;
                // Cathedral cases
            case WORGEN_ID_CATHEDRAL_1:
                _wayPointCounter = runtCathedralPathSize1;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize1, worgenRuntCathedralPath1, runtCathedralPathSize1);
                break;
            case WORGEN_ID_CATHEDRAL_2:
                _wayPointCounter = runtCathedralPathSize2;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize2, worgenRuntCathedralPath1, runtCathedralPathSize2);
                break;
            case WORGEN_ID_CATHEDRAL_3:
                _wayPointCounter = runtCathedralPathSize3;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize3, worgenRuntCathedralPath1, runtCathedralPathSize3);
                break;
            case WORGEN_ID_CATHEDRAL_4:
                _wayPointCounter = runtCathedralPathSize4;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize4, worgenRuntCathedralPath1, runtCathedralPathSize4);
                break;
            case WORGEN_ID_CATHEDRAL_5:
                _wayPointCounter = runtCathedralPathSize5;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize5, worgenRuntCathedralPath1, runtCathedralPathSize5);
                break;
            case WORGEN_ID_CATHEDRAL_6:
                _wayPointCounter = runtCathedralPathSize6;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize6, worgenRuntCathedralPath1, runtCathedralPathSize6);
                break;
            case WORGEN_ID_CATHEDRAL_7:
                _wayPointCounter = runtCathedralPathSize7;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize7, worgenRuntCathedralPath1, runtCathedralPathSize7);
                break;
            case WORGEN_ID_CATHEDRAL_8:
                _wayPointCounter = runtCathedralPathSize8;
                me->GetMotionMaster()->MoveSmoothPath(runtCathedralPathSize8, worgenRuntCathedralPath1, runtCathedralPathSize8);
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(5s);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == _wayPointCounter && !_jumped)
        {
            _jumped = true;
            _events.ScheduleEvent(EVENT_JUMP_TO_PRISON, 1ms);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !_events.IsInPhase(PHASE_ROOF))
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FORCE_DESPAWN:
                    me->DespawnOrUnsummon();
                    break;
                case EVENT_JUMP_TO_PRISON:
                    me->GetMotionMaster()->MoveJump(worgenRuntJumpPos[_worgenID], 16.0f, _worgenID < WORGEN_ID_CATHEDRAL_1 ? 19.2911f : frand(3.945607f, 4.852813f));
                    me->SetHomePosition(worgenRuntJumpPos[_worgenID]);
                    _events.ScheduleEvent(EVENT_AGGRO_PLAYER, 2s);
                    break;
                case EVENT_AGGRO_PLAYER:
                    if (Unit* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                        if (me->IsInDist(player->GetPosition(), 100.0f))
                            AttackStart(player);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    uint32 _worgenID;
    uint32 _wayPointCounter;
    bool _jumped;
    ObjectGuid _playerGuid;
    EventMap _events;
};

/*######
## Quest 14159 - The Rebel Lord's Arsenal
######*/

enum TheRebelLordsArsena
{
    PHASE_ID_SUMMON         = 170,
    PHASE_ID_WOUND          = 171,
    NPC_LORNA_CROWLEY       = 35378,
    NPC_GENERIC_TRIGGER_LAB = 35374,

    SPELL_SHOOT_INSTAKILL   = 67593,
    SPELL_COSMETIC_ATTACK   = 42880,
    SPELL_PULL_TO           = 67357,

    EVENT_COSMETIC_ATTACK   = 1,
    EVENT_JUMP_TO_PLAYER,
    EVENT_SHOOT_JOSIAH
};

static Position const JosiahJumpPos = { -1796.63f, 1427.73f, 12.4624f };

struct npc_josiah_avery : public PassiveAI
{
    npc_josiah_avery(Creature* creature) : PassiveAI(creature) { }

    void IsSummonedBy(Unit* summoner) override
    {
        PhasingHandler::AddPhase(me, PHASE_ID_SUMMON, true);
        PhasingHandler::AddPhase(me, PHASE_ID_WOUND, true);
        _playerGuid = summoner->GetGUID();
        _events.ScheduleEvent(EVENT_COSMETIC_ATTACK, 500ms);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(5s);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_COSMETIC_ATTACK:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, _playerGuid))
                    {
                        DoCast(player, SPELL_COSMETIC_ATTACK);
                        if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f, true))
                            if (Creature* labTrigger = lorna->FindNearestCreature(NPC_GENERIC_TRIGGER_LAB, 5.0f, true))
                                labTrigger->CastSpell(player, SPELL_PULL_TO);

                        _events.ScheduleEvent(EVENT_JUMP_TO_PLAYER, 1s);
                    }
                    break;
                case EVENT_JUMP_TO_PLAYER:
                    me->GetMotionMaster()->MoveJump(JosiahJumpPos, 10.0f, 14.18636f);
                    _events.ScheduleEvent(EVENT_SHOOT_JOSIAH, 500ms);
                    break;
                case EVENT_SHOOT_JOSIAH:
                    if (Creature* lorna = me->FindNearestCreature(NPC_LORNA_CROWLEY, 30.0f, true))
                        lorna->CastSpell(me, SPELL_SHOOT_INSTAKILL, true);
                    break;
                default:
                    break;
            }
        }
    }
private:
    ObjectGuid _playerGuid;
    EventMap _events;
};

/*######
## Quest 14293 - Save Krennan Aranas
######*/

static Position const GreymanesHorseJumpPos = { -1676.16f, 1346.19f, 15.1349f };

enum GreymanesHorse
{
    SAY_ANNOUNCE_RESCUE     = 0,
    SAY_RESCUED             = 0,
    SAY_TRAPPED             = 0,

    PATH_KRENNAN_TREE       = 0,
    PATH_KRENNAN_BACK       = 1,

    EVENT_START_PATH_1      = 1,
    EVENT_START_PATH_2,
    EVENT_JUMP_TO_KRENNAN,
    EVENT_ANNOUNCE_RESCUE,
    EVENT_DISMOUNT_PLAYER,

    NPC_RESCUED_KRENNAN     = 35907,
    NPC_TRAPPED_KRENNAN     = 35753,
};

struct npc_greymanes_horse : public VehicleAI
{
    npc_greymanes_horse(Creature* creature) : VehicleAI(creature), _currentPath(PATH_KRENNAN_TREE) { }

    void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
    {
        if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            _events.ScheduleEvent(EVENT_START_PATH_1, 1s);
        }
        else if (apply && passenger->GetEntry() == NPC_RESCUED_KRENNAN)
            _events.ScheduleEvent(EVENT_START_PATH_2, 1s);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == EFFECT_MOTION_TYPE && pointId == pathSize1 && _currentPath == PATH_KRENNAN_TREE)
            _events.ScheduleEvent(EVENT_JUMP_TO_KRENNAN, 1ms);
        else if (type == EFFECT_MOTION_TYPE && pointId == pathSize2 && _currentPath == PATH_KRENNAN_BACK)
            _events.ScheduleEvent(EVENT_DISMOUNT_PLAYER, 1ms);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_START_PATH_1:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    _currentPath = PATH_KRENNAN_TREE;
                    me->GetMotionMaster()->MoveSmoothPath(pathSize1, greymanesHorsePath1, pathSize1);
                    break;
                case EVENT_JUMP_TO_KRENNAN:
                    me->GetMotionMaster()->MoveJump(GreymanesHorseJumpPos, 16.0f, 14.00968f);
                    _events.ScheduleEvent(EVENT_ANNOUNCE_RESCUE, 2s);
                    break;
                case EVENT_ANNOUNCE_RESCUE:
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    {
                        Talk(SAY_ANNOUNCE_RESCUE, passenger);
                        if (Creature* krennan = me->FindNearestCreature(NPC_TRAPPED_KRENNAN, 30.0f, true))
                            krennan->AI()->Talk(SAY_TRAPPED, passenger);
                    }
                    break;
                case EVENT_START_PATH_2:
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    _currentPath = PATH_KRENNAN_BACK;
                    me->GetMotionMaster()->MoveSmoothPath(pathSize2, greymanesHorsePath2, pathSize2);
                    break;
                case EVENT_DISMOUNT_PLAYER:
                    if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
                    {
                        if (Unit* player = me->GetVehicleKit()->GetPassenger(0))
                        {
                            if (Creature* krennan = passenger->ToCreature())
                            {
                                std::vector<Unit*> storedAttackers;

                                for (Unit* attacker : me->getAttackers())
                                    storedAttackers.push_back(attacker);

                                for (Unit* attacker : storedAttackers)
                                {
                                    if (Creature* creature = attacker->ToCreature())
                                        if (creature->IsAIEnabled())
                                            creature->AI()->EnterEvadeMode();
                                }

                                player->ExitVehicle();
                                krennan->AddUnitState(UNIT_STATE_ROOT);
                                krennan->ExitVehicle();
                                krennan->AI()->Talk(SAY_RESCUED, me);
                                krennan->DespawnOrUnsummon(7s);
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
private:
    EventMap _events;
    uint32 _currentPath;
};

/*######
## Quest 14212 - Sacrifices
######*/

enum CrowleysHorse
{
    EVENT_JUMP_OVER_BARRICADES_1 = 1,
    EVENT_JUMP_OVER_BARRICADES_2,
    EVENT_MOVE_PATH_MAIN_1,
    EVENT_MOVE_PATH_MAIN_2,
    EVENT_MOVE_OFF_PATH = 6,

    PATH_ID_CROWLEYS_HORSE_1    = 352310,
    PATH_ID_CROWLEYS_HORSE_2    = 352311,
    PATH_ID_CROWLEYS_HORSE_3    = 444280,

    SPELL_THROW_TORCH           = 67063,
    NPC_CROWLEYS_HORSE_2        = 44428,
};

static Position const CrowleysHorseJumpPos = { -1714.762f, 1673.16f, 20.49182f };
static Position const CrowleysHorseJumpPos2 = { -1566.71f, 1708.04f, 20.4849f };

struct npc_crowleys_horse : public VehicleAI
{
    npc_crowleys_horse(Creature* creature) : VehicleAI(creature), _currentPath(0) { }

    void PassengerBoarded(Unit* passenger, int8 /*seatId*/, bool apply) override
    {
        if (apply && passenger->GetTypeId() == TYPEID_PLAYER && me->GetEntry() != NPC_CROWLEYS_HORSE_2)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            _events.ScheduleEvent(EVENT_JUMP_OVER_BARRICADES_1, 2s);
        }
        else if (apply && passenger->GetTypeId() == TYPEID_PLAYER)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            _events.ScheduleEvent(EVENT_MOVE_OFF_PATH, 2s);
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == WAYPOINT_MOTION_TYPE && pointId == 14 && _currentPath == PATH_ID_CROWLEYS_HORSE_1)
            _events.ScheduleEvent(EVENT_JUMP_OVER_BARRICADES_2, 1s);
        else if (type == WAYPOINT_MOTION_TYPE && pointId == 15 && _currentPath == PATH_ID_CROWLEYS_HORSE_2)
            _events.ScheduleEvent(EVENT_DISMOUNT_PLAYER, 1ms);
        else if (type == WAYPOINT_MOTION_TYPE && pointId == 16 && _currentPath == PATH_ID_CROWLEYS_HORSE_3)
            _events.ScheduleEvent(EVENT_DISMOUNT_PLAYER, 1ms);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_JUMP_OVER_BARRICADES_1:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->GetMotionMaster()->MoveJump(CrowleysHorseJumpPos, 16.0f, 18.56182f);
                    _events.ScheduleEvent(EVENT_MOVE_PATH_MAIN_1, 2s);
                    break;
                case EVENT_MOVE_PATH_MAIN_1:
                    me->GetMotionMaster()->MovePath(PATH_ID_CROWLEYS_HORSE_1, false);
                    _currentPath = PATH_ID_CROWLEYS_HORSE_1;
                    break;
                case EVENT_JUMP_OVER_BARRICADES_2:
                    me->GetMotionMaster()->MoveJump(CrowleysHorseJumpPos2, 16.0f, 18.56182f);
                    _events.ScheduleEvent(EVENT_MOVE_PATH_MAIN_2, 2s);
                    break;
                case EVENT_MOVE_PATH_MAIN_2:
                    _currentPath = PATH_ID_CROWLEYS_HORSE_2;
                    me->GetMotionMaster()->MovePath(PATH_ID_CROWLEYS_HORSE_2, false);
                    break;
                case EVENT_DISMOUNT_PLAYER:
                {
                    std::set<Unit*> attackersCopy = me->getAttackers();
                    for (Unit* attacker : attackersCopy)
                    {
                        if (Creature* creature = attacker->ToCreature())
                            if (creature->IsAIEnabled())
                                creature->AI()->EnterEvadeMode();
                    }

                    me->RemoveAurasDueToSpell(VEHICLE_SPELL_RIDE_HARDCODED);
                    me->DespawnOrUnsummon(5s);
                    break;
                }
                case EVENT_MOVE_OFF_PATH:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    _currentPath = PATH_ID_CROWLEYS_HORSE_3;
                    me->GetMotionMaster()->MovePath(PATH_ID_CROWLEYS_HORSE_3, false);
                    break;
                default:
                    break;
            }
        }
    }
private:
    EventMap _events;
    uint32 _currentPath;
};

enum GileanCrow
{
    SPELL_GILNEAN_CROW      = 93275,
    EVENT_APPLY_HOVER_BYTES = 1,
    EVENT_FLY_AWAY_1        = 2,
    EVENT_FLY_AWAY_2        = 3,

    POINT_NONE              = 0,
    POINT_CROW_FLIGHT       = 1
};

struct npc_gilnean_crow : public PassiveAI
{
    npc_gilnean_crow(Creature* creature) : PassiveAI(creature) { }

    void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_GILNEAN_CROW)
            _events.ScheduleEvent(EVENT_APPLY_HOVER_BYTES, 500ms);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == POINT_MOTION_TYPE && pointId == POINT_CROW_FLIGHT)
        {
            Position pos = me->GetRandomNearPosition(8.0f);
            pos.m_positionZ = me->GetPositionZ() + 10.0f;
            me->GetMotionMaster()->MovePoint(POINT_NONE, pos);
            me->DespawnOrUnsummon(14s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_APPLY_HOVER_BYTES:
                    me->SetStandState(UNIT_STAND_STATE_SIT);
                    me->SetAnimationTier(AnimationTier::Submerged);
                    _events.ScheduleEvent(EVENT_FLY_AWAY_1, 1s);
                    break;
                case EVENT_FLY_AWAY_1:
                {
                    Position pos = me->GetRandomNearPosition(7.0f);
                    pos.m_positionZ = me->GetPositionZ() + 8.0f;
                    me->GetMotionMaster()->MovePoint(POINT_CROW_FLIGHT, pos);
                    break;
                }
                default:
                    break;
            }
        }
    }
private:
    EventMap _events;
};

void AddSC_gilneas_chapter_1()
{
    RegisterCreatureAI(npc_frightened_citizen);
    RegisterCreatureAI(npc_worgen_runt);
    RegisterCreatureAI(npc_josiah_avery);
    RegisterCreatureAI(npc_greymanes_horse);
    RegisterCreatureAI(npc_crowleys_horse);
    RegisterCreatureAI(npc_gilnean_crow);
}
