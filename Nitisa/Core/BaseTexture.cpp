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
#pragma region Constructor & destructor
	CBaseTexture::CBaseTexture() :
		CReleasable()
	{
		m_bCreated = false;
		m_hHandle = 0;
		m_eFormat = TextureFormat::RGBA;
		m_sRect = nitisa::Rect{ 0, 0, 0, 0 };
		m_sRectf = RectF{ 0, 0, 0, 0 };
		m_sInvalidRect = nitisa::Rect{ 0, 0, -1, -1 };
	}
#pragma endregion

#pragma region IBaseTexture getters
	bool CBaseTexture::isValid() const
	{
		return !m_sInvalidRect.is_valid();
	}
#pragma endregion

#pragma region IBaseTexture setters
	bool CBaseTexture::setValid(const bool value)
	{
		if (value == m_sInvalidRect.is_valid())
		{
			m_sInvalidRect = value ? nitisa::Rect{ 0, 0, -1, -1 } : m_sRect;
			return true;
		}
		return false;
	}

	bool CBaseTexture::setInvalidRect(const nitisa::Rect &value)
	{
		if (value != m_sInvalidRect)
		{
			m_sInvalidRect = value;
			return true;
		}
		return false;
	}
#pragma endregion
}