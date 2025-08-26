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
		CParserHexadecimal::CParserHexadecimal(IReader *reader, ILexic *lexic) :
			CReleasable(),
			m_pReader{ reader },
			m_pLexic{ lexic }
		{

		}
	#pragma endregion

	#pragma region IParser methods
		bool CParserHexadecimal::Parse(size_t &index, Token &token)
		{
			const String symbols{ L"0123456789abcdefABCDEF" };
			// First symbols should be 0x or 0X
			wchar_t c{ m_pReader->Read(index + 1) };
			if (m_pReader->Read(index) != L'0' || (c != L'x' && c != L'X'))
				return false;
			// Previous symbol should not be any identifier symbols
			c = m_pReader->Read(index - 1);
			if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
				return false;
			// Search index of last symbols in 0..f range
			size_t last{ index + 2 };
			while (last < m_pReader->Max && symbols.find(m_pReader->Read(last)) != String::npos)
				last++;
			// Next symbol should not be any identifier symbol
			c = m_pReader->Read(last);
			if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
				return false;
			// Length should not be 0
			if (last == index + 2)
				return false;
			token.Type = TokenType::Integer;
			token.Index = index;
			token.Length = last - index;
			token.ContentIndex = token.Index + 2;
			token.ContentLength = token.Length - 2;
			token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
			token.Prefix = m_pReader->Read(token.Index, 2);
			token.Postfix = L"";
			token.Count = 1;
			token.Finished = true;
			token.Op = nullptr;
			token.Base = 16;
			if (!TryHexToUInt64(token.Value, token.Integer))
				return false;
			token.Float = 0;
			index = last;
			return true;
		}
	#pragma endregion
	}
}