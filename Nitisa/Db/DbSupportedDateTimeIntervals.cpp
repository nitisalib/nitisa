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
	DbSupportedDateTimeIntervals::operator String() const
	{
		StringArray list;
		if (SecondFracture) list.push_back(L"SecondFracture");
		if (Second) list.push_back(L"Second");
		if (Minute) list.push_back(L"Minute");
		if (Hour) list.push_back(L"Hour");
		if (Day) list.push_back(L"Day");
		if (Week) list.push_back(L"Week");
		if (Month) list.push_back(L"Month");
		if (Quarter) list.push_back(L"Quarter");
		if (Year) list.push_back(L"Year");
		return Implode(L", ", list);
	}
}