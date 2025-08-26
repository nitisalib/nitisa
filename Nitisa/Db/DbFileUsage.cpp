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
	String ToString(const DbFileUsage value)
	{
		switch (value)
		{
		case DbFileUsage::NotSupported: return L"NotSupported";
		case DbFileUsage::Table: return L"Table";
		case DbFileUsage::Catalog: return L"Catalog";
		default: return L"Unknown";
		}
	}
}