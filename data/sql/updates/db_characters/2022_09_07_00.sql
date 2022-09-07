DELETE FROM `updates`;

DELETE FROM `updates_include`;
INSERT INTO `updates_include` (`path`, `state`) VALUES
('$/data/sql/updates/db_characters', 'RELEASED');
