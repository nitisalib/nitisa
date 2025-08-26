// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Image/Color.h"
#include "../Interfaces/IFont.h"
#include "../Math/PointF.h"
#include "FeedbackEx.h"
#include "FontProperties.h"
#include "FontWeight.h"
#include "Strings.h"
#include "Variant.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IFeedbackExListener;
	class IFont;
	class IFontProperties;
	class IPlatformFont;

	class CFont :public virtual IFont, public CFeedbackEx, public CFontProperties
	{
	private:
		IPlatformFont *m_pPlatformFont; // Released if any platform form dependent parameter is changed

		bool FeedbackBefore();
	public:
		IPlatformFont *getPlatformFont(IRenderer *renderer) override;

		bool setFontName(const String &value) override;
		bool setHeight(const int value) override;
		bool setWeight(const FontWeight value) override;
		bool setDistance(const float value) override;
		bool setColor(const nitisa::Color &value) override;
		bool setShadowShift(const PointF &value) override;
		bool setShadowRadius(const int value) override;
		bool setShadowColor(const nitisa::Color &value) override;
		bool setItalic(const bool value) override;
		bool setUnderline(const bool value) override;
		bool setStrikeOut(const bool value) override;
		bool setMonospace(const bool value) override;

		void Release() override;
		bool Copy(IFontProperties *src) override;

		void NotifyOnFreeResources() override;

		CFont(); // Create without listener
		CFont(IFeedbackExListener *listener); // Create with specified listener
		CFont(IFeedbackExListener *listener, IFont *font); // Create with specified listener and copy properties from specified font
		~CFont() override;
	};

	bool FontToVariant(IFontProperties *IFont, Variant &out);
	bool VariantToFont(IFont *font, const Variant &value);
}