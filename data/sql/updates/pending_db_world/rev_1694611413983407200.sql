
--
DELETE FROM `creature` WHERE `id`=22519;
DELETE FROM `creature` WHERE  `guid` IN (86488,86489,86490);

DELETE FROM `creature_template_addon` WHERE `entry`=22521;
INSERT INTO `creature_template_addon` (`entry`,`bytes2`,`auras`) VALUES
(22521,1,'39383');

UPDATE `creature_template` SET `flags_extra` = 130 WHERE `entry` IN (17208,17305,17317,17316,22521);
UPDATE `creature_template` SET `flags_extra`='16777218' WHERE `entry` IN (17469,17211,21748,21664,21750,21683,21747,21682,21726,21160,21752,21684);
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37471', `spell4`='37474' WHERE  `entry`=21684; -- King Llane
UPDATE `creature_template` SET `spell1`='37148', `spell2`='30284', `spell3`='37462', `spell4`='37465' WHERE  `entry`=21683; -- Human Conjurer
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37455', `spell4`='37459' WHERE  `entry`=21682; -- Human Cleric
UPDATE `creature_template` SET `spell1`='37144', `spell2`='30284', `spell3`='37453', `spell4`='37498' WHERE  `entry`=21664; -- Human Charger
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37427', `spell4`='37432' WHERE  `entry`=21160; -- Conjured Water Elemental
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37406', `spell4`='37414' WHERE  `entry`=17211; -- Human Footman
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37472', `spell4`='37476' WHERE  `entry`=21752; -- Warchief Blackhand
UPDATE `creature_template` SET `spell1`='37148', `spell2`='30284', `spell3`='37463', `spell4`='37461' WHERE  `entry`=21750; -- Orc Warlock
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37456', `spell4`='37461' WHERE  `entry`=21747; -- Orc Necrolyte
UPDATE `creature_template` SET `spell1`='37144', `spell2`='30284', `spell3`='37454', `spell4`='37502' WHERE  `entry`=21748; -- Orc Wolf
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37428', `spell4`='37434' WHERE  `entry`=21726; -- Summoned Daemon
UPDATE `creature_template` SET `spell1`='37146', `spell2`='30284', `spell3`='37413', `spell4`='37416' WHERE  `entry`=17469; -- Orc Grunt

UPDATE `creature_template` SET `RegenHealth`=0, `BaseAttackTime`=3000 WHERE `entry` IN (21726,21748,21747,21750,21752,17469,21160,21664,21682,21684,21683,17211);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` IN (37465,37476,30012,37144,37148,37151,37152,37153,37472,37461,37454,37502,37428,37413,37471,37474,37459,37453,37498,37427,37406,39384,37462,37455,37463,37456,37144,37146,37148,30284,37469);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ScriptName`,`Comment`) VALUES
(13,1,37146,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,30012,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,37144,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,37148,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,37151,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,37152,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),
(13,1,37153,0,31,3,22519,0,'',"Move - Target Chess Piece: Karazhan Invisible Stalker"),

(13,3,30284,0,31,3,22519,0,'',"Change Facing - Target Chess Piece: Karazhan Invisible Stalker"),

(13,1,39384,0,31,3,21752,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,1,39384,1,31,3,21750,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,1,39384,2,31,3,21747,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,1,39384,3,31,3,21748,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,1,39384,4,31,3,21726,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,1,39384,5,31,3,17469,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,0,31,3,21683,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,1,31,3,21684,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,2,31,3,21682,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,3,31,3,21664,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,4,31,3,21160,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),
(13,2,39384,5,31,3,17211,0,'',"Alliance and Horde Chess Spell - Burning Flames - Target Alliance and Horde Pieces"),

(13,1,37471,0,31,3,21683,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),
(13,1,37471,1,31,3,21684,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),
(13,1,37471,2,31,3,21682,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),
(13,1,37471,3,31,3,21664,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),
(13,1,37471,4,31,3,21160,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),
(13,1,37471,5,31,3,17211,0,'',"Alliance Chess Spell - Heroism - Target Alliance Pieces"),

