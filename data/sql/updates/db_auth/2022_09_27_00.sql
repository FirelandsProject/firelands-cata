DELETE FROM `rbac_permissions` WHERE `id`=1434;
INSERT INTO `rbac_permissions` (`id`, `name`) VALUES
(1434, 'Command: anticheat');

DELETE FROM `rbac_linked_permissions` WHERE `linkedId`=1434 AND `id` IN (196, 197, 198);
INSERT INTO `rbac_linked_permissions` (`id`, `linkedId`) VALUES
(196, 1434),
(197, 1434),
(198, 1434);
