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

#ifndef DEF_ENDTIME_H
#define DEF_ENDTIME_H

#include "CreatureAIImpl.h"
#include "Define.h"

class Creature;

#define DataHeader "ET"
#define ETScriptName "instance_end_time"

uint32 const EncounterCount = 5;

enum ETDataTypes
{
    // Bosses
    DATA_ECHO_OF_BAINE      = 0,
    DATA_ECHO_OF_JAINA      = 1,
    DATA_ECHO_OF_SYLVANAS   = 2,
    DATA_ECHO_OF_TYRANDE    = 3,
    DATA_MUROZOND           = 4,

    // Additional Data
    DATA_HOURGLASS_OF_TIME,
    DATA_MUROZOND_INTRO,
    DATA_NOZDORMU_BRONZE_DRAGON_SHRINE,
    DATA_ARCANE_CIRCLE,
    DATA_COLLECTED_FRAGMENT_OF_JAINAS_STAFF,
};

enum ETCreatures
{
    // Bosses
    BOSS_MUROZOND               = 54432,

    // Encounter Related Creatures
    /*Murozond*/
    NPC_INFINITE_WARDEN         = 54923,
    NPC_INFINITE_SUPRESSOR      = 54920,
    NPC_NOZDORMU_DRAGON_SHRINES = 54751,

    /*Echo of Jaina*/
    NPC_ARCANE_CIRCLE           = 54639,
    NPC_FROST_BLADE             = 54494,
    NPC_BLINK_TARGET            = 54542,
    NPC_FLARECORE_EMBER         = 54446
};

enum ETGameObjectIds
{
    GO_HOURGLASS_OF_TIME = 209249
};

template<class AI>
AI* GetEndTimeAI(Creature* creature)
{
    return GetInstanceAI<AI>(creature, ETScriptName);
}

#define RegisterEndTimeCreatureAI(ai_name) RegisterCreatureAIWithFactory(ai_name, GetEndTimeAI)

#endif // DEF_ENDTIME_H
