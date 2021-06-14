-- MySQL dump 10.13  Distrib 8.0.19, for FreeBSD11.3 (amd64)
--
-- Host: localhost    Database: common
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
-- Table structure for table `gmhost`
--

DROP TABLE IF EXISTS `gmhost`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gmhost` (
  `mIP` varchar(16) NOT NULL DEFAULT '',
  PRIMARY KEY (`mIP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gmhost`
--

LOCK TABLES `gmhost` WRITE;
/*!40000 ALTER TABLE `gmhost` DISABLE KEYS */;
INSERT IGNORE INTO `gmhost` VALUES ('ALL');
/*!40000 ALTER TABLE `gmhost` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gmlist`
--

DROP TABLE IF EXISTS `gmlist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `gmlist` (
  `mID` int unsigned NOT NULL AUTO_INCREMENT,
  `mAccount` varchar(16) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `mName` varchar(16) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `mContactIP` varchar(16) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `mServerIP` varchar(16) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'ALL',
  `mAuthority` enum('IMPLEMENTOR','GOD','HIGH_WIZARD','WIZARD','LOW_WIZARD','PLAYER') CHARACTER SET latin1 COLLATE latin1_swedish_ci DEFAULT 'PLAYER',
  PRIMARY KEY (`mID`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=42 DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gmlist`
--

LOCK TABLES `gmlist` WRITE;
/*!40000 ALTER TABLE `gmlist` DISABLE KEYS */;
INSERT IGNORE INTO `gmlist` VALUES (1,'asikoo','ASIKOO','','ALL','IMPLEMENTOR'),(5,'kijaru','Kijaru','','ALL','IMPLEMENTOR'),(11,'playerone','PlayerOne','','ALL','IMPLEMENTOR'),(6,'asikoo','OOKISA','','ALL','IMPLEMENTOR'),(12,'playertwo','PlayerTwo','','ALL','IMPLEMENTOR'),(13,'playerthree','PlayerThree','','ALL','IMPLEMENTOR'),(14,'playerfour','PlayerFour','','ALL','IMPLEMENTOR'),(15,'playerfive','PlayerFive','','ALL','IMPLEMENTOR'),(16,'playersix','PlayerSix','','ALL','IMPLEMENTOR'),(17,'playerseven','PlayerSeven','','ALL','IMPLEMENTOR'),(18,'playereight','PlayerEight','','ALL','IMPLEMENTOR'),(19,'playernine','PlayerNine','','ALL','IMPLEMENTOR'),(20,'playerten','PlayerTen','','ALL','IMPLEMENTOR'),(4,'veltor','Veltor88','','ALL','IMPLEMENTOR'),(33,'saug','Saug','','ALL','IMPLEMENTOR'),(34,'azertytest54','Benkei','','ALL','IMPLEMENTOR'),(36,'dedif','Nashaiia','','ALL','IMPLEMENTOR'),(37,'saug','Saug1','','ALL','IMPLEMENTOR'),(38,'rex','Rex','','ALL','IMPLEMENTOR'),(39,'gurgarath','Gurgarath','','ALL','IMPLEMENTOR'),(40,'floflodu959','Gloupy','','ALL','IMPLEMENTOR'),(41,'firaton','Daerian','','ALL','IMPLEMENTOR');
/*!40000 ALTER TABLE `gmlist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `locale`
--

DROP TABLE IF EXISTS `locale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `locale` (
  `mKey` varchar(255) NOT NULL DEFAULT '',
  `mValue` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`mKey`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `locale`
--

LOCK TABLES `locale` WRITE;
/*!40000 ALTER TABLE `locale` DISABLE KEYS */;
INSERT IGNORE INTO `locale` VALUES ('SKILL_POWER_BY_LEVEL_TYPE0','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE1','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE2','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE3','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE4','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE5','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE6','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('SKILL_POWER_BY_LEVEL_TYPE7','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125'),('LOCALE','france'),('DB_NAME_COLUMN','locale_name'),('SKILL_DAMAGE_BY_LEVEL_UNDER_90','0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0'),('SKILL_DAMAGE_BY_LEVEL_UNDER_45','0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0'),('SKILL_POWER_BY_LEVEL','0 5 6 8 10 12 14 16 18 20 22 24 26 28 30 32 34 36 38 40 50 52 54 56 58 60 63 66 69 72 82 85 88 91 94 98 102 106 110 115 125 125 125 125 125');
/*!40000 ALTER TABLE `locale` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `locale_bug`
--

DROP TABLE IF EXISTS `locale_bug`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `locale_bug` (
  `mKey` varchar(255) NOT NULL DEFAULT '',
  `mValue` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`mKey`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `locale_bug`
--

LOCK TABLES `locale_bug` WRITE;
/*!40000 ALTER TABLE `locale_bug` DISABLE KEYS */;
/*!40000 ALTER TABLE `locale_bug` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `spam_db`
--

DROP TABLE IF EXISTS `spam_db`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `spam_db` (
  `word` varchar(15) DEFAULT NULL,
  `score` varchar(15) DEFAULT NULL,
  `type` varchar(15) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `spam_db`
--

LOCK TABLES `spam_db` WRITE;
/*!40000 ALTER TABLE `spam_db` DISABLE KEYS */;
/*!40000 ALTER TABLE `spam_db` ENABLE KEYS */;
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
