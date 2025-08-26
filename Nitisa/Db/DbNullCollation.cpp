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
	String ToString(const DbNullCollation value)
	{
		switch (value)
		{
		case DbNullCollation::End: return L"End";
		case DbNullCollation::High: return L"High";
		case DbNullCollation::Low: return L"Low";
		case DbNullCollation::Start: return L"Start";
		default: return L"Unknown";
		}
	}
}