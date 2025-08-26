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
	String ToString(const DbUpdatableType value)
	{
		switch (value)
		{
		case DbUpdatableType::ReadOnly: return L"ReadOnly";
		case DbUpdatableType::Write: return L"Write";
		case DbUpdatableType::Unspecified: return L"Unspecified";
		default: return L"Unknown";
		}
	}
}