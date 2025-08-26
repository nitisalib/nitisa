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
	DbSupportedNumericValueFunctions::operator String() const
	{
		StringArray list;
		if (BitLength) list.push_back(L"BitLength");
		if (CharLength) list.push_back(L"CharLength");
		if (CharacterLength) list.push_back(L"CharacterLength");
		if (Extract) list.push_back(L"Extract");
		if (OctetLength) list.push_back(L"OctetLength");
		if (Position) list.push_back(L"Position");
		return Implode(L", ", list);
	}
}