import item
########Anti Exp Button by Sanii##########
#ANTI_EXP = 0
#ANTI_EXP_STATE = 0
##########################################

##########################################
## BONISWITCHER ENTRIES
##########################################
#SWITCHER_COUNT = 5
#OPTION_FILE_NAME = "config.inf"
#ATTR_BONI_LIST = ["Keiner", "Max. TP", "Max. MP", "Vitalität", "Intelligenz", "Stärke", "Beweglichkeit", "Angriffsgeschwindigkeit", "Bewegungsgeschwindigkeit",
				  #"Zaubergeschwindigkeit", "Lebensregeneration", "Manaregeneration", "Vergiftungschance", "Ohnmachtschance", "Verlangsamungschance",
				  #"Chance auf krit. Treffer", "Chance auf durchbohrenden Treffer", "Schaden gegen Halbmenschen", "Schaden gegen Tiere", "Schaden gegen Orks",
				  #"Schaden gegen Esoterische", "Schaden gegen Untote", "Schaden gegen Teufel", "Schaden wird von TP absorbiert", "Schaden wird von MP absorbiert",
				  #"Chance auf Manaraub", "Chance, MP bei Treffer zurückzuerhalten", "Chance, Nahkampf-Angriff abzublocken", "Chance, Pfeilangriff auszuweichen",
				  #"Schwertverteidigung", "Zweihänderverteidigung", "Dolchverteidigung", "Glockenverteidigung", "Fächerverteidigung", "Pfeilwiderstand",
				  #"Feuerwiderstand", "Blitzwiderstand", "Magiewiderstand", "Windwiderstand", "Chance, Nahkampftreffer zu reflektieren", 
				  #"Chance, Fluch zu reflektieren", "Giftwiderstand", "Chance, MP wiederherzustellen", "Chance auf EXP-Bonus",
				  #"Chance, eine doppelte Menge Yang fallen zu lassen", "Chance, eine doppelte Menge von Gegenständen fallen zu lassen", "Trank Effektzuwachs",
				  #"Chance, TP wiederherzustellen", "Abwehr gegen Ohnmacht", "Abwehr gegen Verlangsamung", "Immun gegen Stürzen", "SKILL", "Bogenreichweite",
				  #"Angriffswert", "Verteidigung", "Magieangriffswert", "Magieverteidigung", "-", "Max. Ausdauer", "Schaden gegen Krieger", 
				  #"Schaden gegen Ninjas", "Schaden gegen Suras", "Schaden gegen Schamanen", "Schaden gegen Monster", "-", "-", "-", "-", "-", "-", "-",
				  #"Fertigkeitsschaden", "Durchschn. Schaden"]
#ITEM_LIST_WEAPON_ADDON = [189, 199, 299, 3169, 3219, 5119, 5129, 7169, 2159, 2179, 1139, 1179, 469, 479, 9919, 5349, 7379, 1349, 2379]
#BONI_LIST_NO_PLUS = [0, 48, 49, 50]
#BONI_LIST_NO_PERCENT = [0, 1, 2, 3, 4, 5, 6, 48, 49, 50, 52, 53, 54, 55, 56]
#BONI_LIST_NO_VALUE = [0, 48, 49, 50]
#def GetAttrText(attrtyp, attrval):
	#attrtyp = int(attrtyp)
	#attrval = int(attrval)
	#attrtext = ""
	#if BONI_LIST_NO_PLUS.count(attrtyp) == 0 and int(attrval) >= 0:
		#attrtext = "+"
	#if BONI_LIST_NO_VALUE.count(attrtyp) == 0:
		#attrtext = attrtext + str(attrval)
	#if BONI_LIST_NO_PERCENT.count(attrtyp) == 0:
		#attrtext = attrtext + "%"
	#if BONI_LIST_NO_VALUE.count(attrtyp) == 0:
		#attrtext = attrtext + " "
	#attrtext = attrtext + ATTR_BONI_LIST[attrtyp]
	#return attrtext
	
