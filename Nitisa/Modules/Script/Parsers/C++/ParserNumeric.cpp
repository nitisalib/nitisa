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
				bool exponent{ false }, has_quote{ false };
				size_t last{ index + 1 };
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
				// Check whether there are specifiers (L, l, U, u, Z, z, F, f)
				int f_count{ 0 }, u_count{ 0 }, l_count{ 0 }, z_count{ 0 };
				String postfix;
				if (separator || exponent)
				{
					c = m_pReader->Read(last + 1);
					if (c == L'f' || c == L'F')
						f_count++;
					else if (c == L'l' || c == L'L')
						l_count++;
					if ((f_count + l_count > 0) && (f_count == 0 || l_count == 0) && m_pLexic->IsIdentifierBoundary(m_pReader->Read(last + f_count + l_count + 1)))
						last += f_count + l_count;
					else
						f_count = l_count = 0;
				}
				else
				{
					for (size_t i = 1; i <= 3; i++)
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
					if ((u_count + l_count + z_count > 0) && l_count <= 2 && u_count <= 1 && z_count <= 1 && (z_count == 0 || l_count == 0) && m_pLexic->IsIdentifierBoundary(m_pReader->Read(last + u_count + l_count + z_count + 1)))
						last += u_count + l_count + z_count;
					else
						u_count = l_count = z_count = 0;
				}
				// Next symbol should not be any identifier symbol
				c = m_pReader->Read(last + 1);
				if (m_pLexic->IsIdentifierNotStart(c)) // Identifier after the number is user-defined literal
					return false;
				// Check convert string to integer
				token.Index = index;
				token.Length = last - index + 1;
				token.ContentIndex = token.Index;
				if (!separator && !exponent)
				{
					token.ContentLength = token.Length - u_count - l_count - z_count;
					token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
					if (TryStringToUInt64(has_quote ? ReplaceAll(token.Value, StringKeyValue{ L"'", L"" }) : token.Value, token.Integer))
					{
						token.Type = TokenType::Integer;
						token.Prefix = L"";
						token.Postfix = m_pReader->Read(token.ContentIndex + token.ContentLength, u_count + l_count + z_count);
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
					token.ContentLength = token.Length - f_count - l_count;
					token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
					if (TryStringToDouble(has_quote ? ReplaceAll(token.Value, StringKeyValue{ L"'", L"" }) : token.Value, token.Float))
					{
						token.Type = TokenType::Float;
						token.Prefix = L"";
						token.Postfix = m_pReader->Read(token.ContentIndex + token.ContentLength, f_count + l_count);
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
}