/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `reputation_reward_rate` (
  `faction` int unsigned NOT NULL DEFAULT '0',
  `quest_rate` float NOT NULL DEFAULT '1',
  `quest_daily_rate` float NOT NULL DEFAULT '1',
  `quest_weekly_rate` float NOT NULL DEFAULT '1',
  `quest_monthly_rate` float NOT NULL DEFAULT '1',
  `quest_repeatable_rate` float NOT NULL DEFAULT '1',
  `creature_rate` float NOT NULL DEFAULT '1',
  `spell_rate` float NOT NULL DEFAULT '1',
  PRIMARY KEY (`faction`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `reputation_reward_rate`;
/*!40000 ALTER TABLE `reputation_reward_rate` DISABLE KEYS */;
INSERT INTO `reputation_reward_rate` (`faction`, `quest_rate`, `quest_daily_rate`, `quest_weekly_rate`, `quest_monthly_rate`, `quest_repeatable_rate`, `creature_rate`, `spell_rate`) VALUES
	(529, 1, 1, 1, 1, 1, 1, 2),
	(576, 4, 1, 1, 1, 4, 1, 1),
	(609, 1, 1, 1, 1, 1, 1, 2),
	(941, 2, 1, 1, 1, 1, 1, 1),
	(970, 1, 1, 1, 1, 3, 1, 3),
	(978, 2, 1, 1, 1, 1, 1, 1),
	(1037, 1.3, 1.3, 1.3, 1.3, 1.3, 1, 1),
	(1052, 1.3, 1.3, 1.3, 1.3, 1.3, 1, 1),
	(1073, 1, 2, 1, 1, 1, 2, 2),
	(1090, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3),
	(1091, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3),
	(1098, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3),
	(1104, 1, 2, 1, 1, 1, 2, 2),
	(1105, 1, 2, 1, 1, 1, 2, 2),
	(1106, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3, 1.3),
	(1119, 1, 1, 1, 1, 1, 1.3, 1.3);
/*!40000 ALTER TABLE `reputation_reward_rate` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
