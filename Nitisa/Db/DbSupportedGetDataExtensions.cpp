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
	DbSupportedGetDataExtensions::operator String() const
	{
		StringArray list;
		if (AnyColumn) list.push_back(L"AnyColumn");
		if (AnyOrder) list.push_back(L"AnyOrder");
		if (Block) list.push_back(L"Block");
		if (Bound) list.push_back(L"Bound");
		if (OutputParams) list.push_back(L"OutputParams");
		return Implode(L", ", list);
	}
}