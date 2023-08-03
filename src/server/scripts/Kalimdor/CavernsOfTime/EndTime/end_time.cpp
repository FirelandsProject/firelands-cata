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

#include "end_time.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "PassiveAI.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"

enum Events
{
    // Nozdormu
    EVENT_TALK_ENCOUNTER_INTRO = 1,
    EVENT_TALK_ENCOUNTER_OUTRO_1,
    EVENT_TALK_ENCOUNTER_OUTRO_2,
    EVENT_TALK_ENCOUNTER_OUTRO_3,
    EVENT_TALK_ENCOUNTER_OUTRO_4
};

enum Actions
{
    // Nozdormu
    ACTION_ENCOUNTER_INTRO = 1,
    ACTION_ENCOUNTER_OUTRO = 2
};

enum Texts
{
    // Nozdormu
    SAY_ENCOUNTER_INTRO     = 0,
    SAY_ENCOUNTER_OUTRO_1   = 1,
    SAY_ENCOUNTER_OUTRO_2   = 2,
    SAY_ENCOUNTER_OUTRO_3   = 3,
    SAY_ENCOUNTER_OUTRO_4   = 4
};

enum GossipMenuIds
{
    GOSSIP_MENU_ID_NOZDORMU                 = 13360,
    GOSSIP_MENU_OPTION_ID_WELL_OF_ETERNITY  = 0
};

Position const NozdormuEncounterTeleportPosition    = { 4033.37f, -294.457f, 181.613f, 5.8119464f };
Position const NozdormuDefeatTeleportPosition       = { 4138.48f, -429.436f, 122.259f, 5.8119464f };

struct npc_end_time_nozdormu : public NullCreatureAI
{
    npc_end_time_nozdormu(Creature* creature) : NullCreatureAI(creature),  _instance(nullptr), _introDone(false) { }

    void InitializeAI() override
    {
        _instance = me->GetInstanceScript();
    }

    bool GossipHello(Player* player) override
    {
        if (!_instance)
            return true;

        if (_instance->GetBossState(DATA_MUROZOND) == DONE)
            AddGossipItemFor(player, GOSSIP_MENU_ID_NOZDORMU, GOSSIP_MENU_OPTION_ID_WELL_OF_ETERNITY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, player->GetGossipTextId(GOSSIP_MENU_ID_NOZDORMU, me), me->GetGUID());

        return true;
    }

    bool GossipSelect(Player* /*player*/, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        // Todo: Well of Eternity teleport

        return true;
    }

    void DoAction(int32 action) override
    {
        switch (action)
        {
            case ACTION_ENCOUNTER_INTRO:
                if (!_introDone)
                {
                    _events.ScheduleEvent(EVENT_TALK_ENCOUNTER_INTRO, 8s + 400ms);
                    _introDone = true;
                }
                break;
            case ACTION_ENCOUNTER_OUTRO:
                me->setActive(true);
                me->NearTeleportTo(NozdormuDefeatTeleportPosition);
                _events.ScheduleEvent(EVENT_TALK_ENCOUNTER_OUTRO_1, 8s + 700ms);
                me->setActive(false);
                break;
            default:
                break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_TALK_ENCOUNTER_INTRO:
                    Talk(SAY_ENCOUNTER_INTRO);
                    me->setActive(true);
                    me->NearTeleportTo(NozdormuEncounterTeleportPosition);
                    me->setActive(false);
                    break;
                case EVENT_TALK_ENCOUNTER_OUTRO_1:
                    Talk(SAY_ENCOUNTER_OUTRO_1);
                    _events.ScheduleEvent(EVENT_TALK_ENCOUNTER_OUTRO_2, 17s);
                    break;
                case EVENT_TALK_ENCOUNTER_OUTRO_2:
                    Talk(SAY_ENCOUNTER_OUTRO_2);
                    _events.ScheduleEvent(EVENT_TALK_ENCOUNTER_OUTRO_3, 17s);
                    break;
                case EVENT_TALK_ENCOUNTER_OUTRO_3:
                    Talk(SAY_ENCOUNTER_OUTRO_3);
                    _events.ScheduleEvent(EVENT_TALK_ENCOUNTER_OUTRO_4, 14s);
                    break;
                case EVENT_TALK_ENCOUNTER_OUTRO_4:
                    Talk(SAY_ENCOUNTER_OUTRO_4);
                    me->SetFacingTo(3.1765f);
                    break;
                default:
                    break;
            }
        }
    }

