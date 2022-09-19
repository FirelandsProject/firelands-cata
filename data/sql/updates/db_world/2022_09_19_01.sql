/*
Update DB Version
*/
DELETE FROM `version`;
/*!40000 ALTER TABLE `version` DISABLE KEYS */;
INSERT INTO `version` (`core_version`, `core_revision`, `db_version`, `cache_id`) VALUES
	('Firelands rev. c2b1d7f36b11 2022-09-13 12:04:43 -0500 (master branch) (MacOSX, RelWithDebInfo, Static)', 'c2b1d7f36b11', 'FDB 434.22012', 22012);
