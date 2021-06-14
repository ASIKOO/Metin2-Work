#!/usr/bin/python
# -*- coding: latin-1 -*-
import ui
import chat
import app
import player
import snd
import item
import net
import game

class BonusBoardDialog(ui.ScriptWindow):
	MaxBoni = { "1": 999000, "2": 999, "3": 999, "4": 999, "5": 999, "6": 999, "7": 999, "9": 999, "10": 999, "11": 999, "12": 999, "13": 999, "14": 999, "15": 999, "16": 999, "17": 999, "18": 999, "19": 999, "20": 999, "21": 999, "22": 999, "23": 999, "24": 999, "27": 999, "28": 999, "29": 999, "30": 999, "31": 999, "32": 999, "33": 999, "34": 999, "35": 999, "36": 999, "37": 999, "38": 999, "39": 999, "41": 999, "43": 999, "44": 999, "45": 999, "48": 1, "53": 999 }
	BonusDict = ["Bonus PvP", "Bonus PvE", "Autre"]
	BonusIDListe = [["", 0, 0],["PV", 1, 0],["PM", 2, 0],["VIT", 3, 0],["INT", 4, 0],
	["STR", 5, 0],["DEX", 6, 0],["Vitesse d'attaque", 7, 0],["Vitesse de déplacement", 8, 0],
	["Vitesse du sort", 9, 0],["Régénération PV", 10, 32],["Régénération PM", 11, 33],
	["Chance d’empoisonner", 12, 37],["Chance de stun", 13, 38],["Chance de ralentir", 14, 39],
	["Coup Critique", 15, 40],["Coup perçant", 16, 41],
	["DH", 17, 43],["Animaux", 18, 44],
	["Orc", 19, 45],["Mystiques", 20, 46],
	["MV", 21, 47],["Mal", 22, 48],
	["Drain PV", 23, 63],["Drain PM", 24, 64],
	["Chance de regen PV", 25, 65],["Chance de regen PM", 26, 66],
	["Bloquer Cac", 27, 67],["Evite fléche", 28, 68],
	["Def. Epée", 29, 69],["Def. Epée 2 mains ", 30, 70],
	["Def. Dague", 31, 71],["Def. Gong", 32, 72],
	["Def. Event", 33, 73],["Rés. fléches", 34, 74],
	["Rés. feu", 35, 75],["Rés. Lumiére", 36, 76],
	["Rés. Magie", 37, 77],["Rés. Vent", 38, 78],["Détourner Cac", 39, 79],
	["Odbicie ciosow", 40, 80],["Rés. psn", 41, 81],
	["Restaurer Pm", 42, 82],["EXP", 43, 83],
	["Chance de drop x2 yang", 44, 84],["Chance de drop x2 objet", 45, 85],
	["Augmentation des effets de la potion", 46, 86],["Chance de restaurer les PV", 47, 87],
	["Immunise contre l'étourdissement", 48, 88],["Immunise contre le ralentissement", 49, 89],
	["Immunise contre les chutes", 50, 90],["APPLY_SKILL", 51, 0],["Portée de l'Arc", 52, 95],
	["Valeur d'attaque", 53, 0],["Défense", 54, 96],["Valeur d'attaque magique", 55, 97],
	["Défense magique", 56, 98],["", 57, 0],["Max endurance", 58, 0],
	["Bonus contre les Guerriers", 59, 54],["Bonus contre les N", 60, 55],
	["Bonus contre les S", 61, 56],["Bonus contre les Sh", 62, 57],
	["Monstres", 63, 53],["Valeur d'attaque", 64, 114],
	["Défense", 65, 115],["EXP (IS)", 66, 116],["Drop Objet (IS)", 67, 117],
	["Drop yang (IS)", 68, 118],["APPLY_MAX_HP_PCT", 69, 119],["APPLY_MAX_SP_PCT", 70, 120],
	["DC", 71, 121],["DM", 72, 122],["Rés. DC", 73, 123],["Rés. DM", 74, 124],["", 75, 0],
	["iCafe EXP", 76, 125],["iCafe Item-Bonus", 77, 126],["Parer G", 78, 59],
	["Parer N", 79, 60],["Parer S", 80, 61],["Parer Sh", 81, 62]]
	SpecialBoni = { 1: "Norm.State", 2: "Norm.State", 3: "Norm.State", 4: "Norm.State", 5: "Norm.State", 6: "Norm.State", 55: "Norm.State", 56: "Norm.State", 58: "Norm.State" }
	PvPOffenseBoni = ["Parer G", "Parer N", "Parer S", "Parer Sh", "Bonus contre les Guerriers", "Bonus contre les N", "Bonus contre les S", "Bonus contre les Sh", "DH"]
	PvPDefenseBoni = ["Def. Epée", "Def. Epée 2 mains ", "Def. Dague", "Def. Gong", "Def. Event", "Rés. fléches", "Evite fléche", "Rés. Magie", "Bloquer Cac", "Niewrazliwy na Omdlenia"]
	PvMOffenseBoni = ["Monstres", "Mal", "MV", "Animaux", "Orc", "Mystiques", "Chance de stun", "Chance d’empoisonner", "Chance de ralentir"]
	PvMDefenseBoni = ["Chance de regen PV", "Chance de regen PM", "Drain PV", "Drain PM"]
	LeftoversOffenseBoni = ["Coup Critique", "Coup perçant", "Vitesse d'attaque", "Vitesse de déplacement", "Vitesse du sort", "PV", "PM", "DM", "DC"]
	LeftoversDefenseBoni = ["Rés. DM", "Rés. DC", "VIT", "INT", "STR", "DEX"]

	BonusList = []
	UI = []
	
	TestSystem = 0
	ProcessTimeStamp = 0
	
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.LoadUI()
		game.BPisLoaded = 1
		
	def __del__(self):
		ui.ScriptWindow.__del__(self)
		self.Board.Hide()
		game.BPisLoaded = 0
	
	def LoadUI(self):
		self.Board = ui.BoardWithTitleBar()
		self.Board.SetSize(313, 420)
		self.Board.SetCenterPosition()
		self.Board.AddFlag("movable")
		self.Board.AddFlag("float")
		self.Board.SetTitleName("Bonus")
		self.Board.SetCloseEvent(self.__del__)
		self.Board.Show()
		
		Vertical = ui.Line()
		Vertical.SetParent(self.Board)
		Vertical.SetPosition(8, 60)
		Vertical.SetSize(297, 0)
		Vertical.SetColor(0xff777777)
		Vertical.Show()
		self.UI.append(Vertical)
		
		x = 25
		for i in xrange(3):
			ChangeBonusDict = ui.Button()
			ChangeBonusDict.SetParent(self.Board)
			ChangeBonusDict.SetUpVisual("d:/ymir work/ui/public/large_button_01.sub")
			ChangeBonusDict.SetOverVisual("d:/ymir work/ui/public/large_button_02.sub")
			ChangeBonusDict.SetDownVisual("d:/ymir work/ui/public/large_button_03.sub")
			ChangeBonusDict.SetText(self.BonusDict[i])
			ChangeBonusDict.SetPosition(x, 380)
			ChangeBonusDict.SetEvent(lambda arg = ChangeBonusDict.GetText(): self.ChangeBonusDict(arg))
			ChangeBonusDict.Show()
			x += 88
			self.UI.append(ChangeBonusDict)
		
		x = 55
		Type = ["", ""]
		for i in xrange(2):
			BonusDescription = ui.TextLine()
			BonusDescription.SetParent(self.Board)
			BonusDescription.SetPosition(x, 35)
			BonusDescription.SetText(str(Type[i]))
			BonusDescription.SetFontColor(1.0, 0.63, 0)
			BonusDescription.Show()			
			x += 150
			self.UI.append(BonusDescription)

		self.SetBoni(self.BonusDict[0])
		self.dict = self.BonusDict[0]
		
	def SetBoni(self, type):
		Offense = [[25, 70], [25, 100], [25, 130], [25, 160], [25, 190], [25, 220], [25, 250], [25, 280], [25, 310], [25, 340]]
		Defense = [[170, 70], [170, 100], [170, 130], [170, 160], [170, 190], [170, 220], [170, 250], [170, 280], [170, 310], [170, 340]]
		for bonus in self.BonusIDListe:
			if type == self.BonusDict[0]:
				self.CheckBonus(bonus, self.PvPOffenseBoni, Offense)
				self.CheckBonus(bonus, self.PvPDefenseBoni, Defense)
			elif type == self.BonusDict[1]:
				self.CheckBonus(bonus, self.PvMOffenseBoni, Offense)
				self.CheckBonus(bonus, self.PvMDefenseBoni, Defense)
			elif type == self.BonusDict[2]:
				self.CheckBonus(bonus, self.LeftoversOffenseBoni, Offense)
				self.CheckBonus(bonus, self.LeftoversDefenseBoni, Defense)
			else:
				return
				
	def CheckBonus(self, bonus, bonuslist, offset):
		for boni in bonuslist:
			if bonus[0] == boni:
				try:
					Index = bonuslist.index(boni)
					BonusDescription = ui.TextLine()
					BonusDescription.SetParent(self.Board)
					BonusDescription.SetPosition(offset[Index][0], offset[Index][1])
					BonusDescription.SetText(str(bonus[0]))
					BonusDescription.Show()
					
					BonusSlotBar = ui.SlotBar()
					BonusSlotBar.SetParent(self.Board)
					BonusSlotBar.SetSize(115, 15)
					BonusSlotBar.SetPosition(offset[Index][0], offset[Index][1] + 15)
					BonusSlotBar.Show()
					
					BonusAttrLine = ui.TextLine()
					BonusAttrLine.SetParent(self.Board)
					BonusAttrLine.SetPosition(offset[Index][0] + 5, offset[Index][1] + 15)
					
					try:
						Type = self.SpecialBoni[bonus[1]]
						Attribute = self.EquipAttribute(bonus)
					except:
						Attribute = player.GetStatus(int(bonus[2]))
					if self.TestSystem != 1:
						BonusAttrLine.SetText(str(Attribute))
						try:
							if int(Attribute) >= int(self.MaxBoni[str(bonus[1])]):
								BonusAttrLine.SetFontColor(1.0, 0.63, 0)
							else:
								BonusAttrLine.SetFontColor(1, 1, 1)
						except:
							BonusAttrLine.SetFontColor(1, 1, 1)
					else:
						BonusAttrLine.SetText("Test system is active")
						BonusAttrLine.SetFontColor(0.1, 0.7, 1.0)
					
					BonusAttrLine.Show()
					self.BonusList.append([BonusDescription, BonusAttrLine, BonusSlotBar])
				except:
					pass		
				
	def EquipAttribute(self, bonus):
		value = 0
		for slot in xrange(90, 101):
			for attr in xrange(0, 7):
				attr, val = player.GetItemAttribute(slot, attr)
				if int(attr) == bonus[1]:
					value += int(val)
		return int(value)

	def ChangeBonusDict(self, dict):
		self.dict = dict
		for bonus in self.BonusList:
			try:
				for array in bonus:
					array.Hide()
			except:
				pass			
		self.SetBoni(dict)
		
	def OnUpdate(self):
		import item
		if int(app.GetTime()) > int(self.ProcessTimeStamp) + 6:
			self.SetBoni(self.dict)
			self.ProcessTimeStamp = app.GetTime()

#BonusBoardDialog().Show()
