/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `game_weather` (
  `zone` int unsigned NOT NULL DEFAULT '0',
  `spring_rain_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `spring_snow_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `spring_storm_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `summer_rain_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `summer_snow_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `summer_storm_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `fall_rain_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `fall_snow_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `fall_storm_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `winter_rain_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `winter_snow_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `winter_storm_chance` tinyint unsigned NOT NULL DEFAULT '25',
  `ScriptName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`zone`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Weather System';

DELETE FROM `game_weather`;
/*!40000 ALTER TABLE `game_weather` DISABLE KEYS */;
INSERT INTO `game_weather` (`zone`, `spring_rain_chance`, `spring_snow_chance`, `spring_storm_chance`, `summer_rain_chance`, `summer_snow_chance`, `summer_storm_chance`, `fall_rain_chance`, `fall_snow_chance`, `fall_storm_chance`, `winter_rain_chance`, `winter_snow_chance`, `winter_storm_chance`, `ScriptName`) VALUES
	(1, 0, 25, 0, 0, 15, 0, 0, 25, 0, 0, 25, 0, ''),
	(3, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 15, ''),
	(10, 15, 0, 0, 15, 0, 0, 20, 0, 0, 15, 0, 0, ''),
	(11, 25, 0, 0, 15, 0, 0, 25, 0, 0, 25, 0, 0, ''),
	(12, 20, 0, 0, 15, 0, 0, 20, 0, 0, 20, 0, 0, ''),
	(15, 25, 0, 0, 20, 0, 0, 25, 0, 0, 25, 0, 0, ''),
	(28, 10, 0, 0, 15, 0, 0, 15, 0, 0, 10, 0, 0, ''),
	(33, 20, 0, 0, 25, 0, 0, 25, 0, 0, 20, 0, 0, ''),
	(36, 0, 20, 0, 0, 20, 0, 0, 25, 0, 0, 30, 0, ''),
	(38, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(41, 15, 0, 0, 5, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(44, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(45, 23, 0, 0, 15, 0, 0, 23, 0, 0, 23, 0, 0, ''),
	(47, 10, 0, 0, 10, 0, 0, 15, 0, 0, 10, 0, 0, ''),
	(85, 20, 0, 0, 15, 0, 0, 20, 0, 0, 20, 0, 0, ''),
	(139, 10, 0, 0, 15, 0, 0, 15, 0, 0, 10, 0, 0, ''),
	(141, 15, 0, 0, 5, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(148, 15, 0, 0, 10, 0, 0, 20, 0, 0, 15, 0, 0, ''),
	(215, 15, 0, 0, 10, 0, 0, 20, 0, 0, 15, 0, 0, ''),
	(267, 15, 0, 0, 10, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(357, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(405, 10, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, ''),
	(440, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, ''),
	(490, 15, 0, 0, 10, 0, 0, 20, 0, 0, 15, 0, 0, ''),
	(618, 0, 25, 0, 0, 20, 0, 0, 20, 0, 0, 25, 0, ''),
	(796, 5, 0, 0, 10, 0, 0, 25, 0, 0, 5, 0, 0, ''),
	(1377, 0, 0, 20, 0, 0, 25, 0, 0, 20, 0, 0, 15, ''),
	(1977, 15, 0, 0, 5, 0, 0, 15, 0, 0, 15, 0, 0, ''),
	(2017, 5, 0, 0, 5, 0, 0, 5, 0, 0, 5, 0, 0, ''),
	(2597, 0, 15, 0, 0, 15, 0, 0, 20, 0, 0, 25, 0, ''),
	(3358, 10, 0, 0, 10, 0, 0, 10, 0, 0, 10, 0, 0, ''),
	(3428, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, ''),
	(3429, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, ''),
	(3521, 10, 0, 0, 15, 0, 0, 20, 0, 0, 10, 0, 0, ''),
	(4080, 20, 0, 0, 20, 0, 0, 20, 0, 0, 10, 0, 0, '');
/*!40000 ALTER TABLE `game_weather` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
