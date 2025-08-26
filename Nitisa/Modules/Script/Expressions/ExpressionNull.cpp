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
		CExpressionNull::CExpressionNull(const size_t index, const String &value) :
			CExpression(index, ExpressionType::Null, false),
			m_sValue{ value }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionNull::toString()
		{
			return PriorOperatorsToString() + m_sValue + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}