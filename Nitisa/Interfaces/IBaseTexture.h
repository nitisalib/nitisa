// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/TextureFormat.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "IReleasable.h"

namespace nitisa
{
	/*
		In implementations avoid calculating values on the fly in getWidthf(), getHeightf(), getSize(), getSizef(), getRect(), getRectf() methods. Instead use stored prior calculated value which is
		only calculated when texture size is being changed. Rect and RectF types are the best choice for storing texture size information. For example, the size can be get directly as RightBottom
		property.
	*/
	class IBaseTexture : public virtual IReleasable
	{
	protected:
		IBaseTexture() = default;
		~IBaseTexture() = default;
		IBaseTexture(const IBaseTexture &other) = delete;
		IBaseTexture(IBaseTexture &&other) = delete;
		IBaseTexture &operator=(const IBaseTexture &other) = delete;
		IBaseTexture &operator=(IBaseTexture &&other) = delete;
	protected:
		bool m_bCreated;
		PlatformHandle m_hHandle;
		TextureFormat m_eFormat;
		nitisa::Rect m_sRect;
		RectF m_sRectf;
		nitisa::Rect m_sInvalidRect;
	public:
		bool const &Created{ m_bCreated };
		PlatformHandle const &Handle{ m_hHandle };
		TextureFormat const &Format{ m_eFormat };
		int const &Width{ m_sRect.Right };
		float const &Widthf{ m_sRectf.Right };
		int const &Height{ m_sRect.Bottom };
		float const &Heightf{ m_sRectf.Bottom };
		Point const &Size{ m_sRect.RightBottom };
		PointF const &Sizef{ m_sRectf.RightBottom };
		nitisa::Rect const &Rect{ m_sRect };
		RectF const &Rectf{ m_sRectf };
		nitisa::Rect const &InvalidRect{ m_sInvalidRect };

		virtual bool isValid() const = 0; // Return true only if invalid rectangle value is invalid

		virtual bool setFormat(const TextureFormat value) = 0;
		virtual bool setSize(const int width, const int height) = 0; // Resize
		virtual bool setValid(const bool value) = 0;
		virtual bool setInvalidRect(const nitisa::Rect &value) = 0;
	};
}