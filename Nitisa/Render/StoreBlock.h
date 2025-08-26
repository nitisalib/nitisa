// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRenderer.h"
#include "../Math/Block.h"

namespace nitisa
{
	class CStoreBlock final
	{
	private:
		IRenderer *m_pRenderer;
		const Block *m_pBlock;
		Block m_sBlock;
	public:
		CStoreBlock(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pBlock{ renderer->ActiveBlock }
		{
			if (m_pBlock)
				m_sBlock = *m_pBlock;
		}

		~CStoreBlock()
		{
			m_pRenderer->ActivateBlock(m_pBlock ? &m_sBlock : nullptr);
		}

		CStoreBlock(const CStoreBlock&) = delete;
		CStoreBlock(CStoreBlock&&) = delete;
		CStoreBlock &operator=(const CStoreBlock&) = delete;
		CStoreBlock &operator=(CStoreBlock&&) = delete;
	};
}