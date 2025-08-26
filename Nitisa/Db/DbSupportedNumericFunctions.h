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
	struct DbSupportedNumericFunctions
	{
		bool Valid; // Indicates whether this structure contains valid data (it was successfully retrieved from data source)
		bool Abs;
		bool Acos;
		bool Asin;
		bool Atan;
		bool Atan2;
		bool Ceiling;
		bool Cos;
		bool Cot;
		bool Degrees;
		bool Exp;
		bool Floor;
		bool Log;
		bool Log10;
		bool Mod;
		bool Pi;
		bool Power;
		bool Radians;
		bool Rand;
		bool Round;
		bool Sign;
		bool Sin;
		bool Sqrt;
		bool Tan;
		bool Truncate;

		explicit operator String() const;
	};
}