private:
    EventMap _events;
    InstanceScript* _instance;
    bool _introDone;
};

enum TimeTransitDeviceAreaIds
{
    AREA_ID_ENTRYWAY_OF_TIME = 5796
};

enum TimeTransitDeviceSpells
{
    SPELL_TELEPORT_TO_ENTRANCE          = 102564,
    SPELL_TELEPORT_TO_BLUE_DRAGONSHRINE = 102126
};

enum TimeTransitGossipMenuIds
{
    GOSSIP_MENU_ID_SELECT_YOUR_DESTINATION = 13321
};

enum TimeTransitGossipIndexes
{
    GOSSIP_INDEX_TELEPORT_TO_ENTRYWAY_OF_TIME               = 0,
    GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_FIRST_ECHO   = 3,
    GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_SECOND_ECHO  = 7
};

static std::unordered_map<uint32 /*gossipMenuId*/, uint32 /*teleportSpellId*/> TransitDeviceTeleportSpells =
{
    { GOSSIP_INDEX_TELEPORT_TO_ENTRYWAY_OF_TIME,                SPELL_TELEPORT_TO_ENTRANCE          },
    { GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_FIRST_ECHO,    SPELL_TELEPORT_TO_BLUE_DRAGONSHRINE },
    { GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_SECOND_ECHO,   SPELL_TELEPORT_TO_BLUE_DRAGONSHRINE }
};

struct go_end_time_time_transit_device : public GameObjectAI
{
    go_end_time_time_transit_device(GameObject* gameObject) : GameObjectAI(gameObject), _instance(nullptr) { }

    void InitializeAI() override
    {
        _instance = me->GetInstanceScript();
    }

    bool GossipHello(Player* player) override
    {
        if (!_instance)
            return false;

        if (player->GetAreaId() != AREA_ID_ENTRYWAY_OF_TIME)
            AddGossipItemFor(player, GOSSIP_MENU_ID_SELECT_YOUR_DESTINATION, GOSSIP_INDEX_TELEPORT_TO_ENTRYWAY_OF_TIME, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + GOSSIP_INDEX_TELEPORT_TO_ENTRYWAY_OF_TIME);

        // @todo: world state based menu generation
        AddGossipItemFor(player, GOSSIP_MENU_ID_SELECT_YOUR_DESTINATION, GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_FIRST_ECHO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + GOSSIP_INDEX_TELEPORT_TO_BLUE_DRAGONSHRINE_FIRST_ECHO);

        SendGossipMenuFor(player, player->GetGossipTextId(GOSSIP_MENU_ID_SELECT_YOUR_DESTINATION, me), me->GetGUID());

        return true;
    }

    bool GossipSelect(Player* player, uint32 /*gossipMenuId*/, uint32 action) override
    {
        uint32 index = player->PlayerTalkClass->GetGossipOptionAction(action) - GOSSIP_ACTION_INFO_DEF;
        player->CastSpell(player, TransitDeviceTeleportSpells[index]);
        ClearGossipMenuFor(player);

        return true;
    }

private:
    InstanceScript* _instance;
};

struct go_end_time_fragment_of_jainas_staff : public GameObjectAI
{
    go_end_time_fragment_of_jainas_staff(GameObject* gameObject) : GameObjectAI(gameObject), _instance(nullptr) { }

    void InitializeAI() override
    {
        _instance = me->GetInstanceScript();
    }

    bool GossipHello(Player* /*player*/) override
    {
        if (!_instance)
            return false;

        _instance->SetData(DATA_COLLECTED_FRAGMENT_OF_JAINAS_STAFF, 0);
        me->DespawnOrUnsummon();

        return true;
    }

private:
    InstanceScript* _instance;
};

void AddSC_end_time()
{
    RegisterEndTimeCreatureAI(npc_end_time_nozdormu);
    RegisterGameObjectAI(go_end_time_time_transit_device);
    RegisterGameObjectAI(go_end_time_fragment_of_jainas_staff);
}
