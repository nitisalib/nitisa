// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	enum class FocusedBy // Identifies how control was focused
	{
		Tab, // By Tab key
		ShiftTab, // By Shift+Tab combination
		LeftMouse, // By left mouse button down
		MiddleMouse, // By middle mouse button down
		RightMouse, // By right mouse button down
		Refocus, // Gain focus agian after form deactivation and activation after
		Other // Any other way
	};
}