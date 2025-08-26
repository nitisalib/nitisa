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
	struct DbTime
	{
		unsigned short Hour;
		unsigned short Minute;
		unsigned short Second;

		explicit operator String() const; // Convert to Unicode string in HH:MM:SS format
		explicit operator AnsiString() const; // Convert to ANSI string in HH:MM:SS format

		bool operator==(const DbTime &other) const;
		bool operator!=(const DbTime &other) const;
		bool operator>(const DbTime &other) const;
		bool operator>=(const DbTime &other) const;
		bool operator<(const DbTime &other) const;
		bool operator<=(const DbTime &other) const;
	};
}