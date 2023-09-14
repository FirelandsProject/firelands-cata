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

#ifndef FIRELANDS_DISABLEMGR_H
#define FIRELANDS_DISABLEMGR_H

#include "Define.h"

class Unit;

enum DisableType
{
    DISABLE_TYPE_SPELL                  = 0,
    DISABLE_TYPE_QUEST                  = 1,
    DISABLE_TYPE_MAP                    = 2,
    DISABLE_TYPE_BATTLEGROUND           = 3,
    DISABLE_TYPE_ACHIEVEMENT_CRITERIA   = 4,
    DISABLE_TYPE_OUTDOORPVP             = 5,
    DISABLE_TYPE_VMAP                   = 6,
    DISABLE_TYPE_MMAP                   = 7,
    DISABLE_TYPE_LFG_MAP                = 8,
    DISABLE_TYPE_ITEM                   = 9
};

enum SpellDisableTypes
{
    SPELL_DISABLE_PLAYER            = 0x1,
    SPELL_DISABLE_CREATURE          = 0x2,
    SPELL_DISABLE_PET               = 0x4,
    SPELL_DISABLE_DEPRECATED_SPELL  = 0x8,
    SPELL_DISABLE_MAP               = 0x10,
    SPELL_DISABLE_AREA              = 0x20,
    SPELL_DISABLE_LOS               = 0x40,
    MAX_SPELL_DISABLE_TYPE = (  SPELL_DISABLE_PLAYER | SPELL_DISABLE_CREATURE | SPELL_DISABLE_PET |
                                SPELL_DISABLE_DEPRECATED_SPELL | SPELL_DISABLE_MAP | SPELL_DISABLE_AREA |
                                SPELL_DISABLE_LOS)
};

enum ItemDisableTypes
{
    ITEM_DISABLE_AUCTIONHOUSE     = 0x01,
    ITEM_DISABLE_AUCTIONHOUSE_BOT = 0x02,
    ITEM_DISABLE_LOOT_DROP        = 0x04,
    ITEM_DISABLE_VENDOR           = 0x08,

    MAX_ITEM_DISABLE_TYPE = (ITEM_DISABLE_AUCTIONHOUSE | ITEM_DISABLE_AUCTIONHOUSE_BOT | ITEM_DISABLE_LOOT_DROP | ITEM_DISABLE_VENDOR)
};

enum MMapDisableTypes
{
    MMAP_DISABLE_PATHFINDING    = 0x0
};

namespace DisableMgr
{
    FC_GAME_API void LoadDisables();
    FC_GAME_API bool IsDisabledFor(DisableType type, uint32 entry, Unit const* unit, uint8 flags = 0);
    FC_GAME_API void CheckQuestDisables();
    FC_GAME_API bool IsVMAPDisabledFor(uint32 entry, uint8 flags);
    FC_GAME_API bool IsPathfindingEnabled(uint32 mapId);
}

#endif //FIRELANDS_DISABLEMGR_H
