// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRenderer.h"
#include "../Math/CubicBezierSplineLimits.h"

namespace nitisa
{
	class CStoreSplineLimits final
	{
	private:
		IRenderer *m_pRenderer;
		const CubicBezierSplineLimits *m_pLimits;
		CubicBezierSplineLimits m_sLimits;
	public:
		CStoreSplineLimits(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pLimits{ renderer->ActiveSplineLimits }
		{
			if (m_pLimits)
				m_sLimits = *m_pLimits;
		}

		~CStoreSplineLimits()
		{
			m_pRenderer->ActivateSplineLimits(m_pLimits ? &m_sLimits : nullptr);
		}

		CStoreSplineLimits(const CStoreSplineLimits&) = delete;
		CStoreSplineLimits(CStoreSplineLimits&&) = delete;
		CStoreSplineLimits &operator=(const CStoreSplineLimits&) = delete;
		CStoreSplineLimits &operator=(CStoreSplineLimits&&) = delete;
	};
}