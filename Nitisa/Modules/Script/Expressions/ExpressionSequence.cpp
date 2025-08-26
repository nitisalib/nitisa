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
	#pragma region Static members
		const StringArray CExpressionSequence::OPERATORS_WITH_POSTERIOR_SPACE{
				L":",
				L"?",
				L"+",
				L"-",
				L"*",
				L"/",
				L"%",
				L"^",
				L"&",
				L"|",
				L"=",
				L"+=",
				L"-=",
				L"*=",
				L"/=",
				L"%=",
				L"^=",
				L"&=",
				L"|=",
				L"<=>",
				L"==",
				L"!=",
				L"<",
				L">",
				L"<=",
				L">=",
				L"&&",
				L"||",
				L"<<",
				L"<<=",
				L">>",
				L">>=",
				L",",
				L"and",
				L"or",
				L"xor",
				L"not",
				L"bitand",
				L"bitor",
				L"compl",
				L"and_eq",
				L"or_eq",
				L"xor_eq",
				L"not_eq"
		};
		const StringArray CExpressionSequence::OPERATORS_WITH_PRIOR_SPACE{
			L":",
			L"?",
			L"+",
			L"-",
			L"*",
			L"/",
			L"%",
			L"^",
			L"&",
			L"|",
			L"=",
			L"+=",
			L"-=",
			L"*=",
			L"/=",
			L"%=",
			L"^=",
			L"&=",
			L"|=",
			L"<=>",
			L"==",
			L"!=",
			L"<",
			L">",
			L"<=",
			L">=",
			L"&&",
			L"||",
			L"<<",
			L"<<=",
			L">>",
			L">>=",
			L"and",
			L"or",
			L"xor",
			L"not",
			L"bitand",
			L"bitor",
			L"compl",
			L"and_eq",
			L"or_eq",
			L"xor_eq",
			L"not_eq"
		};
	#pragma endregion

	#pragma region Constructor & destructor
		CExpressionSequence::CExpressionSequence(const size_t index, const bool ternary) :
			CExpression(index, ExpressionType::Sequence, true),
			m_bTernary{ ternary }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionSequence::toString()
		{
			String result{ PriorOperatorsToString() };
			if (getPriorOperatorCount() + getPosteriorOperatorCount() > 0)
				result += L"(";
			for (size_t i = 0; i < m_aExpressions.size(); i++)
			{
				if (i % 2 == 0)
				{
					if (m_aExpressions[i]->Type == ExpressionType::Sequence)
						result += L"(";
					result += m_aExpressions[i]->toString();
					if (m_aExpressions[i]->Type == ExpressionType::Sequence)
						result += L")";
					continue;
				}
				if (in(cast<CExpressionOperator*>(m_aExpressions[i])->Op->Name, OPERATORS_WITH_PRIOR_SPACE))
					result += L" ";
				result += m_aExpressions[i]->toString();
				if (in(cast<CExpressionOperator*>(m_aExpressions[i])->Op->Name, OPERATORS_WITH_POSTERIOR_SPACE))
					result += L" ";
			}
			if (getPriorOperatorCount() + getPosteriorOperatorCount() > 0)
				result += L")";
			return result + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}