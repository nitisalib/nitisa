// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRenderer.h"

namespace nitisa
{
	class IFramebuffer;

	class CStoreFramebuffer final
	{
	private:
		IRenderer *m_pRenderer;
		IFramebuffer *m_pFramebuffer;
	public:
		CStoreFramebuffer(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pFramebuffer{ renderer->ActiveFramebuffer }
		{

		}

		~CStoreFramebuffer()
		{
			m_pRenderer->ActivateFramebuffer(m_pFramebuffer);
		}

		CStoreFramebuffer(const CStoreFramebuffer&) = delete;
		CStoreFramebuffer(CStoreFramebuffer&&) = delete;
		CStoreFramebuffer &operator=(const CStoreFramebuffer&) = delete;
		CStoreFramebuffer &operator=(CStoreFramebuffer&&) = delete;
	};
}