// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/DateTime.h"
#include "../Core/Strings.h"
#include "DbDate.h"
#include "DbTime.h"

namespace nitisa
{
	struct DbDateTime
	{
		DbDate Date;
		DbTime Time;
		unsigned int NanoSecond;

		explicit operator String() const; // Convert to Unicode string in YYYY-MM-DD HH:MM:SS format
		explicit operator AnsiString() const; // Convert to ANSI string in YYYY-MM-DD HH:MM:SS format
		explicit operator CDateTime() const; // Convert to CDateTime class

		bool operator==(const DbDateTime &other) const;
		bool operator!=(const DbDateTime &other) const;
		bool operator>(const DbDateTime &other) const;
		bool operator>=(const DbDateTime &other) const;
		bool operator<(const DbDateTime &other) const;
		bool operator<=(const DbDateTime &other) const;

		DbDateTime& operator=(const DbDateTime&) = default;
		DbDateTime& operator=(DbDateTime&&) = default;
		DbDateTime& operator=(const CDateTime& dt);

		DbDateTime() = default;
		DbDateTime(const DbDateTime&) = default;
		DbDateTime(DbDateTime&&) = default;
		DbDateTime(const DbDate& date, const DbTime& time, const unsigned int nano_second = 0);
		DbDateTime(const CDateTime& dt);
	};
}