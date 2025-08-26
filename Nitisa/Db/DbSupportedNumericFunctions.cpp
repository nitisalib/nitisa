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
	DbSupportedNumericFunctions::operator String() const
	{
		StringArray list;
		if (Abs) list.push_back(L"Abs");
		if (Acos) list.push_back(L"Acos");
		if (Asin) list.push_back(L"Asin");
		if (Atan) list.push_back(L"Atan");
		if (Atan2) list.push_back(L"Atan2");
		if (Ceiling) list.push_back(L"Ceiling");
		if (Cos) list.push_back(L"Cos");
		if (Cot) list.push_back(L"Cot");
		if (Degrees) list.push_back(L"Degrees");
		if (Exp) list.push_back(L"Exp");
		if (Floor) list.push_back(L"Floor");
		if (Log) list.push_back(L"Log");
		if (Log10) list.push_back(L"Log10");
		if (Mod) list.push_back(L"Mod");
		if (Pi) list.push_back(L"Pi");
		if (Power) list.push_back(L"Power");
		if (Radians) list.push_back(L"Radians");
		if (Rand) list.push_back(L"Rand");
		if (Round) list.push_back(L"Round");
		if (Sign) list.push_back(L"Sign");
		if (Sin) list.push_back(L"Sin");
		if (Sqrt) list.push_back(L"Sqrt");
		if (Tan) list.push_back(L"Tan");
		if (Truncate) list.push_back(L"Truncate");
		return Implode(L", ", list);
	}
}