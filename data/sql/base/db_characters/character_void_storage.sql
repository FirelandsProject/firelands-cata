/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `character_void_storage` (
  `itemId` bigint unsigned NOT NULL,
  `playerGuid` int unsigned NOT NULL,
  `itemEntry` int unsigned NOT NULL,
  `slot` tinyint unsigned NOT NULL,
  `creatorGuid` int unsigned NOT NULL DEFAULT '0',
  `randomPropertyType` tinyint unsigned NOT NULL DEFAULT '0',
  `randomProperty` int unsigned NOT NULL DEFAULT '0',
  `suffixFactor` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`itemId`),
  UNIQUE KEY `idx_player_slot` (`playerGuid`,`slot`),
  KEY `idx_player` (`playerGuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `character_void_storage`;
/*!40000 ALTER TABLE `character_void_storage` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_void_storage` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
