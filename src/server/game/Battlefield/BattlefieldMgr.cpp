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

#include "BattlefieldMgr.h"
#include "BattlefieldWG.h"
#include "BattlefieldTB.h"
#include "Log.h"
#include "Player.h"

BattlefieldMgr::BattlefieldMgr()
{
    _updateTimer = 0;
}

BattlefieldMgr::~BattlefieldMgr()
{
    for (BattlefieldSet::iterator itr = _battlefieldSet.begin(); itr != _battlefieldSet.end(); ++itr)
        delete *itr;

    _battlefieldMap.clear();
}

BattlefieldMgr* BattlefieldMgr::instance()
{
    static BattlefieldMgr instance;
    return &instance;
}

void BattlefieldMgr::InitBattlefield()
{
    Battlefield* wg = new BattlefieldWG();
    // respawn, init variables
    if (!wg->SetupBattlefield())
    {
        LOG_INFO("bg.battlefield", "Battlefield: Wintergrasp init failed.");
        delete wg;
    }
    else
    {
        _battlefieldSet.push_back(wg);
        LOG_INFO("bg.battlefield", "Battlefield: Wintergrasp successfully initiated.");
    }

    Battlefield* tb = new BattlefieldTB;
    // respawn, init variables
    if (!tb->SetupBattlefield())
    {
        LOG_DEBUG("bg.battlefield", "Battlefield: Tol Barad init failed.");
        delete tb;
    }
    else
    {
        _battlefieldSet.push_back(tb);
        LOG_DEBUG("bg.battlefield", "Battlefield: Tol Barad successfully initiated.");
    }
}

void BattlefieldMgr::AddZone(uint32 zoneId, Battlefield* bf)
{
    _battlefieldMap[zoneId] = bf;
}

void BattlefieldMgr::HandlePlayerEnterZone(Player* player, uint32 zoneId)
{
    BattlefieldMap::iterator itr = _battlefieldMap.find(zoneId);
    if (itr == _battlefieldMap.end())
        return;

    Battlefield* bf = itr->second;
    if (!bf->IsEnabled() || bf->HasPlayer(player))
        return;

    bf->HandlePlayerEnterZone(player, zoneId);
    LOG_DEBUG("bg.battlefield", "Player %u entered battlefield id %u", player->GetGUID().GetCounter(), bf->GetTypeId());
}

void BattlefieldMgr::HandlePlayerLeaveZone(Player* player, uint32 zoneId)
{
    BattlefieldMap::iterator itr = _battlefieldMap.find(zoneId);
    if (itr == _battlefieldMap.end())
        return;

    // teleport: remove once in removefromworld, once in updatezone
    if (!itr->second->HasPlayer(player))
        return;

    itr->second->HandlePlayerLeaveZone(player, zoneId);
    LOG_DEBUG("bg.battlefield", "Player %u left battlefield id %u", player->GetGUID().GetCounter(), itr->second->GetTypeId());
}

Battlefield* BattlefieldMgr::GetBattlefieldToZoneId(uint32 zoneId)
{
    BattlefieldMap::iterator itr = _battlefieldMap.find(zoneId);
    if (itr == _battlefieldMap.end())
    {
        // no handle for this zone, return
        return nullptr;
    }

    if (!itr->second->IsEnabled())
        return nullptr;

    return itr->second;
}

Battlefield* BattlefieldMgr::GetBattlefieldByBattleId(uint32 battleId)
{
    for (BattlefieldSet::iterator itr = _battlefieldSet.begin(); itr != _battlefieldSet.end(); ++itr)
    {
        if ((*itr)->GetBattleId() == battleId)
            return *itr;
    }
    return nullptr;
}

Battlefield* BattlefieldMgr::GetBattlefieldByGUID(ObjectGuid guid)
{
    for (BattlefieldSet::iterator itr = _battlefieldSet.begin(); itr != _battlefieldSet.end(); ++itr)
        if ((*itr)->GetGUID() == guid)
            return *itr;

    return nullptr;
}

ZoneScript* BattlefieldMgr::GetZoneScript(uint32 zoneId)
{
    BattlefieldMap::iterator itr = _battlefieldMap.find(zoneId);
    if (itr != _battlefieldMap.end())
        return itr->second;

    return nullptr;
}

void BattlefieldMgr::Update(uint32 diff)
{
    _updateTimer += diff;
    if (_updateTimer > BATTLEFIELD_OBJECTIVE_UPDATE_INTERVAL)
    {
        for (BattlefieldSet::iterator itr = _battlefieldSet.begin(); itr != _battlefieldSet.end(); ++itr)
            if ((*itr)->IsEnabled())
                (*itr)->Update(_updateTimer);
        _updateTimer = 0;
    }
}
