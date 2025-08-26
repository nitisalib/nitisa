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
				// TODO: Add using missing ranges. Probably chr should be char16_t for that
				return
					isAz(chr) ||
					isUnderscore(chr)/* ||
					chr == L'\u00A8' ||
					chr == L'\u00AA' ||
					chr == L'\u00AD' ||
					chr == L'\u00AF' ||
					chr == L'\u2054' ||
					ntl::IsBetween<wchar_t>(chr, L'\u00B7', L'\u00BA') ||
					ntl::IsBetween<wchar_t>(chr, L'\u0100', L'\u167F') ||
					ntl::IsBetween<wchar_t>(chr, L'\u200B', L'\u200D') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2070', L'\u218F') ||
					ntl::IsBetween<wchar_t>(chr, L'\u3004', L'\u3007') ||
					ntl::IsBetween<wchar_t>(chr, L'\uF900', L'\uFD3D') ||
					ntl::IsBetween<wchar_t>(chr, L'\u00BC', L'\u00BE') ||
					ntl::IsBetween<wchar_t>(chr, L'\u1681', L'\u180D') ||
					ntl::IsBetween<wchar_t>(chr, L'\u202A', L'\u202E') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2460', L'\u24FF') ||
					ntl::IsBetween<wchar_t>(chr, L'\u3021', L'\u302F') ||
					ntl::IsBetween<wchar_t>(chr, L'\uFD40', L'\uFDCF') ||
					ntl::IsBetween<wchar_t>(chr, L'\u00C0', L'\u00D6') ||
					ntl::IsBetween<wchar_t>(chr, L'\u180F', L'\u1FFF') ||
					ntl::IsBetween<wchar_t>(chr, L'\u203F', L'\u2040') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2776', L'\u2793') ||
					ntl::IsBetween<wchar_t>(chr, L'\u3031', L'\uD7FF') ||
					ntl::IsBetween<wchar_t>(chr, L'\uFDF0', L'\uFE44') ||
					ntl::IsBetween<wchar_t>(chr, L'\u00D8', L'\u00F6') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2C00', L'\u2FDD') ||
					ntl::IsBetween<wchar_t>(chr, L'\uFE47', L'\uFFFD') ||
					ntl::IsBetween<wchar_t>(chr, L'\u00B2', L'\u00B5') ||
					ntl::IsBetween<wchar_t>(chr, L'\u00F8', L'\u00FF') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2060', L'\u206F') ||
					ntl::IsBetween<wchar_t>(chr, L'\u2E80', L'\u2FFF')*/;
			}

			bool CLexic::IsIdentifierNotStart(const wchar_t chr)
			{
				return
					isDigit(chr)/* ||
					ntl::IsBetween<wchar_t>(chr, L'\u0300', L'\u036F') ||
					ntl::IsBetween<wchar_t>(chr, L'\u1DC0', L'\u1DFF') ||
					ntl::IsBetween<wchar_t>(chr, L'\u20D0', L'\u20FF') ||
					ntl::IsBetween<wchar_t>(chr, L'\uFE20', L'\uFE2F')*/;
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
				{
					wchar_t next{ m_pReader->Read(index + 1) };
					if (next != L'\n' && next != L'\r')
						return index + 2;
				}
				return index;
			}
		#pragma endregion
		}
	}
}