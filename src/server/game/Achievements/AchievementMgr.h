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

#ifndef __FIRELANDS_ACHIEVEMENTMGR_H
#define __FIRELANDS_ACHIEVEMENTMGR_H

#include "DatabaseEnvFwd.h"
#include "DBCEnums.h"
#include "DBCStores.h"
#include "ObjectGuid.h"
#include <string>
#include <unordered_map>
#include <vector>

class Unit;
class Player;
class GameObject;
class WorldPacket;

typedef std::vector<AchievementCriteriaEntry const*> AchievementCriteriaEntryList;
typedef std::vector<AchievementEntry const*>         AchievementEntryList;

typedef std::unordered_map<uint32, AchievementCriteriaEntryList> AchievementCriteriaListByAchievement;
typedef std::unordered_map<uint32, AchievementCriteriaEntryList> AchievementCriteriaListByMiscValue;
typedef std::unordered_map<uint32, AchievementCriteriaEntryList> AchievementCriteriaListByCondition;
typedef std::unordered_map<uint32, AchievementEntryList>         AchievementListByReferencedId;

struct CriteriaProgress
{
    uint64 counter;
    time_t date;                                            // latest update time.
    ObjectGuid CompletedGUID;                               // GUID of the player that completed this criteria (guild achievements)
    bool changed;
};

enum AchievementCriteriaDataType
{                                                            // value1         value2        comment
    ACHIEVEMENT_CRITERIA_DATA_TYPE_NONE                = 0,  // 0              0
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_CREATURE          = 1,  // creature_id    0
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_CLASS_RACE = 2,  // class_id       race_id
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_LESS_HEALTH= 3,  // health_percent 0
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_AURA              = 5,  // spell_id       effect_idx
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_AURA              = 7,  // spell_id       effect_idx
    ACHIEVEMENT_CRITERIA_DATA_TYPE_VALUE               = 8,  // minvalue                     value provided with achievement update must be not less that limit
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_LEVEL             = 9,  // minlevel                     minlevel of target
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_GENDER            = 10, // gender                       0=male; 1=female
    ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT              = 11, // scripted requirement
    ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_DIFFICULTY      = 12, // used on 3.3.5a branch
    ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_PLAYER_COUNT    = 13, // count                        "with less than %u people in the zone"
    ACHIEVEMENT_CRITERIA_DATA_TYPE_T_TEAM              = 14, // team                         HORDE(67), ALLIANCE(469)
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_DRUNK             = 15, // drunken_state  0             (enum DrunkenState) of player
    ACHIEVEMENT_CRITERIA_DATA_TYPE_HOLIDAY             = 16, // holiday_id     0             event in holiday time
    ACHIEVEMENT_CRITERIA_DATA_TYPE_BG_LOSS_TEAM_SCORE  = 17, // min_score      max_score     player's team win bg and opposition team have team score in range
    ACHIEVEMENT_CRITERIA_DATA_TYPE_INSTANCE_SCRIPT     = 18, // 0              0             maker instance script call for check current criteria requirements fit
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_EQUIPPED_ITEM     = 19, // item_level     item_quality  for equipped item in slot to check item level and quality
    ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_ID              = 20, // map_id         0             player must be on map with id in map_id
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_PLAYER_CLASS_RACE = 21, // class_id       race_id
    ACHIEVEMENT_CRITERIA_DATA_TYPE_NTH_BIRTHDAY        = 22, // used on 3.3.5a branch
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_KNOWN_TITLE       = 23, // title_id                     known (pvp) title, values from dbc
    ACHIEVEMENT_CRITERIA_DATA_TYPE_GAME_EVENT          = 24, // game_event_id  0
    ACHIEVEMENT_CRITERIA_DATA_TYPE_S_ITEM_QUALITY      = 25, // item_quality

    MAX_ACHIEVEMENT_CRITERIA_DATA_TYPE
};

