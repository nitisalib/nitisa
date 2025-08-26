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
		CFunctionPi::CFunctionPi(IErrorListener *error_listener) :
			CFunction(L"pi", error_listener)
		{
			m_pResult = &m_sResult;
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionPi::Run()
		{
			m_sResult = ntl::Pi<double>;
			return true;
		}
	#pragma endregion
	}
}