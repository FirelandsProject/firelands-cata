-- Remove skinnable flag from all units
UPDATE `creature_template` SET `unit_flags`= `unit_flags` &~ 67108864;

-- Add missing firelands string
DELETE FROM `firelands_string` WHERE `entry`= 1189;
INSERT INTO `firelands_string` (`entry`, `content_default`) VALUES
(1189, 'No instances were found matching your input.');
