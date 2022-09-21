/*
    (Fix/Quest): Necessary Roughness (24502)
*/
UPDATE `creature_template` SET `npcflag` = 2 WHERE `entry` = 37106;
UPDATE `creature_template` SET `vehicleId` = 582, `IconName` = "vehichleCursor" WHERE `entry`= 37179;
UPDATE `creature_template` SET `vehicleId` = 116, `IconName` = "vehichleCursor" WHERE `entry`= 37213;

UPDATE `quest_template_addon` SET `ScriptName`="quest_fourth_and_goal" WHERE `ID` IN (28414);
UPDATE `creature_template` SET `ScriptName`="npc_coach_crosscheck" WHERE `entry` = 37106;
UPDATE `creature_template` SET `ScriptName`="npc_bucanneer_gob" WHERE `entry` IN (37179, 37213);
UPDATE `creature_template` SET `ScriptName`="npc_shark_gob" WHERE `entry` = 37114;
UPDATE `creature_template` SET `ScriptName`="npc_fourth_and_goal_target" WHERE `entry` = 37203;
UPDATE `creature_template` SET `ScriptName`="npc_fourth_and_goal_deathwing" WHERE `entry` = 48572;
