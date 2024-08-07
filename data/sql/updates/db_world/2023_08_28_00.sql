-- add npcs in their place they were absent before
DELETE FROM `creature` WHERE `guid` IN (3254, 3256);
INSERT INTO `creature` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseUseFlags`, `phaseMask`, `PhaseId`, `PhaseGroup`, `terrainSwapMap`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`, `ScriptName`, `VerifiedBuild`) VALUES
(3254, 10676, 1, 0, 0, 1, 0, 1, 169, 0, -1, 0, 0, -599.237, -4291.68, 37.8486, 4.70128, 300, 0, 0, 2440, 0, 0, 0, 0, 0, NULL, 0),
(3256, 10682, 1, 0, 0, 1, 0, 1, 169, 0, -1, 0, 0, -596.62146, -4292.42, 37.8486, 4.70128, 300, 0, 0, 2440, 0, 0, 0, 0, 0, NULL, 0);

-- removes gossip_menu_id as npc does not have gossip and does not give xp on kill
UPDATE `creature_template` SET `gossip_menu_id`=0, `npcflag`=0, `flags_extra`=32832 WHERE  `entry`=10676;

-- delete any and all waypoint data and creature addon dealing with the two raiders for rebuild
DELETE FROM `waypoint_data` WHERE `id` IN (32540, 32560);
DELETE FROM `creature_addon` WHERE `guid` IN (3254, 3256);

