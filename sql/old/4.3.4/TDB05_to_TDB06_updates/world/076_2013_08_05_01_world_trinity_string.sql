DELETE FROM `firelands_string` WHERE `entry`=5038;
INSERT INTO `firelands_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
(5038, 'Unit Flags: %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

UPDATE `firelands_string` SET `content_default`=
'Unit Flags 2: %u.
Dynamic Flags: %u.
Faction Template: %u.' WHERE `entry`=542;
