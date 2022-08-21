/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `item_script_names` (
  `Id` int unsigned NOT NULL,
  `ScriptName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `item_script_names`;
/*!40000 ALTER TABLE `item_script_names` DISABLE KEYS */;
INSERT INTO `item_script_names` (`Id`, `ScriptName`) VALUES
	(19169, 'item_generic_limit_chance_above_60'),
	(24538, 'item_only_for_flight'),
	(30175, 'item_gor_dreks_ointment'),
	(31088, 'item_tainted_core'),
	(31742, 'item_nether_wraith_beacon'),
	(33098, 'item_petrov_cluster_bombs'),
	(34475, 'item_only_for_flight'),
	(34489, 'item_only_for_flight'),
	(35127, 'item_pile_fake_furs'),
	(35228, 'item_dehta_trap_smasher'),
	(35704, 'item_incendiary_explosives'),
	(39878, 'item_mysterious_egg'),
	(44717, 'item_disgusting_jar'),
	(53510, 'item_captured_frog');
/*!40000 ALTER TABLE `item_script_names` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
