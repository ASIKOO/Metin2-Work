-- MySQL dump 10.13  Distrib 8.0.19, for FreeBSD11.3 (amd64)
--
-- Host: localhost    Database: account
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
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `id` int NOT NULL AUTO_INCREMENT,
  `login` varchar(30) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `password` varchar(45) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99',
  `social_id` varchar(7) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '1234567',
  `email` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'project@metin2.dev',
  `create_time` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `status` varchar(8) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'OK',
  `securitycode` varchar(192) CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT '',
  `availDt` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `mileage` int NOT NULL DEFAULT '0',
  `cash` int NOT NULL DEFAULT '0',
  `gold_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `silver_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `safebox_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `autoloot_expire` datetime NOT NULL DEFAULT '2030-12-31 23:59:59',
  `fish_mind_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `marriage_fast_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `money_drop_rate_expire` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  `last_play` datetime NOT NULL DEFAULT '2001-01-01 00:00:00',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE KEY `login` (`login`) USING BTREE,
  KEY `social_id` (`social_id`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=59543 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT IGNORE INTO `account` VALUES (1,'asikoo','*93D7FFC7C7FBB5B2A7B4AC1C744D47FBDDFCD1FC','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,1650,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 05:16:31'),(11,'playerone','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:16:30'),(12,'playertwo','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:16:43'),(13,'playerthree','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:17:33'),(14,'playerfour','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:17:57'),(15,'playerfive','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:18:16'),(16,'playersix','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:18:38'),(17,'playerseven','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:18:58'),(18,'playereight','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:19:34'),(19,'playernine','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:19:59'),(20,'playerten','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2021-02-02 02:20:20'),(4,'veltor','*3F45D03FB42F67684F712E29B2EB2DB242563886','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-08-06 01:22:00'),(5,'kijaru','*60C3BDAA00D5CF4CA2BF8D712FBE5AF27E3CBD7D','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00'),(2,'player','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-11-28 12:11:18'),(59536,'saug','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-17 20:34:35'),(59537,'azertytest54','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-13 15:08:07'),(59538,'dedif','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-12 07:10:02'),(59539,'rex','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-07-05 11:32:29'),(59540,'gurgarath','*957D0549970CA499A7ACAE4F5CED8ED65FEB44B9','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-26 21:09:01'),(59541,'floflodu959','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-14 15:26:48'),(59542,'firaton','*98E1AE238461FEB88F0B9F447BDA292CDFC3AA99','1234567','project@metin2.dev','2001-01-01 00:00:00','OK','','2001-01-01 00:00:00',0,0,'2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2030-12-31 23:59:59','2001-01-01 00:00:00','2001-01-01 00:00:00','2001-01-01 00:00:00','2020-06-29 10:25:19');
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `admin` (
  `id` int NOT NULL DEFAULT '0',
  `admin` varchar(50) DEFAULT NULL,
  `password` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
INSERT IGNORE INTO `admin` VALUES (1,'192.168.0.16','dPm\"21pe6D4GKH*??45lJD');
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `block_exception`
--

DROP TABLE IF EXISTS `block_exception`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `block_exception` (
  `login` int DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `block_exception`
--

LOCK TABLES `block_exception` WRITE;
/*!40000 ALTER TABLE `block_exception` DISABLE KEYS */;
INSERT IGNORE INTO `block_exception` VALUES (1);
/*!40000 ALTER TABLE `block_exception` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gametime`
--

DROP TABLE IF EXISTS `gametime`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gametime` (
  `UserID` varchar(50) NOT NULL DEFAULT '',
  `paymenttype` tinyint NOT NULL DEFAULT '1',
  `LimitTime` int DEFAULT '0',
  `LimitDt` datetime DEFAULT '1990-01-01 00:00:00',
  `Scores` int DEFAULT '0',
  PRIMARY KEY (`UserID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gametime`
--

LOCK TABLES `gametime` WRITE;
/*!40000 ALTER TABLE `gametime` DISABLE KEYS */;
/*!40000 ALTER TABLE `gametime` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gametimeip`
--

