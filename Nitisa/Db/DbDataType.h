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
	enum class DbDataType
	{
		Unknown,
		Char,
		VarChar,
		LongVarChar,
		WChar,
		WVarChar,
		WLongChar,
		Decimal,
		Numeric,
		SmallInt,
		Integer,
		Real,
		Float,
		Double,
		Bit,
		TinyInt,
		BigInt,
		Binary,
		VarBinary,
		LongVarBinary,
		Date,
		Time,
		DateTime,
		IntervalMonth,
		IntervalYear,
		IntervalYearToMonth,
		IntervalDay,
		IntervalHour,
		IntervalMinute,
		IntervalSecond,
		IntervalDayToHour,
		IntervalDayToMinute,
		IntervalDayToSecond,
		IntervalHourToMinute,
		IntervalHourToSecond,
		IntervalMinuteToSecond,
		Guid
	};

	String ToString(const DbDataType value);
}