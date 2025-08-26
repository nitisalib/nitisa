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
		struct Operator;

		class CExpressionOperator :public CExpression
		{
		private:
			const Operator *m_pOp;
			bool m_bMemberAccess;
		public:
			const Operator* const &Op{ m_pOp };
			bool &MemberAccess{ m_bMemberAccess }; // Whether operator is member access one

			// IExpression methods
			String toString() override;

			CExpressionOperator(const size_t index, const Operator *op);
		};
	}
}