DROP TABLE IF EXISTS `gametimeip`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gametimeip` (
  `ipid` int NOT NULL AUTO_INCREMENT,
  `name` varchar(128) DEFAULT NULL,
  `ip` varchar(11) NOT NULL DEFAULT '000.000.000',
  `startIP` int NOT NULL DEFAULT '0',
  `endIP` int NOT NULL DEFAULT '255',
  `paymenttype` tinyint NOT NULL DEFAULT '1',
  `LimitTime` int NOT NULL DEFAULT '0',
  `LimitDt` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `readme` varchar(128) DEFAULT NULL,
  PRIMARY KEY (`ipid`),
  UNIQUE KEY `ip_uniq` (`ip`,`startIP`,`endIP`),
  KEY `ip_idx` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gametimeip`
--

LOCK TABLES `gametimeip` WRITE;
/*!40000 ALTER TABLE `gametimeip` DISABLE KEYS */;
/*!40000 ALTER TABLE `gametimeip` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gametimelog`
--

DROP TABLE IF EXISTS `gametimelog`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gametimelog` (
  `login` varchar(16) DEFAULT NULL,
  `type` enum('IP_FREE','FREE','IP_TIME','IP_DAY','TIME','DAY') DEFAULT NULL,
  `logon_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `logout_time` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `use_time` int DEFAULT NULL,
  `ip` varchar(15) NOT NULL DEFAULT '000.000.000.000',
  `server` varchar(32) NOT NULL DEFAULT '',
  KEY `login_key` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gametimelog`
--

LOCK TABLES `gametimelog` WRITE;
/*!40000 ALTER TABLE `gametimelog` DISABLE KEYS */;
/*!40000 ALTER TABLE `gametimelog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `iptocountry`
--

DROP TABLE IF EXISTS `iptocountry`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `iptocountry` (
  `IP_FROM` varchar(16) DEFAULT NULL,
  `IP_TO` varchar(16) DEFAULT NULL,
  `COUNTRY_NAME` varchar(16) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `iptocountry`
--

LOCK TABLES `iptocountry` WRITE;
/*!40000 ALTER TABLE `iptocountry` DISABLE KEYS */;
INSERT IGNORE INTO `iptocountry` VALUES ('127.0.0.1','127.0.0.1','localhost ');
/*!40000 ALTER TABLE `iptocountry` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `monarch`
--

DROP TABLE IF EXISTS `monarch`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `monarch` (
  `empire` int unsigned NOT NULL DEFAULT '0',
  `pid` int unsigned DEFAULT '0',
  `name` varchar(16) DEFAULT NULL,
  `windate` datetime DEFAULT '0000-00-00 00:00:00',
  `money` bigint unsigned DEFAULT '0',
  PRIMARY KEY (`empire`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `monarch`
--

LOCK TABLES `monarch` WRITE;
/*!40000 ALTER TABLE `monarch` DISABLE KEYS */;
/*!40000 ALTER TABLE `monarch` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `send_notice`
--

DROP TABLE IF EXISTS `send_notice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `send_notice` (
  `id` int NOT NULL AUTO_INCREMENT,
  `type` tinyint NOT NULL DEFAULT '0',
  `server` varchar(3) NOT NULL DEFAULT '',
  `show_check` tinyint NOT NULL DEFAULT '0',
  `content` text,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `send_notice`
--

LOCK TABLES `send_notice` WRITE;
/*!40000 ALTER TABLE `send_notice` DISABLE KEYS */;
/*!40000 ALTER TABLE `send_notice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tele_block`
--

DROP TABLE IF EXISTS `tele_block`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tele_block` (
  `account_id` int NOT NULL DEFAULT '0',
  `lastlogin` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `tele_block` varchar(30) NOT NULL DEFAULT '',
  PRIMARY KEY (`account_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tele_block`
--

LOCK TABLES `tele_block` WRITE;
/*!40000 ALTER TABLE `tele_block` DISABLE KEYS */;
/*!40000 ALTER TABLE `tele_block` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-02-02  5:25:24
