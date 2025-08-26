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
	DbSupportedValueExpressions::operator String() const
	{
		StringArray list;
		if (Case) list.push_back(L"Case");
		if (Cast) list.push_back(L"Cast");
		if (Coalesce) list.push_back(L"Coalesce");
		if (NullIf) list.push_back(L"NullIf");
		return Implode(L", ", list);
	}
}