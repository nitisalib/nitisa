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
		CFunctionLiteral::CFunctionLiteral(IErrorListener *error_listener, const Variable &value) :
			CFunction(L"", error_listener),
			m_sValue{ value },
			m_sStore{ value }
		{
			m_pResult = &m_sValue;
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionLiteral::Run()
		{
			m_sValue = m_sStore;
			return true;
		}
	#pragma endregion
	}
}