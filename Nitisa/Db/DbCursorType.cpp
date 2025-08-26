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
	String ToString(const DbCursorType value)
	{
		switch (value)
		{
		case DbCursorType::ForwardOnly: return L"ForwardOnly";
		case DbCursorType::Static: return L"Static";
		case DbCursorType::Keyset: return L"Keyset";
		case DbCursorType::Dynamic: return L"Dynamic";
		default: return L"Unknown";
		}
	}
}