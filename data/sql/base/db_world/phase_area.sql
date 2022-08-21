/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `phase_area` (
  `AreaId` int unsigned NOT NULL,
  `PhaseId` int unsigned NOT NULL,
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`AreaId`,`PhaseId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `phase_area`;
/*!40000 ALTER TABLE `phase_area` DISABLE KEYS */;
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
	(108, 226, 'Sentinel Hill - Rise of the Brotherhood'),
	(4714, 105, 'Gilneas - Phase 105'),
	(4861, 194, 'Mount Hyjal - The Regrowth - Phase 194'),
	(4979, 195, 'Mount Hyjal - Shrine of Goldrinn - Phase 195'),
	(4989, 194, 'Mount Hyjal - Grove of Aessina - Phase 194'),
	(4990, 194, 'Mount Hyjal - Shrine of Aviana - Phase 194'),
	(5013, 194, 'Mount Hyjal - Blackhorn\'s Penance - Phase 194'),
	(5014, 194, 'Mount Hyjal - The Inferno - Phase 194'),
	(5016, 194, 'Mount Hyjal - Whistling Grove - Phase 194'),
	(5018, 194, 'Mount Hyjal - Ashen Lake - Phase 194'),
	(5019, 194, 'Mount Hyjal - Sanctuary of Malorne - Phase 194'),
	(5020, 194, 'Mount Hyjal - The Flamewake - Phase 194'),
	(5022, 194, 'Mount Hyjal - Rim of the World - Phase 194'),
	(5140, 169, 'Highbank phase after quest 28598 complete'),
	(5140, 361, 'Highbank phase before quest 28598 complete'),
	(5424, 169, 'Obsidian Breakers phase after quest 28598 complete'),
	(5424, 361, 'Obsidian Breakers phase before quest 28598 complete'),
	(5602, 312, 'Schnottz\'s Landing phase while quest 27950 taken'),
	(5602, 313, 'Schnottz\'s Landing phase up to quest 27950 rewarded'),
	(5602, 315, 'Schnottz\'s Landing phase after quest 27950 rewarded'),
	(5602, 324, 'Schnottz\'s Landing phase after quest 28002 rewarded'),
	(5602, 325, 'Schnottz\'s Landing phase after quest 27990 Completed'),
	(5700, 313, 'Schnottz\'s Hostel phase up to quest 27950 rewarded'),
	(5700, 315, 'Schnottz\'s Hostel phase after quest 27950 rewarded'),
	(5700, 324, 'Schnottz\'s Hostel phase after quest 28002 rewarded');
/*!40000 ALTER TABLE `phase_area` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
