-- MySQL dump 10.13  Distrib 8.0.29, for macos12 (x86_64)
--
-- Host: 127.0.0.1    Database: firelands_hotfixes
-- ------------------------------------------------------
-- Server version	8.0.30

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `item_extended_cost`
--

DROP TABLE IF EXISTS `item_extended_cost`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `item_extended_cost` (
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
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `item_extended_cost`
--

LOCK TABLES `item_extended_cost` WRITE;
/*!40000 ALTER TABLE `item_extended_cost` DISABLE KEYS */;
/*!40000 ALTER TABLE `item_extended_cost` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-03 10:44:38
