// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"

namespace nitisa
{
	namespace script
	{
		constexpr const uint GROUP_SKIP{ 0 }; // Operator can be skipped. It's presence is token list is irrelevant
		constexpr const uint GROUP_SPACE{ 1 }; // Operator is a space operator. It doesn't matter what kind of space it is and how may of them are located together
		constexpr const uint GROUP_NEW_LINE{ 2 }; // Operator is a new line operator. It doesn't matter what kind of new line it is and how may of them are located together
		constexpr const uint GROUP_SEPARATOR{ 3 }; // Operator is a either space or new line operator. It doesn't matter what kind of space or new line it is and how may of them are located together
		constexpr const uint GROUP_NO_SKIP{ 0xFFFFFFFF }; // Operator cannot be in a group. It's presence in token list matters
	}
}