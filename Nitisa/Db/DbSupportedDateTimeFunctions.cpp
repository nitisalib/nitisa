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
	DbSupportedDateTimeFunctions::operator String() const
	{
		StringArray list;
		if (CurrentDate) list.push_back(L"CurrentDate");
		if (CurrentTime) list.push_back(L"CurrentTime");
		if (CurrentTimestamp) list.push_back(L"CurrentTimestamp");
		return Implode(L", ", list);
	}
}