// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"

namespace nitisa
{
	enum class WindowPosition // Window position
	{
		ScreenLeftTop,
		ScreenRightTop,
		ScreenLeftBottom,
		ScreenRightBottom,
		ScreenCenter,
		MainFormLeftTop,
		MainFormRightTop,
		MainFormLeftBottom,
		MainFormRightBottom,
		MainFormCenter,
		Custom // Specified in Position member of creation params
	};

	String WindowPositionToString(const WindowPosition value);
	WindowPosition StringToWindowPosition(const String &value);
	StringArray WindowPositionItems();
}