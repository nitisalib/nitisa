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
		String PostfixTypeToString(const PostfixType type, const String &custom)
		{
			switch (type)
			{
			case PostfixType::None: return L"";
			case PostfixType::L: return L"l";
			case PostfixType::LL: return L"ll";
			case PostfixType::F: return L"f";
			case PostfixType::Z: return L"z";
			case PostfixType::U: return L"u";
			case PostfixType::UL: return L"ul";
			case PostfixType::ULL: return L"ull";
			case PostfixType::UZ: return L"uz";
			default: return custom;
			}
		}
	}
}