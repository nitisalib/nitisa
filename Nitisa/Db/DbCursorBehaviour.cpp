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
	String ToString(const DbCursorBehaviour value)
	{
		switch (value)
		{
		case DbCursorBehaviour::Delete: return L"Delete";
		case DbCursorBehaviour::Close: return L"Close";
		case DbCursorBehaviour::Preserve: return L"Preserve";
		default: return L"Unknown";
		}
	}
}