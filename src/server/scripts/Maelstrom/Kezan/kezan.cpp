/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for
 * Copyright information
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

#include <unordered_map>

#include "CombatAI.h"
#include "Log.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "QuestDef.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "UnitDefines.h"
#include "Vehicle.h"
#include "kezan.h"

/* ###
#   Quest Rolling With My Homies
### */

std::unordered_map<uint32, std::tuple<uint32, uint32>> const seatPerHomie = {{SUMMON_NPC_ACE, {1, SPELL_RESUMMON_ACE}},
    {SUMMON_NPC_GOBBER, {2, SPELL_RESUMMON_GOBBER}}, {SUMMON_NPC_IZZY, {3, SPELL_RESUMMON_IZZY}}};

std::unordered_map<uint32, std::tuple<uint32, uint32, uint32>> const goalAndSpellPerHomie = {
    {NPC_ACE, {OBJECTIVE_ACE_PICKED_UP, SPELL_SUMMON_ACE, SPELL_INV_DETECTION_1}},
    {NPC_GOBBER, {OBJECTIVE_GOBBER_PICKED_UP, SPELL_SUMMON_GOBBER, SPELL_INV_DETECTION_2}},
    {NPC_IZZY, {OBJECTIVE_IZZY_PICKED_UP, SPELL_SUMMON_IZZY, SPELL_INV_DETECTION_3}},
};

std::unordered_map<uint32, bool> objectivesCompleted = {
    {OBJECTIVE_IZZY_PICKED_UP, false}, {OBJECTIVE_ACE_PICKED_UP, false}, {OBJECTIVE_GOBBER_PICKED_UP, false}};

class quest_rolling_with_my_homies : public QuestScript
{
  public:
    quest_rolling_with_my_homies() : QuestScript("quest_rolling_with_my_homies") {}

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_INCOMPLETE)
        {
            player->AddItem(HOT_ROD_ITEM, 1);
        }
    }
};

struct npc_hot_rod : public ScriptedAI
{
    npc_hot_rod(Creature* creature) : ScriptedAI(creature) {}

    void OnCharmed(bool /*apply*/) override {}

    void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) override
    {
        if (me->IsSummon() && apply)
        {
            Player* player = who->ToPlayer();
            if (!player)
            {
                return;
            }

            me->GetScheduler().Schedule(250ms,
                [this, player](TaskContext context)
                {
                    if (me->m_movementInfo.HasMovementFlag(MOVEMENTFLAG_FORWARD))
                    {
                        player->CastSpell(nullptr, SPELL_HOT_ROD_KNOCKBACK, true);
                    }

                    context.Repeat();
                });

            for (auto it : seatPerHomie)
            {
                if (Creature* homie = player->GetSummonedCreatureByEntry(it.first))
                {
                    homie->AI()->DoAction(ACTION_ROD_ENTER_VEHICLE);
                }
                else if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) == QUEST_STATUS_REWARDED)
                {
                    uint32 seatId, resummonSpellId;
                    std::tie(seatId, resummonSpellId) = it.second;
                    player->CastSpell(nullptr, resummonSpellId, true);
                }
            }
        }
    }
};

class spell_klaxon : public SpellScript
{
    PrepareSpellScript(spell_klaxon);

    void HandleOnHit()
    {
        if (Unit* owner = GetCaster()->GetOwner())
            if (Player* player = owner->ToPlayer())
                GetCaster()->PlayDirectSound(KLAXON_SOUND, player);
    }

    void Register() override { OnHit.Register(&spell_klaxon::HandleOnHit); }
};

class spell_radio : public SpellScript
{
    PrepareSpellScript(spell_radio);

    void HandleOnHit()
    {
        if (Unit* caster = GetCaster()->GetOwner())
            if (caster->IsPlayer())
                GetCaster()->PlayDistanceSound(RADIO_SOUND, caster->ToPlayer());
    }

    void Register() override { OnHit.Register(&spell_radio::HandleOnHit); }
};

struct npc_homies : public ScriptedAI
{
    npc_homies(Creature* creature) : ScriptedAI(creature) {}

