// This file is a part of Nitisa framework
// Copyright © 2025 Nitisa. All rights reserved.
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
		CTokenizer::CTokenizer(const Groups &skip_groups) :
			CReleasable(),
			m_pReader{ nullptr },
			m_pParserOperator{ nullptr },
			m_pParserString{ nullptr },
			m_pParserBinary{ nullptr },
			m_pParserOctal{ nullptr },
			m_pParserHexadecimal{ nullptr },
			m_pParserNumeric{ nullptr },
			m_pParserIdentifier{ nullptr },
			m_aSkipGroups{ skip_groups }
		{

		}
	#pragma endregion

	#pragma region Setters
		void CTokenizer::setSkipGroups(const Groups &skip_groups)
		{
			m_aSkipGroups = skip_groups;
		}
	#pragma endregion

	#pragma region ITokenizer methods
		bool CTokenizer::Next(size_t &index, Token &token)
		{
			if (!m_pReader || index < m_pReader->Min || index >= m_pReader->Max)
				return false;
			Token unknown;
			bool is_unknown{ false };
			size_t old_index;
			while (index < m_pReader->Max)
			{
				old_index = index;
				bool is_operator{ false };
				token.Type = TokenType::Unknown;
				if (m_pParserOperator && m_pParserOperator->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					is_operator = true;
				}
				if (m_pParserString && m_pParserString->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (is_operator)
					return true;
				if (m_pParserBinary && m_pParserBinary->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (m_pParserOctal && m_pParserOctal->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (m_pParserHexadecimal && m_pParserHexadecimal->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (m_pParserNumeric && m_pParserNumeric->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (m_pParserIdentifier && m_pParserIdentifier->Parse(index, token))
				{
					if (is_unknown)
					{
						index = old_index;
						token = unknown;
						token.ContentLength = token.Length;
						token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
						return true;
					}
					return true;
				}
				if (is_unknown)
				{
					unknown.Length++;
				}
				else
				{
					is_unknown = true;
					unknown.Type = TokenType::Unknown;
					unknown.Index = index;
					unknown.Length = 1;
					unknown.ContentIndex = index;
					unknown.ContentLength = 1;
					unknown.Value = L"";
					unknown.Prefix = L"";
					unknown.Postfix = L"";
					unknown.Count = 1;
					unknown.Finished = true;
					unknown.Op = nullptr;
					unknown.Base = 0;
					unknown.Integer = 0;
					unknown.Float = 0;
				}
				index++;
			}
			token = unknown;
			token.ContentLength = token.Length;
			token.Value = m_pReader->Read(token.ContentIndex, token.ContentLength);
			return true;
		}

		bool CTokenizer::Next(size_t &index, Tokens &tokens)
		{
			Token token;
			if (!Next(index, token))
				return false;
			if (token.Op && (token.Op->Group == GROUP_SKIP || in(token.Op->Group, m_aSkipGroups)))
				return true;
			if (tokens.empty() || !token.Op || token.Op->Group == GROUP_NO_SKIP)
			{
				tokens.push_back(token);
				return true;
			}
			Token &prev{ tokens[tokens.size() - 1] };
			if (prev.Op && prev.Op->Group == token.Op->Group)
			{
				prev.Type = TokenType::Group;
				prev.Count++;
				return true;
			}
			tokens.push_back(token);
			return true;
		}
	#pragma endregion
	}
}