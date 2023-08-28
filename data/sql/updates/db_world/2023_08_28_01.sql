-- Condition is invalid and was never process and is ignored by world server
DELETE FROM `conditions` WHERE  `SourceTypeOrReferenceId`=13 AND `SourceGroup`=1 AND `SourceEntry`=29528 AND `SourceId`=0 AND `ElseGroup`=0 AND `ConditionTypeOrReference`=31 AND `ConditionTarget`=0 AND `ConditionValue1`=3 AND `ConditionValue2`=16518 AND `ConditionValue3`=0;

-- scripted spell not assigned in the database
DELETE FROM `spell_script_names` WHERE `spell_id`=-11327 AND `ScriptName`='spell_rog_vanish';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (-11327, 'spell_rog_vanish');
