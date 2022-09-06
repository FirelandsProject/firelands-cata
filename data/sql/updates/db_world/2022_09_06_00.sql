DELETE FROM `phase_area` WHERE `AreaId`=4806 AND `PhaseId`=181;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES 
(4806, 181, 'Phase for quest 14400');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `SourceGroup`=181 AND `SourceEntry`=4806 AND `SourceId`=0 AND `ElseGroup`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(26, 181, 4806, 0, 0, 9, 0, 14400, 0, 0, 0, 0, 0, '', 'Phase only if quest 14400 is taken');
