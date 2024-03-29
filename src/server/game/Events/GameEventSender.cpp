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

#include "GameEventSender.h"
#include "Battleground.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Map.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Util.h"

void GameEvents::Trigger(uint32 gameEventId, WorldObject* source, WorldObject* target)
{
    ASSERT(source || target, "At least one of [source] or [target] must be provided");

    WorldObject* refForMapAndZoneScript = Coalesce<WorldObject>(source, target);

    ZoneScript* zoneScript = refForMapAndZoneScript->GetZoneScript();
    if (!zoneScript && refForMapAndZoneScript->IsPlayer())
        zoneScript = refForMapAndZoneScript->FindZoneScript();

    if (zoneScript)
        zoneScript->ProcessEvent(target, gameEventId, source);

    Map* map = refForMapAndZoneScript->GetMap();

    if (target && target->IsGameObject())
        if (GameObject* goTarget = target->ToGameObject())
            if (GameObjectAI* goAI = goTarget->AI())
                goAI->EventInform(gameEventId);

    if (source && source->IsPlayer())
        if (Player* sourcePlayer = source->ToPlayer())
            TriggerForPlayer(gameEventId, sourcePlayer);

    TriggerForMap(gameEventId, map, source, target);
}

void GameEvents::TriggerForPlayer(uint32 gameEventId, Player* source)
{
    Map* map = source->GetMap();
    if (map->Instanceable())
        source->StartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, gameEventId);
}

void GameEvents::TriggerForMap(uint32 gameEventId, Map* map, WorldObject* source, WorldObject* target)
{
    if (BattlegroundMap* bgMap = map->ToBattlegroundMap())
        bgMap->GetBG()->ProcessEvent(target, gameEventId, source);

    map->ScriptsStart(sEventScripts, gameEventId, source, target);
}
