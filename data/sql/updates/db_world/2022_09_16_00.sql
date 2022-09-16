UPDATE `creature_template` SET `ScriptName` = 'npc_sanitron500' WHERE `entry` = 46185;
DELETE FROM `creature_template_movement` WHERE `CreatureId` = 46185; -- Make Sanitron 500 able to Fly
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES
(46185, 1, 1, 1, 0, 0,NULL);
