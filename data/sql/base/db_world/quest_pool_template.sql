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
-- Table structure for table `quest_pool_template`
--

DROP TABLE IF EXISTS `quest_pool_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quest_pool_template` (
  `poolId` int unsigned NOT NULL,
  `numActive` int unsigned NOT NULL COMMENT 'Number of indices to have active at any time',
  `description` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`poolId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quest_pool_template`
--

LOCK TABLES `quest_pool_template` WRITE;
/*!40000 ALTER TABLE `quest_pool_template` DISABLE KEYS */;
INSERT INTO `quest_pool_template` VALUES (348,1,'Public Relations Agent <Crown Chemical Co.> - Daily Quests'),(349,1,'High Crusader Adelard - Daily Quests'),(350,1,'Toxic Tolerance Daily-Quests'),(351,1,'Toxic Tolerance Daily-Quests'),(352,1,'The Rokk <Master of Cooking> - Daily Quests'),(353,1,'Old Man Barlowned - Daily Quests'),(354,1,'Gretta the Arbiter - Daily Quests'),(356,1,'Wind Trader Zhareem - Daily Quests'),(357,1,'Nether-Stalker Mah\'duun - Daily Quests'),(358,1,'Marith Lazuria - Daily Quests'),(359,1,'Isabel Jones - Daily Quests'),(360,1,'Aska Mistrunner - Daily Quests'),(361,1,'Marogg - Daily Quests'),(362,1,'Eunice Burch - Daily Quests'),(363,1,'Narasi Snowdawn <The Silver Covenant> - Daily Quests'),(364,1,'Savinia Loresong <The Silver Covenant> - Daily Quests'),(365,1,'Girana the Blooded <The Sunreavers> - Daily Quests'),(366,1,'Tylos Dawnrunner <The Sunreavers> - Daily Quests'),(367,1,'Crusader Silverdawn Dailies'),(368,2,'Eredar Soul-Eater'),(369,5,'Ethereum Jailor'),(370,1,'Grimnur Stonebrand - Daily Quests'),(371,1,'Astaia - Daily Quests'),(372,2,'Commander Marcus Johnson - Daily Quests'),(373,1,'Dr. Whitherlimb'),(374,1,'Serfex the Reaver Spawn (1 out 4)'),(375,1,'North Sea Kraken (1 out 4)'),(376,2,'Commander Larmash - Daily Quests'),(377,1,'Tivax the Breaker (1 out 2)'),(378,2,'Private Sarlosk - Daily Quests'),(379,2,'Captain Prug - Daily Quests'),(380,1,'Borgoth the Bloodletter'),(381,1,'Masophet the Black'),(382,1,'Eye of DarKhan/Wailer Spawn 1'),(383,1,'Eye of Dar\'Khan/Wailer 3'),(5662,1,'TournamentDaily Sunreavers'),(5663,1,'TournamentDaily Orks'),(5664,1,'TournamentDaily Trolls'),(5665,1,'TournamentDaily Taurens'),(5666,1,'TournamentDaily Undeads '),(5667,1,'TournamentDaily Bloodelfs'),(5668,1,'TournamentDaily Convenant'),(5669,1,'TournamentDaily Humans'),(5670,1,'TournamentDaily Dwarfs'),(5671,1,'TournamentDaily Gnomes'),(5672,1,'TournamentDaily Nightelfs'),(5673,1,'TournamentDaily Dranei'),(5674,1,'DalaranCookingDaily Ally'),(5675,1,'DalaranCookingDaily Horde'),(5676,1,'DalaranFishingDaily'),(5677,1,'DalaranJewelcraftingDaily'),(5678,1,'Raiding weeklies'),(5707,1,'Wintergrasp weekly quests (Alliance, attackers)'),(5708,1,'Wintergrasp weekly quests (Alliance, defenders)'),(5709,1,'Wintergrasp weekly quests (Horde, attackers)'),(5710,1,'Wintergrasp weekly quests (Horde, defenders)'),(645019,1,'Molten Front Dalies 1'),(645020,1,'Molten Front Dalies 2'),(645021,1,'Molten Front Dalies 3'),(645024,1,'Molten Front Dalies Pool 1'),(645030,1,'Molten Front Dalies Pool 2');
/*!40000 ALTER TABLE `quest_pool_template` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-08-09 10:21:42
