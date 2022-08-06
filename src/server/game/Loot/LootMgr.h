/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FIRELANDS_LOOTMGR_H
#define FIRELANDS_LOOTMGR_H

#include "Define.h"
#include "ConditionMgr.h"
#include "ObjectGuid.h"
#include "SharedDefines.h"
#include <list>
#include <vector>

class LootStore;
class LootTemplate;
class Player;
struct Loot;
struct LootItem;

struct FC_GAME_API LootStoreItem
{
    uint32  itemid;                                         // id of the item
    uint32  reference;                                      // referenced TemplateleId
    float   chance;                                         // chance to drop for both quest and non-quest items, chance to be used for refs
    uint16  lootmode;
    bool    needs_quest : 1;                                // quest drop (quest is required for item to drop)
    bool    is_currency : 1;                                // currency loot (entry is currency instead of an item)
    uint8   groupid     : 7;
    uint8   mincount;                                       // mincount for drop items
    uint8   maxcount;                                       // max drop count for the item mincount or Ref multiplicator
    ConditionContainer conditions;                          // additional loot condition

    // Constructor
    // displayid is filled in IsValid() which must be called after
    LootStoreItem(uint32 _itemid, uint32 _reference, float _chance, bool _needs_quest, bool _is_currency, uint16 _lootmode, uint8 _groupid, int32 _mincount, uint8 _maxcount)
        : itemid(_itemid), reference(_reference), chance(_chance), lootmode(_lootmode), needs_quest(_needs_quest),
        is_currency(_is_currency), groupid(_groupid), mincount(_mincount), maxcount(_maxcount)
    { }

    bool Roll(bool rate) const;                                 // Checks if the entry takes it's chance (at loot generation)
    bool IsValid(LootStore const& store, uint32 entry) const;   // Checks correctness of values
};

typedef std::list<LootStoreItem*> LootStoreItemList;
typedef std::unordered_map<uint32, LootTemplate*> LootTemplateMap;

typedef std::set<uint32> LootIdSet;

class FC_GAME_API LootStore
{
    public:
        explicit LootStore(char const* name, char const* entryName, bool ratesAllowed)
            : m_name(name), m_entryName(entryName), m_ratesAllowed(ratesAllowed) { }

        virtual ~LootStore() { Clear(); }

        void Verify(LootTypeId lootTypeId) const;

        uint32 LoadAndCollectLootIds(LootIdSet& ids_set, LootTypeId lootTypeId);
        void CheckLootRefs(LootTypeId lootTypeId, LootIdSet* ref_set = nullptr) const; // check existence reference and remove it from ref_set
        void ReportUnusedIds(LootIdSet const& ids_set, LootTypeId lootTypeId) const;
        void ReportNonExistingId(uint32 lootId, LootTypeId lootTypeId) const;
        void ReportNonExistingId(uint32 lootId, char const* ownerType, uint32 ownerId, LootTypeId lootTypeId) const;

        bool HaveLootFor(uint32 loot_id) const { return m_LootTemplates.find(loot_id) != m_LootTemplates.end(); }
        bool HaveQuestLootFor(uint32 loot_id) const;
        bool HaveQuestLootForPlayer(uint32 loot_id, Player* player) const;

        LootTemplate const* GetLootFor(uint32 loot_id) const;
        void ResetConditions();
        LootTemplate* GetLootForConditionFill(uint32 loot_id);

        char const* GetName() const { return m_name; }
        char const* GetEntryName() const { return m_entryName; }
        bool IsRatesAllowed() const { return m_ratesAllowed; }
    protected:
        uint32 LoadLootTable(LootTypeId);
        void Clear();
    private:
        LootTemplateMap m_LootTemplates;
        char const* m_name;
        char const* m_entryName;
        bool m_ratesAllowed;
};

class FC_GAME_API LootTemplate
{
    class LootGroup;                                       // A set of loot definitions for items (refs are not allowed inside)
    typedef std::vector<LootGroup*> LootGroups;

    public:
        LootTemplate() { }
        ~LootTemplate();

        // Adds an entry to the group (at loading stage)
        void AddEntry(LootStoreItem* item);
        // Rolls for every item in the template and adds the rolled items the the loot
        void Process(Loot& loot, bool rate, uint16 lootMode, uint8 groupId = 0) const;
        void CopyConditions(const ConditionContainer& conditions);
        void CopyConditions(LootItem* li) const;

        // True if template includes at least 1 quest drop entry
        bool HasQuestDrop(LootTemplateMap const& store, uint8 groupId = 0) const;
        // True if template includes at least 1 quest drop for an active quest of the player
        bool HasQuestDropForPlayer(LootTemplateMap const& store, Player const* player, uint8 groupId = 0) const;

        // Checks integrity of the template
        void Verify(LootStore const& store, uint32 Id, LootTypeId lootTypeId) const;
        void CheckLootRefs(LootTemplateMap const& store, LootTypeId, LootIdSet* ref_set) const;
        bool addConditionItem(Condition* cond);
        bool isReference(uint32 id);

    private:
        LootStoreItemList Entries;                          // not grouped only
        LootGroups        Groups;                           // groups have own (optimised) processing, grouped entries go there

        // Objects of this class must never be copied, we are storing pointers in container
        LootTemplate(LootTemplate const&) = delete;
        LootTemplate& operator=(LootTemplate const&) = delete;
};

FC_GAME_API extern LootStore LootTemplates_Creature;
FC_GAME_API extern LootStore LootTemplates_Fishing;
FC_GAME_API extern LootStore LootTemplates_Gameobject;
FC_GAME_API extern LootStore LootTemplates_Item;
FC_GAME_API extern LootStore LootTemplates_Mail;
FC_GAME_API extern LootStore LootTemplates_Milling;
FC_GAME_API extern LootStore LootTemplates_Pickpocketing;
FC_GAME_API extern LootStore LootTemplates_Reference;
FC_GAME_API extern LootStore LootTemplates_Skinning;
FC_GAME_API extern LootStore LootTemplates_Disenchant;
FC_GAME_API extern LootStore LootTemplates_Prospecting;
FC_GAME_API extern LootStore LootTemplates_Spell;

FC_GAME_API void LoadLootTemplates_Creature();
FC_GAME_API void LoadLootTemplates_Fishing();
FC_GAME_API void LoadLootTemplates_Gameobject();
FC_GAME_API void LoadLootTemplates_Item();
FC_GAME_API void LoadLootTemplates_Mail();
FC_GAME_API void LoadLootTemplates_Milling();
FC_GAME_API void LoadLootTemplates_Pickpocketing();
FC_GAME_API void LoadLootTemplates_Skinning();
FC_GAME_API void LoadLootTemplates_Disenchant();
FC_GAME_API void LoadLootTemplates_Prospecting();

FC_GAME_API void LoadLootTemplates_Spell();
FC_GAME_API void LoadLootTemplates_Reference();

FC_GAME_API void LoadLootTables();

#endif
