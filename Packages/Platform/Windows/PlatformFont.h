// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/Aliases.h"
#include "../Core/BasePlatformFont.h"

namespace nitisa
{
	class IRenderer;
	class ITexture;

	namespace platform
	{
		namespace windows
		{
			namespace opengl31d
			{
				class CRenderer;
			}

			namespace opengl31r
			{
				class CRenderer;
			}

			namespace opengl45d
			{
				class CRenderer;
			}

			namespace opengl45r
			{
				class CRenderer;
			}

			class CPlatformFont :public CBasePlatformFont
			{
				friend opengl31d::CRenderer;
				friend opengl31r::CRenderer;
				friend opengl45d::CRenderer;
				friend opengl45r::CRenderer;
			private:
				IRenderer * m_pRenderer;
				PlatformHandle m_hDC;

				ITexture *m_pTexture;
			protected:
				void BeforeRelease() override;
				Char *CreateChar(const wchar_t chr) override;

				CPlatformFont(IRenderer *renderer);
				CPlatformFont(const CPlatformFont&) = delete;
				CPlatformFont(CPlatformFont&&) = delete;
				CPlatformFont &operator=(const CPlatformFont&) = delete;
				CPlatformFont &operator=(CPlatformFont&&) = delete;
			public:
				Char *getChar(const wchar_t chr) override;
				ITexture *getTexture() override; // Return texture containing all characters
			};
		}
	}
}
#endif