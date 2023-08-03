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

#ifndef _ITEM_ENCHANTMENT_MGR_H
#define _ITEM_ENCHANTMENT_MGR_H

#include "Common.h"

enum class ItemRandomEnchantmentType : uint8
{
    Property    = 0,
    Suffix      = 1
};

struct ItemRandomEnchantmentId
{
    ItemRandomEnchantmentId() = default;
    ItemRandomEnchantmentId(ItemRandomEnchantmentType type, uint32 id) : Type(type), Id(id) { }

    ItemRandomEnchantmentType Type = ItemRandomEnchantmentType::Property;
    uint32 Id = 0;
};

FC_GAME_API void LoadRandomEnchantmentsTable();
FC_GAME_API ItemRandomEnchantmentId GenerateItemRandomPropertyId(uint32 item_id);
FC_GAME_API uint32 GenerateEnchSuffixFactor(uint32 item_id);
FC_GAME_API uint32 GetRandomPropertyPoints(uint32 itemLevel, uint32 quality, uint32 inventoryType, uint32 subclass);

#endif
