DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=36440 AND `spell_id`=68735;

INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(36440, 68735, 1, 1);

UPDATE `creature_template` SET `npcflag`=`npcflag`|16777216, `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=36440;

DELETE FROM `smart_scripts` WHERE `entryorguid`=36440 AND `source_type`=0;

DELETE FROM `smart_scripts` WHERE `entryorguid` IN (5542, 5543, 5544, 5545, 5546, 5574, 5577) AND `source_type`=2;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(36440, 0, 0, 1, 73, 0, 100, 0, 0, 0, 0, 0, 0, 85, 68735, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - On Spellclick - Cast Rescue Drowning Watchman - Invoker"),
(36440, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 47020, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Cast Ride Vehicle - Invoker"),
(36440, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 83, 16777216, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Remove spellclick Flag - self"),
(36440, 0, 3, 4, 38, 0, 100, 0, 1, 1, 0, 0, 0, 28, 68735, 0, 0, 0, 0, 0, 18, 10, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Remove Aura Rescue Drowning Watchman - player"),
(36440, 0, 4, 5, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 68730, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Remove Aura Drowning - self"),
(36440, 0, 5, 6, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Talk"),
(36440, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, 36450, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Kill credit"),
(36440, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 0, 81, 16777216, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Set spellclick Flags"),
(36440, 0, 8, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Drowning Watchman - Linked - Self: Despawn in 5000 ms"),
(5542, 2, 0, 0, 46, 0, 100, 0, 5542, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5543, 2, 0, 0, 46, 0, 100, 0, 5543, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5544, 2, 0, 0, 46, 0, 100, 0, 5544, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5545, 2, 0, 0, 46, 0, 100, 0, 5545, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5546, 2, 0, 0, 46, 0, 100, 0, 5546, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5574, 2, 0, 0, 46, 0, 100, 0, 5574, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman"),
(5577, 2, 0, 0, 46, 0, 100, 0, 5577, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 19, 36440, 10, 0, 0, 0, 0, 0, "Areatrigger - On Trigger - Set Data 1 1 - Drowning Watchman");

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (5542, 5543, 5544, 5545, 5546, 5574, 5577);

INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5542, 'SmartTrigger'),
(5543, 'SmartTrigger'),
(5544, 'SmartTrigger'),
(5545, 'SmartTrigger'),
(5546, 'SmartTrigger'),
(5574, 'SmartTrigger'),
(5577, 'SmartTrigger');

UPDATE `creature_text` SET `BroadcastTextId`=36418 WHERE `CreatureID`=36440 AND `GroupID`=0 AND `ID`=0;
UPDATE `creature_text` SET `BroadcastTextId`=36417 WHERE `CreatureID`=36440 AND `GroupID`=1 AND `ID`=0;
UPDATE `creature_text` SET `BroadcastTextId`=36419 WHERE `CreatureID`=36440 AND `GroupID`=2 AND `ID`=0;
