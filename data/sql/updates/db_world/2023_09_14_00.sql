--
DELETE FROM command WHERE name IN ('disable add item', 'disable remove item');
INSERT INTO command (name, permission, help) VALUES
('disable add item', 875, 'Syntax: .disable add item #itemId #flag'),
('disable remove item', 876, 'Syntax: .disable remove item #itemId');


DELETE FROM disables WHERE sourceType = 9;
INSERT INTO disables (sourceType, entry, flags, comment, params_0, params_1) VALUES
(9,  2586, 3, 'Disable item 2586 (GameMaster\'s Robe) for Auction House Player & Bot', "", ""),
(9, 11508, 3, 'Disable item 11508 (GameMaster\'s Slippers) for Auction House Player & Bot', "", ""),
(9, 12064, 3, 'Disable item 12064 (GameMaster\'s Hood) for Auction House Player & Bot', "", ""),
(9,  7192, 2, 'Disable item 7192 (Plans: Goblin Rocket Boots) for Auction House Bot', "", "");
