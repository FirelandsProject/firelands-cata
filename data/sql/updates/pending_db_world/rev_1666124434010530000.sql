UPDATE `creature_template` SET `ScriptName` = "npc_bilgewater_bucaneer", `NpcFlag` = 1 WHERE `entry` IN (37179,37213);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (70052,69987);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(70052, "npc_fourth_and_goal_kick_footbomb"),
(69987, "spell_kezan_despawn_sharks");