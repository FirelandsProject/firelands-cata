/* new firelands_strings */
DELETE FROM `firelands_string` WHERE `entry` IN (5059,5060,5061);
INSERT INTO `firelands_string` (`entry`, `content_default`) VALUES
(5059, 'Mutes for account: %s'),
(5060, 'No mutes for account: %s'),
(5061, 'Mute Date: %20s Mutetime: %10u mins. Reason: %s Set by: %s');
