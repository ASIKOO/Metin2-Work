-- MySQL dump 10.13  Distrib 8.0.19, for FreeBSD11.3 (amd64)
--
-- Host: localhost    Database: log
-- ------------------------------------------------------
-- Server version	8.0.19

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES UTF8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bootlog`
--

DROP TABLE IF EXISTS `bootlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bootlog` (
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `hostname` char(128) NOT NULL DEFAULT 'UNKNOWN',
  `channel` tinyint(1) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bootlog`
--

LOCK TABLES `bootlog` WRITE;
/*!40000 ALTER TABLE `bootlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `bootlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `change_name`
--

DROP TABLE IF EXISTS `change_name`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `change_name` (
  `pid` int unsigned NOT NULL DEFAULT '0',
  `old_name` varchar(30) NOT NULL,
  `new_name` varchar(30) NOT NULL,
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `ip` char(15) NOT NULL DEFAULT ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `change_name`
--

LOCK TABLES `change_name` WRITE;
/*!40000 ALTER TABLE `change_name` DISABLE KEYS */;
/*!40000 ALTER TABLE `change_name` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `command_log`
--

DROP TABLE IF EXISTS `command_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `command_log` (
  `userid` varchar(70) DEFAULT NULL,
  `server` varchar(70) DEFAULT NULL,
  `ip` char(15) NOT NULL DEFAULT '',
  `port` varchar(70) DEFAULT NULL,
  `username` varchar(70) DEFAULT NULL,
  `command` varchar(70) DEFAULT NULL,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `command_log`
--

LOCK TABLES `command_log` WRITE;
/*!40000 ALTER TABLE `command_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `command_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cube`
--

DROP TABLE IF EXISTS `cube`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `cube` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `pid` int unsigned NOT NULL DEFAULT '0',
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `x` int unsigned NOT NULL DEFAULT '0',
  `y` int unsigned NOT NULL DEFAULT '0',
  `item_vnum` int unsigned NOT NULL DEFAULT '0',
  `item_uid` int unsigned NOT NULL DEFAULT '0',
  `item_count` int unsigned NOT NULL DEFAULT '0',
  `success` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `pid` (`pid`),
  KEY `item_vnum` (`item_vnum`),
  KEY `item_uid` (`item_uid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `cube`
--

LOCK TABLES `cube` WRITE;
/*!40000 ALTER TABLE `cube` DISABLE KEYS */;
/*!40000 ALTER TABLE `cube` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dragon_slay_log`
--

DROP TABLE IF EXISTS `dragon_slay_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `dragon_slay_log` (
  `1` varchar(16) NOT NULL,
  `2` varchar(16) NOT NULL,
  `3` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `4` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `dragon_slay_log`
--

LOCK TABLES `dragon_slay_log` WRITE;
/*!40000 ALTER TABLE `dragon_slay_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `dragon_slay_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `fish_log`
--

DROP TABLE IF EXISTS `fish_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `fish_log` (
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `player_id` int unsigned NOT NULL DEFAULT '0',
  `map_index` tinyint NOT NULL DEFAULT '0',
  `fish_id` int unsigned NOT NULL DEFAULT '0',
  `fishing_level` int NOT NULL DEFAULT '0',
  `waiting_time` int NOT NULL DEFAULT '0',
  `success` tinyint NOT NULL DEFAULT '0',
  `size` smallint NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `fish_log`
--

LOCK TABLES `fish_log` WRITE;
/*!40000 ALTER TABLE `fish_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `fish_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `goldlog`
--

DROP TABLE IF EXISTS `goldlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `goldlog` (
  `date` varchar(10) NOT NULL DEFAULT '0000-00-00',
  `time` varchar(8) NOT NULL DEFAULT '00:00:00',
  `pid` int unsigned NOT NULL DEFAULT '0',
  `what` int NOT NULL DEFAULT '0',
  `how` set('BUY','SELL','SHOP_SELL','SHOP_BUY','EXCHANGE_TAKE','EXCHANGE_GIVE','QUEST') DEFAULT NULL,
  `hint` varchar(50) DEFAULT NULL,
  KEY `date_idx` (`date`),
  KEY `pid_idx` (`pid`),
  KEY `what_idx` (`what`),
  KEY `how_idx` (`how`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `goldlog`
--

LOCK TABLES `goldlog` WRITE;
/*!40000 ALTER TABLE `goldlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `goldlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hack_crc_log`
--

DROP TABLE IF EXISTS `hack_crc_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `hack_crc_log` (
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `login` char(16) NOT NULL DEFAULT '',
  `name` char(24) NOT NULL DEFAULT '',
  `ip` char(15) NOT NULL DEFAULT '',
  `server` char(100) NOT NULL DEFAULT '',
  `why` char(255) NOT NULL DEFAULT '',
  `crc` int NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hack_crc_log`
--

LOCK TABLES `hack_crc_log` WRITE;
/*!40000 ALTER TABLE `hack_crc_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `hack_crc_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hack_log`
--

DROP TABLE IF EXISTS `hack_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `hack_log` (
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `login` char(16) NOT NULL DEFAULT '',
  `name` char(24) NOT NULL DEFAULT '',
  `ip` char(15) NOT NULL DEFAULT '',
  `server` char(100) NOT NULL DEFAULT '',
  `why` char(255) NOT NULL DEFAULT ''
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hack_log`
--

LOCK TABLES `hack_log` WRITE;
/*!40000 ALTER TABLE `hack_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `hack_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hackshield_log`
--

DROP TABLE IF EXISTS `hackshield_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `hackshield_log` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `account_id` int DEFAULT NULL,
  `login` char(16) NOT NULL DEFAULT '',
  `pid` int DEFAULT NULL,
  `name` char(24) NOT NULL DEFAULT '',
  `reason` varchar(20) DEFAULT NULL,
  `ip` char(15) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hackshield_log`
--

LOCK TABLES `hackshield_log` WRITE;
/*!40000 ALTER TABLE `hackshield_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `hackshield_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `levellog`
--

DROP TABLE IF EXISTS `levellog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `levellog` (
  `name` char(24) NOT NULL DEFAULT '',
  `level` tinyint NOT NULL DEFAULT '0',
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `account_id` int DEFAULT NULL,
  `pid` int DEFAULT NULL,
  `playtime` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`name`,`level`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `levellog`
--

LOCK TABLES `levellog` WRITE;
/*!40000 ALTER TABLE `levellog` DISABLE KEYS */;
/*!40000 ALTER TABLE `levellog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `log` (
  `type` enum('ITEM','CHARACTER') NOT NULL DEFAULT 'ITEM',
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `who` int unsigned NOT NULL DEFAULT '0',
  `x` int unsigned NOT NULL DEFAULT '0',
  `y` int unsigned NOT NULL DEFAULT '0',
  `what` int NOT NULL DEFAULT '0',
  `how` varchar(50) NOT NULL DEFAULT '',
  `hint` varchar(50) DEFAULT NULL,
  `ip` char(15) NOT NULL DEFAULT '',
  `vnum` int NOT NULL DEFAULT '0',
  KEY `who_idx` (`who`),
  KEY `what_idx` (`what`),
  KEY `how_idx` (`how`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loginlog`
--

DROP TABLE IF EXISTS `loginlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `loginlog` (
  `type` enum('LOGIN','LOGOUT') DEFAULT NULL,
  `time` datetime DEFAULT NULL,
  `channel` tinyint DEFAULT NULL,
  `account_id` int unsigned DEFAULT NULL,
  `pid` int unsigned DEFAULT NULL,
  `level` smallint DEFAULT NULL,
  `job` tinyint DEFAULT NULL,
  `playtime` int unsigned DEFAULT NULL,
  KEY `pid` (`pid`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loginlog`
--

LOCK TABLES `loginlog` WRITE;
/*!40000 ALTER TABLE `loginlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `loginlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loginlog2`
--

DROP TABLE IF EXISTS `loginlog2`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `loginlog2` (
  `id` int NOT NULL AUTO_INCREMENT,
  `type` enum('VALID','INVALID') DEFAULT NULL,
  `is_gm` int DEFAULT NULL,
  `login_time` datetime DEFAULT '2001-01-01 00:00:00',
  `channel` tinyint DEFAULT NULL,
  `account_id` int unsigned DEFAULT NULL,
  `pid` int unsigned DEFAULT NULL,
  `ip` char(15) NOT NULL DEFAULT '',
  `client_version` varchar(20) DEFAULT NULL,
  `logout_time` datetime DEFAULT '2001-01-01 00:00:00',
  `playtime` int unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `pid` (`pid`,`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loginlog2`
--

LOCK TABLES `loginlog2` WRITE;
/*!40000 ALTER TABLE `loginlog2` DISABLE KEYS */;
/*!40000 ALTER TABLE `loginlog2` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `money_log`
--

DROP TABLE IF EXISTS `money_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `money_log` (
  `time` datetime DEFAULT NULL,
  `type` enum('MONSTER','SHOP','REFINE','QUEST','GUILD','MISC','KILL','DROP') DEFAULT NULL,
  `vnum` int NOT NULL DEFAULT '0',
  `gold` int NOT NULL DEFAULT '0',
  KEY `type` (`type`,`vnum`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `money_log`
--

LOCK TABLES `money_log` WRITE;
/*!40000 ALTER TABLE `money_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `money_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pcbang_loginlog`
--

DROP TABLE IF EXISTS `pcbang_loginlog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pcbang_loginlog` (
  `id` int NOT NULL AUTO_INCREMENT,
  `time` datetime DEFAULT NULL,
  `pcbang_id` int NOT NULL DEFAULT '0',
  `ip` varchar(15) NOT NULL DEFAULT '000.000.000.000',
  `pid` int unsigned DEFAULT NULL,
  `play_time` int unsigned DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `pid` (`pid`),
  KEY `pcbang_id` (`pcbang_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pcbang_loginlog`
--

LOCK TABLES `pcbang_loginlog` WRITE;
/*!40000 ALTER TABLE `pcbang_loginlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `pcbang_loginlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `quest_reward_log`
--

DROP TABLE IF EXISTS `quest_reward_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `quest_reward_log` (
  `quest_name` varchar(32) DEFAULT NULL,
  `player_id` int unsigned DEFAULT NULL,
  `player_level` tinyint DEFAULT NULL,
  `reward_type` enum('EXP','ITEM') DEFAULT NULL,
  `reward_value1` int unsigned DEFAULT NULL,
  `reward_value2` int DEFAULT NULL,
  `time` datetime DEFAULT NULL,
  KEY `player_id` (`player_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `quest_reward_log`
--

LOCK TABLES `quest_reward_log` WRITE;
/*!40000 ALTER TABLE `quest_reward_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `quest_reward_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `refinelog`
--

DROP TABLE IF EXISTS `refinelog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `refinelog` (
  `pid` int unsigned DEFAULT NULL,
  `item_name` varchar(24) NOT NULL DEFAULT '',
  `item_id` int NOT NULL DEFAULT '0',
  `step` varchar(50) NOT NULL DEFAULT '',
  `time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `is_success` tinyint(1) NOT NULL DEFAULT '0',
  `setType` set('SOCKET','POWER','ROD','GUILD','SCROLL','HYUNIRON','GOD_SCROLL') DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `refinelog`
--

LOCK TABLES `refinelog` WRITE;
/*!40000 ALTER TABLE `refinelog` DISABLE KEYS */;
/*!40000 ALTER TABLE `refinelog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `shout_log`
--

DROP TABLE IF EXISTS `shout_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `shout_log` (
  `time` datetime DEFAULT '0000-00-00 00:00:00',
  `channel` tinyint DEFAULT NULL,
  `empire` tinyint DEFAULT NULL,
  `shout` varchar(64) DEFAULT NULL,
  KEY `time_idx` (`time`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `shout_log`
--

LOCK TABLES `shout_log` WRITE;
/*!40000 ALTER TABLE `shout_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `shout_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `speed_hack`
--

DROP TABLE IF EXISTS `speed_hack`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `speed_hack` (
  `pid` int unsigned DEFAULT NULL,
  `time` datetime DEFAULT '0000-00-00 00:00:00',
  `x` int unsigned NOT NULL DEFAULT '0',
  `y` int unsigned NOT NULL DEFAULT '0',
  `hack_count` varchar(20) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `speed_hack`
--

LOCK TABLES `speed_hack` WRITE;
/*!40000 ALTER TABLE `speed_hack` DISABLE KEYS */;
/*!40000 ALTER TABLE `speed_hack` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vcard_log`
--

DROP TABLE IF EXISTS `vcard_log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `vcard_log` (
  `vcard_id` int unsigned NOT NULL AUTO_INCREMENT,
  `x` int unsigned NOT NULL DEFAULT '0',
  `y` int unsigned NOT NULL DEFAULT '0',
  `hostname` char(128) NOT NULL DEFAULT 'UNKNOWN',
  `giver_name` varchar(30) NOT NULL,
  `giver_ip` char(15) NOT NULL DEFAULT '',
  `taker_name` varchar(30) NOT NULL,
  `taker_ip` char(15) NOT NULL DEFAULT '',
  PRIMARY KEY (`vcard_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vcard_log`
--

LOCK TABLES `vcard_log` WRITE;
/*!40000 ALTER TABLE `vcard_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `vcard_log` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-02-02  5:25:26
