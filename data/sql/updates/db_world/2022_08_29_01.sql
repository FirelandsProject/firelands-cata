UPDATE `creature_trainer` SET `MenuId`=10699, `OptionIndex`=0 WHERE `CreatureId`=35871;

DELETE FROM `gossip_menu_option` WHERE `MenuID`=10699;

INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcflag`, `VerifiedBuild`) VALUES
(10699, 0, 3, 'I would like training.', 3266, 5, 16, 15600),
(10699, 1, 0, 'I wish to unlearn my talents.', 62295, 16, 16, 15600),
(10699, 2, 0, 'Learn about Dual Talent Specialization.', 33762, 20, 1, 15600);
