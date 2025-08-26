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
	enum class EdgeType // Window edges and corners
	{
		None, // None
		Bottom, // Bottom border
		BottomLeft, // Left-bottom corner
		BottomRight, // Right-bottom corner
		Left, // Left border
		Right, // Right border
		Top, // Top border
		TopLeft, // Left-top corner
		TopRight // Right-top corner
	};
}