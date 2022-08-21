/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `npc_text_locale` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `Locale` varchar(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `Text0_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text0_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text1_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text1_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text2_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text2_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text3_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text3_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text4_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text4_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text5_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text5_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text6_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text6_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text7_0` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `Text7_1` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  PRIMARY KEY (`ID`,`Locale`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `npc_text_locale`;
/*!40000 ALTER TABLE `npc_text_locale` DISABLE KEYS */;
/*!40000 ALTER TABLE `npc_text_locale` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
