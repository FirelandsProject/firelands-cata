/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `lfg_dungeon_rewards` (
  `dungeonId` int unsigned NOT NULL DEFAULT '0' COMMENT 'Dungeon entry from dbc',
  `maxLevel` tinyint unsigned NOT NULL DEFAULT '0' COMMENT 'Max level at which this reward is rewarded',
  `firstQuestId` int unsigned NOT NULL DEFAULT '0' COMMENT 'Quest id with rewards for first dungeon this day',
  `otherQuestId` int unsigned NOT NULL DEFAULT '0' COMMENT 'Quest id with rewards for Nth dungeon this day',
  `shortageQuestId` int unsigned DEFAULT '0' COMMENT 'Quest ID with rewards for joining a random dungeon queue while the role is short on supply',
  `completionsPerPeriod` tinyint unsigned DEFAULT '0' COMMENT 'Maximum amount that the first quest may be rewarded',
  `dailyReset` tinyint unsigned DEFAULT '0' COMMENT 'Indicator for resetting rewards daily or weekly',
  PRIMARY KEY (`dungeonId`,`maxLevel`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `lfg_dungeon_rewards`;
/*!40000 ALTER TABLE `lfg_dungeon_rewards` DISABLE KEYS */;
INSERT INTO `lfg_dungeon_rewards` (`dungeonId`, `maxLevel`, `firstQuestId`, `otherQuestId`, `shortageQuestId`, `completionsPerPeriod`, `dailyReset`) VALUES
	(258, 15, 24881, 24889, 0, 7, 0),
	(258, 25, 24882, 24890, 0, 7, 0),
	(258, 34, 24883, 24891, 0, 7, 0),
	(258, 45, 24884, 24892, 0, 7, 0),
	(258, 55, 24885, 24893, 0, 7, 0),
	(258, 60, 24886, 24894, 0, 7, 0),
	(259, 64, 24887, 24895, 0, 7, 0),
	(259, 70, 24888, 24896, 0, 7, 0),
	(260, 70, 24922, 24923, 0, 7, 0),
	(261, 80, 24790, 24791, 0, 7, 0),
	(262, 80, 24788, 24789, 0, 7, 0),
	(285, 80, 25482, 0, 0, 1, 1),
	(286, 80, 25484, 0, 0, 1, 1),
	(287, 80, 25483, 0, 0, 1, 1),
	(288, 80, 25485, 0, 0, 1, 1),
	(300, 85, 28907, 28908, 0, 7, 0),
	(301, 85, 28905, 28906, 29339, 0, 0),
	(416, 85, 30110, 30111, 0, 1, 0),
	(417, 85, 30110, 30111, 0, 1, 0),
	(434, 85, 29185, 29183, 29339, 0, 0);
/*!40000 ALTER TABLE `lfg_dungeon_rewards` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