#ATTR_BONI_LIST = ["Keiner", "Max. TP", "Max. MP", "Vitalität", "Intelligenz", "Stärke", "Beweglichkeit", "Angriffsgeschwindigkeit", "Bewegungsgeschwindigkeit",
				  #"Zaubergeschwindigkeit", "Lebensregeneration", "Manaregeneration", "Vergiftungschance", "Ohnmachtschance", "Verlangsamungschance",
				  #"Chance auf krit. Treffer", "Chance auf durchbohrenden Treffer", "Schaden gegen Halbmenschen", "Schaden gegen Tiere", "Schaden gegen Orks",
				  #"Schaden gegen Esoterische", "Schaden gegen Untote", "Schaden gegen Teufel", "Schaden wird von TP absorbiert", "Schaden wird von MP absorbiert",
				  #"Chance auf Manaraub", "Chance, MP bei Treffer zurückzuerhalten", "Chance, Nahkampf-Angriff abzublocken", "Chance, Pfeilangriff auszuweichen",
				  #"Schwertverteidigung", "Zweihänderverteidigung", "Dolchverteidigung", "Glockenverteidigung", "Fächerverteidigung", "Pfeilwiderstand",
				  #"Feuerwiderstand", "Blitzwiderstand", "Magiewiderstand", "Windwiderstand", "Chance, Nahkampftreffer zu reflektieren", 
				  #"Chance, Fluch zu reflektieren", "Giftwiderstand", "Chance, MP wiederherzustellen", "Chance auf EXP-Bonus",
				  #"Chance, eine doppelte Menge Yang fallen zu lassen", "Chance, eine doppelte Menge von Gegenständen fallen zu lassen", "Trank Effektzuwachs",
				  #"Chance, TP wiederherzustellen", "Abwehr gegen Ohnmacht", "Abwehr gegen Verlangsamung", "Immun gegen Stürzen", "SKILL", "Bogenreichweite",
				  #"Angriffswert", "Verteidigung", "Magieangriffswert", "Magieverteidigung", "-", "Max. Ausdauer", "Schaden gegen Krieger", 
				  #"Schaden gegen Ninjas", "Schaden gegen Suras", "Schaden gegen Schamanen", "Schaden gegen Monster", "-", "-", "-", "-", "-", "-", "-",
				  #"Fertigkeitsschaden", "Durchschn. Schaden"]
				  
#BONI_LIST_MAX_VALUE = {1:2500, 2:80, 3:12, 4:12, 5:12, 6:12, 7:8, 8:20, 9:20, 10:30, 11:30, 12:8, 13:8, 14:8, 15:10, 16:10, 17:10, 18:20, 19:20, 20:20, 21:20, 22:20, 23:10, 24:10, 25:10, 27:15, 28:15, 29:15, 30:15, 31:15, 32:15, 33:15, 34:15, 35:15, 36:15, 37:15, 38:15, 39:10, 41:5, 43:20, 44:20, 45:20, 48:1, 49:1, 53:50, 59:10, 60:10, 61:10, 62:10, 78:10, 79:10, 80:10, 81:10}
#BONI_LIST_ARMOR = [1, 9, 23, 24, 29, 30, 31, 32, 33, 34, 37, 39, 53]
#BONI_LIST_SHIELD = [3, 4, 5, 6, 17, 18, 19, 20, 21, 22, 27, 39, 48, 49, 66, 68]
#BONI_LIST_BOOTS = [1, 7, 8, 13, 14, 15, 28, 29, 30, 31, 32, 33, 34, 66, 68]
#BONI_LIST_BRACELET = [1, 16, 17, 18, 19, 20, 21, 22, 23, 25, 37, 67]
#BONI_LIST_HELMET = [7, 10, 11, 12, 17, 18, 19, 20, 21, 22, 24, 28, 37]
#BONI_LIST_EARRINGS = [8, 17, 18, 19, 20, 21, 22, 25, 29, 30, 31, 32, 33, 34, 41, 67]
#BONI_LIST_WEAPON = [3, 4, 5, 6, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22]
#BONI_LIST_NECKLACE = [1, 10, 11, 13, 15, 16, 24, 29, 30, 31, 32, 33, 34, 66, 68]
#BONI_LIST_WEAPON_ADDON = [3, 4, 5, 6, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 71, 72]
#BONI_SWITCHER_LOAD = TRUE
#BONI_SWITCHER_ACTIVE = [FALSE, FALSE, FALSE, FALSE, FALSE]
##########################################
## BONISWITCHER ENTRIES [END]
##########################################

