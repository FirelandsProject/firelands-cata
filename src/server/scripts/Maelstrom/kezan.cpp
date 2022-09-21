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

#include "Log.h"
#include "MotionMaster.h"
#include "Player.h"
#include "QuestDef.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "UnitDefines.h"
#include "Vehicle.h"

/* ###
#   Quest Rolling With My Homies
### */

// clang-format off
enum QuestRollingWithMyHomies
{
    // Quest ID
    QUEST_ROLLING_WITH_MY_HOMIES      = 14071,
    // Objectives ID's
    OBJECTIVE_IZZY_PICKED_UP          = 265516,
    OBJECTIVE_ACE_PICKED_UP           = 265517,
    OBJECTIVE_GOBBER_PICKED_UP        = 265518,
    // NPC defs
    NPC_HOT_ROD                       = 34840,
    NPC_IZZY                          = 34890,
    NPC_ACE                           = 34892,
    NPC_GOBBER                        = 34954,
    // Summons
    SUMMON_NPC_IZZY                   = 34959,
    SUMMON_NPC_ACE                    = 34957,
    SUMMON_NPC_GOBBER                 = 34958,
    // Inv Detections
    SPELL_INV_DETECTION_1             = 66403,
    SPELL_INV_DETECTION_2             = 66404,
    SPELL_INV_DETECTION_3             = 66405,
    // Summon Spells
    SPELL_SUMMON_IZZY                 = 66600,
    SPELL_SUMMON_ACE                  = 66597,
    SPELL_SUMMON_GOBBER               = 66599,
    // Re-Summon NPC Spells
    SPELL_RESUMMON_IZZY               = 66644,
    SPELL_RESUMMON_ACE                = 66646,
    SPELL_RESUMMON_GOBBER             = 66645,
    // ROD Spells
    SPELL_HOT_ROD_KNOCKBACK           = 66301,
    // Quest Actions
    ACTION_ROD_ENTER_VEHICLE          = 1,
    // Vehicle Sounds
    RADIO_SOUND                       = 23406,
    KLAXON_SOUND                      = 22491,
    // Quest Item
    HOT_ROD_ITEM                      = 46856
};
// clang-format on

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

// clang-format off
enum QuestNecessaryRoughness
{
    QUEST_NECESSARY_ROUGHNESS            = 24502,
    QUEST_FOURTH_AND_GOAL                = 28414,
    // Despawn Spell Definitions
    SPELL_DESPAWN_SHARKS                 = 69987,
    // Summon Spell Definitions
    SPELL_SUMMON_BILGWATER_BUCCANEER     = 70015,
    SPELL_SUMMON_BILGWATER_BUCCANEER_2   = 70075,
    SPELL_SUMMON_DEATHWING               = 66322,
    // Spell Definition
    SPELL_GROUND_RUMBLE_EARTHQUAKE       = 78607,
    SPELL_THROW_FOOTBOMB                 = 69993,
    SPELL_KICK_FOOTBOMB                  = 70052,
    SPELL_GENERIC_INV_DETECTION_4        = 90161,
    // NPC Definitions
    NPC_SUMMON_BILGWATER_BUCCANEER       = 37179,
    NPC_SUMMON_BILGWATER_BUCCANEER_2     = 37213,
    NPC_FOURTH_AND_GOAL_KILL_CREDIT      = 37203,
    NPC_NECEESARY_ROUGHNESS_KILL_CREDIT  = 48271,
    NPC_SHARK                            = 37114,
    // Aura Definitions
    AURA_BILWATER_BUCANEER               = 70016,
    AURA_BILWATER_BUCANEER2              = 70065,
};
// clang-format on
// Used in fourth_and_goal Logic
Position const playerTeleportPos = {-8250.910156f, 1484.290039f, 41.499901f, 3.124140f};

