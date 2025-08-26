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
		CFunctionMax::CFunctionMax(IErrorListener *error_listener, const Arguments &arguments) :
			CFunction(L"max", error_listener),
			m_aArguments{ arguments }
		{
			m_pResult = &m_sResult;
		}

		void CFunctionMax::BeforeRelease()
		{
			for (auto a : m_aArguments)
				a->Release();
		}
	#pragma endregion

	#pragma region IFunction methods
		bool CFunctionMax::Run()
		{
			if (m_aArguments.size() < 1)
			{
				if (m_pErrorListener)
				{
					m_pErrorListener->NotifyOnError(
						__FUNCTION__,
						__LINE__,
						ERROR_FUNCTION_EXPECTED_ARGUMENTS,
						StringKeyValueArray{ StringKeyValue{ L"{name}", m_sName } }
					);
				}
				return false;
			}
			for (auto a : m_aArguments)
				if (!a->Run())
					return false;
			bool has_string{ false }, has_float{ false };
			for (auto a : m_aArguments)
				if (a->Result->type() == VariableType::String)
				{
					has_string = true;
					break;
				}
				else if (a->Result->type() == VariableType::Float)
					has_float = true;
			if (has_string)
			{
				String v{ String(*m_aArguments[0]->Result) };
				for (size_t i = 1; i < m_aArguments.size(); i++)
					v = ntl::Max<String>(v, String(*m_aArguments[i]->Result));
				m_sResult = v;
			}
			else if (has_float)
			{
				double v{ double(*m_aArguments[0]->Result) };
				for (size_t i = 1; i < m_aArguments.size(); i++)
					v = ntl::Max<double>(v, double(*m_aArguments[i]->Result));
				m_sResult = v;
			}
			else
			{
				int64 v{ int64(*m_aArguments[0]->Result) };
				for (size_t i = 1; i < m_aArguments.size(); i++)
					v = ntl::Max<int64>(v, int64(*m_aArguments[i]->Result));
				m_sResult = v;
			}
			return true;
		}
	#pragma endregion
	}
}