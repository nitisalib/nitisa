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
		CFunctionModulo::CFunctionModulo(IErrorListener *error_listener, IFunction *operand1, IFunction *operand2) :
			CFunction(L"%", error_listener),
			m_pOperand1{ operand1 },
			m_pOperand2{ operand2 }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionModulo::BeforeRelease()
		{
			if (m_pOperand1)
				m_pOperand1->Release();
			if (m_pOperand2)
				m_pOperand2->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionModulo::Run()
		{
			if (!m_pOperand1)
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
			if (!m_pOperand2)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_FUNCTION_MISSING_OPERAND_2,
						StringKeyValueArray{ StringKeyValue{ L"{name}", m_sName } }
					);
				}
				return false;
			}
			if (!m_pOperand1->Run())
				return false;
			if (!m_pOperand2->Run())
				return false;
			m_sResult = int64(*m_pOperand1->Result) % int64(*m_pOperand2->Result);
			return true;
		}
	#pragma endregion
	}
}