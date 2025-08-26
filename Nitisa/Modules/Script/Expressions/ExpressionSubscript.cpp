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
		CExpressionSubscript::CExpressionSubscript(const size_t index, const Operator *op, IExpression *name, IExpression *arguments) :
			CExpression(index, ExpressionType::Subscript, false),
			m_pOp{ op },
			m_pName{ name },
			m_pArguments{ arguments }
		{

		}

		void CExpressionSubscript::BeforeRelease()
		{
			CExpression::BeforeRelease();
			if (m_pName)
				m_pName->Release();
			if (m_pArguments)
				m_pArguments->Release();
		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionSubscript::toString()
		{
			String result{ PriorOperatorsToString() };
			if (m_pName)
				result += m_pName->toString();
			if (m_pOp)
				result += m_pOp->Name;
			if (m_pArguments)
				result += m_pArguments->toString();
			if (m_pOp)
				result += m_pOp->Close;
			result += PosteriorOperatorsToString();
			return result;
		}
	#pragma endregion

	#pragma region Getters
		IExpression **CExpressionSubscript::getInnerName()
		{
			if (!m_pName)
				return nullptr;
			switch (m_pName->Type)
			{
			case ExpressionType::Brace:
				return cast<CExpressionBrace*>(m_pName)->getInnerName();
			case ExpressionType::Call:
				return cast<CExpressionCall*>(m_pName)->getInnerName();
			case ExpressionType::Subscript:
				return cast<CExpressionSubscript*>(m_pName)->getInnerName();
			default:
				return &m_pName;
			}
		}
	#pragma endregion
	}
}