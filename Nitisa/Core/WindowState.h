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
	enum class WindowState // Window states
	{
		Normal, // Normal
		Maximized, // Maximized
		Minimized, // Minimized
		Hidden // Hidden
	};

	String WindowStateToString(const WindowState value);
	WindowState StringToWindowState(const String &value);
	StringArray WindowStateItems();
}