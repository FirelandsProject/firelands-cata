DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=29528;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(13, 1, 29528, 0, 0, 31, 0, 3, 16518, 0, 0, 'Inoculate Nestlewood Owlkin - Implicit target - Nestlewood Owlkin');

DELETE FROM `smart_scripts` WHERE `entryorguid`=16518 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(16518, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Reset - Set phase 1"),
(16518, 0, 1, 0, 8, 1, 100, 0, 29528, 0, 3000, 3000, 0, 22, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Spellhit - Set phase 2"),
(16518, 0, 2, 0, 23, 2, 100, 1, 29528, 0, 0, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Missing aura - Set phase 1"),
(16518, 0, 3, 4, 1, 2, 100, 1, 2900, 2900,  0, 0, 0, 22, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Set phase 3 (see conditions)"),
(16518, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Face invoker"),
(16518, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Despawn in 5 seconds"),
(16518, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 0, 36, 16534, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Update template"),
(16518, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Say text"),
(16518, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, 16534, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Nestlewood Owlkin - Update OOC - Give credit");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`=16518 AND `SourceId`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `Comment`) VALUES
(22, 4, 16518, 0, 0, 1, 1, 29528, 0, 0, 0,'Nestlewood Owlkin - Activate SAI if object has aura');

UPDATE `creature` SET `spawntimesecs`=90 WHERE `id`=16518;
