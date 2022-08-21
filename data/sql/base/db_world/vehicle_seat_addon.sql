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
-- Table structure for table `vehicle_seat_addon`
--

DROP TABLE IF EXISTS `vehicle_seat_addon`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `vehicle_seat_addon` (
  `SeatEntry` int unsigned NOT NULL COMMENT 'VehicleSeatEntry.dbc identifier',
  `SeatOffsetX` float DEFAULT '0',
  `SeatOffsetY` float DEFAULT '0',
  `SeatOffsetZ` float DEFAULT '0',
  `SeatOffsetO` float DEFAULT '0' COMMENT 'Seat Orientation override value',
  `ExitParamX` float DEFAULT '0',
  `ExitParamY` float DEFAULT '0',
  `ExitParamZ` float DEFAULT '0',
  `ExitParamO` float DEFAULT '0',
  `ExitParamValue` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`SeatEntry`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vehicle_seat_addon`
--

LOCK TABLES `vehicle_seat_addon` WRITE;
/*!40000 ALTER TABLE `vehicle_seat_addon` DISABLE KEYS */;
INSERT INTO `vehicle_seat_addon` VALUES (2764,0,0,0,0,-2,2,0,0,1),(2765,0,0,0,0,-2,-2,0,0,1),(2767,0,0,0,0,-2,2,0,0,1),(2768,0,0,0,0,-2,-2,0,0,1),(7909,0,0,0,0,-311.465,-48.5972,212.807,1.06465,2),(7936,0,0,0,0,-311.465,-48.5972,212.807,1.06465,2),(8030,0,0,0,0,-9618.69,-1030.11,41.6842,4.84749,2),(8104,0,0,0,0,-311.465,-48.5972,212.807,1.06465,2),(8372,0,0,0,3.14159,0,0,0,0,0),(8426,0,0,0,3.14159,0,0,0,0,0),(8450,0,0,0,3.14159,0,0,0,0,0),(8451,0,0,0,3.14159,0,0,0,0,0),(8453,0,0,0,3.14159,0,0,0,0,0),(10472,0,0,0,0,-11929.8,12035.6,35.458,2.16421,2),(10699,263.089,15.0095,100.149,0,0,0,0,0,0);
/*!40000 ALTER TABLE `vehicle_seat_addon` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-08-03 10:29:19
