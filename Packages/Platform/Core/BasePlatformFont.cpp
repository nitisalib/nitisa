// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace platform
	{
	#pragma region Constructor & destructor
		CBasePlatformFont::CBasePlatformFont() :
			CReleasable(),
			m_bSorted{ true }
		{
			
		}
	#pragma endregion

	#pragma region Getters
		PointF CBasePlatformFont::getStringSize(const String &str, const float distance)
		{
			PointF result{ 0, 0 };
			if (str.length() > 0)
			{
				if (ntl::IsGreater<float>(m_sCharacterSize.X, 0) && ntl::IsGreater<float>(m_sCharacterSize.Y, 0))
				{
					result.X = (float)str.length() * m_sCharacterSize.X;
					result.Y = m_sCharacterSize.Y;
					for (const wchar_t c : str) // Need to generate all characters before rendering started. No characters generation in rendering should happen because texture can be changed
						GetChar(c);
				}
				else
				{
					Char *chr{ nullptr };
					for (const wchar_t c : str)
					{
						if (!(chr = GetChar(c)))
							continue;
						result.X += chr->Width;
						result.Y = ntl::Max<float>(result.Y, chr->Height);
					}
				}
				result.X += distance * float(str.length() - 1);
			}
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		void CBasePlatformFont::ClearChars()
		{
			for (auto pos = m_aChars.begin(); pos != m_aChars.end(); pos++)
				delete (*pos);
			m_aChars.clear();
			m_bSorted = true;
		}

		void CBasePlatformFont::SortChars()
		{
			if (!m_bSorted)
			{
				std::sort(m_aChars.begin(), m_aChars.end(), [](const Char *a, const Char *b) { return a->Char < b->Char; });
				m_bSorted = true;
			}
		}

		int CBasePlatformFont::FindCharIndex(const wchar_t chr)
		{
			SortChars();
			m_sSearch.Char = chr;
			auto pos = std::lower_bound(m_aChars.begin(), m_aChars.end(), &m_sSearch, [](const Char *a, const Char *b) {return a->Char < b->Char; });
			if (pos == m_aChars.end())
				return -1;
			if ((*pos)->Char != chr)
				return -1;
			return int(pos - m_aChars.begin());
		}

		CBasePlatformFont::Char *CBasePlatformFont::GetChar(const wchar_t chr)
		{
			int index{ FindCharIndex(chr) };
			if (index >= 0)
				return m_aChars[index];
			Char *img{ CreateChar(chr) };
			if (!img)
				return nullptr;
			m_aChars.push_back(img);
			m_bSorted = false;
			return img;
		}
	#pragma endregion
	}
}