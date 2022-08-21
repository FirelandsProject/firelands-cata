/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `instance_spawn_groups` (
  `instanceMapId` smallint unsigned NOT NULL,
  `bossStateId` tinyint unsigned NOT NULL,
  `bossStates` tinyint unsigned NOT NULL,
  `spawnGroupId` int unsigned NOT NULL,
  `flags` tinyint unsigned NOT NULL,
  PRIMARY KEY (`instanceMapId`,`bossStateId`,`spawnGroupId`,`bossStates`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `instance_spawn_groups`;
/*!40000 ALTER TABLE `instance_spawn_groups` DISABLE KEYS */;
INSERT INTO `instance_spawn_groups` (`instanceMapId`, `bossStateId`, `bossStates`, `spawnGroupId`, `flags`) VALUES
	(36, 4, 15, 409, 5),
	(36, 4, 15, 410, 9),
	(189, 0, 31, 453, 5),
	(189, 0, 31, 454, 9),
	(389, 0, 31, 456, 9),
	(645, 2, 8, 434, 1),
	(645, 4, 8, 452, 1),
	(657, 0, 17, 403, 1),
	(657, 0, 8, 406, 1),
	(657, 1, 17, 404, 1),
	(657, 1, 8, 407, 1),
	(657, 2, 17, 405, 1),
	(657, 2, 8, 408, 1),
	(671, 0, 17, 439, 1),
	(671, 1, 17, 440, 1),
	(671, 2, 17, 441, 1),
	(671, 3, 17, 442, 1),
	(720, 0, 17, 447, 1),
	(720, 1, 7, 457, 1),
	(720, 2, 17, 444, 1),
	(720, 3, 17, 446, 1),
	(720, 4, 17, 445, 1),
	(720, 5, 17, 448, 1),
	(720, 6, 17, 449, 1),
	(757, 2, 17, 443, 1),
	(938, 4, 17, 438, 1);
/*!40000 ALTER TABLE `instance_spawn_groups` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
