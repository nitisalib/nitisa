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
		CParserNumeric::CParserNumeric(IReader *reader, ILexic *lexic) :
			CReleasable(),
			m_pReader{ reader },
			m_pLexic{ lexic }
		{

		}
	#pragma endregion

	#pragma region IParser methods
		bool CParserNumeric::Parse(size_t &index, Token &token)
		{
			const String symbols{ L"0123456789" }, signs{ L"+-" }, exponents{ L"eE" };
			// First symbols should be number
			wchar_t c{ m_pReader->Read(index) };
			if (c != L'.' && symbols.find(c) == String::npos)
				return false;
			bool separator{ c == L'.' };
			// Previous symbol should not be any identifier symbols
			c = m_pReader->Read(index - 1);
			if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
				return false;
			// Search possible end of the number
			bool exponent{ false };
			size_t last{ index + 1 };
			while (last < m_pReader->Max)
			{
				c = m_pReader->Read(last);
				if (c == L'.')
				{
					if (separator || exponent)
						break;
					separator = true;
				}
				else if (exponents.find(c) != String::npos)
				{
					if (exponent)
						break;
					exponent = true;
					if (signs.find(m_pReader->Read(last + 1)) != String::npos)
						last++;
				}
				else if (symbols.find(c) == String::npos)
					break;
				last++;
			}
			// Remove any not number at the end
			while (last > index && symbols.find(m_pReader->Read(last)) == String::npos && m_pReader->Read(last) != L'.')
				last--;
			// Next symbol should not be any identifier symbol
			c = m_pReader->Read(last + 1);
			if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
				return false;
			// Check convert string to integer
			token.Index = index;
			token.Length = last - index + 1;
			token.ContentIndex = token.Index;
			token.ContentLength = token.Length;
			token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
			if (!separator && !exponent)
			{
				if (TryStringToUInt64(token.Value, token.Integer))
				{
					token.Type = TokenType::Integer;
					token.Prefix = L"";
					token.Postfix = L"";
					token.Count = 1;
					token.Finished = true;
					token.Op = nullptr;
					token.Base = 10;
					token.Float = 0;
					index = last + 1;
					return true;
				}
			}
			else
			{
				if (TryStringToDouble(token.Value, token.Float))
				{
					token.Type = TokenType::Float;
					token.Prefix = L"";
					token.Postfix = L"";
					token.Count = 1;
					token.Finished = true;
					token.Op = nullptr;
					token.Base = 10;
					token.Integer = 0;
					index = last + 1;
					return true;
				}
			}
			return false;
		}
	#pragma endregion
	}
}