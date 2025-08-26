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
	DbCatalogUsage::operator String() const
	{
		StringArray list;
		if (Statements) list.push_back(L"Statements");
		if (Procedures) list.push_back(L"Procedures");
		if (Tables) list.push_back(L"Tables");
		if (Indices) list.push_back(L"Indices");
		if (Privileges) list.push_back(L"Privileges");
		return Implode(L", ", list);
	}
}