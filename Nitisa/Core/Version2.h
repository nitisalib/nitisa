// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Strings.h"

namespace nitisa
{
	struct Version2
	{
		int Major;
		int Minor;

		Version2() : // Construct with 0.0 version
			Major{ 0 },
			Minor{ 0 }
		{

		}

		Version2(const int major, const int minor) : // Construct with specified version
			Major{ major },
			Minor{ minor }
		{

		}

		Version2(const Version2&) = default;
		Version2(Version2&&) = default;
		Version2 &operator=(const Version2&) = default;
		Version2 &operator=(Version2&&) = default;

		bool operator==(const Version2 &other) const // Compare if it equals to another version
		{
			return Major == other.Major && Minor == other.Minor;
		}

		bool operator!=(const Version2 &other) const // Compare if it doesn't equal to another version
		{
			return Major != other.Major || Minor != other.Minor;
		}

		bool operator>(const Version2 &other) const // Check if it greater than another one
		{
			if (Major > other.Major)
				return true;
			if (Major < other.Major)
				return false;
			return Minor > other.Minor;
		}

		bool operator<(const Version2 &other) const // Check if it less than another one
		{
			if (Major > other.Major)
				return false;
			if (Major < other.Major)
				return true;
			return Minor < other.Minor;
		}

		bool operator>=(const Version2 &other) const // Check if it greater or equal to another one
		{
			if (Major > other.Major)
				return true;
			if (Major < other.Major)
				return false;
			return Minor >= other.Minor;
		}

		bool operator<=(const Version2 &other) const // Check if it less or equal to another one
		{
			if (Major > other.Major)
				return false;
			if (Major < other.Major)
				return true;
			return Minor <= other.Minor;
		}
	};

	inline Version2 Max(const Version2 &a, const Version2 &b)
	{
		if (a > b)
			return a;
		return b;
	}

	inline Version2 Min(const Version2 &a, const Version2 &b)
	{
		if (a < b)
			return a;
		return b;
	}

	inline String ToString(const Version2 &value)
	{
		return ToString(value.Major) + L"." + ToString(value.Minor);
	}
}