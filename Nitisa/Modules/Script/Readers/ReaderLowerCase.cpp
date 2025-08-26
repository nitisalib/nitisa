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
		CReaderLowerCase::CReaderLowerCase() :
			CReleasable()
		{
			m_iMin = 0;
			m_iMax = 0;
		}

		CReaderLowerCase::CReaderLowerCase(const String &source) :
			CReleasable(),
			m_sSource{ source }
		{
			m_iMin = 0;
			m_iMax = m_sSource.length();
		}

		CReaderLowerCase::CReaderLowerCase(const String &source, const size_t min, const size_t max) :
			CReleasable(),
			m_sSource{ source }
		{
			m_iMin = ntl::Clamp<size_t>(min, 0, m_sSource.length());
			m_iMax = ntl::Clamp<size_t>(max, m_iMin, m_sSource.length());
		}
	#pragma endregion

	#pragma region IReader setters
		void CReaderLowerCase::setSource(const String &value)
		{
			m_sSource = value;
			m_iMin = 0;
			m_iMax = m_sSource.length();
		}

		void CReaderLowerCase::setSource(const String &value, const size_t &min, const size_t &max)
		{
			m_sSource = value;
			m_iMin = ntl::Clamp<size_t>(min, 0, m_sSource.length());
			m_iMax = ntl::Clamp<size_t>(max, m_iMin, m_sSource.length());
		}
	#pragma endregion

	#pragma region IReader methods
		wchar_t CReaderLowerCase::Read(const size_t index)
		{
			if (index >= m_iMin && index < m_iMax && index < m_sSource.length())
				return std::use_facet<std::ctype<wchar_t>>(std::locale()).tolower(m_sSource[index]);
			return 0;
		}

		String CReaderLowerCase::Read(const size_t index, const size_t length)
		{
			if (index >= m_iMin && index < m_iMax)
				return m_sSource.substr(index, ntl::Min<size_t>(length, m_iMax - index));
			return L"";
		}
	#pragma endregion
	}
}