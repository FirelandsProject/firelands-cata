UPDATE `creature_template` SET `ScriptName` = "boss_morchok" WHERE `entry`=55265;
UPDATE `creature_template` SET `ScriptName` = "boss_kohcrom" WHERE `entry`=57773;
UPDATE `creature_template` SET `ScriptName` = "npc_ds_earthen_vortex_vehicle" WHERE `entry`=55723;

DELETE FROM `spell_script_names` WHERE `spell_id` IN (103528, 104573, 103494, 103545, 108572, 110040, 110041, 103176, 103821, 110045, 110046, 110047, 103851, 103785, 108570, 110287, 110288);

INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(103528, 'spell_ds_target_selection'),
(104573, 'spell_ds_target_selection'),
(103494, 'spell_ds_resonating_crystal_periodic'),
(103545, 'spell_ds_resonating_crystal_explosion'),
(108572, 'spell_ds_resonating_crystal_explosion'),
(110040, 'spell_ds_resonating_crystal_explosion'),
(110041, 'spell_ds_resonating_crystal_explosion'),
(103176, 'spell_ds_falling_fragments_periodic'),
(103821, 'spell_ds_earthen_vortex_teleport'),
(110045, 'spell_ds_earthen_vortex_teleport'),
(110046, 'spell_ds_earthen_vortex_teleport'),
(110047, 'spell_ds_earthen_vortex_teleport'),
(103851, 'spell_ds_black_blood_of_the_earth_periodic'),
(103785, 'spell_ds_black_blood_of_the_earth_damage'),
(108570, 'spell_ds_black_blood_of_the_earth_damage'),
(110287, 'spell_ds_black_blood_of_the_earth_damage'),
(110288, 'spell_ds_black_blood_of_the_earth_damage');