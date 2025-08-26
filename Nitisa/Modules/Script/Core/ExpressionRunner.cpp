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
		CExpressionRunner::CExpressionRunner():
			m_pErrorListener{ nullptr },
			m_pFunction{ nullptr }
		{

		}

		void CExpressionRunner::BeforeRelease()
		{
			if (m_pFunction)
				m_pFunction->Release();
			DeleteVariables();
		}
	#pragma endregion

	#pragma region IExpressionRunner getters
		size_t CExpressionRunner::getVariableCount() const
		{
			return m_aVariables.size();
		}

		Variable *CExpressionRunner::getVariable(const size_t index)
		{
			if (index < m_aVariables.size())
				return m_aVariables[index].second;
			return nullptr;
		}

		Variable *CExpressionRunner::getVariable(const String &name)
		{
			for (auto &i : m_aVariables)
				if (i.first == name)
					return i.second;
			return nullptr;
		}
	#pragma endregion

	#pragma region IExpressionRunner variables
		bool CExpressionRunner::AddVariable(const String &name, const Variable &variable)
		{
			if (!name.empty())
			{
				for (auto &i : m_aVariables)
					if (i.first == name)
					{
						i.second = new Variable(variable);
						return true;
					}
				m_aVariables.push_back({ name, new Variable(variable) });
				return true;
			}
			return false;
		}

		bool CExpressionRunner::DeleteVariable(const size_t index)
		{
			if (index < m_aVariables.size())
			{
				delete m_aVariables[index].second;
				m_aVariables.erase(m_aVariables.begin() + index);
				return true;
			}
			return false;
		}

		bool CExpressionRunner::DeleteVariable(const String &name)
		{
			if (!name.empty())
				for (auto pos = m_aVariables.begin(); pos != m_aVariables.end(); pos++)
					if (pos->first == name)
					{
						delete pos->second;
						m_aVariables.erase(pos);
						return true;
					}
			return false;
		}

		bool CExpressionRunner::DeleteVariables()
		{
			if (m_aVariables.size() > 0)
			{
				for (auto i : m_aVariables)
					delete i.second;
				m_aVariables.clear();
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}