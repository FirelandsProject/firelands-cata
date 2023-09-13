--
UPDATE `creature_template` SET `flags_extra`='16777218' WHERE `entry` IN (17469,17211,21748,21664,21750,21683,21747,21682,21726,21160,21752,21684);
UPDATE `creature_template` SET `ScriptName` = "npc_chesspiece" WHERE `entry` IN (17469,17211,21748,21664,21750,21683,21747,21682,21726,21160,21752,21684);
UPDATE `creature_template` SET `ScriptName` = "npc_echo_of_medivh" WHERE `entry`=16816;
UPDATE `creature_template` SET `ScriptName` = "npc_chess_move_trigger", `flags_extra`=130 WHERE `entry`=22519;

DELETE FROM `spell_script_names` WHERE `spell_id`=30019;
INSERT INTO `spell_script_names` VALUES
(30019,'spell_control_piece');
