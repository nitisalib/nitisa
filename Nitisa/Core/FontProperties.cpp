// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CFontProperties::CFontProperties()
	{
		m_sFontName = L"Tahoma";
		m_iHeight = -11;
		m_eWeight = FontWeight::Normal;
		m_bItalic = false;
		m_bUnderline = false;
		m_bStrikeOut = false;
		m_fDistance = 0;
		m_sColor = nitisa::Color{ 0, 0, 0, 255 };
		m_sShadowShift = PointF{ 0, 0 };
		m_iShadowRadius = 1;
		m_sShadowColor = nitisa::Color{ 0, 0, 0, 0 };
		m_bMonospace = false;
	}

	CFontProperties::CFontProperties(IFontProperties *other) : CFontProperties()
	{
		if (other)
		{
			m_sFontName = other->FontName;
			m_iHeight = other->Height;
			m_eWeight = other->Weight;
			m_bItalic = other->Italic;
			m_bUnderline = other->Underline;
			m_bStrikeOut = other->StrikeOut;
			m_fDistance = other->Distance;
			m_sColor = other->Color;
			m_sShadowShift = other->ShadowShift;
			m_iShadowRadius = other->ShadowRadius;
			m_sShadowColor = other->ShadowColor;
			m_bMonospace = other->Monospace;
		}
	}

	bool CFontProperties::isEqual(IFontProperties *font)
	{
		return font &&
			font->FontName == m_sFontName &&
			font->Height == m_iHeight &&
			font->Weight == m_eWeight &&
			ntl::IsEqual<float>(font->Distance, m_fDistance) &&
			font->Color == m_sColor &&
			IsEqual(font->ShadowShift, m_sShadowShift) &&
			font->ShadowRadius == m_iShadowRadius &&
			font->ShadowColor == m_sShadowColor &&
			font->Italic == m_bItalic &&
			font->Underline == m_bUnderline &&
			font->StrikeOut == m_bStrikeOut &&
			font->Monospace == m_bMonospace;
	}

	bool CFontProperties::Copy(IFontProperties *src)
	{
		if (!src || src == this)
			return false;
		bool result{ false };
		if (m_sFontName != src->FontName)
		{
			m_sFontName = src->FontName;
			result = true;
		}
		if (m_iHeight != src->Height)
		{
			m_iHeight = src->Height;
			result = true;
		}
		if (m_eWeight != src->Weight)
		{
			m_eWeight = src->Weight;
			result = true;
		}
		if (m_bItalic != src->Italic)
		{
			m_bItalic = src->Italic;
			result = true;
		}
		if (m_bUnderline != src->Underline)
		{
			m_bUnderline = src->Underline;
			result = true;
		}
		if (m_bStrikeOut != src->StrikeOut)
		{
			m_bStrikeOut = src->StrikeOut;
			result = true;
		}
		if (ntl::IsNotEqual<float>(m_fDistance, src->Distance))
		{
			m_fDistance = src->Distance;
			result = true;
		}
		if (m_sColor != src->Color)
		{
			m_sColor = src->Color;
			result = true;
		}
		if (IsNotEqual(m_sShadowShift, src->ShadowShift))
		{
			m_sShadowShift = src->ShadowShift;
			result = true;
		}
		if (m_iShadowRadius != src->ShadowRadius)
		{
			m_iShadowRadius = src->ShadowRadius;
			result = true;
		}
		if (m_sShadowColor != src->ShadowColor)
		{
			m_sShadowColor = src->ShadowColor;
			result = true;
		}
		if (m_bMonospace != src->Monospace)
		{
			m_bMonospace = src->Monospace;
			result = true;
		}
		return result;
	}
}