(13,1,37459,0,31,3,21752,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),
(13,1,37459,1,31,3,21750,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),
(13,1,37459,2,31,3,21747,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),
(13,1,37459,3,31,3,21748,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),
(13,1,37459,4,31,3,21726,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),
(13,1,37459,5,31,3,17469,0,'',"Alliance Chess Spell - Holy Lance - Target Horde Pieces"),

(13,1,37453,0,31,3,21752,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),
(13,1,37453,1,31,3,21750,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),
(13,1,37453,2,31,3,21747,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),
(13,1,37453,3,31,3,21748,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),
(13,1,37453,4,31,3,21726,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),
(13,1,37453,5,31,3,17469,0,'',"Alliance Chess Spell - Smash - Target Horde Pieces"),

(13,1,37427,0,31,3,21752,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),
(13,1,37427,1,31,3,21750,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),
(13,1,37427,2,31,3,21747,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),
(13,1,37427,3,31,3,21748,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),
(13,1,37427,4,31,3,21726,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),
(13,1,37427,5,31,3,17469,0,'',"Alliance Chess Spell - Geyser - Target Horde Pieces"),

(13,1,37474,0,31,3,21752,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),
(13,1,37474,1,31,3,21750,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),
(13,1,37474,2,31,3,21747,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),
(13,1,37474,3,31,3,21748,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),
(13,1,37474,4,31,3,21726,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),
(13,1,37474,5,31,3,17469,0,'',"Alliance Chess Spell - Sweep - Target Horde Pieces"),

(13,1,37465,0,31,3,21752,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),
(13,1,37465,1,31,3,21750,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),
(13,1,37465,2,31,3,21747,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),
(13,1,37465,3,31,3,21748,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),
(13,1,37465,4,31,3,21726,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),
(13,1,37465,5,31,3,17469,0,'',"Alliance Chess Spell - Rain of Fire - Target Horde Pieces"),

(13,1,37498,0,31,3,21752,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),
(13,1,37498,1,31,3,21750,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),
(13,1,37498,2,31,3,21747,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),
(13,1,37498,3,31,3,21748,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),
(13,1,37498,4,31,3,21726,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),
(13,1,37498,5,31,3,17469,0,'',"Alliance Chess Spell - Stomp - Target Horde Pieces"),

(13,1,37406,0,31,3,21752,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),
(13,1,37406,1,31,3,21750,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),
(13,1,37406,2,31,3,21747,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),
(13,1,37406,3,31,3,21748,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),
(13,1,37406,4,31,3,21726,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),
(13,1,37406,5,31,3,17469,0,'',"Alliance Chess Spell - Heroic Blow - Target Horde Pieces"),

(13,1,37472,0,31,3,21752,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),
(13,1,37472,1,31,3,21750,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),
(13,1,37472,2,31,3,21747,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),
(13,1,37472,3,31,3,21748,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),
(13,1,37472,4,31,3,21726,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),
(13,1,37472,5,31,3,17469,0,'',"Horde Chess Spell - Bloodlust - Target Horde Pieces"),

(13,1,37461,0,31,3,21683,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),
(13,1,37461,1,31,3,21684,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),
(13,1,37461,2,31,3,21682,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),
(13,1,37461,3,31,3,21664,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),
(13,1,37461,4,31,3,21160,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),
(13,1,37461,5,31,3,17211,0,'',"Horde Chess Spell - Shadow Spear - Target Alliance Pieces"),

(13,1,37502,0,31,3,21683,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),
(13,1,37502,1,31,3,21684,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),
(13,1,37502,2,31,3,21682,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),
(13,1,37502,3,31,3,21664,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),
(13,1,37502,4,31,3,21160,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),
(13,1,37502,5,31,3,17211,0,'',"Horde Chess Spell - Howl - Target Alliance Pieces"),

(13,1,37428,0,31,3,21683,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),
(13,1,37428,1,31,3,21684,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),
(13,1,37428,2,31,3,21682,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),
(13,1,37428,3,31,3,21664,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),
(13,1,37428,4,31,3,21160,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),
(13,1,37428,5,31,3,17211,0,'',"Horde Chess Spell - Hellfire - Target Alliance Pieces"),

