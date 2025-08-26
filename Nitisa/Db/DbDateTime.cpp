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
#pragma region Constructor & destructor
	DbDateTime::DbDateTime(const DbDate& date, const DbTime& time, const unsigned int nano_second)
	{
		Date = date;
		Time = time;
		NanoSecond = nano_second;
	}

	DbDateTime::DbDateTime(const CDateTime& dt) :
		NanoSecond{ 0 }
	{
		Date.Year = (short)dt.getYear();
		Date.Month = (unsigned short)dt.getMonth();
		Date.Day = (unsigned short)dt.getDay();
		Time.Hour = (unsigned short)dt.getHour();
		Time.Minute = (unsigned short)dt.getMinute();
		Time.Second = (unsigned short)dt.getSecond();
	}
#pragma endregion

	DbDateTime::operator String() const
	{
		if (NanoSecond == 0)
			return (String)Date + L" " + (String)Time;
		return (String)Date + L" " + (String)Time + L"." + PadLeft(ToString(NanoSecond), L'0', 9);
	}

	DbDateTime::operator AnsiString() const
	{
		if (NanoSecond == 0)
			return (AnsiString)Date + " " + (AnsiString)Time;
		return (AnsiString)Date + " " + (AnsiString)Time + "." + PadLeft(ToAnsi(NanoSecond), '0', 9);
	}

	DbDateTime::operator CDateTime() const
	{
		return CDateTime{ Date.Year, Date.Month, Date.Day, Time.Hour, Time.Minute, Time.Second };
	}

	bool DbDateTime::operator==(const DbDateTime &other) const
	{
		return Date == other.Date && Time == other.Time && NanoSecond == other.NanoSecond;
	}

	bool DbDateTime::operator!=(const DbDateTime &other) const
	{
		return Date != other.Date || Time != other.Time || NanoSecond != other.NanoSecond;
	}

	bool DbDateTime::operator>(const DbDateTime &other) const
	{
		if (Date > other.Date)
			return true;
		if (Date < other.Date)
			return false;
		if (Time > other.Time)
			return true;
		if (Time < other.Time)
			return false;
		return NanoSecond > other.NanoSecond;
	}

	bool DbDateTime::operator>=(const DbDateTime &other) const
	{
		if (Date > other.Date)
			return true;
		if (Date < other.Date)
			return false;
		if (Time > other.Time)
			return true;
		if (Time < other.Time)
			return false;
		return NanoSecond >= other.NanoSecond;
	}

	bool DbDateTime::operator<(const DbDateTime &other) const
	{
		if (Date < other.Date)
			return true;
		if (Date > other.Date)
			return false;
		if (Time < other.Time)
			return true;
		if (Time > other.Time)
			return false;
		return NanoSecond < other.NanoSecond;
	}

	bool DbDateTime::operator<=(const DbDateTime &other) const
	{
		if (Date < other.Date)
			return true;
		if (Date > other.Date)
			return false;
		if (Time < other.Time)
			return true;
		if (Time > other.Time)
			return false;
		return NanoSecond <= other.NanoSecond;
	}

	DbDateTime& DbDateTime::operator=(const CDateTime& dt)
	{
		Date.Year = (short)dt.getYear();
		Date.Month = (unsigned short)dt.getMonth();
		Date.Day = (unsigned short)dt.getDay();
		Time.Hour = (unsigned short)dt.getHour();
		Time.Minute = (unsigned short)dt.getMinute();
		Time.Second = (unsigned short)dt.getSecond();
		NanoSecond = 0;
		return *this;
	}
}