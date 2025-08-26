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
	DbSupportedCreateDomainClauses::operator String() const
	{
		StringArray list;
		if (Create) list.push_back(L"Create");
		if (ConstraintNameDefinition) list.push_back(L"ConstraintNameDefinition");
		if (Default) list.push_back(L"Default");
		if (Constraint) list.push_back(L"Constraint");
		if (Collation) list.push_back(L"Collation");
		if (Deferrable) list.push_back(L"Deferrable");
		if (NonDeferrable) list.push_back(L"NonDeferrable");
		if (InitiallyDeferred) list.push_back(L"InitiallyDeferred");
		if (InitiallyImmediate) list.push_back(L"InitiallyImmediate");
		return Implode(L", ", list);
	}
}