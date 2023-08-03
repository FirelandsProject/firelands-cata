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

#ifndef FIRELANDS_ARENA_SCORE_H
#define FIRELANDS_ARENA_SCORE_H

#include "BattlegroundScore.h"
#include <sstream>

struct FC_GAME_API ArenaScore : public BattlegroundScore
{
    friend class Arena;

    protected:
        ArenaScore(ObjectGuid playerGuid, uint32 team) : BattlegroundScore(playerGuid, team), TeamId(team == ALLIANCE ? BG_TEAM_ALLIANCE : BG_TEAM_HORDE) { }

        void AppendToPacket(WorldPacket& data, ByteBuffer& content) final override;
        void BuildObjectivesBlock(WorldPacket& data, ByteBuffer& content) final override;

        // For Logging purpose
        std::string ToString() const override
        {
            std::ostringstream stream;
            stream << "Damage done: " << DamageDone << ", Healing done: " << HealingDone << ", Killing blows: " << KillingBlows;
            return stream.str();
        }

        uint8 TeamId; // BattlegroundTeamId
};

struct FC_GAME_API ArenaTeamScore
{
    friend class Arena;
    friend class Battleground;

    protected:
        ArenaTeamScore() : RatingChange(0), MatchmakerRating(0) { }

        virtual ~ArenaTeamScore() { }

        void Reset()
        {
            RatingChange = 0;
            MatchmakerRating = 0;
            TeamName.clear();
        }

        void Assign(int32 ratingChange, uint32 matchMakerRating, std::string const& teamName)
        {
            RatingChange = ratingChange;
            MatchmakerRating = matchMakerRating;
            TeamName = teamName;
        }

        void BuildRatingInfoBlock(WorldPacket& data);
        void BuildTeamInfoLengthBlock(WorldPacket& data);
        void BuildTeamInfoBlock(WorldPacket& data);

        int32 RatingChange;
        uint32 MatchmakerRating;
        std::string TeamName;
};

#endif // FIRELANDS_ARENA_SCORE_H