struct AchievementCriteriaData
{
    AchievementCriteriaDataType dataType;
    union
    {
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_NONE              = 0 (no data)
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_CREATURE        = 1
        struct
        {
            uint32 id;
        } creature;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_CLASS_RACE = 2
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_S_PLAYER_CLASS_RACE = 21
        struct
        {
            uint32 class_id;
            uint32 race_id;
        } classRace;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_PLAYER_LESS_HEALTH = 3
        struct
        {
            uint32 percent;
        } health;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_S_AURA            = 5
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_AURA            = 7
        struct
        {
            uint32 spell_id;
            uint32 effect_idx;
        } aura;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_VALUE             = 8
        struct
        {
            uint32 value;
            uint32 compType;
        } value;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_LEVEL           = 9
        struct
        {
            uint32 minlevel;
        } level;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_GENDER          = 10
        struct
        {
            uint32 gender;
        } gender;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_SCRIPT            = 11 (no data)
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_PLAYER_COUNT  = 13
        struct
        {
            uint32 maxcount;
        } map_players;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_T_TEAM            = 14
        struct
        {
            uint32 team;
        } team;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_S_DRUNK           = 15
        struct
        {
            uint32 state;
        } drunk;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_HOLIDAY           = 16
        struct
        {
            uint32 id;
        } holiday;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_BG_LOSS_TEAM_SCORE= 17
        struct
        {
            uint32 min_score;
            uint32 max_score;
        } bg_loss_team_score;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_INSTANCE_SCRIPT   = 18 (no data)
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_S_EQUIPPED_ITEM   = 19
        struct
        {
            uint32 item_level;
            uint32 item_quality;
        } equipped_item;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_MAP_ID            = 20
        struct
        {
            uint32 mapId;
        } map_id;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_KNOWN_TITLE       = 22
        struct
        {
            uint32 title_id;
        } known_title;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_GAME_EVENT        = 24
        struct
        {
            uint32 id;
        } game_event;
        // ACHIEVEMENT_CRITERIA_DATA_TYPE_S_ITEM_QUALITY    = 25
        struct
        {
            uint32 item_quality;
        } item;
        // raw
        struct
        {
            uint32 value1;
            uint32 value2;
        } raw;
    };
    uint32 ScriptId;

    AchievementCriteriaData() : dataType(ACHIEVEMENT_CRITERIA_DATA_TYPE_NONE)
    {
        raw.value1 = 0;
        raw.value2 = 0;
        ScriptId = 0;
    }

    AchievementCriteriaData(uint32 _dataType, uint32 _value1, uint32 _value2, uint32 _scriptId) : dataType(AchievementCriteriaDataType(_dataType))
    {
        raw.value1 = _value1;
        raw.value2 = _value2;
        ScriptId = _scriptId;
    }

    bool IsValid(AchievementCriteriaEntry const* criteria);
    bool Meets(uint32 criteria_id, Player const* source, Unit const* target, uint32 miscValue1 = 0, uint32 miscValue2 = 0) const;
};

struct FC_GAME_API AchievementCriteriaDataSet
{
        AchievementCriteriaDataSet() : criteria_id(0) { }
        typedef std::vector<AchievementCriteriaData> Storage;
        void Add(AchievementCriteriaData const& data) { storage.push_back(data); }
        bool Meets(Player const* source, Unit const* target, uint32 miscValue1 = 0, uint32 miscValue2 = 0) const;
        void SetCriteriaId(uint32 id) {criteria_id = id;}
    private:
        uint32 criteria_id;
        Storage storage;
};

typedef std::unordered_map<uint32, AchievementCriteriaDataSet> AchievementCriteriaDataMap;

struct AchievementReward
{
    uint32 TitleID[2];
    uint32 ItemID;
    uint32 Sender;
    std::string Subject;
    std::string Text;
    uint32 MailTemplateID;
};

typedef std::unordered_map<uint32, AchievementReward> AchievementRewards;

struct AchievementRewardLocale
{
    std::vector<std::string> Subject;
    std::vector<std::string> Text;
};

typedef std::unordered_map<uint32, AchievementRewardLocale> AchievementRewardLocales;

struct CompletedAchievementData
{
    time_t date;
    GuidSet guids;
    bool changed;
};

typedef std::unordered_map<uint32, CriteriaProgress> CriteriaProgressMap;
typedef std::unordered_map<uint32, CompletedAchievementData> CompletedAchievementMap;

enum ProgressType
{
    PROGRESS_SET,
    PROGRESS_ACCUMULATE,
    PROGRESS_HIGHEST
};

template<class T>
class FC_GAME_API AchievementMgr
{
    public:
        AchievementMgr(T* owner);
        ~AchievementMgr();

