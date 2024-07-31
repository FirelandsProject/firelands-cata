DELETE FROM `areatrigger_scripts` WHERE `ScriptName`= 'at_sb_razorfen_kraul_entrance';
INSERT INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(6348, 'at_sb_razorfen_kraul_entrance');

DELETE FROM `firelands_string` WHERE `entry` IN (11022, 11023);
INSERT INTO `firelands_string` (`entry`, `content_default`) VALUES
  (11022, 'LFG is set to 1 player queue for debugging.'),
  (11023, 'LFG is set to normal queue.');

  DELETE FROM `command` WHERE `name` = 'debug lfg';
INSERT INTO `command` (`name`, `permission`, `help`) VALUES
  ('debug lfg', 300, 'Syntax: .debug lfg\r\nToggle debug mode for lfg. In debug mode GM can start lfg queue with one player.');