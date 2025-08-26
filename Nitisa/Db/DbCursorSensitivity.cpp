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
	String ToString(const DbCursorSensitivity value)
	{
		switch (value)
		{
		case DbCursorSensitivity::Insensitive: return L"Insensitive";
		case DbCursorSensitivity::Unspecified: return L"Unspecified";
		case DbCursorSensitivity::Sensitive: return L"Sensitive";
		default: return L"Unknown";
		}
	}
}