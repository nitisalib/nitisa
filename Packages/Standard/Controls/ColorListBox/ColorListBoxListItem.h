// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "../../ListItems/Color/ListItemColor.h"

namespace nitisa
{
	namespace standard
	{
		class CColorListBoxListItem :public CListItemColor
		{
		public:
			CColorListBoxListItem(const Color &color, const String &caption);
		};
	}
}