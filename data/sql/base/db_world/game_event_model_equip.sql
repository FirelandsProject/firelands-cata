/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `game_event_model_equip` (
  `eventEntry` tinyint NOT NULL COMMENT 'Entry of the game event.',
  `guid` int unsigned NOT NULL DEFAULT '0',
  `modelid` int unsigned NOT NULL DEFAULT '0',
  `equipment_id` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `game_event_model_equip`;
/*!40000 ALTER TABLE `game_event_model_equip` DISABLE KEYS */;
INSERT INTO `game_event_model_equip` (`eventEntry`, `guid`, `modelid`, `equipment_id`) VALUES
	(25, 307151, 0, 2),
	(25, 313764, 0, 2),
	(25, 313836, 0, 2),
	(25, 313928, 0, 2),
	(25, 314015, 0, 2),
	(25, 314048, 0, 2),
	(25, 314065, 0, 2),
	(25, 314069, 0, 2),
	(25, 314087, 0, 2),
	(25, 314119, 0, 2),
	(25, 314174, 0, 2),
	(25, 314219, 0, 2),
	(25, 314253, 0, 2),
	(25, 314331, 0, 2),
	(25, 314333, 0, 2),
	(25, 314338, 0, 2),
	(25, 314421, 0, 2),
	(25, 314481, 0, 2),
	(25, 314625, 0, 2),
	(25, 314630, 0, 2),
	(25, 314635, 0, 2),
	(25, 326106, 0, 2);
/*!40000 ALTER TABLE `game_event_model_equip` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
