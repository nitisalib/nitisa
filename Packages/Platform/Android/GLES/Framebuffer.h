// This file is a part of Nitisa framework
// Copyright © 2023 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#ifdef __ANDROID__
#include "Nitisa/Core/Releasable.h"
#include "Nitisa/Interfaces/IFramebuffer.h"
#include <vector>

namespace nitisa
{
	class IRenderer;
	class IBaseTexture;

	class COpenGL;

	namespace platform
	{
		namespace android
		{
			namespace gles31d
			{
				class CRenderer;
			}

			namespace gles31r
			{
				class CRenderer;
			}

			namespace gles
			{
				class CFramebuffer :public virtual IFramebuffer, public CReleasable
				{
					friend gles31d::CRenderer;
					friend gles31r::CRenderer;
				private:
					struct ATTACHMENT
					{
						IBaseTexture *Texture;
						int Level;
					};
				private:
					COpenGL *m_pGraphics;
					IRenderer *m_pRenderer;
					std::vector<ATTACHMENT> m_aColorAttachments;
				protected:
					void BeforeRelease() override;

					CFramebuffer(COpenGL *graphics, IRenderer *renderer);
					CFramebuffer(const CFramebuffer&) = delete;
					CFramebuffer(CFramebuffer&&) = delete;
					CFramebuffer &operator=(const CFramebuffer&) = delete;
					CFramebuffer &operator=(CFramebuffer&&) = delete;

					static CFramebuffer *Create(COpenGL *graphics, IRenderer *renderer);
				public:
					// IFramebuffer getters
					int getColorAttachmentCount() const override;
					IBaseTexture *getColorAttachment(const int index) override;
					int getColorAttachmentLevel(const int index) const override;

					// IFramebuffer setters
					bool setDepthAttachment(IBaseTexture *value, const int level = 0, const bool force = false) override;
					bool setStencilAttachment(IBaseTexture *value, const int level = 0, const bool force = false) override;
					bool setDepthStencilAttachment(IBaseTexture *value, const int level = 0, const bool force = false) override;
					bool setColorAttachment(IBaseTexture *value, const int index, const int level = 0, const bool force = false) override;
				};
			}
		}
	}
}
#endif