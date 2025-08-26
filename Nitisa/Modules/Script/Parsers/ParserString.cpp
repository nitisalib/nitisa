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
	#pragma region Constructor & destructor
		CParserString::CParserString(IReader *reader, ILexic *lexic):
			CReleasable(),
			m_pReader{ reader },
			m_pLexic{ lexic }
		{

		}
	#pragma endregion

	#pragma region IParser methods
		bool CParserString::Parse(size_t &index, Token &token)
		{
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
				while (i != npos && CheckNames(token.Op->Replace, i, name_index))
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
	#pragma endregion
	}
}