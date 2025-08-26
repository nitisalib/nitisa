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
	DbSupportedAlterDomainClauses::operator String() const
	{
		StringArray list;
		if (Add) list.push_back(L"Add");
		if (Deferrable) list.push_back(L"Deferrable");
		if (NonDeferrable) list.push_back(L"NonDeferrable");
		if (InitiallyDeferred) list.push_back(L"InitiallyDeferred");
		if (InitiallyImmediate) list.push_back(L"InitiallyImmediate");
		if (SetDefault) list.push_back(L"SetDefault");
		if (NameDefinition) list.push_back(L"NameDefinition");
		if (Drop) list.push_back(L"Drop");
		if (DropDefault) list.push_back(L"DropDefault");
		return Implode(L", ", list);
	}
}