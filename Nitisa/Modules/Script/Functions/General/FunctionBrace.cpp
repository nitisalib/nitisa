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
		CFunctionBrace::CFunctionBrace(IErrorListener *error_listener, const Arguments &arguments) :
			CFunction(L"{}", error_listener),
			m_aArguments{ arguments }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionBrace::BeforeRelease()
		{
			for (auto f : m_aArguments)
				f->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionBrace::Run()
		{
			for (auto f : m_aArguments)
				if (!f->Run())
					return false;
			m_sResult.clear();
			m_sResult.type(VariableType::Array);
			for (auto f : m_aArguments)
				m_sResult.push_back(*f->Result);
			return true;
		}
	#pragma endregion
	}
}