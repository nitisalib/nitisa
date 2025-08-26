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
	class IVertexArray;

	class CStoreVertexArray final
	{
	private:
		IRenderer *m_pRenderer;
		IVertexArray *m_pVertexArray;
	public:
		CStoreVertexArray(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pVertexArray{ renderer->ActiveVertexArray }
		{

		}

		~CStoreVertexArray()
		{
			m_pRenderer->ActivateVertexArray(m_pVertexArray);
		}

		CStoreVertexArray(const CStoreVertexArray&) = delete;
		CStoreVertexArray(CStoreVertexArray&&) = delete;
		CStoreVertexArray &operator=(const CStoreVertexArray&) = delete;
		CStoreVertexArray &operator=(CStoreVertexArray&&) = delete;
	};
}