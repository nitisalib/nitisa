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
	DbSupportedOuterJoins::operator String() const
	{
		StringArray list;
		if (Left) list.push_back(L"Left");
		if (Right) list.push_back(L"Right");
		if (Full) list.push_back(L"Full");
		if (Nested) list.push_back(L"Nested");
		if (NotOrdered) list.push_back(L"NotOrdered");
		if (Inner) list.push_back(L"Inner");
		if (AllComparisonOperators) list.push_back(L"AllComparisonOperators");
		return Implode(L", ", list);
	}
}