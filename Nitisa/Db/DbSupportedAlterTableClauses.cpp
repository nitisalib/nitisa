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
	DbSupportedAlterTableClauses::operator String() const
	{
		StringArray list;
		if (Deferrable) list.push_back(L"Deferrable");
		if (NonDeferrable) list.push_back(L"NonDeferrable");
		if (InitiallyDeferred) list.push_back(L"InitiallyDeferred");
		if (InitiallyImmediate) list.push_back(L"InitiallyImmediate");
		if (NameDefinition) list.push_back(L"NameDefinition");
		if (AddConstraint) list.push_back(L"AddConstraint");
		if (AddColumnCollation) list.push_back(L"AddColumnCollation");
		if (AddColumnDefault) list.push_back(L"AddColumnDefault");
		if (AddColumnSingle) list.push_back(L"AddColumnSingle");
		if (DropColumnCascade) list.push_back(L"DropColumnCascade");
		if (DropColumnDefault) list.push_back(L"DropColumnDefault");
		if (DropColumnRestrict) list.push_back(L"DropColumnRestrict");
		if (SetDefaultColumn) list.push_back(L"SetDefaultColumn");
		if (AddTable) list.push_back(L"AddTable");
		if (DropTableCascade) list.push_back(L"DropTableCascade");
		if (DropTableRestrict) list.push_back(L"DropTableRestrict");
		return Implode(L", ", list);
	}
}