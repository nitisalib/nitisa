// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/FontWeight.h"
#include "../Core/Strings.h"
#include "../Image/ImageMask.h"
#include "../Math/PointF.h"
#include "IReleasable.h"

namespace nitisa
{
	class ITexture;

	class IPlatformFont : public virtual IReleasable
	{
	protected:
		IPlatformFont() = default;
		~IPlatformFont() = default;
		IPlatformFont(const IPlatformFont &other) = delete;
		IPlatformFont(IPlatformFont &&other) = delete;
		IPlatformFont &operator=(const IPlatformFont &other) = delete;
		IPlatformFont &operator=(IPlatformFont &&other) = delete;
	public:
		struct Char // Character data
		{
			wchar_t Char; // Character
			float Width; // Width returned by system
			float Height; // Height returned by system
			ImageMask Data; // Character image
			// Texture coordinates of the character in all characters texture
			float Tx1;
			float Ty1;
			float Tx2;
			float Ty2;
		};
	protected:
		PlatformHandle m_hHandle;
		bool m_bItalic;
		bool m_bUnderline;
		bool m_bStrikeOut;
		bool m_bMonospace;
		String m_sFontName;
		int m_iHeight;
		FontWeight m_eWeight;
		PointF m_sCharacterSize;
	public:
		PlatformHandle const &Handle{ m_hHandle }; // Platform dependent handle
		bool const &Italic{ m_bItalic }; // Whether font is italic or not
		bool const &Underline{ m_bUnderline }; // Whether font is underlined or not
		bool const &StrikeOut{ m_bStrikeOut }; // Whether font is strike outed or not
		bool const &Monospace{ m_bMonospace }; // Return whether font was created in monospace mode
		String const &FontName{ m_sFontName }; // Font family name
		int const &Height{ m_iHeight }; // Height
		FontWeight const &Weight{ m_eWeight }; // Weight
		PointF const &CharacterSize{ m_sCharacterSize }; // Character size. If font isn't monospaced the result is PointF{ 0, 0 }

		virtual Char *getChar(const wchar_t chr) = 0; // Find character information. Create if not found and possible
		virtual PointF getStringSize(const String &str, const float distance) = 0; // Return string size, with specified distance between characters added
		virtual ITexture *getTexture() = 0;
	};
}