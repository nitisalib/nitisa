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
	DbSupportedForeignKeyRules::operator String() const
	{
		StringArray list;
		if (Cascade) list.push_back(L"Cascade");
		if (NoAction) list.push_back(L"NoAction");
		if (SetDefault) list.push_back(L"SetDefault");
		if (SetNull) list.push_back(L"SetNull");
		return Implode(L", ", list);
	}
}