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
	DbSupportedCreateIndexKeywords::operator String() const
	{
		StringArray list;
		if (None) list.push_back(L"None");
		if (Asc) list.push_back(L"Asc");
		if (Desc) list.push_back(L"Desc");
		if (All) list.push_back(L"All");
		return Implode(L", ", list);
	}
}