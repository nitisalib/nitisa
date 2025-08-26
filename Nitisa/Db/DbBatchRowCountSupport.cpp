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
	DbBatchRowCountSupport::operator String() const
	{
		StringArray list;
		if (RolledUp) list.push_back(L"RolledUp");
		if (Procedures) list.push_back(L"Procedures");
		if (Explicit) list.push_back(L"Explicit");
		return Implode(L", ", list);
	}
}