import net
import player
import item
import snd
import shop
import net
import wndMgr
import app
import chat

import ui
import uiCommon
import mouseModule
import localeInfo

###################################################################################################
## Shop
class ShopDialog(ui.ScriptWindow):

	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.tooltipItem = 0
		self.xShopStart = 0
		self.yShopStart = 0
		self.questionDialog = None
		self.popup = None
		self.itemBuyQuestionDialog = None

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def Refresh(self):
		getItemID=shop.GetItemID
		getItemCount=shop.GetItemCount
		setItemID=self.itemSlotWindow.SetItemSlot
		for i in xrange(shop.SHOP_SLOT_COUNT):
			itemCount = getItemCount(i)
			if itemCount <= 1:
				itemCount = 0
			setItemID(i, getItemID(i), itemCount)

		wndMgr.RefreshSlot(self.itemSlotWindow.GetWindowHandle())

	def SetItemData(self, pos, itemID, itemCount, itemPrice):
		shop.SetItemData(pos, itemID, itemCount, itemPrice)

	def LoadDialog(self):
		try:
			PythonScriptLoader = ui.PythonScriptLoader()
			PythonScriptLoader.LoadScriptFile(self, "UIScript/shopdialog.py")
		except:
			import exception
			exception.Abort("ShopDialog.LoadDialog.LoadObject")

		try:
			GetObject = self.GetChild
			self.itemSlotWindow = GetObject("ItemSlot")
			self.btnBuy = GetObject("BuyButton")
			self.btnSell = GetObject("SellButton")
			self.btnClose = GetObject("CloseButton")
			self.titleBar = GetObject("TitleBar")
		except:
			import exception
			exception.Abort("ShopDialog.LoadDialog.BindObject")

		self.itemSlotWindow.SetSlotStyle(wndMgr.SLOT_STYLE_NONE)
		self.itemSlotWindow.SAFE_SetButtonEvent("LEFT", "EMPTY", self.SelectEmptySlot)
		self.itemSlotWindow.SAFE_SetButtonEvent("LEFT", "EXIST", self.SelectItemSlot)
		self.itemSlotWindow.SAFE_SetButtonEvent("RIGHT", "EXIST", self.UnselectItemSlot)

		self.itemSlotWindow.SetOverInItemEvent(ui.__mem_func__(self.OverInItem))
		self.itemSlotWindow.SetOverOutItemEvent(ui.__mem_func__(self.OverOutItem))

		self.btnBuy.SetToggleUpEvent(ui.__mem_func__(self.CancelShopping))
		self.btnBuy.SetToggleDownEvent(ui.__mem_func__(self.OnBuy))

		self.btnSell.SetToggleUpEvent(ui.__mem_func__(self.CancelShopping))
		self.btnSell.SetToggleDownEvent(ui.__mem_func__(self.OnSell))

		self.btnClose.SetEvent(ui.__mem_func__(self.AskClosePrivateShop))

		self.titleBar.SetCloseEvent(ui.__mem_func__(self.Close))

		self.Refresh()

	def Destroy(self):
		self.Close()
		self.ClearDictionary()

		self.tooltipItem = 0
		self.itemSlotWindow = 0
		self.btnBuy = 0
		self.btnSell = 0
		self.btnClose = 0
		self.titleBar = 0
		self.questionDialog = None
		self.popup = None

	def Open(self, vid):

		isPrivateShop = FALSE
		isMainPlayerPrivateShop = FALSE

		import chr
		if chr.IsNPC(vid):
			isPrivateShop = FALSE
		else:
			isPrivateShop = TRUE

		if player.IsMainCharacterIndex(vid):

			isMainPlayerPrivateShop = TRUE

			self.btnBuy.Hide()
			self.btnSell.Hide()
			self.btnClose.Show()

		else:

			isMainPlayerPrivateShop = FALSE

			self.btnBuy.Show()
			self.btnSell.Show()
			self.btnClose.Hide()

		shop.Open(isPrivateShop, isMainPlayerPrivateShop)
		self.Refresh()
		self.SetTop()
		self.Show()

		(self.xShopStart, self.yShopStart, z) = player.GetMainCharacterPosition()

	def Close(self):
		self.OnCloseQuestionDialog()
		shop.Close()
		net.SendShopEndPacket()
		self.CancelShopping()
		self.tooltipItem.HideToolTip()
		self.Hide()

	def AskClosePrivateShop(self):
		questionDialog = uiCommon.QuestionDialog()
		questionDialog.SetText(localeInfo.PRIVATE_SHOP_CLOSE_QUESTION)
		questionDialog.SetAcceptEvent(ui.__mem_func__(self.OnClosePrivateShop))
		questionDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseQuestionDialog))
		questionDialog.Open()
		self.questionDialog = questionDialog

		return TRUE

	def OnClosePrivateShop(self):
		net.SendChatPacket("/close_shop")
		self.OnCloseQuestionDialog()
		return TRUE

	def OnPressEscapeKey(self):
		self.Close()
		return TRUE

	def OnPressExitKey(self):
		self.Close()
		return TRUE

	def OnBuy(self):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SHOP_BUY_INFO)
		app.SetCursor(app.BUY)
		self.btnSell.SetUp()

	def OnSell(self):
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SHOP_SELL_INFO)
		app.SetCursor(app.SELL)
		self.btnBuy.SetUp()

	def CancelShopping(self):
		self.btnBuy.SetUp()
		self.btnSell.SetUp()
		app.SetCursor(app.NORMAL)

	def __OnClosePopupDialog(self):
		self.pop = None

	def SellAttachedItem(self):

		if shop.IsPrivateShop():
			mouseModule.mouseController.DeattachObject()
			return

		attachedSlotType = mouseModule.mouseController.GetAttachedType()
		attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
		attachedCount = mouseModule.mouseController.GetAttachedItemCount()
		if player.SLOT_TYPE_INVENTORY == attachedSlotType:

			itemIndex = player.GetItemIndex(attachedSlotPos)
			item.SelectItem(itemIndex)

			if item.IsAntiFlag(item.ANTIFLAG_SELL):
				popup = uiCommon.PopupDialog()
				popup.SetText(localeInfo.SHOP_CANNOT_SELL_ITEM)
				popup.SetAcceptEvent(self.__OnClosePopupDialog)
				popup.Open()
				self.popup = popup

			elif player.IsValuableItem(attachedSlotPos):

				itemPrice = item.GetISellItemPrice()

				if item.Is1GoldItem():
					itemPrice = attachedCount / itemPrice / 5
				else:
					itemPrice = itemPrice * max(1, attachedCount) / 5

				itemName = item.GetItemName()

				questionDialog = uiCommon.QuestionDialog()
				questionDialog.SetText(localeInfo.DO_YOU_SELL_ITEM(itemName, attachedCount, itemPrice))

				questionDialog.SetAcceptEvent(lambda arg1=attachedSlotPos, arg2=attachedCount: self.OnSellItem(arg1, arg2))
				questionDialog.SetCancelEvent(ui.__mem_func__(self.OnCloseQuestionDialog))
				questionDialog.Open()
				self.questionDialog = questionDialog

			else:
				self.OnSellItem(attachedSlotPos, attachedCount)

		else:
			snd.PlaySound("sound/ui/loginfail.wav")

		mouseModule.mouseController.DeattachObject()

	def OnSellItem(self, slotPos, count):
		net.SendShopSellPacketNew(slotPos, count)
		snd.PlaySound("sound/ui/money.wav")
		self.OnCloseQuestionDialog()

	def OnCloseQuestionDialog(self):
		if self.questionDialog:
			self.questionDialog.Close()

		self.questionDialog = None

	def SelectEmptySlot(self, selectedSlotPos):

		isAttached = mouseModule.mouseController.isAttached()
		if isAttached:
			self.SellAttachedItem()

	def UnselectItemSlot(self, selectedSlotPos):
		if shop.IsPrivateShop():
			self.AskBuyItem(selectedSlotPos)
		else:
			net.SendShopBuyPacket(selectedSlotPos)

	def SelectItemSlot(self, selectedSlotPos):

		isAttached = mouseModule.mouseController.isAttached()
		if isAttached:
			self.SellAttachedItem()

		else:

			if TRUE == shop.IsMainPlayerPrivateShop():
				return

			curCursorNum = app.GetCursor()
			if app.BUY == curCursorNum:
				self.AskBuyItem(selectedSlotPos)

			elif app.SELL == curCursorNum:
				chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.SHOP_SELL_INFO)

			else:
				selectedItemID = shop.GetItemID(selectedSlotPos)
				itemCount = shop.GetItemCount(selectedSlotPos)

				type = player.SLOT_TYPE_SHOP
				if shop.IsPrivateShop():
					type = player.SLOT_TYPE_PRIVATE_SHOP

				mouseModule.mouseController.AttachObject(self, type, selectedSlotPos, selectedItemID, itemCount)
				mouseModule.mouseController.SetCallBack("INVENTORY", ui.__mem_func__(self.DropToInventory))
				snd.PlaySound("sound/ui/pick.wav")

	def DropToInventory(self):
		attachedSlotPos = mouseModule.mouseController.GetAttachedSlotNumber()
		self.AskBuyItem(attachedSlotPos)

	def AskBuyItem(self, slotPos):
		itemIndex = shop.GetItemID(slotPos)
		itemPrice = shop.GetItemPrice(slotPos)
		itemCount = shop.GetItemCount(slotPos)

		item.SelectItem(itemIndex)
		itemName = item.GetItemName()

		itemBuyQuestionDialog = uiCommon.QuestionDialog()
		itemBuyQuestionDialog.SetText(localeInfo.DO_YOU_BUY_ITEM(itemName, itemCount, localeInfo.NumberToMoneyString(itemPrice)))
		itemBuyQuestionDialog.SetAcceptEvent(lambda arg=TRUE: self.AnswerBuyItem(arg))
		itemBuyQuestionDialog.SetCancelEvent(lambda arg=FALSE: self.AnswerBuyItem(arg))
		itemBuyQuestionDialog.Open()
		itemBuyQuestionDialog.pos = slotPos
		self.itemBuyQuestionDialog = itemBuyQuestionDialog

	def AnswerBuyItem(self, flag):

		if flag:
			pos = self.itemBuyQuestionDialog.pos
			net.SendShopBuyPacket(pos)

		self.itemBuyQuestionDialog.Close()
		self.itemBuyQuestionDialog = None

	def SetItemToolTip(self, tooltipItem):
		self.tooltipItem = tooltipItem

	def OverInItem(self, slotIndex):
		if mouseModule.mouseController.isAttached():
			return

		if 0 != self.tooltipItem:
			self.tooltipItem.SetShopItem(slotIndex)

	def OverOutItem(self):
		if 0 != self.tooltipItem:
			self.tooltipItem.HideToolTip()

	def OnUpdate(self):

		USE_SHOP_LIMIT_RANGE = 1000

		(x, y, z) = player.GetMainCharacterPosition()
		if abs(x - self.xShopStart) > USE_SHOP_LIMIT_RANGE or abs(y - self.yShopStart) > USE_SHOP_LIMIT_RANGE:
			self.Close()


class MallPageDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def Destroy(self):
		self.ClearDictionary()

	def Open(self):
		scriptLoader = ui.PythonScriptLoader()
		scriptLoader.LoadScriptFile(self, "uiscript/mallpagedialog.py")

		self.GetChild("titlebar").SetCloseEvent(ui.__mem_func__(self.Close))
		
		(x, y)=self.GetGlobalPosition()
		x+=10
		y+=30
		
		MALL_PAGE_WIDTH = 600
		MALL_PAGE_HEIGHT = 480
		
		app.ShowWebPage(
			"http://metin2.co.kr/08_mall/game_mall/login_fail.htm", 
			(x, y, x+MALL_PAGE_WIDTH, y+MALL_PAGE_HEIGHT))

		self.Lock()
		self.Show()
		
	def Close(self):			
		app.HideWebPage()
		self.Unlock()
		self.Hide()
		
	def OnPressEscapeKey(self):
		self.Close()
		return TRUE
