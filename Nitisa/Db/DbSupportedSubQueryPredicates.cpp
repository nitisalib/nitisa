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
	DbSupportedSubQueryPredicates::operator String() const
	{
		StringArray list;
		if (CorrelatedSubQueries) list.push_back(L"CorrelatedSubQueries");
		if (Comparison) list.push_back(L"Comparison");
		if (Exists) list.push_back(L"Exists");
		if (In) list.push_back(L"In");
		if (Quantified) list.push_back(L"Quantified");
		return Implode(L", ", list);
	}
}