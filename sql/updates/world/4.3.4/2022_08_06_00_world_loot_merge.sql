--
-- 

DROP TABLE IF EXISTS world_loot_template;
CREATE TABLE world_loot_template (
    `Entry` mediumint(8) unsigned NOT NULL DEFAULT 0,
    `lootTypeId` tinyint(3) unsigned NOT NULL,
    `Item` mediumint(8) unsigned NOT NULL DEFAULT 0,
    `Reference` mediumint(8) unsigned NOT NULL DEFAULT 0,
    `Chance` float NOT NULL DEFAULT 100,
    `QuestRequired` tinyint(1) NOT NULL DEFAULT 0,
    `LootMode` smallint(5) unsigned NOT NULL DEFAULT 1,
    `GroupId` tinyint(3) unsigned NOT NULL DEFAULT 0,
    `MinCount` tinyint(3) unsigned NOT NULL DEFAULT 1,
    `MaxCount` tinyint(3) unsigned NOT NULL DEFAULT 1,
    `Comment` varchar(255) DEFAULT NULL,
    PRIMARY KEY (`Entry`, `lootTypeId`, `Item`),
    KEY `Entry` (`Entry`, `lootTypeId`)
  ) ENGINE = MyISAM DEFAULT CHARSET = utf8mb4 COMMENT = 'Loot System';

-- creature loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 1, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM creature_loot_template ORDER BY Entry ASC;

-- disenchant loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 2, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM disenchant_loot_template ORDER BY Entry ASC;

-- fishing loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 3, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM fishing_loot_template ORDER BY Entry ASC;

-- gameobject loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 4, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM gameobject_loot_template ORDER BY Entry ASC;    

-- item loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 5, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM item_loot_template ORDER BY Entry ASC;

-- mail loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 6, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM mail_loot_template ORDER BY Entry ASC;

-- milling loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 7, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM milling_loot_template ORDER BY Entry ASC;

-- pickpocketing loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 8, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM pickpocketing_loot_template ORDER BY Entry ASC;

-- prospecting loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 9, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM prospecting_loot_template ORDER BY Entry ASC;

-- reference loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 10, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM reference_loot_template ORDER BY Entry ASC;
    
-- skinning loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 11, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM skinning_loot_template ORDER BY Entry ASC;
    
-- spell loot
INSERT INTO world_loot_template (Entry, lootTypeId, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount)
SELECT Entry, 12, Item, Reference, Chance, QuestRequired, LootMode, GroupId, MinCount, MaxCount
    FROM spell_loot_template ORDER BY Entry ASC;

-- drop old loot tables
DROP TABLE creature_loot_template;
DROP TABLE disenchant_loot_template;
DROP TABLE fishing_loot_template;
DROP TABLE gameobject_loot_template;
DROP TABLE item_loot_template;
DROP TABLE mail_loot_template;
DROP TABLE milling_loot_template;
DROP TABLE pickpocketing_loot_template;
DROP TABLE prospecting_loot_template;
DROP TABLE reference_loot_template;
DROP TABLE skinning_loot_template;
DROP TABLE spell_loot_template;
