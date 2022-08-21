/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `key_chain` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `Key1` tinyint unsigned NOT NULL DEFAULT '0',
  `Key2` tinyint unsigned NOT NULL DEFAULT '0',
  `Key3` tinyint unsigned NOT NULL DEFAULT '0',
  `Key4` tinyint unsigned NOT NULL DEFAULT '0',
  `Key5` tinyint unsigned NOT NULL DEFAULT '0',
  `Key6` tinyint unsigned NOT NULL DEFAULT '0',
  `Key7` tinyint unsigned NOT NULL DEFAULT '0',
  `Key8` tinyint unsigned NOT NULL DEFAULT '0',
  `Key9` tinyint unsigned NOT NULL DEFAULT '0',
  `Key10` tinyint unsigned NOT NULL DEFAULT '0',
  `Key11` tinyint unsigned NOT NULL DEFAULT '0',
  `Key12` tinyint unsigned NOT NULL DEFAULT '0',
  `Key13` tinyint unsigned NOT NULL DEFAULT '0',
  `Key14` tinyint unsigned NOT NULL DEFAULT '0',
  `Key15` tinyint unsigned NOT NULL DEFAULT '0',
  `Key16` tinyint unsigned NOT NULL DEFAULT '0',
  `Key17` tinyint unsigned NOT NULL DEFAULT '0',
  `Key18` tinyint unsigned NOT NULL DEFAULT '0',
  `Key19` tinyint unsigned NOT NULL DEFAULT '0',
  `Key20` tinyint unsigned NOT NULL DEFAULT '0',
  `Key21` tinyint unsigned NOT NULL DEFAULT '0',
  `Key22` tinyint unsigned NOT NULL DEFAULT '0',
  `Key23` tinyint unsigned NOT NULL DEFAULT '0',
  `Key24` tinyint unsigned NOT NULL DEFAULT '0',
  `Key25` tinyint unsigned NOT NULL DEFAULT '0',
  `Key26` tinyint unsigned NOT NULL DEFAULT '0',
  `Key27` tinyint unsigned NOT NULL DEFAULT '0',
  `Key28` tinyint unsigned NOT NULL DEFAULT '0',
  `Key29` tinyint unsigned NOT NULL DEFAULT '0',
  `Key30` tinyint unsigned NOT NULL DEFAULT '0',
  `Key31` tinyint unsigned NOT NULL DEFAULT '0',
  `Key32` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `key_chain`;
/*!40000 ALTER TABLE `key_chain` DISABLE KEYS */;
INSERT INTO `key_chain` (`ID`, `Key1`, `Key2`, `Key3`, `Key4`, `Key5`, `Key6`, `Key7`, `Key8`, `Key9`, `Key10`, `Key11`, `Key12`, `Key13`, `Key14`, `Key15`, `Key16`, `Key17`, `Key18`, `Key19`, `Key20`, `Key21`, `Key22`, `Key23`, `Key24`, `Key25`, `Key26`, `Key27`, `Key28`, `Key29`, `Key30`, `Key31`, `Key32`) VALUES
	(33, 53, 6, 164, 135, 117, 210, 209, 135, 247, 162, 85, 200, 76, 220, 107, 56, 80, 214, 44, 121, 29, 66, 81, 25, 41, 38, 208, 8, 235, 154, 58, 139),
	(35, 16, 209, 60, 47, 154, 100, 204, 97, 125, 161, 79, 126, 191, 163, 7, 45, 64, 188, 199, 88, 141, 46, 153, 90, 143, 40, 6, 80, 29, 133, 217, 135),
	(36, 3, 169, 217, 5, 156, 76, 33, 82, 75, 181, 233, 203, 230, 52, 67, 197, 57, 99, 27, 108, 100, 197, 93, 156, 174, 2, 248, 216, 244, 115, 164, 210),
	(37, 119, 7, 189, 206, 199, 253, 234, 73, 232, 17, 162, 79, 0, 35, 222, 224, 7, 98, 132, 147, 229, 36, 19, 253, 79, 59, 198, 59, 48, 121, 97, 215);
/*!40000 ALTER TABLE `key_chain` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
