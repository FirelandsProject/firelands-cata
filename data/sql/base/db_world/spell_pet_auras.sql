/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `spell_pet_auras` (
  `spell` int unsigned NOT NULL COMMENT 'dummy spell id',
  `effectId` tinyint unsigned NOT NULL DEFAULT '0',
  `pet` int unsigned NOT NULL DEFAULT '0' COMMENT 'pet id; 0 = all',
  `aura` int unsigned NOT NULL COMMENT 'pet aura id',
  PRIMARY KEY (`spell`,`effectId`,`pet`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `spell_pet_auras`;
/*!40000 ALTER TABLE `spell_pet_auras` DISABLE KEYS */;
INSERT INTO `spell_pet_auras` (`spell`, `effectId`, `pet`, `aura`) VALUES
	(19028, 0, 0, 25228),
	(19578, 0, 0, 19579),
	(20895, 0, 0, 24529),
	(23785, 0, 416, 23759),
	(23785, 0, 417, 23762),
	(23785, 0, 1860, 23760),
	(23785, 0, 1863, 23761),
	(23785, 0, 17252, 35702),
	(23822, 0, 416, 23826),
	(23822, 0, 417, 23837),
	(23822, 0, 1860, 23841),
	(23822, 0, 1863, 23833),
	(23822, 0, 17252, 35703),
	(23823, 0, 416, 23827),
	(23823, 0, 417, 23838),
	(23823, 0, 1860, 23842),
	(23823, 0, 1863, 23834),
	(23823, 0, 17252, 35704),
	(23824, 0, 416, 23828),
	(23824, 0, 417, 23839),
	(23824, 0, 1860, 23843),
	(23824, 0, 1863, 23835),
	(23824, 0, 17252, 35705),
	(23825, 0, 416, 23829),
	(23825, 0, 417, 23840),
	(23825, 0, 1860, 23844),
	(23825, 0, 1863, 23836),
	(23825, 0, 17252, 35706),
	(28757, 0, 0, 28758),
	(34460, 0, 0, 75447),
	(35691, 0, 0, 35696),
	(35692, 0, 0, 35696),
	(35693, 0, 0, 35696),
	(47236, 0, 0, 53646);
/*!40000 ALTER TABLE `spell_pet_auras` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
