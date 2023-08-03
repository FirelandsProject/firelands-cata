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

#include "Arena.h"
#include "ArenaScore.h"
#include "ArenaTeamMgr.h"
#include "GuildMgr.h"
#include "Guild.h"
#include "Log.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "World.h"
#include "WorldSession.h"
#include "WorldStatePackets.h"

void ArenaScore::AppendToPacket(WorldPacket& data, ByteBuffer& content)
{
    uint32 primaryTree = 0;
    if (Player* player = ObjectAccessor::FindPlayer(PlayerGuid))
        primaryTree = player->GetPrimaryTalentTree(player->GetActiveSpec());

    data.WriteBit(0);                   // Unk 1
    data.WriteBit(0);                   // Unk 2
    data.WriteBit(PlayerGuid[2]);
    data.WriteBit(/*!IsArena*/ 0);      // IsArena
    data.WriteBit(0);                   // Unk 4
    data.WriteBit(0);                   // Unk 5
    data.WriteBit(0);                   // Unk 6
    data.WriteBit(PlayerGuid[3]);
    data.WriteBit(PlayerGuid[0]);
    data.WriteBit(PlayerGuid[5]);
    data.WriteBit(PlayerGuid[1]);
    data.WriteBit(PlayerGuid[6]);
    data.WriteBit(TeamId);
    data.WriteBit(PlayerGuid[7]);

    content << uint32(HealingDone);     // healing done
    content << uint32(DamageDone);      // damage done

    content.WriteByteSeq(PlayerGuid[4]);
    content << uint32(KillingBlows);

    //if (unk5)
    //  content << int32(RatingChange); // RatingChange

    content.WriteByteSeq(PlayerGuid[5]);

    //if (unk 6)
    //    content << uint32();

    //if (unk 2)
    //    content << uint32();

    content.WriteByteSeq(PlayerGuid[1]);
    content.WriteByteSeq(PlayerGuid[6]);

    content << int32(primaryTree);

    BuildObjectivesBlock(data, content);

    data.WriteBit(PlayerGuid[4]);

    content.WriteByteSeq(PlayerGuid[0]);
    content.WriteByteSeq(PlayerGuid[3]);

    //if (unk 4)
    //    content << uint32() unk

    content.WriteByteSeq(PlayerGuid[7]);
    content.WriteByteSeq(PlayerGuid[2]);
}

void ArenaScore::BuildObjectivesBlock(WorldPacket& data, ByteBuffer& /*content*/)
{
    data.WriteBits(0, 24); // Objectives Count
}

void ArenaTeamScore::BuildRatingInfoBlock(WorldPacket& data)
{
    uint32 ratingLost = std::abs(std::min(RatingChange, 0));
    uint32 ratingWon = std::max(RatingChange, 0);

    // should be old rating, new rating, and client will calculate rating change itself
    data << uint32(MatchmakerRating);
    data << uint32(ratingLost);
    data << uint32(ratingWon);
}

void ArenaTeamScore::BuildTeamInfoLengthBlock(WorldPacket& data)
{
    data.WriteBits(TeamName.length(), 8);
}

void ArenaTeamScore::BuildTeamInfoBlock(WorldPacket& data)
{
    data.WriteString(TeamName);
}

Arena::Arena()
{
    StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;

    StartMessageIds[BG_STARTING_EVENT_FIRST]  = ARENA_TEXT_START_ONE_MINUTE;
    StartMessageIds[BG_STARTING_EVENT_SECOND] = ARENA_TEXT_START_THIRTY_SECONDS;
    StartMessageIds[BG_STARTING_EVENT_THIRD]  = ARENA_TEXT_START_FIFTEEN_SECONDS;
    StartMessageIds[BG_STARTING_EVENT_FOURTH] = ARENA_TEXT_START_BATTLE_HAS_BEGUN;
}

