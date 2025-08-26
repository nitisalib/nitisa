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
	DbSupportedAvailabilityOfResultSetsInParameterizedExecution::operator String() const
	{
		StringArray list;
		if (Batch) list.push_back(L"Batch");
		if (NoBatch) list.push_back(L"NoBatch");
		if (NoSelect) list.push_back(L"NoSelect");
		return Implode(L", ", list);
	}
}