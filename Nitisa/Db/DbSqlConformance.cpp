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
	DbSqlConformance::operator String() const
	{
		StringArray list;
		if (Entry) list.push_back(L"Entry");
		if (Transitional) list.push_back(L"Transitional");
		if (Full) list.push_back(L"Full");
		if (Intermediate) list.push_back(L"Intermediate");
		return Implode(L", ", list);
	}
}