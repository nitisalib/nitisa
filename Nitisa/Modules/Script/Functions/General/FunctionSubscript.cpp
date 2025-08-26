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
		CFunctionSubscript::CFunctionSubscript(IErrorListener *error_listener, IFunction *operand1, IFunction *operand2) :
			CFunction(L"[]", error_listener),
			m_pOperand1{ operand1 },
			m_pOperand2{ operand2 }
		{

		}

		void CFunctionSubscript::BeforeRelease()
		{
			if (m_pOperand1)
				m_pOperand1->Release();
			if (m_pOperand2)
				m_pOperand2->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionSubscript::Run()
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
			if (m_pOperand2->Result->type() == VariableType::String)
			{
				if (m_pOperand1->Result->type() != VariableType::Object)
				{
					if (m_pErrorListener)
					{
						m_pErrorListener->NotifyOnError(
							__FUNCTION__,
							__LINE__,
							ERROR_FUNCTION_OPERAND_1_NOT_OBJECT,
							StringKeyValueArray{ StringKeyValue{ L"{name}", m_sName } }
						);
					}
					return false;
				}
				m_pResult = &(*m_pOperand1->Result)[String(*m_pOperand2->Result)];
				return true;
			}
			if (m_pOperand1->Result->type() != VariableType::Array)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_FUNCTION_OPERAND_1_NOT_ARRAY,
						StringKeyValueArray{ StringKeyValue{ L"{name}", m_sName } }
					);
				}
				return false;
			}
			if (int64(*m_pOperand2->Result) < 0 || int64(*m_pOperand2->Result) >= int64(m_pOperand1->Result->size()))
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_FUNCTION_INDEX_OUT_OF_BOUNDS,
						StringKeyValueArray{
							StringKeyValue{ L"{index}", ToString(int64(*m_pOperand2->Result)) },
							StringKeyValue{ L"{size}", ToString(int64(m_pOperand1->Result->size())) },
							StringKeyValue{ L"{name}", m_sName } }
					);
				}
				return false;
			}
			m_pResult = &(*m_pOperand1->Result)[size_t(int64(*m_pOperand2->Result))];
			return true;
		}
	#pragma endregion
	}
}