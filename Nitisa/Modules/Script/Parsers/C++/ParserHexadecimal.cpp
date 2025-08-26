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
				const String symbols{ L"0123456789abcdefABCDEF" }, symbols_after_exponent{ L"0123456789" }, signs{ L"+-" }, exponents{ L"pP" };
				// First symbols should be 0x or 0X
				wchar_t c{ m_pReader->Read(index + 1) };
				if (m_pReader->Read(index) != L'0' || (c != L'x' && c != L'X'))
					return false;
				// Previous symbol should not be any identifier symbols
				c = m_pReader->Read(index - 1);
				if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
					return false;
				// Search possible end of the number
				bool separator{ false }, exponent{ false }, has_quote{ false };
				size_t last{ index + 2 }, separator_index{ 0 }, exponent_index{ 0 };
				const String *psymbols{ &symbols };
				while (last < m_pReader->Max)
				{
					c = m_pReader->Read(last);
					if (c == L'\'')
					{
						if (psymbols->find(m_pReader->Read(last - 1)) == String::npos || psymbols->find(m_pReader->Read(last + 1)) == String::npos) // ' allowed only between digits
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
						separator_index = last;
					}
					else if (exponents.find(c) != String::npos)
					{
						if (exponent)
							break;
						exponent = true;
						exponent_index = last;
						psymbols = &symbols_after_exponent;
						if (signs.find(m_pReader->Read(last + 1)) != String::npos)
							last++;
					}
					else if (psymbols->find(c) == String::npos)
						break;
					last++;
				}
				if (separator && !exponent) // The exponent is never optional for hexadecimal floating-point literals
					return false;
				// Remove any not number at the end
				while (last > index && psymbols->find(m_pReader->Read(last)) == String::npos && m_pReader->Read(last) != L'.')
					last--;
				// Check whether there are specifiers (L, l, U, u, Z, z, F, f)
				int f_count{ 0 }, u_count{ 0 }, l_count{ 0 }, z_count{ 0 };
				String postfix;
				if (exponent) // Floating-point literal
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
				else // Integer literal
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
				if (token.Length <= 2)
					return false;
				token.ContentIndex = token.Index + 2;
				if (!exponent) // Integer literal
				{
					token.ContentLength = token.Length - u_count - l_count - z_count - 2;
					token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
					if (TryHexToUInt64(has_quote ? ReplaceAll(token.Value, StringKeyValue{ L"'", L"" }) : token.Value, token.Integer))
					{
						token.Type = TokenType::Integer;
						token.Prefix = m_pReader->Read(token.Index, 2);
						token.Postfix = m_pReader->Read(token.ContentIndex + token.ContentLength, u_count + l_count + z_count);
						token.Count = 1;
						token.Finished = true;
						token.Op = nullptr;
						token.Base = 16;
						token.Float = 0;
						index = last + 1;
						return true;
					}
				}
				else // Floating point literal
				{
					token.ContentLength = token.Length - f_count - l_count - 2;
					token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
					token.Float = 0;
					bool valid{ true };
					if (separator) // Has separator and maybe exponent
					{
						// Decode part before separator
						String v1{ token.Value.substr(0, separator_index - token.ContentIndex) };
						if (has_quote)
							ReplaceDirect(v1, StringKeyValue{ L"'", L"" });
						if (!v1.empty())
						{
							uint64 i;
							if (TryHexToUInt64(v1, i))
								token.Float = (double)i;
							else
								valid = false;
						}
						// Decode part after separator
						if (valid)
						{
							String v2;
							if (exponent)
								v2 = token.Value.substr(separator_index - token.ContentIndex + 1, exponent_index - separator_index - 1);
							else
								v2 = token.Value.substr(separator_index - token.ContentIndex + 1, token.Value.length() - v1.length() - 1);
							if (has_quote)
								ReplaceDirect(v2, StringKeyValue{ L"'", L"" });
							if (!v2.empty())
							{
								uint64 i;
								if (TryHexToUInt64(v2, i))
									token.Float += (double)i / double(1llu << (4 * v2.length()));
								else
									valid = false;
							}
							else if (v1.empty()) // Either before or after separator part is required
								valid = false;
						}
						// Decode exponent
						if (valid)
						{
							bool negative{ false };
							c = m_pReader->Read(exponent_index + 1);
							if (c == L'-')
							{
								negative = true;
								exponent_index++;
							}
							else if (c == L'+')
								exponent_index++; // 0xA.Bp31 5-> 5 - (6 - 5 + 1)
							String v2{ token.Value.substr(exponent_index - token.ContentIndex + 1, token.Value.length() - (exponent_index - token.ContentIndex) - 1) };
							if (has_quote)
								ReplaceDirect(v2, StringKeyValue{ L"'", L"" });
							int i;
							if (TryStringToInt(v2, i))
							{
								if (negative)
									token.Float /= (std::pow(2.0, (double)i));
								else
									token.Float *= (std::pow(2.0, (double)i));
							}
						}
					}
					else // Has exponent only
					{
						// Decode part before exponent
						String v1{ token.Value.substr(0, exponent_index - token.ContentIndex) };
						if (has_quote)
							ReplaceDirect(v1, StringKeyValue{ L"'", L"" });
						if (!v1.empty())
						{
							uint64 i;
							if (TryHexToUInt64(v1, i))
								token.Float = (double)i;
							else
								valid = false;
						}
						else
							valid = false;
						// Decode exponent
						if (valid)
						{
							bool negative{ false };
							c = m_pReader->Read(exponent_index + 1);
							if (c == L'-')
							{
								negative = true;
								exponent_index++;
							}
							else if (c == L'+')
								exponent_index++; // 0xA.Bp31 5-> 5 - (6 - 5 + 1)
							String v2{ token.Value.substr(exponent_index - token.ContentIndex + 1, token.Value.length() - (exponent_index - token.ContentIndex) - 1) };
							if (has_quote)
								ReplaceDirect(v2, StringKeyValue{ L"'", L"" });
							int i;
							if (TryStringToInt(v2, i))
							{
								if (negative)
									token.Float /= (std::pow(2.0, (double)i));
								else
									token.Float *= (std::pow(2.0, (double)i));
							}
						}
					}
					if (valid)
					{
						token.Type = TokenType::Float;
						token.Prefix = m_pReader->Read(token.Index, 2);
						token.Postfix = m_pReader->Read(token.ContentIndex + token.ContentLength, f_count + l_count);
						token.Count = 1;
						token.Finished = true;
						token.Op = nullptr;
						token.Base = 16;
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