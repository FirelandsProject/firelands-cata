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
-- Table structure for table `phase_area`
--

DROP TABLE IF EXISTS `phase_area`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `phase_area` (
  `AreaId` int unsigned NOT NULL,
  `PhaseId` int unsigned NOT NULL,
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`AreaId`,`PhaseId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `phase_area`
--

LOCK TABLES `phase_area` WRITE;
/*!40000 ALTER TABLE `phase_area` DISABLE KEYS */;
INSERT INTO `phase_area` VALUES (108,226,'Sentinel Hill - Rise of the Brotherhood'),(4714,105,'Gilneas - Phase 105'),(4861,194,'Mount Hyjal - The Regrowth - Phase 194'),(4979,195,'Mount Hyjal - Shrine of Goldrinn - Phase 195'),(4989,194,'Mount Hyjal - Grove of Aessina - Phase 194'),(4990,194,'Mount Hyjal - Shrine of Aviana - Phase 194'),(5013,194,'Mount Hyjal - Blackhorn\'s Penance - Phase 194'),(5014,194,'Mount Hyjal - The Inferno - Phase 194'),(5016,194,'Mount Hyjal - Whistling Grove - Phase 194'),(5018,194,'Mount Hyjal - Ashen Lake - Phase 194'),(5019,194,'Mount Hyjal - Sanctuary of Malorne - Phase 194'),(5020,194,'Mount Hyjal - The Flamewake - Phase 194'),(5022,194,'Mount Hyjal - Rim of the World - Phase 194'),(5140,169,'Highbank phase after quest 28598 complete'),(5140,361,'Highbank phase before quest 28598 complete'),(5424,169,'Obsidian Breakers phase after quest 28598 complete'),(5424,361,'Obsidian Breakers phase before quest 28598 complete'),(5602,312,'Schnottz\'s Landing phase while quest 27950 taken'),(5602,313,'Schnottz\'s Landing phase up to quest 27950 rewarded'),(5602,315,'Schnottz\'s Landing phase after quest 27950 rewarded'),(5602,324,'Schnottz\'s Landing phase after quest 28002 rewarded'),(5602,325,'Schnottz\'s Landing phase after quest 27990 Completed'),(5700,313,'Schnottz\'s Hostel phase up to quest 27950 rewarded'),(5700,315,'Schnottz\'s Hostel phase after quest 27950 rewarded'),(5700,324,'Schnottz\'s Hostel phase after quest 28002 rewarded');
/*!40000 ALTER TABLE `phase_area` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-03 10:29:20
