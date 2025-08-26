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
		CExpressionIdentifier::CExpressionIdentifier(const size_t index, const String &name) :
			CExpression(index, ExpressionType::Identifier, false),
			m_sName{ name }
		{

		}
	#pragma endregion

	#pragma region IExpression methods
		String CExpressionIdentifier::toString()
		{
			return PriorOperatorsToString() + m_sName + PosteriorOperatorsToString();
		}
	#pragma endregion
	}
}