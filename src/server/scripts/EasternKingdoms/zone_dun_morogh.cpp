/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "MotionMaster.h"
#include "ScriptedCreature.h"
#include "ObjectAccessor.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "GridNotifiers.h"
#include "CellImpl.h"
#include "GridNotifiersImpl.h"
#include "ObjectMgr.h"
#include "Map.h"

enum FrozenMountaineer
{
    DATA_SET_ICE_BROKEN      = 1,
    EVENT_RUN_AWAY           = 1,
    SAY_MONSTEREMOTE         = 0,
    SPELL_SUMMON_FROZEN_TOMB = 77906,
    SPELL_FREEZE_ANIM        = 77910
};

/*######
# npc_frozen_mountaineer
######*/

class npc_frozen_mountaineer : public CreatureScript
{
public:
    npc_frozen_mountaineer() : CreatureScript("npc_frozen_mountaineer") { }

    struct npc_frozen_mountaineerAI : public ScriptedAI
    {
        npc_frozen_mountaineerAI(Creature* creature) : ScriptedAI(creature), _dataOneSet(false) { }

        void Reset() override
        {
            _events.Reset();
            DoCastSelf(SPELL_SUMMON_FROZEN_TOMB, true);
            DoCastSelf(SPELL_FREEZE_ANIM, true);
        }

        void SetData(uint32 /*type*/, uint32 data) override
        {
            if (data == DATA_SET_ICE_BROKEN && !_dataOneSet)
            {
                me->RemoveAllAuras();
                Talk(SAY_MONSTEREMOTE);
                _dataOneSet = true;
                _events.ScheduleEvent(EVENT_RUN_AWAY, Seconds(3));
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_dataOneSet)
                return;

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_RUN_AWAY)
            {
                me->GetMotionMaster()->MovePoint(0, me->GetPositionX() + (std::cos(me->GetOrientation()) * 15.0f), me->GetPositionY() + (std::sin(me->GetOrientation()) * 15.0f), me->GetPositionZ());
                me->DespawnOrUnsummon(Seconds(2));
            }
        }
    private:
        EventMap _events;
        bool _dataOneSet;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_frozen_mountaineerAI(creature);
    }
};

/*######
## npc_sanitron500
######*/

/*
 *  @Npc   : Sanitron 500 (46185)
 *  @Quest : Decontamination (27635)
 *  @Descr : Board the Sanitron 500 to begin the decontamination process.
 */
enum eSanitron
{
    SPELL_CANNON_BURST = 86080,
    SPELL_DECONTAMINATE_STAGE_1 = 86075,
    SPELL_DECONTAMINATE_STAGE_2 = 86086,
    SPELL_IRRADIATE = 80653,

    SPELL_EXPLOSION = 30934,

    QUEST_DECONTAMINATION = 27635,

    NPC_DECONTAMINATION_BUNNY = 46165,
    NPC_CLEAN_CANNON = 46208,
    NPC_SAFE_TECHNICAN = 46230,
    HANDLE_EMOTE_SANNITRON_01 = 0,
};

Position const eQuestPosition[14] = {
    /*X    Y*/
    {-5165.209961f, 713.809021f},  //Move To Waypoint 0
    {-5164.919922f, 723.890991f},  // Move To Waypoint 1
    {-5182.560059f, 726.656982f},  // Move To Waypoint 2
    {-5166.350098f, 706.336975f},  // Move To Waypoint 3
    {-5184.040039f, 708.405029f},  // Move To Waypoint 4
    {-5164.209961f, 719.267029f},  // Move To Waypoint 5
    {-5165.000000f, 709.453979f},  // Move To Waypoint 6
    {-5183.830078f, 722.093994f},  // Move To Waypoint 7
    {-5184.470215f, 712.554993f},  // Move To Waypoint 8
    {-5173.94f, 725.62f, 291.387f}, // Move To Waypoint 9 Motion Master
    {-5174.56f, 716.36f, 289.387f},  // Move To Waypoint 10 Motion Master
    {-5175.21f, 707.18f, 291.887f},   // Move To Waypoint 11 Motion Master
    {-5175.98f, 700.18f, 291.387f},     // Move To Waypoint 12 Motion Master
    {-5175.61f, 700.38f, 290.89f}, // Move To Waypoint 13 Motion Master
};

