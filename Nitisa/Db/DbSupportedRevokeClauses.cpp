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
	DbSupportedRevokeClauses::operator String() const
	{
		StringArray list;
		if (Cascade) list.push_back(L"Cascade");
		if (DeleteTable) list.push_back(L"DeleteTable");
		if (GrantOptionFor) list.push_back(L"GrantOptionFor");
		if (InsertColumn) list.push_back(L"InsertColumn");
		if (InsertTable) list.push_back(L"InsertTable");
		if (ReferenceColumn) list.push_back(L"ReferenceColumn");
		if (ReferenceTable) list.push_back(L"ReferenceTable");
		if (Restrict) list.push_back(L"Restrict");
		if (SelectTable) list.push_back(L"SelectTable");
		if (UpdateColumn) list.push_back(L"UpdateColumn");
		if (UpdateTable) list.push_back(L"UpdateTable");
		if (UsageOnDomain) list.push_back(L"UsageOnDomain");
		if (UsageOnCharacterSet) list.push_back(L"UsageOnCharacterSet");
		if (UsageOnCollation) list.push_back(L"UsageOnCollation");
		if (UsageOnTranslation) list.push_back(L"UsageOnTranslation");
		return Implode(L", ", list);
	}
}