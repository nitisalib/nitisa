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
	String ToString(const DbCaseSensitivity value)
	{
		switch (value)
		{
		case DbCaseSensitivity::Upper: return L"Upper";
		case DbCaseSensitivity::Lower: return L"Lower";
		case DbCaseSensitivity::Sensitive: return L"Sensitive";
		case DbCaseSensitivity::Mixed: return L"Mixed";
		default: return L"Unknown";
		}
	}
}