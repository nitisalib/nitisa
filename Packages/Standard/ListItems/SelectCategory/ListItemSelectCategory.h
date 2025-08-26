// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Label/ListItemLabel.h"
#include "../IListItemSelectCategory.h"

namespace nitisa
{
	namespace standard
	{
		class CListItemSelectCategory :public virtual IListItemSelectCategory, public CListItemLabel
		{
		public:
			IFont *getFont() override;

			bool setVisible(const bool value) override;

			CListItemSelectCategory();
			CListItemSelectCategory(const String &caption);
		};
	}
}