/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `pvpstats_players` (
  `battleground_id` bigint unsigned NOT NULL,
  `character_guid` int unsigned NOT NULL,
  `winner` bit(1) NOT NULL,
  `score_killing_blows` int unsigned NOT NULL,
  `score_deaths` int unsigned NOT NULL,
  `score_honorable_kills` int unsigned NOT NULL,
  `score_bonus_honor` int unsigned NOT NULL,
  `score_damage_done` int unsigned NOT NULL,
  `score_healing_done` int unsigned NOT NULL,
  `attr_1` int unsigned NOT NULL DEFAULT '0',
  `attr_2` int unsigned NOT NULL DEFAULT '0',
  `attr_3` int unsigned NOT NULL DEFAULT '0',
  `attr_4` int unsigned NOT NULL DEFAULT '0',
  `attr_5` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`battleground_id`,`character_guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `pvpstats_players`;
/*!40000 ALTER TABLE `pvpstats_players` DISABLE KEYS */;
/*!40000 ALTER TABLE `pvpstats_players` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
