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
		CFunctionPrefixIncrement::CFunctionPrefixIncrement(IErrorListener *error_listener, IFunction *operand, IFunction *modify) :
			CFunction(L"++x", error_listener),
			m_pOperand{ operand },
			m_pModify{ modify }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionPrefixIncrement::BeforeRelease()
		{
			if (m_pOperand)
				m_pOperand->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionPrefixIncrement::Run()
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
			if (!m_pModify)
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
			if (!m_pOperand->Run())
				return false;
			if (m_pOperand->Result->type() == VariableType::Float)
				*m_pModify->Result = double(*m_pModify->Result) + 1;
			else
				*m_pModify->Result = int64(*m_pModify->Result) + 1;
			m_sResult = *m_pModify->Result;
			return true;
		}
	#pragma endregion
	}
}