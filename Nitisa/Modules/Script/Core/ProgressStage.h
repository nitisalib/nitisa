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
		enum class ProgressStage
		{
			Parsing, // Parsing into tokens
			Decoding, // Decoding into final object
			Encoding, // Encoding into string
			Expression, // Building expression
			Precedence, // Re-arranging expression according to operators precedence
		};
	}
}