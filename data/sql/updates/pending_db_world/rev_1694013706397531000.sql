UPDATE `creature_template` SET `ScriptName`="boss_yorsahj" WHERE `entry`= 55312;
UPDATE `creature_template` SET `ScriptName`="npc_globule" WHERE `entry`IN (55862, 55863, 55864, 55865, 55866, 55867);
UPDATE `creature_template` SET `ScriptName`="npc_chosen_one" WHERE `entry`IN (56265, 57434, 57435, 57436);
UPDATE `creature_template` SET `ScriptName`="npc_mana_void" WHERE `entry`= 56231;
UPDATE `creature_template` SET `unit_flags`=33554560, `flags_extra`=130 WHERE `entry`=55346;


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

DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (18495, 18496, 18497, 18498);
INSERT INTO `achievement_criteria_data` (`criteria_id`, `type`, `value1`, `value2`, `ScriptName`) VALUES 
(18495, 11, 0, 0, 'achievement_taste_the_rainbow_1'),
(18496, 11, 0, 0, 'achievement_taste_the_rainbow_2'),
(18497, 11, 0, 0, 'achievement_taste_the_rainbow_3'),
(18498, 11, 0, 0, 'achievement_taste_the_rainbow_4');

DELETE FROM `creature_text` WHERE `CreatureID` = 55265;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `Comment`, `BroadcastTextId`) VALUES
(55265, 0, 0, 'No mortal shall turn me from my task.', 14, 0, 100, 0, 0, 0, 'Morchok - Group One', 56455),
(55265, 1, 0, 'Cowards. Weaklings. Come down and fight, or I will bring you down.', 14, 0, 100, 0, 0, 0, 'Morchok - Group One 2', 56475),
(55265, 2, 0, 'You cannot hide in this temple forever, Shaman.', 14, 0, 100, 0, 0, 0, 'Morchok - Group Two 1', 56476),
(55265, 2, 1, 'Wyrmrest will fall. All will be dust.', 14, 0, 100, 0, 0, 0, 'Morchok - Group Two 1', 56478),
(55265, 3, 0, 'I will turn this tower to rubble, and scatter it across the wastes.', 14, 0, 100, 0, 0, 0, 'Morchok - Group Two 2', 56477),
(55265, 4, 0, 'You seek to halt an avalanche. I will bury you.', 14, 0, 100, 0, 0, 0, 'Morchok - Aggro', 56456),
(55265, 5, 0, 'You thought to fight me alone?', 14, 0, 100, 0, 0, 0, 'Morchok - Summon Kohcrom', 56457),
(55265, 6, 0, 'Flee, and die.', 14, 0, 100, 0, 0, 0, 'Morchok - Summon Resonating Crystal', 56471),
(55265, 6, 1, 'Run, and perish.', 14, 0, 100, 0, 0, 0, 'Morchok - Summon Resonating Crystal', 56472),
(55265, 7, 0, 'The stone calls...', 14, 0, 100, 0, 0, 0, 'Morchok - Earthen Vortex', 56462),
(55265, 7, 1, 'The ground shakes...', 14, 0, 100, 0, 0, 0, 'Morchok - Earthen Vortex', 56463),
(55265, 7, 2, 'The rocks tremble...', 14, 0, 100, 0, 0, 0, 'Morchok - Earthen Vortex', 56465),
(55265, 7, 3, 'The surface quakes...', 14, 0, 100, 0, 0, 0, 'Morchok - Earthen Vortex', 56466),
(55265, 8, 0, '...and the black blood of the earth consumes you.', 14, 0, 100, 0, 0, 0, 'Morchok - Black Blood of the Earth', 56467),
(55265, 8, 1, '...and there is no escape from the Old Gods.', 14, 0, 100, 0, 0, 0, 'Morchok - Black Blood of the Earth', 56468),
(55265, 8, 2, '...and the rage of the true gods follows.', 14, 0, 100, 0, 0, 0, 'Morchok - Black Blood of the Earth', 56469),
(55265, 8, 3, '...and you drown in the hate of The Master.', 14, 0, 100, 0, 0, 0, 'Morchok - Black Blood of the Earth', 56470),
(55265, 9, 0, 'I am unstoppable.', 14, 0, 100, 0, 0, 0, 'Morchok - Killing a player', 56459),
(55265, 9, 1, 'It was inevitable.', 14, 0, 100, 0, 0, 0, 'Morchok - Killing a player', 56460),
(55265, 9, 2, 'Ground to dust.', 14, 0, 100, 0, 0, 0, 'Morchok - Killing a player', 56461),
(55265, 10, 0, 'Impossible. This cannot be. The tower... must... fall...', 14, 0, 100, 0, 0, 0, 'Morchok - Death', 56458);

UPDATE `creature_template` SET `ScriptName` ="boss_dw_spine" WHERE `entry` = 53879;
UPDATE `creature_template` SET `ScriptName` ="npc_dw_corruption" WHERE `entry` IN (53891, 56161, 56162);
UPDATE `creature_template` SET `ScriptName` ="npc_hideous_amalgamation" WHERE `entry` = 53890;
UPDATE `creature_template` SET `ScriptName` ="npc_corrupted_blood" WHERE `entry` = 53889;
UPDATE `creature_template` SET `ScriptName` ="npc_burning_tendon" WHERE `entry` IN (56341, 56575);
UPDATE `creature_template` SET `ScriptName` ="npc_spine_spawner" WHERE `entry` = 53888;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (109022, 105241, 105248, 109379, 105845, 105846, 104621, 105740, 105847, 105848, 106199, 106200, 109083);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(109022, 'spell_dw_spine_check_player'),
(105241, 'spell_absorb_blood'),
(105248, 'spell_absorb_blood_aura'),
(109379, 'spell_searing_plasma'),
(105845, 'spell_nuclear_blast'),
(105846, 'spell_nuclear_blast_triggered'),
(104621, 'spell_dw_spine_roll_control'),
(105740, 'spell_dw_spine_roll_control_roll'),
(105847, 'spell_seal_armor_breach'),
(105848, 'spell_seal_armor_breach'),
(106199, 'spell_blood_corruption_aura'),
(106200, 'spell_blood_corruption_aura'),
(106199, 'spell_blood_corruption_spell'),
(106200, 'spell_blood_corruption_spell'),
(109083, 'spell_energize_spine');
