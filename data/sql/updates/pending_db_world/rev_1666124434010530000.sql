UPDATE `creature_template` SET `ScriptName` = "npc_bilgewater_bucaneer", `NpcFlag` = 1 WHERE `entry` IN (37179,37213);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (70052,69987);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(70052, "npc_fourth_and_goal_kick_footbomb"),
(69987, "spell_kezan_despawn_sharks");

DELETE FROM `creature_template_movement` WHERE `CreatureId` = 48572;
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES 
(48572, 1, 0, 1, 0, 0, 0);

DELETE FROM `creature_text` WHERE `CreatureID` IN (48572,37213);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(48572, 0, 0, '', 41, 0, 100, 0, 0, 0, 37041, 0, 'Fourth and Goal Deathwing Dialog.'),
(37213, 0, 0, '', 41, 0, 100, 0, 0, 0, 37050, 0, 'Fourth and Goal First Dialogue.');