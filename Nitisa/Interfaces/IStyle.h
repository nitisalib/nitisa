// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Image/BorderColor.h"
#include "../Image/Color.h"
#include "../Image/Gradient.h"
#include "../Math/PointB.h"
#include "../Math/PointF.h"
#include "../Math/Rect.h"
#include "../Math/RectB.h"
#include "../Math/RectF.h"

namespace nitisa
{
	class IStyleFont;
	class IStyleImage;
	class IStyleSkin;

	class IStyle
	{
	protected:
		IStyle() = default;
		~IStyle() = default;
		IStyle(const IStyle &other) = delete;
		IStyle(IStyle &&other) = delete;
		IStyle &operator=(const IStyle &other) = delete;
		IStyle &operator=(IStyle &&other) = delete;
	protected:
		String m_sClassName;
	public:
		String const &ClassName{ m_sClassName }; // Class name

		virtual int getImageCount() = 0; // Return image count
		virtual IStyleImage *getImage(const int index) = 0; // Return image by index
		virtual IStyleImage *getImage(const String &name) = 0; // Return image by name
		virtual int getSkinCount() = 0; // Return skin count
		virtual IStyleSkin *getSkin(const int index) = 0; // Return skin by index
		virtual IStyleSkin *getSkin(const String &name) = 0; // Return skin by name
		virtual int getFontCount() = 0; // Return font count
		virtual IStyleFont *getFont(const int index) = 0; // Return font by index
		virtual IStyleFont *getFont(const String &name) = 0; // Return font by name
		virtual int getOptionCount() = 0; // Return option count

		// Find option by name and store in value if found. If not found, remain unchanged
		virtual bool getOption(const String &name, String &value) = 0;
		virtual bool getOption(const String &name, int &value) = 0;
		virtual bool getOption(const String &name, float &value) = 0;
		virtual bool getOption(const String &name, bool &value) = 0;
		virtual bool getOption(const String &name, Rect &value) = 0;
		virtual bool getOption(const String &name, RectF &value) = 0;
		virtual bool getOption(const String &name, RectB &value) = 0;
		virtual bool getOption(const String &name, BorderColor &value) = 0;
		virtual bool getOption(const String &name, Color &value) = 0;
		virtual bool getOption(const String &name, Point &value) = 0;
		virtual bool getOption(const String &name, PointF &value) = 0;
		virtual bool getOption(const String &name, PointB &value) = 0;
		virtual bool getOption(const String &name, Gradient &value) = 0;
		virtual bool getOption(const String &name, unsigned int &value) = 0;

		virtual void Release() = 0; // Destroy instance. For internal usage only
	};
}