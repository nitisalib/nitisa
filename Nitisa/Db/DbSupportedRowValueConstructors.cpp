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
	DbSupportedRowValueConstructors::operator String() const
	{
		StringArray list;
		if (ValueExpression) list.push_back(L"ValueExpression");
		if (Null) list.push_back(L"Null");
		if (Default) list.push_back(L"Default");
		if (RowSubQuery) list.push_back(L"RowSubQuery");
		return Implode(L", ", list);
	}
}