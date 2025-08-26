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
		class IExpression;

		struct Operator;

		// Arguments are in expression list
		class CExpressionBrace :public CExpression
		{
		private:
			const Operator *m_pOp;
			IExpression *m_pName;
			IExpression *m_pArguments;
		protected:
			void BeforeRelease() override;
		public:
			const Operator* &Op{ m_pOp };
			IExpression* &Name{ m_pName };
			IExpression* &Arguments{ m_pArguments };

			// IExpression methods
			String toString() override;

			CExpressionBrace(const size_t index, const Operator *op, IExpression *name, IExpression *arguments);

			IExpression **getInnerName();
		};
	}
}