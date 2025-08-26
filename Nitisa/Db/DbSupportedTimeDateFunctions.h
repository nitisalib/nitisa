// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"

namespace nitisa
{
	struct DbSupportedTimeDateFunctions
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool CurrentDate;
		bool CurrentTime;
		bool CurrentTimestamp;
		bool CurDate;
		bool CurTime;
		bool DayName;
		bool DayOfMonth;
		bool DayOfWeek;
		bool DayOfYear;
		bool Extract;
		bool Hour;
		bool Minute;
		bool Month;
		bool MonthName;
		bool Now;
		bool Quarter;
		bool Second;
		bool TimestampAdd;
		bool TimestampDiff;
		bool Week;
		bool Year;

		explicit operator String() const;
	};
}