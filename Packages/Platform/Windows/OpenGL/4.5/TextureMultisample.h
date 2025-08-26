// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef _WIN32
#include "Nitisa/Core/BaseTexture.h"
#include "Nitisa/Core/TextureDepthStencilMode.h"
#include "Nitisa/Core/TextureFormat.h"
#include "Nitisa/Core/TextureSwizzle.h"
#include "Nitisa/Interfaces/ITextureMultisample.h"
#include "Nitisa/Math/Rect.h"

namespace nitisa
{
	class IReleasable;
	class IRenderer;

	class COpenGL;

	namespace platform
	{
		namespace windows
		{
			namespace opengl45d
			{
				class CRenderer;
			}

			namespace opengl45r
			{
				class CRenderer;
			}

			namespace opengl45
			{
				class CTextureMultisample :public virtual ITextureMultisample, public CBaseTexture
				{
					friend opengl45d::CRenderer;
					friend opengl45r::CRenderer;
				protected:
					COpenGL *m_pGraphics;
					IRenderer *m_pRenderer;

					CTextureMultisample(COpenGL *graphics, IRenderer *renderer, const int samples, const bool fixed_sample_locations);

					CTextureMultisample(const CTextureMultisample &other) = delete;
					CTextureMultisample(CTextureMultisample &&other) = delete;
					CTextureMultisample &operator=(const CTextureMultisample &other) = delete;
					CTextureMultisample &operator=(CTextureMultisample &&other) = delete;

					void UpdateParameters();
					void BeforeRelease() override;

					static CTextureMultisample *Create(COpenGL *graphics, IRenderer *renderer, const int samples, const bool fixed_sample_locations);
				public:
					bool setFormat(const TextureFormat value) override;
					bool setSize(const int width, const int height) override;
					bool setDepthStencilMode(const TextureDepthStencilMode value) override;
					bool setSwizzleR(const TextureSwizzle value) override;
					bool setSwizzleG(const TextureSwizzle value) override;
					bool setSwizzleB(const TextureSwizzle value) override;
					bool setSwizzleA(const TextureSwizzle value) override;
					bool setSwizzleRGBA(const TextureSwizzle value) override;
					bool setSamples(const int value) override;
					bool setFixedSampleLocations(const bool value) override;
				};
			}
		}
	}
}
#endif