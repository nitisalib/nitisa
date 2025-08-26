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
	DbSupportedSystemFunctions::operator String() const
	{
		StringArray list;
		if (DBName) list.push_back(L"DBName");
		if (IfNull) list.push_back(L"IfNull");
		if (UserName) list.push_back(L"UserName");
		return Implode(L", ", list);
	}
}