# option
IN_GAME_SHOP_ENABLE = 1
CONSOLE_ENABLE = 0

PVPMODE_ENABLE = 1
PVPMODE_TEST_ENABLE = 0
PVPMODE_ACCELKEY_ENABLE = 1
PVPMODE_ACCELKEY_DELAY = 0.5
PVPMODE_PROTECTED_LEVEL = 30

FOG_LEVEL0 = 4800.0
FOG_LEVEL1 = 9600.0
FOG_LEVEL2 = 12800.0
FOG_LEVEL = FOG_LEVEL0
FOG_LEVEL_LIST=[FOG_LEVEL0, FOG_LEVEL1, FOG_LEVEL2]		

CAMERA_MAX_DISTANCE_SHORT = 2500.0
CAMERA_MAX_DISTANCE_LONG = 3500.0
CAMERA_MAX_DISTANCE_LIST=[CAMERA_MAX_DISTANCE_SHORT, CAMERA_MAX_DISTANCE_LONG]
CAMERA_MAX_DISTANCE = CAMERA_MAX_DISTANCE_SHORT

CHRNAME_COLOR_INDEX = 0

ENVIRONMENT_NIGHT="d:/ymir work/environment/moonlight04.msenv"

# constant
HIGH_PRICE = 500000
MIDDLE_PRICE = 50000
ERROR_METIN_STONE = 28960
SUB2_LOADING_ENABLE = 1
EXPANDED_COMBO_ENABLE = 1
CONVERT_EMPIRE_LANGUAGE_ENABLE = 1
USE_ITEM_WEAPON_TABLE_ATTACK_BONUS = 0
ADD_DEF_BONUS_ENABLE = 1
LOGIN_COUNT_LIMIT_ENABLE = 0

USE_SKILL_EFFECT_UPGRADE_ENABLE = 1

VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD = 1
GUILD_MONEY_PER_GSP = 100
GUILD_WAR_TYPE_SELECT_ENABLE = 1
TWO_HANDED_WEAPON_ATT_SPEED_DECREASE_VALUE = 0

HAIR_COLOR_ENABLE = 1
ARMOR_SPECULAR_ENABLE = 1
WEAPON_SPECULAR_ENABLE = 1
SEQUENCE_PACKET_ENABLE = 1
KEEP_ACCOUNT_CONNETION_ENABLE = 1
MINIMAP_POSITIONINFO_ENABLE = 0
CONVERT_EMPIRE_LANGUAGE_ENABLE = 0
USE_ITEM_WEAPON_TABLE_ATTACK_BONUS = 0
ADD_DEF_BONUS_ENABLE = 0
LOGIN_COUNT_LIMIT_ENABLE = 0
PVPMODE_PROTECTED_LEVEL = 15
TWO_HANDED_WEAPON_ATT_SPEED_DECREASE_VALUE = 10

isItemDropQuestionDialog = 0

def GET_ITEM_DROP_QUESTION_DIALOG_STATUS():
	global isItemDropQuestionDialog
	return isItemDropQuestionDialog

def SET_ITEM_DROP_QUESTION_DIALOG_STATUS(flag):
	global isItemDropQuestionDialog
	isItemDropQuestionDialog = flag

import app
import net

########################

def SET_DEFAULT_FOG_LEVEL():
	global FOG_LEVEL
	app.SetMinFog(FOG_LEVEL)

def SET_FOG_LEVEL_INDEX(index):
	global FOG_LEVEL
	global FOG_LEVEL_LIST
	try:
		FOG_LEVEL=FOG_LEVEL_LIST[index]
	except IndexError:
		FOG_LEVEL=FOG_LEVEL_LIST[0]
	app.SetMinFog(FOG_LEVEL)

def GET_FOG_LEVEL_INDEX():
	global FOG_LEVEL
	global FOG_LEVEL_LIST
	return FOG_LEVEL_LIST.index(FOG_LEVEL)

########################

def SET_DEFAULT_CAMERA_MAX_DISTANCE():
	global CAMERA_MAX_DISTANCE
	app.SetCameraMaxDistance(CAMERA_MAX_DISTANCE)

