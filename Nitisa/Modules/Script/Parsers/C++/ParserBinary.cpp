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
		namespace cpp
		{
		#pragma region Constructor & destructor
			CParserBinary::CParserBinary(IReader *reader, ILexic *lexic) :
				CReleasable(),
				m_pReader{ reader },
				m_pLexic{ lexic }
			{

			}
		#pragma endregion

		#pragma region IParser methods
			bool CParserBinary::Parse(size_t &index, Token &token)
			{
				static String symbols{ L"01" };
				// First symbol should be 0
				if (m_pReader->Read(index) != L'0')
					return false;
				// Second symbol should be b
				if (m_pReader->Read(index + 1) != L'b' && m_pReader->Read(index + 1) != L'B')
					return false;
				// Previous symbol should not be any identifier symbols
				wchar_t c{ m_pReader->Read(index - 1) };
				if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
					return false;
				// Search index of last symbols in 0..1 range
				size_t last{ index + 2 };
				bool has_quote{ false };
				while (last < m_pReader->Max)
				{
					c = m_pReader->Read(last);
					if (c == L'\'')
					{
						if (symbols.find(m_pReader->Read(last - 1)) == String::npos || symbols.find(m_pReader->Read(last + 1)) == String::npos) // ' allowed only between digits
							return false;
						has_quote = true;
						last++;
						continue;
					}
					if (symbols.find(m_pReader->Read(last)) == String::npos)
						break;
					last++;
				}
				// Check whether there are specifiers (L, l, U, u)
				int u_count{ 0 }, l_count{ 0 }, z_count{ 0 };
				String postfix;
				for (size_t i = 0; i <= 2; i++)
				{
					c = m_pReader->Read(last + i);
					if (c == L'u' || c == L'U')
						u_count++;
					else if (c == L'l' || c == L'L')
						l_count++;
					else if (c == L'z' || c == L'Z') // C++23
						z_count++;
					else
						break;
				}
				if ((u_count + l_count + z_count > 0) && l_count <= 2 && u_count <= 1 && z_count <= 1 && (z_count == 0 || l_count == 0) && m_pLexic->IsIdentifierBoundary(m_pReader->Read(last + u_count + l_count + z_count)))
					last += u_count + l_count + z_count;
				else
					u_count = l_count = z_count = 0;
				// Next symbol should not be any identifier symbol
				c = m_pReader->Read(last);
				if (m_pLexic->IsIdentifierNotStart(c)) // Identifier after the number is user-defined literal
					return false;
				token.Type = TokenType::Integer;
				token.Index = index;
				token.Length = last - index;
				if (token.Length <= 2)
					return false;
				token.ContentIndex = token.Index + 2;
				token.ContentLength = token.Length - u_count - l_count - z_count - 2;
				token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
				token.Prefix = m_pReader->Read(token.Index, 2);
				token.Postfix = m_pReader->Read(token.ContentIndex + token.ContentLength, u_count + l_count + z_count);
				token.Count = 1;
				token.Finished = true;
				token.Op = nullptr;
				token.Base = 2;
				if (!TryBinToUInt64(has_quote ? ReplaceAll(token.Value, StringKeyValue{ L"'", L"" }) : token.Value, token.Integer))
					return false;
				token.Float = 0;
				index = last;
				return true;
			}
		#pragma endregion
		}
	}
}