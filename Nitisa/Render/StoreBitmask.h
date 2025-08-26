// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Bitmask.h"
#include "../Interfaces/IRenderer.h"

namespace nitisa
{
	class CStoreBitmask final
	{
	private:
		IRenderer *m_pRenderer;
		const Bitmask *m_pBitmask;
		Bitmask m_sBitmask;
	public:
		CStoreBitmask(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pBitmask{ renderer->ActiveBitmask }
		{
			if (m_pBitmask)
				m_sBitmask = *m_pBitmask;
		}

		~CStoreBitmask()
		{
			m_pRenderer->ActivateBitmask(m_pBitmask ? &m_sBitmask : nullptr);
		}

		CStoreBitmask(const CStoreBitmask&) = delete;
		CStoreBitmask(CStoreBitmask&&) = delete;
		CStoreBitmask &operator=(const CStoreBitmask&) = delete;
		CStoreBitmask &operator=(CStoreBitmask&&) = delete;
	};
}