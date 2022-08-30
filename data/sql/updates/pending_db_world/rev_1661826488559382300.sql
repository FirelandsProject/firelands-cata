
/*KEZAN QUEST*/
UPDATE `quest_template_addon` SET `PrevQuestID` = '0' WHERE  `ID` = '14138'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14138' WHERE  `ID` = '14069';  
UPDATE `quest_template_addon` SET `PrevQuestID` = '14138' WHERE  `ID` = '14075'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14075' WHERE  `ID` = '25473'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '25473' WHERE  `ID` = '28349'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '28349' WHERE  `ID` = '14071'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14071' WHERE  `ID` = '24567'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24567' WHERE  `ID` = '24488'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24488' WHERE  `ID` = '24502'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24502' WHERE  `ID` = '24503'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24503' WHERE  `ID` = '24520'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24520' WHERE  `ID` = '14070'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '24520' WHERE  `ID` = '26712'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '26712' WHERE  `ID` = '14113'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '26712' WHERE  `ID` = '14153'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14113' WHERE  `ID` = '14115'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14115' WHERE  `ID` = '14116';
UPDATE `quest_template_addon` SET `PrevQuestID` = '14116' WHERE  `ID` = '14120'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14120' WHERE  `ID` = '14122';
UPDATE `quest_template_addon` SET `PrevQuestID` = '14122' WHERE  `ID` = '14123'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14122' WHERE  `ID` = '14121';
UPDATE `quest_template_addon` SET `PrevQuestID` = '14122' WHERE  `ID` = '14124'; 
UPDATE `quest_template_addon` SET `PrevQuestID` = '14124' WHERE  `ID` = '14125';
UPDATE `quest_template_addon` SET `PrevQuestID` = '14125' WHERE  `ID` = '14126';

INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `FemaleName`, `Title`, `VerifiedBuild`) VALUES
(34830,'esMX','Trol desafiante','','',18019),
(34830,'esES','Trol desafiante','','',18019);
ALTER TABLE `creature_text_locale`
DROP PRIMARY KEY;

INSERT INTO `creature_text_locale` ( `CreatureID`,`GroupID`,`ID`,`Locale`,`Text`) VALUES
(34830,0,0,'esMX','¡No me acribilles'),
(34830,0,0,'esES','¡No me acribilles'),
(34830,0,1,'esMX','¡Te denuncio con Recursos Humanos!'),
(34830,0,1,'esES','¡Te denuncio con Recursos Humanos!'),
(34830,0,2,'esMX','Me voy. ¡Me voy!'),
(34830,0,2,'esES','Me voy. ¡Me voy!'),
(34830,0,3,'esMX','Uy, se acabó el descanso.'),
(34830,0,3,'esES','Uy, se acabó el descanso.'),
(34830,0,4,'esMX','Lo siento. No volverá a ocurrir.'),
(34830,0,4,'esES','Lo siento. No volverá a ocurrir.'),
(34830,0,5,'esMX','¿Qué estoy haciendo mal? ¿No tengo un almuerzo y dos descansos al día?'),
(34830,0,5,'esES','¿Qué estoy haciendo mal? ¿No tengo un almuerzo y dos descansos al día?'),
(34830,0,6,'esMX','¡El trabajo era mejor en la mina!'),
(34830,0,6,'esES','¡El trabajo era mejor en la mina!');

