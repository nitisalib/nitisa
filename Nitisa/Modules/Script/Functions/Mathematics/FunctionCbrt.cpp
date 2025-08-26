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
		CFunctionCbrt::CFunctionCbrt(IErrorListener *error_listener, IFunction *operand) :
			CFunction(L"cbrt", error_listener),
			m_pOperand{ operand }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionCbrt::BeforeRelease()
		{
			if (m_pOperand)
				m_pOperand->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionCbrt::Run()
		{
			if (!m_pOperand)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_FUNCTION_MISSING_OPERAND_1,
						StringKeyValueArray{ StringKeyValue{ L"{name}", m_sName } }
					);
				}
				return false;
			}
			if (!m_pOperand->Run())
				return false;
			m_sResult = cbrt(double(*m_pOperand->Result));
			return true;
		}
	#pragma endregion
	}
}