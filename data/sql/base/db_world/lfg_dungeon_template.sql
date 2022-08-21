/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `lfg_dungeon_template` (
  `dungeonId` int unsigned NOT NULL DEFAULT '0' COMMENT 'Unique id from LFGDungeons.dbc',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `position_x` float NOT NULL DEFAULT '0',
  `position_y` float NOT NULL DEFAULT '0',
  `position_z` float NOT NULL DEFAULT '0',
  `orientation` float NOT NULL DEFAULT '0',
  `requiredItemLevel` smallint NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint DEFAULT '0',
  PRIMARY KEY (`dungeonId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `lfg_dungeon_template`;
/*!40000 ALTER TABLE `lfg_dungeon_template` DISABLE KEYS */;
INSERT INTO `lfg_dungeon_template` (`dungeonId`, `name`, `position_x`, `position_y`, `position_z`, `orientation`, `requiredItemLevel`, `VerifiedBuild`) VALUES
	(18, 'Scarlet Monastery - Graveyard', 1688.99, 1053.48, 18.6775, 0.00117, 0, 0),
	(26, 'Maraudon - Orange Crystals', 1019.69, -458.31, -43.43, 0.31, 0, 0),
	(30, 'Blackrock Depths - Prison', 456.929, 34.0923, -68.0896, 4.71239, 0, 11159),
	(34, 'Dire Maul - East', 44.4499, -154.822, -2.71201, 0, 0, 0),
	(36, 'Dire Maul - West', -62.9658, 159.867, -3.46206, 3.14788, 0, 0),
	(38, 'Dire Maul - North', 255.249, -16.0561, -2.58737, 4.7, 0, 0),
	(40, 'Stratholme - Main Gate', 3395.09, -3380.25, 142.702, 0.1, 0, 0),
	(163, 'Scarlet Monastery - Armory', 1610.83, -323.433, 18.6738, 6.28022, 0, 0),
	(164, 'Scarlet Monastery - Cathedral', 855.683, 1321.5, 18.6709, 0.001747, 0, 0),
	(165, 'Scarlet Monastery - Library', 255.346, -209.09, 18.6773, 6.26656, 0, 0),
	(205, 'Utgarde Pinnacle Heroic', 0, 0, 0, 0, 180, 0),
	(210, 'Culling of Stratholme Heroic', 0, 0, 0, 0, 180, 0),
	(211, 'Oculus Heroic', 0, 0, 0, 0, 180, 0),
	(212, 'Halls of Lightning Heroic', 0, 0, 0, 0, 180, 0),
	(213, 'Halls of Stone Heroic', 0, 0, 0, 0, 180, 0),
	(215, 'Drak\'Tharon Keep Heroic', 0, 0, 0, 0, 180, 0),
	(217, 'Gundrak Heroic', 0, 0, 0, 0, 180, 0),
	(219, 'Ahn\'kahet: The Old Kingdom Heroic', 0, 0, 0, 0, 180, 0),
	(221, 'Violet Hold Heroic', 0, 0, 0, 0, 180, 0),
	(226, 'The Nexus Heroic', 0, 0, 0, 0, 180, 0),
	(241, 'Azjol-Nerub Heroic', 0, 0, 0, 0, 180, 0),
	(242, 'Utgarde Keep Heroic', 0, 0, 0, 0, 180, 0),
	(245, 'Trial of the Champion', 0, 0, 0, 0, 200, 0),
	(249, 'Trial of the Champion Heroic', 0, 0, 0, 0, 200, 0),
	(251, 'Forge of Souls', 0, 0, 0, 0, 200, 0),
	(252, 'Forge of Souls Heroic', 0, 0, 0, 0, 200, 0),
	(253, 'Pit of Saron', 0, 0, 0, 0, 200, 0),
	(254, 'Pit of Saron Heroic', 0, 0, 0, 0, 200, 0),
	(255, 'Halls of Reflection (Normal)', 5239.01, 1932.64, 707.695, 0.800565, 219, 0),
	(256, 'Halls of Reflection (Heroic)', 5239.01, 1932.64, 707.695, 0.800565, 219, 0),
	(262, NULL, 0, 0, 0, 0, 180, 0),
	(272, 'Maraudon - Purple Crystals', 752.91, -616.53, -33.11, 1.37, 0, 0),
	(273, 'Maraudon - Pristine Waters', 495.702, 17.3372, -96.3128, 3.11854, 0, 0),
	(274, 'Stratholme - Service Entrance', 3593.15, -3646.56, 138.5, 5.33, 0, 0),
	(276, 'Blackrock Depths - Upper City', 456.929, 34.0923, -68.0896, 4.71239, 0, 11159),
	(285, 'The Headless Horseman', 0, 0, 0, 0, 329, 0),
	(286, 'Frostlord Ahune', 0, 0, 0, 0, 329, 0),
	(287, 'Coren Direbrew', 0, 0, 0, 0, 329, 0),
	(288, 'The Crown Chemical Co.', 0, 0, 0, 0, 329, 0),
	(299, 'Prince Sarsarun', -9132.12, 1599.28, 26.848, 5.31086, 0, 0),
	(300, 'Random Dungeon - Cataclysm', 0, 0, 0, 0, 226, 0),
	(301, 'Heroic Random (Cataclysm)', 0, 0, 0, 0, 329, 0),
	(302, 'Throne of the Tides Normal', 0, 0, 0, 0, 226, 0),
	(303, 'Blackrock Caverns Normal', 0, 0, 0, 0, 226, 0),
	(304, 'Grim Batol Normal', 0, 0, 0, 0, 305, 0),
	(305, 'Halls of Origination Normal', 0, 0, 0, 0, 305, 0),
	(307, 'The Stonecore Normal', 0, 0, 0, 0, 272, 0),
	(310, 'Prince Sarsarun', -9132.12, 1599.28, 26.848, 5.31086, 0, 0),
	(311, 'TheVortex Pinnacle Normal', 0, 0, 0, 0, 272, 0),
	(312, 'The Lost City of the Tol\'Vir Normal', 0, 0, 0, 0, 305, 0),
	(319, 'The Vortex Pinnacle Heroic', 0, 0, 0, 0, 329, 0),
	(320, 'The Stonecore Heroic', 0, 0, 0, 0, 329, 0),
	(321, 'Halls of Origination', 0, 0, 0, 0, 329, 0),
	(322, 'Grim Batol Heroic', 0, 0, 0, 0, 329, 0),
	(323, 'Blackrock Caverns Heroic', 0, 0, 0, 0, 329, 0),
	(324, 'Throne of the Tides Heroic', 0, 0, 0, 0, 329, 0),
	(325, 'The Lost City of the Tol\'Vir Heroic', 0, 0, 0, 0, 329, 0),
	(326, 'Deadmines Heroic', 0, 0, 0, 0, 329, 0),
	(327, 'Shadowfang Keep Heroic', 0, 0, 0, 0, 329, 0),
	(334, 'Zul\'Gurub Heroic', 0, 0, 0, 0, 346, 0),
	(340, 'Zul\'Aman Heroic', 0, 0, 0, 0, 346, 0),
	(416, 'Siege of the Wyrmrest Temple', 0, 0, 0, 0, 372, 0),
	(417, 'Fall of Deathwing', 0, 0, 0, 0, 372, 0),
	(434, 'Heroic Random (Hour of Twlight)', 0, 0, 0, 0, 353, 0),
	(435, 'End Time Heroic', 0, 0, 0, 0, 353, 0),
	(437, 'Well of Eternity', 0, 0, 0, 0, 353, 0),
	(439, 'Hour of Twilight', 0, 0, 0, 0, 353, 0);
/*!40000 ALTER TABLE `lfg_dungeon_template` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
