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
	String ToString(const DbOdbcInterfaceConformance value)
	{
		switch (value)
		{
		case DbOdbcInterfaceConformance::Core: return L"Core";
		case DbOdbcInterfaceConformance::Level1: return L"Level1";
		case DbOdbcInterfaceConformance::Level2: return L"Level2";
		default: return L"Unknown";
		}
	}
}