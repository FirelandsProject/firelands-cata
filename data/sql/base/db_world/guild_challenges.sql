/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `guild_challenges` (
  `ChallengeType` int unsigned NOT NULL DEFAULT '0',
  `ChallengeCount` int unsigned DEFAULT '1',
  `Experience` int unsigned DEFAULT '0',
  `Gold` int unsigned DEFAULT '0',
  `GoldMaxLevel` int unsigned DEFAULT '0',
  PRIMARY KEY (`ChallengeType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `guild_challenges`;
/*!40000 ALTER TABLE `guild_challenges` DISABLE KEYS */;
INSERT INTO `guild_challenges` (`ChallengeType`, `ChallengeCount`, `Experience`, `Gold`, `GoldMaxLevel`) VALUES
	(0, 0, 0, 0, 0),
	(1, 7, 300000, 125, 250),
	(2, 1, 3000000, 500, 1000),
	(3, 3, 1500000, 250, 500);
/*!40000 ALTER TABLE `guild_challenges` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
