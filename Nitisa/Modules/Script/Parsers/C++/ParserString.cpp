// This file is a part of Nitisa framework
// Copyright © 2024 Nitisa. All rights reserved.
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
			CParserString::CParserString(IReader *reader, ILexic *lexic, const Operator *single_quote, const Operator *double_quote) :
				CReleasable(),
				m_pReader{ reader },
				m_pLexic{ lexic },
				m_pSingleQuote{ single_quote },
				m_pDoubleQuote{ double_quote }
			{

			}
		#pragma endregion

		#pragma region IParser methods
			bool CParserString::Parse(size_t &index, Token &token)
			{
				if (token.Type == TokenType::Operator)
					index -= token.Op->Name.length();
				// Check single quote string
				wchar_t c{ m_pReader->Read(index) };
				if (c == L'\'')
					return ParseSingleQuote(index, token, 0);
				if ((c == L'L' || c == L'U') && m_pReader->Read(index + 1) == L'\'')
					return ParseSingleQuote(index, token, 1);
				if (c == L'u')
				{
					wchar_t n{ m_pReader->Read(index + 1) };
					if (n == L'\'')
						return ParseSingleQuote(index, token, 1);
					if (n == L'8' && m_pReader->Read(index + 2) == L'\'')
						return ParseSingleQuote(index, token, 2);
				}

				// Check double quote string
				if (c == L'"')
					return ParseDoubleQuote(index, token, 0, false);
				if (c == L'L' || c == L'U')
				{
					wchar_t n{ m_pReader->Read(index + 1) };
					if (n == L'"')
						return ParseDoubleQuote(index, token, 1, false);
					if (n == L'R' && m_pReader->Read(index + 2) == L'"')
						return ParseDoubleQuote(index, token, 2, true);
				}
				if (c == L'u')
				{
					wchar_t n{ m_pReader->Read(index + 1) };
					if (n == L'"')
						return ParseDoubleQuote(index, token, 1, false);
					if (n == L'R' && m_pReader->Read(index + 2) == L'"')
						return ParseDoubleQuote(index, token, 2, true);
					if (n == L'8')
					{
						n = m_pReader->Read(index + 2);
						if (n == L'"')
							return ParseDoubleQuote(index, token, 2, false);
						if (n == L'R' && m_pReader->Read(index + 3) == L'"')
							return ParseDoubleQuote(index, token, 3, true);
					}
				}
				if (c == L'R' && m_pReader->Read(index + 1) == L'"')
					return ParseDoubleQuote(index, token, 1, true);
				if (token.Type == TokenType::Operator)
					index += token.Op->Name.length();
				
				// Another string type, operator based
				if (token.Type != TokenType::Operator)
					return false;
				// If operator isn't a sequence, than it can't be string
				if (!token.Op->Sequence)
					return false;
				// Multi-line operator should have close sequence
				if (token.Op->Multiline && token.Op->Close.empty())
					return false;
				// Find index of close substring
				size_t i{ Find(token.Op->Close, index, token.Op->Multiline) };
				// If there is ignoring substring, than search close substring until it isn't ignore substring or string end
				if (token.Op->Replace != EmptyStringKeyValueArray)
				{
					size_t name_index;
					while (i != npos && CheckNames(token.Op->Replace, i - 1, name_index))
						i = Find(token.Op->Close, i + token.Op->Replace[name_index].first.length(), token.Op->Multiline);
				}
				// Create token
				token.Type = TokenType::String;
				token.ContentIndex = index;
				if (i == npos)
				{
					// Not finished, end of file
					token.Length = m_pReader->Max - token.Index;
					token.ContentLength = m_pReader->Max - token.ContentIndex;
					token.Finished = false;
					index = m_pReader->Max;
				}
				else if (!CheckName(token.Op->Close, i))
				{
					// Not finished, end of line
					token.Length = i - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = !token.Op->Multiline && token.Op->Close.empty();
					index = i;
				}
				else
				{
					// Finished
					token.Length = i + token.Op->Close.length() - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = true;
					index = i + token.Op->Close.length();
				}
				token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
				if (token.Op->Replace != EmptyStringKeyValueArray)
					ReplaceAllDirect(token.Value, token.Op->Replace);
				return true;
			}
		#pragma endregion

		#pragma region Helpers
			bool CParserString::CheckName(const String &name, const size_t index)
			{
				for (size_t i = 0; i < name.length(); i++)
					if (name[i] != m_pReader->Read(index + i))
						return false;
				return true;
			}

			bool CParserString::CheckNames(const StringKeyValueArray &names, const size_t index, size_t &name_index)
			{
				for (name_index = 0; name_index < names.size(); name_index++)
					if (CheckName(names[name_index].first, index))
						return true;
				return false;
			}

			size_t CParserString::Find(const String &substring, const size_t start, const bool multiline)
			{
				if (multiline)
				{
					size_t i{ start };
					while (i < m_pReader->Max)
					{
						size_t new_i{ m_pLexic->Escape(i) };
						while (new_i > i)
						{
							i = new_i;
							new_i = m_pLexic->Escape(i);
						}
						i = ntl::Min<size_t>(i, m_pReader->Max);
						if (CheckName(substring, i))
							return i;
						i++;
					}
				}
				else
				{
					size_t i{ start };
					while (i < m_pReader->Max)
					{
						size_t new_i{ m_pLexic->Escape(i) };
						while (new_i > i)
						{
							i = new_i;
							new_i = m_pLexic->Escape(i);
						}
						i = ntl::Min<size_t>(i, m_pReader->Max);
						if (CheckName(substring, i) || m_pLexic->IsNewLine(m_pReader->Read(i)))
							return i;
						i++;
					}
				}
				return npos;
			}

			bool CParserString::ParseSingleQuote(size_t &index, Token &token, const size_t prefix_length)
			{
				// There should not be any identifier like part before prefix
				if (prefix_length > 0)
				{
					wchar_t c{ m_pReader->Read(index - 1) };
					if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
						return false;
				}
				// Find index of close substring
				size_t i{ Find(L"'", index + prefix_length + 1, false) };
				// If there is ignoring substring, than search close substring until it isn't ignore substring or string end
				while (i != npos && CheckName(L"\\'", i))
					i = Find(L"'", i + 2, false);
				// Create token
				token.Type = TokenType::String;
				token.Index = index;
				token.ContentIndex = index + prefix_length + 1;
				if (i == npos)
				{
					// Not finished, end of file
					token.Length = m_pReader->Max - token.Index;
					token.ContentLength = m_pReader->Max - token.ContentIndex;
					token.Finished = false;
					index = m_pReader->Max;
				}
				else if (!CheckName(L"'", i))
				{
					// Not finished, end of line
					token.Length = i - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = false;
					index = i;
				}
				else
				{
					// Finished
					token.Length = i + 1 - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = true;
					index = i + 1;
				}
				token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
				ReplaceAllDirect(token.Value, StringKeyValue{ L"\\'", L"'" });
				token.Prefix = m_pReader->Read(token.Index, prefix_length);
				token.Postfix = L"";
				token.Count = 1;
				token.Op = m_pSingleQuote;
				token.Base = 0;
				token.Integer = 0;
				token.Float = 0;
				return true;
			}

			bool CParserString::ParseDoubleQuote(size_t &index, Token &token, const size_t prefix_length, const bool raw)
			{
				// There should not be any identifier like part before prefix
				wchar_t c;
				if (prefix_length > 0)
				{
					c = m_pReader->Read(index - 1);
					if (m_pLexic->IsIdentifier(c) || m_pLexic->IsIdentifierNotStart(c) || m_pLexic->IsIdentifierNotAll(c))
						return false;
				}
				size_t delimiter_length{ 0 }, i;
				String close;
				bool multiline;
				if (raw)
				{
					bool success{ false };
					size_t j{ index + prefix_length + 1 };
					while (j < m_pReader->Max)
					{
						c = m_pReader->Read(j);
						if (c == L'\\' || c == L')' || m_pLexic->IsSpace(c) || m_pLexic->IsNewLine(c))
							return false;
						if (c == L'(')
						{
							success = true;
							break;
						}
						delimiter_length++;
						j++;
					}
					if (!success)
						return false;
					close = L")" + m_pReader->Read(index + prefix_length + 1, delimiter_length) + L"\"";
					multiline = true;
					i = index + prefix_length + delimiter_length + 2;
				}
				else
				{
					close = L"\"";
					multiline = false;
					i = index + prefix_length + 1;
				}

				// Find index of close substring
				i = Find(close, i, multiline);
				// Create token
				token.Type = TokenType::String;
				token.Index = index;
				token.ContentIndex = index + prefix_length + 1 + (raw ? (delimiter_length + 1) : 0);
				if (i == npos)
				{
					// Not finished, end of file
					token.Length = m_pReader->Max - token.Index;
					token.ContentLength = m_pReader->Max - token.ContentIndex;
					token.Finished = false;
					index = m_pReader->Max;
				}
				else if (!CheckName(close, i))
				{
					// Not finished, end of line
					token.Length = i - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = false;
					index = i;
				}
				else
				{
					// Finished
					token.Length = i + close.length() - token.Index;
					token.ContentLength = i - token.ContentIndex;
					token.Finished = true;
					index = i + close.length();
				}
				token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
				token.Prefix = m_pReader->Read(token.Index, prefix_length);
				token.Postfix = raw ? close.substr(1, close.length() - 2) : L"";
				token.Count = 1;
				token.Op = m_pDoubleQuote;
				token.Base = 0;
				token.Integer = 0;
				token.Float = 0;
				return true;
			}
		#pragma endregion
		}
	}
}