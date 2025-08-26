// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	enum class GradientType // Supported gradient types
	{
		Horizontal = 0, // Horizontal(from left to right)
		Vertical = 1, // Vertical(from top to bottom)
		Radial = 2, // Radial(from center)
		DiagonalDown = 3, // From left-top to right-bottom
		DiagonalUp = 4, // From left-bottom to right-top
		Circle = 5 // The same as gtRadial but drawing appears only inside circle which radius is maximum of width and height of the rectangle where drawing is
	};

	String GradientTypeToString(const GradientType value);
}