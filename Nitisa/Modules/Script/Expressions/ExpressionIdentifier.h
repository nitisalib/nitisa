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

namespace nitisa
{
	namespace script
	{
		class CExpressionIdentifier :public CExpression
		{
		private:
			String m_sName;
		public:
			String &Name{ m_sName };

			// IExpression methods
			String toString() override;

			CExpressionIdentifier(const size_t index, const String &name);
		};
	}
}