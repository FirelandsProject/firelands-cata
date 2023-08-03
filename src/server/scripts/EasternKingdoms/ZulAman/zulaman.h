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

#ifndef DEF_ZULAMAN_H
#define DEF_ZULAMAN_H

#include "CreatureAIImpl.h"

uint32 const EncounterCount = 6;
#define ZulAmanScriptName "instance_zulaman"
#define DataHeader "ZA"

enum ZADataTypes
{
    // Bosss
    DATA_ALKILZON           = 0,
    DATA_NALORAKK           = 1,
    DATA_JANALAI            = 2,
    DATA_HALAZZI            = 3,
    DATA_HEXLORD_MALACRASS  = 4,
    DATA_DAAKARA            = 5,

    // Additional Data
    DATA_VOLJIN,
    DATA_HEXLORD_MALACRASS_TRIGGER,
    DATA_STRANGE_GONG,
    DATA_MASSIVE_GATE,
    DATA_ZULAMAN_SPEEDRUN_STATE,
    DATA_TRIGGER_AMANISHI_GUARDIANS,
    DATA_TRIGGER_AMANISHI_SAVAGES
};

enum ZACreatureIds
{
    // Bosses
    BOSS_AKILZON                    = 23574,
    BOSS_NALORAKK                   = 23576,
    BOSS_JANALAI                    = 23578,
    BOSS_HALAZZI                    = 23577,
    BOSS_HEXLORD_MALACRASS          = 24239,
    BOSS_DAAKARA                    = 23863,

    // Encounter related creatures
    /*Akil'zon*/
    NPC_SOARING_EAGLE               = 24858,

    /*Jan'alai*/
    NPC_FIRE_BOMB_ZULAMAN           = 23920,
    NPC_WORLD_TRIGGER_NOT_IMMUNE_PC = 21252,
    NPC_AMANISHI_HATCHER_1          = 23818,
    NPC_AMANISHI_HATCHER_2          = 24504,
    NPC_AMANI_DRAGONHAWK_HATCHLING  = 23598,
    NPC_DRAGONHAWK_EGG              = 23817,

    NPC_VOLJIN                      = 52924,
    NPC_HEXLORD_MALACRASS_TRIGGER   = 24363,
    NPC_AMANISHI_GUARDIAN           = 23597,
    NPC_AMANISHI_SAVAGE             = 23889
};

enum ZAGameObjectIds
{
    GO_STRANGE_GONG             = 187359,
    GO_MASSIVE_GATE             = 186728,
    GO_DOODAD_ZULAMAN_WIND_DOOR = 186858,
};

enum ZAEvents
{
    EVENT_RIUAL_OF_POWER            = 15897,
    EVENT_UPDATE_SPEED_RUN_TIMER    = 1,
};

enum ZAActions
{
    ACTION_OPEN_MASSIVE_GATES       = 1,
    ACTION_ALERT_AMANISHI_GUARDIANS = 1
};

enum ZAWorldStates
{
    WORLD_STATE_ZULAMAN_TIMER_ENABLED   = 3104,
    WORLD_STATE_ZULAMAN_TIMER           = 3106,
};

template <class AI, class T>
inline AI* GetZulAmanAI(T* obj)
{
    return GetInstanceAI<AI>(obj, ZulAmanScriptName);
}

#define RegisterZulAamanCreatureAI(ai_name) RegisterCreatureAIWithFactory(ai_name, GetZulAmanAI)

#endif
