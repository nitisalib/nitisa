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
		enum class PrefixType
		{
			None, // No prefix
			L, // wstring
			U, // 32-bit
			u, // 16-bit
			u8, // 8-bit

			Custom // Custom prefix (none of the above)
		};

		String PrefixTypeToString(const PrefixType type, const String &custom);
	}
}