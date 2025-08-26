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
	enum class ScrollVisibility // Scrollbar visibility type
	{
		Auto, // Visible when required and hidden when doesn't
		Visible, // Always visible
		None // Never visible
	};

	String ScrollVisibilityToString(const ScrollVisibility value);
	ScrollVisibility StringToScrollVisibility(const String &value);
	StringArray ScrollVisibilityItems();
}