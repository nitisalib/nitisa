// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/ListItem.h"
#include "Nitisa/Core/Strings.h"
#include "../IListItemStatusPanel.h"

namespace nitisa
{
	class IListItem;

	namespace standard
	{
		class CListItemStatusPanel :public virtual IListItemStatusPanel, public CListItem
		{
		private:
			float m_fWidth;
		public:
			float getWidth() override;

			bool setWidth(const float value) override;

			bool Copy(IListItem *dest) override;

			CListItemStatusPanel(const String &class_name);
		};
	}
}