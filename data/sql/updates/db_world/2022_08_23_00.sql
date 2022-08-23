UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry` IN (36698, 36797, 36798);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (36698, 36797, 36798) AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(36698, 0, 0, 0, 25, 0, 100, 512, 0, 0, 0, 0, 0, 3, 0, 30295, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Captive Worgen - On Reset - Morph To Model 30295"),
(36797, 0, 0, 0, 25, 0, 100, 512, 0, 0, 0, 0, 0, 3, 0, 30295, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Captive Worgen - On Reset - Morph To Model 30295"),
(36798, 0, 0, 0, 25, 0, 100, 512, 0, 0, 0, 0, 0, 3, 0, 30295, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Captive Worgen - On Reset - Morph To Model 30295");
