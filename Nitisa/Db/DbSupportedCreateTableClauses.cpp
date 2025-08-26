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
	DbSupportedCreateTableClauses::operator String() const
	{
		StringArray list;
		if (Create) list.push_back(L"Create");
		if (TableConstraint) list.push_back(L"TableConstraint");
		if (ConstraintNameDefinition) list.push_back(L"ConstraintNameDefinition");
		if (TemporaryTableCommitPreserve) list.push_back(L"TemporaryTableCommitPreserve");
		if (TemporaryTableCommitDelete) list.push_back(L"TemporaryTableCommitDelete");
		if (TemporaryTableGlobal) list.push_back(L"TemporaryTableGlobal");
		if (TemporaryTableLocal) list.push_back(L"TemporaryTableLocal");
		if (ColumnConstraint) list.push_back(L"ColumnConstraint");
		if (ColumnDefault) list.push_back(L"ColumnDefault");
		if (ColumnCollation) list.push_back(L"ColumnCollation");
		if (Deferrable) list.push_back(L"Deferrable");
		if (NonDeferrable) list.push_back(L"NonDeferrable");
		if (InitiallyDeferred) list.push_back(L"InitiallyDeferred");
		if (InitiallyImmediate) list.push_back(L"InitiallyImmediate");
		return Implode(L", ", list);
	}
}