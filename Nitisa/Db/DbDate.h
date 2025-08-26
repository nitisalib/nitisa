// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	struct DbDate
	{
		short Year;
		unsigned short Month;
		unsigned short Day;

		explicit operator String() const; // Convert to Unicode string in YYYY-MM-DD format
		explicit operator AnsiString() const; // Convert to ANSI string in YYYY-MM-DD format

		bool operator==(const DbDate &other) const;
		bool operator!=(const DbDate &other) const;
		bool operator>(const DbDate &other) const;
		bool operator>=(const DbDate &other) const;
		bool operator<(const DbDate &other) const;
		bool operator<=(const DbDate &other) const;
	};
}