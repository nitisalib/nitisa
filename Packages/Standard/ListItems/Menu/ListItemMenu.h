// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Hotkey.h"
#include "Nitisa/Core/Key.h"
#include "Nitisa/Core/ListItem.h"
#include "Nitisa/Core/Strings.h"
#include "../IListItemMenu.h"
#include <vector>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IListItem;
	class IListItemService;

	namespace standard
	{
		class CListItemMenuService;

		class CListItemMenu :public virtual IListItemMenu, public CListItem
		{
			friend CListItemMenuService;
		private:
			float m_fIconWidth;
			float m_fHotkeyWidth;
			float m_fArrowWidth;
			std::vector<Hotkey> m_aHotkeys;
			IListItemMenuService *m_pService;
			bool m_bDestroying;
		public:
			CListItemMenu(const String &class_name, const bool accept_items);
			~CListItemMenu() override;

			int getHotkeyCount() override;
			Hotkey getHotkey(const int index) override;
			String getHotkeys() override;

			bool AddHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool down) override;
			bool DeleteHotkey(const int index) override;
			bool DeleteHotkeys() override;

			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;

			IListItemService *QueryService() override;
		};
	}
}