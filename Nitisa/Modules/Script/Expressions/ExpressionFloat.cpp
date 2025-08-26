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
		CExpressionFloat::CExpressionFloat(const size_t index, const double value, const String &postfix, const PostfixType postfix_type, const byte base, const String &user_defined_literal) :
			CExpression(index, ExpressionType::Float, false),
			m_fValue{ value },
			m_sPostfix{ postfix },
			m_eTypeOfPostfix{ postfix_type },
			m_iBase{ base },
			m_sUserDefinedLiteral{ user_defined_literal }
		{

		}
	#pragma endregion

	#pragma region
		String CExpressionFloat::toString()
		{
			String s{ ToStringCompact(m_fValue) };
			if (s.find(L".") == String::npos && s.find(L"e") == String::npos)
				s += L".0";
			return PriorOperatorsToString() + s + PostfixTypeToString(m_eTypeOfPostfix, m_sPostfix) + m_sUserDefinedLiteral + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}