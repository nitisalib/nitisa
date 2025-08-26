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
#include "IFeedbackEx.h"
#include "IFontProperties.h"

namespace nitisa
{
	class IPlatformFont;
	class IRenderer;

	class IFont :public virtual IFontProperties, public virtual IFeedbackEx
	{
	protected:
		IFont() = default;
		~IFont() = default;
		IFont(const IFont &other) = delete;
		IFont(IFont &&other) = delete;
		IFont &operator=(const IFont &other) = delete;
		IFont &operator=(IFont &&other) = delete;
	public:
		virtual IPlatformFont *getPlatformFont(IRenderer *renderer) = 0; // Return platform font. Try to create if not created yet. If failed to create, old one will remain

		virtual bool setFontName(const String &value) = 0; // Set font name
		virtual bool setHeight(const int value) = 0; // Set height
		virtual bool setWeight(const FontWeight value) = 0; // Set weight
		virtual bool setDistance(const float value) = 0; // Set distance between characters
		virtual bool setColor(const nitisa::Color &value) = 0; // Set color
		virtual bool setShadowShift(const PointF &value) = 0; // Set shadow shift
		virtual bool setShadowRadius(const int value) = 0; // Set shadow blur radius
		virtual bool setShadowColor(const nitisa::Color &value) = 0; // Set shadow color
		virtual bool setItalic(const bool value) = 0; // Set italic state
		virtual bool setUnderline(const bool value) = 0; // Set underlined state
		virtual bool setStrikeOut(const bool value) = 0; // Set striked out state
		virtual bool setMonospace(const bool value) = 0; // Set monospace state

		virtual void Release() = 0; // Destroy instance

		virtual void NotifyOnFreeResources() = 0; // Free platform font if assigned
	};
}