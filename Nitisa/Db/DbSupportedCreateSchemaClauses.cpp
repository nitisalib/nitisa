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
	DbSupportedCreateSchemaClauses::operator String() const
	{
		StringArray list;
		if (Create) list.push_back(L"Create");
		if (Authorization) list.push_back(L"Authorization");
		if (DefaultCharacterSet) list.push_back(L"DefaultCharacterSet");
		return Implode(L", ", list);
	}
}