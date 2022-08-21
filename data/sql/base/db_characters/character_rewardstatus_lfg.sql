/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `character_rewardstatus_lfg` (
  `guid` int NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `dungeonId` smallint NOT NULL DEFAULT '0' COMMENT 'Dungeon ID Identifier',
  `rewardCount` tinyint unsigned DEFAULT '0' COMMENT 'Dungeon First Reward Count Identifier',
  `dailyReset` tinyint unsigned DEFAULT '0' COMMENT 'Reward Count Daily Reset Identifier'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `character_rewardstatus_lfg`;
/*!40000 ALTER TABLE `character_rewardstatus_lfg` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_rewardstatus_lfg` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
