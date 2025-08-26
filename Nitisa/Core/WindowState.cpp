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
	String WindowStateToString(const WindowState value)
	{
		switch (value)
		{
		case WindowState::Maximized:	return L"WindowState::Maximized";
		case WindowState::Minimized:	return L"WindowState::Minimized";
		case WindowState::Hidden:		return L"WindowState::Hidden";
		default:						return L"WindowState::Normal";
		}
	}

	WindowState StringToWindowState(const String &value)
	{
		if (value == L"WindowState::Maximized")
			return WindowState::Maximized;
		if (value == L"WindowState::Minimized")
			return WindowState::Minimized;
		if (value == L"WindowState::Hidden")
			return WindowState::Hidden;
		return WindowState::Normal;
	}

	StringArray WindowStateItems()
	{
		return StringArray{
			L"WindowState::Normal",
			L"WindowState::Maximized",
			L"WindowState::Minimized",
			L"WindowState::Hidden" };
	}
}