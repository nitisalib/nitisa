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
	DbSupportedSchemaUsages::operator String() const
	{
		StringArray list;
		if (AllDataManipulations) list.push_back(L"AllDataManipulations");
		if (ProcedureInvocation) list.push_back(L"ProcedureInvocation");
		if (TableDefinition) list.push_back(L"TableDefinition");
		if (IndexDefinition) list.push_back(L"IndexDefinition");
		if (PrivilegeDefinition) list.push_back(L"PrivilegeDefinition");
		return Implode(L", ", list);
	}
}