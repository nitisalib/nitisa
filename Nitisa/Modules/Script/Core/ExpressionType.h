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
		enum class ExpressionType
		{
			Bool, // Boolean literal
			Brace, // Brace expression like "{ optional-arguments }"
			Call, // Call expression like "(optional-arguments)"
			Cast, // Type cast expression like "(type)"
			Float, // Float literal
			Identifier, // Identifier
			Integer, // Integer literal
			Null, // Null, nullptr literal
			Operator, // Operator
			Sequence, // Sequence of expressions
			String, // String literal
			Subscript, // Subscript expression like "[optional-arguments]"
		};

		String ExpressionTypeToString(const ExpressionType type);
	}
}