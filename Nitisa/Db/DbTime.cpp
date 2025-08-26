// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	DbTime::operator String() const
	{
		return PadLeft(ToString(Hour), L'0', 2) + L":" + PadLeft(ToString(Minute), L'0', 2) + L":" + PadLeft(ToString(Second), L'0', 2);
	}

	DbTime::operator AnsiString() const
	{
		return PadLeft(ToAnsi(Hour), '0', 2) + ":" + PadLeft(ToAnsi(Minute), '0', 2) + ":" + PadLeft(ToAnsi(Second), '0', 2);
	}

	bool DbTime::operator==(const DbTime &other) const
	{
		return Hour == other.Hour && Minute == other.Minute && Second == other.Second;
	}

	bool DbTime::operator!=(const DbTime &other) const
	{
		return Hour != other.Hour || Minute != other.Minute || Second != other.Second;
	}

	bool DbTime::operator>(const DbTime &other) const
	{
		if (Hour > other.Hour)
			return true;
		if (Hour < other.Hour)
			return false;
		if (Minute > other.Minute)
			return true;
		if (Minute < other.Minute)
			return false;
		return Second > other.Second;
	}

	bool DbTime::operator>=(const DbTime &other) const
	{
		if (Hour > other.Hour)
			return true;
		if (Hour < other.Hour)
			return false;
		if (Minute > other.Minute)
			return true;
		if (Minute < other.Minute)
			return false;
		return Second >= other.Second;
	}

	bool DbTime::operator<(const DbTime &other) const
	{
		if (Hour < other.Hour)
			return true;
		if (Hour > other.Hour)
			return false;
		if (Minute < other.Minute)
			return true;
		if (Minute > other.Minute)
			return false;
		return Second < other.Second;
	}

	bool DbTime::operator<=(const DbTime &other) const
	{
		if (Hour < other.Hour)
			return true;
		if (Hour > other.Hour)
			return false;
		if (Minute < other.Minute)
			return true;
		if (Minute > other.Minute)
			return false;
		return Second <= other.Second;
	}
}