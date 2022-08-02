SET @ENTRY := 176;
DELETE FROM `firelands_string` WHERE `entry` IN(@ENTRY, @ENTRY+1);
INSERT INTO `firelands_string` (`entry`, `content_default`) VALUES 
(@ENTRY,   'Invalid gameobject type, must be a destructible building.'),
(@ENTRY+1, 'Gameobject %s (GUID: %u) damaged %u (actual health: %u).');