def SET_CAMERA_MAX_DISTANCE_INDEX(index):
	global CAMERA_MAX_DISTANCE
	global CAMERA_MAX_DISTANCE_LIST
	try:
		CAMERA_MAX_DISTANCE=CAMERA_MAX_DISTANCE_LIST[index]
	except:
		CAMERA_MAX_DISTANCE=CAMERA_MAX_DISTANCE_LIST[0]

	app.SetCameraMaxDistance(CAMERA_MAX_DISTANCE)

def GET_CAMERA_MAX_DISTANCE_INDEX():
	global CAMERA_MAX_DISTANCE
	global CAMERA_MAX_DISTANCE_LIST
	return CAMERA_MAX_DISTANCE_LIST.index(CAMERA_MAX_DISTANCE)

########################

import chrmgr
import player
import app

def SET_DEFAULT_CHRNAME_COLOR():
	global CHRNAME_COLOR_INDEX
	chrmgr.SetEmpireNameMode(CHRNAME_COLOR_INDEX)

def SET_CHRNAME_COLOR_INDEX(index):
	global CHRNAME_COLOR_INDEX
	CHRNAME_COLOR_INDEX=index
	chrmgr.SetEmpireNameMode(index)

def GET_CHRNAME_COLOR_INDEX():
	global CHRNAME_COLOR_INDEX
	return CHRNAME_COLOR_INDEX

def SET_VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD(index):
	global VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD
	VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD = index

def GET_VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD():
	global VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD
	return VIEW_OTHER_EMPIRE_PLAYER_TARGET_BOARD

def SET_DEFAULT_CONVERT_EMPIRE_LANGUAGE_ENABLE():
	global CONVERT_EMPIRE_LANGUAGE_ENABLE
	net.SetEmpireLanguageMode(CONVERT_EMPIRE_LANGUAGE_ENABLE)

def SET_DEFAULT_USE_ITEM_WEAPON_TABLE_ATTACK_BONUS():
	global USE_ITEM_WEAPON_TABLE_ATTACK_BONUS
	player.SetWeaponAttackBonusFlag(USE_ITEM_WEAPON_TABLE_ATTACK_BONUS)

def SET_DEFAULT_USE_SKILL_EFFECT_ENABLE():
	global USE_SKILL_EFFECT_UPGRADE_ENABLE
	app.SetSkillEffectUpgradeEnable(USE_SKILL_EFFECT_UPGRADE_ENABLE)

def SET_TWO_HANDED_WEAPON_ATT_SPEED_DECREASE_VALUE():
	global TWO_HANDED_WEAPON_ATT_SPEED_DECREASE_VALUE
	app.SetTwoHandedWeaponAttSpeedDecreaseValue(TWO_HANDED_WEAPON_ATT_SPEED_DECREASE_VALUE)

########################
import item

ACCESSORY_MATERIAL_LIST = [50623, 50624, 50625, 50626, 50627, 50628, 50629, 50630, 50631, 50632, 50633, 50634, 50635, 50636, 50637, 50638]
#ACCESSORY_MATERIAL_LIST = [50623, 50623, 50624, 50624, 50625, 50625, 50626, 50627, 50628, 50629, 50630, 50631, 50632, 50633, 
#			    50623, 50623, 50624, 50624, ]
JewelAccessoryInfos = [
		# jewel		wrist	neck	ear
		[ 50634,	14420,	16220,	17220 ],	
		[ 50635,	14500,	16500,	17500 ],	
		[ 50636,	14520,	16520,	17520 ],	
		[ 50637,	14540,	16540,	17540 ],	
		[ 50638,	14560,	16560,	17560 ],	
	]
