DROP TABLE IF EXISTS `daily_players_reports`; 
 CREATE TABLE IF NOT EXISTS `daily_players_reports` ( 
   `guid` int(10) unsigned NOT NULL DEFAULT '0', 
   `creation_time` int(10) unsigned NOT NULL DEFAULT '0', 
   `average` float NOT NULL DEFAULT '0', 
   `total_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `speed_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `fly_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `jump_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `waterwalk_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `teleportplane_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `climb_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `teleport_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `ignorecontrol_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `zaxis_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `antiswim_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `gravity_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `antiknockback_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `no_fall_damage_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `op_ack_hack_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `counter_measures_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   PRIMARY KEY (`guid`) 
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4; 
  
 DROP TABLE IF EXISTS `players_reports_status`; 
 CREATE TABLE IF NOT EXISTS `players_reports_status` ( 
   `guid` int(10) unsigned NOT NULL DEFAULT '0', 
   `creation_time` int(10) unsigned NOT NULL DEFAULT '0', 
   `average` float NOT NULL DEFAULT '0', 
   `total_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `speed_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `fly_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `jump_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `waterwalk_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `teleportplane_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `climb_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `teleport_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `ignorecontrol_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `zaxis_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `antiswim_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `gravity_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `antiknockback_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `no_fall_damage_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `op_ack_hack_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   `counter_measures_reports` bigint(20) unsigned NOT NULL DEFAULT '0', 
   PRIMARY KEY (`guid`) 
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4; 
  
 DROP TABLE IF EXISTS `lua_cheaters`; 
 CREATE TABLE IF NOT EXISTS `lua_cheaters` ( 
   `guid` int(11) NOT NULL, 
   `account` int(11) NOT NULL, 
   `macro` varchar(255) DEFAULT NULL, 
   PRIMARY KEY (`guid`,`account`) 
 ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;