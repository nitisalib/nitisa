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
		CFunctionVariable::CFunctionVariable(IErrorListener *error_listener, Variable &value) :
			CFunction(L"", error_listener)
		{
			m_pResult = &value;
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionVariable::Run()
		{
			return true;
		}
	#pragma endregion
	}
}