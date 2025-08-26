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
	DbSupportedConvertFunctions::operator String() const
	{
		StringArray list;
		if (Cast) list.push_back(L"Cast");
		if (Convert) list.push_back(L"Convert");
		return Implode(L", ", list);
	}
}