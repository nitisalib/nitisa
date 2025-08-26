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
		CFunctionRnd::CFunctionRnd(IErrorListener *error_listener) :
			CFunction(L"rnd", error_listener),
			m_cDistribution{ 0, 1 }
		{
			m_pResult = &m_sResult;
			auto now{ std::chrono::system_clock::now() };
			std::chrono::milliseconds duration{ std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) };
			m_cEngine.seed((unsigned int)duration.count());
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionRnd::Run()
		{
			m_sResult = m_cDistribution(m_cEngine);
			return true;
		}
	#pragma endregion
	}
}