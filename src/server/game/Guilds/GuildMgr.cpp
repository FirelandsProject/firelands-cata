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

#include "GuildMgr.h"
#include "AchievementMgr.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "Guild.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "World.h"

GuildMgr::GuildMgr() : NextGuildId(1)
{ }

GuildMgr::~GuildMgr()
{
    for (GuildContainer::iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
        delete itr->second;
}

void GuildMgr::AddGuild(Guild* guild)
{
    GuildStore[guild->GetId()] = guild;
}

void GuildMgr::RemoveGuild(ObjectGuid::LowType guildId)
{
    GuildStore.erase(guildId);
}

void GuildMgr::SaveGuilds()
{
    for (GuildContainer::iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
        itr->second->SaveToDB();
}

uint32 GuildMgr::GenerateGuildId()
{
    if (NextGuildId >= 0xFFFFFFFE)
    {
        LOG_ERROR("guild", "Guild ids overflow!! Can't continue, shutting down server. ");
        World::StopNow(ERROR_EXIT_CODE);
    }
    return NextGuildId++;
}

// Guild collection
Guild* GuildMgr::GetGuildById(ObjectGuid::LowType guildId) const
{
    GuildContainer::const_iterator itr = GuildStore.find(guildId);
    if (itr != GuildStore.end())
        return itr->second;

    return nullptr;
}

Guild* GuildMgr::GetGuildByGuid(ObjectGuid guid) const
{
    // Full guids are only used when receiving/sending data to client
    // everywhere else guild id is used
    if (guid.IsGuild())
        if (uint32 guildId = guid.GetCounter())
            return GetGuildById(guildId);

    return nullptr;
}

Guild* GuildMgr::GetGuildByName(const std::string& guildName) const
{
    std::string search = guildName;
    std::transform(search.begin(), search.end(), search.begin(), ::toupper);
    for (GuildContainer::const_iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
    {
        std::string gname = itr->second->GetName();
        std::transform(gname.begin(), gname.end(), gname.begin(), ::toupper);
        if (search == gname)
            return itr->second;
    }
    return nullptr;
}

std::string GuildMgr::GetGuildNameById(ObjectGuid::LowType guildId) const
{
    if (Guild* guild = GetGuildById(guildId))
        return guild->GetName();

    return "";
}

GuildMgr* GuildMgr::instance()
{
    static GuildMgr instance;
    return &instance;
}

Guild* GuildMgr::GetGuildByLeader(ObjectGuid guid) const
{
    for (GuildContainer::const_iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
        if (itr->second->GetLeaderGUID() == guid)
            return itr->second;

    return nullptr;
}

uint32 GuildMgr::GetXPForGuildLevel(uint8 level) const
{
    if (level < GuildXPperLevel.size())
        return GuildXPperLevel[level];
    return 0;
}

void GuildMgr::LoadGuilds()
{
    // 1. Load all guilds
    LOG_INFO("server.loading", "Loading guilds definitions...");
    {
        uint32 oldMSTime = getMSTime();

                                                     //          0          1       2             3              4              5              6
        QueryResult result = CharacterDatabase.Query("SELECT g.guildid, g.name, g.leaderguid, g.EmblemStyle, g.EmblemColor, g.BorderStyle, g.BorderColor, "
                                                     //   7                  8       9       10            11          12        13                14                 15
                                                     "g.BackgroundColor, g.info, g.motd, g.createdate, g.BankMoney, g.level, g.experience, g.todayExperience, COUNT(gbt.guildid), "
                                                     //           16                           17                           18                                 19
                                                     "g.completedDungeonChallenges, g.completedRaidChallenges, g.completedRatedBattlegroundChallenges,  g.WeeklyBonusMoney "
                                                     "FROM guild g LEFT JOIN guild_bank_tab gbt ON g.guildid = gbt.guildid GROUP BY g.guildid ORDER BY g.guildid ASC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild definitions. DB table `guild` is empty.");
            return;
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                Guild* guild = new Guild();

                if (!guild->LoadFromDB(fields))
                {
                    delete guild;
                    continue;
                }

                AddGuild(guild);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 2. Load all guild ranks
    LOG_INFO("server.loading", "Loading guild ranks...");
    {
        uint32 oldMSTime = getMSTime();

        // Delete orphaned guild rank entries before loading the valid ones
        CharacterDatabase.DirectExecute("DELETE gr FROM guild_rank gr LEFT JOIN guild g ON gr.guildId = g.guildId WHERE g.guildId IS NULL");

        //                                                         0    1      2       3                4
        QueryResult result = CharacterDatabase.Query("SELECT guildid, rid, rname, rights, BankMoneyPerDay FROM guild_rank ORDER BY guildid ASC, rid ASC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild ranks. DB table `guild_rank` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadRankFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild ranks in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 3. Load all guild members
    LOG_INFO("server.loading", "Loading guild members...");
    {
        uint32 oldMSTime = getMSTime();

        // Delete orphaned guild member entries before loading the valid ones
        CharacterDatabase.DirectExecute("DELETE gm FROM guild_member gm LEFT JOIN guild g ON gm.guildId = g.guildId WHERE g.guildId IS NULL");
        CharacterDatabase.DirectExecute("DELETE gm FROM guild_member_withdraw gm LEFT JOIN guild_member g ON gm.guid = g.guid WHERE g.guid IS NULL");

                                                //           0           1         2      3      4        5       6       7       8       9       10
        QueryResult result = CharacterDatabase.Query("SELECT gm.guildid, gm.guid, `rank`, pnote, offnote, w.tab0, w.tab1, w.tab2, w.tab3, w.tab4, w.tab5, "
                                                //    11      12      13       14      15       16       17      18         19             20
                                                     "w.tab6, w.tab7, w.money, c.name, c.level, c.class, c.zone, c.account, c.logout_time, gm.activity, "
                                                //    21               22                   23          24
                                                     "gm.weekActivity, c.achievementPoints, r.standing, gm.weekReputation "
                                                     "FROM guild_member gm "
                                                     "LEFT JOIN guild_member_withdraw w ON gm.guid = w.guid "
                                                     "LEFT JOIN character_reputation r ON gm.guid = r.guid AND r.faction = 1168 "
                                                     "LEFT JOIN characters c ON c.guid = gm.guid ORDER BY gm.guildid ASC");

        if (!result)
            LOG_INFO("server.loading", ">> Loaded 0 guild members. DB table `guild_member` is empty.");
        else
        {
            uint32 count = 0;

            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadMemberFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild members in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 4. Load all guild bank tab rights
    LOG_INFO("server.loading", "Loading bank tab rights...");
    {
        uint32 oldMSTime = getMSTime();

        // Delete orphaned guild bank right entries before loading the valid ones
        CharacterDatabase.DirectExecute("DELETE gbr FROM guild_bank_right gbr LEFT JOIN guild g ON gbr.guildId = g.guildId WHERE g.guildId IS NULL");

                                                     //      0        1      2    3        4
        QueryResult result = CharacterDatabase.Query("SELECT guildid, TabId, rid, gbright, SlotPerDay FROM guild_bank_right ORDER BY guildid ASC, TabId ASC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild bank tab rights. DB table `guild_bank_right` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadBankRightFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u bank tab rights in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 5. Load all event logs
    LOG_INFO("server.loading", "Loading guild event logs...");
    {
        uint32 oldMSTime = getMSTime();

        CharacterDatabase.DirectPExecute("DELETE FROM guild_eventlog WHERE LogGuid > %u", sWorld->getIntConfig(CONFIG_GUILD_EVENT_LOG_COUNT));

                                                     //          0        1        2          3            4            5        6
        QueryResult result = CharacterDatabase.Query("SELECT guildid, LogGuid, EventType, PlayerGuid1, PlayerGuid2, NewRank, TimeStamp FROM guild_eventlog ORDER BY TimeStamp DESC, LogGuid DESC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild event logs. DB table `guild_eventlog` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadEventLogFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild event logs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 6. Load all bank event logs
    LOG_INFO("server.loading", "Loading guild bank event logs...");
    {
        uint32 oldMSTime = getMSTime();

        // Remove log entries that exceed the number of allowed entries per guild
        CharacterDatabase.DirectPExecute("DELETE FROM guild_bank_eventlog WHERE LogGuid > %u", sWorld->getIntConfig(CONFIG_GUILD_BANK_EVENT_LOG_COUNT));

                                                     //          0        1      2        3          4           5            6               7          8
        QueryResult result = CharacterDatabase.Query("SELECT guildid, TabId, LogGuid, EventType, PlayerGuid, ItemOrMoney, ItemStackCount, DestTabId, TimeStamp FROM guild_bank_eventlog ORDER BY TimeStamp DESC, LogGuid DESC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild bank event logs. DB table `guild_bank_eventlog` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadBankEventLogFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild bank event logs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 7. Load all news event logs
    LOG_INFO("server.loading", "Loading Guild News...");
    {
        uint32 oldMSTime = getMSTime();

        CharacterDatabase.DirectPExecute("DELETE FROM guild_newslog WHERE LogGuid > %u", sWorld->getIntConfig(CONFIG_GUILD_NEWS_LOG_COUNT));

                                                     //      0        1        2          3           4      5      6
        QueryResult result = CharacterDatabase.Query("SELECT guildid, LogGuid, EventType, PlayerGuid, Flags, Value, Timestamp FROM guild_newslog ORDER BY TimeStamp DESC, LogGuid DESC");

        if (!result)
            LOG_INFO("server.loading", ">> Loaded 0 guild event logs. DB table `guild_newslog` is empty.");
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadGuildNewsLogFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild new logs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }


    // 8. Load all guild bank tabs
    LOG_INFO("server.loading", "Loading guild bank tabs...");
    {
        uint32 oldMSTime = getMSTime();

        // Delete orphaned guild bank tab entries before loading the valid ones
        CharacterDatabase.DirectExecute("DELETE gbt FROM guild_bank_tab gbt LEFT JOIN guild g ON gbt.guildId = g.guildId WHERE g.guildId IS NULL");

                                                     //         0        1      2        3        4
        QueryResult result = CharacterDatabase.Query("SELECT guildid, TabId, TabName, TabIcon, TabText FROM guild_bank_tab ORDER BY guildid ASC, TabId ASC");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild bank tabs. DB table `guild_bank_tab` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[0].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadBankTabFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild bank tabs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 9. Fill all guild bank tabs
    LOG_INFO("guild", "Filling bank tabs with items...");
    {
        uint32 oldMSTime = getMSTime();

        // Delete orphan guild bank items
        CharacterDatabase.DirectExecute("DELETE gbi FROM guild_bank_item gbi LEFT JOIN guild g ON gbi.guildId = g.guildId WHERE g.guildId IS NULL");

                                                     //      0            1                2      3         4        5      6             7                   8                 9           10            11
        QueryResult result = CharacterDatabase.Query("SELECT creatorGuid, giftCreatorGuid, count, duration, charges, flags, enchantments, randomPropertyType, randomPropertyId, durability, creationTime, text, "
                                                     //   12   13     14      15         16
                                                     "guildid, TabId, SlotId, item_guid, itemEntry FROM guild_bank_item gbi INNER JOIN item_instance ii ON gbi.item_guid = ii.guid");

        if (!result)
        {
            LOG_INFO("server.loading", ">> Loaded 0 guild bank tab items. DB table `guild_bank_item` or `item_instance` is empty.");
        }
        else
        {
            uint32 count = 0;
            do
            {
                Field* fields = result->Fetch();
                uint32 guildId = fields[12].GetUInt32();

                if (Guild* guild = GetGuildById(guildId))
                    guild->LoadBankItemFromDB(fields);

                ++count;
            }
            while (result->NextRow());

            LOG_INFO("server.loading", ">> Loaded %u guild bank tab items in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
        }
    }

    // 10. Load guild achievements
    {
        PreparedQueryResult achievementResult;
        PreparedQueryResult criteriaResult;
        for (GuildContainer::const_iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
        {
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GUILD_ACHIEVEMENT);
            stmt->setUInt32(0, itr->first);
            achievementResult = CharacterDatabase.Query(stmt);
            stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_GUILD_ACHIEVEMENT_CRITERIA);
            stmt->setUInt32(0, itr->first);
            criteriaResult = CharacterDatabase.Query(stmt);

            itr->second->GetAchievementMgr().LoadFromDB(achievementResult, criteriaResult);
        }
    }

    // 11. Validate loaded guild data
    LOG_INFO("misc", "Validating data of loaded guilds...");
    {
        uint32 oldMSTime = getMSTime();

        for (GuildContainer::iterator itr = GuildStore.begin(); itr != GuildStore.end();)
        {
            Guild* guild = itr->second;
            ++itr;
            if (guild && !guild->Validate())
                delete guild;
        }

        LOG_INFO("server.loading", ">> Validated data of loaded guilds in %u ms", GetMSTimeDiffToNow(oldMSTime));
    }
}

void GuildMgr::LoadGuildXpForLevel()
{
    uint32 oldMSTime = getMSTime();

    GuildXPperLevel.resize(sWorld->getIntConfig(CONFIG_GUILD_MAX_LEVEL));
    for (uint8 level = 0; level < sWorld->getIntConfig(CONFIG_GUILD_MAX_LEVEL); ++level)
        GuildXPperLevel[level] = 0;

    //                                                 0         1
    QueryResult result  = WorldDatabase.Query("SELECT lvl, xp_for_next_level FROM guild_xp_for_level");

    if (!result)
    {
        LOG_ERROR("server.loading", ">> Loaded 0 xp for guild level definitions. DB table `guild_xp_for_level` is empty.");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();

        uint32 level        = fields[0].GetUInt8();
        uint32 requiredXP   = fields[1].GetUInt32();

        if (level >= sWorld->getIntConfig(CONFIG_GUILD_MAX_LEVEL))
        {
            LOG_INFO("misc", "Unused (> Guild.MaxLevel in worldserver.conf) level %u in `guild_xp_for_level` table, ignoring.", uint32(level));
            continue;
        }

        GuildXPperLevel[level] = requiredXP;
        ++count;

    } while (result->NextRow());

    // fill level gaps
    for (uint8 level = 1; level < sWorld->getIntConfig(CONFIG_GUILD_MAX_LEVEL); ++level)
    {
        if (!GuildXPperLevel[level])
        {
            LOG_ERROR("sql.sql", "Level %i does not have XP for guild level data. Using data of level [%i] + 1660000.", level+1, level);
            GuildXPperLevel[level] = GuildXPperLevel[level - 1] + 1660000;
        }
    }

    LOG_INFO("server.loading", ">> Loaded %u xp for guild level definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void GuildMgr::LoadGuildRewards()
{
    uint32 oldMSTime = getMSTime();

    //                                                 0     1         2         3      4
    QueryResult result  = WorldDatabase.Query("SELECT entry, standing, racemask, price, achievement FROM guild_rewards");

    if (!result)
    {
        LOG_ERROR("server.loading", ">> Loaded 0 guild reward definitions. DB table `guild_rewards` is empty.");
        return;
    }

    uint32 count = 0;

    do
    {
        GuildReward reward;
        Field* fields = result->Fetch();
        reward.Entry         = fields[0].GetUInt32();
        reward.Standing      = fields[1].GetUInt8();
        reward.Racemask      = fields[2].GetInt32();
        reward.Price         = fields[3].GetUInt64();
        reward.AchievementId = fields[4].GetUInt32();

        if (!sObjectMgr->GetItemTemplate(reward.Entry))
        {
            LOG_ERROR("server.loading", "Guild rewards constains not existing item entry %u", reward.Entry);
            continue;
        }

        if (reward.AchievementId != 0 && (!sAchievementMgr->GetAchievement(reward.AchievementId)))
        {
            LOG_ERROR("server.loading", "Guild rewards constains not existing achievement entry %u", reward.AchievementId);
            continue;
        }

        if (reward.Standing >= MAX_REPUTATION_RANK)
        {
            LOG_ERROR("server.loading", "Guild rewards contains wrong reputation standing %u, max is %u", uint32(reward.Standing), MAX_REPUTATION_RANK - 1);
            continue;
        }

        GuildRewards.push_back(reward);
        ++count;
    } while (result->NextRow());

    LOG_INFO("server.loading", ">> Loaded %u guild reward definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void GuildMgr::LoadGuildProfessionData()
{
    for (SkillLineAbilityEntry const* entry : sSkillLineAbilityStore)
    {
        SkillLineEntry const* skill = sSkillLineStore.LookupEntry(entry->SkillLine);
        if (!skill || skill->CategoryID != SKILL_CATEGORY_PROFESSION)
            continue;

        GuildProfession prof;
        prof.SpellId = entry->Spell;
        prof.UniqueBits = entry->UniqueBit;
        prof.AutoLearn = entry->AcquireMethod == SKILL_LINE_ABILITY_LEARNED_ON_SKILL_VALUE;
        GuildProfessionStore[skill->ID].push_back(prof);
    }
}

void GuildMgr::LoadGuildChallenges()
{
    uint32 oldMSTime = getMSTime();

    //                                               0              1               2           3     4
    QueryResult result = WorldDatabase.Query("SELECT ChallengeType, ChallengeCount, Experience, Gold, GoldMaxLevel FROM guild_challenges");

    if (!result)
    {
        LOG_ERROR("server.loading", ">> Loaded 0 guild challenge definitions. DB table `guild_challenges` is empty.");
        return;
    }

    uint32 count = 0;

    do
    {
        GuildChallenge challenge;
        Field* fields = result->Fetch();
        challenge.ChallengeType = fields[0].GetInt32();
        challenge.ChallengeCount = fields[1].GetInt32();
        challenge.Experience = fields[2].GetInt32();
        challenge.Gold = fields[3].GetInt32();
        challenge.GoldMaxLevel = fields[4].GetInt32();

        if (challenge.ChallengeType >= MAX_GUILD_CHALLENGE_TYPES)
        {
            LOG_ERROR("server.loading", "Guild challenge type %u is invalid. Skipped.", challenge.ChallengeType);
            continue;
        }

        GuildChallenges.push_back(challenge);
        ++count;
    } while (result->NextRow());

    LOG_INFO("server.loading", ">> Loaded %u guild challenge definitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void GuildMgr::ResetTimes(bool week)
{
    CharacterDatabase.Execute(CharacterDatabase.GetPreparedStatement(CHAR_UPD_GUILD_RESET_TODAY_EXPERIENCE));
    CharacterDatabase.Execute(CharacterDatabase.GetPreparedStatement(CHAR_DEL_GUILD_MEMBER_WITHDRAW));

    // Delete too old old guild member
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_OLD_OLD_GUILD_MEMBER);
    stmt->setUInt32(0, uint32(GameTime::GetGameTime() - time_t(30 * DAY)));
    CharacterDatabase.Execute(stmt);

    // Reset week reputation for old guild member and reset weekly bonus money from cash flow contributions
    if (week)
    {
        CharacterDatabase.Execute(CharacterDatabase.GetPreparedStatement(CHAR_RESET_OLD_GUILD_WEEK_REPUTATION));
        CharacterDatabase.Execute(CharacterDatabase.GetPreparedStatement(CHAR_UPD_GUILD_WEEKLY_BONUS_MONEY));
    }

    for (GuildContainer::const_iterator itr = GuildStore.begin(); itr != GuildStore.end(); ++itr)
        if (Guild* guild = itr->second)
            guild->ResetTimes(week);
}

void GuildMgr::ClearExpiredGuildNews()
{
    // Clean guild news that are older than a week
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GUILD_NEWS);
    stmt->setUInt64(0, uint64(GameTime::GetGameTime() - time_t(7 * DAY)));
    CharacterDatabase.Execute(stmt);

    for (std::pair<ObjectGuid::LowType, Guild*> guildPair : GuildStore)
        if (Guild* guild = guildPair.second)
            guild->ClearExpiredNews();
}
