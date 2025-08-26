// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../../Core/Aliases.h"
#include "../../../Core/Strings.h"
#include "../Core/Expression.h"
#include "../Core/PostfixType.h"

namespace nitisa
{
	namespace script
	{
		class CExpressionInteger :public CExpression
		{
		private:
			uint64 m_iValue;
			String m_sPostfix;
			PostfixType m_eTypeOfPostfix;
			byte m_iBase;
			String m_sUserDefinedLiteral;
		public:
			uint64 &Value{ m_iValue };
			String &Postfix{ m_sPostfix };
			PostfixType &TypeOfPostfix{ m_eTypeOfPostfix };
			byte &Base{ m_iBase };
			String &UserDefinedLiteral{ m_sUserDefinedLiteral };

			// IExpression methods
			String toString() override;

			CExpressionInteger(const size_t index, const uint64 value, const String &postfix, const PostfixType postfix_type, const byte base, const String &user_defined_literal);
		};
	}
}