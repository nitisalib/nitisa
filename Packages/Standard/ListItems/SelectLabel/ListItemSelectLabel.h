// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Label/ListItemLabel.h"
#include "../IListItemSelectLabel.h"

namespace nitisa
{
	namespace standard
	{
		class CListItemSelectLabel :public virtual IListItemSelectLabel, public CListItemLabel
		{
		public:
			CListItemSelectLabel();
			CListItemSelectLabel(const String &caption);
		};
	}
}