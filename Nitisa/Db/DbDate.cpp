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
	DbDate::operator String() const
	{
		return PadLeft(ToString(Year), L'0', 4) + L"-" + PadLeft(ToString(Month), L'0', 2) + L"-" + PadLeft(ToString(Day), L'0', 2);
	}

	DbDate::operator AnsiString() const
	{
		return PadLeft(ToAnsi(Year), '0', 4) + "-" + PadLeft(ToAnsi(Month), '0', 2) + "-" + PadLeft(ToAnsi(Day), '0', 2);
	}

	bool DbDate::operator==(const DbDate &other) const
	{
		return Year == other.Year && Month == other.Month && Day == other.Day;
	}

	bool DbDate::operator!=(const DbDate &other) const
	{
		return Year != other.Year || Month != other.Month || Day != other.Day;
	}

	bool DbDate::operator>(const DbDate &other) const
	{
		if (Year > other.Year)
			return true;
		if (Year < other.Year)
			return false;
		if (Month > other.Month)
			return true;
		if (Month < other.Month)
			return false;
		return Day > other.Day;
	}

	bool DbDate::operator>=(const DbDate &other) const
	{
		if (Year > other.Year)
			return true;
		if (Year < other.Year)
			return false;
		if (Month > other.Month)
			return true;
		if (Month < other.Month)
			return false;
		return Day >= other.Day;
	}

	bool DbDate::operator<(const DbDate &other) const
	{
		if (Year < other.Year)
			return true;
		if (Year > other.Year)
			return false;
		if (Month < other.Month)
			return true;
		if (Month > other.Month)
			return false;
		return Day < other.Day;
	}

	bool DbDate::operator<=(const DbDate &other) const
	{
		if (Year < other.Year)
			return true;
		if (Year > other.Year)
			return false;
		if (Month < other.Month)
			return true;
		if (Month > other.Month)
			return false;
		return Day <= other.Day;
	}
}