    void MoveInLineOfSight(Unit* who) override
    {
        if (who->GetEntry() != NPC_HOT_ROD || !who->IsVehicle())
            return;

        Vehicle* vehicle = who->GetVehicleKit();
        Unit* driver = vehicle->GetPassenger(0);
        if (!driver)
            return;

        Player* player = driver->ToPlayer();
        if (!player)
            return;

        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) != QUEST_STATUS_INCOMPLETE)
            return;

        if (me->GetDistance(player) > 10.f)
            return;

        uint32 objectiveId, summonSpell, invisibilityDetectionSpell;
        std::tie(objectiveId, summonSpell, invisibilityDetectionSpell) = goalAndSpellPerHomie.at(me->GetEntry());

        if (objectivesCompleted.at(objectiveId))
        {
            return;
        }

        player->RemoveAurasDueToSpell(invisibilityDetectionSpell);
        player->CastSpell(nullptr, summonSpell, true);
        objectivesCompleted[objectiveId] = true;
    }
};

struct npc_homies_summon : public ScriptedAI
{
    npc_homies_summon(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        if (me->IsSummon())
        {
            if (Unit* owner = me->ToTempSummon()->GetOwner())
            {
                if (Player* player = owner->ToPlayer())
                    player->KilledMonsterCredit(me->GetEntry());

                DoAction(ACTION_ROD_ENTER_VEHICLE);
            }
        }
    }

    void DoAction(int32 /*action*/) override
    {
        if (me->IsSummon())
        {
            if (Unit* owner = me->ToTempSummon()->GetOwner())
            {
                if (Vehicle* vehicle = owner->GetVehicle())
                {
                    uint32 seatId, resummonSpellId;
                    std::tie(seatId, resummonSpellId) = seatPerHomie.at(me->GetEntry());
                    me->EnterVehicle(vehicle->GetBase(), seatId);
                }
            }
        }
    }
};

void InitQuestRollingWithMyHomies()
{
    // Quest 14071
    new quest_rolling_with_my_homies();
    RegisterSpellScript(spell_radio);
    RegisterSpellScript(spell_klaxon);
    RegisterCreatureAI(npc_hot_rod);
    RegisterCreatureAI(npc_homies);
    RegisterCreatureAI(npc_homies_summon);
}

/* ###
#   Finish Quest Rolling With my Homies
### */

/* ###
#   Quest Necessary roughness
#   Quest Fourth and Goal
### */

// For Quests:
// QUEST_NECESSARY_ROUGHNESS
// QUEST_FOURTH_AND_GOAL
class quest_fourth_and_goal : public QuestScript
{
  public:
    quest_fourth_and_goal() : QuestScript("quest_fourth_and_goal") {}

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {

        if (newStatus == QUEST_STATUS_COMPLETE || newStatus == QUEST_STATUS_REWARDED)
        {
            player->CastSpell(player, SPELL_GROUND_RUMBLE_EARTHQUAKE, true);
        }
    }
};

// NPC entry 37106
class npc_coach_crosscheck : public CreatureScript
{
  public:
    npc_coach_crosscheck() : CreatureScript("npc_coach_crosscheck") {}

    struct npc_coach_crosscheckAI : public ScriptedAI
    {
        npc_coach_crosscheckAI(Creature* creature) : ScriptedAI(creature) {}
    };

    bool OnQuestAccept(Player* player, Creature* /*creature*/, Quest const* quest) override
    {
        player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);

        if (quest->GetQuestId() == QUEST_NECESSARY_ROUGHNESS)
        {
            player->GetScheduler().Schedule(
                500ms, [player](TaskContext /*ctx*/) { player->CastSpell(player, SPELL_SUMMON_BILGWATER_BUCCANEER, true); });
        }
        else if (quest->GetQuestId() == QUEST_FOURTH_AND_GOAL)
        {
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_5);
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_6);
            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
            if (player->IsMounted())
            {
                player->ExitVehicle();
            }
            player->GetScheduler().Schedule(
                500ms, [player](TaskContext /*ctx*/) { player->CastSpell(player, SPELL_SUMMON_BILGWATER_BUCCANEER_2, true); });
        }

        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override { return new npc_coach_crosscheckAI(creature); }
};

const Position SharkPos[8] = {
    {-8278.00f, 1485.00f, 43.14f, 6.28f},
    {-8285.00f, 1485.00f, 43.90f, 6.28f},
    {-8285.61f, 1489.94f, 43.90f, 6.28f},
    {-8285.76f, 1480.03f, 43.90f, 6.28f},
    {-8290.68f, 1475.38f, 43.95f, 6.28f},
    {-8291.06f, 1480.00f, 43.98f, 6.28f},
    {-8290.98f, 1487.85f, 43.99f, 6.28f},
    {-8290.90f, 1492.98f, 43.90f, 6.28f},
};

