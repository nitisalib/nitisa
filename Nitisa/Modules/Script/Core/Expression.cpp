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
		CExpression::CExpression(const size_t index, const ExpressionType type, const bool allow_children) :
			CReleasable(),
			m_bAllowChildren{ allow_children }
		{
			m_iIndex = index;
			m_eType = type;
		}

		void CExpression::BeforeRelease()
		{
			DeleteExpressions();
		}
	#pragma endregion

	#pragma region IExpression operators
		IExpression *CExpression::operator[](const size_t index)
		{
			if (index < m_aExpressions.size())
				return m_aExpressions[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region IExpression getters
		size_t CExpression::getPriorOperatorCount() const
		{
			return m_aPriorOperators.size();
		}

		const Operator *CExpression::getPriorOperator(const size_t index) const
		{
			if (index < m_aPriorOperators.size())
				return m_aPriorOperators[index];
			return nullptr;
		}

		size_t CExpression::getPosteriorOperatorCount() const
		{
			return m_aPosteriorOperators.size();
		}

		const Operator *CExpression::getPosteriorOperator(const size_t index) const
		{
			if (index < m_aPosteriorOperators.size())
				return m_aPosteriorOperators[index];
			return nullptr;
		}

		size_t CExpression::getExpressionCount() const
		{
			return m_aExpressions.size();
		}

		size_t CExpression::getExpressionIndex(IExpression *expression) const
		{
			if (expression)
				for (size_t i = 0; i < m_aExpressions.size(); i++)
					if (m_aExpressions[i] == expression)
						return i;
			return npos;
		}

		IExpression *CExpression::getExpression(const size_t index)
		{
			if (index < m_aExpressions.size())
				return m_aExpressions[index];
			return nullptr;
		}
	#pragma endregion

	#pragma region IExpression prior operators
		bool CExpression::AddPriorOperator(const Operator *value)
		{
			if (value)
			{
				m_aPriorOperators.push_back(value);
				return true;
			}
			return false;
		}

		bool CExpression::DeletePriorOperator(const size_t index)
		{
			if (index < m_aPriorOperators.size())
			{
				m_aPriorOperators.erase(m_aPriorOperators.begin() + index);
				return true;
			}
			return false;
		}

		bool CExpression::DeletePriorOperators()
		{
			if (m_aPriorOperators.size() > 0)
			{
				m_aPriorOperators.clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IExpression posterior operators
		bool CExpression::AddPosteriorOperator(const Operator *value)
		{
			if (value)
			{
				m_aPosteriorOperators.push_back(value);
				return true;
			}
			return false;
		}

		bool CExpression::DeletePosteriorOperator(const size_t index)
		{
			if (index < m_aPosteriorOperators.size())
			{
				m_aPosteriorOperators.erase(m_aPosteriorOperators.begin() + index);
				return true;
			}
			return false;
		}

		bool CExpression::DeletePosteriorOperators()
		{
			if (m_aPosteriorOperators.size() > 0)
			{
				m_aPosteriorOperators.clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IExpression expression methods
		bool CExpression::AddExpression(IExpression *expression)
		{
			if (m_bAllowChildren && expression)
			{
				m_aExpressions.push_back(expression);
				return true;
			}
			return false;
		}

		bool CExpression::InsertExpression(IExpression *expression, const size_t before)
		{
			if (m_bAllowChildren && expression)
			{
				if (before < m_aExpressions.size())
					m_aExpressions.insert(m_aExpressions.begin() + before, expression);
				else
					m_aExpressions.push_back(expression);
				return true;
			}
			return false;
		}

		bool CExpression::DetachExpression(const size_t index)
		{
			if (index < m_aExpressions.size())
			{
				m_aExpressions.erase(m_aExpressions.begin() + index);
				return true;
			}
			return false;
		}

		bool CExpression::DetachExpression(IExpression *expression)
		{
			if (expression)
			{
				for (auto pos = m_aExpressions.begin(); pos != m_aExpressions.end(); pos++)
					if (*pos == expression)
					{
						m_aExpressions.erase(pos);
						return true;
					}
			}
			return false;
		}

		bool CExpression::DetachExpressions(const size_t index, const size_t count)
		{
			if (count > 0 && index + count <= m_aExpressions.size())
			{
				m_aExpressions.erase(m_aExpressions.begin() + index, m_aExpressions.begin() + index + count);
				return true;
			}
			return false;
		}

		bool CExpression::DetachExpressions()
		{
			if (m_aExpressions.size() > 0)
			{
				m_aExpressions.clear();
				return true;
			}
			return false;
		}

		bool CExpression::DeleteExpression(const size_t index)
		{
			if (index < m_aExpressions.size())
			{
				m_aExpressions[index]->Release();
				m_aExpressions.erase(m_aExpressions.begin() + index);
				return true;
			}
			return false;
		}

		bool CExpression::DeleteExpression(IExpression *expression)
		{
			if (expression)
			{
				for (auto pos = m_aExpressions.begin(); pos != m_aExpressions.end(); pos++)
					if (*pos == expression)
					{
						expression->Release();
						m_aExpressions.erase(pos);
						return true;
					}
			}
			return false;
		}

		bool CExpression::DeleteExpressions(const size_t index, const size_t count)
		{
			if (count > 0 && index + count <= m_aExpressions.size())
			{
				for (size_t i = 0; i < count; i++)
					m_aExpressions[index + i]->Release();
				m_aExpressions.erase(m_aExpressions.begin() + index, m_aExpressions.begin() + index + count);
				return true;
			}
			return false;
		}

		bool CExpression::DeleteExpressions()
		{
			if (m_aExpressions.size() > 0)
			{
				for (auto e : m_aExpressions)
					e->Release();
				m_aExpressions.clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		String CExpression::PriorOperatorsToString() const
		{
			String result;
			for (auto pos = m_aPriorOperators.rbegin(); pos != m_aPriorOperators.rend(); pos++)
			{
				result += (*pos)->Name;
				if ((*pos)->RequireSpace)
					result += L" ";
			}
			return result;
		}

		String CExpression::PosteriorOperatorsToString() const
		{
			String result;
			for (auto op : m_aPosteriorOperators)
			{
				if (op->RequireSpace)
					result += L" ";
				result += op->Name;
			}
			return result;
		}
	#pragma endregion
	}
}