// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Math/RectF.h"

namespace nitisa
{
	class IStyleImage;

	class IStyleSkin
	{
	protected:
		IStyleSkin() = default;
		~IStyleSkin() = default;
		IStyleSkin(const IStyleSkin &other) = delete;
		IStyleSkin(IStyleSkin &&other) = delete;
		IStyleSkin &operator=(const IStyleSkin &other) = delete;
		IStyleSkin &operator=(IStyleSkin &&other) = delete;
	protected:
		String m_sName;
		RectF m_sRect;
	public:
		String const &Name{ m_sName }; // Name
		RectF const &Rect{ m_sRect }; // Rectangle which is an image part

		virtual IStyleImage *getImage() = 0; // Return corresponding style image
	};
}