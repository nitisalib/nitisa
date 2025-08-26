// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ListItemService.h"
#include "Nitisa/Math/Point.h"
#include "../IListItemMenu.h"

namespace nitisa
{
	namespace standard
	{
		class CListItemMenu;

		class CListItemMenuService :public virtual IListItemMenuService, public CListItemService
		{
		private:
			CListItemMenu *m_pListItem;
			Point m_sDPI;
		public:
			CListItemMenuService(CListItemMenu *listitem);

			float getIconWidth() override;
			float getHotkeyWidth() override;
			float getArrowWidth() override;

			bool setDPI(const Point &value) override;
			bool setIconWidth(const float value) override;
			bool setHotkeyWidth(const float value) override;
			bool setArrowWidth(const float value) override;

			bool NotifyOnHotkey() override;

			Point getDPI() const;
		};
	}
}