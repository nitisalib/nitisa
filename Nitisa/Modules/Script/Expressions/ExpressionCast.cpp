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
		CExpressionCast::CExpressionCast(const size_t index, const Operator *op, IExpression *name, const String &data_type, IExpression *operand) :
			CExpression(index, ExpressionType::Cast, false),
			m_pOp{ op },
			m_pName{ name },
			m_sDataType{ data_type },
			m_pOperand{ operand }
		{

		}

		void CExpressionCast::BeforeRelease()
		{
			CExpression::BeforeRelease();
			if (m_pName)
				m_pName->Release();
			if (m_pOperand)
				m_pOperand->Release();
		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionCast::toString()
		{
			String result{ PriorOperatorsToString() };
			if (m_pName)
				result += m_pName->toString();
			if (m_pOp)
				result += m_pOp->Name;
			result += m_sDataType;
			if (m_pOp)
				result += m_pOp->Close;
			if (m_pOperand)
				result += m_pOperand->toString();
			return result + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}