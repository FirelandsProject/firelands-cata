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

#include "CreatureAI.h"
#include "AreaBoundary.h"
#include "Creature.h"
#include "CreatureAIImpl.h"
#include "CreatureTextMgr.h"
#include "DBCStores.h"
#include "Language.h"
#include "Log.h"
#include "Map.h"
#include "MapReference.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "SpellMgr.h"
#include "SpellHistory.h"
#include "TemporarySummon.h"
#include "Vehicle.h"
#include "World.h"

//Disable CreatureAI when charmed
void CreatureAI::OnCharmed(bool isNew)
{
    if (isNew && !me->IsCharmed() && me->LastCharmerGUID)
    {
        if (!me->HasReactState(REACT_PASSIVE))
        {
            if (Unit* lastCharmer = ObjectAccessor::GetUnit(*me, me->LastCharmerGUID))
                me->EngageWithTarget(lastCharmer);
        }

        me->LastCharmerGUID.Clear();

        if (!me->IsInCombat())
            EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
    }
    UnitAI::OnCharmed(isNew);
    me->NeedChangeAI = true;
    me->IsAIEnabledAlt = false;
}

AISpellInfoType* UnitAI::AISpellInfo;
AISpellInfoType* GetAISpellInfo(uint32 i) { return &UnitAI::AISpellInfo[i]; }

CreatureAI::CreatureAI(Creature* creature) : UnitAI(creature), me(creature), _boundary(nullptr), _negateBoundary(false), _isEngaged(false), _moveInLOSLocked(false)
{
}

CreatureAI::~CreatureAI()
{
}

void CreatureAI::Talk(uint8 id, WorldObject const* whisperTarget /*= nullptr*/)
{
    sCreatureTextMgr->SendChat(me, id, whisperTarget);
}

void CreatureAI::DoZoneInCombat(Creature* creature /*= nullptr*/)
{
    if (!creature)
        creature = me;

    Map* map = creature->GetMap();
    if (!map->IsDungeon())                                  //use IsDungeon instead of Instanceable, in case battlegrounds will be instantiated
    {
        LOG_ERROR("misc", "DoZoneInCombat call for map that isn't an instance (creature entry = %d)", creature->GetTypeId() == TYPEID_UNIT ? creature->ToCreature()->GetEntry() : 0);
        return;
    }

    if (!map->HavePlayers())
        return;

    for (MapReference const& ref : map->GetPlayers())
    {
        if (Player* player = ref.GetSource())
        {
            if (!player->IsAlive() || !CombatManager::CanBeginCombat(creature, player))
                continue;

            creature->EngageWithTarget(player);

            for (Unit* pet : player->m_Controlled)
                creature->EngageWithTarget(pet);

            if (Unit* vehicle = player->GetVehicleBase())
                creature->EngageWithTarget(vehicle);
        }
    }
}

// scripts does not take care about MoveInLineOfSight loops
// MoveInLineOfSight can be called inside another MoveInLineOfSight and cause stack overflow
void CreatureAI::MoveInLineOfSight_Safe(Unit* who)
{
    if (_moveInLOSLocked == true)
        return;
    _moveInLOSLocked = true;
    MoveInLineOfSight(who);
    _moveInLOSLocked = false;
}

void CreatureAI::MoveInLineOfSight(Unit* who)
{
    if (me->IsEngaged())
        return;

    if (me->HasReactState(REACT_AGGRESSIVE) && !me->IsIgnoringCombat() && me->CanStartAttack(who, false))
        me->EngageWithTarget(who);
}

void CreatureAI::_OnOwnerCombatInteraction(Unit* target)
{
    if (!target || !me->IsAlive())
        return;

    if (!me->HasReactState(REACT_PASSIVE) && me->CanStartAttack(target, true))
        me->EngageWithTarget(target);
}

// Distract creature, if player gets too close while stealthed/prowling
void CreatureAI::TriggerAlert(Unit const* who) const
{
    // If there's no target, or target isn't a player do nothing
    if (!who || who->GetTypeId() != TYPEID_PLAYER)
        return;

    // If this unit isn't an NPC, is already distracted, is fighting, is confused, stunned or fleeing, do nothing
    if (me->GetTypeId() != TYPEID_UNIT || me->IsEngaged() || me->HasUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_STUNNED | UNIT_STATE_FLEEING | UNIT_STATE_DISTRACTED))
        return;

    // Only alert for hostiles!
    if (me->IsCivilian() || me->HasReactState(REACT_PASSIVE) || !me->IsHostileTo(who) || !me->_IsTargetAcceptable(who))
        return;

    // Send alert sound (if any) for this creature
    me->SendAIReaction(AI_REACTION_ALERT);

    // Face the unit (stealthed player) and set distracted state for 5 seconds
    me->GetMotionMaster()->MoveDistract(5 * IN_MILLISECONDS);
    me->StopMoving();
    me->SetFacingTo(me->GetAngle(who));
}

