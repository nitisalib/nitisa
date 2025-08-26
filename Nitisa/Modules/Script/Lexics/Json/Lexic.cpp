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
		namespace json
		{
		#pragma region Constructor & destructor
			CLexic::CLexic(IReader *reader) :
				CReleasable(),
				m_pReader{ reader }
			{

			}
		#pragma endregion

		#pragma region ILexic methods
			bool CLexic::IsSpace(const wchar_t chr)
			{
				return chr == 0 || std::isspace(chr, std::locale());
			}

			bool CLexic::IsNewLine(const wchar_t chr)
			{
				return chr == L'\n';
			}

			bool CLexic::IsIdentifier(const wchar_t chr)
			{
				return isAz(chr) || chr == L'_' || chr == L'$';
			}

			bool CLexic::IsIdentifierNotStart(const wchar_t chr)
			{
				return isDigit(chr);
			}

			bool CLexic::IsIdentifierNotAll(const wchar_t chr)
			{
				return false;
			}

			bool CLexic::IsIdentifierBoundary(const wchar_t chr)
			{
				return !IsIdentifier(chr) && !IsIdentifierNotStart(chr) && !IsIdentifierNotAll(chr);
			}

			size_t CLexic::Escape(const size_t index)
			{
				if (m_pReader->Read(index) == L'\\')
					return index + 2;
				return index;
			}
		#pragma endregion
		}
	}
}