enum eTexts
{
    SAY_SANITRON_01 = 46323,
    SAY_SANITRON_02 = 46342,
    SAY_SANITRON_03 = 46324,
    SAY_SANITRON_04 = 46325,
};

class npc_sanitron500 : public CreatureScript
{
   public:
    npc_sanitron500() : CreatureScript("npc_sanitron500") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        QuestStatus status = pPlayer->GetQuestStatus(QUEST_DECONTAMINATION);
        if (status == QUEST_STATUS_INCOMPLETE)
        {
            Vehicle* vehicle = pCreature->GetVehicleKit();
            pPlayer->HandleEmoteCommand(HANDLE_EMOTE_SANNITRON_01);
            pPlayer->EnterVehicle(pCreature->ToUnit(), 0);
            pCreature->Say(SAY_SANITRON_01);
        }
        return true;
    }

    struct npc_sanitron500AI : public ScriptedAI
    {
        Vehicle* vehicle;
        Unit* Technician = 0;
        Creature::Unit* Bunny[4] = {0};
        Creature::Unit* Cannon[4] = {0};
        uint32 uiTimer = 0;
        uint32 uiRespawnTimer = 0;
        uint8 uiPhase = 0;

        npc_sanitron500AI(Creature* pCreature)
            : ScriptedAI(pCreature), vehicle(pCreature->GetVehicleKit())
        {
            assert(vehicle);
        }
        void Reset()
        {
            uiTimer = 0;
            uiRespawnTimer = 6000;
            uiPhase = 0;
        }

        Unit* unit(uint32 entry, uint32 range, bool alive)
        {
            if (Unit* unit =
                    me->FindNearestCreature(entry, float(range), alive))
                if (Unit* unit2 = ObjectAccessor::GetCreature(*me, unit->GetGUID()))
                    return unit2;
        }

        void GetTargets()
        {
            float radius = 100.0f;
            std::list<Unit*> targets;
            Firelands::AnyUnitInObjectRangeCheck go_check(me, radius);
            Firelands::UnitListSearcher<Firelands::AnyUnitInObjectRangeCheck> searcher(me, targets, go_check);
            Cell::VisitGridObjects(me, searcher, radius);
            if (!targets.empty())
                for (std::list<Unit*>::const_iterator iter = targets.begin();
                     iter != targets.end(); ++iter)
                {
                    if ((*iter)->GetTypeId() != TYPEID_PLAYER)
                    {
                        switch ((*iter)->GetEntry())
                        {
                            case 46230:
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[0].GetPositionX(),
                                        eQuestPosition[0].GetPositionY()) <= 1)
                                    Technician = (*iter);
                                break;
                            case 46165:
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[1].GetPositionX(),
                                        eQuestPosition[1].GetPositionY()) <= 1)
                                    Bunny[0] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[2].GetPositionX(),
                                        eQuestPosition[2].GetPositionY()) <= 1)
                                    Bunny[1] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[3].GetPositionX(),
                                        eQuestPosition[3].GetPositionY()) <= 1)
                                    Bunny[2] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[4].GetPositionX(),
                                        eQuestPosition[4].GetPositionY()) <= 1)
                                    Bunny[3] = (*iter);
                                break;
                            case 46208:
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[5].GetPositionX(),
                                        eQuestPosition[5].GetPositionY()) <= 1)
                                    Cannon[0] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[6].GetPositionX(),
                                        eQuestPosition[6].GetPositionY()
                                        ) <= 1)
                                    Cannon[1] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[7].GetPositionX(),
                                        eQuestPosition[7].GetPositionY()) <= 1)
                                    Cannon[2] = (*iter);
                                if ((*iter)->GetDistance2d(
                                        eQuestPosition[8].GetPositionX(),
                                        eQuestPosition[8].GetPositionY()) <= 1)
                                    Cannon[3] = (*iter);
                                break;
                        }
                    }
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!vehicle->HasEmptySeat(0))
                if (uiTimer <= diff)
                {
                    switch (uiPhase)
                    {
                        case 0:
                            me->GetMotionMaster()->MovePoint(1,
                                eQuestPosition[9].GetPositionX(),
                                eQuestPosition[9].GetPositionY(),
                                eQuestPosition[9].GetPositionZ());
                            GetTargets();
                            ++uiPhase;
                            me->Say(SAY_SANITRON_01);
                            uiTimer = 6000;
                            break;
                        case 1:
                            if (Bunny[0] && Bunny[1])
                            {
                                Bunny[0]->CastSpell(
                                    me, SPELL_DECONTAMINATE_STAGE_1, true);
                                Bunny[1]->CastSpell(
                                    me, SPELL_DECONTAMINATE_STAGE_1, true);
                            }
                            ++uiPhase;
                            uiTimer = 6000;
                            break;
                        case 2:
                            if (Cannon[0] && Cannon[1] && Cannon[2] &&
                                Cannon[3])
                            {
                                me->GetMotionMaster()->MovePoint(2,
                                    eQuestPosition[10].GetPositionX(),
                                    eQuestPosition[10].GetPositionY(),
                                    eQuestPosition[10].GetPositionZ());
                                Cannon[0]->CastSpell(
                                    me, SPELL_CANNON_BURST, true);
                                Cannon[1]->CastSpell(
                                    me, SPELL_CANNON_BURST, true);
                                Cannon[2]->CastSpell(
                                    me, SPELL_CANNON_BURST, true);
                                Cannon[3]->CastSpell(
                                    me, SPELL_CANNON_BURST, true);
                            }
                            ++uiPhase;
                            uiTimer = 6000;
                            break;
                        case 3:
                            if (Technician)
                                me->GetMotionMaster()->MovePoint(3,
                                    eQuestPosition[11].GetPositionX(),
                                    eQuestPosition[11].GetPositionY(),
                                    eQuestPosition[11].GetPositionZ());
                            Technician->Say(SAY_SANITRON_02);
                            ++uiPhase;
                            uiTimer = 3000;
                            break;
                        case 4:
                            if (Bunny[2] && Bunny[3])
                            {
                                me->GetMotionMaster()->MovePoint(4,
                                    eQuestPosition[12].GetPositionX(),
                                    eQuestPosition[12].GetPositionY(),
                                    eQuestPosition[12].GetPositionZ());
                                Bunny[2]->CastSpell(
                                    me, SPELL_DECONTAMINATE_STAGE_2, true);
                                Bunny[3]->CastSpell(
                                    me, SPELL_DECONTAMINATE_STAGE_2, true);
                            }
                            ++uiPhase;
                            uiTimer = 6000;
                            break;
                        case 5:
                            if (vehicle->GetPassenger(0))
                                if (Player* player =
                                        vehicle->GetPassenger(0)->ToPlayer())
                                    player->CompleteQuest(
                                        QUEST_DECONTAMINATION);
                            me->Say(SAY_SANITRON_03);
                            me->GetMotionMaster()->MovePoint(5,
                                eQuestPosition[13].GetPositionX(),
                                eQuestPosition[13].GetPositionY(),
                                eQuestPosition[13].GetPositionZ());
                            ++uiPhase;
                            uiTimer = 3000;
                            break;
                        case 6:
                            me->Say(SAY_SANITRON_04);
                            me->CastSpell(me, SPELL_EXPLOSION);
                            ++uiPhase;
                            uiTimer = 1000;
                            break;
                        case 7:
                            me->SetCanFly(false);
                            vehicle->GetPassenger(0)->RemoveAurasDueToSpell(
                                SPELL_IRRADIATE);
                            vehicle->RemoveAllPassengers();
                            me->setDeathState(JUST_DIED);
                            ++uiPhase;
                            uiTimer = 0;
                            break;
                    }
                }
                else
                    uiTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_sanitron500AI(pCreature);
    }
};

void AddSC_dun_morogh()
{
    new npc_frozen_mountaineer();
    new npc_sanitron500();
}
