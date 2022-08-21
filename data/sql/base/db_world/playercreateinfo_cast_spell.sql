/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `playercreateinfo_cast_spell` (
  `raceMask` int unsigned NOT NULL DEFAULT '0',
  `classMask` int unsigned NOT NULL DEFAULT '0',
  `spell` int unsigned NOT NULL DEFAULT '0',
  `note` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `playercreateinfo_cast_spell`;
/*!40000 ALTER TABLE `playercreateinfo_cast_spell` DISABLE KEYS */;
INSERT INTO `playercreateinfo_cast_spell` (`raceMask`, `classMask`, `spell`, `note`) VALUES
	(0, 32, 48266, 'Death Knight - Blood Presence'),
	(0, 1, 2457, 'Warrior - Battle Stance'),
	(1, 4, 79597, 'Human - Hunter - Young Wolf'),
	(2, 4, 79598, 'Orc - Hunter - Young Boar'),
	(4, 4, 79593, 'Dwarf - Hunter - Young Boar'),
	(8, 4, 79602, 'Night Elf - Hunter - Young Boar'),
	(16, 4, 79600, 'Undead - Hunter - Young Widow'),
	(32, 4, 79603, 'Tauren - Hunter - Young Tallstrider'),
	(128, 4, 79599, 'Troll - Hunter - Young Raptor'),
	(256, 4, 79595, 'Goblin - Hunter - Young Crab'),
	(512, 4, 79594, 'Blood Elf - Hunter - Young Dragonhawk'),
	(1024, 4, 79601, 'Draenei - Hunter - Young Moth'),
	(2097152, 4, 79596, 'Worgen - Hunter - Young Mastiff'),
	(0, 256, 688, 'Warlock - Summon Imp'),
	(16, 925, 73523, 'Undead - Rigor Mortis'),
	(64, 256, 80653, 'Warlock - Gnome - Irradiated Aura'),
	(64, 128, 80653, 'Mage - Gnome - Irradiated Aura'),
	(64, 16, 80653, 'Priest - Gnome - Irradiated Aura'),
	(64, 8, 80653, 'Rogue - Gnome - Irradiated Aura'),
	(64, 1, 80653, 'Warrior - Gnome - Irradiated Aura'),
	(128, 1503, 71033, 'Troll - Calm of the Novice');
/*!40000 ALTER TABLE `playercreateinfo_cast_spell` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
