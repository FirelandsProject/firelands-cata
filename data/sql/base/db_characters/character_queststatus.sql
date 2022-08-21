/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `character_queststatus` (
  `guid` int unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `quest` int unsigned NOT NULL DEFAULT '0' COMMENT 'Quest Identifier',
  `status` tinyint unsigned NOT NULL DEFAULT '0',
  `explored` tinyint unsigned NOT NULL DEFAULT '0',
  `timer` int unsigned NOT NULL DEFAULT '0',
  `mobcount1` smallint unsigned NOT NULL DEFAULT '0',
  `mobcount2` smallint unsigned NOT NULL DEFAULT '0',
  `mobcount3` smallint unsigned NOT NULL DEFAULT '0',
  `mobcount4` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount1` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount2` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount3` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount4` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount5` smallint unsigned NOT NULL DEFAULT '0',
  `itemcount6` smallint unsigned NOT NULL DEFAULT '0',
  `playercount` smallint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`,`quest`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Player System';

DELETE FROM `character_queststatus`;
/*!40000 ALTER TABLE `character_queststatus` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_queststatus` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
