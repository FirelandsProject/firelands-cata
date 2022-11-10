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

#include "CombatAI.h"

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
    // Spell Definition
    SPELL_GROUND_RUMBLE_EARTHQUAKE       = 68707,
    SPELL_THROW_FOOTBOMB                 = 69993,
    SPELL_SIGNAL_BACK_TO_SHREDDER        = 70062,
    SPELL_INVISIBILITY_DETECTION_4       = 90161,
    SPELL_INVISIBILITY_DETECTION_5       = 94566,
    SPELL_INVISIBILITY_DETECTION_6       = 94567,
    SPELL_INVISIBILITY_DETECTION_7       = 94568,
    SPELL_QUEST_INVISIBILITY_6           = 82358,
    SPELL_QUEST_INVISIBILITY_7           = 85096,
    SPELL_MARK                           = 70086,
    SPELL_DEATHWINGS_ATTACK              = 66858,
    SPELL_DEATHWING_SOUND_4              = 69988,
    SPELL_INCREASED_MOD_DETECTED_RANGE   = 76651,
    // NPC Definitions
    NPC_SUMMON_BILGWATER_BUCCANEER       = 37179,
    NPC_SUMMON_BILGWATER_BUCCANEER_2     = 37213,
    NPC_FOURTH_AND_GOAL_TARGET           = 37203,
    NPC_NECEESARY_ROUGHNESS_KILL_CREDIT  = 48271,
    NPC_SHARK                            = 37114,
    NPC_DEATHWING                        = 48572,
    // Aura Definitions
    AURA_BILWATER_BUCANEER               = 70016,
    AURA_BILWATER_BUCANEER2              = 70065,
    AURA_SPARKLES                        = 92406,
};
// clang-format on
// clang-format off
enum Sounds {
    SOUND_WOW               = 8574,
    SOUND_WOW1              = 17466,
    SOUND_DEATHWING         = 23227,
    SOUND_DEATHWING_ATTACK  = 23229,
    SOUND_DEATHWING_1       = 23230,
    SOUND_EXIT_VEHICLE      = 14559,
    SOUND_SUMMON_DEATHWING  = 17467,
    SOUND_RAND_1            = 14556,
    SOUND_RAND_2            = 14557,
    SOUND_RAND_3            = 14558,
};
enum QuestEvents {
    EVENT_MOVE_PART0,
    EVENT_MOVE_PART1,
    EVENT_MOVE_PART2,
    EVENT_MOVE_PART3,
    EVENT_MOVE_PART4,
    EVENT_MOVE_PART5,
    EVENT_MOVE_PART6,
    EVENT_MOVE_PART7,
    EVENT_WAIT_TO_MOVE,
    EVENT_WAIT_FOR_NEW_SPEED,
    EVENT_TALK,
    EVENT_ATTACK_SPELL,
    EVENT_PLAY_SOUND1,
    EVENT_PLAY_SOUND2,
    EVENT_EXIT_VEHICLE,
    EVENT_EARTHQUAKE,
    EVENT_SUMMON_DEATHWING,
};
enum QuestDialogs {
    DEATHWING_DIALOG_1      = 37041,
    BUCANEER_DIALOG_1       = 37050,
};
// clang-format on
