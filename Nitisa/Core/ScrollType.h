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
	enum class ScrollType // Window scrolling request
	{
		None, // None
		EndScroll, // Ends scroll
		Left, // Scroll to the upper left
		Right, // Scrolls to the lower right
		LineLeft, // Scrolls left by one unit
		LineRight, // Scrolls right by one unit
		PageLeft, // Scrolls left by the width of the window
		PageRight, // Scrolls right by the width of the window
		ThumbPosition, // The user has dragged the scroll box (thumb) and released the mouse button
		ThumbTrack // The user is dragging the scroll box
	};
}