/*
	(FIX/QUEST): Life of the party (14153).
*/
SET @GOBLIN_MODEL_1= 35186;
SET @GOBLIN_MODEL_2= 35175;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=26 AND `SourceGroup` IN (379, 169) AND `SourceEntry`= 4765;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry` IN (66909, 66910, 66911, 66912, 66913);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(26, 379, 4765, 0, 0, 9, 0, 14153, 0, 0, 0, 0, 0, "", "Set Phase 379 in area 4765; Kezan, Quest Life of the party (14153)"),
(26, 169, 4765, 0, 0, 9, 0, 14153, 0, 0, 0, 0, 0, "", "Set Phase 169 in area 4765; Kezan, Quest Life of the party (14153)"),

(17, 0, 66909, 0, 0, 31, 1, 3, @GOBLIN_MODEL_2, 0, 0, 0, 0, "", "Allow Bubbly only on this specific target - Kezan Partygoer"),
(17, 0, 66909, 0, 0, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 0, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 0, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 0, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Bubbly - Handle Error - Missing aura"),

(17, 0, 66909, 0, 1, 31, 1, 3, @GOBLIN_MODEL_1, 0, 0, 0, 0, "", "Allow Bubbly only on this specific target - Kezan Partygoer"),
(17, 0, 66909, 0, 1, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 1, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 1, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Bubbly - Handle Error - Missing aura"),
(17, 0, 66909, 0, 1, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Bubbly - Handle Error - Missing aura"),

(17, 0, 66910,  0,  0, 31, 1, 3, @GOBLIN_MODEL_2, 0, 0, 0, 0, "", "Allow Bucket only on this specific target - Kezan Partygoer"),
(17, 0, 66910, 0, 0, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 0, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 0, 1, 1, 75048, 0, 0, 1, 209, 71, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 0, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 1, 31, 1, 3, @GOBLIN_MODEL_1, 0, 0, 0, 0, "", "Allow Bucket only on this specific target - Kezan Partygoer"),
(17, 0, 66910, 0, 1, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 1, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 1, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Bucket - Handle Error - Missing aura"),
(17, 0, 66910, 0, 1, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Bucket - Handle Error - Missing aura"),

(17, 0, 66911, 0, 0, 31, 1, 3, @GOBLIN_MODEL_2, 0, 0, 0, 0, "", "Allow Dance only on this specific target - Kezan Partygoer"),
(17, 0, 66911, 0, 0, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 0, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 0, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 0, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 1, 31, 1, 3, @GOBLIN_MODEL_1, 0, 0, 0, 0, "", "Allow Dance only on this specific target - Kezan Partygoer"),
(17, 0, 66911, 0, 1, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 1, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 1, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Dance - Handle Error - Missing aura"),
(17, 0, 66911, 0, 1, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Dance - Handle Error - Missing aura"),

(17, 0, 66912, 0, 0, 31, 1, 3, @GOBLIN_MODEL_2, 0, 0, 0, 0, "", "Allow Fireworks only on this specific target - Kezan Partygoer"),
(17, 0, 66912, 0, 0, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 0, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 0, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 0, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 1, 31, 1, 3, @GOBLIN_MODEL_1, 0, 0, 0, 0, "", "Allow Fireworks only on this specific target - Kezan Partygoer"),
(17, 0, 66912, 0, 1, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 1, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 1, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Fireworks - Handle Error - Missing aura"),
(17, 0, 66912, 0, 1, 1, 1, 75050, 0, 0, 1, 209, 73, "", "Fireworks - Handle Error - Missing aura"),

(17, 0, 66913, 0, 0, 31, 1, 3, @GOBLIN_MODEL_2, 0, 0, 0, 0, "", "Allow Hors D'oeuvres on this specific target - Kezan Partygoer"),
(17, 0, 66913, 0, 0, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 0, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 0, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 0, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 1, 31, 1, 3, @GOBLIN_MODEL_1, 0, 0, 0, 0, "", "Allow Hors D'oeuvres on this specific target - Kezan Partygoer"),
(17, 0, 66913, 0, 1, 1, 1, 75044, 0, 0, 1, 209, 70, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 1, 1, 1, 75046, 0, 0, 1, 209, 71, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 1, 1, 1, 75048, 0, 0, 1, 209, 72, "", "Hors D'oeuvres - Handle Error - Missing aura"),
(17, 0, 66913, 0, 1, 1, 1, 75042, 0, 0, 1, 209, 69, "", "Hors D'oeuvres - Handle Error - Missing aura");

DELETE FROM `phase_area` WHERE `AreaId`=4765 AND `PhaseId` IN (379, 169);
INSERT INTO `phase_area` (`AreaId`, `PhaseId`, `Comment`) VALUES
(4765, 379, "Kezan (Quest 14153)"),
(4765, 169, "Kezan (Quest 14153)");

UPDATE `creature_template` SET `AIName` = "SmartAI" WHERE `entry`=35175; -- Set AI to Model 2

DELETE FROM `creature_text` WHERE `CreatureID` IN (35175, 35186);
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `SoundType`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(@GOBLIN_MODEL_1, 0, 1, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, 0, 35425, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 0, 2, "How do you like my moves, $n?", 12, 0, 100, 0, 0, 0, 0, 35426, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 0, 3, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, 0, 35427, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 0, 4, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, 0, 35428, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 1, 0, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, 0, 40223, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 1, 1, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, 0, 35424, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 1, 2, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, 0, 35422, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 1, 3, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, 0, 35423, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 0, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, 0, 40222, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 1, "Thanks for the refill, $g sir : ma'am;!", 12, 0, 100, 0, 0, 0, 0, 35418, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 2, "A fresh glass of bubbly. Just what the doctor ordered, $n.", 12, 0, 100, 0, 0, 0, 0, 35417, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 3, "This sparkling white wine is delicious! Wherever did you get it?", 12, 0, 100, 0, 0, 0, 0, 35419, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 4, "I think this one will have to be my last. I'm driving home after the party.", 12, 0, 100, 0, 0, 0, 0, 35420, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 2, 5, "Thanksh!", 12, 0, 100, 0, 0, 0, 0, 35421, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 3, 0, "I love fireworks!", 12, 0, 100, 0, 0, 0, 0, 40225, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 3, 1, "Wow! That sure beats this puny, little sparkler!", 12, 0, 100, 0, 0, 0, 0, 35429, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 3, 2, "You really stop at no expense, $n! Amazing!", 12, 0, 100, 0, 0, 0, 0, 35430, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 3, 3, "Best... Party... Evar!", 12, 0, 100, 0, 0, 0, 0, 35431, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 3, 4, "Woo hoo, fireworks! More, more!", 12, 0, 100, 0, 0, 0, 0, 35432, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 4, 0, "This is delicious! Are there more hors d'oeuvres?", 12, 0, 100, 0, 0, 0, 0, 40226, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 4, 1, "Nom, nom, nom!", 12, 0, 100, 0, 0, 0, 0, 35436, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 4, 2, "Finger licking good!", 12, 0, 100, 0, 0, 0, 0, 35435, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 4, 3, "Thanks. I was almost out. So hungry!", 12, 0, 100, 0, 0, 0, 0, 35433, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 4, 4, "These are the most delicious hors d'oeurves I have ever tasted. You must share your recipe, $n!", 12, 0, 100, 0, 0, 0, 0, 35434, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 0, "If only I had someone to dance with.", 12, 0, 100, 0, 0, 0, 0, 40224, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 1, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, 0, 35425, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 2, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, 0, 35427, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 3, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, 0, 35428, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 4, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, 0, 40223, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 5, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, 0, 35424, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 6, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, 0, 35422, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 7, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, 0, 35423, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_1, 5, 8, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, 0, 40222, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 0, 1, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, 0, 35425, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 0, 2, "How do you like my moves, $n?", 12, 0, 100, 0, 0, 0, 0, 35426, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 0, 3, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, 0, 35427, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 0, 4, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, 0, 35428, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 1, 0, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, 0, 40223, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 1, 1, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, 0, 35424, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 1, 2, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, 0, 35422, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 1, 3, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, 0, 35423, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 0, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, 0, 40222, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 1, "Thanks for the refill, $g sir : ma'am;!", 12, 0, 100, 0, 0, 0, 0, 35418, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 2, "A fresh glass of bubbly. Just what the doctor ordered, $n.", 12, 0, 100, 0, 0, 0, 0, 35417, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 3, "This sparkling white wine is delicious! Wherever did you get it?", 12, 0, 100, 0, 0, 0, 0, 35419, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 4, "I think this one will have to be my last. I'm driving home after the party.", 12, 0, 100, 0, 0, 0, 0, 35420, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 2, 5, "Thanksh!", 12, 0, 100, 0, 0, 0, 0, 35421, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 3, 0, "I love fireworks!", 12, 0, 100, 0, 0, 0, 0, 40225, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 3, 1, "Wow! That sure beats this puny, little sparkler!", 12, 0, 100, 0, 0, 0, 0, 35429, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 3, 2, "You really stop at no expense, $n! Amazing!", 12, 0, 100, 0, 0, 0, 0, 35430, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 3, 3, "Best... Party... Evar!", 12, 0, 100, 0, 0, 0, 0, 35431, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 3, 4, "Woo hoo, fireworks! More, more!", 12, 0, 100, 0, 0, 0, 0, 35432, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 4, 0, "This is delicious! Are there more hors d'oeuvres?", 12, 0, 100, 0, 0, 0, 0, 40226, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 4, 1, "Nom, nom, nom!", 12, 0, 100, 0, 0, 0, 0, 35436, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 4, 2, "Finger licking good!", 12, 0, 100, 0, 0, 0, 0, 35435, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 4, 3, "Thanks. I was almost out. So hungry!", 12, 0, 100, 0, 0, 0, 0, 35433, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 4, 4, "These are the most delicious hors d'oeurves I have ever tasted. You must share your recipe, $n!", 12, 0, 100, 0, 0, 0, 0, 35434, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 0, "If only I had someone to dance with.", 12, 0, 100, 0, 0, 0, 0, 40224, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 1, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, 0, 35425, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 2, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, 0, 35427, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 3, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, 0, 35428, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 4, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, 0, 40223, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 5, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, 0, 35424, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 6, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, 0, 35422, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 7, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, 0, 35423, 0, "Kezan Partygoer"),
(@GOBLIN_MODEL_2, 5, 8, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, 0, 40222, 0, "Kezan Partygoer");



DELETE FROM `smart_scripts` WHERE `entryorguid` IN (35175, 35186) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@GOBLIN_MODEL_1, 0, 0, 1, 8, 0, 100, 0, 66911, 0, 15000, 15000, 0, 5, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Play Emote 10"),
(@GOBLIN_MODEL_1, 0, 1, 2, 61, 0, 100, 0, 0, 0, 15000, 15000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Say Line 0"),
(@GOBLIN_MODEL_1, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75046, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Remove Aura Dance"),
(@GOBLIN_MODEL_1, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_1, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Get Credit"),

(@GOBLIN_MODEL_1, 0, 5, 6, 8, 0, 100, 0, 66910, 0, 15000, 15000, 0, 5, 17, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Play Emote 17"),
(@GOBLIN_MODEL_1, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Say Line 1"),
(@GOBLIN_MODEL_1, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75044, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Remove Aura Bucket"),
(@GOBLIN_MODEL_1, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66931, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Summon Bucket"),
(@GOBLIN_MODEL_1, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_1, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Get Credit"),

(@GOBLIN_MODEL_1, 0, 11, 12, 8, 0, 100, 0, 66909, 0, 12000, 12000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Play Emote 7"),
(@GOBLIN_MODEL_1, 0, 12, 13, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Say Line 2"),
(@GOBLIN_MODEL_1, 0, 13, 14, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75042, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Remove Aura Bubbly"),
(@GOBLIN_MODEL_1, 0, 14, 15, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_1, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Get Credit"),

(@GOBLIN_MODEL_1, 0, 16, 17, 8, 0, 100, 0, 66912, 0, 12000, 12000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Play Emote 7"),
(@GOBLIN_MODEL_1, 0, 17, 18, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Say Line 3"),
(@GOBLIN_MODEL_1, 0, 18, 19, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75048, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Remove Aura Fireworks"),
(@GOBLIN_MODEL_1, 0, 19, 20, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_1, 0, 20, 21, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66919, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Cast Fireworks"),
(@GOBLIN_MODEL_1, 0, 21, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Get Credit"),

(@GOBLIN_MODEL_1, 0, 22, 23, 8, 0, 100, 0, 66913, 0, 10000, 10000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Play Emote 7"),
(@GOBLIN_MODEL_1, 0, 23, 24, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Say Line 4"),
(@GOBLIN_MODEL_1, 0, 24, 25, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75050, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Remove Aura Hors D'oeuvres"),
(@GOBLIN_MODEL_1, 0, 25, 26, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_1, 0, 26, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Get Credit"),

(@GOBLIN_MODEL_1, 0, 27, 0, 64, 0, 100, 0, 0, 0, 0, 0, 0, 10, 1, 3, 5, 6, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Gossip Hello - Play Random Emote (1, 3, 5, 6)"),
(@GOBLIN_MODEL_1, 0, 28, 0, 1, 0,  60,  0,  2000,  8000,  10000,  20000,  0,  1,  5,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  "Kezan Partygoer - Out of Combat - Say Line 5"),

(@GOBLIN_MODEL_2, 0, 0, 1, 8, 0, 100, 0, 66911, 0, 15000, 15000, 0, 5, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Play Emote 10"),
(@GOBLIN_MODEL_2, 0, 1, 2, 61, 0, 100, 0, 0, 0, 15000, 15000, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Say Line 0"),
(@GOBLIN_MODEL_2, 0, 2, 3, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75046, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Remove Aura Dance"),
(@GOBLIN_MODEL_2, 0, 3, 4, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_2, 0, 4, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Dance' - Get Credit"),

(@GOBLIN_MODEL_2, 0, 5, 6, 8, 0, 100, 0, 66910, 0, 15000, 15000, 0, 5, 17, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Play Emote 17"),
(@GOBLIN_MODEL_2, 0, 6, 7, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Say Line 1"),
(@GOBLIN_MODEL_2, 0, 7, 8, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75044, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Remove Aura Bucket"),
(@GOBLIN_MODEL_2, 0, 8, 9, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66931, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Summon Bucket"),
(@GOBLIN_MODEL_2, 0, 9, 10, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_2, 0, 10, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bucket' - Get Credit"),

(@GOBLIN_MODEL_2, 0, 11, 12, 8, 0, 100, 0, 66909, 0, 12000, 12000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Play Emote 7"),
(@GOBLIN_MODEL_2, 0, 12, 13, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Say Line 2"),
(@GOBLIN_MODEL_2, 0, 13, 14, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75042, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Remove Aura Bubbly"),
(@GOBLIN_MODEL_2, 0, 14, 15, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_2, 0, 15, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Get Credit"),

(@GOBLIN_MODEL_2, 0, 16, 17, 8, 0, 100, 0, 66912, 0, 12000, 12000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Play Emote 7"),
(@GOBLIN_MODEL_2, 0, 17, 18, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Say Line 3"),
(@GOBLIN_MODEL_2, 0, 18, 19, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75048, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Remove Aura Fireworks"),
(@GOBLIN_MODEL_2, 0, 19, 20, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_2, 0, 20, 21, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66919, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Fireworks' - Cast Fireworks"),
(@GOBLIN_MODEL_2, 0, 21, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Bubbly' - Get Credit"),

(@GOBLIN_MODEL_2, 0, 22, 23, 8, 0, 100, 0, 66913, 0, 10000, 10000, 0, 5, 7, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Play Emote 7"),
(@GOBLIN_MODEL_2, 0, 23, 24, 61, 0, 100, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Say Line 4"),
(@GOBLIN_MODEL_2, 0, 24, 25, 61, 0, 100, 0, 0, 0, 0, 0, 0, 28, 75050, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Remove Aura Hors D'oeuvres"),
(@GOBLIN_MODEL_2, 0, 25, 26, 61, 0, 100, 0, 0, 0, 0, 0, 0, 11, 66916, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Apply Aura Happy Partygoer"),
(@GOBLIN_MODEL_2, 0, 26, 0, 61, 0, 100, 0, 0, 0, 0, 0, 0, 33, @GOBLIN_MODEL_2, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Spellhit 'Hors D'oeuvres' - Get Credit"),

(@GOBLIN_MODEL_2, 0, 27, 0, 64, 0, 100, 0, 0, 0, 0, 0, 0, 10, 1, 3, 5, 6, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, "Kezan Partygoer - On Gossip Hello - Play Random Emote (1, 3, 5, 6)"),
(@GOBLIN_MODEL_2, 0, 28, 0, 1, 0,  60,  0,  2000,  8000,  10000,  20000,  0,  1,  5,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  "Kezan Partygoer - Out of Combat - Say Line 5");
