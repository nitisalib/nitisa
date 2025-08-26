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
	class ITexture;

	class CStoreMask final
	{
	private:
		IRenderer *m_pRenderer;
		ITexture *m_pMask;
	public:
		CStoreMask(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pMask{ renderer->ActiveMask }
		{

		}

		~CStoreMask()
		{
			m_pRenderer->ActivateMask(m_pMask);
		}

		CStoreMask(const CStoreMask&) = delete;
		CStoreMask(CStoreMask&&) = delete;
		CStoreMask &operator=(const CStoreMask&) = delete;
		CStoreMask &operator=(CStoreMask&&) = delete;
	};
}