// NPC entry 37179
// NPC entry 37213
class npc_bilgewater_bucaneer : public CreatureScript
{
  public:
    npc_bilgewater_bucaneer() : CreatureScript("npc_bilgewater_bucaneer") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature) override
    {
        pPlayer->EnterVehicle(pCreature->ToUnit(), 0);
        pPlayer->KilledMonsterCredit(NPC_NECEESARY_ROUGHNESS_KILL_CREDIT, pCreature->GetGUID());

        return true;
    }

    struct npc_bucanneer_gob : public VehicleAI
    {

        npc_bucanneer_gob(Creature* creature) : VehicleAI(creature) {}

        EventMap m_events;
        ObjectGuid m_playerGUID;
        bool m_DeathwingSummoned;
        uint32 m_counter;

        void Reset() override
        {
            m_DeathwingSummoned = false;
            m_counter = 0;
            me->AddAura(SPELL_QUEST_INVISIBILITY_6, me);
            me->AddAura(SPELL_QUEST_INVISIBILITY_7, me);
            me->AddUnitState(UNIT_STATE_ROOT);
            me->AddUnitMovementFlag(MOVEMENTFLAG_ROOT);
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_4);
                player->AddAura(SPELL_INVISIBILITY_DETECTION_7, player);
                me->NearTeleportTo(-8250.910156f, 1484.290039f, 41.499901f, 3.14f);
                m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
            }
        }

        void SpellHit(Unit* /*caster*/, SpellInfo const* spell) override
        {
            if (!m_DeathwingSummoned)
                if (spell->Id == SPELL_SIGNAL_BACK_TO_SHREDDER)
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(SOUND_WOW, player);
                        m_events.ScheduleEvent(EVENT_SUMMON_DEATHWING, 100);
                    }
        }

        void PassengerBoarded(Unit* unit, int8 /*seat*/, bool apply) override
        {
            Player* player = unit->ToPlayer();
            if (!player)
            {
                return;
            }

            if (apply)
            {
                if (player->GetQuestStatus(QUEST_NECESSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE)
                {
                    me->AddAura(AURA_BILWATER_BUCANEER, me);

                    for (uint8 count = 0; count < 8; ++count)
                        me->SummonCreature(NPC_SHARK, SharkPos[count], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120 * IN_MILLISECONDS);
                }
                else if (player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) == QUEST_STATUS_INCOMPLETE)
                {
                    me->CastSpell(me, SPELL_INCREASED_MOD_DETECTED_RANGE, true);
                    if (Creature* npc = me->FindNearestCreature(NPC_FOURTH_AND_GOAL_TARGET, 50.0f))
                        player->ToUnit()->Talk(BUCANEER_DIALOG_1, CHAT_MSG_RAID_BOSS_WHISPER, 50.0f, player);
                }
            }
            else
            {
                player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                player->AddAura(SPELL_INVISIBILITY_DETECTION_4, player);

                me->RemoveAura(SPELL_INCREASED_MOD_DETECTED_RANGE);
                me->DespawnOrUnsummon(100);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);
            VehicleAI::UpdateAI(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_PLAY_SOUND1:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(SOUND_WOW1, player);
                    m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 1000);
                    break;
                }
                case EVENT_PLAY_SOUND2:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(RAND(SOUND_RAND_1, SOUND_RAND_2, SOUND_RAND_3), player);
                    m_counter += 1;
                    if (m_counter < 3)
                        m_events.ScheduleEvent(EVENT_PLAY_SOUND2, 3000);
                    break;
                }
                case EVENT_SUMMON_DEATHWING:
                {
                    if (!m_DeathwingSummoned)
                        if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        {
                            m_DeathwingSummoned = true;
                            player->RemoveAura(SPELL_INVISIBILITY_DETECTION_7);
                            player->AddAura(SPELL_INVISIBILITY_DETECTION_6, player);
                            player->SummonCreature(NPC_DEATHWING, -8230.59f, 1482.14f, 110.9156f, TEMPSUMMON_MANUAL_DESPAWN);
                            player->KilledMonsterCredit(NPC_FOURTH_AND_GOAL_TARGET);
                            m_events.CancelEvent(EVENT_PLAY_SOUND1);
                            player->PlayDirectSound(SOUND_SUMMON_DEATHWING, player);
                            m_events.ScheduleEvent(EVENT_PLAY_SOUND2, 3000);
                        }
                    break;
                }
                }
            }

            if (!UpdateVictim())
                return;
            else
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override { return new npc_bucanneer_gob(creature); }
};

