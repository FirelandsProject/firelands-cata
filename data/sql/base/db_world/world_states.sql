/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `world_states` (
  `ID` int unsigned NOT NULL,
  `DefaultValue` int NOT NULL DEFAULT '0',
  `MapID` int unsigned DEFAULT NULL,
  `Comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `world_states`;
/*!40000 ALTER TABLE `world_states` DISABLE KEYS */;
INSERT INTO `world_states` (`ID`, `DefaultValue`, `MapID`, `Comment`) VALUES
	(5117, 0, 670, 'Grim Batol - Erudax - Don\'t need to Break Eggs to Make an Omelet'),
	(5607, 0, 671, 'Bastion of Twilight - Halfus Wyrmbreaker - The Only Escape'),
	(5621, 0, 671, 'Bastion of Twilight - Ascendant Council - Elementary'),
	(5637, 0, 645, 'Blackrock Caverns - Ascendant Lord Obsidius - Ascendant Descending'),
	(5638, 0, 644, 'Halls of Origination - Temple Guardian Anhuur - I Hate That Song'),
	(5639, 0, 644, 'Halls of Origination - Rajh - Sun of a...'),
	(5640, 0, 669, 'Blackwing Descent - Magmaw - Parasite Evening'),
	(5643, 0, 669, 'Blackwing Descent - Chimaeron - Full of Sound and Fury'),
	(5644, 0, 669, 'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),
	(5645, 0, 669, 'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),
	(5646, 0, 669, 'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),
	(5647, 0, 669, 'Blackwing Descent - Omnotron Defense System - Achieve-a-tron'),
	(5652, 1, 669, 'Blackwing Descent - Nefarian\'s End - Keeping it in the Family'),
	(5653, 0, 644, 'Halls of Origination - Vault of Lights - Faster Than The Speed Of Light'),
	(5655, 0, 669, 'Blackwing Descent - Atramedes - Silence is Golden'),
	(5659, 0, 671, 'Bastion of Twilight - Cho\'Gall - The Abyss Will Gate Back Into You'),
	(5670, 0, 33, 'Shadowfang Keep - Baron Ashbury - Pardon Denied'),
	(5672, 0, 33, 'Shadowfang Keep - Commander Srpingvale - To the Ground!'),
	(5931, 0, 720, 'Firelands - Lord Rhyolith - Not an Ambi-Turner');
/*!40000 ALTER TABLE `world_states` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
