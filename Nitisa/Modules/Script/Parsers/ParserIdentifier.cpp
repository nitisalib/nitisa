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
		CParserIdentifier::CParserIdentifier(IReader *reader, ILexic *lexic) :
			CReleasable(),
			m_pReader{ reader },
			m_pLexic{ lexic }
		{

		}
	#pragma endregion

	#pragma region IParser methods
		bool CParserIdentifier::Parse(size_t &index, Token &token)
		{
			// First symbols shouldn't be number
			wchar_t c{ m_pReader->Read(index) };
			if (!m_pLexic->IsIdentifier(c) && !m_pLexic->IsIdentifierNotAll(c))
				return false;
			bool check{ m_pLexic->IsIdentifier(c) };
			// Search possible end
			size_t last{ index + 1 };
			while (last < m_pReader->Max)
			{
				c = m_pReader->Read(last);
				if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c))
					check = true;
				else if (!m_pLexic->IsIdentifierNotAll(c))
					break;
				last++;
			}
			// Check
			if (!check)
				return false;
			token.Type = TokenType::Identifier;
			token.Index = index;
			token.Length = last - index;
			token.ContentIndex = token.Index;
			token.ContentLength = token.Length;
			token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
			token.Prefix = L"";
			token.Postfix = L"";
			token.Count = 1;
			token.Finished = true;
			token.Op = nullptr;
			token.Base = 0;
			token.Integer = 0;
			token.Float = 0;
			index = last;
			return true;
		}
	#pragma endregion
	}
}