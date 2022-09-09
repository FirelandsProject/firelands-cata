DELETE FROM `creature_template_movement` WHERE `CreatureId` IN (50372, 49044, 49128);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES 
(50372, NULL, NULL, 1, NULL, NULL, NULL),
(49044, NULL, NULL, 1, NULL, NULL, NULL),
(49128, NULL, NULL, 1, NULL, NULL, NULL);
