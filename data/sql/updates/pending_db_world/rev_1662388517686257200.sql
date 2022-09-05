DELETE FROM `creature_template_movement` WHERE `CreatureId` IN (38038, 44794);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES
(38038, 0, 0, 0, 1, 0, 0),
(44794, 0, 0, 0, 1, 0, 0);
