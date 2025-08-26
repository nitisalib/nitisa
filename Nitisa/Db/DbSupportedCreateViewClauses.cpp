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
	DbSupportedCreateViewClauses::operator String() const
	{
		StringArray list;
		if (Create) list.push_back(L"Create");
		if (CheckOption) list.push_back(L"CheckOption");
		if (Cascade) list.push_back(L"Cascade");
		if (Local) list.push_back(L"Local");
		return Implode(L", ", list);
	}
}