DELETE FROM `creature_template_addon` WHERE `entry` IN (10676, 10682);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes2`) VALUES
(10676, 207, 1),
(10682, 2328, 1);

-- place them in a formation
DELETE FROM `creature_formations` WHERE `leaderGUID`=3254;
INSERT INTO `creature_formations` (`LeaderGUID`, `MemberGUID`, `FollowDistance`, `FollowAngle`, `GroupAI`, `InversionPoint1`, `InversionPoint2`) VALUES
(3254, 3254, 3, 0, 515, 0, 0),
(3254, 3256, 3, 270, 515, 0, 0);

-- the smart scripts
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (10676, 10682) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` BETWEEN 1067600 AND 1067604 AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1068200 AND `source_type`=9;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(10676, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 0, 53, 1, 1067600, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Respawn - Start Waypoint 1067600 (Run)"),
(10676, 0, 1, 0, 40, 0, 100, 0, 8, 1067600, 0, 0, 0, 80, 1067600, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 8 (Path 1067600) Reached - Run Script"),
(10676, 0, 2, 0, 40, 0, 100, 0, 8, 1067601, 0, 0, 0, 80, 1067601, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 8 (Path 1067601) Reached - Run Script"),
(10676, 0, 3, 0, 40, 0, 100, 0, 30, 1067602, 0, 0, 0, 80, 1067602, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 30 (Path 1067602) Reached - Run Script"),
(10676, 0, 4, 0, 40, 0, 100, 0, 58, 1067602, 0, 0, 0, 80, 1067603, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 58 (Path 1067602) Reached - Run Script"),
(10676, 0, 5, 0, 40, 0, 100, 0, 8, 1067603, 0, 0, 0, 80, 1067604, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 8 (Path 1067603) Reached - Run Script"),
(10676, 0, 6, 0, 40, 0, 100, 0, 7, 1067604, 0, 0, 0, 53, 0, 1067605, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 7 (Path 1067604) Reached - Start Waypoint 1067605 (Walk)"),
(10676, 0, 7, 0, 40, 0, 100, 0, 9, 1067605, 0, 0, 0, 53, 1, 1067600, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Waypoint 9 (Path 1067605) Reached - Start Waypoint 1067600 (Run)"),
(10676, 0, 8, 0, 34, 0, 100, 0, 8, 1, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0.523598790168762207, "Raider Jhash - On Point 1 Reached - Set Orientation"),
(10676, 0, 9, 10, 4, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Aggro - Say Line 1"),
(10676, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 4, 6495, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Aggro - Play Sound 6495"),

(1067600, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 53, 0, 1067601, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Start Waypoint 1067601 (Walk)"),
(1067601, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 4, 6494, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Play Sound 6494"),
(1067601, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 53, 1, 1067602, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Start Waypoint 1067602 (Run)"),

(1067602, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 54, 60000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Pause Waypoint"),
(1067602, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 5.515240192413330078, "Raider Jhash - Set Orientation"),
(1067602, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 80, 1068200, 0, 0, 0, 0, 0, 19, 10682, 50, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Playaction Script (Raider Kerr)"),
(1067602, 9, 3, 0, 0, 0, 100, 0, 17000, 17000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Say Line 0"),
(1067602, 9, 4, 0, 0, 0, 100, 0, 40000, 40000, 0, 0, 0, 5, 15, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Play Emote 'Roar'"),
(1067602, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 4, 6494, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Play Sound 6494"),
(1067602, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Resume Waypoint"),

(1067603, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 5, 66, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Play Emote 'Salute'"),
(1067603, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 5, 66, 0, 0, 0, 0, 0, 19, 10682, 50, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Play Emote 'Salute' (Raider Kerr)"),
(1067603, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 53, 0, 1067603, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Start Waypoint 1067603 (Walk)"),

(1067604, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 53, 1, 1067604, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Raider Jhash - On Script - Start Waypoint 1067604 (Run)"),

(10682, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 0, 29, 2.5, 90, 0, 0, 0, 0, 10, 3254, 10676, 0, 0, 0, 0, 0, "Raider Kerr - On Respawn - Follow Jhash"),
(1068200, 9, 0, 0, 0, 0, 100, 0, 1000, 1000, 0, 0, 0, 69, 5, 0, 0, 0, 0, 0, 8, 0, 0, 0, 329.32263, -4714.65722, 13.73018, 0, "Raider Kerr - Move To Pos"),

(1068200, 9, 1, 0, 0, 0, 100, 0, 400, 400, 0, 0, 0, 69, 5, 0, 0, 0, 0, 0, 8, 0, 0, 0, 330.68191, -4711.53515, 14.45225, 0, "Raider Kerr - Move To Pos"),
(1068200, 9, 2, 0, 0, 0, 100, 0, 400, 400, 0, 0, 0, 69, 5, 0, 0, 0, 0, 0, 8, 0, 0, 0, 331.87692, -4712.71337, 14.20777, 0, "Raider Kerr - Move To Pos"),
(1068200, 9, 3, 0, 0, 0, 100, 0, 400, 400, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 5.22995, "Raider Kerr - Set Orientation"),
(1068200, 9, 4, 0, 11, 0, 100, 0, 55000, 55000, 0, 0, 0, 29, 2.5, 90, 0, 0, 0, 0, 10, 3254, 10676, 0, 0, 0, 0, 0, "Raider Kerr - On Respawn - Follow Jhash");

-- add missing creature text
DELETE FROM `creature_text` WHERE `CreatureID`=10676;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(10676, 0, 0, "%s and Raider Kerr let their wolves rest a bit and drink...", 16, 0, 100, 0, 0, 0, 5986, 0, "Raider Jhash"),
(10676, 1, 0, "%s and Raider Kerr charge into battle...", 16, 0, 100, 0, 0, 0, 5987, 0, "Raider Jhash");

DELETE FROM `waypoints` WHERE `entry` BETWEEN 1067600 AND 1067605;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `point_comment`) VALUES
(1067600, 1, -599.2371, -4291.6836, 37.848602, 0, 0, "Raider Jhash"),
(1067600, 2, -599.7293, -4335.894, 37.688942, 0, 0, "Raider Jhash"),
(1067600, 3, -601.2648, -4384.689, 41.060635, 0, 0, "Raider Jhash"),
(1067600, 4, -598.0551, -4419.4204, 43.002014, 0, 0, "Raider Jhash"),
(1067600, 5, -584.5332, -4447.333, 41.701958, 0, 0, "Raider Jhash"),
(1067600, 6, -570.7077, -4472.1426, 42.374924, 0, 0, "Raider Jhash"),
(1067600, 7, -570.6846, -4501.2607, 42.598244, 0, 0, "Raider Jhash"),
(1067600, 8, -585.5773, -4518.713, 42.16514, 0, 0, "Raider Jhash"),

(1067601, 1, -576.5585, -4541.884, 41.42739, 0, 0, "Raider Jhash"),
(1067601, 2, -561.1756, -4549.6494, 41.684326, 0, 0, "Raider Jhash"),
(1067601, 3, -550.39703, -4557.4243, 41.501465, 0, 0, "Raider Jhash"),
(1067601, 4, -548.9717, -4570.2046, 41.336086, 0, 0, "Raider Jhash"),
(1067601, 5, -556.14606, -4581.976, 41.360744, 0, 0, "Raider Jhash"),
(1067601, 6, -580.87695, -4576.482, 41.440994, 0, 0, "Raider Jhash"),
(1067601, 7, -595.3176, -4577.6396, 40.936844, 0, 0, "Raider Jhash"),
(1067601, 8, -603.52106, -4601.4224, 41.33285, 0, 1000, "Raider Jhash"),

(1067602, 1, -603.5151, -4638.0845, 39.97652, 0, 0, "Raider Jhash"),
(1067602, 2, -603.6497, -4681.4507, 38.446796, 0, 0, "Raider Jhash"),
(1067602, 3, -587.5975, -4717.4146, 34.612785, 0, 0, "Raider Jhash"),
(1067602, 4, -562.9297, -4734.5234, 33.51207, 0, 0, "Raider Jhash"),
(1067602, 5, -522.4446, -4753.3247, 32.819477, 0, 0, "Raider Jhash"),
(1067602, 6, -483.75717, -4771.397, 32.07699, 0, 0, "Raider Jhash"),
(1067602, 7, -441.95572, -4778.6074, 32.86317, 0, 0, "Raider Jhash"),
(1067602, 8, -400.21158, -4799.721, 32.80925, 0, 0, "Raider Jhash"),
(1067602, 9, -362.8971, -4817.076, 32.30573, 0, 0, "Raider Jhash"),
(1067602, 10, -316.79178, -4809.2085, 30.34805, 0, 0, "Raider Jhash"),
(1067602, 11, -281.21582, -4800.572, 28.988167, 0, 0, "Raider Jhash"),
(1067602, 12, -235.25412, -4791.385, 25.662184, 0, 0, "Raider Jhash"),
(1067602, 13, -196.36171, -4776.911, 23.777937, 0, 0, "Raider Jhash"),
(1067602, 14, -164.07004, -4760.921, 23.24671, 0, 0, "Raider Jhash"),
(1067602, 15, -116.39774, -4749.244, 22.060966, 0, 0, "Raider Jhash"),
(1067602, 16, -90.16314, -4744.409, 21.303497, 0, 0, "Raider Jhash"),
(1067602, 17, -50.609863, -4746.969, 20.990366, 0, 0, "Raider Jhash"),
(1067602, 18, -27.26709, -4752.6387, 21.397404, 0, 0, "Raider Jhash"),
(1067602, 19, 21.396755, -4745.7646, 22.191298, 0, 0, "Raider Jhash"),
(1067602, 20, 63.49501, -4743.182, 19.271624, 0, 0, "Raider Jhash"),
(1067602, 21, 92.094376, -4742.205, 17.27318, 0, 0, "Raider Jhash"),
(1067602, 22, 131.74504, -4765.455, 12.510933, 0, 0, "Raider Jhash"),
(1067602, 23, 152.06288, -4766.4907, 11.915387, 0, 0, "Raider Jhash"),
(1067602, 24, 184.83345, -4748.722, 11.376129, 0, 0, "Raider Jhash"),
(1067602, 25, 224.2197, -4741.7437, 10.2271185, 0, 0, "Raider Jhash"),
(1067602, 26, 248.53986, -4737.5625, 10.174372, 0, 0, "Raider Jhash"),
(1067602, 27, 268.48297, -4748.651, 9.945413, 0, 0, "Raider Jhash"),
(1067602, 28, 292.89496, -4739.643, 9.445413, 0, 0, "Raider Jhash"),
(1067602, 29, 315.01544, -4721.6387, 11.161858, 0, 1000, "Raider Jhash"),
(1067602, 30, 330.34033, -4717.3843, 13.432976, 0, 0, "Raider Jhash"),
(1067602, 31, 300.93216, -4734.499, 9.456657, 0, 0, "Raider Jhash"),
(1067602, 32, 259.13663, -4745.543, 10.265436, 0, 0, "Raider Jhash"),
(1067602, 33, 242.19347, -4735.6865, 10.174372, 0, 0, "Raider Jhash"),
(1067602, 34, 211.73262, -4744.541, 10.4771185, 0, 0, "Raider Jhash"),
(1067602, 35, 165.80643, -4756.8716, 11.665387, 0, 0, "Raider Jhash"),
(1067602, 36, 137.9082, -4768.714, 12.052091, 0, 0, "Raider Jhash"),
(1067602, 37, 101.19268, -4747.204, 16.555244, 0, 0, "Raider Jhash"),
(1067602, 38, 65.22982, -4739.0806, 19.004534, 0, 0, "Raider Jhash"),
(1067602, 39, 46.486057, -4745.1973, 20.724749, 0, 0, "Raider Jhash"),
(1067602, 40, 6.258626, -4750.5312, 22.066298, 0, 0, "Raider Jhash"),
(1067602, 41, -35.577312, -4751.9727, 21.240366, 0, 0, "Raider Jhash"),
(1067602, 42, -69.944176, -4744.792, 20.803497, 0, 0, "Raider Jhash"),
(1067602, 43, -108.87934, -4746.857, 22.002617, 0, 0, "Raider Jhash"),
(1067602, 44, -153.25586, -4758.7554, 23.202032, 0, 0, "Raider Jhash"),
(1067602, 45, -195.36014, -4773.2456, 23.777937, 0, 0, "Raider Jhash"),
(1067602, 46, -242.28743, -4789.2783, 25.895338, 0, 0, "Raider Jhash"),
(1067602, 47, -282.123, -4800.222, 28.988167, 0, 0, "Raider Jhash"),
(1067602, 48, -325.77042, -4810.031, 30.752834, 0, 0, "Raider Jhash"),
(1067602, 49, -360.74756, -4814.1533, 32.43073, 0, 0, "Raider Jhash"),
(1067602, 50, -385.3788, -4807.941, 32.647865, 0, 0, "Raider Jhash"),
(1067602, 51, -421.02887, -4788.0566, 32.329025, 0, 0, "Raider Jhash"),
(1067602, 52, -461.6259, -4771.8433, 32.464977, 0, 0, "Raider Jhash"),
(1067602, 53, -502.95486, -4765.191, 32.563618, 0, 0, "Raider Jhash"),
(1067602, 54, -545.53406, -4742.614, 33.28868, 0, 0, "Raider Jhash"),
(1067602, 55, -585.4644, -4722.433, 34.362785, 0, 0, "Raider Jhash"),
(1067602, 56, -603.311, -4687.974, 37.78908, 0, 0, "Raider Jhash"),
(1067602, 57, -604.6183, -4646.8384, 39.59322, 0, 0, "Raider Jhash"),
(1067602, 58, -605.4658, -4617.5815, 40.83285, 0, 0, "Raider Jhash"),

(1067603, 1, -604.02527, -4601.9395, 41.33285, 0, 0, "Raider Jhash"),
(1067603, 2, -599.3594, -4580.025, 40.775467, 0, 0, "Raider Jhash"),
(1067603, 3, -605.0215, -4570.3887, 41.265697, 0, 0, "Raider Jhash"),
(1067603, 4, -629.72644, -4561.113, 41.531494, 0, 0, "Raider Jhash"),
(1067603, 5, -634.988, -4551.78, 41.45483, 0, 0, "Raider Jhash"),
(1067603, 6, -630.24695, -4537.6045, 41.406494, 0, 0, "Raider Jhash"),
(1067603, 7, -618.5096, -4532.729, 41.46484, 0, 0, "Raider Jhash"),
(1067603, 8, -588.9078, -4523.6235, 41.701027, 0, 0, "Raider Jhash"),

(1067604, 1, -570.4182, -4500.8887, 42.598244, 0, 0, "Raider Jhash"),
(1067604, 2, -571.04224, -4474.9595, 42.69255, 0, 0, "Raider Jhash"),
(1067604, 3, -591.1685, -4436.435, 42.01983, 0, 0, "Raider Jhash"),
(1067604, 4, -602.0001, -4403.7026, 43.60982, 0, 0, "Raider Jhash"),
(1067604, 5, -599.8392, -4357.3574, 38.563942, 0, 0, "Raider Jhash"),
(1067604, 6, -600.4566, -4327.557, 37.63661, 0, 0, "Raider Jhash"),
(1067604, 7, -601.6419, -4288.526, 37.926933, 0, 0, "Raider Jhash"),

(1067605, 1, -612.84106, -4276.936, 37.926933, 0, 0, "Raider Jhash"),
(1067605, 2, -625.5621, -4261.94, 38.31095, 0, 0, "Raider Jhash"),
(1067605, 3, -628.084, -4246, 38.43595, 0, 0, "Raider Jhash"),
(1067605, 4, -621.9834, -4229.883, 38.383945, 0, 0, "Raider Jhash"),
(1067605, 5, -607.5233, -4224.2124, 38.383945, 0, 0, "Raider Jhash"),
(1067605, 6, -591.1214, -4229.637, 38.498894, 0, 0, "Raider Jhash"),
(1067605, 7, -579.3559, -4238.155, 38.11686, 0, 0, "Raider Jhash"),
(1067605, 8, -576.72754, -4251.9297, 38.06095, 0, 0, "Raider Jhash"),
(1067605, 9, -580.829, -4268.681, 38.098602, 0, 0, "Raider Jhash");