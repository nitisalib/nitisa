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
	DbSupportedScrollOptions::operator String() const
	{
		StringArray list;
		if (ForwardOnly) list.push_back(L"ForwardOnly");
		if (Static) list.push_back(L"Static");
		if (KeysetDriven) list.push_back(L"KeysetDriven");
		if (Dynamic) list.push_back(L"Dynamic");
		if (Mixed) list.push_back(L"Mixed");
		return Implode(L", ", list);
	}
}