// NPC entry 37114
struct npc_shark_gob : public ScriptedAI
{
    npc_shark_gob(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetWalk(true);

        me->GetScheduler().Schedule(3s, [this](TaskContext /*context*/)
            { me->GetMotionMaster()->MovePoint(1, -8260.0f, me->GetPositionY(), me->GetPositionZ()); });
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_THROW_FOOTBOMB)
        {
            if (caster->GetVehicleKit())
                if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(0))
                    if (Player* player = passenger->ToPlayer())
                        player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());

            caster->Kill(me);
        }
    }

    void JustReachedHome() override {}
};

// Spell Id 70052
class npc_fourth_and_goal_kick_footbomb : public SpellScript
{
    PrepareSpellScript(npc_fourth_and_goal_kick_footbomb);

    void HandleBeforeCast()
    {
        if (Position* dest = const_cast<WorldLocation*>(GetExplTargetDest()))
        {
            if (dest->GetPositionY() > 1450.0f && dest->GetPositionY() < 1525.0f)
                if (dest->GetPositionZ() > 100.0f && dest->GetPositionZ() < 300.0f)
                    GetCaster()->CastSpell(GetCaster(), SPELL_SIGNAL_BACK_TO_SHREDDER);
        }
    }

    void Register() override { BeforeCast.Register(&npc_fourth_and_goal_kick_footbomb::HandleBeforeCast); }
};

// NPC entry 37203
struct npc_fourth_and_goal_target : public ScriptedAI
{
    npc_fourth_and_goal_target(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->CastSpell(me, SPELL_MARK, true);
        me->AddAura(SPELL_QUEST_INVISIBILITY_7, me);
    }
};

// NPC entry 48572
class npc_fourth_and_goal_deathwing : public CreatureScript
{
  public:
    npc_fourth_and_goal_deathwing() : CreatureScript("npc_fourth_and_goal_deathwing") {}

    struct npc_fourth_and_goal_deathwingAI : public ScriptedAI
    {
        npc_fourth_and_goal_deathwingAI(Creature* creature) : ScriptedAI(creature) {}

        EventMap m_events;
        ObjectGuid m_playerGUID;
        uint32 m_nextPoint;
        float m_newSpeed;

        void Reset() override
        {
            me->AddAura(SPELL_QUEST_INVISIBILITY_6, me);
            me->setActive(true);
            me->SetDisableGravity(true);
            me->SetObjectScale(0.6f);
            me->GetMotionMaster()->MovePoint(2001, -8320.0f, 1473.0f, 110.0f);
            m_nextPoint = 0;
            m_newSpeed = 0;
        }

        void IsSummonedBy(Unit* summoner) override
        {
            if (Player* player = summoner->ToPlayer())
            {
                m_playerGUID = player->GetGUID();
                player->PlayDirectSound(SOUND_WOW, player);
            }
        }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE)
                return;

