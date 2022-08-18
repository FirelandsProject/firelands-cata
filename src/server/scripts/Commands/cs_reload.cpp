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

/* ScriptData
Name: reload_commandscript
%Complete: 100
Comment: All reload related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "AchievementMgr.h"
#include "AuctionHouseMgr.h"
#include "BattlegroundMgr.h"
#include "Chat.h"
#include "CreatureTextMgr.h"
#include "DatabaseEnv.h"
#include "DisableMgr.h"
#include "ItemEnchantmentMgr.h"
#include "Language.h"
#include "LFGMgr.h"
#include "Log.h"
#include "LootMgr.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "SkillDiscovery.h"
#include "SkillExtraItems.h"
#include "SmartAI.h"
#include "SpellMgr.h"
#include "TicketMgr.h"
#include "WardenCheckMgr.h"
#include "WaypointManager.h"
#include "World.h"

class reload_commandscript : public CommandScript
{
public:
    reload_commandscript() : CommandScript("reload_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> reloadAllCommandTable =
        {
            { "achievement",                   SEC_ADMINISTRATOR,      true,  &HandleReloadAllAchievementCommand,              "" },
            { "area",                          SEC_ADMINISTRATOR,      true,  &HandleReloadAllAreaCommand,                     "" },
            { "gossips",                       SEC_ADMINISTRATOR,      true,  &HandleReloadAllGossipsCommand,                  "" },
            { "item",                          SEC_ADMINISTRATOR,      true,  &HandleReloadAllItemCommand,                     "" },
            { "locales",                       SEC_ADMINISTRATOR,      true,  &HandleReloadAllLocalesCommand,                  "" },
            { "loot",                          SEC_ADMINISTRATOR,      true,  &HandleReloadAllLootCommand,                     "" },
            { "npc",                           SEC_ADMINISTRATOR,      true,  &HandleReloadAllNpcCommand,                      "" },
            { "quest",                         SEC_ADMINISTRATOR,      true,  &HandleReloadAllQuestCommand,                    "" },
            { "scripts",                       SEC_ADMINISTRATOR,      true,  &HandleReloadAllScriptsCommand,                  "" },
            { "spell",                         SEC_ADMINISTRATOR,      true,  &HandleReloadAllSpellCommand,                    "" },
            { "",                              SEC_ADMINISTRATOR,      true,  &HandleReloadAllCommand,                         "" },
        };
        static std::vector<ChatCommand> reloadCommandTable =
        {
            { "auctions",                      SEC_ADMINISTRATOR,      true,  &HandleReloadAuctionsCommand,                   "" },
            { "access_requirement",            SEC_ADMINISTRATOR,      true,  &HandleReloadAccessRequirementCommand,          "" },
            { "achievement_criteria_data",     SEC_ADMINISTRATOR,      true,  &HandleReloadAchievementCriteriaDataCommand,    "" },
            { "achievement_reward",            SEC_ADMINISTRATOR,      true,  &HandleReloadAchievementRewardCommand,          "" },
            { "all",                           SEC_ADMINISTRATOR,      true,  nullptr,                                        "", reloadAllCommandTable },
            { "areatrigger_involvedrelation",  SEC_ADMINISTRATOR,      true,  &HandleReloadQuestAreaTriggersCommand,          "" },
            { "areatrigger_tavern",            SEC_ADMINISTRATOR,      true,  &HandleReloadAreaTriggerTavernCommand,          "" },
            { "areatrigger_teleport",          SEC_ADMINISTRATOR,      true,  &HandleReloadAreaTriggerTeleportCommand,        "" },
            { "autobroadcast",                 SEC_ADMINISTRATOR,      true,  &HandleReloadAutobroadcastCommand,              "" },
            { "battleground_template",         SEC_ADMINISTRATOR,      true,  &HandleReloadBattlegroundTemplate,              "" },
            { "broadcast_text",                SEC_ADMINISTRATOR,      true,  &HandleReloadBroadcastTextCommand,              "" },
            { "command",                       SEC_ADMINISTRATOR,      true,  &HandleReloadCommandCommand,                    "" },
            { "conditions",                    SEC_ADMINISTRATOR,      true,  &HandleReloadConditions,                        "" },
            { "config",                         SEC_ADMINISTRATOR,      true,  &HandleReloadConfigCommand,                      "" },
            { "creature_text",                 SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureText,                      "" },
            { "creature_questender",           SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureQuestEnderCommand,         "" },
            { "creature_linked_respawn",       SEC_ADMINISTRATOR,      true,  &HandleReloadLinkedRespawnCommand,              "" },
            { "creature_loot_template",        SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesCreatureCommand,      "" },
            { "creature_movement_override",    SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureMovementOverrideCommand,   "" },
            { "creature_onkill_reward",        SEC_ADMINISTRATOR,      true,  &HandleReloadOnKillRewardCommand,               "" },
            { "creature_queststarter",         SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureQuestStarterCommand,       "" },
            { "creature_summon_groups",        SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureSummonGroupsCommand,       "" },
            { "creature_template",             SEC_ADMINISTRATOR,      true,  &HandleReloadCreatureTemplateCommand,           "" },
            { "disables",                      SEC_ADMINISTRATOR,      true,  &HandleReloadDisablesCommand,                   "" },
            { "disenchant_loot_template",      SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesDisenchantCommand,    "" },
            { "event_scripts",                 SEC_ADMINISTRATOR,      true,  &HandleReloadEventScriptsCommand,               "" },
            { "fishing_loot_template",          SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesFishingCommand,       "" },
            { "graveyard_zone",                SEC_ADMINISTRATOR,      true,  &HandleReloadGameGraveyardZoneCommand,          "" },
            { "game_tele",                     SEC_ADMINISTRATOR,      true,  &HandleReloadGameTeleCommand,                   "" },
            { "gameobject_questender",         SEC_ADMINISTRATOR,      true,  &HandleReloadGOQuestEnderCommand,               "" },
            { "gameobject_loot_template",      SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesGameobjectCommand,    "" },
            { "gameobject_queststarter",       SEC_ADMINISTRATOR,      true,  &HandleReloadGOQuestStarterCommand,             "" },
            { "gm_tickets",                    SEC_ADMINISTRATOR,      true,  &HandleReloadGMTicketsCommand,                  "" },
            { "gossip_menu",                   SEC_ADMINISTRATOR,      true,  &HandleReloadGossipMenuCommand,                 "" },
            { "gossip_menu_option",            SEC_ADMINISTRATOR,      true,  &HandleReloadGossipMenuOptionCommand,           "" },
            { "item_enchantment_template",     SEC_ADMINISTRATOR,      true,  &HandleReloadItemEnchantementsCommand,          "" },
            { "item_loot_template",            SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesItemCommand,          "" },
            { "lfg_dungeon_rewards",           SEC_ADMINISTRATOR,      true,  &HandleReloadLfgRewardsCommand,                 "" },
            { "achievement_reward_locale",     SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesAchievementRewardCommand,   "" },
            { "creature_template_locale",      SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesCreatureCommand,            "" },
            { "creature_text_locale",          SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesCreatureTextCommand,        "" },
            { "gameobject_template_locale",    SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesGameobjectCommand,          "" },
            { "gossip_menu_option_locale",     SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesGossipMenuOptionCommand,    "" },
            { "npc_text_locale",               SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesNpcTextCommand,             "" },
            { "page_text_locale",              SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesPageTextCommand,            "" },
            { "points_of_interest_locale",     SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesPointsOfInterestCommand,    "" },
            { "quest_template_locale",         SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesQuestCommand,               "" },
            { "mail_level_reward",             SEC_ADMINISTRATOR,      true,  &HandleReloadMailLevelRewardCommand,            "" },
            { "mail_loot_template",            SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesMailCommand,          "" },
            { "milling_loot_template",         SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesMillingCommand,       "" },
            { "npc_spellclick_spells",         SEC_ADMINISTRATOR,      true,  &HandleReloadSpellClickSpellsCommand,           "" },
            { "npc_vendor",                    SEC_ADMINISTRATOR,      true,  &HandleReloadNpcVendorCommand,                  "" },
            { "page_text",                     SEC_ADMINISTRATOR,      true,  &HandleReloadPageTextsCommand,                  "" },
            { "pickpocketing_loot_template",   SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesPickpocketingCommand, "" },
            { "points_of_interest",            SEC_ADMINISTRATOR,      true,  &HandleReloadPointsOfInterestCommand,           "" },
            { "prospecting_loot_template",     SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesProspectingCommand,   "" },
            { "quest_greeting",                SEC_ADMINISTRATOR,      true,  &HandleReloadQuestGreetingCommand,              "" },
            { "quest_greeting_locale",         SEC_ADMINISTRATOR,      true,  &HandleReloadLocalesQuestGreetingCommand,       "" },
            { "quest_poi",                     SEC_ADMINISTRATOR,      true,  &HandleReloadQuestPOICommand,                   "" },
            { "quest_template",                SEC_ADMINISTRATOR,      true,  &HandleReloadQuestTemplateCommand,              "" },
            { "reference_loot_template",       SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesReferenceCommand,     "" },
            { "reserved_name",                 SEC_ADMINISTRATOR,      true,  &HandleReloadReservedNameCommand,               "" },
            { "reputation_reward_rate",        SEC_ADMINISTRATOR,      true,  &HandleReloadReputationRewardRateCommand,       "" },
            { "reputation_spillover_template", SEC_ADMINISTRATOR,      true,  &HandleReloadReputationRewardRateCommand,       "" },
            { "skill_discovery_template",      SEC_ADMINISTRATOR,      true,  &HandleReloadSkillDiscoveryTemplateCommand,     "" },
            { "skill_extra_item_template",     SEC_ADMINISTRATOR,      true,  &HandleReloadSkillExtraItemTemplateCommand,     "" },
            { "skill_fishing_base_level",       SEC_ADMINISTRATOR,      true,  &HandleReloadSkillFishingBaseLevelCommand,      "" },
            { "skinning_loot_template",        SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesSkinningCommand,      "" },
            { "smart_scripts",                 SEC_ADMINISTRATOR,      true,  &HandleReloadSmartScripts,                      "" },
            { "spell_required",                SEC_ADMINISTRATOR,      true,  &HandleReloadSpellRequiredCommand,              "" },
            { "spell_area",                    SEC_ADMINISTRATOR,      true,  &HandleReloadSpellAreaCommand,                  "" },
            { "spell_bonus_data",              SEC_ADMINISTRATOR,      true,  &HandleReloadSpellBonusesCommand,               "" },
            { "spell_group",                   SEC_ADMINISTRATOR,      true,  &HandleReloadSpellGroupsCommand,                "" },
            { "spell_learn_spell",             SEC_ADMINISTRATOR,      true,  &HandleReloadSpellLearnSpellCommand,            "" },
            { "spell_loot_template",           SEC_ADMINISTRATOR,      true,  &HandleReloadLootTemplatesSpellCommand,         "" },
            { "spell_linked_spell",            SEC_ADMINISTRATOR,      true,  &HandleReloadSpellLinkedSpellCommand,           "" },
            { "spell_pet_auras",               SEC_ADMINISTRATOR,      true,  &HandleReloadSpellPetAurasCommand,              "" },
            { "spell_proc",                    SEC_ADMINISTRATOR,      true,  &HandleReloadSpellProcsCommand,                 "" },
            { "spell_scripts",                 SEC_ADMINISTRATOR,      true,  &HandleReloadSpellScriptsCommand,               "" },
            { "spell_target_position",         SEC_ADMINISTRATOR,      true,  &HandleReloadSpellTargetPositionCommand,        "" },
            { "spell_threats",                 SEC_ADMINISTRATOR,      true,  &HandleReloadSpellThreatsCommand,               "" },
            { "spell_group_stack_rules",       SEC_ADMINISTRATOR,      true,  &HandleReloadSpellGroupStackRulesCommand,       "" },
            { "firelands_string",               SEC_ADMINISTRATOR,      true,  &HandleReloadFirelandsStringCommand,            "" },
            { "trainer",                       SEC_ADMINISTRATOR,      true,  &HandleReloadTrainerCommand,                    "" },
            { "warden_action",                 SEC_ADMINISTRATOR,      true,  &HandleReloadWardenactionCommand,               "" },
            { "waypoint_scripts",              SEC_ADMINISTRATOR,      true,  &HandleReloadWpScriptsCommand,                  "" },
            { "waypoint_data",                 SEC_ADMINISTRATOR,      true,  &HandleReloadWpCommand,                         "" },
            { "vehicle_accessory",             SEC_ADMINISTRATOR,      true,  &HandleReloadVehicleAccessoryCommand,           "" },
            { "vehicle_template_accessory",    SEC_ADMINISTRATOR,      true,  &HandleReloadVehicleTemplateAccessoryCommand,   "" },
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "reload",                        SEC_ADMINISTRATOR,      true,  nullptr,                                        "", reloadCommandTable },
        };
        return commandTable;
    }

    //reload commands
    static bool HandleReloadGMTicketsCommand(ChatHandler* /*handler*/, char const* /*args*/)
    {
        sTicketMgr->LoadTickets();
        return true;
    }

    static bool HandleReloadAllCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadSkillFishingBaseLevelCommand(handler, "");

        HandleReloadAllAchievementCommand(handler, "");
        HandleReloadAllAreaCommand(handler, "");
        HandleReloadAllLootCommand(handler, "");
        HandleReloadAllNpcCommand(handler, "");
        HandleReloadAllQuestCommand(handler, "");
        HandleReloadAllSpellCommand(handler, "");
        HandleReloadAllItemCommand(handler, "");
        HandleReloadAllGossipsCommand(handler, "");
        HandleReloadAllLocalesCommand(handler, "");

        HandleReloadAccessRequirementCommand(handler, "");
        HandleReloadMailLevelRewardCommand(handler, "");
        HandleReloadCommandCommand(handler, "");
        HandleReloadReservedNameCommand(handler, "");
        HandleReloadFirelandsStringCommand(handler, "");
        HandleReloadGameTeleCommand(handler, "");

        HandleReloadCreatureMovementOverrideCommand(handler, "");
        HandleReloadCreatureSummonGroupsCommand(handler, "");

        HandleReloadVehicleAccessoryCommand(handler, "");
        HandleReloadVehicleTemplateAccessoryCommand(handler, "");

        HandleReloadAutobroadcastCommand(handler, "");
        HandleReloadBattlegroundTemplate(handler, "");
        return true;
    }

    static bool HandleReloadAllAchievementCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadAchievementCriteriaDataCommand(handler, "");
        HandleReloadAchievementRewardCommand(handler, "");
        return true;
    }

    static bool HandleReloadAllAreaCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadQuestGreetingCommand(handler, "");
        //HandleReloadQuestAreaTriggersCommand(handler, ""); -- reloaded in HandleReloadAllQuestCommand
        HandleReloadAreaTriggerTeleportCommand(handler, "");
        HandleReloadAreaTriggerTavernCommand(handler, "");
        HandleReloadGameGraveyardZoneCommand(handler, "");
        return true;
    }

    static bool HandleReloadAllLootCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables...");
        LoadLootTables();
        handler->SendGlobalGMSysMessage("DB tables `*_loot_template` reloaded.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadAllNpcCommand(ChatHandler* handler, char const* args)
    {
        if (*args != 'a')                                          // will be reloaded from all_gossips
        HandleReloadTrainerCommand(handler, "a");
        HandleReloadNpcVendorCommand(handler, "a");
        HandleReloadPointsOfInterestCommand(handler, "a");
        HandleReloadSpellClickSpellsCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllQuestCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadQuestAreaTriggersCommand(handler, "a");
        HandleReloadQuestPOICommand(handler, "a");
        HandleReloadQuestTemplateCommand(handler, "a");

        LOG_INFO("misc", "Re-Loading Quests Relations...");
        sObjectMgr->LoadQuestStartersAndEnders();
        handler->SendGlobalGMSysMessage("DB tables `*_queststarter` and `*_questender` reloaded.");
        return true;
    }

    static bool HandleReloadAllScriptsCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (sMapMgr->IsScriptScheduled())
        {
            handler->PSendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        LOG_INFO("misc", "Re-Loading Scripts...");
        HandleReloadEventScriptsCommand(handler, "a");
        HandleReloadSpellScriptsCommand(handler, "a");
        handler->SendGlobalGMSysMessage("DB tables `*_scripts` reloaded.");
        HandleReloadWpScriptsCommand(handler, "a");
        HandleReloadWpCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllSpellCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadSkillDiscoveryTemplateCommand(handler, "a");
        HandleReloadSkillExtraItemTemplateCommand(handler, "a");
        HandleReloadSpellRequiredCommand(handler, "a");
        HandleReloadSpellAreaCommand(handler, "a");
        HandleReloadSpellGroupsCommand(handler, "a");
        HandleReloadSpellLearnSpellCommand(handler, "a");
        HandleReloadSpellLinkedSpellCommand(handler, "a");
        HandleReloadSpellProcsCommand(handler, "a");
        HandleReloadSpellBonusesCommand(handler, "a");
        HandleReloadSpellTargetPositionCommand(handler, "a");
        HandleReloadSpellThreatsCommand(handler, "a");
        HandleReloadSpellGroupStackRulesCommand(handler, "a");
        HandleReloadSpellPetAurasCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllGossipsCommand(ChatHandler* handler, char const* args)
    {
        HandleReloadGossipMenuCommand(handler, "a");
        HandleReloadGossipMenuOptionCommand(handler, "a");
        if (*args != 'a')                                          // already reload from all_scripts
        HandleReloadPointsOfInterestCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllItemCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadPageTextsCommand(handler, "a");
        HandleReloadItemEnchantementsCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllLocalesCommand(ChatHandler* handler, char const* /*args*/)
    {
        HandleReloadLocalesAchievementRewardCommand(handler, "a");
        HandleReloadLocalesCreatureCommand(handler, "a");
        HandleReloadLocalesCreatureTextCommand(handler, "a");
        HandleReloadLocalesGameobjectCommand(handler, "a");
        HandleReloadLocalesGossipMenuOptionCommand(handler, "a");
        HandleReloadLocalesNpcTextCommand(handler, "a");
        HandleReloadLocalesPageTextCommand(handler, "a");
        HandleReloadLocalesPointsOfInterestCommand(handler, "a");
        HandleReloadLocalesQuestCommand(handler, "a");
        HandleReloadLocalesQuestGreetingCommand(handler, "");
        return true;
    }

    static bool HandleReloadConfigCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading config settings...");
        sWorld->LoadConfigSettings(true);
        sMapMgr->InitializeVisibilityDistanceInfo();
        handler->SendGlobalGMSysMessage("World config settings reloaded.");
        return true;
    }

    static bool HandleReloadAccessRequirementCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Access Requirement definitions...");
        sObjectMgr->LoadAccessRequirements();
        handler->SendGlobalGMSysMessage("DB table `access_requirement` reloaded.");
        return true;
    }

    static bool HandleReloadAchievementCriteriaDataCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Additional Achievement Criteria Data...");
        sAchievementMgr->LoadAchievementCriteriaData();
        handler->SendGlobalGMSysMessage("DB table `achievement_criteria_data` reloaded.");
        return true;
    }

    static bool HandleReloadAchievementRewardCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Achievement Reward Data...");
        sAchievementMgr->LoadRewards();
        handler->SendGlobalGMSysMessage("DB table `achievement_reward` reloaded.");
        return true;
    }

    static bool HandleReloadAreaTriggerTavernCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Tavern Area Triggers...");
        sObjectMgr->LoadTavernAreaTriggers();
        handler->SendGlobalGMSysMessage("DB table `areatrigger_tavern` reloaded.");
        return true;
    }

    static bool HandleReloadAreaTriggerTeleportCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading AreaTrigger teleport definitions...");
        sObjectMgr->LoadAreaTriggerTeleports();
        handler->SendGlobalGMSysMessage("DB table `areatrigger_teleport` reloaded.");
        return true;
    }

    static bool HandleReloadAutobroadcastCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Autobroadcasts...");
        sWorld->LoadAutobroadcasts();
        handler->SendGlobalGMSysMessage("DB table `autobroadcast` reloaded.");
        return true;
    }

    static bool HandleReloadBattlegroundTemplate(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Battleground Templates...");
        sBattlegroundMgr->LoadBattlegroundTemplates();
        handler->SendGlobalGMSysMessage("DB table `battleground_template` reloaded.");
        return true;
    }

    static bool HandleReloadBroadcastTextCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Broadcast texts...");
        sObjectMgr->LoadBroadcastTexts();
        sObjectMgr->LoadBroadcastTextLocales();
        handler->SendGlobalGMSysMessage("DB table `broadcast_text` reloaded.");
        return true;
    }

    static bool HandleReloadCommandCommand(ChatHandler* handler, char const* /*args*/)
    {
        ChatHandler::invalidateCommandTable();
        handler->SendGlobalGMSysMessage("DB table `command` will be reloaded at next chat command use.");
        return true;
    }

    static bool HandleReloadOnKillRewardCommand(ChatHandler* handler, const char* /*args*/)    {
        LOG_INFO("misc", "Re-Loading creature reward definitions...");
        sObjectMgr->LoadRewardOnKill();
        handler->SendGlobalGMSysMessage("DB table `creature_onkill_reward` reloaded.");
        return true;
    }

    static bool HandleReloadCreatureSummonGroupsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Reloading creature summon groups...");
        sObjectMgr->LoadTempSummons();
        handler->SendGlobalGMSysMessage("DB table `creature_summon_groups` reloaded.");
        return true;
    }

    static bool HandleReloadCreatureTemplateCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Tokenizer entries(std::string(args), ' ');

        for (Tokenizer::const_iterator itr = entries.begin(); itr != entries.end(); ++itr)
        {
            uint32 entry = uint32(atoi(*itr));

            WorldDatabasePreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
            stmt->setUInt32(0, entry);
            PreparedQueryResult result = WorldDatabase.Query(stmt);

            if (!result)
            {
                handler->PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, entry);
                continue;
            }

            CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(entry);
            if (!cInfo)
            {
                handler->PSendSysMessage(LANG_COMMAND_CREATURESTORAGE_NOTFOUND, entry);
                continue;
            }

            LOG_INFO("misc", "Reloading creature template entry %u", entry);

            Field* fields = result->Fetch();
            sObjectMgr->LoadCreatureTemplate(fields);
            sObjectMgr->CheckCreatureTemplate(cInfo);
        }

        sObjectMgr->InitializeQueriesData(QUERY_DATA_CREATURES);
        handler->SendGlobalGMSysMessage("Creature template reloaded.");
        return true;
    }

    static bool HandleReloadCreatureQuestStarterCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading Quests Relations... (`creature_queststarter`)");
        sObjectMgr->LoadCreatureQuestStarters();
        handler->SendGlobalGMSysMessage("DB table `creature_queststarter` reloaded.");
        return true;
    }

    static bool HandleReloadLinkedRespawnCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading Linked Respawns... (`creature_linked_respawn`)");
        sObjectMgr->LoadLinkedRespawn();
        handler->SendGlobalGMSysMessage("DB table `creature_linked_respawn` (creature linked respawns) reloaded.");
        return true;
    }

    static bool HandleReloadCreatureQuestEnderCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading Quests Relations... (`creature_questender`)");
        sObjectMgr->LoadCreatureQuestEnders();
        handler->SendGlobalGMSysMessage("DB table `creature_questender` reloaded.");
        return true;
    }

    static bool HandleReloadGossipMenuCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `gossip_menu` Table!");
        sObjectMgr->LoadGossipMenu();
        handler->SendGlobalGMSysMessage("DB table `gossip_menu` reloaded.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadGossipMenuOptionCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `gossip_menu_option` Table!");
        sObjectMgr->LoadGossipMenuItems();
        handler->SendGlobalGMSysMessage("DB table `gossip_menu_option` reloaded.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadGOQuestStarterCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading Quests Relations... (`gameobject_queststarter`)");
        sObjectMgr->LoadGameobjectQuestStarters();
        handler->SendGlobalGMSysMessage("DB table `gameobject_queststarter` reloaded.");
        return true;
    }

    static bool HandleReloadGOQuestEnderCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading Quests Relations... (`gameobject_questender`)");
        sObjectMgr->LoadGameobjectQuestEnders();
        handler->SendGlobalGMSysMessage("DB table `gameobject_questender` reloaded.");
        return true;
    }

    static bool HandleReloadQuestAreaTriggersCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest Area Triggers...");
        sObjectMgr->LoadQuestAreaTriggers();
        handler->SendGlobalGMSysMessage("DB table `areatrigger_involvedrelation` (quest area triggers) reloaded.");
        return true;
    }

    static bool HandleReloadQuestGreetingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest Greeting ...");
        sObjectMgr->LoadQuestGreetings();
        handler->SendGlobalGMSysMessage("DB table `quest_greeting` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesQuestGreetingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest Greeting locales...");
        sObjectMgr->LoadQuestGreetingsLocales();
        handler->SendGlobalGMSysMessage("DB table `quest_greeting_locale` reloaded.");
        return true;
    }

    static bool HandleReloadQuestTemplateCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest Templates...");
        sObjectMgr->LoadQuests();
        sObjectMgr->InitializeQueriesData(QUERY_DATA_QUESTS);
        handler->SendGlobalGMSysMessage("DB table `quest_template` (quest definitions) reloaded.");

        /// dependent also from `gameobject` but this table not reloaded anyway
        LOG_INFO("misc", "Re-Loading GameObjects for quests...");
        sObjectMgr->LoadGameObjectForQuests();
        handler->SendGlobalGMSysMessage("Data GameObjects for quests reloaded.");
        return true;
    }

    static bool HandleReloadCreatureMovementOverrideCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Creature movement overrides...");
        sObjectMgr->LoadCreatureMovementOverrides();
        handler->SendGlobalGMSysMessage("DB table `creature_movement_override` reloaded.");
        return true;
    }

    static bool HandleReloadLootTemplatesCreatureCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 1 (Creature)...");
        LoadLootTemplates_Creature();
        LootTemplates_Creature.CheckLootRefs(LOOT_TYPE_CREATURE);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Creature.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesDisenchantCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 2 (Disenchant)...");
        LoadLootTemplates_Disenchant();
        LootTemplates_Disenchant.CheckLootRefs(LOOT_TYPE_DISENCHANT);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Disenchant.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesFishingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 3 (Fishing)...");
        LoadLootTemplates_Fishing();
        LootTemplates_Fishing.CheckLootRefs(LOOT_TYPE_FISHING);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Fishing.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesGameobjectCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 4 (GameObject)...");
        LoadLootTemplates_Gameobject();
        LootTemplates_Gameobject.CheckLootRefs(LOOT_TYPE_GAMEOBJECT);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for GameObject.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesItemCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 5 (Item)...");
        LoadLootTemplates_Item();
        LootTemplates_Item.CheckLootRefs(LOOT_TYPE_ITEM);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Item.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesMailCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 6 (Mail)...");
        LoadLootTemplates_Mail();
        LootTemplates_Mail.CheckLootRefs(LOOT_TYPE_MAIL);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Mail.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesMillingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 7 (Milling)...");
        LoadLootTemplates_Milling();
        LootTemplates_Milling.CheckLootRefs(LOOT_TYPE_MILLING);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Milling.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesPickpocketingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 8 (PickPocketing)...");
        LoadLootTemplates_Pickpocketing();
        LootTemplates_Pickpocketing.CheckLootRefs(LOOT_TYPE_PICKPOCKETING);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for PickPocketing.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesProspectingCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 9 (Prospecting)...");
        LoadLootTemplates_Prospecting();
        LootTemplates_Prospecting.CheckLootRefs(LOOT_TYPE_PROSPECTING);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Prospecting.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesReferenceCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 10 (Reference)...");
        LoadLootTemplates_Reference();
        LootTemplates_Reference.CheckLootRefs(LOOT_TYPE_REFERENCE);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for reference.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesSkinningCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 11 (Skinning)...");
        LoadLootTemplates_Skinning();
        LootTemplates_Skinning.CheckLootRefs(LOOT_TYPE_SKINNING);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Skinning.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesSpellCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Loot Tables LootType 12 (Spell)...");
        LoadLootTemplates_Spell();
        LootTemplates_Spell.CheckLootRefs(LOOT_TYPE_SPELL);
        handler->SendGlobalGMSysMessage("DB table `world_loot_template` reloaded for Spell.");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadFirelandsStringCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading firelands_string Table!");
        sObjectMgr->LoadFirelandsStrings();
        handler->SendGlobalGMSysMessage("DB table `firelands_string` reloaded.");
        return true;
    }

    static bool HandleReloadWardenactionCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (!sWorld->getBoolConfig(CONFIG_WARDEN_ENABLED))
        {
            handler->SendSysMessage("Warden system disabled by config - reloading warden_action skipped.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        LOG_INFO("misc", "Re-Loading warden_action Table!");
        sWardenCheckMgr->LoadWardenOverrides();
        handler->SendGlobalGMSysMessage("DB table `warden_action` reloaded.");
        return true;
    }

    static bool HandleReloadTrainerCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `trainer` Table!");
        sObjectMgr->LoadTrainers();
        sObjectMgr->LoadCreatureTrainers();
        handler->SendGlobalGMSysMessage("DB table `trainer` reloaded.");
        handler->SendGlobalGMSysMessage("DB table `trainer_locale` reloaded.");
        handler->SendGlobalGMSysMessage("DB table `trainer_spell` reloaded.");
        handler->SendGlobalGMSysMessage("DB table `creature_trainer` reloaded.");
        return true;
    }

    static bool HandleReloadNpcVendorCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `npc_vendor` Table!");
        sObjectMgr->LoadVendors();
        handler->SendGlobalGMSysMessage("DB table `npc_vendor` reloaded.");
        return true;
    }

    static bool HandleReloadPointsOfInterestCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `points_of_interest` Table!");
        sObjectMgr->LoadPointsOfInterest();
        handler->SendGlobalGMSysMessage("DB table `points_of_interest` reloaded.");
        return true;
    }

    static bool HandleReloadQuestPOICommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest POI ..." );
        sObjectMgr->LoadQuestPOI();
        sObjectMgr->InitializeQueriesData(QUERY_DATA_POIS);
        handler->SendGlobalGMSysMessage("DB Table `quest_poi` and `quest_poi_points` reloaded.");
        return true;
    }

    static bool HandleReloadSpellClickSpellsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `npc_spellclick_spells` Table!");
        sObjectMgr->LoadNPCSpellClickSpells();
        handler->SendGlobalGMSysMessage("DB table `npc_spellclick_spells` reloaded.");
        return true;
    }

    static bool HandleReloadReservedNameCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Loading ReservedNames... (`reserved_name`)");
        sObjectMgr->LoadReservedPlayersNames();
        handler->SendGlobalGMSysMessage("DB table `reserved_name` (player reserved names) reloaded.");
        return true;
    }

    static bool HandleReloadReputationRewardRateCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `reputation_reward_rate` Table!" );
        sObjectMgr->LoadReputationRewardRate();
        handler->SendGlobalSysMessage("DB table `reputation_reward_rate` reloaded.");
        return true;
    }

    static bool HandleReloadReputationSpilloverTemplateCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading `reputation_spillover_template` Table!" );
        sObjectMgr->LoadReputationSpilloverTemplate();
        handler->SendGlobalSysMessage("DB table `reputation_spillover_template` reloaded.");
        return true;
    }

    static bool HandleReloadSkillDiscoveryTemplateCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Skill Discovery Table...");
        LoadSkillDiscoveryTable();
        handler->SendGlobalGMSysMessage("DB table `skill_discovery_template` (recipes discovered at crafting) reloaded.");
        return true;
    }

    static bool HandleReloadSkillPerfectItemTemplateCommand(ChatHandler* handler, char const* /*args*/)
    { // latched onto HandleReloadSkillExtraItemTemplateCommand as it's part of that table group (and i don't want to chance all the command IDs)
        LOG_INFO("misc", "Re-Loading Skill Perfection Data Table...");
        LoadSkillPerfectItemTable();
        handler->SendGlobalGMSysMessage("DB table `skill_perfect_item_template` (perfect item procs when crafting) reloaded.");
        return true;
    }

    static bool HandleReloadSkillExtraItemTemplateCommand(ChatHandler* handler, char const* args)
    {
        LOG_INFO("misc", "Re-Loading Skill Extra Item Table...");
        LoadSkillExtraItemTable();
        handler->SendGlobalGMSysMessage("DB table `skill_extra_item_template` (extra item creation when crafting) reloaded.");

        return HandleReloadSkillPerfectItemTemplateCommand(handler, args);
    }

    static bool HandleReloadSkillFishingBaseLevelCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Skill Fishing base level requirements...");
        sObjectMgr->LoadFishingBaseSkillLevel();
        handler->SendGlobalGMSysMessage("DB table `skill_fishing_base_level` (fishing base level for zone/subzone) reloaded.");
        return true;
    }

    static bool HandleReloadSpellAreaCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading SpellArea Data...");
        sSpellMgr->LoadSpellAreas();
        handler->SendGlobalGMSysMessage("DB table `spell_area` (spell dependences from area/quest/auras state) reloaded.");
        return true;
    }

    static bool HandleReloadSpellRequiredCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Required Data... ");
        sSpellMgr->LoadSpellRequired();
        handler->SendGlobalGMSysMessage("DB table `spell_required` reloaded.");
        return true;
    }

    static bool HandleReloadSpellGroupsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Groups...");
        sSpellMgr->LoadSpellGroups();
        handler->SendGlobalGMSysMessage("DB table `spell_group` (spell groups) reloaded.");
        return true;
    }

    static bool HandleReloadSpellLearnSpellCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Learn Spells...");
        sSpellMgr->LoadSpellLearnSpells();
        handler->SendGlobalGMSysMessage("DB table `spell_learn_spell` reloaded.");
        return true;
    }

    static bool HandleReloadSpellLinkedSpellCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Linked Spells...");
        sSpellMgr->LoadSpellLinked();
        handler->SendGlobalGMSysMessage("DB table `spell_linked_spell` reloaded.");
        return true;
    }

    static bool HandleReloadSpellProcsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Proc conditions and data...");
        sSpellMgr->LoadSpellProcs();
        handler->SendGlobalGMSysMessage("DB table `spell_proc` (spell proc conditions and data) reloaded.");
        return true;
    }

    static bool HandleReloadSpellBonusesCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Bonus Data...");
        sSpellMgr->LoadSpellBonuses();
        handler->SendGlobalGMSysMessage("DB table `spell_bonus_data` (spell damage/healing coefficients) reloaded.");
        return true;
    }

    static bool HandleReloadSpellTargetPositionCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell target coordinates...");
        sSpellMgr->LoadSpellTargetPositions();
        handler->SendGlobalGMSysMessage("DB table `spell_target_position` (destination coordinates for spell targets) reloaded.");
        return true;
    }

    static bool HandleReloadSpellThreatsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Aggro Spells Definitions...");
        sSpellMgr->LoadSpellThreats();
        handler->SendGlobalGMSysMessage("DB table `spell_threat` (spell aggro definitions) reloaded.");
        return true;
    }

    static bool HandleReloadSpellGroupStackRulesCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell Group Stack Rules...");
        sSpellMgr->LoadSpellGroupStackRules();
        handler->SendGlobalGMSysMessage("DB table `spell_group_stack_rules` (spell stacking definitions) reloaded.");
        return true;
    }

    static bool HandleReloadSpellPetAurasCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Spell pet auras...");
        sSpellMgr->LoadSpellPetAuras();
        handler->SendGlobalGMSysMessage("DB table `spell_pet_auras` reloaded.");
        return true;
    }

    static bool HandleReloadPageTextsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Page Text...");
        sObjectMgr->LoadPageTexts();
        handler->SendGlobalGMSysMessage("DB table `page_text` reloaded.");
        return true;
    }

    static bool HandleReloadItemEnchantementsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Item Random Enchantments Table...");
        LoadRandomEnchantmentsTable();
        handler->SendGlobalGMSysMessage("DB table `item_enchantment_template` reloaded.");
        return true;
    }

    static bool HandleReloadEventScriptsCommand(ChatHandler* handler, char const* args)
    {
        if (sMapMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            LOG_INFO("misc", "Re-Loading Scripts from `event_scripts`...");

        sObjectMgr->LoadEventScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("DB table `event_scripts` reloaded.");

        return true;
    }

    static bool HandleReloadWpScriptsCommand(ChatHandler* handler, char const* args)
    {
        if (sMapMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            LOG_INFO("misc", "Re-Loading Scripts from `waypoint_scripts`...");

        sObjectMgr->LoadWaypointScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("DB table `waypoint_scripts` reloaded.");

        return true;
    }

    static bool HandleReloadWpCommand(ChatHandler* handler, char const* args)
    {
        if (*args != 'a')
            LOG_INFO("misc", "Re-Loading Waypoints data from 'waypoints_data'");

        sWaypointMgr->Load();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("DB Table 'waypoint_data' reloaded.");

        return true;
    }

    static bool HandleReloadSpellScriptsCommand(ChatHandler* handler, char const* args)
    {
        if (sMapMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            LOG_INFO("misc", "Re-Loading Scripts from `spell_scripts`...");

        sObjectMgr->LoadSpellScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("DB table `spell_scripts` reloaded.");

        return true;
    }

    static bool HandleReloadGameGraveyardZoneCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Graveyard-zone links...");

        sObjectMgr->LoadGraveyardZones();

        handler->SendGlobalGMSysMessage("DB table `game_graveyard_zone` reloaded.");

        return true;
    }

    static bool HandleReloadGameTeleCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Game Tele coordinates...");

        sObjectMgr->LoadGameTele();

        handler->SendGlobalGMSysMessage("DB table `game_tele` reloaded.");

        return true;
    }

    static bool HandleReloadDisablesCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading disables table...");
        DisableMgr::LoadDisables();
        LOG_INFO("misc", "Checking quest disables...");
        DisableMgr::CheckQuestDisables();
        handler->SendGlobalGMSysMessage("DB table `disables` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesAchievementRewardCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Achievement Reward Data Locale...");
        sAchievementMgr->LoadRewardLocales();
        handler->SendGlobalGMSysMessage("DB table `achievement_reward_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLfgRewardsCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading lfg dungeon rewards...");
        sLFGMgr->LoadRewards();
        handler->SendGlobalGMSysMessage("DB table `lfg_dungeon_rewards` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesCreatureCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Creature Template Locale...");
        sObjectMgr->LoadCreatureLocales();
        handler->SendGlobalGMSysMessage("DB table `creature_template_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesCreatureTextCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Creature Texts Locale...");
        sCreatureTextMgr->LoadCreatureTextLocales();
        handler->SendGlobalGMSysMessage("DB table `creature_text_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesGameobjectCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Gameobject Template Locale... ");
        sObjectMgr->LoadGameObjectLocales();
        handler->SendGlobalGMSysMessage("DB table `gameobject_template_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesGossipMenuOptionCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Gossip Menu Option Locale... ");
        sObjectMgr->LoadGossipMenuItemsLocales();
        handler->SendGlobalGMSysMessage("DB table `gossip_menu_option_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesNpcTextCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading NPC Text Locale... ");
        sObjectMgr->LoadNpcTextLocales();
        handler->SendGlobalGMSysMessage("DB table `npc_text_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesPageTextCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Page Text Locale... ");
        sObjectMgr->LoadPageTextLocales();
        handler->SendGlobalGMSysMessage("DB table `locales_page_text` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesPointsOfInterestCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Points Of Interest Locale... ");
        sObjectMgr->LoadPointOfInterestLocales();
        handler->SendGlobalGMSysMessage("DB table `points_of_interest_locale` reloaded.");
        return true;
    }

    static bool HandleReloadLocalesQuestCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Quest Template Locale... ");
        sObjectMgr->LoadQuestLocales();
        handler->SendGlobalGMSysMessage("DB table `quest_template_locale` reloaded.");
        return true;
    }

    static bool HandleReloadMailLevelRewardCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Player level dependent mail rewards...");
        sObjectMgr->LoadMailLevelRewards();
        handler->SendGlobalGMSysMessage("DB table `mail_level_reward` reloaded.");
        return true;
    }

    static bool HandleReloadAuctionsCommand(ChatHandler* handler, char const* /*args*/)
    {
        ///- Reload dynamic data tables from the database
        LOG_INFO("misc", "Re-Loading Auctions...");
        sAuctionMgr->LoadAuctionItems();
        sAuctionMgr->LoadAuctions();
        handler->SendGlobalGMSysMessage("Auctions reloaded.");
        return true;
    }

    static bool HandleReloadConditions(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Conditions...");
        sConditionMgr->LoadConditions(true);
        handler->SendGlobalGMSysMessage("Conditions reloaded.");
        return true;
    }

    static bool HandleReloadCreatureText(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Creature Texts...");
        sCreatureTextMgr->LoadCreatureTexts();
        handler->SendGlobalGMSysMessage("Creature Texts reloaded.");
        return true;
    }

    static bool HandleReloadSmartScripts(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Re-Loading Smart Scripts...");
        sSmartScriptMgr->LoadSmartAIFromDB();
        handler->SendGlobalGMSysMessage("Smart Scripts reloaded.");
        return true;
    }

    static bool HandleReloadVehicleAccessoryCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Reloading vehicle_accessory table...");
        sObjectMgr->LoadVehicleAccessories();
        handler->SendGlobalGMSysMessage("Vehicle accessories reloaded.");
        return true;
    }

    static bool HandleReloadVehicleTemplateAccessoryCommand(ChatHandler* handler, char const* /*args*/)
    {
        LOG_INFO("misc", "Reloading vehicle_template_accessory table...");
        sObjectMgr->LoadVehicleTemplateAccessories();
        handler->SendGlobalGMSysMessage("Vehicle template accessories reloaded.");
        return true;
    }

};

void AddSC_reload_commandscript()
{
    new reload_commandscript();
}
