// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace script
	{
	#pragma region Constructor & destructor
		CExpressionOperator::CExpressionOperator(const size_t index, const Operator *op) :
			CExpression(index, ExpressionType::Operator, false),
			m_pOp{ op },
			m_bMemberAccess{ false }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionOperator::toString()
		{
			if (m_pOp)
				return m_pOp->Name;
			return L"";
		}
	#pragma endregion
	}
}