/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `item_extended_cost` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `RequiredHonorPoints` int unsigned NOT NULL DEFAULT '0',
  `RequiredArenaPoints` int unsigned NOT NULL DEFAULT '0',
  `RequiredArenaSlot` int unsigned NOT NULL DEFAULT '0',
  `RequiredItem1` int unsigned NOT NULL DEFAULT '0',
  `RequiredItem2` int unsigned NOT NULL DEFAULT '0',
  `RequiredItem3` int unsigned NOT NULL DEFAULT '0',
  `RequiredItem4` int unsigned NOT NULL DEFAULT '0',
  `RequiredItem5` int unsigned NOT NULL DEFAULT '0',
  `RequiredItemCount1` int unsigned NOT NULL DEFAULT '0',
  `RequiredItemCount2` int unsigned NOT NULL DEFAULT '0',
  `RequiredItemCount3` int unsigned NOT NULL DEFAULT '0',
  `RequiredItemCount4` int unsigned NOT NULL DEFAULT '0',
  `RequiredItemCount5` int unsigned NOT NULL DEFAULT '0',
  `RequiredPersonalArenaRating` int unsigned NOT NULL DEFAULT '0',
  `ItemPurchaseGroup` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrency1` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrency2` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrency3` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrency4` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrency5` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrencyCount1` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrencyCount2` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrencyCount3` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrencyCount4` int unsigned NOT NULL DEFAULT '0',
  `RequiredCurrencyCount5` int unsigned NOT NULL DEFAULT '0',
  `RequiredFactionId` int unsigned NOT NULL DEFAULT '0',
  `RequiredFactionStanding` int unsigned NOT NULL DEFAULT '0',
  `RequirementFlags` int unsigned NOT NULL DEFAULT '0',
  `RequiredGuildLevel` int unsigned NOT NULL DEFAULT '0',
  `RequiredAchievement` int unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `item_extended_cost`;
/*!40000 ALTER TABLE `item_extended_cost` DISABLE KEYS */;
/*!40000 ALTER TABLE `item_extended_cost` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