// adapted from logic in Spell:EFfectSummonType before commit 8499434
static bool ShouldFollowOnSpawn(SummonPropertiesEntry const* properties)
{
    // Summons without SummonProperties are generally scripted summons that don't belong to any owner
    if (!properties)
        return false;

    switch (properties->Control)
    {
        case SUMMON_CATEGORY_PET:
            return true;
        case SUMMON_CATEGORY_WILD:
        case SUMMON_CATEGORY_ALLY:
        case SUMMON_CATEGORY_UNK:
            if (properties->Flags & 512)
                return true;

            // Guides. They have their own movement
            if (properties->Flags & SUMMON_PROP_FLAG_UNK14)
                return false;

            switch (SummonTitle(properties->Title))
            {
                case SummonTitle::Pet:
                case SummonTitle::Guardian:
                case SummonTitle::Runeblade:
                case SummonTitle::Minion:
                case SummonTitle::Companion:
                    return true;
                default:
                    return false;
            }
        default:
            return false;
    }
}
void CreatureAI::JustAppeared()
{
    if (!IsEngaged())
    {
        if (TempSummon* summon = me->ToTempSummon())
        {
            // Only apply this to specific types of summons
            if (!summon->GetVehicle() && ShouldFollowOnSpawn(summon->m_Properties))
            {
                if (Unit* owner = summon->GetCharmerOrOwner())
                {
                    summon->GetMotionMaster()->Clear();
                    summon->FollowTarget(owner);
                }
            }
        }
    }
}

void CreatureAI::JustEnteredCombat(Unit* who)
{
    if (!IsEngaged() && !me->CanHaveThreatList())
        EngagementStart(who);
}

void CreatureAI::EnterEvadeMode(EvadeReason why)
{
    if (!_EnterEvadeMode(why))
        return;

    LOG_DEBUG("entities.unit", "Creature %u enters evade mode.", me->GetEntry());

    if (!me->GetVehicle()) // otherwise me will be in evade mode forever
    {
        if (Unit* owner = me->GetCharmerOrOwner())
            me->FollowTarget(owner);
        else
        {
            // Required to prevent attacking creatures that are evading and cause them to reenter combat
            // Does not apply to MoveFollow
            me->AddUnitState(UNIT_STATE_EVADE);
            me->GetMotionMaster()->MoveTargetedHome();
        }
    }

    Reset();
}

bool CreatureAI::UpdateVictim()
{
    if (!IsEngaged())
        return false;

    if (!me->IsAlive())
    {
        EngagementOver();
        return false;
    }

    if (!me->HasReactState(REACT_PASSIVE))
    {
        if (Unit* victim = me->SelectVictim())
            if (victim != me->GetVictim())
                AttackStart(victim);

        return me->GetVictim() != nullptr;
    }
    else if (!me->IsInCombat())
    {
        EnterEvadeMode(EVADE_REASON_NO_HOSTILES);
        return false;
    }
    else if (me->GetVictim())
        me->AttackStop();

    return true;
}

void CreatureAI::EngagementStart(Unit* who)
{
    if (_isEngaged)
    {
        LOG_ERROR("scripts.ai", "CreatureAI::EngagementStart called even though creature is already engaged.");
        return;
    }
    _isEngaged = true;

    me->AtEngage(who);
}

void CreatureAI::EngagementOver()
{
    if (!_isEngaged)
    {
        LOG_ERROR("scripts.ai", "CreatureAI::EngagementOver called even though creature is not currently engaged.");
        return;
    }
    _isEngaged = false;

    me->AtDisengage();
}

bool CreatureAI::_EnterEvadeMode(EvadeReason /*why*/)
{
    if (me->IsInEvadeMode())
        return false;

    if (!me->IsAlive())
    {
        EngagementOver();
        return false;
    }

    me->RemoveAurasOnEvade();

    me->CombatStop(true);
    me->LoadCreaturesAddon();
    me->SetLootRecipient(nullptr);
    me->ResetPlayerDamageReq();
    me->SetLastDamagedTime(0);
    me->SetCannotReachTarget(false);
    me->ResetSpellFocusInfo();
    me->GetSpellHistory()->ResetAllCooldowns();
    me->SetTarget(ObjectGuid::Empty);
    EngagementOver();

    return true;
}

