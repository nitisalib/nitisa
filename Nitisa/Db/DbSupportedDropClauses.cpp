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
	DbSupportedDropClauses::operator String() const
	{
		StringArray list;
		if (Drop) list.push_back(L"Drop");
		if (Cascade) list.push_back(L"Cascade");
		if (Restrict) list.push_back(L"Restrict");
		return Implode(L", ", list);
	}
}