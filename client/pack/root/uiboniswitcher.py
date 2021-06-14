import ui
import wndMgr
import player
import item
import time
import shop
import net
import constInfo
import grp
import app
import mouseModule

SWITCHER_VNUM = 71084

class BoniSwitcherEditLine(ui.EditLine):

	def __init__(self, bordercolor):
		ui.EditLine.__init__(self)
		self.borders = []
		for i in xrange(7+1):
			self.borders.append(ui.Line())
			self.borders[len(self.borders)-1].SetParent(self)
			self.borders[len(self.borders)-1].SetColor(bordercolor)
			self.borders[len(self.borders)-1].Show()

	def RefreshBorders(self):
		(x, y, width, height) = self.GetRect()
		x = -3
		y = -3
		self.borders[0].SetSize(width-3, 0)
		self.borders[0].SetPosition(x+2, y)
		self.borders[1].SetSize(width-3, 0)
		self.borders[1].SetPosition(x+2, y+height)
		self.borders[2].SetSize(0, height-4)
		self.borders[2].SetPosition(x, y+2)
		self.borders[3].SetSize(0, height-3)
		self.borders[3].SetPosition(x+width, y+1)
		self.borders[4].SetSize(2, -2)
		self.borders[4].SetPosition(x, y+2)
		self.borders[5].SetSize(2, 2)
		self.borders[5].SetPosition(x, y+height-2)
		self.borders[6].SetSize(2, 2)
		self.borders[6].SetPosition(x+width-2, y)
		self.borders[7].SetSize(2, -2)
		self.borders[7].SetPosition(x+width-2, y+height)

	def SetSize(self, width, height):
		ui.EditLine.SetSize(self, width, height)
		self.RefreshBorders()

	def SetPosition(self, x, y):
		ui.EditLine.SetPosition(self, x, y)
		self.RefreshBorders()

