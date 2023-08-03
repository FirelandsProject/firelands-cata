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

#include "SplineChainMovementGenerator.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Log.h"

uint32 SplineChainMovementGenerator::SendPathSpline(Unit* me, float velocity, Movement::PointsArray const& wp) const
{
    uint32 numWp = wp.size();
    ASSERT(numWp > 1 && "Every path must have source & destination");
    Movement::MoveSplineInit init(me);
    if (numWp > 2)
        init.MovebyPath(wp);
    else
        init.MoveTo(wp[1], false, true);

    if (velocity > 0.f)
        init.SetVelocity(velocity);

    if (me->IsFlying())
    {
        init.SetFly();
        init.SetUncompressed();
        init.SetSmooth();
    }
    else
        init.SetWalk(_walk);

    // inform formation
    if (me->IsCreature())
        me->ToCreature()->SignalFormationMovement();

    return init.Launch();
}

void SplineChainMovementGenerator::SendSplineFor(Unit* me, uint32 index, uint32& toNext)
{
    ASSERT(index < _chainSize);
    LOG_DEBUG("movement.splinechain", "%s: Sending spline for %u.", me->GetGUID().ToString().c_str(), index);

    SplineChainLink const& thisLink = _chain[index];
    uint32 actualDuration = SendPathSpline(me, thisLink.Velocity, thisLink.Points);
    if (actualDuration != thisLink.ExpectedDuration)
    {
        LOG_DEBUG("movement.splinechain", "%s: Sent spline for %u, duration is %u ms. Expected was %u ms (delta %d ms). Adjusting.", me->GetGUID().ToString().c_str(), index, actualDuration, thisLink.ExpectedDuration, int32(actualDuration) - int32(thisLink.ExpectedDuration));
        toNext = uint32(double(actualDuration)/double(thisLink.ExpectedDuration) * toNext);
    }
    else
    {
        LOG_DEBUG("movement.splinechain", "%s: Sent spline for %u, duration is %u ms.", me->GetGUID().ToString().c_str(), index, actualDuration);
    }
}

void SplineChainMovementGenerator::Initialize(Unit* me)
{
    if (!_chainSize)
    {
        LOG_ERROR("movement.splinechain", "SplineChainMovementGenerator::Initialize: couldn't initialize generator, referenced spline is empty! (%s)", me->GetGUID().ToString().c_str());
        return;
    }

    if (_nextIndex >= _chainSize)
    {
        LOG_WARN("movement.splinechain", "SplineChainMovementGenerator::Initialize: couldn't initialize generator, _nextIndex is >= _chainSize (%s)", me->GetGUID().ToString().c_str());
        _msToNext = 0;
        return;
    }

    if (_nextFirstWP) // this is a resumed movegen that has to start with a partial spline
    {
        if (finished)
            return;

        SplineChainLink const& thisLink = _chain[_nextIndex];
        if (_nextFirstWP >= thisLink.Points.size())
        {
            LOG_ERROR("movement.splinechain", "%s: Attempted to resume spline chain from invalid resume state (%u, %u).", me->GetGUID().ToString().c_str(), _nextIndex, _nextFirstWP);
            _nextFirstWP = thisLink.Points.size() - 1;
        }

        Movement::PointsArray partial(thisLink.Points.begin() + (_nextFirstWP - 1), thisLink.Points.end());
        SendPathSpline(me, thisLink.Velocity, partial);

        LOG_DEBUG("movement.splinechain", "%s: Resumed spline chain generator from resume state.", me->GetGUID().ToString().c_str());

        ++_nextIndex;
        if (_nextIndex >= _chainSize)
            _msToNext = 0;
        else if (!_msToNext)
            _msToNext = 1;
        _nextFirstWP = 0;
    }
    else
    {
        _msToNext = std::max(_chain[_nextIndex].TimeToNext, 1u);
        SendSplineFor(me, _nextIndex, _msToNext);

        ++_nextIndex;
        if (_nextIndex >= _chainSize)
            _msToNext = 0;
    }
}

void SplineChainMovementGenerator::Finalize(Unit* me)
{
    if (!finished)
        return;
    Creature* ownerCreature = me->ToCreature();
    if (CreatureAI* AI = ownerCreature ? ownerCreature->AI() : nullptr)
        AI->MovementInform(SPLINE_CHAIN_MOTION_TYPE, _id);
}

bool SplineChainMovementGenerator::Update(Unit* me, uint32 diff)
{
    if (finished)
        return false;

    // _msToNext being zero here means we're on the final spline
    if (!_msToNext)
    {
        finished = me->movespline->Finalized();
        return !finished;
    }

    if (_msToNext <= diff)
    {
        // Send next spline
        LOG_DEBUG("movement.splinechain", "%s: Should send spline %u (%u ms late).", me->GetGUID().ToString().c_str(), _nextIndex, diff - _msToNext);
        _msToNext = std::max(_chain[_nextIndex].TimeToNext, 1u);
        SendSplineFor(me, _nextIndex, _msToNext);
        ++_nextIndex;
        if (_nextIndex >= _chainSize)
        {
            // We have reached the final spline, once it finalizes we should also finalize the movegen (start checking on next update)
            _msToNext = 0;
            return true;
        }
    }
    else
        _msToNext -= diff;
    return true;
}

SplineChainResumeInfo SplineChainMovementGenerator::GetResumeInfo(Unit const* me) const
{
    if (!_nextIndex)
        return SplineChainResumeInfo(_id, &_chain, _walk, 0, 0, _msToNext);
    if (me->movespline->Finalized())
    {
        if (_nextIndex < _chainSize)
            return SplineChainResumeInfo(_id, &_chain, _walk, _nextIndex, 0, 1u);
        else
            return SplineChainResumeInfo();
    }
    return SplineChainResumeInfo(_id, &_chain, _walk, uint8(_nextIndex - 1), uint8(me->movespline->_currentSplineIdx()), _msToNext);
}

/* static */ void SplineChainMovementGenerator::GetResumeInfo(Unit const* me, SplineChainResumeInfo& info)
{
    if (MovementGenerator const* activeGen = me->GetMotionMaster()->GetMotionSlot(MOTION_SLOT_ACTIVE))
    {
        if (activeGen->GetMovementGeneratorType() == SPLINE_CHAIN_MOTION_TYPE)
        {
            info = reinterpret_cast<SplineChainMovementGenerator const*>(activeGen)->GetResumeInfo(me);
            return;
        }
    }
    info.Chain = nullptr;
}
