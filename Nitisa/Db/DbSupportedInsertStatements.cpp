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
	DbSupportedInsertStatements::operator String() const
	{
		StringArray list;
		if (InsertLiterals) list.push_back(L"InsertLiterals");
		if (InsertSearched) list.push_back(L"InsertSearched");
		if (SelectInto) list.push_back(L"SelectInto");
		return Implode(L", ", list);
	}
}