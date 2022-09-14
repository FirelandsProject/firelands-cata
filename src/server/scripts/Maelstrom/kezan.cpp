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

enum QuestRollingWithMyHomies
{
    // Quest ID
    QUEST_ROLLING_WITH_MY_HOMIES = 14071,
    // Objectives ID's
    OBJECTIVE_IZZY_PICKED_UP = 265516,
    OBJECTIVE_ACE_PICKED_UP = 265517,
    OBJECTIVE_GOBBER_PICKED_UP = 265518,
    // NPC defs
    NPC_HOT_ROD = 34840,
    NPC_IZZY = 34890,
    NPC_ACE = 34892,
    NPC_GOBBER = 34954,
    // Summons
    SUMMON_NPC_IZZY = 34959,
    SUMMON_NPC_ACE = 34957,
    SUMMON_NPC_GOBBER = 34958,
    // Inv Detections
    SPELL_INV_DETECTION_1 = 66403,
    SPELL_INV_DETECTION_2 = 66404,
    SPELL_INV_DETECTION_3 = 66405,
    // Summon Spells
    SPELL_SUMMON_IZZY = 66600,
    SPELL_SUMMON_ACE = 66597,
    SPELL_SUMMON_GOBBER = 66599,
    // Re-Summon NPC Spells
    SPELL_RESUMMON_IZZY = 66644,
    SPELL_RESUMMON_ACE = 66646,
    SPELL_RESUMMON_GOBBER = 66645,
    // ROD Spells
    SPELL_HOT_ROD_KNOCKBACK = 66301,
    // Quest Actions
    ACTION_ROD_ENTER_VEHICLE = 1,
    // Vehicle Sounds
    RADIO_SOUND = 23406,
    KLAXON_SOUND = 22491,
    // Quest Item
    HOT_ROD_ITEM = 46856
};

std::unordered_map<uint32, std::tuple<uint32, uint32>> const seatPerHomie = {
    {SUMMON_NPC_ACE, {1, SPELL_RESUMMON_ACE}},
    {SUMMON_NPC_GOBBER, {2, SPELL_RESUMMON_GOBBER}},
    {SUMMON_NPC_IZZY, {3, SPELL_RESUMMON_IZZY}}};

std::unordered_map<uint32, std::tuple<uint32, uint32, uint32>> const
    goalAndSpellPerHomie = {
        {NPC_ACE,
            {OBJECTIVE_ACE_PICKED_UP, SPELL_SUMMON_ACE, SPELL_INV_DETECTION_1}},
        {NPC_GOBBER, {OBJECTIVE_GOBBER_PICKED_UP, SPELL_SUMMON_GOBBER,
                         SPELL_INV_DETECTION_2}},
        {NPC_IZZY, {OBJECTIVE_IZZY_PICKED_UP, SPELL_SUMMON_IZZY,
                       SPELL_INV_DETECTION_3}},
};

std::unordered_map<uint32, bool> objectivesCompleted = {
    {OBJECTIVE_IZZY_PICKED_UP, false}, {OBJECTIVE_ACE_PICKED_UP, false},
    {OBJECTIVE_GOBBER_PICKED_UP, false}};

class quest_rolling_with_my_homies : public QuestScript
{
   public:
    quest_rolling_with_my_homies() : QuestScript("quest_rolling_with_my_homies")
    {
    }

    void OnQuestStatusChange(Player* player, Quest const* /*quest*/,
        QuestStatus /*oldStatus*/, QuestStatus newStatus) override
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
                    if (me->m_movementInfo.HasMovementFlag(
                            MOVEMENTFLAG_FORWARD))
                    {
                        player->CastSpell(
                            nullptr, SPELL_HOT_ROD_KNOCKBACK, true);
                    }

                    context.Repeat();
                });

            for (auto it : seatPerHomie)
            {
                if (Creature* homie =
                        player->GetSummonedCreatureByEntry(it.first))
                {
                    homie->AI()->DoAction(ACTION_ROD_ENTER_VEHICLE);
                }
                else if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) ==
                         QUEST_STATUS_REWARDED)
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
        if (who->GetEntry() != NPC_HOT_ROD || !who->IsVehicle()) return;

        Vehicle* vehicle = who->GetVehicleKit();
        Unit* driver = vehicle->GetPassenger(0);
        if (!driver) return;

        Player* player = driver->ToPlayer();
        if (!player) return;

        if (player->GetQuestStatus(QUEST_ROLLING_WITH_MY_HOMIES) !=
            QUEST_STATUS_INCOMPLETE)
            return;

        if (me->GetDistance(player) > 10.f) return;

        uint32 objectiveId, summonSpell, invisibilityDetectionSpell;
        std::tie(objectiveId, summonSpell, invisibilityDetectionSpell) =
            goalAndSpellPerHomie.at(me->GetEntry());

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
                    std::tie(seatId, resummonSpellId) =
                        seatPerHomie.at(me->GetEntry());
                    me->EnterVehicle(vehicle->GetBase(), seatId);
                }
            }
        }
    }
};

/* ###
#   Finish Quest Rolling With my Homies
### */

void AddSC_kezan()
{
    // Quest 14071
    new quest_rolling_with_my_homies();
    RegisterSpellScript(spell_radio);
    RegisterSpellScript(spell_klaxon);
    RegisterCreatureAI(npc_hot_rod);
    RegisterCreatureAI(npc_homies);
    RegisterCreatureAI(npc_homies_summon);
}
