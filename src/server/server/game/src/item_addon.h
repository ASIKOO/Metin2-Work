#ifndef __ITEM_ADDON_H
#define __ITEM_ADDON_H

class CItemAddonManager : public singleton<CItemAddonManager>
{
	public:
		CItemAddonManager();
		virtual ~CItemAddonManager();

		void ApplyAddonTo(int32_t iAddonType, LPITEM pItem);
};

#endif
