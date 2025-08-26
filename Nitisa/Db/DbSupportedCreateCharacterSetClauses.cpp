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
	DbSupportedCreateCharacterSetClauses::operator String() const
	{
		StringArray list;
		if (Create) list.push_back(L"Create");
		if (Collate) list.push_back(L"Collate");
		if (LimitedCollation) list.push_back(L"LimitedCollation");
		return Implode(L", ", list);
	}
}