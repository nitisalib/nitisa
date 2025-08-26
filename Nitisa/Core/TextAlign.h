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
	enum class TextAlign // Text horizontal alignment
	{
		Left, // Aligned to the left
		Center, // Aligned to the center horizontally
		Right // Aligned to the right
	};

	TextAlign StringToTextAlign(const String &value);
	String TextAlignToString(const TextAlign value);
	StringArray TextAlignItems();
}