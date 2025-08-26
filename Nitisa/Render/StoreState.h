// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Bitmask.h"
#include "../Interfaces/IRenderer.h"
#include "../Math/Block.h"
#include "../Math/CubicBezierSplineLimits.h"
#include "../Math/Mat4f.h"

namespace nitisa
{
	class IBaseTexture;
	class IFramebuffer;
	class IProgram;
	class ITexture;
	class IVertexArray;

	class CStoreState final
	{
	private:
		IRenderer *m_pRenderer;
		IProgram *m_pProgram;
		IFramebuffer *m_pFramebuffer;
		IVertexArray *m_pVertexArray;
		IBaseTexture *m_pTarget;
		ITexture *m_pMask;
		const Block *m_pBlock;
		Block m_sBlock;
		const Bitmask *m_pBitmask;
		Bitmask m_sBitmask;
		const CubicBezierSplineLimits *m_pLimits;
		CubicBezierSplineLimits m_sLimits;
		const Mat4f *m_pMatrix;
		Mat4f m_sMatrix;
	public:
		CStoreState(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pProgram{ renderer->ActiveProgram },
			m_pFramebuffer{ renderer->ActiveFramebuffer },
			m_pVertexArray{ renderer->ActiveVertexArray },
			m_pTarget{ renderer->ActiveTarget },
			m_pMask{ renderer->ActiveMask },
			m_pBlock{ renderer->ActiveBlock },
			m_pBitmask{ renderer->ActiveBitmask },
			m_pLimits{ renderer->ActiveSplineLimits },
			m_pMatrix{ renderer->ActivePrimitiveMatrix }
		{
			if (m_pBlock)
				m_sBlock = *m_pBlock;
			if (m_pBitmask)
				m_sBitmask = *m_pBitmask;
			if (m_pLimits)
				m_sLimits = *m_pLimits;
			if (m_pMatrix)
				m_sMatrix = *m_pMatrix;
		}

		~CStoreState()
		{
			m_pRenderer
				->ActivateProgram(m_pProgram)
				->ActivateFramebuffer(m_pFramebuffer)
				->ActivateVertexArray(m_pVertexArray)
				->ActivateTarget(m_pTarget)
				->ActivateMask(m_pMask)
				->ActivateBlock(m_pBlock ? &m_sBlock : nullptr)
				->ActivateBitmask(m_pBitmask ? &m_sBitmask : nullptr)
				->ActivateSplineLimits(m_pLimits ? &m_sLimits : nullptr)
				->ActivatePrimitiveMatrix(m_pMatrix ? &m_sMatrix : nullptr);
		}

		CStoreState(const CStoreState&) = delete;
		CStoreState(CStoreState&&) = delete;
		CStoreState &operator=(const CStoreState&) = delete;
		CStoreState &operator=(CStoreState&&) = delete;
	};
}