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
	String ToString(const DbAsyncMode value)
	{
		switch (value)
		{
		case DbAsyncMode::None: return L"None";
		case DbAsyncMode::Connection: return L"Connection";
		case DbAsyncMode::Statement: return L"Statement";
		default: return L"Unknown";
		}
	}
}