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
	String ToString(const DbCursorConcurrency value)
	{
		switch (value)
		{
		case DbCursorConcurrency::ReadOnly: return L"ReadOnly";
		case DbCursorConcurrency::Lock: return L"Lock";
		case DbCursorConcurrency::Rows: return L"Rows";
		case DbCursorConcurrency::Values: return L"Values";
		default: return L"Unknown";
		}
	}
}