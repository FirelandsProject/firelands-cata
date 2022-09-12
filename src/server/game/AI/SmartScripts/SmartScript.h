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

#ifndef FIRELANDS_SMARTSCRIPT_H
#define FIRELANDS_SMARTSCRIPT_H

#include "Define.h"
#include "SmartScriptMgr.h"

class Creature;
class GameObject;
class Player;
class Quest;
class SpellInfo;
class Unit;
class WorldObject;
struct AreaTriggerEntry;

class FC_GAME_API SmartScript
{
    public:
        SmartScript();
        ~SmartScript();

        void OnInitialize(WorldObject* obj, AreaTriggerEntry const* at = nullptr, Quest const* qst = nullptr);
        void GetScript();
        void FillScript(SmartAIEventList e, WorldObject* obj, AreaTriggerEntry const* at, Quest const* qst = nullptr);

        void ProcessEventsFor(SMART_EVENT e, Unit* unit = nullptr, uint32 var0 = 0, uint32 var1 = 0, bool bvar = false, SpellInfo const* spell = nullptr, GameObject* gob = nullptr);
        void ProcessEvent(SmartScriptHolder& e, Unit* unit = nullptr, uint32 var0 = 0, uint32 var1 = 0, bool bvar = false, SpellInfo const* spell = nullptr, GameObject* gob = nullptr);
        bool CheckTimer(SmartScriptHolder const& e) const;
        void RecalcTimer(SmartScriptHolder& e, uint32 min, uint32 max);
        void UpdateTimer(SmartScriptHolder& e, uint32 const diff);
        void InitTimer(SmartScriptHolder& e);
        void ProcessAction(SmartScriptHolder& e, Unit* unit = nullptr, uint32 var0 = 0, uint32 var1 = 0, bool bvar = false, SpellInfo const* spell = nullptr, GameObject* gob = nullptr);
        void ProcessTimedAction(SmartScriptHolder& e, uint32 const& min, uint32 const& max, Unit* unit = nullptr, uint32 var0 = 0, uint32 var1 = 0, bool bvar = false, SpellInfo const* spell = nullptr, GameObject* gob = nullptr);
        void GetTargets(ObjectVector& targets, SmartScriptHolder const& e, Unit* invoker = nullptr);
        void GetWorldObjectsInDist(ObjectVector& targets, float dist);
        void InstallTemplate(SmartScriptHolder const& e);
        SmartScriptHolder CreateSmartEvent(SMART_EVENT e, uint32 event_flags, uint32 event_param1, uint32 event_param2, uint32 event_param3, uint32 event_param4, uint32 event_param5, SMART_ACTION action, uint32 action_param1, uint32 action_param2, uint32 action_param3, uint32 action_param4, uint32 action_param5, uint32 action_param6, SMARTAI_TARGETS t, uint32 target_param1, uint32 target_param2, uint32 target_param3, uint32 phaseMask = 0);
        void AddEvent(SMART_EVENT e, uint32 event_flags, uint32 event_param1, uint32 event_param2, uint32 event_param3, uint32 event_param4, uint32 event_param5, SMART_ACTION action, uint32 action_param1, uint32 action_param2, uint32 action_param3, uint32 action_param4, uint32 action_param5, uint32 action_param6, SMARTAI_TARGETS t, uint32 target_param1, uint32 target_param2, uint32 target_param3, uint32 phaseMask = 0);
        void SetPathId(uint32 id) { mPathId = id; }
        uint32 GetPathId() const { return mPathId; }
        WorldObject* GetBaseObject() const;
        static bool IsUnit(WorldObject* obj);
        static bool IsPlayer(WorldObject* obj);
        static bool IsCreature(WorldObject* obj);
        static bool IsCharmedCreature(WorldObject* obj);
        static bool IsGameObject(WorldObject* obj);

        void OnUpdate(const uint32 diff);
        void OnMoveInLineOfSight(Unit* who);

        Unit* DoSelectLowestHpFriendly(float range, uint32 MinHPDiff);
        Unit* DoSelectLowestHpPctFriendly(float range, uint8 hpPctMin, uint8 hpPctMax);
        void DoFindFriendlyCC(std::list<Creature*>& _list, float range);
        void DoFindFriendlyMissingBuff(std::list<Creature*>& list, float range, uint32 spellid);
        Unit* DoFindClosestFriendlyInRange(float range, bool playerOnly);


        bool IsSmart(Creature* c, bool silent = false);
        bool IsSmart(GameObject* g, bool silent = false);
        bool IsSmart(bool silent = false);

        void StoreTargetList(ObjectVector const& targets, uint32 id);
        ObjectVector const* GetStoredTargetVector(uint32 id, WorldObject const& ref) const;

        void StoreCounter(uint32 id, uint32 value, uint32 reset);
        uint32 GetCounterValue(uint32 id) const;

        GameObject* FindGameObjectNear(WorldObject* searchObject, ObjectGuid::LowType guid) const;
        Creature* FindCreatureNear(WorldObject* searchObject, ObjectGuid::LowType guid) const;

        void OnReset();
        void ResetBaseObject();

        uint32 GetPhase() { return mEventPhase; }

        //TIMED_ACTIONLIST (script type 9 aka script9)
        void SetScript9(SmartScriptHolder& e, uint32 entry);
        Unit* GetLastInvoker(Unit* invoker = nullptr);
        ObjectGuid mLastInvoker;
        typedef std::unordered_map<uint32, uint32> CounterMap;
        CounterMap mCounterList;

        uint32 GetEventPhaseMask() { return mEventPhase; }

    private:
        void IncPhase(uint32 p);
        void DecPhase(uint32 p);

        void SetPhase(uint32 p);
        bool IsInPhase(uint32 p) const;

        SmartAIEventList mEvents;
        SmartAIEventList mInstallEvents;
        SmartAIEventList mTimedActionList;
        bool isProcessingTimedActionList;
        Creature* me;
        ObjectGuid meOrigGUID;
        GameObject* go;
        ObjectGuid goOrigGUID;
        AreaTriggerEntry const* trigger;
        Quest const* quest;
        SmartScriptType mScriptType;
        uint32 mEventPhase;

        uint32 mPathId;
        SmartAIEventStoredList mStoredEvents;
        std::vector<uint32> mRemIDs;

        uint32 mTextTimer;
        uint32 mLastTextID;
        uint32 mTalkerEntry;
        bool mUseTextTimer;

        ObjectVectorMap _storedTargets;

        SMARTAI_TEMPLATE mTemplate;
        void InstallEvents();

        void RemoveStoredEvent(uint32 id);
};

#endif
