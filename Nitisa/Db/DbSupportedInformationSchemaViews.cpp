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
	DbSupportedInformationSchemaViews::operator String() const
	{
		StringArray list;
		if (Assertions) list.push_back(L"Assertions");
		if (CharacterSets) list.push_back(L"CharacterSets");
		if (CheckConstraints) list.push_back(L"CheckConstraints");
		if (Collations) list.push_back(L"Collations");
		if (ColumnDomainUsage) list.push_back(L"ColumnDomainUsage");
		if (ColumnPrivileges) list.push_back(L"ColumnPrivileges");
		if (Columns) list.push_back(L"Columns");
		if (ConstraintColumnUsage) list.push_back(L"ConstraintColumnUsage");
		if (ConstraintTableUsage) list.push_back(L"ConstraintTableUsage");
		if (DomainConstraints) list.push_back(L"DomainConstraints");
		if (Domains) list.push_back(L"Domains");
		if (KeyColumnUsage) list.push_back(L"KeyColumnUsage");
		if (ReferentialConstraints) list.push_back(L"ReferentialConstraints");
		if (Schemata) list.push_back(L"Schemata");
		if (SQLLanguages) list.push_back(L"SQLLanguages");
		if (TableConstraints) list.push_back(L"TableConstraints");
		if (TablePrivileges) list.push_back(L"TablePrivileges");
		if (Tables) list.push_back(L"Tables");
		if (Translations) list.push_back(L"Translations");
		if (UsagePrivileges) list.push_back(L"UsagePrivileges");
		if (ViewColumnUsage) list.push_back(L"ViewColumnUsage");
		if (ViewTableUsage) list.push_back(L"ViewTableUsage");
		if (Views) list.push_back(L"Views");
		return Implode(L", ", list);
	}
}