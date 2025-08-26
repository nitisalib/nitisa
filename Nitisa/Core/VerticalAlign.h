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
	enum class VerticalAlign // Text vertical alignement
	{
		Top, // Aligned to the top
		Middle, // Aligned to the center vertically
		Bottom // Aligned to the bottom
	};

	VerticalAlign StringToVerticalAlign(const String &value);
	String VerticalAlignToString(const VerticalAlign value);
	StringArray VerticalAlignItems();
}