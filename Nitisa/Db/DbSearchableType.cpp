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
	String ToString(const DbSearchableType value)
	{
		switch (value)
		{
		case DbSearchableType::None: return L"None";
		case DbSearchableType::Char: return L"Char";
		case DbSearchableType::Basic: return L"Basic";
		case DbSearchableType::Searchable: return L"Searchable";
		default: return L"Unknown";
		}
	}
}