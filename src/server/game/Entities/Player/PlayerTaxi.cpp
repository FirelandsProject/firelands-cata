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

#include "PlayerTaxi.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "Player.h"
#include <sstream>

void PlayerTaxi::InitTaxiNodesForLevel(uint32 race, uint32 chrClass, uint8 level)
{
    // class specific initial known nodes
    switch (chrClass)
    {
        case CLASS_DEATH_KNIGHT:
        {
            for (uint8 i = 0; i < TaxiMaskSize; ++i)
                m_taximask[i] |= sOldContinentsNodesMask[i];
            break;
        }
    }

    uint32 team = Player::TeamForRace(race);

    // Patch 4.2: players will also unlock all taxi nodes within the recommended level range of the player
    for (TaxiNodesEntry const* itr : sTaxiNodesStore)
    {
        // Skip scripted and debug nodes
        if (itr->Flags == TAXI_NODE_FLAG_SCRIPT)
            continue;

        // Skip nodes that are restricted the player's opposite faction
        if ((!(itr->Flags & TAXI_NODE_FLAG_ALLIANCE_RESTRICTED) && team == ALLIANCE)
            || (!(itr->Flags & TAXI_NODE_FLAG_HORDE_RESTRICTED) && team == HORDE))
            continue;

        if (sObjectMgr->IsTaxiNodeUnlockedFor(itr->ID, level))
            SetTaximaskNode(itr->ID);
    }

    // https://wow.gamepedia.com/Flight_path: Patch 4.0.3a (2010-11-23): All characters now know the flight paths to their faction's capital cities, starting zone hubs, and Dalaran.
    switch (team)
    {
        case ALLIANCE:
            SetTaximaskNode(2);   // Stormwind, Elwynn
            SetTaximaskNode(582); // Goldshire, Elwynn
            SetTaximaskNode(589); // Eastvale Logging Camp, Elwynn
            SetTaximaskNode(6);   // Ironforge, Dun Morogh
            SetTaximaskNode(619); // Kharanos, Dun Morogh
            SetTaximaskNode(620); // Gol'Bolar Quarry, Dun Morogh
            SetTaximaskNode(26);  // Lor'danel, Darkshore
            SetTaximaskNode(456); // Dolanaar, Teldrassil
            SetTaximaskNode(457); // Darnassus, Teldrassil
            SetTaximaskNode(94);  // The Exodar
            SetTaximaskNode(624); // Azure Watch, Azuremyst Isle
            SetTaximaskNode(49);  // Moonglade
            SetTaximaskNode(100); // Honor Hold, Hellfire Peninsula
            SetTaximaskNode(245); // Valiance Keep
            break;
        case HORDE:
            SetTaximaskNode(23);  // Orgrimmar, Durotar
            SetTaximaskNode(536); // Sen'jin Village, Durotar
            SetTaximaskNode(537); // Razor Hill, Durotar
            SetTaximaskNode(11);  // Undercity, Tirisfal
            SetTaximaskNode(384); // The Bulwark, Tirisfal
            SetTaximaskNode(460); // Brill, Tirisfal Glades
            SetTaximaskNode(22);  // Thunder Bluff, Mulgore
            SetTaximaskNode(402); // Bloodhoof Village, Mulgore
            SetTaximaskNode(82);  // Silvermoon City
            SetTaximaskNode(625); // Fairbreeze Village, Eversong Woods
            SetTaximaskNode(631); // Falconwing Square, Eversong Woods
            SetTaximaskNode(99);  // Thrallmar, Hellfire Peninsula
            SetTaximaskNode(257); // Warsong Hold
            break;
    }
    SetTaximaskNode(128); // Shattrath, Terokkar Forest
    SetTaximaskNode(310); // Dalaran

    // level dependent taxi hubs
    if (level >= 68)
        SetTaximaskNode(213); // Shattered Sun Staging Area
}

void PlayerTaxi::LoadTaxiMask(std::string const &data)
{
    Tokenizer tokens(data, ' ');

    uint8 index = 0;
    for (Tokenizer::const_iterator iter = tokens.begin(); index < TaxiMaskSize && iter != tokens.end(); ++iter, ++index)
    {
        // load and set bits only for existing taxi nodes
        m_taximask[index] = sTaxiNodesMask[index] & atoul(*iter);
    }
}

void PlayerTaxi::AppendTaximaskTo(ByteBuffer& data, bool all)
{
    data << uint32(TaxiMaskSize);
    if (all)
    {
        for (uint8 i = 0; i < TaxiMaskSize; ++i)
            data << uint8(sTaxiNodesMask[i]);              // all existing nodes
    }
    else
    {
        for (uint8 i = 0; i < TaxiMaskSize; ++i)
            data << uint8(m_taximask[i]);                  // known nodes
    }
}

bool PlayerTaxi::LoadTaxiDestinationsFromString(std::string const& values, uint32 team)
{
    ClearTaxiDestinations();

    Tokenizer Tokenizer(values, ' ');

    for (Tokenizer::const_iterator iter = Tokenizer.begin(); iter != Tokenizer.end(); ++iter)
    {
        uint32 node = atoul(*iter);
        AddTaxiDestination(node);
    }

    if (m_TaxiDestinations.empty())
        return true;

    // Check integrity
    if (m_TaxiDestinations.size() < 2)
        return false;

    for (size_t i = 1; i < m_TaxiDestinations.size(); ++i)
    {
        uint32 cost;
        uint32 path;
        sObjectMgr->GetTaxiPath(m_TaxiDestinations[i - 1], m_TaxiDestinations[i], path, cost);
        if (!path)
            return false;
    }

    // can't load taxi path without mount set (quest taxi path?)
    if (!sObjectMgr->GetTaxiMountDisplayId(GetTaxiSource(), team, true))
        return false;

    return true;
}

std::string PlayerTaxi::SaveTaxiDestinationsToString()
{
    if (m_TaxiDestinations.empty())
        return "";

    std::ostringstream ss;

    for (size_t i = 0; i < m_TaxiDestinations.size(); ++i)
        ss << m_TaxiDestinations[i] << ' ';

    return ss.str();
}

uint32 PlayerTaxi::GetCurrentTaxiPath() const
{
    if (m_TaxiDestinations.size() < 2)
        return 0;

    uint32 path;
    uint32 cost;

    sObjectMgr->GetTaxiPath(m_TaxiDestinations[0], m_TaxiDestinations[1], path, cost);

    return path;
}

std::ostringstream& operator<<(std::ostringstream& ss, PlayerTaxi const& taxi)
{
    for (uint8 i = 0; i < TaxiMaskSize; ++i)
        ss << uint32(taxi.m_taximask[i]) << ' ';
    return ss;
}