class BoniSwitcherDialog(ui.ScriptWindow):

	def __init__(self, itempos):
		ui.ScriptWindow.__init__(self)

		self.defaultItemPos = int(itempos)
		self.aktItemPos = int(itempos)
		self.aktItem = -1
		self.resetBoni = TRUE

		self.bonilist_pos = 0
		self.bonilist_scrollsize = 0
		self.bonilist_maxentry = 12
		self.bonilist_selindex = -1
		
		self.boniattr =  [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
		self.bonivalues = [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
		
		self.is_switching = 0
		self.switchingItem = 0
		self.lastSwitchingTime = 0
		self.resetChoosedItemTitleColor = 0
		self.speed = 0.5
		self.ShowEditLine = FALSE

		self.save_line_start = 4
		self.save_lines_need = 12
		
		self.ChangeBonusSwitcherEvent = lambda : None
		self.HasBoniSwitcherPos = lambda : None

		self.state = "NORMAL"

		self.__Load()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def Destroy(self):
		self.SaveBoni()
		self.Hide()
		return TRUE

	def GetFileStartLine(self, pos=-1):
		if pos <= -1:
			pos = self.defaultItemPos
		return self.save_line_start + self.save_lines_need * pos

	def SaveBoni(self):
		for a in xrange(len(self.boniattr)):
			for b in xrange(len(self.boniattr[a])):
				constInfo.WriteLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + a*len(self.boniattr[a]) + b, str(self.boniattr[a][b])+","+str(self.bonivalues[a][b]))
		constInfo.WriteLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + len(self.boniattr)*len(self.boniattr[0]), str(self.is_switching))
		constInfo.WriteLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + len(self.boniattr)*len(self.boniattr[0])+1, str(self.ChangeSpeedSlider.GetSliderPos()))

	def LoadBoni(self):
		for a in xrange(len(self.boniattr)):
			for b in xrange(len(self.boniattr[a])):
				line = constInfo.ReadLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + a*len(self.boniattr[a]) + b).split(",")
				if len(line) != 2:
					line = ["0", "0"]
				try:
					self.boniattr[a][b] = int(line[0])
				except:
					self.boniattr[a][b] = 0
				try:
					self.bonivalues[a][b] = int(line[1])
				except:
					self.bonivalues[a][b] = 0
		try:
			is_switching = int(constInfo.ReadLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + len(self.boniattr)*len(self.boniattr[0])))
			if is_switching == TRUE and self.is_switching == FALSE:
				self.ClickStartButton()
			elif is_switching == FALSE and self.is_switching == TRUE:
				self.ClickStartButton()
		except:
			pass
		try:
			self.ChangeSpeedSlider.SetSliderPos(float(constInfo.ReadLineInFile(constInfo.OPTION_FILE_NAME, self.GetFileStartLine() + len(self.boniattr)*len(self.boniattr[0])+1)))
		except:
			pass

	def __Load_LoadScript(self, fileName):
		try:
			pyScriptLoader = ui.PythonScriptLoader()
			pyScriptLoader.LoadScriptFile(self, fileName)
		except:
			import exception
			exception.Abort("BoniSwitcherDialog.__Load_LoadScript")

	def __Load_BindObject(self):
		try:
			self.board = self.GetChild("board")
			self.title = self.GetChild("titlebar")
		except:
			import exception
			exception.Abort("BoniSwitcherDialog.__Load_BindObject")

		self.title.SetCloseEvent(self.Hide)
		self.GetChild("title").SetText("Boni ändern ("+str(self.defaultItemPos+1)+". Gegenstand)")

	def __Load_CreateObject(self):
		self.board.SetClickEvent(self.CheckForAttachedItem)

		self.bonuschangerwindow = ui.Window()
		self.bonuschangerwindow.SetParent(self)
		self.bonuschangerwindow.SetSize(38 * 5 + 4 * 2, 19)
		self.bonuschangerwindow.SetPosition(0, self.title.GetHeight())
		self.bonuschangerwindow.SetWindowHorizontalAlignCenter()
		self.bonuschangerwindow.SetClickEvent(self.CheckForAttachedItem)
		self.bonuschangerwindow.Show()
		
		self.bonuschanger_choose = []
		for i in xrange(constInfo.SWITCHER_COUNT):
			self.bonuschanger_choose.append(ui.Button())
			self.bonuschanger_choose[i].SetParent(self.bonuschangerwindow)
			self.bonuschanger_choose[i].SetPosition(38 * i + 2 * i, 0)
			self.bonuschanger_choose[i].SetUpVisual("d:/ymir work/ui/public/XSmall_Button_01.sub")
			self.bonuschanger_choose[i].SetOverVisual("d:/ymir work/ui/public/XSmall_Button_02.sub")
			self.bonuschanger_choose[i].SetDownVisual("d:/ymir work/ui/public/XSmall_Button_03.sub")
			self.bonuschanger_choose[i].SetText(str(i+1))
			self.bonuschanger_choose[i].SetEvent(self.ChangeBoniSwitcher, i)
			if self.defaultItemPos == i:
				self.bonuschanger_choose[i].Disable()
			self.bonuschanger_choose[i].Show()

		self.lines = []
		self.lines.append(ui.ExpandedImageBox())
		self.lines[0].SetParent(self)
		self.lines[0].LoadImage("d:/ymir work/ui/pattern/line_hr.tga")
		self.lines[0].SetRenderingRect(0, 0, -1.0 + float(float(self.GetWidth()-16*2+2) / 125), 0)
		self.lines[0].SetPosition(6, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight())
		self.lines[0].Show()
		
		self.bonilist_textline = ui.TextLine()
		self.bonilist_textline.SetParent(self)
		self.bonilist_textline.SetFontName("ARIAL:14")
		self.bonilist_textline.SetText("Bonus wählen")
		self.bonilist_textline.SetPosition(15, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 5)
		self.bonilist_textline.SetPackedFontColor(ui.GenerateColor(221, 141, 8))
		self.bonilist_textline.SetOutline()
		self.bonilist_textline.Show()
		
		self.bonilist = ui.ListBox()
		self.bonilist.SetParent(self)
		self.bonilist.SetSize(300, 205)
		self.bonilist.SetPosition(15, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 5 + 12)
		self.bonilist.Show()
		
		self.bonilist_scrollbar = ui.ScrollBar()
		self.bonilist_scrollbar.SetParent(self)
		self.bonilist_scrollbar.SetScrollBarSize(205)
		self.bonilist_scrollbar.SetPosition(315, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 5 + 12)
		self.bonilist_scrollbar.SetScrollEvent(self.OnScroll)
		self.bonilist_scrollbar.Show()

		self.bonivalue_textline = ui.TextLine()
		self.bonivalue_textline.SetParent(self)
		self.bonivalue_textline.SetPosition(20, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 5 + 223)
		self.bonivalue_textline.SetDefaultFontName()
		self.bonivalue_textline.SetText("Bonusstärke:")
		self.bonivalue_textline.Show()
		
		self.bonivalue = BoniSwitcherEditLine(ui.HALF_WHITE_COLOR)
		self.bonivalue.SetParent(self)
		self.bonivalue.SetSize(220, 18)
		self.bonivalue.SetPosition(96, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 5 + 223 + 1)
		self.bonivalue.SetNumberMode()
		self.bonivalue.SetMax(10)
		self.bonivalue.SetText("0")
		self.bonivalue.SetEscapeEvent(self.Hide)
		self.bonivalue.Show()
		
		self.lines.append(ui.ExpandedImageBox())
		self.lines[1].SetParent(self)
		self.lines[1].LoadImage("d:/ymir work/ui/pattern/line_vr.tga")
		self.lines[1].SetRenderingRect(0, 0, 0, -1.0 + float(float(8 + 223 + 1 + self.bonivalue.GetHeight() + 2) / 125))
		self.lines[1].SetPosition(320 + self.bonilist_scrollbar.GetWidth(), self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight())
		self.lines[1].Show()
		self.lines.append(ui.ExpandedImageBox())
		self.lines[2].SetParent(self)
		self.lines[2].LoadImage("d:/ymir work/ui/pattern/line_vr.tga")
		self.lines[2].SetRenderingRect(0, 0, 0, -1.0 + float(float(8 + 223 + 1 + self.bonivalue.GetHeight() + 2) / 125))
		self.lines[2].SetPosition(650 - 5 - self.lines[1].GetWidth(), self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight())
		self.lines[2].Show()
		self.lines.append(ui.ExpandedImageBox())
		self.lines[3].SetParent(self)
		self.lines[3].LoadImage("d:/ymir work/ui/pattern/line_hr.tga")
		self.lines[3].SetRenderingRect(0, 0, -1.0 + float(float(self.GetWidth()-16*2+2) / 125), 0)
		self.lines[3].SetPosition(6, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + self.lines[1].GetHeight() * 2)
		self.lines[3].Show()
		
		self.choosed_item_textline = ui.TextLine()
		self.choosed_item_textline.SetParent(self)
		self.choosed_item_textline.SetFontName("ARIAL:14")
		self.choosed_item_textline.SetText("Gewählter Gegenstand")
		self.choosed_item_textline.SetPosition(649, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 8)
		self.choosed_item_textline.SetPackedFontColor(ui.GenerateColor(221, 141, 8))
		self.choosed_item_textline.SetOutline()
		self.choosed_item_textline.Show()
		
		self.choosed_item_window = ui.Window()
		self.choosed_item_window.SetParent(self)
		self.choosed_item_window.SetSize(108, self.lines[1].GetHeight())
		self.choosed_item_window.SetPosition(650, self.title.GetHeight() + 2 * 3 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight())
		self.choosed_item_window.SetClickEvent(self.CheckForAttachedItem)
		self.choosed_item_window.Show()
		
		self.choosed_item = ui.ImageBox()
		self.choosed_item.SetParent(self.choosed_item_window)
		self.choosed_item.SetPosition(0, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight())
		self.choosed_item.SetWindowHorizontalAlignCenter()
		self.choosed_item.SetWindowVerticalAlignCenter()
		self.choosed_item.SAFE_SetStringEvent("MOUSE_OVER_IN", self.__OnMouseOverChoosedItem)
		self.choosed_item.SAFE_SetStringEvent("MOUSE_OVER_OUT", self.__OnMouseOutChoosedItem)
		self.choosed_item.SAFE_SetStringEvent("MOUSE_BUTTON_DOWN", self.CheckForAttachedItem)
		self.choosed_item.Hide()
		
		import uiToolTip
		self.choosed_item_tooltip = uiToolTip.ItemToolTip()
		self.choosed_item_tooltip.HideToolTip()
		
		self.boni_choose_item_textline = ui.TextLine()
		self.boni_choose_item_textline.SetParent(self)
		self.boni_choose_item_textline.SetFontName("ARIAL:14")
		self.boni_choose_item_textline.SetText("Boni einstellen")
		self.boni_choose_item_textline.SetPosition(320 + self.bonilist_scrollbar.GetWidth() + self.lines[1].GetWidth() + 8, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 8)
		self.boni_choose_item_textline.SetPackedFontColor(ui.GenerateColor(221, 141, 8))
		self.boni_choose_item_textline.SetOutline()
		self.boni_choose_item_textline.Show()

		self.bonichoosewindow = ui.Window()
		self.bonichoosewindow.SetParent(self)
		self.bonichoosewindow.SetSize(650 - 5 - self.lines[1].GetWidth() - 320 - self.bonilist_scrollbar.GetWidth() - self.lines[1].GetWidth(), self.GetHeight() - self.title.GetHeight() - 7 - 5)
		self.bonichoosewindow.SetPosition(320 + self.bonilist_scrollbar.GetWidth() + self.lines[1].GetWidth(), self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 8 + 22)
		self.bonichoosewindow.SetClickEvent(self.CheckForAttachedItem)
		self.bonichoosewindow.Show()

		self.bonustext = []
		self.bonusbutton = []
		for i in xrange(4+1):
			self.bonustext.append(ui.TextLine())
			self.bonustext[i].SetParent(self.bonichoosewindow)
			self.bonustext[i].SetPosition(0, i * (15 + 25 + 5))
			self.bonustext[i].SetDefaultFontName()
			self.bonustext[i].SetWindowHorizontalAlignCenter()
			self.bonustext[i].SetHorizontalAlignCenter()
			self.bonustext[i].SetText("Bonus "+str(i+1)+": Keiner gewählt")
			self.bonustext[i].Show()
			self.bonusbutton.append(ui.Button())
			self.bonusbutton[i].SetParent(self.bonichoosewindow)
			self.bonusbutton[i].SetPosition(0, i * (15 + 25 + 5) + 15)
			self.bonusbutton[i].SetUpVisual("d:/ymir work/ui/public/XLarge_Button_01.sub")
			self.bonusbutton[i].SetOverVisual("d:/ymir work/ui/public/XLarge_Button_02.sub")
			self.bonusbutton[i].SetDownVisual("d:/ymir work/ui/public/XLarge_Button_03.sub")
			self.bonusbutton[i].SetWindowHorizontalAlignCenter()
			self.bonusbutton[i].SetText("Bonus ändern")
			self.bonusbutton[i].SetEvent(self.ClickButton, i)
			self.bonusbutton[i].Show()

		self.bonusalternative = ui.Button()
		self.bonusalternative.SetParent(self)
		self.bonusalternative.SetPosition(320 + self.bonilist_scrollbar.GetWidth() + self.lines[1].GetWidth() + 8 + (650 - 5 - self.lines[1].GetWidth() - 320 - self.bonilist_scrollbar.GetWidth() - self.lines[1].GetWidth()) - 50, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + 8)
		self.bonusalternative.SetUpVisual("d:/ymir work/ui/public/XSmall_Button_01.sub")
		self.bonusalternative.SetOverVisual("d:/ymir work/ui/public/XSmall_Button_02.sub")
		self.bonusalternative.SetDownVisual("d:/ymir work/ui/public/XSmall_Button_03.sub")
		self.bonusalternative.SetText("A")
		self.bonusalternative.SetToolTipText("Zur alternativen Boniseite wechseln")
		self.bonusalternative.SetEvent(self.ClickAlternativeButton)
		self.bonusalternative.Show()

		self.StartButton = ui.Button()
		self.StartButton.SetParent(self)
		self.StartButton.SetPosition(30, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + self.lines[1].GetHeight() * 2 + self.lines[3].GetHeight() + 6)
		self.StartButton.SetUpVisual("d:/ymir work/ui/public/XLarge_Button_01.sub")
		self.StartButton.SetOverVisual("d:/ymir work/ui/public/XLarge_Button_02.sub")
		self.StartButton.SetDownVisual("d:/ymir work/ui/public/XLarge_Button_03.sub")
		self.StartButton.SetText("Starten")
		self.StartButton.SetEvent(self.ClickStartButton)
		self.StartButton.Show()
		
		self.ChangeSpeedSlider = ui.SliderBar()
		self.ChangeSpeedSlider.SetParent(self)
		self.ChangeSpeedSlider.SetPosition(0, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + self.lines[1].GetHeight() * 2 + self.lines[3].GetHeight() + 6)
		self.ChangeSpeedSlider.SetWindowHorizontalAlignCenter()
		self.ChangeSpeedSlider.SetEvent(self.OnChangeSpeedSlider)
		self.ChangeSpeedSlider.Show()
		
		self.ChangeSpeedText = ui.TextLine()
		self.ChangeSpeedText.SetParent(self)
		self.ChangeSpeedText.SetPosition(0, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + self.lines[1].GetHeight() * 2 + self.lines[3].GetHeight() + 6 + self.ChangeSpeedSlider.GetHeight() + 2)
		self.ChangeSpeedText.SetWindowHorizontalAlignCenter()
		self.ChangeSpeedText.SetHorizontalAlignCenter()
		self.ChangeSpeedText.SetText("1x pro Sekunde")
		self.ChangeSpeedText.Show()

		self.CloseButton = ui.Button()
		self.CloseButton.SetParent(self)
		self.CloseButton.SetPosition(self.GetWidth()-30-180, self.title.GetHeight() + 2 * 2 + self.bonuschangerwindow.GetHeight() + self.lines[0].GetHeight() + self.lines[1].GetHeight() * 2 + self.lines[3].GetHeight() + 6)
		self.CloseButton.SetUpVisual("d:/ymir work/ui/public/XLarge_Button_01.sub")
		self.CloseButton.SetOverVisual("d:/ymir work/ui/public/XLarge_Button_02.sub")
		self.CloseButton.SetDownVisual("d:/ymir work/ui/public/XLarge_Button_03.sub")
		self.CloseButton.SetText("Schlie"+chr(223)+"en")
		self.CloseButton.SetEvent(self.Hide)
		self.CloseButton.Show()

	def CheckForAttachedItem(self):
		if mouseModule.mouseController.isAttached():
			if player.SLOT_TYPE_INVENTORY == mouseModule.mouseController.GetAttachedType():
				slotIndex = int(mouseModule.mouseController.GetAttachedSlotNumber())
				item.SelectItem(player.GetItemIndex(slotIndex))
				if self.is_switching == 1:
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Du musst erst das Ändern der Boni stoppen.")
					self.choosed_item_textline.SetPackedFontColor(ui.GenerateColor(155, 20, 20))
					self.resetChoosedItemTitleColor = app.GetTime()+1
					return
				elif slotIndex == self.aktItemPos:
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast diesen Gegenstand bereits ausgewählt.")
					return
				elif slotIndex >= 0 and slotIndex <= 4 and self.HasBoniSwitcherPos(slotIndex) == TRUE:
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Dieser Gegenstand ist bereits von einem anderen Fenster ausgewählt.")
					return
				elif item.GetItemType() != 1 and item.GetItemType() != 2:
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Der Gegenstand muss eine Ausrüstung sein.")
					return
				self.aktItemPos = slotIndex
			mouseModule.mouseController.DeattachObject()

	def OnScroll(self):
		import math
		pos = self.bonilist_scrollbar.GetPos()
		itempos = math.floor(float(pos) / float(float(1) / float(self.bonilist.GetItemCount() - self.bonilist_maxentry)) + 0.001)
		if itempos != self.bonilist_pos:
			self.bonilist_pos = itempos
			self.bonilist.SetBasePos(itempos)

	def OnChangeSpeedSlider(self):
		pos = self.ChangeSpeedSlider.GetSliderPos()
		self.speed = 1.5 - (pos * 0.5 + 0.5)
		text = "1"
		if self.speed == 0.5:
			text = "2"
		elif self.speed < 1:
			text = str(float(int((pos * 0.5 + 0.5)*2*100+0.5)) / 100)[0:4]
		text = text + "x pro Sekunde"
		self.ChangeSpeedText.SetText(text)

	def __OnMouseOverChoosedItem(self):
		item.SelectItem(self.aktItem)
		if item.GetItemType() == 1 or item.GetItemType() == 2:
			self.choosed_item_tooltip.ClearToolTip()
			self.choosed_item_tooltip.SetInventoryItem(self.aktItemPos)
			self.choosed_item_tooltip.ShowToolTip()

	def __OnMouseOutChoosedItem(self):
		self.choosed_item_tooltip.HideToolTip()

	def ClickButton(self, buttonId):
		if constInfo.ATTR_BONI_LIST.count(self.bonilist.GetSelectedItemText()) <= 0:
			import chat
			chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast keinen oder einen ungültigen Bonus ausgewählt.")
			return
		elif int(self.bonivalue.GetText()) <= 0 and constInfo.BONI_LIST_NO_VALUE.count(constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText())) <= 0:
			import chat
			chat.AppendChat(chat.CHAT_TYPE_INFO, "Der mindestwert für einen Bonus ist 1.")
			return
		elif constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText()) > 0:
			for i in xrange(4+1):
				if constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText()) == self.boniattr[self.GetBonusPage()][i] and i != buttonId:
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Dieser Bonus ist bereits als "+str(i+1)+". Bonus gewählt.")
					return
		if constInfo.BONI_LIST_NO_VALUE.count(constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText())) <= 0 and constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText()) in constInfo.BONI_LIST_MAX_VALUE:
			if constInfo.BONI_LIST_MAX_VALUE[constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText())] < int(self.bonivalue.GetText()):
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Der Maximalwert für diesen Bonus beträgt +"+str(constInfo.BONI_LIST_MAX_VALUE[constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText())])+".")
				return
		self.boniattr[self.GetBonusPage()][buttonId] = constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText())
		self.bonivalues[self.GetBonusPage()][buttonId] = int(self.bonivalue.GetText())
		self.bonustext[buttonId].SetText("Bonus "+str(buttonId+1)+": "+constInfo.GetAttrText(constInfo.ATTR_BONI_LIST.index(self.bonilist.GetSelectedItemText()), self.bonivalue.GetText()))

	def ClickAlternativeButton(self):
		if self.state == "NORMAL":
			self.state = "ALTERNATIVE"
			self.bonusalternative.SetText("N")
			self.bonusalternative.SetToolTipText("Zur normalen Boniseite wechseln")
		else:
			self.state = "NORMAL"
			self.bonusalternative.SetText("A")
			self.bonusalternative.SetToolTipText("Zur alternativen Boniseite wechseln")
		self.SetBonusPage()

	def SetBonusPage(self, page=-1):
		if page == -1:
			page = self.GetBonusPage()
		for i in xrange(len(self.bonustext)):
			self.bonustext[i].SetText("Bonus "+str(i+1)+": "+constInfo.GetAttrText(self.boniattr[page][i], self.bonivalues[page][i]))

	def GetBonusPage(self, state=""):
		if state == "":
			state = self.state
		if state == "NORMAL":
			return 0
		else:
			return 1

	def ClickStartButton(self):
		if self.is_switching != 1:
			constInfo.BONI_SWITCHER_ACTIVE[self.defaultItemPos] = TRUE
			switchCount1 = 0
			switchCount2 = 0
			for i in xrange(4+1):
				if self.boniattr[self.GetBonusPage("NORMAL")][i] > 0 and (self.bonivalues[self.GetBonusPage("NORMAL")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("NORMAL")][i]) > 0):
					switchCount1 = switchCount1 + 1
				if self.boniattr[self.GetBonusPage("ALTERNATIVE")][i] > 0 and (self.bonivalues[self.GetBonusPage("ALTERNATIVE")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("ALTERNATIVE")][i]) > 0):
					switchCount2 = switchCount2 + 1
			if switchCount1 <= 0 and switchCount2 <= 0:
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast keinen Bonus angegeben.")
				return
			attrSlotCount = 0
			attrSlot = [player.GetItemAttribute(self.aktItemPos, i) for i in xrange(4+1)]
			for i in xrange(len(attrSlot)):
				if attrSlot[i][0] > 0 and attrSlot[i][1] > 0:
					attrSlotCount = attrSlotCount + 1
			if attrSlotCount < switchCount1:
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast nicht genügend eingefügte Boni, um alle eingegeben normalen Boni zu bekommen.")
				return
			elif attrSlotCount < switchCount2:
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast nicht genügend eingefügte Boni, um alle eingegeben alternativen Boni zu bekommen.")
				return
			elif self.GetBonusSwitcherIndex() <= -1:
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast keine Bonusänderungs-Gegenstände.")
				return
			elif self.CheckBonusSwitched() == 1:
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Du hast diese Boni bereits auf dem Gegenstand.")
				return
			for i in xrange(4+1):
				self.bonusbutton[i].Disable()
			self.StartButton.SetText("Abbrechen")
			self.switchingItem = player.GetItemIndex(self.aktItemPos)
			self.is_switching = 1
			import chat
			chat.AppendChat(chat.CHAT_TYPE_INFO, "Das Ändern der Boni wurde gestartet.")
		else:
			constInfo.BONI_SWITCHER_ACTIVE[self.defaultItemPos] = FALSE
			self.is_switching = 0
			for i in xrange(4+1):
				self.bonusbutton[i].Enable()
			self.StartButton.SetText("Starten")
			self.swiitchingResult = "Fehlgeschlagen wegen Abbruch"
			import chat
			chat.AppendChat(chat.CHAT_TYPE_INFO, "Das Ändern der Boni wurde abgebrochen.")

	def ChangeBoniSwitcher(self, index):
		self.ChangeBonusSwitcherEvent(index)

	def SetChangeBonusSwitcherEvent(self, event):
		self.ChangeBonusSwitcherEvent = ui.__mem_func__(event)

	def GetBonusSwitcherIndex(self):
		for i in xrange(player.INVENTORY_PAGE_SIZE*2):
			if player.GetItemIndex(i) == SWITCHER_VNUM:
				return i
		player_money = player.GetElk()
		for i in xrange(39+1):
			if shop.GetItemID(i) == SWITCHER_VNUM and shop.GetItemPrice(i) <= player_money:
				net.SendShopBuyPacket(i)
				return 0
		return -1

	def CheckBonusSwitched(self):
		res1 = 1
		res2 = 1
		switchCount1 = 0
		switchCount2 = 0
		for i in xrange(4+1):
			if self.boniattr[self.GetBonusPage("NORMAL")][i] > 0 and (self.bonivalues[self.GetBonusPage("NORMAL")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("NORMAL")][i]) > 0):
				switchCount1 = switchCount1 + 1
			if self.boniattr[self.GetBonusPage("ALTERNATIVE")][i] > 0 and (self.bonivalues[self.GetBonusPage("ALTERNATIVE")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("ALTERNATIVE")][i]) > 0):
				switchCount2 = switchCount2 + 1
		attrSlot = [player.GetItemAttribute(self.aktItemPos, i) for i in xrange(4+1)]
		if switchCount1 > 0:
			for i in xrange(len(self.boniattr[self.GetBonusPage("NORMAL")])):
				attrFound = 0
				for x in xrange(len(attrSlot)):
					if self.boniattr[self.GetBonusPage("NORMAL")][i] <= 0 or (self.bonivalues[self.GetBonusPage("NORMAL")][i] <= 0 and constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("NORMAL")][i]) == 0) or (self.boniattr[self.GetBonusPage("NORMAL")][i] != 0 and (self.bonivalues[self.GetBonusPage("NORMAL")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("NORMAL")][i]) > 0) and (attrSlot[x][0] == self.boniattr[self.GetBonusPage("NORMAL")][i] and (attrSlot[x][1] >= self.bonivalues[self.GetBonusPage("NORMAL")][i] or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("NORMAL")][i]) > 0))):
						attrFound = 1
					if x >= len(attrSlot) - 1 and attrFound == 0:
						res1 = 0
						break
		else:
			res1 = 0
		if switchCount2 > 0:
			for i in xrange(len(self.boniattr[self.GetBonusPage("ALTERNATIVE")])):
				attrFound = 0
				for x in xrange(len(attrSlot)):
					if self.boniattr[self.GetBonusPage("ALTERNATIVE")][i] <= 0 or (self.bonivalues[self.GetBonusPage("ALTERNATIVE")][i] <= 0 and constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("ALTERNATIVE")][i]) == 0) or (self.boniattr[self.GetBonusPage("ALTERNATIVE")][i] != 0 and (self.bonivalues[self.GetBonusPage("ALTERNATIVE")][i] > 0 or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("ALTERNATIVE")][i]) > 0) and (attrSlot[x][0] == self.boniattr[self.GetBonusPage("ALTERNATIVE")][i] and (attrSlot[x][1] >= self.bonivalues[self.GetBonusPage("ALTERNATIVE")][i] or constInfo.BONI_LIST_NO_VALUE.count(self.boniattr[self.GetBonusPage("ALTERNATIVE")][i]) > 0))):
						attrFound = 1
					if x >= len(attrSlot) - 1 and attrFound == 0:
						res2 = 0
						break
		else:
			res2 = 0
		res = 0
		if res1 == 1 and res2 == 1:
			res = 3
		elif res1 == 1:
			res = 1
		elif res2 == 1:
			res = 2
		return res

	def __Load(self):
		self.__Load_LoadScript("uiscript/boniswitcherboard.py")
		self.__Load_BindObject()
		self.__Load_CreateObject()
		self.resetBoni = FALSE
		self.LoadBoni()
		for i in xrange(len(self.boniattr[self.GetBonusPage()])):
			self.bonustext[i].SetText("Bonus "+str(i+1)+": "+constInfo.GetAttrText(self.boniattr[self.GetBonusPage()][i], self.bonivalues[self.GetBonusPage()][i]))

	def OnUpdate(self):
		self.checkAktItem()
		if self.is_switching == 1 and self.choosed_item_tooltip.IsShow():
			self.choosed_item_tooltip.ClearToolTip()
			self.choosed_item_tooltip.SetInventoryItem(self.aktItemPos)
		if self.is_switching == 1 and self.lastSwitchingTime < time.clock():
			check = self.CheckBonusSwitched()
			if check != 0:
				constInfo.BONI_SWITCHER_ACTIVE[self.defaultItemPos] = FALSE
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "------------------------------------")
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Das Ändern der Boni war erfolgreich!")
				if check == 1:
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Die normalen Boni wurden erreicht!")
				elif check == 2:
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Die alternativen Boni wurden erreicht!")
				elif check == 3:
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Die normalen und alternativen Boni wurden erreicht!")
				chat.AppendChat(chat.CHAT_TYPE_INFO, "------------------------------------")
				for i in xrange(4+1):
					self.bonusbutton[i].Enable()
				self.is_switching = 0
				self.StartButton.SetText("Starten")
			else:
				switcherId = self.GetBonusSwitcherIndex()
				if switcherId <= -1:
					constInfo.BONI_SWITCHER_ACTIVE[self.defaultItemPos] = FALSE
					import chat
					chat.AppendChat(chat.CHAT_TYPE_INFO, "------------------------------------")
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Der Bonusänderungs-Gegenstand ist nicht mehr vorhanden.")
					chat.AppendChat(chat.CHAT_TYPE_INFO, "Das Ändern der Boni ist fehlgeschlagen.")
					chat.AppendChat(chat.CHAT_TYPE_INFO, "------------------------------------")
					for i in xrange(4+1):
						self.bonusbutton[i].Enable()
					self.StartButton.SetText("Starten")
					self.is_switching = 0
				elif switcherId > 0:
					net.SendItemUseToItemPacket(switcherId, self.aktItemPos)
				self.lastSwitchingTime = time.clock() + self.speed
		if self.resetChoosedItemTitleColor > 0 and app.GetTime() >= self.resetChoosedItemTitleColor:
			self.resetChoosedItemTitleColor = 0
			self.choosed_item_textline.SetPackedFontColor(ui.GenerateColor(221, 141, 8))

	def SecToDate(self, s):
		s = int(s)
		days = 0
		while s >= 60*60*24:
			days = days + 1
			s = s - 60*60*24
		hours = 0
		while s >= 60*60*1:
			hours = hours + 1
			s = s - 60*60*1
		if hours <= 9:
			hours = "0"+str(hours)
		minutes = 0
		while s >= 60*1:
			minutes = minutes + 1
			s = s - 60*1
		if minutes <= 9:
			minutes = "0"+str(minutes)
		if s <= 9:
			s = "0"+str(s)
		res_str = ""
		if days > 0:
			res_str = str(days) + " Tag"
			if days > 1:
				res_str = res_str + "e"
		if hours > 0 or minutes > 0 or s > 0:
			if days > 0:
				res_str = res_str + " "
			res_str = res_str + str(hours) + ":" + str(minutes) + ":" + str(s)
		return res_str

	def checkAktItem(self, nocheck=0):
		if (player.GetItemIndex(self.aktItemPos) != self.aktItem or nocheck == 1) and constInfo.BONI_SWITCHER_LOAD == TRUE:
			if self.is_switching == 1 and player.GetItemIndex(self.aktItemPos) != self.aktItem:
				constInfo.BONI_SWITCHER_ACTIVE[self.defaultItemPos] = FALSE
				self.is_switching = 0
				for i in xrange(4+1):
					self.bonusbutton[i].Enable()
				self.ChangeSpeedSlider.Show()
				self.ChangeSpeedText.Show()
				self.StartButton.SetText("Starten")
				import chat
				chat.AppendChat(chat.CHAT_TYPE_INFO, "Das Ändern der Boni wurde wegen Gegenstandswechsel abgebrochen.")
			self.aktItem = player.GetItemIndex(self.aktItemPos)
			self.state = "NORMAL"
			self.boniattr = [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
			self.bonivalues = [[0, 0, 0, 0, 0], [0, 0, 0, 0, 0]]
			self.bonilist.ClearItem()
			self.bonilist.SetBasePos(0)
			self.bonilist.InsertItem(0, constInfo.ATTR_BONI_LIST[0])
			if self.aktItem == 0:
				self.ShowEditLine = FALSE
				self.bonivalue_textline.Hide()
				self.bonivalue.Hide()
				self.ChangeSpeedSlider.Hide()
				self.ChangeSpeedText.Hide()
				self.bonilist_scrollbar.Hide()
				self.choosed_item.Hide()
				for i in xrange(4+1):
					self.bonustext[i].SetText("Bonus "+str(i+1)+": Keiner")
					self.bonusbutton[i].Disable()
				self.StartButton.Disable()
			else:
				item.SelectItem(self.aktItem)
				if item.GetItemType() != 1 and item.GetItemType() != 2:
					self.ShowEditLine = FALSE
					self.bonivalue_textline.Hide()
					self.bonivalue.Hide()
					self.ChangeSpeedSlider.Hide()
					self.ChangeSpeedText.Hide()
					self.bonilist_scrollbar.Hide()
					self.choosed_item.Hide()
					for i in xrange(4+1):
						self.bonustext[i].SetText("Bonus "+str(i+1)+": Keiner")
						self.bonusbutton[i].Disable()
					self.StartButton.Disable()
				else:
					self.ChangeSpeedSlider.Show()
					self.ChangeSpeedText.Show()
					for i in xrange(4+1):
						self.bonusbutton[i].Enable()
					if self.resetBoni == TRUE:
						attrSlot = [player.GetItemAttribute(self.aktItemPos, i) for i in xrange(4+1)]
						for i in xrange(len(attrSlot)):
							self.boniattr[self.GetBonusPage()][i] = attrSlot[i][0]
							self.bonivalues[self.GetBonusPage()][i] = attrSlot[i][1]
							self.bonustext[i].SetText("Bonus "+str(i+1)+": "+constInfo.GetAttrText(attrSlot[i][0], attrSlot[i][1]))
					else:
						self.resetBoni = TRUE
					list = self.GetBoniList(self.aktItem, item.GetItemType(), item.GetItemSubType())
					for i in xrange(len(list)):
						self.bonilist.InsertItem(i+1, constInfo.ATTR_BONI_LIST[list[i]])
					if len(list) > self.bonilist_maxentry:
						self.bonilist_scrollsize = float(float(self.bonilist_maxentry)/len(list))
						self.bonilist_scrollbar.SetMiddleBarSize(float(float(self.bonilist_maxentry)/len(list)))
						self.bonilist_scrollbar.SetPos(0)
						self.bonilist_scrollbar.Show()
					else:
						self.bonilist_scrollbar.Hide()
					self.choosed_item.LoadImage(item.GetIconImageFileName())
					self.choosed_item.Show()
					self.ShowEditLine = TRUE
					self.bonivalue_textline.Show()
					self.bonivalue.Show()
					self.bonichoosewindow.Show()
					self.StartButton.Enable()

	def GetBoniList(self, itemVNum, itemType, itemSubType):
		if itemType == 1:
			if constInfo.ITEM_LIST_WEAPON_ADDON.count(self.GetHighestUpgradeItemVnum(itemVNum)) == 1:
				return constInfo.BONI_LIST_WEAPON_ADDON
			else:
				return constInfo.BONI_LIST_WEAPON
		elif itemSubType == 0:
			return constInfo.BONI_LIST_ARMOR
		elif itemSubType == 1:
			return constInfo.BONI_LIST_HELMET
		elif itemSubType == 2:
			return constInfo.BONI_LIST_SHIELD
		elif itemSubType == 3:
			return constInfo.BONI_LIST_BRACELET
		elif itemSubType == 4:
			return constInfo.BONI_LIST_BOOTS
		elif itemSubType == 5:
			return constInfo.BONI_LIST_NECKLACE
		elif itemSubType == 6:
			return constInfo.BONI_LIST_EARRINGS
		else:
			return []

	def GetHighestUpgradeItemVnum(self, itemVNum):
		itemVNum = str(itemVNum)
		while itemVNum[len(itemVNum)-1] != '9':
			itemVNum = str(int(itemVNum) + 1)
		return int(itemVNum)

	def GAMESetBoniSwitcherCheckEvent(self, event):
		self.HasBoniSwitcherPos = event

	def Show(self, checkItem=TRUE):
		if checkItem == TRUE:
			self.checkAktItem(1)
		else:
			self.checkAktItem()
		wndMgr.Show(self.hWnd)

	def OnPressEscapeKey(self):
		self.Hide()
		return TRUE
