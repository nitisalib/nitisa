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
	DbSupportedStringFunctions::operator String() const
	{
		StringArray list;
		if (Convert) list.push_back(L"Convert");
		if (Lower) list.push_back(L"Lower");
		if (Upper) list.push_back(L"Upper");
		if (SubString) list.push_back(L"SubString");
		if (Translate) list.push_back(L"Translate");
		if (TrimBoth) list.push_back(L"TrimBoth");
		if (TrimLeading) list.push_back(L"TrimLeading");
		if (TrimTrailing) list.push_back(L"TrimTrailing");
		return Implode(L", ", list);
	}
}