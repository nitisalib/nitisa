// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "../Core/TextureDepthStencilMode.h"
#include "../Core/TextureFormat.h"
#include "../Core/TextureSwizzle.h"
#include "../Math/Rect.h"
#include "../Math/RectF.h"
#include "IBaseTexture.h"

namespace nitisa
{
	class ITextureMultisample : public virtual IBaseTexture
	{
	protected:
		ITextureMultisample() = default;
		~ITextureMultisample() = default;
		ITextureMultisample(const ITextureMultisample &other) = delete;
		ITextureMultisample(ITextureMultisample &&other) = delete;
		ITextureMultisample &operator=(const ITextureMultisample &other) = delete;
		ITextureMultisample &operator=(ITextureMultisample &&other) = delete;
	protected:
		TextureDepthStencilMode m_eDepthStencilMode;
		TextureSwizzle m_eSwizzleR;
		TextureSwizzle m_eSwizzleG;
		TextureSwizzle m_eSwizzleB;
		TextureSwizzle m_eSwizzleA;
		int m_iSamples;
		bool m_bFixedSampleLocations;
	public:
		TextureDepthStencilMode const &DepthStencilMode{ m_eDepthStencilMode };
		TextureSwizzle const &SwizzleR{ m_eSwizzleR };
		TextureSwizzle const &SwizzleG{ m_eSwizzleG };
		TextureSwizzle const &SwizzleB{ m_eSwizzleB };
		TextureSwizzle const &SwizzleA{ m_eSwizzleA };
		int const &Samples{ m_iSamples };
		bool const &FixedSampleLocations{ m_bFixedSampleLocations };

		virtual bool setDepthStencilMode(const TextureDepthStencilMode value) = 0;
		virtual bool setSwizzleR(const TextureSwizzle value) = 0;
		virtual bool setSwizzleG(const TextureSwizzle value) = 0;
		virtual bool setSwizzleB(const TextureSwizzle value) = 0;
		virtual bool setSwizzleA(const TextureSwizzle value) = 0;
		virtual bool setSwizzleRGBA(const TextureSwizzle value) = 0;
		virtual bool setSamples(const int value) = 0;
		virtual bool setFixedSampleLocations(const bool value) = 0;
	};
}