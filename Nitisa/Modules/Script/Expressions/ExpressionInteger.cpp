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
		CExpressionInteger::CExpressionInteger(const size_t index, const uint64 value, const String &postfix, const PostfixType postfix_type, const byte base, const String &user_defined_literal) :
			CExpression(index, ExpressionType::Integer, false),
			m_iValue{ value },
			m_sPostfix{ postfix },
			m_eTypeOfPostfix{ postfix_type },
			m_iBase{ base },
			m_sUserDefinedLiteral{ user_defined_literal }
		{

		}
	#pragma endregion

	#pragma region
		String CExpressionInteger::toString()
		{
			if (m_iBase == 16)
				return PriorOperatorsToString() + L"0x" + Hex(m_iValue) + m_sPostfix + m_sUserDefinedLiteral + PosteriorOperatorsToString();
			return PriorOperatorsToString() + ToString(m_iValue) + PostfixTypeToString(m_eTypeOfPostfix, m_sPostfix) + m_sUserDefinedLiteral + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}