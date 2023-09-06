--
DELETE FROM command WHERE name IN ('disable add item', 'disable remove item');
INSERT INTO command (name, permission, help) VALUES
('disable add item', 875, 'Syntax: .disable add item #itemId #flag'),
('disable remove item', 876, 'Syntax: .disable remove item #itemId');
