UPDATE `creature_trainer` SET `MenuId`=10702, `OptionIndex`=0 WHERE `CreatureId`=35869;

DELETE FROM `gossip_menu_option` WHERE `MenuId`=10702;

INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcflag`, `VerifiedBuild`) VALUES
(10702, 0, 3, 'I am interested in warlock training.', 2544, 5, 16, 15050),
(10702, 1, 0, 'I wish to unlearn my talents.', 62295, 16, 16, 15050),
(10702, 2, 0, 'Learn about Dual Talent Specialization.', 33762, 20, 1, 0);
