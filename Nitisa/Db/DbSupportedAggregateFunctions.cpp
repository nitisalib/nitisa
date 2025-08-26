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
	DbSupportedAggregateFunctions::operator String() const
	{
		StringArray list;
		if (All) list.push_back(L"All");
		if (Avg) list.push_back(L"Avg");
		if (Count) list.push_back(L"Count");
		if (Distinct) list.push_back(L"Distinct");
		if (Max) list.push_back(L"Max");
		if (Min) list.push_back(L"Min");
		if (Sum) list.push_back(L"Sum");
		return Implode(L", ", list);
	}
}