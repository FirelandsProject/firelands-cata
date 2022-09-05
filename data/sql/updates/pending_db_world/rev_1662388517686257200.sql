DELETE FROM `creature_template_movement` WHERE `CreatureId` IN (38038, 44794);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES
(38038, NULL, NULL, NULL, 1, NULL, NULL),
(44794, NULL, NULL, NULL, 1, NULL, NULL);

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid`=251604;

DELETE FROM `creature_template_addon` WHERE `entry`=38038;
INSERT INTO `creature_template_addon` (`entry`, `waypointPathId`, `cyclicSplinePathId`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(38038, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, '71065 83470');
