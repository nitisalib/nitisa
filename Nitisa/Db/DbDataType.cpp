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
	String ToString(const DbDataType value)
	{
		switch (value)
		{
		case DbDataType::Char: return L"Char";
		case DbDataType::VarChar: return L"VarChar";
		case DbDataType::LongVarChar: return L"LongVarChar";
		case DbDataType::WChar: return L"WChar";
		case DbDataType::WVarChar: return L"WVarChar";
		case DbDataType::WLongChar: return L"WLongChar";
		case DbDataType::Decimal: return L"Decimal";
		case DbDataType::Numeric: return L"Numeric";
		case DbDataType::SmallInt: return L"SmallInt";
		case DbDataType::Integer: return L"Integer";
		case DbDataType::Real: return L"Real";
		case DbDataType::Float: return L"Float";
		case DbDataType::Double: return L"Double";
		case DbDataType::Bit: return L"Bit";
		case DbDataType::TinyInt: return L"TinyInt";
		case DbDataType::BigInt: return L"BigInt";
		case DbDataType::Binary: return L"Binary";
		case DbDataType::VarBinary: return L"VarBinary";
		case DbDataType::LongVarBinary: return L"LongVarBinary";
		case DbDataType::Date: return L"Date";
		case DbDataType::Time: return L"Time";
		case DbDataType::DateTime: return L"DateTime";
		case DbDataType::IntervalMonth: return L"IntervalMonth";
		case DbDataType::IntervalYear: return L"IntervalYear";
		case DbDataType::IntervalYearToMonth: return L"IntervalYearToMonth";
		case DbDataType::IntervalDay: return L"IntervalDay";
		case DbDataType::IntervalHour: return L"IntervalHour";
		case DbDataType::IntervalMinute: return L"IntervalMinute";
		case DbDataType::IntervalSecond: return L"IntervalSecond";
		case DbDataType::IntervalDayToHour: return L"IntervalDayToHour";
		case DbDataType::IntervalDayToMinute: return L"IntervalDayToMinute";
		case DbDataType::IntervalDayToSecond: return L"IntervalDayToSecond";
		case DbDataType::IntervalHourToMinute: return L"IntervalHourToMinute";
		case DbDataType::IntervalHourToSecond: return L"IntervalHourToSecond";
		case DbDataType::IntervalMinuteToSecond: return L"IntervalMinuteToSecond";
		case DbDataType::Guid: return L"Guid";
		default: return L"Unknown";
		}
	}
}