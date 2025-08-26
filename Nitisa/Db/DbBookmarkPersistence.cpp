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
	DbBookmarkPersistence::operator String() const
	{
		StringArray list;
		if (Close) list.push_back(L"Close");
		if (Delete) list.push_back(L"Delete");
		if (Drop) list.push_back(L"Drop");
		if (Transaction) list.push_back(L"Transaction");
		if (Update) list.push_back(L"Update");
		if (OtherStatement) list.push_back(L"OtherStatement");
		return Implode(L", ", list);
	}
}