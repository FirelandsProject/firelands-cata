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

#ifndef FIRELANDS_SPAWNDATA_H
#define FIRELANDS_SPAWNDATA_H

#include "Position.h"
#include "PhaseShift.h"

class Creature;
class GameObject;
class Pool;
struct PoolTemplate;

enum SpawnObjectType
{
    SPAWN_TYPE_CREATURE = 0,
    SPAWN_TYPE_GAMEOBJECT = 1,
    NUM_SPAWN_TYPES_WITH_DATA, // SKIP
    NUM_SPAWN_TYPES = NUM_SPAWN_TYPES_WITH_DATA // SKIP
};

enum SpawnObjectTypeMask
{
    SPAWN_TYPEMASK_CREATURE = (1 << SPAWN_TYPE_CREATURE),
    SPAWN_TYPEMASK_GAMEOBJECT = (1 << SPAWN_TYPE_GAMEOBJECT),

    SPAWN_TYPEMASK_WITH_DATA = (1 << NUM_SPAWN_TYPES_WITH_DATA) - 1,
    SPAWN_TYPEMASK_ALL = (1 << NUM_SPAWN_TYPES) - 1
};

enum SpawnGroupFlags
{
    SPAWNGROUP_FLAG_NONE                = 0x00,
    SPAWNGROUP_FLAG_SYSTEM              = 0x01,
    SPAWNGROUP_FLAG_COMPATIBILITY_MODE  = 0x02,
    SPAWNGROUP_FLAG_MANUAL_SPAWN        = 0x04,
    SPAWNGROUP_FLAG_DYNAMIC_SPAWN_RATE  = 0x08,
    SPAWNGROUP_FLAG_ESCORTQUESTNPC      = 0x10,

    SPAWNGROUP_FLAGS_ALL = (SPAWNGROUP_FLAG_SYSTEM | SPAWNGROUP_FLAG_COMPATIBILITY_MODE | SPAWNGROUP_FLAG_MANUAL_SPAWN | SPAWNGROUP_FLAG_DYNAMIC_SPAWN_RATE | SPAWNGROUP_FLAG_ESCORTQUESTNPC)
};

struct SpawnGroupTemplateData
{
    uint32 groupId;
    std::string name;
    uint32 mapId;
    SpawnGroupFlags flags;
};

namespace Firelands { namespace Impl {
    template <typename T>
    struct SpawnObjectTypeForImpl { static_assert(!std::is_same<T,T>::value, "This type does not have an associated spawn type!"); };
    template <> struct SpawnObjectTypeForImpl<Creature> { static constexpr SpawnObjectType value = SPAWN_TYPE_CREATURE; };
    template <> struct SpawnObjectTypeForImpl<GameObject> { static constexpr SpawnObjectType value = SPAWN_TYPE_GAMEOBJECT; };
}}

struct SpawnData;
struct SpawnMetadata
{
    static constexpr bool TypeInMask(SpawnObjectType type, SpawnObjectTypeMask mask) { return ((1 << type) & mask); }
    static constexpr bool TypeHasData(SpawnObjectType type) { return (type < NUM_SPAWN_TYPES_WITH_DATA); }
    static constexpr bool TypeIsValid(SpawnObjectType type) { return (type < NUM_SPAWN_TYPES); }
    template <typename T>
    static constexpr SpawnObjectType TypeFor = Firelands::Impl::SpawnObjectTypeForImpl<T>::value;

    SpawnData const* ToSpawnData() const { return TypeHasData(type) ? reinterpret_cast<SpawnData const*>(this) : nullptr; }

    SpawnObjectType const type;
    uint32 spawnId = 0;
    uint32 mapId = MAPID_INVALID;
    bool dbData = true;
    SpawnGroupTemplateData const* spawnGroupData = nullptr;

    protected:
    SpawnMetadata(SpawnObjectType t) : type(t) {}
};

struct SpawnData : public SpawnMetadata
{
    uint32 id = 0; // entry in respective _template table
    Position spawnPoint;
    int32 spawntimesecs = 0;
    uint8 spawnMask = 0;
    uint8 phaseUseFlags = 0;
    uint32 phaseId = DEFAULT_PHASE;
    uint32 phaseGroup = 0;
    int32 terrainSwapMap = -1;
    uint32 scriptId = 0;

    protected:
    SpawnData(SpawnObjectType t) : SpawnMetadata(t) {}
};

#endif
