DELETE FROM `firelands_string` WHERE `entry` IN (5022, 5023);
INSERT INTO `firelands_string` (`entry`, `content_default`) VALUES
(5022, 'Granting ownership to first person that joins the channel \"%s\": Enabled.'),
(5023, 'Granting ownership to first person that joins the channel \"%s\": Disabled.');
