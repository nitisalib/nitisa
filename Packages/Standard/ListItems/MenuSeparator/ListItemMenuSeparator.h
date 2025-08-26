// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Key.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Math/Mat4f.h"
#include "../Menu/ListItemMenu.h"

namespace nitisa
{
	class IListItem;
	class IListItemService;
	class IStyle;

	struct Block;

	namespace standard
	{
		class CListItemMenuSeparatorService;

		class CListItemMenuSeparator :public CListItemMenu
		{
			friend CListItemMenuSeparatorService;
		private:
			IListItemMenuService *m_pService;
			float m_fHeight;
			Color m_sColor;

			bool m_bIgnoreEnabled;

			bool setEnabledInternal(const bool value);
			void UpdateFromStyle(IStyle *style);
			void Render(const Mat4f &matrix, const Block *block);
		public:
			CListItemMenuSeparator();
			~CListItemMenuSeparator() override;

			bool setEnabled(const bool value) override;
			bool setSelected(const bool value) override;
			bool setActive(const bool value) override;

			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;
			bool AddHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool down) override;

			IListItemService *QueryService() override;

			float getHeight() const; // Return height
			Color getColor() const; // Return color

			bool setHeight(const float value); // Set height
			bool setColor(const Color &value); // Set color

			IListItem *Clone() override;
			bool Copy(IListItem *dest) override;
		};
	}
}