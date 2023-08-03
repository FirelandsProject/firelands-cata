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

#ifndef FIRELANDS_WAYPOINTMOVEMENTGENERATOR_H
#define FIRELANDS_WAYPOINTMOVEMENTGENERATOR_H

/**
 * @page PathMovementGenerator is used to generate movements
 * of waypoints and flight paths.  Each serves the purpose
 * of generate activities so that it generates updated
 * packets for the players.
 */

#include "DBCStructure.h"
#include "MovementGenerator.h"
#include "PathMovementBase.h"
#include "Timer.h"

class Creature;
struct WaypointNode;
struct WaypointPath;

template<class T>
class WaypointMovementGenerator;

template<>
class WaypointMovementGenerator<Creature> : public MovementGeneratorMedium<Creature, WaypointMovementGenerator<Creature>>, public PathMovementBase<Creature, WaypointPath const*>
{
    public:
        explicit WaypointMovementGenerator(uint32 pathId = 0, bool repeating = true);
        explicit WaypointMovementGenerator(WaypointPath& path, bool repeating = true);

        ~WaypointMovementGenerator() { _path = nullptr; }

        void DoInitialize(Creature*);
        void DoFinalize(Creature*);
        void DoReset(Creature*);
        bool DoUpdate(Creature*, uint32 diff);

        MovementGeneratorType GetMovementGeneratorType() const override { return WAYPOINT_MOTION_TYPE; }
        void UnitSpeedChanged() override { _recalculateSpeed = true; }
        void Pause(uint32 timer = 0) override;
        void Resume(uint32 overrideTimer = 0) override;
        bool GetResetPosition(Unit*, float& x, float& y, float& z) override;

    private:
        void ProcessWaypointArrival(Creature*, WaypointNode const&);
        void StartMove(Creature*, bool relaunch = false);
        bool IsAllowedToMove(Creature*);

        uint32 _lastSplineId;
        uint32 _pathId;
        int32 _waypointDelay;
        int32 _pauseTime;
        bool _waypointReached;
        bool _recalculateSpeed;
        bool _repeating;
        bool _loadedFromDB;
        bool _stalled;
        bool _hasBeenStalled;
        bool _done;
};

#endif
