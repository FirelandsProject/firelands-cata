DELETE FROM `creature_trainer` WHERE `CreatureId`=35874;

INSERT INTO `creature_trainer` (`CreatureId`, `TrainerId`, `MenuId`, `OptionIndex`) VALUES
(35874, 15, 10697, 0);

DELETE FROM `gossip_menu_option` WHERE `MenuID`=10697;

INSERT INTO `gossip_menu_option` (`MenuId`, `OptionIndex`, `OptionIcon`, `OptionText`, `OptionBroadcastTextId`, `OptionType`, `OptionNpcflag`, `VerifiedBuild`) VALUES
(10697, 0, 3, "I seek training in the ways of the Hunter.", 3266, 5, 16, 15600),
(10697, 1, 0, "I wish to unlearn my talents.", 62295, 16, 16, 15600),
(10697, 2, 0, "Learn about Dual Talent Specialization.", 33762, 20, 1, 15600);
