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
	DbSupportedTimeDateFunctions::operator String() const
	{
		StringArray list;
		if (CurrentDate) list.push_back(L"CurrentDate");
		if (CurrentTime) list.push_back(L"CurrentTime");
		if (CurrentTimestamp) list.push_back(L"CurrentTimestamp");
		if (CurDate) list.push_back(L"CurDate");
		if (CurTime) list.push_back(L"CurTime");
		if (DayName) list.push_back(L"DayName");
		if (DayOfMonth) list.push_back(L"DayOfMonth");
		if (DayOfWeek) list.push_back(L"DayOfWeek");
		if (DayOfYear) list.push_back(L"DayOfYear");
		if (Extract) list.push_back(L"Extract");
		if (Hour) list.push_back(L"Hour");
		if (Minute) list.push_back(L"Minute");
		if (Month) list.push_back(L"Month");
		if (MonthName) list.push_back(L"MonthName");
		if (Now) list.push_back(L"Now");
		if (Quarter) list.push_back(L"Quarter");
		if (Second) list.push_back(L"Second");
		if (TimestampAdd) list.push_back(L"TimestampAdd");
		if (TimestampDiff) list.push_back(L"TimestampDiff");
		if (Week) list.push_back(L"Week");
		if (Year) list.push_back(L"Year");
		return Implode(L", ", list);
	}
}