// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "List.h"

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			struct Range
			{
				List *Begin;
				List *End;

				String toString() const;
				String toStringEx() const; // Tries to put spaces more accurately
			};
		}
	}
}