        void Reset();
        static void DeleteFromDB(ObjectGuid lowguid);
        void LoadFromDB(PreparedQueryResult achievementResult, PreparedQueryResult criteriaResult);
        void SaveToDB(CharacterDatabaseTransaction& trans);
        void ResetAchievementCriteria(AchievementCriteriaCondition condition, uint64 value, bool evenIfCriteriaComplete);
        void UpdateAchievementCriteria(AchievementCriteriaTypes type, uint64 miscValue1 = 0, uint64 miscValue2 = 0, uint64 miscValue3 = 0, Unit const* unit = nullptr, Player* referencePlayer = nullptr, GameObject* go = nullptr);
        void CompletedAchievement(AchievementEntry const* entry, Player* referencePlayer);
        void CheckAllAchievementCriteria(Player* referencePlayer);
        void SendAllAchievementData(Player* receiver) const;
        void SendAllTrackedCriterias(Player* receiver, std::set<uint32> const& trackedCriterias) const;
        void SendAchievementInfo(Player* receiver, uint32 achievementId = 0) const;
        bool HasAchieved(uint32 achievementId) const;
        CompletedAchievementData* GetCompletedDataForAchievement(uint32 achievementId);
        T* GetOwner() const { return _owner; }

        void UpdateTimedAchievements(uint32 timeDiff);
        void StartTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry, uint32 timeLost = 0);
        void RemoveTimedAchievement(AchievementCriteriaTimedTypes type, uint32 entry);   // used for quest and scripted timed achievements

        uint32 GetAchievementPoints() const { return _achievementPoints; }
    private:
        void SendAchievementEarned(AchievementEntry const* achievement) const;
        void SendCriteriaUpdate(AchievementCriteriaEntry const* entry, CriteriaProgress const* progress, uint32 timeElapsed, bool timedCompleted) const;
        CriteriaProgress* GetCriteriaProgress(AchievementCriteriaEntry const* entry);
        void SetCriteriaProgress(AchievementCriteriaEntry const* entry, uint64 changeValue, Player* referencePlayer, ProgressType ptype = PROGRESS_SET);
        void RemoveCriteriaProgress(AchievementCriteriaEntry const* entry);
        void CompletedCriteriaFor(AchievementEntry const* achievement, Player* referencePlayer);
        bool IsCompletedCriteria(AchievementCriteriaEntry const* achievementCriteria, AchievementEntry const* achievement);
        bool IsCompletedAchievement(AchievementEntry const* entry);
        bool CanUpdateCriteria(AchievementCriteriaEntry const* criteria, AchievementEntry const* achievement, uint64 miscValue1, uint64 miscValue2, uint64 miscValue3, Unit const* unit, Player* referencePlayer, GameObject* go = nullptr);
        void SendPacket(WorldPacket const* data) const;

        bool ConditionsSatisfied(AchievementCriteriaEntry const* criteria, Player* referencePlayer) const;
        bool RequirementsSatisfied(AchievementCriteriaEntry const* criteria, uint64 miscValue1, uint64 miscValue2, uint64 miscValue3, Unit const* unit, Player* referencePlayer, GameObject* go = nullptr) const;
        bool AdditionalRequirementsSatisfied(AchievementCriteriaEntry const* criteria, uint64 miscValue1, uint64 miscValue2, Unit const* unit, Player* referencePlayer) const;

        T* _owner;
        CriteriaProgressMap m_criteriaProgress;
        CompletedAchievementMap m_completedAchievements;
        typedef std::map<uint32, uint32> TimedAchievementMap;
        TimedAchievementMap m_timedAchievements;      // Criteria id/time left in MS
        uint32 _achievementPoints;
};

class FC_GAME_API AchievementGlobalMgr
{
        AchievementGlobalMgr() { }
        ~AchievementGlobalMgr() { }

    public:
        static char const* GetCriteriaTypeString(AchievementCriteriaTypes type);
        static char const* GetCriteriaTypeString(uint32 type);

        static AchievementGlobalMgr* instance();

        AchievementCriteriaEntryList const& GetAchievementCriteriaByType(AchievementCriteriaTypes type, uint32 miscValue, bool guild = false) const;

        AchievementCriteriaEntryList const& GetTimedAchievementCriteriaByType(AchievementCriteriaTimedTypes type) const
        {
            return m_AchievementCriteriasByTimedType[type];
        }

