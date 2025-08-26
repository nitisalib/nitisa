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
	#pragma region Consructor & destructor
		CParserOperator::CParserOperator(const Operators &operators, IReader *reader, ILexic *lexic):
			CReleasable(),
			m_pLexic{ lexic },
			m_pReader{ reader }
		{
			m_aOperators.resize(operators.size());
			for (size_t i = 0; i < operators.size(); i++)
				m_aOperators[i] = &operators[i];
			// Sort by first character ASC, then by length DESC
			std::sort(m_aOperators.begin(), m_aOperators.end(), [](const Operator *a, const Operator *b) {
				if (a->Name[0] == b->Name[0])
					return b->Name.length() < a->Name.length();
				return a->Name[0] < b->Name[0];
			});
		}
	#pragma endregion

	#pragma region IParser methods
		bool CParserOperator::Parse(size_t &index, Token &token)
		{
			m_sSearchOperator.Name = m_pReader->Read(index);
			auto pos{ std::lower_bound(m_aOperators.begin(), m_aOperators.end(), &m_sSearchOperator, [](const Operator *a, const Operator *b) {
				return a->Name[0] < b->Name[0];
			}) };
			if (pos == m_aOperators.end() || (*pos)->Name[0] != m_pReader->Read(index))
				return false;
			while (pos != m_aOperators.end() && (*pos)->Name[0] == m_pReader->Read(index))
			{
				if (CheckName((*pos)->Name, index))
				{
					if ((*pos)->RequireSpace)
					{
						if (!m_pLexic->IsIdentifierBoundary(m_pReader->Read(index - 1)))
						{
							pos++;
							continue;
						}
						if (!m_pLexic->IsIdentifierBoundary(m_pReader->Read(index + (*pos)->Name.length())))
						{
							pos++;
							continue;
						}
					}
					token.Type = TokenType::Operator;
					token.Op = *pos;
					token.Index = index;
					token.Length = token.Op->Name.length();
					token.ContentIndex = token.Index;
					token.ContentLength = token.Length;
					token.Value = token.Op->Name;
					token.Prefix = L"";
					token.Postfix = L"";
					token.Count = 1;
					token.Finished = true;
					token.Base = 0;
					token.Integer = 0;
					token.Float = 0;
					index += (*pos)->Name.length();
					return true;
				}
				pos++;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CParserOperator::CheckName(const String &name, const size_t index)
		{
			for (size_t i = 0; i < name.length(); i++)
				if (name[i] != m_pReader->Read(index + i))
					return false;
			return true;
		}
	#pragma endregion
	}
}