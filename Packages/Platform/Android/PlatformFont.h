// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "../Core/BasePlatformFont.h"
#include "Application.h"

namespace nitisa
{
	class IReleasableListener;
	class IRenderer;
	class ITexture;

	namespace platform
	{
		namespace android
		{
			class CApplication;

			namespace gles31d
			{
				class CRenderer;
			}

			namespace gles31r
			{
				class CRenderer;
			}

			class CPlatformFont :public CBasePlatformFont
			{
				friend gles31d::CRenderer;
				friend gles31r::CRenderer;
			private:
				IRenderer * m_pRenderer;
				ITexture *m_pTexture;
				CApplication *m_pApplication;
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
				ITexture *getTexture() override;
			};
		}
	}
}
#endif