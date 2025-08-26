// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"
#include "../../../Core/Strings.h"

namespace nitisa
{
	namespace script
	{
		struct Operator
		{
			// Parsing related properties
			String Name; // Operator sequence
			String Close; // Close sequence for block operator
			StringKeyValueArray Replace; // Key-value pair array to replace inside block (like { L"\\"", "\"" } or { "\\n", "" })
			bool RequireSpace; // Whether space should be before and after operator
			bool Sequence; // Whether operator is a sequence and can be closed either by "Close" sequence of by new line
			bool Multiline; // Whether block operator can be closed by "Close" sequence only
			uint Group; // Group identifier indicating whether operators withing the same group should be treated as one token
			// Expression related properties
			bool Normal; // Whether operator can be a normal, connecting two arguments, operator
			bool Block; // Whether operator defines block. Block close operator should be specified in "Close" member
			bool Prior; // Whether operator can be used as prior-modification operator (like ++ in "++i" expression)
			bool Posterior; // Whether operator can be used as posterior-modification operator (like ++ in "i++" expression)
			bool AllowPrior; // Whether prior operator is allowed before this one
			bool AllowPosterior; // Whether posterior operator is allowed after this one
			byte Precedence; // Mathematical precedence. Highest one is 0
		};
	}
}