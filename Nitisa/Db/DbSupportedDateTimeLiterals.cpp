// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	DbSupportedDateTimeLiterals::operator String() const
	{
		StringArray list;
		if (Date) list.push_back(L"Date");
		if (Time) list.push_back(L"Time");
		if (Timestamp) list.push_back(L"Timestamp");
		if (IntervalYear) list.push_back(L"IntervalYear");
		if (IntervalMonth) list.push_back(L"IntervalMonth");
		if (IntervalDay) list.push_back(L"IntervalDay");
		if (IntervalHour) list.push_back(L"IntervalHour");
		if (IntervalMinute) list.push_back(L"IntervalMinute");
		if (IntervalSecond) list.push_back(L"IntervalSecond");
		if (IntervalYearToMonth) list.push_back(L"IntervalYearToMonth");
		if (IntervalDayToHour) list.push_back(L"IntervalDayToHour");
		if (IntervalDayToMinute) list.push_back(L"IntervalDayToMinute");
		if (IntervalDayToSecond) list.push_back(L"IntervalDayToSecond");
		if (IntervalHourToMinute) list.push_back(L"IntervalHourToMinute");
		if (IntervalHourToSecond) list.push_back(L"IntervalHourToSecond");
		if (IntervalMinuteToSecond) list.push_back(L"IntervalMinuteToSecond");
		return Implode(L", ", list);
	}
}