def GET_ACCESSORY_MATERIAL_VNUM(vnum, subType):
	ret = vnum
	item_base = (vnum / 10) * 10
	for info in JewelAccessoryInfos:
		if item.ARMOR_WRIST == subType:	
			if info[1] == item_base:
				return info[0]
		elif item.ARMOR_NECK == subType:	
			if info[2] == item_base:
				return info[0]
		elif item.ARMOR_EAR == subType:	
			if info[3] == item_base:
				return info[0]
 
	if vnum >= 16210 and vnum <= 16219:
		return 50625

	if item.ARMOR_WRIST == subType:	
		WRIST_ITEM_VNUM_BASE = 14000
		ret -= WRIST_ITEM_VNUM_BASE
	elif item.ARMOR_NECK == subType:
		NECK_ITEM_VNUM_BASE = 16000
		ret -= NECK_ITEM_VNUM_BASE
	elif item.ARMOR_EAR == subType:
		EAR_ITEM_VNUM_BASE = 17000
		ret -= EAR_ITEM_VNUM_BASE

	type = ret/20

	if type<0 or type>=len(ACCESSORY_MATERIAL_LIST):
		type = (ret-170) / 20
		if type<0 or type>=len(ACCESSORY_MATERIAL_LIST):
			return 0

	return ACCESSORY_MATERIAL_LIST[type]

##################################################################
## »õ·Î Ãß°¡µÈ 'º§Æ®' ¾ÆÀÌÅÛ Å¸ÀÔ°ú, º§Æ®ÀÇ ¼ÒÄÏ¿¡ ²ÈÀ» ¾ÆÀÌÅÛ °ü·Ã.. 
## º§Æ®ÀÇ ¼ÒÄÏ½Ã½ºÅÛÀº ¾Ç¼¼¼­¸®¿Í µ¿ÀÏÇÏ±â ¶§¹®¿¡, À§ ¾Ç¼¼¼­¸® °ü·Ã ÇÏµåÄÚµùÃ³·³ ÀÌ·±½ÄÀ¸·Î ÇÒ ¼ö¹Û¿¡ ¾ø´Ù..

def GET_BELT_MATERIAL_VNUM(vnum, subType = 0):
	# ÇöÀç´Â ¸ğµç º§Æ®¿¡´Â ÇÏ³ªÀÇ ¾ÆÀÌÅÛ(#18900)¸¸ »ğÀÔ °¡´É
	return 18900
	
	
## ÀÚµ¿¹°¾à (HP: #72723 ~ #72726, SP: #72727 ~ #72730)

# ÇØ´ç vnumÀÌ ÀÚµ¿¹°¾àÀÎ°¡?
def IS_AUTO_POTION(itemVnum):
	return IS_AUTO_POTION_HP(itemVnum) or IS_AUTO_POTION_SP(itemVnum)
	
# ÇØ´ç vnumÀÌ HP ÀÚµ¿¹°¾àÀÎ°¡?
def IS_AUTO_POTION_HP(itemVnum):
	if 72723 <= itemVnum and 72726 >= itemVnum:
		return 1
	elif itemVnum >= 76021 and itemVnum <= 76022:		## »õ·Î µé¾î°£ ¼±¹°¿ë È­·æÀÇ Ãàº¹
		return 1
	elif itemVnum == 79012:
		return 1
		
	return 0
	
# ÇØ´ç vnumÀÌ SP ÀÚµ¿¹°¾àÀÎ°¡?
def IS_AUTO_POTION_SP(itemVnum):
	if 72727 <= itemVnum and 72730 >= itemVnum:
		return 1
	elif itemVnum >= 76004 and itemVnum <= 76005:		## »õ·Î µé¾î°£ ¼±¹°¿ë ¼ö·æÀÇ Ãàº¹
		return 1
	elif itemVnum == 79013:
		return 1
				
	return 0
def WriteLineInFile(fname, linenum, s):
	import os
	farr = []
	if os.path.exists(fname):
		f = open(fname, "r")
		for line in f:
			farr.append(line)
		f.close()
	while len(farr) < int(linenum):
		farr.append("")
	farr[int(linenum)-1] = str(s)
	f = open(fname, "w")
	for line in farr:
		f.write(line)
		if (len(line) > 0 and line[-1:] != "\n") or len(line) == 0:
			f.write("\n")
	f.close()

def ReadLineInFile(fname, linenum):
	import os
	if not os.path.exists(fname):
		return ""
	f = open(fname, "r")
	farr = []
	for line in f:
		farr.append(line)
	f.close()
	if len(farr) >= int(linenum):
		ret = farr[int(linenum)-1]
		if ret[-1:] == "\n":
			return ret[:-1]
		else:
			return ret
	else:
		return ""

