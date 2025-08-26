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
	enum class Align // Control alignment
	{
		None, // None, use position and size specified in control
		Left, // Aligned to the left
		Top, // Aligned to the top
		Right, // Aligned to the right
		Bottom, // Aligned to the bottom
		Client // Fills all client area of parent
	};

	Align StringToAlign(const String &value);
	String AlignToString(const Align value);
	StringArray AlignItems();
}