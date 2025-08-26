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
		CFunctionGreater::CFunctionGreater(IErrorListener *error_listener, IFunction *operand1, IFunction *operand2) :
			CFunction(L">", error_listener),
			m_pOperand1{ operand1 },
			m_pOperand2{ operand2 }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionGreater::BeforeRelease()
		{
			if (m_pOperand1)
				m_pOperand1->Release();
			if (m_pOperand2)
				m_pOperand2->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionGreater::Run()
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
			m_sResult = *m_pOperand1->Result > *m_pOperand2->Result;
			return true;
		}
	#pragma endregion
	}
}