void Arena::AddPlayer(Player* player)
{
    Battleground::AddPlayer(player);
    PlayerScores[player->GetGUID().GetCounter()] = new ArenaScore(player->GetGUID(), player->GetBGTeam());

    if (player->GetBGTeam() == ALLIANCE)        // gold
    {
        if (player->GetTeam() == HORDE)
            player->CastSpell(player, SPELL_HORDE_GOLD_FLAG, true);
        else
            player->CastSpell(player, SPELL_ALLIANCE_GOLD_FLAG, true);
    }
    else                                        // green
    {
        if (player->GetTeam() == HORDE)
            player->CastSpell(player, SPELL_HORDE_GREEN_FLAG, true);
        else
            player->CastSpell(player, SPELL_ALLIANCE_GREEN_FLAG, true);
    }

    UpdateArenaWorldState();
}

void Arena::RemovePlayer(Player* /*player*/, ObjectGuid /*guid*/, uint32 /*team*/)
{
    if (GetStatus() == STATUS_WAIT_LEAVE)
        return;

    UpdateArenaWorldState();
    CheckWinConditions();
}

void Arena::FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& data)
{
    data.Worldstates.emplace_back(uint32(ARENA_WORLD_STATE_ALIVE_PLAYERS_GREEN), uint32(GetAlivePlayersCountByTeam(HORDE)));
    data.Worldstates.emplace_back(uint32(ARENA_WORLD_STATE_ALIVE_PLAYERS_GOLD), uint32(GetAlivePlayersCountByTeam(ALLIANCE)));
}

void Arena::UpdateArenaWorldState()
{
    UpdateWorldState(ARENA_WORLD_STATE_ALIVE_PLAYERS_GREEN, GetAlivePlayersCountByTeam(HORDE));
    UpdateWorldState(ARENA_WORLD_STATE_ALIVE_PLAYERS_GOLD, GetAlivePlayersCountByTeam(ALLIANCE));
}

void Arena::HandleKillPlayer(Player* player, Player* killer)
{
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;

    Battleground::HandleKillPlayer(player, killer);

    UpdateArenaWorldState();
    CheckWinConditions();
}

void Arena::RemovePlayerAtLeave(ObjectGuid guid, bool transport, bool sendPacket)
{
    if (isRated() && GetStatus() == STATUS_IN_PROGRESS)
    {
        BattlegroundPlayerMap::const_iterator itr = m_Players.find(guid);
        if (itr != m_Players.end()) // check if the player was a participant of the match, or only entered through gm command (appear)
        {
            // if the player was a match participant, calculate rating
            uint32 team = itr->second.Team;

            ArenaTeam* winnerArenaTeam = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(GetOtherTeam(team)));
            ArenaTeam* loserArenaTeam = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(team));

            // left a rated match while the encounter was in progress, consider as loser
            if (winnerArenaTeam && loserArenaTeam && winnerArenaTeam != loserArenaTeam)
            {
                if (Player* player = _GetPlayer(itr->first, itr->second.OfflineRemoveTime != 0, "Arena::RemovePlayerAtLeave"))
                    loserArenaTeam->MemberLost(player, GetArenaMatchmakerRating(GetOtherTeam(team)));
                else
                    loserArenaTeam->OfflineMemberLost(guid, GetArenaMatchmakerRating(GetOtherTeam(team)));
            }
        }
    }

    // remove player
    Battleground::RemovePlayerAtLeave(guid, transport, sendPacket);
}

void Arena::CheckWinConditions()
{
    if (!GetAlivePlayersCountByTeam(ALLIANCE) && GetPlayersCountByTeam(HORDE))
        EndBattleground(HORDE);
    else if (GetPlayersCountByTeam(ALLIANCE) && !GetAlivePlayersCountByTeam(HORDE))
        EndBattleground(ALLIANCE);
}

