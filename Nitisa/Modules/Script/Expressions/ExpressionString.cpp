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
		CExpressionString::CExpressionString(
			const size_t index,
			const String &value,
			const String &prefix,
			const PrefixType prefix_type,
			const Operator *op,
			const bool raw,
			const String &raw_separator,
			const String &user_defined_literal) :
			CExpression(index, ExpressionType::String, false),
			m_sValue{ value },
			m_sPrefix{ prefix },
			m_eTypeOfPrefix{ prefix_type },
			m_pOp{ op },
			m_bRaw{ raw },
			m_sRawSeparator{ raw_separator },
			m_sUserDefinedLiteral{ user_defined_literal }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionString::toString()
		{
			String result{ PriorOperatorsToString() + PrefixTypeToString(m_eTypeOfPrefix, m_sPrefix) };
			if (m_bRaw)
			{
				result += L"R";
				if (m_pOp)
					result += m_pOp->Name;
				result += m_sRawSeparator + L"(" + m_sValue + L")" + m_sRawSeparator;
				if (m_pOp)
					result += m_pOp->Close;
			}
			else
			{
				if (m_pOp)
					result += m_pOp->Name;
				result += m_sValue;
				if (m_pOp)
					result += m_pOp->Close;
			}
			result += m_sUserDefinedLiteral + PosteriorOperatorsToString();
			return result;
		}
	#pragma endregion
	}
}