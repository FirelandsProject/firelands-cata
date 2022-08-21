/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `spawn_group_template` (
  `groupId` int unsigned NOT NULL,
  `groupName` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `groupFlags` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`groupId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DELETE FROM `spawn_group_template`;
/*!40000 ALTER TABLE `spawn_group_template` DISABLE KEYS */;
INSERT INTO `spawn_group_template` (`groupId`, `groupName`, `groupFlags`) VALUES
	(0, 'Default Group', 1),
	(1, 'Legacy Group', 3),
	(2, 'Dynamic Scaling (Quest objectives)', 9),
	(3, 'Dynamic Scaling (Escort NPCs)', 25),
	(4, 'Dynamic Scaling (Gathering nodes)', 9),
	(52, 'Culling of Stratholme - Chromie (middle)', 4),
	(53, 'Culling of Stratholme - Crate Helpers', 4),
	(54, 'Culling of Stratholme - Undead - Gauntlet', 4),
	(55, 'Culling of Stratholme - Undead', 4),
	(56, 'Culling of Stratholme - Stratholme residents', 4),
	(67, 'Ulduar - Assembly of Iron', 4),
	(400, 'Blackwing Descent - Ancient Dwarven Shields', 4),
	(401, 'Blackwing Descent - Growth Chambers', 4),
	(402, 'Blackwing Descent - Nefarian\'s End', 4),
	(403, 'The Vortex Pinnacle - Grandvizier Ertan Trash', 4),
	(404, 'The Vortex Pinnacle - Altairus Trash', 4),
	(405, 'The Vortex Pinnacle - Asaad Trash', 4),
	(406, 'The Vortex Pinnacle - Grandvizier Ertan Slipstreams', 4),
	(407, 'The Vortex Pinnacle - Altairus Slipstreams', 4),
	(408, 'The Vortex Pinnacle - Asaad Slipstreams', 4),
	(409, 'The Deadmines - Alliance Entrance', 4),
	(410, 'The Deadmines - Horde Entrance', 4),
	(411, 'The Deadmines - Goblin Event', 4),
	(412, 'Shadowfang Keep - Alliance Entrance', 4),
	(413, 'Shadowfang Keep - Horde Entrance', 4),
	(414, 'Shadowfang Keep - Disease Clouds Entrance', 4),
	(415, 'Shadowfang Keep - Disease Clouds Baron Ashbury', 4),
	(416, 'Shadowfang Keep - Disease Clouds Baron Silverlaine', 4),
	(417, 'Shadowfang Keep - Disease Clouds Commander Springvale', 4),
	(418, 'Shadowfang Keep - Disease Clouds Lord Walden', 4),
	(419, 'Shadowfang Keep - Lord Godfrey Dead Alliance Troups', 4),
	(420, 'Shadowfang Keep - Lord Godfrey Dead Horde Troups', 4),
	(421, 'Shadowfang Keep - Baron Ashbury Alliance Troups', 4),
	(422, 'Shadowfang Keep - Baron Ashbury Horde Troups', 4),
	(423, 'Shadowfang Keep - Baron Silverlaine Alliance Troups', 4),
	(424, 'Shadowfang Keep - Baron Silverlaine Horde Troups', 4),
	(425, 'Shadowfang Keep - Commander Springvale Alliance Troups', 4),
	(426, 'Shadowfang Keep - Outside Alliance Troups', 4),
	(427, 'Shadowfang Keep - Lord Walden Alliance Troups', 4),
	(428, 'Shadownfang Keep - Commander Springvale Horde Troups', 4),
	(429, 'Shadowfang Keep - Commander Springvale - Deathstalker Commander Belmont', 4),
	(430, 'Shadowfang Keep - Lord Walden - Deathstalker Commander Belmont', 4),
	(431, 'Shadowfang Keep - Lord Godfrey - Packleader Ivar Bloodfang', 4),
	(432, 'Shadowfang Keep - Lord Godfrey - Deathstalker Commander Belmont', 4),
	(433, 'Scarlet Monastry - Houndmaster Loksey - Scarlet Tracking Hounds', 4),
	(434, 'Blackrock Caverns - Twilight Portals', 4),
	(435, 'Blackwing Descent - Dwarven Spirits Left', 4),
	(436, 'Blackwing Descent - Dwarven Spirits Left', 4),
	(437, 'End Time - Murozond Chest', 4),
	(438, 'End Time - Murozond Trash Pack', 4),
	(439, 'Bastion of Twilight - Halfus Trash', 4),
	(440, 'Bastion of Twilight - Theralion and Valiona Trash', 4),
	(441, 'Bastion of Twilight - Ascendant Council Trash', 4),
	(442, 'Bastion of Twilight - Cho\'Gall Trash', 4),
	(443, 'Baradin Hold - Alizabal Trash', 4),
	(444, 'Firelands - Shannox Trash', 4),
	(445, 'Firelands - Baleroc Trash', 4),
	(446, 'Firelands - Alysrazor Trash', 4),
	(447, 'Firelands - Beth\'tilac Trash', 4),
	(448, 'Firelands - Majodomo Staghelm Trash', 4),
	(449, 'Firelands - Ragnaros Trash', 4),
	(450, 'The Stockade - Alliance Entrance', 4),
	(451, 'The Scarlet Monastery - Mograine and Whitemane', 4),
	(452, 'Blackrock Caverns - Finkle Einhorn', 4),
	(453, 'Scarlet Monastery - Alliance Spawns', 4),
	(454, 'Scarlet Monastery - Horde Spawns', 4),
	(455, 'Throne of the Tides - Ozumat Wing Event', 4),
	(456, 'Ragefire Chasm - Horde Spawns', 4),
	(457, 'Firelands - Lord Rhyolith', 4),
	(458, 'Firelands - Ragnaros', 4),
	(459, 'Firelands - Ragnaros Stalkers', 4),
	(460, 'End Time - Echo of Jaina - Jaina', 4);
/*!40000 ALTER TABLE `spawn_group_template` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
