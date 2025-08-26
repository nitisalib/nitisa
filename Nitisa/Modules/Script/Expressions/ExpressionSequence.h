// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Strings.h"
#include "../Core/Expression.h"

namespace nitisa
{
	namespace script
	{
		class CExpressionSequence :public CExpression
		{
		private:
			bool m_bTernary;

			static const StringArray OPERATORS_WITH_PRIOR_SPACE;
			static const StringArray OPERATORS_WITH_POSTERIOR_SPACE;
		public:
			bool const &Ternary{ m_bTernary }; // Indicates whether sequence represents ternary operator

			// IExpression methods
			String toString() override;

			CExpressionSequence(const size_t index, const bool ternary);
		};
	}
}