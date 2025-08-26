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
	DbConvertTo::operator String() const
	{
		StringArray list;
		if (BigInt) list.push_back(L"BigInt");
		if (Binary) list.push_back(L"Binary");
		if (Bit) list.push_back(L"Bit");
		if (Guid) list.push_back(L"Guid");
		if (Char) list.push_back(L"Char");
		if (Date) list.push_back(L"Date");
		if (Decimal) list.push_back(L"Decimal");
		if (Double) list.push_back(L"Double");
		if (Float) list.push_back(L"Float");
		if (Integer) list.push_back(L"Integer");
		if (IntervalYearMonth) list.push_back(L"IntervalYearMonth");
		if (IntervalDayTime) list.push_back(L"IntervalDayTime");
		if (LongVarBinary) list.push_back(L"LongVarBinary");
		if (LongVarChar) list.push_back(L"LongVarChar");
		if (Numeric) list.push_back(L"Numeric");
		if (Real) list.push_back(L"Real");
		if (SmallInt) list.push_back(L"SmallInt");
		if (Time) list.push_back(L"Time");
		if (DateTime) list.push_back(L"DateTime");
		if (TinyInt) list.push_back(L"TinyInt");
		if (VarBinary) list.push_back(L"VarBinary");
		if (VarChar) list.push_back(L"VarChar");
		return Implode(L", ", list);
	}
}