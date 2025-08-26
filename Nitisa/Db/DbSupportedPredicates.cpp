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
	DbSupportedPredicates::operator String() const
	{
		StringArray list;
		if (Between) list.push_back(L"Between");
		if (Comparison) list.push_back(L"Comparison");
		if (Exists) list.push_back(L"Exists");
		if (In) list.push_back(L"In");
		if (IsNotNull) list.push_back(L"IsNotNull");
		if (IsNull) list.push_back(L"IsNull");
		if (Like) list.push_back(L"Like");
		if (MatchFull) list.push_back(L"MatchFull");
		if (MatchPartial) list.push_back(L"MatchPartial");
		if (MatchUniqueFull) list.push_back(L"MatchUniqueFull");
		if (MatchUniquePartial) list.push_back(L"MatchUniquePartial");
		if (Overlaps) list.push_back(L"Overlaps");
		if (QuantifierComparison) list.push_back(L"QuantifierComparison");
		if (Unique) list.push_back(L"Unique");
		return Implode(L", ", list);
	}
}