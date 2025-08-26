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
	namespace script
	{
		String PrefixTypeToString(const PrefixType type, const String &custom)
		{
			switch (type)
			{
			case PrefixType::None: return L"";
			case PrefixType::L: return L"L";
			case PrefixType::U: return L"U";
			case PrefixType::u: return L"u";
			case PrefixType::u8: return L"u8";
			default: return custom;
			}
		}
	}
}