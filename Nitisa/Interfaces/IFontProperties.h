// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/FontWeight.h"
#include "../Core/Strings.h"
#include "../Math/PointF.h"
#include "../Image/Color.h"

namespace nitisa
{
	class IFontProperties
	{
	protected:
		IFontProperties() = default;
		~IFontProperties() = default;
		IFontProperties(const IFontProperties &other) = delete;
		IFontProperties(IFontProperties &&other) = delete;
		IFontProperties &operator=(const IFontProperties &other) = delete;
		IFontProperties &operator=(IFontProperties &&other) = delete;
	protected:
		String m_sFontName;
		int m_iHeight;
		FontWeight m_eWeight;
		float m_fDistance;
		nitisa::Color m_sColor;
		PointF m_sShadowShift;
		int m_iShadowRadius;
		nitisa::Color m_sShadowColor;
		bool m_bItalic;
		bool m_bUnderline;
		bool m_bStrikeOut;
		bool m_bMonospace;
	public:
		String const &FontName{ m_sFontName }; // Font name
		int const &Height{ m_iHeight }; // Height
		FontWeight const &Weight{ m_eWeight }; // Weight
		float const &Distance{ m_fDistance }; // Distance between characters
		nitisa::Color const &Color{ m_sColor }; // Color
		PointF const &ShadowShift{ m_sShadowShift }; // Shadow shift
		int const &ShadowRadius{ m_iShadowRadius }; // Shadow blur radius
		nitisa::Color const &ShadowColor{ m_sShadowColor }; // Shadow color
		bool const &Italic{ m_bItalic }; // Whether it is italic
		bool const &Underline{ m_bUnderline }; // Whether it is underlined
		bool const &StrikeOut{ m_bStrikeOut }; // Whether it is striked out
		bool const &Monospace{ m_bMonospace }; // Whether font was created as monospace one

		virtual bool isEqual(IFontProperties *font) = 0; // Check if has the same properties as the specified font

		virtual bool Copy(IFontProperties *src) = 0; // Copy properties from specified font
	};
}