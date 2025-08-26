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
	struct DbConvertTo
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool BigInt;
		bool Binary;
		bool Bit;
		bool Guid;
		bool Char;
		bool Date;
		bool Decimal;
		bool Double;
		bool Float;
		bool Integer;
		bool IntervalYearMonth;
		bool IntervalDayTime;
		bool LongVarBinary;
		bool LongVarChar;
		bool Numeric;
		bool Real;
		bool SmallInt;
		bool Time;
		bool DateTime;
		bool TinyInt;
		bool VarBinary;
		bool VarChar;

		explicit operator String() const;
	};
}