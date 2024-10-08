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

#ifndef THE_STOCKADE_H
#define THE_STOCKADE_H

#include "CreatureAIImpl.h"
#include "MotionMaster.h"

#define StormwindStockadeScriptName "instance_the_stockade"
#define DataHeader "SS"

uint32 const EncounterCount = 3;

enum SSDataTypes
{
    DATA_RANDOLPH_MOLOCH = 0,
    DATA_LORD_OVERHEAT   = 1,
    DATA_HOGGER          = 2
};

enum SSCreatureIds
{
    NPC_RANDOLPH_MOLOCH  = 46383,
    NPC_LORD_OVERHEAT    = 46264,
    NPC_HOGGER           = 46254,
    NPC_WARDEN_THELWATER = 46409,
    NPC_MORTIMER_MOLOCH  = 46482
};

template <class AI, class T>
inline AI* GetStormwindStockadeAI(T* obj)
{
    return GetInstanceAI<AI>(obj, StormwindStockadeScriptName);
}

#define RegisterStormwindStockadeAI(ai_name) RegisterCreatureAIWithFactory(ai_name, GetStormwindStockadeAI)

#endif