// For Quests:
// QUEST_NECESSARY_ROUGHNESS
// QUEST_FOURTH_AND_GOAL
class quest_fourth_and_goal : public QuestScript
{
  public:
    quest_fourth_and_goal() : QuestScript("quest_fourth_and_goal") {}

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/, QuestStatus /*oldStatus*/, QuestStatus newStatus) override
    {
        if (newStatus == QUEST_STATUS_INCOMPLETE)
        {
            player->ExitVehicle();

            player->GetScheduler().Schedule(1s,
                [player](TaskContext /*ctx*/)
                {
                    player->RemoveAurasDueToSpell(SPELL_GENERIC_INV_DETECTION_4);
                    player->NearTeleportTo(playerTeleportPos);

                    player->GetScheduler().Schedule(1s,
                        [player](TaskContext /*ctx*/) { player->CastSpell(nullptr, SPELL_SUMMON_BILGWATER_BUCCANEER_2, true); });
                });
        }
        else if (newStatus == QUEST_STATUS_COMPLETE)
        {
            player->CastSpell(player, SPELL_GROUND_RUMBLE_EARTHQUAKE, true);
            player->CastSpell(nullptr, SPELL_SUMMON_DEATHWING, true);
        }
        else if (newStatus == QUEST_STATUS_REWARDED)
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
        if (quest->GetQuestId() == QUEST_NECESSARY_ROUGHNESS)
        {
            player->NearTeleportTo(playerTeleportPos);
            player->GetScheduler().Schedule(500ms,
                [player](TaskContext /*ctx*/)
                {
                    player->CastSpell(nullptr, SPELL_SUMMON_BILGWATER_BUCCANEER, true);
                    player->RemoveAurasDueToSpell(SPELL_GENERIC_INV_DETECTION_4);
                });
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
struct npc_bucanneer_gob : public ScriptedAI
{
    npc_bucanneer_gob(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        if (me->GetEntry() == NPC_SUMMON_BILGWATER_BUCCANEER_2 && me->IsSummon())
        {
            Unit* summoner = me->ToTempSummon()->GetSummoner();
            if (summoner && summoner->IsPlayer())
            {
                summoner->EnterVehicle(me);
            }
        }
    }

    void OnCharmed(bool /*apply*/) override {}

    void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply) override
    {
        Player* player = who->ToPlayer();
        if (!player)
            return;

        if (apply)
        {
            me->SetSpeed(MOVE_RUN, 0.001f);
            player->RemoveAurasDueToSpell(SPELL_GENERIC_INV_DETECTION_4);

            if (player->GetQuestStatus(QUEST_NECESSARY_ROUGHNESS) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(NPC_NECEESARY_ROUGHNESS_KILL_CREDIT, me->GetGUID());
                me->AddAura(AURA_BILWATER_BUCANEER, me);

                for (uint8 count = 0; count < 8; ++count)
                    me->SummonCreature(NPC_SHARK, SharkPos[count], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120 * IN_MILLISECONDS);
            }
            else if (player->GetQuestStatus(QUEST_FOURTH_AND_GOAL) == QUEST_STATUS_INCOMPLETE)
                me->AddAura(AURA_BILWATER_BUCANEER2, me);
        }
        else
        {
            player->CastSpell(player, SPELL_GENERIC_INV_DETECTION_4, true);
            me->CastSpell(nullptr, SPELL_DESPAWN_SHARKS, true);
            me->GetScheduler().Schedule(1s, [this](TaskContext /*context*/) { me->DespawnOrUnsummon(); });
        }
    }
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

    void HandleAfterCast()
    {
        if (GetCaster()->IsVehicle())
            if (Unit* passenger = GetCaster()->GetVehicleKit()->GetPassenger(0))
                if (Player* player = passenger->ToPlayer())
                    player->KilledMonsterCredit(NPC_FOURTH_AND_GOAL_KILL_CREDIT);
    }

    void Register() override { AfterCast.Register(&npc_fourth_and_goal_kick_footbomb::HandleAfterCast); }
};

// NPC entry 37203
struct npc_fourth_and_goal_target : public ScriptedAI
{
    npc_fourth_and_goal_target(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override { me->setActive(true); }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_KICK_FOOTBOMB)
        {
            if (caster->GetVehicleKit())
                if (Unit* passenger = caster->GetVehicleKit()->GetPassenger(0))
                    if (Player* player = passenger->ToPlayer())
                        player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
        }
    }

    void JustReachedHome() override {}
};

// NPC entry 48572
struct npc_fourth_and_goal_deathwing : public ScriptedAI
{
    npc_fourth_and_goal_deathwing(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        me->setActive(true);

        // TODO waypoints when parser is available
    }
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
    RegisterCreatureAI(npc_bucanneer_gob);
    RegisterCreatureAI(npc_shark_gob);
    RegisterSpellScript(npc_fourth_and_goal_kick_footbomb);
    RegisterCreatureAI(npc_fourth_and_goal_target);
    RegisterCreatureAI(npc_fourth_and_goal_deathwing);
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
