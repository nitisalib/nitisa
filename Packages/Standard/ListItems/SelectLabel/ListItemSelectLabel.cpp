// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CListItemSelectLabel::CListItemSelectLabel():
			CListItemLabel()
		{
			setPadding(RectF{ 16, 2, 2, 2 });
		}

		CListItemSelectLabel::CListItemSelectLabel(const String &caption) :
			CListItemLabel(caption)
		{
			setPadding(RectF{ 16, 2, 2, 2 });
		}
	}
}