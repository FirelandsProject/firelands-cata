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
-- Table structure for table `playercreateinfo_cast_spell`
--

DROP TABLE IF EXISTS `playercreateinfo_cast_spell`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `playercreateinfo_cast_spell` (
  `raceMask` int unsigned NOT NULL DEFAULT '0',
  `classMask` int unsigned NOT NULL DEFAULT '0',
  `spell` int unsigned NOT NULL DEFAULT '0',
  `note` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `playercreateinfo_cast_spell`
--

LOCK TABLES `playercreateinfo_cast_spell` WRITE;
/*!40000 ALTER TABLE `playercreateinfo_cast_spell` DISABLE KEYS */;
INSERT INTO `playercreateinfo_cast_spell` VALUES (0,32,48266,'Death Knight - Blood Presence'),(0,1,2457,'Warrior - Battle Stance'),(1,4,79597,'Human - Hunter - Young Wolf'),(2,4,79598,'Orc - Hunter - Young Boar'),(4,4,79593,'Dwarf - Hunter - Young Boar'),(8,4,79602,'Night Elf - Hunter - Young Boar'),(16,4,79600,'Undead - Hunter - Young Widow'),(32,4,79603,'Tauren - Hunter - Young Tallstrider'),(128,4,79599,'Troll - Hunter - Young Raptor'),(256,4,79595,'Goblin - Hunter - Young Crab'),(512,4,79594,'Blood Elf - Hunter - Young Dragonhawk'),(1024,4,79601,'Draenei - Hunter - Young Moth'),(2097152,4,79596,'Worgen - Hunter - Young Mastiff'),(0,256,688,'Warlock - Summon Imp'),(16,925,73523,'Undead - Rigor Mortis'),(64,256,80653,'Warlock - Gnome - Irradiated Aura'),(64,128,80653,'Mage - Gnome - Irradiated Aura'),(64,16,80653,'Priest - Gnome - Irradiated Aura'),(64,8,80653,'Rogue - Gnome - Irradiated Aura'),(64,1,80653,'Warrior - Gnome - Irradiated Aura'),(128,1503,71033,'Troll - Calm of the Novice');
/*!40000 ALTER TABLE `playercreateinfo_cast_spell` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-08-09 10:21:53
