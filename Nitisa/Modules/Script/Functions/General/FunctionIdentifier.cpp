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
		CFunctionIdentifier::CFunctionIdentifier(IErrorListener *error_listener, const String &value) :
			CFunction(L"", error_listener),
			m_sStore{ value }
		{
			m_pResult = &m_sValue;
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionIdentifier::Run()
		{
			m_sValue = m_sStore;
			return true;
		}
	#pragma endregion
	}
}