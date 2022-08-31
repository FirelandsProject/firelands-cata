DELETE FROM `creature_template_locale` WHERE `entry`=34830 AND `locale` IN ('esMX', 'esES');
INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `FemaleName`, `Title`, `VerifiedBuild`) VALUES
(34830, 'esMX', 'Trol desafiante', '', '', 18019),
(34830, 'esES', 'Trol desafiante', '', '', 18019);

UPDATE `creature_text` SET `BroadcastTextId`=35115 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=0;
UPDATE `creature_text` SET `BroadcastTextId`=40315 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=1;
UPDATE `creature_text` SET `BroadcastTextId`=35113 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=2;
UPDATE `creature_text` SET `BroadcastTextId`=35114 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=3;
UPDATE `creature_text` SET `BroadcastTextId`=35112 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=4;
UPDATE `creature_text` SET `BroadcastTextId`=40313 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=5;
UPDATE `creature_text` SET `BroadcastTextId`=40312 WHERE `CreatureID`=34830 AND `GroupID`=0 AND `ID`=6;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=19 AND `SourceEntry` IN (14069, 14075, 25473, 28349, 14071, 24567, 24488, 24502, 24503, 24520, 14070, 26712, 14113, 14153, 14115, 14116, 14120, 14121, 14122, 14123, 14124, 14125, 14126);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(19, 0, 14069, 0, 0, 8, 0, 14138, 0, 0, 0, 0, 0, '', 'Enable quest 14069, only if the player has completed quest 14138.'),
(19, 0, 14075, 0, 0, 8, 0, 14138, 0, 0, 0, 0, 0, '', 'Enable quest 14075, only if the player has completed quest 14138.'),
(19, 0, 25473, 0, 0, 8, 0, 14075, 0, 0, 0, 0, 0, '', 'Enable quest 25473, only if the player has completed quest 14075.'),
(19, 0, 28349, 0, 0, 8, 0, 25473, 0, 0, 0, 0, 0, '', 'Enable quest 28349, only if the player has completed quest 25473.'),
(19, 0, 14071, 0, 0, 8, 0, 28349, 0, 0, 0, 0, 0, '', 'Enable quest 14071, only if the player has completed quest 28349.'),
(19, 0, 24567, 0, 0, 8, 0, 14071, 0, 0, 0, 0, 0, '', 'Enable quest 24567, only if the player has completed quest 14071.'),
(19, 0, 24488, 0, 0, 8, 0, 24567, 0, 0, 0, 0, 0, '', 'Enable quest 24488, only if the player has completed quest 24567.'),
(19, 0, 24502, 0, 0, 8, 0, 24488, 0, 0, 0, 0, 0, '', 'Enable quest 24502, only if the player has completed quest 24488.'),
(19, 0, 24503, 0, 0, 8, 0, 24502, 0, 0, 0, 0, 0, '', 'Enable quest 25473, only if the player has completed quest 24502.'),
(19, 0, 24520, 0, 0, 8, 0, 24503, 0, 0, 0, 0, 0, '', 'Enable quest 24520, only if the player has completed quest 24503.'),
(19, 0, 14070, 0, 0, 8, 0, 24520, 0, 0, 0, 0, 0, '', 'Enable quest 14070, only if the player has completed quest 24520.'),
(19, 0, 26712, 0, 0, 8, 0, 24520, 0, 0, 0, 0, 0, '', 'Enable quest 26712, only if the player has completed quest 24520.'),
(19, 0, 14113, 0, 0, 8, 0, 24502, 0, 0, 0, 0, 0, '', 'Enable quest 14113, only if the player has completed quest 24502.'),
(19, 0, 14153, 0, 0, 8, 0, 24502, 0, 0, 0, 0, 0, '', 'Enable quest 14153, only if the player has completed quest 24502.'),
(19, 0, 14115, 0, 0, 8, 0, 14113, 0, 0, 0, 0, 0, '', 'Enable quest 14115, only if the player has completed quest 14113.'),
(19, 0, 14116, 0, 0, 8, 0, 14115, 0, 0, 0, 0, 0, '', 'Enable quest 14116, only if the player has completed quest 14115.'),
(19, 0, 14120, 0, 0, 8, 0, 14116, 0, 0, 0, 0, 0, '', 'Enable quest 14120, only if the player has completed quest 14116.'),
(19, 0, 14122, 0, 0, 8, 0, 14120, 0, 0, 0, 0, 0, '', 'Enable quest 14122, only if the player has completed quest 14120.'),
(19, 0, 14123, 0, 0, 8, 0, 14122, 0, 0, 0, 0, 0, '', 'Enable quest 14122, only if the player has completed quest 14122.'),
(19, 0, 14121, 0, 0, 8, 0, 14122, 0, 0, 0, 0, 0, '', 'Enable quest 14121, only if the player has completed quest 14122.'),
(19, 0, 14124, 0, 0, 8, 0, 14122, 0, 0, 0, 0, 0, '', 'Enable quest 14124, only if the player has completed quest 14122.'),
(19, 0, 14125, 0, 0, 8, 0, 14124, 0, 0, 0, 0, 0, '', 'Enable quest 14125, only if the player has completed quest 14124.'),
(19, 0, 14126, 0, 0, 8, 0, 14125, 0, 0, 0, 0, 0, '', 'Enable quest 14126, only if the player has completed quest 14125.');
