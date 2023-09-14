--
DELETE FROM rbac_permissions WHERE id IN (875, 876);
INSERT INTO rbac_permissions (id, name) VALUES
(875, 'Command: disable add item'),
(876, 'Command: disable remove item');

DELETE FROM rbac_linked_permissions WHERE id = 196 AND linkedId IN (875, 876);
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES
(196, 875),
(196, 876);
