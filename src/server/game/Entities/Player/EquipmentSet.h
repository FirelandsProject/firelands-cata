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

#ifndef EquipmentSet_h__
#define EquipmentSet_h__

#include "Define.h"
#include "ObjectGuid.h"
#include <array>
#include <map>

enum EquipmentSetUpdateState
{
    EQUIPMENT_SET_UNCHANGED = 0,
    EQUIPMENT_SET_CHANGED   = 1,
    EQUIPMENT_SET_NEW       = 2,
    EQUIPMENT_SET_DELETED   = 3
};

#define EQUIPMENT_SET_SLOTS 19

struct EquipmentSetInfo
{
    /// Data sent in EquipmentSet related packets
    struct EquipmentSetData
    {
        uint64 Guid = 0;                                        ///< Set Identifier
        uint32 SetID = 0;                                       ///< Index
        uint32 IgnoreMask = 0;                                  ///< Mask of EquipmentSlot
        std::string SetName;
        std::string SetIcon;
        std::array<ObjectGuid, EQUIPMENT_SET_SLOTS> Pieces = {};
        EquipmentSetUpdateState state = EQUIPMENT_SET_UNCHANGED;
    } Data;

    /// Server-side data
    EquipmentSetUpdateState State = EQUIPMENT_SET_NEW;
};

#define MAX_EQUIPMENT_SET_INDEX 10                          // client limit

typedef std::map<uint64, EquipmentSetInfo> EquipmentSetContainer;

#endif // EquipmentSet_h__
