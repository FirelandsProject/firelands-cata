DELETE FROM `smart_scripts` WHERE  `entryorguid` IN (36452, 36741) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(36452, 0, 0, 1, 19, 0, 100, 0, 14465, 0, 0, 0, 0, 85, 69256, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, ''),
(36452, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 0, 85, 82892, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(36452, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 85, 105011, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(36741, 0, 0, 0, 60, 0, 100, 513, 1000, 1000, 0, 0, 0, 53, 1, 36741, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(36741, 0, 1, 0, 40, 0, 100, 512, 2, 36741, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 9956226, 196399, 0, 0, 0, 0, 0, ''),
(36741, 0, 2, 0, 40, 0, 100, 512, 3, 36741, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 9956226, 196399, 0, 0, 0, 0, 0, ''),
(36741, 0, 3, 0, 40, 0, 100, 512, 10, 36741, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 58409, 196401, 0, 0, 0, 0, 0, ''),
(36741, 0, 4, 5, 40, 0, 100, 512, 11, 36741, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 14, 58409, 196401, 0, 0, 0, 0, 0, ''),
(36741, 0, 5, 6, 61, 0, 100, 512, 0, 0, 0, 0, 0, 28, 69254, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(36741, 0, 6, 7, 61, 0, 100, 512, 0, 0, 0, 0, 0, 11, 89180, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(36741, 0, 7, 0, 61, 0, 100, 512, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=20 AND `SourceGroup`=0 AND `SourceEntry`=14465 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=14402 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=20 AND `SourceGroup`=0 AND `SourceEntry`=14465 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=14405 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=20 AND `SourceGroup`=0 AND `SourceEntry`=14465 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=8 AND `ConditionTarget`=0 AND `ConditionValue1`=14463 AND `ConditionValue2`=0 AND `ConditionValue3`=0;
INSERT INTO `conditions` VALUES 
(20, 0, 14465, 0, 0, 8, 0, 14402, 0, 0, 0, 0, 0, '', NULL),
(20, 0, 14465, 0, 0, 8, 0, 14405, 0, 0, 0, 0, 0, '', NULL),
(20, 0, 14465, 0, 0, 8, 0, 14463, 0, 0, 0, 0, 0, '', NULL);

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE (`entry`='36452');
UPDATE `creature_template` SET `VehicleId`='542', `AIName`='SmartAI' WHERE (`entry`='36741');
DELETE FROM `waypoints` WHERE `entry` = 36741;
INSERT INTO `waypoints` VALUES 
(36741, 1, -1852.99, 2301.16, 41.9977, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 2, -1823.12, 2328.65, 36.7526, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 3, -1805.07, 2343.1, 35.8043, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 4, -1787.15, 2361.19, 38.3096, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 5, -1780.21, 2411.32, 51.7868, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 6, -1767.36, 2450.6, 63.4333, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 7, -1753.56, 2463.85, 69.5242, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 8, -1713.72, 2465.74, 81.9161, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 9, -1697.41, 2483.61, 91.2958, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 10, -1686.66, 2501.5, 97.1973, NULL, 0, 0, 0, 'Swift Mountain Horse'),
(36741, 11, -1669.87, 2520.1, 97.9796, NULL, 0, 0, 0, 'Swift Mountain Horse');
