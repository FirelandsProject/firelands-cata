/*
	[Fix/Quest]: Proving pit (24768).
    [Fix/DB]: Remove duplicate entry for gossip option in npc 39062.
*/

DELETE FROM `gossip_menu_option` WHERE `MenuId`=10974 AND `OptionIndex`=1;
UPDATE `conditions` SET `SourceEntry`= 0  WHERE `SourceTypeorReferenceId`=15 and `SourceGroup`=10974 and `SourceEntry`=1;
UPDATE `gossip_menu_option` SET `OptionType`=1, `OptionNpcflag`=1 WHERE `MenuId`=10974 AND `OptionIndex`=0;

-- Darkspear Jailor
SET @ENTRY := 39062;
UPDATE `creature` SET  `zoneId`=6453, `areaId`=4865, `modelid`=31289, `curhealth`=1110 WHERE `id`=@ENTRY;
UPDATE `creature_template` SET `MovementType`=2 WHERE `entry`=@ENTRY;

-- Darkspear Jailor SAI
SET @GUID := -309082;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY*100+01 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,0,1,62,0,100,0,10974,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Say Line 0"),
(@GUID,0,1,2,61,0,100,0,0,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Quest Credit ''"),
(@GUID,0,2,3,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Say Line 0"),
(@GUID,0,3,0,61,0,100,0,0,0,0,0,80,@ENTRY*100+01,0,2,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Run Script"),
(@GUID,0,4,5,40,0,100,0,3,@ENTRY*10+01,0,0,9,0,0,0,0,0,0,15,201968,10,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Activate Gameobject"),
(@GUID,0,5,6,61,0,100,0,0,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Pause Waypoint"),
(@GUID,0,6,0,61,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Set Run Off"),
(@ENTRY*100+01,9,0,0,0,0,100,0,0,0,0,0,53,1,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Script - Start Waypoint");

-- Darkspear Jailor SAI
SET @GUID := -309155;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@GUID AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY*100+00 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUID,0,0,1,62,0,100,0,10974,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Say Line 0"),
(@GUID,0,1,2,61,0,100,0,0,0,0,0,33,@ENTRY,0,0,0,0,0,7,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Quest Credit ''"),
(@GUID,0,2,3,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Say Line 0"),
(@GUID,0,3,0,61,0,100,0,0,0,0,0,80,@ENTRY*100+00,0,2,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Gossip Option 0 Selected - Run Script"),
(@GUID,0,4,5,40,0,100,0,3,@ENTRY*10+00,0,0,9,0,0,0,0,0,0,15,201968,10,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Activate Gameobject"),
(@GUID,0,5,6,61,0,100,0,0,0,0,0,54,1000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Pause Waypoint"),
(@GUID,0,6,0,61,0,100,0,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Waypoint 3 Reached - Set Run Off"),
(@ENTRY*100+00,9,0,0,0,0,100,0,0,0,0,0,53,1,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Darkspear Jailor - On Script - Start Waypoint");

DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Get in the pit and show us your stuff, $Gboy:girl;.', 12, 0, 100, 0, 0, 0, 37886, 0, '');

DELETE FROM `waypoints` WHERE `entry`=@ENTRY*10+00;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1143.20, -5429.86, 13.8643, 'Point 1'),
(@ENTRY*10+00, 2, -1137.68, -5429.41, 13.7173, 'Point 2'),
(@ENTRY*10+00, 3, -1136.07, -5416.94, 13.2693, 'Point 3'),
(@ENTRY*10+00, 4, -1137.68, -5429.41, 13.7173, 'Point 4'),
(@ENTRY*10+00, 5, -1143.20, -5429.86, 13.8643, 'Point 5');

DELETE FROM `waypoints` WHERE `entry`=@ENTRY*10+01;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+01, 1, -1159.23, -5530.07, 11.9526, 'Point 1'),
(@ENTRY*10+01, 2, -1159.07, -5520.38, 12.0749, 'Point 2'),
(@ENTRY*10+01, 3, -1153.49, -5518.96, 11.9982, 'Point 3'),
(@ENTRY*10+01, 4, -1158.26, -5519.84, 12.0920, 'Point 4'),
(@ENTRY*10+01, 5, -1159.07, -5529.94, 11.9540, 'Point 5');

-- Darkspear Cage
SET @ENTRY := 201968;
UPDATE `gameobject_template` SET `Data0`=920, `Data3`=600000, `ScriptName`='SmartGameObjectAI' WHERE `entry`=@ENTRY;
UPDATE `gameobject` SET  `zoneId`=6453, `areaId`=4865 WHERE `id`=@ENTRY;

-- Darkspear Cage SAI
UPDATE `gameobject_template` SET `AIName`="SmartGameObjectAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,1,0,0,70,0,100,0,2,0,0,0,45,1,1,0,0,0,0,11,38142,10,0,0,0,0,0,"Darkspear Cage - On Gameobject State Changed - Set Data 1 1");

-- Captive Spitescale Scout
SET @ENTRY := 38142;
UPDATE `creature_template` SET `spell1`=15089 WHERE `entry`=@ENTRY;
UPDATE `creature` SET `zoneId`=6453, `areaId`=4865, `spawntimesecs`=60 WHERE `id`=@ENTRY;

-- Captive Spitescale Scout SAI
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,1000,2000,10000,11000,11,15089,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Frost Cleave'),
(@ENTRY,0,1,2,38,0,100,0,1,1,0,0,114,0,0,0,0,0,0,1,0,0,0,0,10,0,0,"Captive Spitescale Scout - On Data Set 1 1"),
(@ENTRY,0,2,3,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captive Spitescale Scout - On Data Set 1 1- Say Line 0"),
(@ENTRY,0,3,4,61,0,100,0,0,0,0,0,19,256,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captive Spitescale Scout - Set Hostile"),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,21,100,0,0,0,0,0,0,"Captive Spitescale Scout - Start Attack"),
(@ENTRY,0,6,0,6,0,100,0,0,0,0,0,45,2,2,0,0,0,0,11,38242,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 2 2"),
(@ENTRY,0,7,0,6,0,100,0,0,0,0,0,45,3,3,0,0,0,0,11,38247,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 3 3"),
(@ENTRY,0,8,0,6,0,100,0,0,0,0,0,45,4,4,0,0,0,0,11,38246,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 4 4"),
(@ENTRY,0,9,0,6,0,100,0,0,0,0,0,45,5,5,0,0,0,0,11,38244,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 5 5"),
(@ENTRY,0,10,0,6,0,100,0,0,0,0,0,45,6,6,0,0,0,0,11,38245,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 6 6"),
(@ENTRY,0,11,0,6,0,100,0,0,0,0,0,45,8,8,0,0,0,0,11,38037,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 8 8"),
(@ENTRY,0,12,0,6,0,100,0,0,0,0,0,45,9,9,0,0,0,0,11,38243,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 9 9"),
(@ENTRY,0,13,0,6,0,100,0,0,0,0,0,45,10,10,0,0,0,0,11,42618,20,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Data 10 10"),
(@ENTRY,0,14,0,6,0,100,0,0,0,0,0,9,0,0,0,0,0,0,14,218472,0,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Lootstate Ready"),
(@ENTRY,0,15,16,6,0,100,0,0,0,0,0,27,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Stop combat"),
(@ENTRY,0,16,0,61,0,100,0,0,0,0,0,18,256,0,0,0,0,0,1,0,0,0,0,0,0,0,"Captive Spitescale Scout - On Just Died - Set Flag IMMUNE_TO_PC(256)");

DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'The Sssea Witch will kill you all.', 12, 0, 100, 0, 0, 0, 39090, 0, 'Captive Spitescale Scout');

-- Nekali SAI
SET @ENTRY := 38242;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,2,2,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nekali - On Data Set 2 2 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24762,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Nekali - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24762,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Nekali - On Quest '' Taken - Start Waypoint");

-- Nekali Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Nekali');

-- Nekali Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1160.19, -5396.27, 12.2370, 'Point 1'),
(@ENTRY*10+00, 2, -1150.25, -5407.53, 13.2418, 'Point 2'),
(@ENTRY*10+01, 1, -1150.25, -5407.53, 13.2418, 'Point 1'),
(@ENTRY*10+01, 2, -1160.19, -5396.27, 12.2370, 'Point 2');

DELETE FROM `creature_queststarter` WHERE `id`=@ENTRY AND `quest`=24760;
DELETE FROM `creature_questender` WHERE `id`=@ENTRY AND `quest`=24760;

-- Ortezza SAI
SET @ENTRY := 38247;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,3,3,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Ortezza - On Data Set 3 3 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24780,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Ortezza - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24780,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Ortezza - On Quest '' Taken - Start Waypoint");

-- Ortezza Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Ortezza');

-- Ortezza Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1128.28, -5510.01, 11.9823, 'Point 1'),
(@ENTRY*10+00, 2, -1136.21, -5526.92, 11.9810, 'Point 2'),
(@ENTRY*10+01, 1, -1136.21, -5526.92, 11.9810, 'Point 1'),
(@ENTRY*10+01, 2, -1128.28, -5510.01, 11.9823, 'Point 2');

-- Soratha SAI
SET @ENTRY := 38246;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,4,4,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Soratha - On Data Set 4 4 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24754,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Soratha - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24754,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Soratha - On Quest '' Taken - Start Waypoint");

-- Soratha Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Soratha');

-- Soratha Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1152.24, -5569.91, 11.9353, 'Point 1'),
(@ENTRY*10+00, 2, -1146.48, -5541.75, 12.4997, 'Point 2'),
(@ENTRY*10+01, 1, -1146.48, -5541.75, 12.4997, 'Point 1'),
(@ENTRY*10+01, 2, -1152.24, -5569.91, 11.9353, 'Point 2');

-- Legati SAI
SET @ENTRY := 38244;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,5,5,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Legati - On Data Set 5 5 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24774,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Legati - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24774,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Legati - On Quest '' Taken - Start Waypoint");

-- Legati Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Legati');

-- Legati Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1126.19, -5446.60, 11.9830, 'Point 1'),
(@ENTRY*10+00, 2, -1145.74, -5429.52, 13.6803, 'Point 2'),
(@ENTRY*10+01, 1, -1145.74, -5429.52, 13.6803, 'Point 1'),
(@ENTRY*10+01, 2, -1126.19, -5446.60, 11.9830, 'Point 2');

-- Tunari SAI
SET @ENTRY := 38245;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,6,6,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Tunari - On Data Set 6 6 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24786,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Tunari - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24786,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Tunari - On Quest '' Taken - Start Waypoint");

-- Tunari Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Tunari');

-- Tunari Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1118.18, -5540.01, 11.9782, 'Point 1'),
(@ENTRY*10+00, 2, -1137.49, -5528.34, 11.9790, 'Point 2'),
(@ENTRY*10+01, 1, -1137.49, -5528.34, 11.9790, 'Point 1'),
(@ENTRY*10+01, 2, -1118.18, -5540.01, 11.9782, 'Point 2');

-- Nortet SAI
SET @ENTRY := 38037;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,8,8,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Nortet - On Data Set 8 8 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24642,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Nortet - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24642,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Nortet - On Quest '' Taken - Start Waypoint");

-- Nortet Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Nortet');

-- Nortet Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1171.06, -5441.19, 11.9470, 'Point 1'),
(@ENTRY*10+00, 2, -1159.10, -5419.11, 13.2431, 'Point 2'),
(@ENTRY*10+01, 1, -1159.10, -5419.11, 13.2431, 'Point 1'),
(@ENTRY*10+01, 2, -1171.06, -5441.19, 11.9470, 'Point 2');

-- Zentabra SAI
SET @ENTRY := 38243;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,9,9,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Zentabra - On Data Set 9 9 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,24768,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Zentabra - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,24768,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Zentabra - On Quest '' Taken - Start Waypoint");

-- Zentabra Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Zentabra');

-- Zentabra Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1175.60, -5540.47, 11.9406, 'Point 1'),
(@ENTRY*10+00, 2, -1158.96, -5532.81, 11.9406, 'Point 2'),
(@ENTRY*10+01, 1, -1158.96, -5532.81, 11.9406, 'Point 1'),
(@ENTRY*10+01, 2, -1175.60, -5540.47, 11.9406, 'Point 2');

-- Voldreka SAI
SET @ENTRY := 42618;
UPDATE `creature_template` SET `AIName`="SmartAI" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,38,0,100,0,10,10,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Voldreka - On Data Set 10 10 - Say Line 0"),
(@ENTRY,0,1,0,20,0,100,0,26276,0,0,0,53,0,@ENTRY*10+01,0,0,0,0,1,0,0,0,0,0,0,0,"Voldreka - On Quest '' Finished - Start Waypoint"),
(@ENTRY,0,2,0,19,0,100,0,26276,0,0,0,53,0,@ENTRY*10+00,0,0,0,0,1,0,0,0,0,0,0,0,"Voldreka - On Quest '' Taken - Start Waypoint");

-- Voldreka Text
DELETE FROM `creature_text` WHERE `CreatureID`=@ENTRY;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@ENTRY, 0, 0, 'Well done, $n!', 12, 0, 100, 0, 0, 0, 37898, 0, 'Voldreka');

-- Voldreka Waypoints
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY*10+00,@ENTRY*10+01);
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES
(@ENTRY*10+00, 1, -1126.12, -5395.10, 12.2185, 'Point 1'),
(@ENTRY*10+00, 2, -1149.21, -5408.07, 13.2484, 'Point 2'),
(@ENTRY*10+01, 1, -1149.21, -5408.07, 13.2484, 'Point 1'),
(@ENTRY*10+01, 2, -1126.12, -5395.10, 12.2185, 'Point 2');
