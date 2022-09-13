/*
    Fix: Quest Rolling with my homies (14071)
*/
UPDATE `creature_template` SET `VehicleId`= 448, `ScriptName`='npc_hot_rod' WHERE `entry`=34840;
UPDATE `creature_template` SET `ScriptName` = "npc_homies" WHERE `entry` IN (34890, 34892, 34954);
UPDATE `creature_template` SET `ScriptName` = "npc_homies_summon" WHERE `entry` IN (34959, 34957, 34958);

UPDATE `quest_template_addon` SET `ScriptName` = "quest_rolling_with_my_homies" WHERE `ID` = 14071;
