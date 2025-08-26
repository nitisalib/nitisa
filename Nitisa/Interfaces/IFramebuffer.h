// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Aliases.h"
#include "IReleasable.h"

namespace nitisa
{
	class IBaseTexture;

	class IFramebuffer :public virtual IReleasable
	{
	protected:
		IFramebuffer() = default;
		~IFramebuffer() = default;
		IFramebuffer(const IFramebuffer &other) = delete;
		IFramebuffer(IFramebuffer &&other) = delete;
		IFramebuffer &operator=(const IFramebuffer &other) = delete;
		IFramebuffer &operator=(IFramebuffer &&other) = delete;
	protected:
		PlatformHandle m_hHandle;
		IBaseTexture *m_pDepthAttachment;
		int m_iDepthAttachmentLevel;
		IBaseTexture *m_pStencilAttachment;
		int m_iStencilAttachmentLevel;
	public:
		PlatformHandle const &Handle{ m_hHandle }; // Platform-dependent handle
		IBaseTexture* const &DepthAttachment{ m_pDepthAttachment }; // Texture attached as depth attachment
		int &DepthAttachmentLevel{ m_iDepthAttachmentLevel }; // Used depth attachment texture level
		IBaseTexture* const &StencilAttachment{ m_pStencilAttachment }; // Texture attached as stencil attachment
		int &StencilAttachmentLevel{ m_iStencilAttachmentLevel }; // Used stencil attachment texture level

		virtual int getColorAttachmentCount() const = 0; // Return count of set color attachments
		virtual IBaseTexture *getColorAttachment(const int index) = 0; // Return texture attached as color attachment by index
		virtual int getColorAttachmentLevel(const int index) const = 0; // Return used color attachment texture level by index

		virtual bool setDepthAttachment(IBaseTexture *value, const int level = 0, const bool force = false) = 0; // Attach texture as depth attachment. Use nullptr to clear attachment
		virtual bool setStencilAttachment(IBaseTexture *value, const int level = 0, const bool force = false) = 0; // Attach texture as stencil attachment. Use nullptr to clear attachment
		virtual bool setDepthStencilAttachment(IBaseTexture *value, const int level = 0, const bool force = false) = 0; // Attach texture as both depth and stencil attachment. Use nullptr to clear attachment
		virtual bool setColorAttachment(IBaseTexture *value, const int index, const int level = 0, const bool force = false) = 0; // Attach texture as color attachment. Use nullptr to clear attachment
	};
}