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
	DbStandardCliConformance::operator String() const
	{
		StringArray list;
		if (XOpenVersion1) list.push_back(L"XOpenVersion1");
		if (ISO92) list.push_back(L"ISO92");
		return Implode(L", ", list);
	}
}