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
	struct DbSupportedDateTimeLiterals
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Date;
		bool Time;
		bool Timestamp;
		bool IntervalYear;
		bool IntervalMonth;
		bool IntervalDay;
		bool IntervalHour;
		bool IntervalMinute;
		bool IntervalSecond;
		bool IntervalYearToMonth;
		bool IntervalDayToHour;
		bool IntervalDayToMinute;
		bool IntervalDayToSecond;
		bool IntervalHourToMinute;
		bool IntervalHourToSecond;
		bool IntervalMinuteToSecond;

		explicit operator String() const;
	};
}