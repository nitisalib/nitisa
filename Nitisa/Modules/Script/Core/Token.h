// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"
#include "../../../Core/Strings.h"
#include "TokenType.h"

namespace nitisa
{
	namespace script
	{
		struct Operator;

		/*
			If Type = Group only first operator in a group parameters is stored in the structure. Count member shows how many tokens were treaded as a group.
		*/
		struct Token
		{
			TokenType Type; // Token type
			size_t Index; // Token start index in a source
			size_t Length; // Token length
			size_t ContentIndex; // Token content start index in a source
			size_t ContentLength; // Token content length
			String Value; // Token value
			String Prefix; // Prefix
			String Postfix; // Postfix
			size_t Count; // Number of combined operators if it is a grouppable one
			bool Finished; // Whether token is finished or ended up with source end
			const Operator *Op; // Empty if token is not an operator or group. Operator if token is operator, group or string. First operator if token is a group.
			byte Base; // Base for integer and float values
			uint64 Integer; // Integer value if token is integer
			double Float; // Float value if token is float

			bool operator==(const Token &other) const;
			bool operator!=(const Token &other) const;
		};

		String TokenToString(const Token &token);
	}
}