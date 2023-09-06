UPDATE `creature_template` SET `ScriptName`="boss_yorsahj" WHERE `entry`= 55312;
UPDATE `creature_template` SET `ScriptName`="npc_globule" WHERE `entry`IN (55862, 55863, 55864, 55865, 55866, 55867);
UPDATE `creature_template` SET `ScriptName`="npc_chosen_one" WHERE `entry`IN (56265, 57434, 57435, 57436);
UPDATE `creature_template` SET `ScriptName`="npc_mana_void" WHERE `entry`= 56231;


DELETE FROM `spell_script_names` WHERE `spell_id` IN (105420, 105435, 105436, 105437, 105439, 105440);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(105420, 'spell_summon_globule'),
(105435, 'spell_summon_globule'),
(105436, 'spell_summon_globule'),
(105437, 'spell_summon_globule'),
(105439, 'spell_summon_globule'),
(105440, 'spell_summon_globule');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (103628, 109389);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(103628, 'spell_deep_corruption'),
(109389, 'spell_deep_corruption');

DELETE FROM `spell_script_names` WHERE `spell_id` = 105539;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(105539, 'spell_mana_difussion');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (105033, 108356, 108357, 108358);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(105033, 'spell_searing_blood'),
(108356, 'spell_searing_blood'),
(108357, 'spell_searing_blood'),
(108358, 'spell_searing_blood');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (103635, 103968);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(103635, 'spell_fusing_vapors_heal'),
(103968, 'spell_fusing_vapors');

DELETE FROM `spell_script_names` WHERE `spell_id` = 105571;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(105571, 'spell_digestive_acid');

DELETE FROM `spell_script_names` WHERE `spell_id` = 105034;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(105034, 'spell_summon_manavoid');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (109894, 109895, 109896, 109897, 109898);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(109894,'spell_yorsahj_text'),
(109895,'spell_yorsahj_text'),
(109896,'spell_yorsahj_text'),
(109897,'spell_yorsahj_text'),
(109898,'spell_yorsahj_text');

UPDATE `achievement_criteria_data` SET `ScriptName`="achievement_taste_the_rainbow_1" WHERE `criteria_id` = 18495;
UPDATE `achievement_criteria_data` SET `ScriptName`="achievement_taste_the_rainbow_2" WHERE `criteria_id` = 18496;
UPDATE `achievement_criteria_data` SET `ScriptName`="achievement_taste_the_rainbow_3" WHERE `criteria_id` = 18497;
UPDATE `achievement_criteria_data` SET `ScriptName`="achievement_taste_the_rainbow_4" WHERE `criteria_id` = 18498;
