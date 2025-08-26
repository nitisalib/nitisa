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
	String ToString(const DbOdbcVersion value)
	{
		switch (value)
		{
		case DbOdbcVersion::V2: return L"V2";
		case DbOdbcVersion::V3: return L"V3";
		default: return L"V3_80";
		}
	}
}