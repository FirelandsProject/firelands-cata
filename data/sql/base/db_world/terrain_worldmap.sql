/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `terrain_worldmap` (
  `TerrainSwapMap` int unsigned NOT NULL,
  `WorldMapArea` int unsigned NOT NULL,
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`TerrainSwapMap`,`WorldMapArea`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `terrain_worldmap`;
/*!40000 ALTER TABLE `terrain_worldmap` DISABLE KEYS */;
INSERT INTO `terrain_worldmap` (`TerrainSwapMap`, `WorldMapArea`, `Comment`) VALUES
	(638, 545, 'Gilneas'),
	(655, 678, 'Gilneas_terrain1'),
	(656, 679, 'Gilneas_terrain2'),
	(719, 683, 'Hyjal_terrain1');
/*!40000 ALTER TABLE `terrain_worldmap` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
