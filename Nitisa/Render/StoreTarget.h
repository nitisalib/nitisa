// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRenderer.h"

namespace nitisa
{
	class IBaseTexture;

	class CStoreTarget final
	{
	private:
		IRenderer *m_pRenderer;
		IBaseTexture *m_pTarget;
	public:
		CStoreTarget(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pTarget{ renderer->ActiveTarget }
		{

		}

		~CStoreTarget()
		{
			m_pRenderer->ActivateTarget(m_pTarget);
		}

		CStoreTarget(const CStoreTarget&) = delete;
		CStoreTarget(CStoreTarget&&) = delete;
		CStoreTarget &operator=(const CStoreTarget&) = delete;
		CStoreTarget &operator=(CStoreTarget&&) = delete;
	};
}