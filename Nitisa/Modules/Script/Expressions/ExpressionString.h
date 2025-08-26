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
#include "../Core/PrefixType.h"

namespace nitisa
{
	namespace script
	{
		struct Operator;

		class CExpressionString :public CExpression
		{
		private:
			String m_sValue;
			String m_sPrefix;
			PrefixType m_eTypeOfPrefix;
			const Operator *m_pOp;
			bool m_bRaw;
			String m_sRawSeparator;
			String m_sUserDefinedLiteral;
		public:
			String &Value{ m_sValue };
			String &Prefix{ m_sPrefix };
			PrefixType &TypeOfPrefix{ m_eTypeOfPrefix };
			const Operator* &Op{ m_pOp };
			bool &Raw{ m_bRaw };
			String &RawSeparator{ m_sRawSeparator };
			String &UserDefinedLiteral{ m_sUserDefinedLiteral };

			// IExpression methods
			String toString() override;

			CExpressionString(
				const size_t index,
				const String &value,
				const String &prefix,
				const PrefixType prefix_type,
				const Operator *op,
				const bool raw,
				const String &raw_separator,
				const String &user_defined_literal
			);
		};
	}
}