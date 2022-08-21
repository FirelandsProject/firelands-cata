/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `addons` (
  `name` varchar(120) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '',
  `crc` int unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Addons';

DELETE FROM `addons`;
/*!40000 ALTER TABLE `addons` DISABLE KEYS */;
INSERT INTO `addons` (`name`, `crc`) VALUES
	('Blizzard_AchievementUI', 1276933997),
	('Blizzard_ArchaeologyUI', 1276933997),
	('Blizzard_ArenaUI', 1276933997),
	('Blizzard_AuctionUI', 1276933997),
	('Blizzard_BarbershopUI', 1276933997),
	('Blizzard_BattlefieldMinimap', 1276933997),
	('Blizzard_BindingUI', 1276933997),
	('Blizzard_Calendar', 1276933997),
	('Blizzard_ClientSavedVariables', 1276933997),
	('Blizzard_CombatLog', 1276933997),
	('Blizzard_CombatText', 1276933997),
	('Blizzard_CompactRaidFrames', 1276933997),
	('Blizzard_CUFProfiles', 1276933997),
	('Blizzard_DebugTools', 1276933997),
	('Blizzard_EncounterJournal', 1276933997),
	('Blizzard_GlyphUI', 1276933997),
	('Blizzard_GMChatUI', 1276933997),
	('Blizzard_GMSurveyUI', 1276933997),
	('Blizzard_GuildBankUI', 1276933997),
	('Blizzard_GuildControlUI', 1276933997),
	('Blizzard_GuildUI', 1276933997),
	('Blizzard_InspectUI', 1276933997),
	('Blizzard_ItemAlterationUI', 1276933997),
	('Blizzard_ItemSocketingUI', 1276933997),
	('Blizzard_LookingForGuildUI', 1276933997),
	('Blizzard_MacroUI', 1276933997),
	('Blizzard_MovePad', 1276933997),
	('Blizzard_RaidUI', 1276933997),
	('Blizzard_ReforgingUI', 1276933997),
	('Blizzard_TalentUI', 1276933997),
	('Blizzard_TimeManager', 1276933997),
	('Blizzard_TokenUI', 1276933997),
	('Blizzard_TradeSkillUI', 1276933997),
	('Blizzard_TrainerUI', 1276933997),
	('Blizzard_VoidStorageUI', 1276933997);
/*!40000 ALTER TABLE `addons` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