const uint32 BOUNDARY_VISUALIZE_CREATURE = 15425;
const float BOUNDARY_VISUALIZE_CREATURE_SCALE = 0.25f;
const int8 BOUNDARY_VISUALIZE_STEP_SIZE = 1;
const int32 BOUNDARY_VISUALIZE_FAILSAFE_LIMIT = 750;
const float BOUNDARY_VISUALIZE_SPAWN_HEIGHT = 5.0f;
int32 CreatureAI::VisualizeBoundary(uint32 duration, Unit* owner, bool fill) const
{
    typedef std::pair<int32, int32> coordinate;

    if (!owner)
        return -1;

    if (!_boundary || _boundary->empty())
        return LANG_CREATURE_MOVEMENT_NOT_BOUNDED;

    std::queue<coordinate> Q;
    std::unordered_set<coordinate> alreadyChecked;
    std::unordered_set<coordinate> outOfBounds;

    Position startPosition = owner->GetPosition();
    if (!CheckBoundary(&startPosition))
    { // fall back to creature position
        startPosition = me->GetPosition();
        if (!CheckBoundary(&startPosition))
        { // fall back to creature home position
            startPosition = me->GetHomePosition();
            if (!CheckBoundary(&startPosition))
                return LANG_CREATURE_NO_INTERIOR_POINT_FOUND;
        }
    }
    float spawnZ = startPosition.GetPositionZ() + BOUNDARY_VISUALIZE_SPAWN_HEIGHT;

    bool boundsWarning = false;
    Q.push({ 0,0 });
    while (!Q.empty())
    {
        coordinate front = Q.front();
        bool hasOutOfBoundsNeighbor = false;
        for (coordinate off : std::initializer_list<coordinate>{{1,0}, {0,1}, {-1,0}, {0,-1}})
        {
            coordinate next(front.first + off.first, front.second + off.second);
            if (next.first > BOUNDARY_VISUALIZE_FAILSAFE_LIMIT || next.first < -BOUNDARY_VISUALIZE_FAILSAFE_LIMIT || next.second > BOUNDARY_VISUALIZE_FAILSAFE_LIMIT || next.second < -BOUNDARY_VISUALIZE_FAILSAFE_LIMIT)
            {
                boundsWarning = true;
                continue;
            }
            if (alreadyChecked.find(next) == alreadyChecked.end()) // never check a coordinate twice
            {
                Position nextPos(startPosition.GetPositionX() + next.first*BOUNDARY_VISUALIZE_STEP_SIZE, startPosition.GetPositionY() + next.second*BOUNDARY_VISUALIZE_STEP_SIZE, startPosition.GetPositionZ());
                if (CheckBoundary(&nextPos))
                    Q.push(next);
                else
                {
                    outOfBounds.insert(next);
                    hasOutOfBoundsNeighbor = true;
                }
                alreadyChecked.insert(next);
            }
            else
                if (outOfBounds.find(next) != outOfBounds.end())
                    hasOutOfBoundsNeighbor = true;
        }
        if (fill || hasOutOfBoundsNeighbor)
            if (TempSummon* point = owner->SummonCreature(BOUNDARY_VISUALIZE_CREATURE, Position(startPosition.GetPositionX() + front.first*BOUNDARY_VISUALIZE_STEP_SIZE, startPosition.GetPositionY() + front.second*BOUNDARY_VISUALIZE_STEP_SIZE, spawnZ), TEMPSUMMON_TIMED_DESPAWN, duration * IN_MILLISECONDS))
            {
                point->SetObjectScale(BOUNDARY_VISUALIZE_CREATURE_SCALE);
                point->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                point->SetImmuneToAll(true);
                if (!hasOutOfBoundsNeighbor)
                    point->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        Q.pop();
    }
    return boundsWarning ? LANG_CREATURE_MOVEMENT_MAYBE_UNBOUNDED : 0;
}

bool CreatureAI::CheckBoundary(Position const* who) const
{
    if (!_boundary)
        return true;

    if (!who)
        who = me;

    return (CreatureAI::IsInBounds(*_boundary, who) != _negateBoundary);
}

bool CreatureAI::IsInBounds(CreatureBoundary const& boundary, Position const* pos)
{
    for (AreaBoundary const* areaBoundary : boundary)
        if (!areaBoundary->IsWithinBoundary(pos))
            return false;

    return true;
}

bool CreatureAI::CheckInRoom()
{
    if (CheckBoundary())
        return true;
    else
    {
        EnterEvadeMode(EVADE_REASON_BOUNDARY);
        return false;
    }
}

void CreatureAI::SetBoundary(CreatureBoundary const* boundary, bool negateBoundaries /*= false*/)
{
    _boundary = boundary;
    _negateBoundary = negateBoundaries;
    me->DoImmediateBoundaryCheck();
}

Creature* CreatureAI::DoSummon(uint32 entry, Position const& pos, uint32 despawnTime, TempSummonType summonType)
{
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}

Creature* CreatureAI::DoSummon(uint32 entry, WorldObject* obj, float radius, uint32 despawnTime, TempSummonType summonType)
{
    Position pos = obj->GetRandomNearPosition(radius);
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}

Creature* CreatureAI::DoSummonFlyer(uint32 entry, WorldObject* obj, float flightZ, float radius, uint32 despawnTime, TempSummonType summonType)
{
    Position pos = obj->GetRandomNearPosition(radius);
    pos.m_positionZ += flightZ;
    return me->SummonCreature(entry, pos, summonType, despawnTime);
}
