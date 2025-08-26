// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Releasable.h"
#include "../../../Core/Strings.h"
#include "../Core/Variable.h"
#include "Identifier.h"
#include "Range.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CAttribute :public CReleasable
			{
			public:
				CIdentifier Identifier;
				bool hasArguments; // Whether there is ()
				std::vector<Range> Arguments;

				CAttribute();

				String toString() const;
				void toVariable(Variable &target) const;
			};
		}
	}
}