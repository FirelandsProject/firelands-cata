-- MySQL dump 10.13  Distrib 8.0.29, for macos12 (x86_64)
--
-- Host: 127.0.0.1    Database: firelands_world
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
-- Table structure for table `summon_properties_parameters`
--

DROP TABLE IF EXISTS `summon_properties_parameters`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `summon_properties_parameters` (
  `RecID` int unsigned NOT NULL COMMENT 'SummonProperties.dbc Identifier',
  `ParamType` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`RecID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `summon_properties_parameters`
--

LOCK TABLES `summon_properties_parameters` WRITE;
/*!40000 ALTER TABLE `summon_properties_parameters` DISABLE KEYS */;
INSERT INTO `summon_properties_parameters` VALUES (41,2),(61,2),(63,1),(64,2),(65,7),(66,2),(67,2),(81,1),(161,4),(181,2),(327,3),(367,3),(467,3),(488,4),(493,3),(607,4),(629,2),(648,2),(689,4),(708,4),(710,4),(711,1),(713,2),(715,2),(716,4),(718,4),(760,4),(780,3),(801,4),(824,4),(827,4),(833,2),(843,4),(861,4),(1061,2),(1081,4),(1101,2),(1161,2),(1201,3),(1261,2),(1281,4),(1321,3),(1541,4),(1562,2),(1601,4),(1621,4),(1641,3),(1761,2),(1821,4),(1861,3),(2301,2),(2321,3),(2601,3),(2742,3),(2909,2),(2914,3),(2929,2),(2932,4),(2933,3),(2947,3),(2948,4),(2976,3),(2977,3),(2986,3),(3006,3),(3021,4),(3033,3),(3035,4),(3038,4),(3090,4),(3097,2),(3099,4),(3105,4),(3112,4),(3118,3),(3131,3),(3134,4),(3144,3);
/*!40000 ALTER TABLE `summon_properties_parameters` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-03 10:29:23
