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

#ifndef SC_SYSTEM_H
#define SC_SYSTEM_H

#include "Define.h"
#include "Hash.h"
#include "WaypointDefines.h"
#include <unordered_map>
#include <vector>

class Creature;
struct SplineChainLink;

class FC_GAME_API SystemMgr
{
    public:
        static SystemMgr* instance();

        // database
        void LoadScriptWaypoints();
        void LoadScriptSplineChains();

        WaypointPath const* GetPath(uint32 creatureEntry) const;

        std::vector<SplineChainLink> const* GetSplineChain(uint32 entry, uint16 chainId) const;
        std::vector<SplineChainLink> const* GetSplineChain(Creature const* who, uint16 id) const;

    protected:
        typedef std::pair<uint32, uint16> ChainKeyType; // creature entry + chain ID

        SystemMgr();
        ~SystemMgr();

        std::unordered_map<uint32, WaypointPath> _waypointStore;
        std::unordered_map<ChainKeyType, std::vector<SplineChainLink>> m_mSplineChainsMap; // spline chains
};

#define sScriptSystemMgr SystemMgr::instance()

#endif
