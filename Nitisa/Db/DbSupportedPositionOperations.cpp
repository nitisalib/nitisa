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
	DbSupportedPositionOperations::operator String() const
	{
		StringArray list;
		if (Position) list.push_back(L"Position");
		if (Refresh) list.push_back(L"Refresh");
		if (Update) list.push_back(L"Update");
		if (Delete) list.push_back(L"Delete");
		if (Add) list.push_back(L"Add");
		return Implode(L", ", list);
	}
}