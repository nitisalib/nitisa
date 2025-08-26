// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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
		CFileList::CFileListItem::CFileListItem(const String &caption) : CListItemLabel(caption)
		{
			setColor(State::Hovered, Color{ 0, 0, 0, 0 });
			setColor(State::Active, Color{ 0, 0, 0, 0 });
			setColor(State::ActiveHovered, Color{ 0, 0, 0, 0 });
			setBackgroundColor(State::Hovered, Color{ 0, 0, 0, 0 });
			for (int i = (int)State::Active; i <= (int)State::ActiveSelectedHovered; i++)
			{
				setBorderWidth((State)i, RectF{ 1, 1, 1, 1 });
				setBorderColor((State)i, BorderColor{ Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 }, Color{ 0, 0, 0, 255 } });
			}
			setBackgroundColor(State::Active, Color{ 0, 0, 0, 0 });
			setBackgroundColor(State::ActiveHovered, Color{ 0, 0, 0, 0 });
		}
	}
}