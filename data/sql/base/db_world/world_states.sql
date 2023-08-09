-- MySQL dump 10.13  Distrib 8.0.34, for macos13 (arm64)
--
-- Host: 127.0.0.1    Database: firelands_world
-- ------------------------------------------------------
-- Server version	8.1.0

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
-- Table structure for table `world_states`
--

DROP TABLE IF EXISTS `world_states`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `world_states` (
  `ID` int unsigned NOT NULL,
  `DefaultValue` int NOT NULL DEFAULT '0',
  `MapID` int unsigned DEFAULT NULL,
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `world_states`
--

LOCK TABLES `world_states` WRITE;
/*!40000 ALTER TABLE `world_states` DISABLE KEYS */;
INSERT INTO `world_states` VALUES (5117,0,670,'Grim Batol - Erudax - Don\'t need to Break Eggs to Make an Omelet'),(5607,0,671,'Bastion of Twilight - Halfus Wyrmbreaker - The Only Escape'),(5621,0,671,'Bastion of Twilight - Ascendant Council - Elementary'),(5637,0,645,'Blackrock Caverns - Ascendant Lord Obsidius - Ascendant Descending'),(5638,0,644,'Halls of Origination - Temple Guardian Anhuur - I Hate That Song'),(5639,0,644,'Halls of Origination - Rajh - Sun of a...'),(5640,0,669,'Blackwing Descent - Magmaw - Parasite Evening'),(5643,0,669,'Blackwing Descent - Chimaeron - Full of Sound and Fury'),(5644,0,669,'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),(5645,0,669,'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),(5646,0,669,'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),(5647,0,669,'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),(5652,1,669,'Blackwing Descent - Nefarian\'s End - Keeping it in the Family'),(5653,0,644,'Halls of Origination - Vault of Lights - Faster Than The Speed Of Light'),(5655,0,669,'Blackwing Descent - Atramedes - Silence is Golden'),(5659,0,671,'Bastion of Twilight - Cho\'Gall - The Abyss Will Gate Back Into You'),(5670,0,33,'Shadowfang Keep - Baron Ashbury - Pardon Denied'),(5672,0,33,'Shadowfang Keep - Commander Srpingvale - To the Ground!'),(5931,0,720,'Firelands - Lord Rhyolith - Not an Ambi-Turner');
/*!40000 ALTER TABLE `world_states` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-08-09 10:21:46
