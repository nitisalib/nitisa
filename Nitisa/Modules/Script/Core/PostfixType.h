// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"

namespace nitisa
{
	namespace script
	{
		enum class PostfixType
		{
			None, // No postfix
			L, // long
			LL, // long long
			F, // float
			Z, // size
			U, // unsigned
			UL, // unsigned long
			ULL, // unsigned long long
			UZ, // unsigned size

			Custom // Custom postfix (no one from above)
		};

		String PostfixTypeToString(const PostfixType type, const String &custom);
	}
}