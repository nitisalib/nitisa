// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../Core/Variable.h"
#include "Range.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CIdentifier
			{
			public:
				struct Name
				{
					bool Template; // name1::template name2
					String Name;
					bool hasArguments; // There is "<[...]>"
					std::vector<Range> Arguments;
				};
			public:
				bool Destructor; // name1::~name2
				bool UserDefinedOperator;
				std::vector<Name> Names; // If identifier starts with "::" the first item Name is empty
				String Operator;

				CIdentifier();

				String toString(const bool arguments) const;
				void toVariable(Variable &target) const;
			};
		}
	}
}