void Arena::EndBattleground(uint32 winner)
{
    // arena rating calculation
    if (isRated())
    {
        uint32 loserTeamRating        = 0;
        uint32 loserMatchmakerRating  = 0;
        int32  loserChange            = 0;
        int32  loserMatchmakerChange  = 0;
        uint32 winnerTeamRating       = 0;
        uint32 winnerMatchmakerRating = 0;
        int32  winnerChange           = 0;
        int32  winnerMatchmakerChange = 0;
        bool   guildAwarded           = false;

        // In case of arena draw, follow this logic:
        // winnerArenaTeam => ALLIANCE, loserArenaTeam => HORDE
        ArenaTeam* winnerArenaTeam = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(winner == 0 ? ALLIANCE : winner));
        ArenaTeam* loserArenaTeam = sArenaTeamMgr->GetArenaTeamById(GetArenaTeamIdForTeam(winner == 0 ? HORDE : GetOtherTeam(winner)));

        if (winnerArenaTeam && loserArenaTeam && winnerArenaTeam != loserArenaTeam)
        {
            // In case of arena draw, follow this logic:
            // winnerMatchmakerRating => ALLIANCE, loserMatchmakerRating => HORDE
            loserTeamRating = loserArenaTeam->GetRating();
            loserMatchmakerRating = GetArenaMatchmakerRating(winner == 0 ? HORDE : GetOtherTeam(winner));
            winnerTeamRating = winnerArenaTeam->GetRating();
            winnerMatchmakerRating = GetArenaMatchmakerRating(winner == 0 ? ALLIANCE : winner);

            if (winner != 0)
            {
                winnerMatchmakerChange = winnerArenaTeam->WonAgainst(winnerMatchmakerRating, loserMatchmakerRating, winnerChange);
                loserMatchmakerChange = loserArenaTeam->LostAgainst(loserMatchmakerRating, winnerMatchmakerRating, loserChange);

                LOG_DEBUG("bg.arena", "match Type: %u --- Winner: old rating: %u, rating gain: %d, old MMR: %u, MMR gain: %d --- Loser: old rating: %u, rating loss: %d, old MMR: %u, MMR loss: %d ---",
                    GetArenaType(), winnerTeamRating, winnerChange, winnerMatchmakerRating, winnerMatchmakerChange,
                    loserTeamRating, loserChange, loserMatchmakerRating, loserMatchmakerChange);

                SetArenaMatchmakerRating(winner, winnerMatchmakerRating + winnerMatchmakerChange);
                SetArenaMatchmakerRating(GetOtherTeam(winner), loserMatchmakerRating + loserMatchmakerChange);

                // bg team that the client expects is different to TeamId
                // alliance 1, horde 0
                uint8 winnerTeam = winner == ALLIANCE ? BG_TEAM_ALLIANCE : BG_TEAM_HORDE;
                uint8 loserTeam = winner == ALLIANCE ? BG_TEAM_HORDE : BG_TEAM_ALLIANCE;

                _arenaTeamScores[winnerTeam].Assign(winnerChange, winnerMatchmakerRating, winnerArenaTeam->GetName());
                _arenaTeamScores[loserTeam].Assign(loserChange, loserMatchmakerRating, loserArenaTeam->GetName());

                LOG_DEBUG("bg.arena", "Arena match Type: %u for Team1Id: %u - Team2Id: %u ended. WinnerTeamId: %u. Winner rating: +%d, Loser rating: %d",
                    GetArenaType(), GetArenaTeamIdByIndex(TEAM_ALLIANCE), GetArenaTeamIdByIndex(TEAM_HORDE), winnerArenaTeam->GetId(), winnerChange, loserChange);

                if (sWorld->getBoolConfig(CONFIG_ARENA_LOG_EXTENDED_INFO))
                    for (auto const& score : PlayerScores)
                        if (Player* player = ObjectAccessor::FindConnectedPlayer(ObjectGuid(HighGuid::Player, score.first)))
                        {
                            LOG_DEBUG("bg.arena", "Statistics match Type: %u for %s (GUID: %u, Team: %d, IP: %s): %s",
                                GetArenaType(), player->GetName().c_str(), score.first, player->GetArenaTeamId(GetArenaType() == 5 ? 2 : GetArenaType() == 3),
                                player->GetSession()->GetRemoteAddress().c_str(), score.second->ToString().c_str());
                        }
            }
            // Deduct 16 points from each teams arena-rating if there are no winners after 45+2 minutes
            else
            {
                _arenaTeamScores[BG_TEAM_ALLIANCE].Assign(ARENA_TIMELIMIT_POINTS_LOSS, winnerMatchmakerRating, winnerArenaTeam->GetName());
                _arenaTeamScores[BG_TEAM_HORDE].Assign(ARENA_TIMELIMIT_POINTS_LOSS, loserMatchmakerRating, loserArenaTeam->GetName());

                winnerArenaTeam->FinishGame(ARENA_TIMELIMIT_POINTS_LOSS);
                loserArenaTeam->FinishGame(ARENA_TIMELIMIT_POINTS_LOSS);
            }

            uint8 aliveWinners = GetAlivePlayersCountByTeam(winner);

            for (auto const& i : GetPlayers())
            {
                uint32 team = i.second.Team;

                if (i.second.OfflineRemoveTime)
                {
                    // if rated arena match - make member lost!
                    if (team == winner)
                        winnerArenaTeam->OfflineMemberLost(i.first, loserMatchmakerRating, winnerMatchmakerChange);
                    else
                    {
                        if (winner == 0)
                            winnerArenaTeam->OfflineMemberLost(i.first, loserMatchmakerRating, winnerMatchmakerChange);

                        loserArenaTeam->OfflineMemberLost(i.first, winnerMatchmakerRating, loserMatchmakerChange);
                    }
                    continue;
                }

                Player* player = _GetPlayer(i.first, i.second.OfflineRemoveTime != 0, "Arena::EndBattleground");
                if (!player)
                    continue;

                // per player calculation
                if (team == winner)
                {
                    // update achievement BEFORE personal rating update
                    uint32 rating = player->GetArenaPersonalRating(winnerArenaTeam->GetSlot());
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA, rating ? rating : 1);
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA, GetMapId());
                    player->ModifyCurrency(CURRENCY_TYPE_CONQUEST_META_ARENA, sWorld->getIntConfig(CONFIG_CURRENCY_CONQUEST_POINTS_ARENA_REWARD));

                    // Last standing - Rated 5v5 arena & be solely alive player
                    if (GetArenaType() == ARENA_TYPE_5v5 && aliveWinners == 1 && player->IsAlive())
                        player->CastSpell(player, SPELL_LAST_MAN_STANDING, true);

                    if (!guildAwarded)
                    {
                        guildAwarded = true;
                        if (uint32 guildId = GetBgMap()->GetOwnerGuildId(player->GetBGTeam()))
                            if (Guild* guild = sGuildMgr->GetGuildById(guildId))
                                guild->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA, std::max<uint32>(winnerArenaTeam->GetRating(), 1), 0, 0, nullptr, player);
                    }

                    winnerArenaTeam->MemberWon(player, loserMatchmakerRating, winnerMatchmakerChange);
                }
                else
                {
                    if (winner == 0)
                        winnerArenaTeam->MemberLost(player, loserMatchmakerRating, winnerMatchmakerChange);

                    loserArenaTeam->MemberLost(player, winnerMatchmakerRating, loserMatchmakerChange);

                    // Arena lost => reset the win_rated_arena having the "no_lose" condition
                    player->ResetAchievementCriteria(ACHIEVEMENT_CRITERIA_CONDITION_NO_LOSE, 0);
                }
            }

            // save the stat changes
            winnerArenaTeam->SaveToDB();
            loserArenaTeam->SaveToDB();
            // send updated arena team stats to players
            // this way all arena team members will get notified, not only the ones who participated in this match
            winnerArenaTeam->NotifyStatsChanged();
            loserArenaTeam->NotifyStatsChanged();
        }
    }

    // end battleground
    Battleground::EndBattleground(winner);
}
