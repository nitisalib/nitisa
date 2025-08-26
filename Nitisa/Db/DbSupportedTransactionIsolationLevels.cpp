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
	DbSupportedTransactionIsolationLevels::operator String() const
	{
		StringArray list;
		if (ReadUncommited) list.push_back(L"ReadUncommited");
		if (ReadCommited) list.push_back(L"ReadCommited");
		if (RepeatableRead) list.push_back(L"RepeatableRead");
		if (Serializable) list.push_back(L"Serializable");
		return Implode(L", ", list);
	}
}