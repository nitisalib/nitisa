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
	enum class CursorType // Cursor types
	{
		None,
		AppStarting, // Standard arrow and small hourglass
		Arrow, // Standard arrow
		Cross, // Crosshair
		Hand, // Hand
		Help, // Arrow and question mark
		IBeam, // I-beam
		No, // Slashed circle
		SizeAll, // Four-pointed arrow pointing north, south, east, and west
		SizeNortheastSouthwest, // Double-pointed arrow pointing northeast and southwest
		SizeNorthSouth, // Double-pointed arrow pointing north and south
		SizeNorthwestSoutheast, // Double-pointed arrow pointing northwest and southeast
		SizeWestEast, // Double-pointed arrow pointing west and east
		UpArrow, // Vertical arrow
		Wait // Hourglass
	};

	CursorType StringToCursorType(const String &value);
	String CursorTypeToString(const CursorType value);
	StringArray CursorTypeItems();
}