        AchievementCriteriaEntryList const* GetAchievementCriteriaByCondition(AchievementCriteriaCondition condition, uint32 val)
        {
            AchievementCriteriaListByCondition::const_iterator itr = m_AchievementCriteriasByCondition[condition].find(val);
            return itr != m_AchievementCriteriasByCondition[condition].end() ? &itr->second : nullptr;
        }

        AchievementCriteriaEntryList const* GetAchievementCriteriaByAchievement(uint32 id) const
        {
            AchievementCriteriaListByAchievement::const_iterator itr = m_AchievementCriteriaListByAchievement.find(id);
            return itr != m_AchievementCriteriaListByAchievement.end() ? &itr->second : nullptr;
        }

        AchievementEntryList const* GetAchievementByReferencedId(uint32 id) const
        {
            AchievementListByReferencedId::const_iterator itr = m_AchievementListByReferencedId.find(id);
            return itr != m_AchievementListByReferencedId.end() ? &itr->second : nullptr;
        }

        AchievementReward const* GetAchievementReward(AchievementEntry const* achievement) const
        {
            AchievementRewards::const_iterator iter = m_achievementRewards.find(achievement->ID);
            return iter != m_achievementRewards.end() ? &iter->second : nullptr;
        }

        AchievementRewardLocale const* GetAchievementRewardLocale(AchievementEntry const* achievement) const
        {
            AchievementRewardLocales::const_iterator iter = m_achievementRewardLocales.find(achievement->ID);
            return iter != m_achievementRewardLocales.end() ? &iter->second : nullptr;
        }

        AchievementCriteriaDataSet const* GetCriteriaDataSet(AchievementCriteriaEntry const* achievementCriteria) const
        {
            AchievementCriteriaDataMap::const_iterator iter = m_criteriaDataMap.find(achievementCriteria->ID);
            return iter != m_criteriaDataMap.end() ? &iter->second : nullptr;
        }

        bool IsGroupCriteriaType(AchievementCriteriaTypes type) const
        {
            switch (type)
            {
                case ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE:
                case ACHIEVEMENT_CRITERIA_TYPE_WIN_BG:
                case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET:         // NYI
                case ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA:
                case ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2:        // NYI
                case ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_BATTLEGROUND:  // NYI
                    return true;
                default:
                    break;
            }

            return false;
        }
        bool IsRealmCompleted(AchievementEntry const* achievement) const;
        void SetRealmCompleted(AchievementEntry const* achievement);

        void LoadAchievementCriteriaList();
        void LoadAchievementCriteriaData();
        void LoadAchievementReferenceList();
        void LoadCompletedAchievements();
        void LoadRewards();
        void LoadRewardLocales();
        AchievementEntry const* GetAchievement(uint32 achievementId) const;
        AchievementCriteriaEntry const* GetAchievementCriteria(uint32 achievementId) const;
    private:
        AchievementCriteriaDataMap m_criteriaDataMap;

        // store achievement criterias by type to speed up lookup
        AchievementCriteriaEntryList m_AchievementCriteriasByType[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];
        AchievementCriteriaEntryList m_GuildAchievementCriteriasByType[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];

        // store achievement criterias split by misc values
        AchievementCriteriaListByMiscValue m_AchievementCriteriasByMiscValue[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];
        AchievementCriteriaListByMiscValue m_GuildAchievementCriteriasByMiscValue[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];

        AchievementCriteriaEntryList m_AchievementCriteriasByTimedType[ACHIEVEMENT_TIMED_TYPE_MAX];

        AchievementCriteriaListByCondition m_AchievementCriteriasByCondition[ACHIEVEMENT_CRITERIA_CONDITION_MAX];

        // store achievement criterias by achievement to speed up lookup
        AchievementCriteriaListByAchievement m_AchievementCriteriaListByAchievement;

        // store achievements by referenced achievement id to speed up lookup
        AchievementListByReferencedId m_AchievementListByReferencedId;

        // store realm first achievements
        // std::chrono::system_clock::time_point::min() is a placeholder value for realm firsts not yet completed
        // std::chrono::system_clock::time_point::max() is a value assigned to realm firsts complete before worldserver started
        std::unordered_map<uint32 /*achievementId*/, std::chrono::system_clock::time_point /*completionTime*/> _allCompletedAchievements;

        AchievementRewards m_achievementRewards;
        AchievementRewardLocales m_achievementRewardLocales;
};

#define sAchievementMgr AchievementGlobalMgr::instance()

#endif
