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
#include "List.h"
#include <vector>

namespace nitisa
{
	namespace script
	{
		namespace cppdoc
		{
			class CExpression :public CReleasable
			{
			protected:
				void BeforeRelease() override;
			public:
				List *Begin; // If not empty, the expression is operand or operator. Can points to "<" operator meaning operand is like "<vector>" and when evaluated, the ">" should be searched to get file name
				String Name; // If not empty, the expression is a function call
				std::vector<CExpression *> Items; // Either function arguments or items of a list
				std::vector<List *> Priors; // Prior operators. For operands only

				CExpression(); // List
				CExpression(List *begin); // Operator
				CExpression(List *begin, std::vector<List*> &priors); // Operand
				CExpression(const String &name); // Function call
			};
		}
	}
}