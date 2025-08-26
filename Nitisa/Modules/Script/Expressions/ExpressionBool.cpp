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
		CExpressionBool::CExpressionBool(const size_t index, const bool value):
			CExpression(index, ExpressionType::Bool, false),
			m_bValue{ value }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionBool::toString()
		{
			return PriorOperatorsToString() + ToString(m_bValue) + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}