// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	struct DbSupportedScalarStringFunctions
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool ASCII;
		bool BitLength;
		bool Char;
		bool CharLength;
		bool CharacterLength;
		bool Concat;
		bool Difference;
		bool Insert;
		bool LCase;
		bool Left;
		bool Length;
		bool Locate;
		bool Locate2;
		bool LTrim;
		bool OctetLength;
		bool Position;
		bool Repeat;
		bool Replace;
		bool Right;
		bool RTrim;
		bool SoundEx;
		bool Space;
		bool SubString;
		bool UCase;

		explicit operator String() const;
	};
}