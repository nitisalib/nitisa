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
		CFunction::CFunction(const String &name, IErrorListener *error_listener):
			CReleasable(),
			m_pErrorListener{ error_listener }
		{
			m_sName = name;
			m_pResult = nullptr;
		}
	#pragma endregion
	}
}