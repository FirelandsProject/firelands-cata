/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `spell_group_stack_rules` (
  `group_id` int unsigned NOT NULL DEFAULT '0',
  `stack_rule` tinyint NOT NULL DEFAULT '0',
  PRIMARY KEY (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `spell_group_stack_rules`;
/*!40000 ALTER TABLE `spell_group_stack_rules` DISABLE KEYS */;
INSERT INTO `spell_group_stack_rules` (`group_id`, `stack_rule`) VALUES
	(1, 1),
	(2, 1),
	(1001, 1),
	(1106, 1),
	(1107, 4),
	(1108, 4),
	(1109, 1),
	(1110, 1),
	(1111, 1),
	(1121, 1),
	(1122, 1),
	(1123, 2),
	(1124, 2),
	(1125, 3),
	(1126, 3),
	(1127, 3),
	(1128, 3),
	(1129, 3),
	(1130, 3),
	(1131, 3),
	(1132, 3),
	(1133, 3),
	(1134, 3),
	(1135, 3),
	(1136, 3),
	(1137, 3),
	(1138, 3),
	(1139, 3),
	(1140, 3),
	(1141, 4),
	(1142, 3),
	(1143, 3),
	(1144, 3),
	(1145, 3),
	(1146, 3),
	(1147, 3),
	(1148, 1),
	(1149, 2),
	(1150, 2),
	(1151, 2),
	(1152, 3);
/*!40000 ALTER TABLE `spell_group_stack_rules` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
