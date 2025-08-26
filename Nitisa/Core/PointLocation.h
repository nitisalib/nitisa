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
	enum class PointLocation // Location in Block
	{
		Left = 0, // Left border
		Top = 1, // Top border
		Right = 2, // Right border
		Bottom = 3, // Bottom border
		Inside = 4, // Inside
		Outside = 5, // Outside
	};
}