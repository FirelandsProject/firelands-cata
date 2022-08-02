UPDATE `firelands_string` SET `content_default`='│ Phases: %s' WHERE `entry`=846;
DELETE FROM `firelands_string` WHERE `entry`=5083;
INSERT INTO `firelands_string` (`entry`,`content_default`) VALUES
(5083,"Uses invalid phaseID.");
