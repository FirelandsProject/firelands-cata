DELETE FROM `creature_template_movement` WHERE `CreatureId` in (50372,49044,49128);
INSERT INTO `creature_template_movement` (`CreatureId`, `Ground`, `Swim`, `Flight`, `Rooted`, `Random`, `InteractionPauseTimer`) VALUES 
(50372, 0, 0, 1, 0, 0, NULL),
(49044, 0, 0, 1, 0, 0, NULL),
(49128, 0, 0, 1, 0, 0, NULL);