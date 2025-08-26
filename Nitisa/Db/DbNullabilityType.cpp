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
	String ToString(const DbNullabilityType value)
	{
		switch (value)
		{
		case DbNullabilityType::Nullable: return L"Nullable";
		case DbNullabilityType::NoNulls: return L"NoNulls";
		default: return L"Unknown";
		}
	}
}