(13,1,37476,0,31,3,21683,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),
(13,1,37476,1,31,3,21684,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),
(13,1,37476,2,31,3,21682,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),
(13,1,37476,3,31,3,21664,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),
(13,1,37476,4,31,3,21160,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),
(13,1,37476,5,31,3,17211,0,'',"Horde Chess Spell - Cleave - Target Alliance Pieces"),

(13,1,37469,0,31,3,21683,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),
(13,1,37469,1,31,3,21684,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),
(13,1,37469,2,31,3,21682,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),
(13,1,37469,3,31,3,21664,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),
(13,1,37469,4,31,3,21160,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),
(13,1,37469,5,31,3,17211,0,'',"Horde Chess Spell - Poison Cloud - Target Alliance Pieces"),

(13,1,37454,0,31,3,21683,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),
(13,1,37454,1,31,3,21684,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),
(13,1,37454,2,31,3,21682,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),
(13,1,37454,3,31,3,21664,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),
(13,1,37454,4,31,3,21160,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),
(13,1,37454,5,31,3,17211,0,'',"Horde Chess Spell - Bite - Target Alliance Pieces"),

(13,1,37413,0,31,3,21683,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces"),
(13,1,37413,1,31,3,21684,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces"),
(13,1,37413,2,31,3,21682,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces"),
(13,1,37413,3,31,3,21664,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces"),
(13,1,37413,4,31,3,21160,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces"),
(13,1,37413,5,31,3,17211,0,'',"Horde Chess Spell - Vicious Strike - Target Alliance Pieces");

DELETE FROM `creature_text` WHERE `CreatureID`=16816;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(16816,0,0,'Very well. Let the game begin.',14,0,100,0,0,0,0,78000,0,'Echo of Medivh - EventBegin'),
(16816,1,0,'Perhaps a change is in order.',14,0,100,0,0,0,0,78001,0,'Echo of Medivh - Cheat 1'),
(16816,1,1,'Time for an alternative scenario.',14,0,100,0,0,0,0,78002,0,'Echo of Medivh - Cheat 2'),
(16816,1,2,'One must not become too complacent.',14,0,100,0,0,0,0,78003,0,'Echo of Medivh - Cheat 3'),
(16816,2,0,'%s cheats',16,0,100,0,0,0,0,78004,0,'Echo of Medivh - CheatEmote'),
(16816,3,0,'Let us see.',14,0,100,0,0,0,0,78005,0,'Echo of Medivh - Player Loose Pawn 1'),
(16816,3,1,'A transparent stratagem.',14,0,100,0,0,0,0,78006,0,'Echo of Medivh - Player Loose Pawn 2'),
(16816,3,2,'Ah, the wheels have begun to turn.',14,0,100,0,0,0,0,78007,0,'Echo of Medivh - Player Loose Pawn 3'),
(16816,4,0,'Foolish! Very foolish!',14,0,100,0,0,0,0,78008,0,'Echo of Medivh - Player Loose Rook'),
(16816,5,0,'Yes... all according to plan.',14,0,100,0,0,0,0,78009,0,'Echo of Medivh - Player Loose Knight'),
(16816,6,0,'The slightest loss of concentration is all it takes.',14,0,100,0,0,0,0,78010,0,'Echo of Medivh - Player Loose Bishop'),
(16816,7,0,'Now it gets interesting.',14,0,100,0,0,0,0,78011,0,'Echo of Medivh - Player Loose Queen'),
(16816,8,0,'As it should be.',14,0,100,0,0,0,0,78012,0,'Echo of Medivh - Player Loose King'),
(16816,9,0,'Hmm.',14,0,100,0,0,0,0,78013,0,'Echo of Medivh - Medivh Loose Pawn 1'),
(16816,9,1,'No matter.',14,0,100,0,0,0,0,78014,0,'Echo of Medivh - Medivh Loose Pawn 2'),
(16816,9,2,'Interesting.',14,0,100,0,0,0,0,78015,0,'Echo of Medivh - Medivh Loose Pawn 3'),
(16816,10,0,'A minor concern.',14,0,100,0,0,0,0,78016,0,'Echo of Medivh - Medivh Loose Rook'),
(16816,11,0,'Yes...of course.',14,0,100,0,0,0,0,78017,0,'Echo of Medivh - Medivh Loose Knight'),
(16816,12,0,'A necessary sacrifice.',14,0,100,0,0,0,0,78018,0,'Echo of Medivh - Medivh Loose Bishop'),
(16816,13,0,'Ahh, I should have known.',14,0,100,0,0,0,0,78019,0,'Echo of Medivh - Medivh Loose Queen'),
(16816,14,0,'And so, the end draws near',14,0,100,0,0,0,0,78020,0,'Echo of Medivh - Medivh Loose King'),
(16816,15,0,'Nothing less than perfection will do.',14,0,100,0,0,0,0,78021,0,'Echo of Medivh - Checkmate 1'),
(16816,15,1,'And so it ends.',14,0,100,0,0,0,0,78022,0,'Echo of Medivh - Checkmate 2'),
(16816,16,0,'The halls of Karazhan shake, as the curse binding the doors of the Gamesman\'s Hall is lifted.',16,0,100,0,0,0,0,78023,0,'Echo of Medivh - Event Ended');

DELETE FROM `broadcast_text` WHERE `ID` IN (78000,78001,78002,78003,78004,78005,78006,78007,78008,78009,78010,78011,78012,78013,78014,78015,78016,78017,78018,78019,78020,78021,78022,78023);
INSERT INTO `broadcast_text` (`ID`, `LanguageID`, `Text`, `Text1`, `EmoteID1`, `EmoteID2`, `EmoteID3`, `EmoteDelay1`, `EmoteDelay2`, `EmoteDelay3`, `SoundEntriesID`, `EmotesID`, `Flags`, `VerifiedBuild`) VALUES 
(78000, 0, 'Very well. Let the game begin.', 'Very well. Let the game begin.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78001, 0, 'Perhaps a change is in order.', 'Perhaps a change is in order.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78002, 0, 'Time for an alternative scenario.', 'Time for an alternative scenario.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78003, 0, 'One must not become too complacent.', 'One must not become too complacent.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78004, 0, '%s cheats', '%s cheats', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78005, 0, 'Let us see.', 'Let us see.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78006, 0, 'A transparent stratagem.', 'A transparent stratagem.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78007, 0, 'Ah, the wheels have begun to turn.', 'Ah, the wheels have begun to turn.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78008, 0, 'Foolish! Very foolish!', 'Foolish! Very foolish!', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78009, 0, 'Yes... all according to plan.', 'Yes... all according to plan.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78010, 0, 'The slightest loss of concentration is all it takes.', 'The slightest loss of concentration is all it takes.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78011, 0, 'Now it gets interesting.', 'Now it gets interesting.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78012, 0, 'As it should be.', 'As it should be.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78013, 0, 'Hmm.', 'Hmm.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78014, 0, 'No matter.', 'No matter.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78015, 0, 'Interesting.', 'Interesting.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78016, 0, 'A minor concern.', 'A minor concern.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78017, 0, 'Yes...of course.', 'Yes...of course.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78018, 0, 'A necessary sacrifice.', 'A necessary sacrifice.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78019, 0, 'Ahh, I should have known.', 'Ahh, I should have known.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78020, 0, 'And so, the end draws near', 'And so, the end draws near', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78021, 0, 'Nothing less than perfection will do.', 'Nothing less than perfection will do.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78022, 0, 'And so it ends.', 'And so it ends.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
(78023, 0, 'The halls of Karazhan shake, as the curse binding the doors of the Gamesman\'s Hall is lifted.', 'The halls of Karazhan shake, as the curse binding the doors of the Gamesman\'s Hall is lifted.', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0);

DELETE FROM `gossip_menu_option` WHERE `menuid` IN (8404,7413,8354,8345,8346,8347,8348,8349,8355,8362,8366,8367,8368);
UPDATE `creature_template` SET `npcflag`=0 WHERE `entry` IN (17469,17211,21748,21664,21750,21683,21747,21682,21726,21160,21752,21684);