            switch (id)
            {
            case 2001:
                m_events.ScheduleEvent(EVENT_MOVE_PART1, 10);
                break;
            case 2002:
                m_events.ScheduleEvent(EVENT_MOVE_PART2, 10);
                break;
            case 2003:
                m_events.ScheduleEvent(EVENT_MOVE_PART3, 10);
                break;
            case 2004:
                m_events.ScheduleEvent(EVENT_MOVE_PART4, 10);
                break;
            case 2005:
                m_events.ScheduleEvent(EVENT_MOVE_PART5, 10);
                break;
            case 2006:
                m_events.ScheduleEvent(EVENT_MOVE_PART6, 10);
                break;
            case 2007:
                m_events.ScheduleEvent(EVENT_MOVE_PART7, 10);
                break;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            m_events.Update(diff);

            while (uint32 eventId = m_events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_WAIT_TO_MOVE:
                {
                    if (m_newSpeed)
                        me->SetSpeed(MOVE_RUN, m_newSpeed);
                    switch (m_nextPoint)
                    {
                    case 2004:
                        me->GetMotionMaster()->MovePoint(2004, -8330.0f, 1460.0f, 110.0f);
                        break;
                    }
                    m_nextPoint = 0;
                    m_newSpeed = 0;
                    break;
                }
                case EVENT_WAIT_FOR_NEW_SPEED:
                    if (m_newSpeed)
                        me->SetSpeed(MOVE_RUN, m_newSpeed);
                    m_newSpeed = 0;
                    break;
                case EVENT_MOVE_PART1:
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(SOUND_DEATHWING, player);
                    me->SetObjectScale(0.4f);
                    me->GetMotionMaster()->MovePoint(2002, -8320.0f, 1480.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART2:
                    me->SetSpeed(MOVE_RUN, 0.2f);
                    m_events.ScheduleEvent(EVENT_TALK, 2000);
                    me->GetMotionMaster()->MovePoint(2003, -8330.0f, 1500.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART3:
                    m_events.ScheduleEvent(EVENT_ATTACK_SPELL, 3000);
                    m_nextPoint = 2004;
                    m_newSpeed = 1.0f;
                    m_events.ScheduleEvent(EVENT_WAIT_TO_MOVE, 6500);
                    break;
                case EVENT_MOVE_PART4:
                    me->GetMotionMaster()->MovePoint(2005, -8320.0f, 1500.0f, 110.0f);
                    break;
                case EVENT_MOVE_PART5:
                    m_events.ScheduleEvent(EVENT_PLAY_SOUND1, 2000);
                    me->SetObjectScale(0.6f);
                    me->GetMotionMaster()->MovePoint(2006, -8250.0f, 1480.0f, 90.0f);
                    break;
                case EVENT_MOVE_PART6:
                    me->SetObjectScale(0.8f);
                    m_events.ScheduleEvent(EVENT_EXIT_VEHICLE, 2000);
                    m_events.ScheduleEvent(EVENT_EARTHQUAKE, 6000);
                    me->GetMotionMaster()->MovePoint(2007, -7900.0f, 1460.0f, 90.0f);
                    break;
                case EVENT_MOVE_PART7:
                    me->GetMotionMaster()->MovePoint(2008, -7900.0f, 1460.0f, 90.0f);
                    break;
                case EVENT_TALK:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        Talk(0, player);
                        player->PlayDirectSound(23228, player);
                    }
                    break;
                }
                case EVENT_ATTACK_SPELL:
                {
                    if (Creature* target = me->FindNearestCreature(42196, 250.0f))
                    {
                        me->SetFacingToObject(target);
                        me->CastSpell(target, SPELL_DEATHWINGS_ATTACK, true);
                    }
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                        player->PlayDirectSound(SOUND_DEATHWING_ATTACK, player);
                    break;
                }
                case EVENT_PLAY_SOUND1:
                {
                    me->CastSpell(me, SPELL_DEATHWING_SOUND_4, true);
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->PlayDirectSound(SOUND_DEATHWING_1, player);
                        player->ToUnit()->Talk(DEATHWING_DIALOG_1, CHAT_MSG_RAID_BOSS_WHISPER, 25.0f, player);
                    }
                    break;
                }
                case EVENT_EXIT_VEHICLE:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->ExitVehicle();
                        player->PlayDirectSound(SOUND_EXIT_VEHICLE, player);
                    }
                    break;
                }
                case EVENT_EARTHQUAKE:
                {
                    if (Player* player = ObjectAccessor::GetPlayer(*me, m_playerGUID))
                    {
                        player->CastSpell(
                            player, SPELL_GROUND_RUMBLE_EARTHQUAKE, true); // This Earthquake is taken drom Duskhaven..
                    }
                    break;
                }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override { return new npc_fourth_and_goal_deathwingAI(creature); }
};

// Spell Id 69987
class spell_kezan_despawn_sharks : public SpellScript
{
    PrepareSpellScript(spell_kezan_despawn_sharks);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (Creature* creature = GetHitCreature())
            if (creature->IsSummon())
                if (creature->ToTempSummon()->GetSummoner() == GetCaster())
                    creature->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnEffectHitTarget.Register(&spell_kezan_despawn_sharks::HandleHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void InitQuestNecessaryRoughness()
{
    new quest_fourth_and_goal();
    new npc_coach_crosscheck();
    new npc_bilgewater_bucaneer();
    new npc_fourth_and_goal_deathwing();
    RegisterCreatureAI(npc_shark_gob);
    RegisterSpellScript(npc_fourth_and_goal_kick_footbomb);
    RegisterCreatureAI(npc_fourth_and_goal_target);
    RegisterSpellScript(spell_kezan_despawn_sharks);
}

/* ###
#   Finish Quest Necessary roughness
#   Finish Quest Fourth and Goal
### */

void AddSC_kezan()
{
    InitQuestRollingWithMyHomies();
    InitQuestNecessaryRoughness();
}
