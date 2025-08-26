// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace script
	{
		enum class TokenType
		{
			Unknown, // Unknown token
			String, // String or comment
			Integer, // Integer (binary, octal, hexadecimal, decimal, etc)
			Float, // Float (hexadecimal, decimal, etc)
			Operator, // Operator
			Identifier, // Identifier
			Group // Group of the same meaning operators
		};
	}
}