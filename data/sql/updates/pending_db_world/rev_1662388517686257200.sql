DELETE FROM `creature_template_movement` WHERE `CreatureId` IN (38038, 44614, 44794, 48304);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES
(38038, NULL, NULL, NULL, 1, NULL, NULL),
(44614, NULL, NULL, NULL, 1, NULL, NULL),
(44794, NULL, NULL, NULL, 1, NULL, NULL),
(48304, NULL, NULL, NULL, 1, NULL, NULL);

UPDATE `creature` SET `spawndist`=0, `MovementType`=0 WHERE `guid`=251604;

DELETE FROM `creature_template_addon` WHERE `entry`=38038;
INSERT INTO `creature_template_addon` (`entry`, `waypointPathId`, `cyclicSplinePathId`, `mount`, `bytes1`, `bytes2`, `emote`, `aiAnimKit`, `movementAnimKit`, `meleeAnimKit`, `visibilityDistanceType`, `auras`) VALUES
(38038, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, '71065 83470');

UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|32, `flags_extra`=`flags_extra`|262144, `AIName`='SmartAI', `ScriptName`='' WHERE `entry` IN (38038, 44614, 44794, 48304);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (38038, 44614, 44794, 48304) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(38038, 0, 0, 0, 8, 0, 100, 512, 100, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 100 - Credit kill"),
(38038, 0, 1, 0, 8, 0, 100, 512, 20271, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 20271 - Credit kill"),
(38038, 0, 2, 0, 8, 0, 100, 512, 56641, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 56641 - Credit kill"),
(38038, 0, 3, 0, 8, 0, 100, 512, 2098, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 2098 - Credit kill"),
(38038, 0, 4, 0, 8, 0, 100, 512, 73899, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 73899 - Credit kill"),
(38038, 0, 5, 0, 8, 0, 100, 512, 348, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 348 - Credit kill"),
(38038, 0, 6, 0, 8, 0, 100, 512, 5143, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On spell hit 5143 - Credit kill"),
(38038, 0, 7, 0, 6, 0, 100, 512, 0, 0, 0, 0, 0, 41, 1000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Tiki Target - On Death - Despawn"),
(44614, 0, 0, 0, 8, 0, 100, 512, 5143, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44614, 0, 1, 0, 8, 0, 100, 512, 100, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44614, 0, 2, 0, 8, 0, 100, 512, 2098, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44614, 0, 3, 0, 8, 0, 100, 512, 56641, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44614, 0, 4, 0, 8, 0, 100, 512, 348, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44794, 0, 0, 0, 8, 0, 100, 512, 5143, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44794, 0, 1, 0, 8, 0, 100, 512, 100, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44794, 0, 2, 0, 8, 0, 100, 512, 2098, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44794, 0, 3, 0, 8, 0, 100, 512, 56641, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(44794, 0, 4, 0, 8, 0, 100, 512, 348, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(48304, 0, 0, 0, 8, 0, 100, 512, 5143, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(48304, 0, 1, 0, 8, 0, 100, 512, 100, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(48304, 0, 2, 0, 8, 0, 100, 512, 2098, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(48304, 0, 3, 0, 8, 0, 100, 512, 56641, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill"),
(48304, 0, 4, 0, 8, 0, 100, 512, 348, 0, 0, 0, 0, 33, 44175, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Training Dummy - On spell hit - Credit kill");
