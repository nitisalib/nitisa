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
	DbBatchSupport::operator String() const
	{
		StringArray list;
		if (SelectExplicit) list.push_back(L"SelectExplicit");
		if (RowCountExplicit) list.push_back(L"RowCountExplicit");
		if (SelectProcedures) list.push_back(L"SelectProcedures");
		if (RowCountProcedures) list.push_back(L"RowCountProcedures");
		return Implode(L", ", list);
	}
}