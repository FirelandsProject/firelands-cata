/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `gossip_menu_option_box` (
  `MenuId` int unsigned NOT NULL DEFAULT '0',
  `OptionIndex` int unsigned NOT NULL DEFAULT '0',
  `BoxCoded` tinyint unsigned NOT NULL DEFAULT '0',
  `BoxMoney` int unsigned NOT NULL DEFAULT '0',
  `BoxText` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `BoxBroadcastTextId` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`MenuId`,`OptionIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `gossip_menu_option_box`;
/*!40000 ALTER TABLE `gossip_menu_option_box` DISABLE KEYS */;
INSERT INTO `gossip_menu_option_box` (`MenuId`, `OptionIndex`, `BoxCoded`, `BoxMoney`, `BoxText`, `BoxBroadcastTextId`) VALUES
	(0, 16, 0, 100000, 'Are you sure you wish to purchase a Dual Talent Specialization?', 0),
	(4150, 1, 0, 0, 'Do you really want to unlearn your Gnomish Engineering specialization and lose all associated recipes?', 0),
	(6565, 0, 1, 0, '', 0),
	(6565, 1, 1, 0, '', 0),
	(6565, 2, 1, 0, '', 0),
	(7034, 0, 1, 0, '', 0),
	(7058, 0, 0, 1500000, 'Do you really want to unlearn your Gnomish Engineering specialization and lose all associated recipes?', 36144),
	(7058, 1, 0, 1500000, 'Do you really want to unlearn your Goblin Engineering specialization and lose all associated recipes?', 36145),
	(9014, 0, 0, 10000, 'Do you really want to bribe Olga?', 0),
	(9016, 0, 0, 10000, 'Do you really want to bribe Olga?', 25743),
	(9191, 0, 1, 0, '', 0),
	(9191, 1, 1, 0, '', 0),
	(9191, 2, 1, 0, '', 0),
	(9192, 0, 1, 0, '', 0),
	(9192, 1, 1, 0, '', 0),
	(9192, 2, 1, 0, '', 0),
	(9193, 0, 1, 0, '', 0),
	(9193, 1, 1, 0, '', 0),
	(9193, 2, 1, 0, '', 0),
	(9193, 3, 1, 0, '', 0),
	(9193, 4, 1, 0, '', 0),
	(9193, 5, 1, 0, '', 0),
	(9193, 6, 1, 0, '', 0),
	(9193, 7, 1, 0, '', 0),
	(9193, 8, 1, 0, '', 0),
	(9193, 9, 1, 0, '', 0),
	(9194, 0, 1, 0, '', 0),
	(9194, 1, 1, 0, '', 0),
	(9194, 2, 1, 0, '', 0),
	(9195, 0, 1, 0, '', 0),
	(9195, 1, 1, 0, '', 0),
	(9195, 2, 1, 0, '', 0),
	(9196, 0, 1, 0, '', 0),
	(9196, 1, 1, 0, '', 0),
	(9196, 2, 1, 0, '', 0),
	(9629, 0, 1, 0, '', 0),
	(9629, 1, 1, 0, '', 0),
	(9629, 2, 1, 0, '', 0),
	(9682, 0, 1, 0, '', 0),
	(9682, 1, 1, 0, '', 0),
	(9682, 2, 1, 0, '', 0),
	(9768, 0, 1, 0, '', 0),
	(10330, 0, 1, 0, '', 0),
	(10330, 1, 1, 0, '', 0),
	(10330, 2, 1, 0, '', 0),
	(10371, 0, 0, 100000, 'Are you sure you would like to purchase your second talent specialization?', 0),
	(10533, 0, 1, 0, '', 0),
	(10533, 1, 1, 0, '', 0),
	(10533, 2, 1, 0, '', 0),
	(10638, 0, 0, 100000, 'Are you certain you wish to stop gaining experience?', 35535),
	(10638, 1, 0, 100000, 'Are you certain you wish to start gaining experience again?', 35533),
	(10810, 0, 1, 0, '', 0),
	(10810, 2, 1, 0, '', 0),
	(10810, 3, 1, 0, '', 0),
	(11342, 0, 1, 0, '', 0),
	(11342, 1, 1, 0, '', 0),
	(11342, 2, 1, 0, '', 0),
	(11343, 0, 1, 0, '', 0),
	(11343, 1, 1, 0, '', 0),
	(11343, 2, 1, 0, '', 0),
	(11635, 1, 0, 2, 'Are you sure you want to give this hobo money?', 42373),
	(12658, 0, 1, 0, '', 0),
	(12658, 1, 1, 0, '', 0),
	(12658, 2, 1, 0, '', 0),
	(12670, 0, 0, 500000, 'Are you sure you want to pay to abandon your minion?', 0),
	(12670, 1, 0, 500000, 'Are you sure you want to pay to abandon your minion?', 0),
	(12670, 2, 0, 500000, 'Are you sure you want to pay to abandon your minion?', 0),
	(12670, 3, 0, 500000, 'Are you sure you want to pay to abandon your minion?', 0),
	(12723, 0, 0, 10000, 'Will you pay "Pretty Boy" Duncan 1 gold to swab the decks for you?', 0),
	(12784, 0, 1, 0, '', 0),
	(12784, 1, 1, 0, '', 0),
	(12784, 2, 1, 0, '', 0),
	(12785, 0, 1, 0, '', 0),
	(12785, 1, 1, 0, '', 0),
	(12785, 2, 1, 0, '', 0),
	(12992, 0, 0, 25, 'Travel to the faire staging area will cost:', 0),
	(12992, 2, 0, 500, 'Travel to the faire staging area will cost:', 0),
	(12992, 5, 0, 3000, 'Travel to the faire staging area will cost:', 0),
	(13003, 0, 1, 0, '', 0),
	(13003, 1, 1, 0, '', 0),
	(13003, 2, 1, 0, '', 0),
	(13088, 0, 1, 0, '', 0),
	(13088, 1, 1, 0, '', 0),
	(13088, 2, 1, 0, '', 0),
	(13089, 0, 1, 0, '', 0),
	(13089, 1, 1, 0, '', 0),
	(13089, 2, 1, 0, '', 0),
	(13124, 0, 0, 25, 'Travel to the faire staging area will cost:', 0),
	(13295, 0, 0, 0, 'Do you want to start the encounter?', 57303),
	(13352, 0, 0, 25, 'Teleportation to the cannon will cost:', 0),
	(13506, 0, 1, 0, '', 0),
	(13506, 1, 1, 0, '', 0),
	(13506, 2, 1, 0, '', 0),
	(21402, 0, 0, 1500000, 'Forgetting your knowledge is an expensive endeavor.  Are you willing to pay the cost?', 21569),
	(21403, 0, 0, 1500000, 'Forgetting your knowledge is an expensive endeavor.  Are you willing to pay the cost?', 21569),
	(21404, 0, 0, 1500000, 'Forgetting your knowledge is an expensive endeavor.  Are you willing to pay the cost?', 21569);
/*!40000 ALTER TABLE `gossip_menu_option_box` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
