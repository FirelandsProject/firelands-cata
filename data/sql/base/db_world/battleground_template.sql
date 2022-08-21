/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `battleground_template` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `MinPlayersPerTeam` smallint unsigned NOT NULL DEFAULT '0',
  `MaxPlayersPerTeam` smallint unsigned NOT NULL DEFAULT '0',
  `MinLvl` tinyint unsigned NOT NULL DEFAULT '0',
  `MaxLvl` tinyint unsigned NOT NULL DEFAULT '0',
  `AllianceStartLoc` int unsigned NOT NULL,
  `AllianceStartO` float NOT NULL,
  `HordeStartLoc` int unsigned NOT NULL,
  `HordeStartO` float NOT NULL,
  `StartMaxDist` float NOT NULL DEFAULT '0',
  `Weight` tinyint unsigned NOT NULL DEFAULT '1',
  `ScriptName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `Comment` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `battleground_template`;
/*!40000 ALTER TABLE `battleground_template` DISABLE KEYS */;
INSERT INTO `battleground_template` (`ID`, `MinPlayersPerTeam`, `MaxPlayersPerTeam`, `MinLvl`, `MaxLvl`, `AllianceStartLoc`, `AllianceStartO`, `HordeStartLoc`, `HordeStartO`, `StartMaxDist`, `Weight`, `ScriptName`, `Comment`) VALUES
	(1, 10, 40, 45, 85, 611, 3.16312, 610, 0.715504, 100, 1, '', 'Alterac Valley'),
	(2, 5, 10, 10, 85, 769, 3.14159, 770, 0.151581, 75, 1, '', 'Warsong Gulch'),
	(3, 8, 15, 10, 85, 890, 3.91571, 889, 0.813671, 75, 1, '', 'Arathi Basin'),
	(4, 0, 5, 10, 85, 929, 0, 936, 3.14159, 0, 1, '', 'Nagrand Arena'),
	(5, 0, 5, 10, 85, 939, 0, 940, 3.14159, 0, 1, '', 'Blades\'s Edge Arena'),
	(6, 0, 5, 10, 85, 0, 0, 0, 0, 0, 1, '', 'All Arena'),
	(7, 8, 15, 35, 85, 1103, 3.03123, 1104, 0.055761, 75, 1, '', 'Eye of The Storm'),
	(8, 0, 5, 10, 85, 1258, 0, 1259, 3.14159, 0, 1, '', 'Ruins of Lordaeron'),
	(9, 8, 15, 65, 85, 1367, 0, 1368, 0, 0, 1, '', 'Strand of the Ancients'),
	(10, 0, 5, 10, 85, 1362, 0, 1363, 3.14159, 0, 1, '', 'Dalaran Sewers'),
	(11, 0, 5, 10, 85, 1364, 0, 1365, 0, 0, 1, '', 'The Ring of Valor'),
	(30, 10, 40, 71, 85, 1485, 0, 1486, 3.16124, 200, 1, '', 'Isle of Conquest'),
	(32, 5, 40, 45, 85, 0, 0, 0, 0, 0, 1, '', 'Random battleground'),
	(108, 5, 10, 75, 85, 1726, 0, 1727, 0, 75, 1, '', 'Twin Peaks'),
	(120, 5, 10, 75, 85, 1798, 0, 1799, 0, 75, 1, '', 'The Battle for Gilneas');
/*!40000 ALTER TABLE `battleground_template` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
