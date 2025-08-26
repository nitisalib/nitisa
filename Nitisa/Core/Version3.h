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
	struct Version3
	{
		int Major;
		int Minor;
		int Build;

		Version3() : // Construct with 0.0.0 version
			Major{ 0 },
			Minor{ 0 },
			Build{ 0 }
		{

		}

		Version3(const int major, const int minor, const int build) : // Construct with specified version
			Major{ major },
			Minor{ minor },
			Build{ build }
		{

		}

		Version3(const Version3&) = default;
		Version3(Version3&&) = default;
		Version3 &operator=(const Version3&) = default;
		Version3 &operator=(Version3&&) = default;

		bool operator==(const Version3 &other) const // Compare if it equals to another version
		{
			return Major == other.Major && Minor == other.Minor && Build == other.Build;
		}

		bool operator!=(const Version3 &other) const // Compare if it doesn't equal to another version
		{
			return Major != other.Major || Minor != other.Minor || Build != other.Build;
		}

		bool operator>(const Version3 &other) const // Check if it greater than another one
		{
			if (Major > other.Major)
				return true;
			if (Major < other.Major)
				return false;
			if (Minor > other.Minor)
				return true;
			if (Minor < other.Minor)
				return false;
			return Build > other.Build;
		}

		bool operator<(const Version3 &other) const // Check if it less than another one
		{
			if (Major > other.Major)
				return false;
			if (Major < other.Major)
				return true;
			if (Minor > other.Minor)
				return false;
			if (Minor < other.Minor)
				return true;
			return Build < other.Build;
		}

		bool operator>=(const Version3 &other) const // Check if it greater or equal to another one
		{
			if (Major > other.Major)
				return true;
			if (Major < other.Major)
				return false;
			if (Minor > other.Minor)
				return true;
			if (Minor < other.Minor)
				return false;
			return Build >= other.Build;
		}

		bool operator<=(const Version3 &other) const // Check if it less or equal to another one
		{
			if (Major > other.Major)
				return false;
			if (Major < other.Major)
				return true;
			if (Minor > other.Minor)
				return false;
			if (Minor < other.Minor)
				return true;
			return Build <= other.Build;
		}
	};

	inline Version3 Max(const Version3 &a, const Version3 &b)
	{
		if (a > b)
			return a;
		return b;
	}

	inline Version3 Min(const Version3 &a, const Version3 &b)
	{
		if (a < b)
			return a;
		return b;
	}

	inline String ToString(const Version3 &value)
	{
		return ToString(value.Major) + L"." + ToString(value.Minor) + L"." + ToString(value.Build);
	}
}