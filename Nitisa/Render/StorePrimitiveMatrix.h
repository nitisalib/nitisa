// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Interfaces/IRenderer.h"
#include "../Math/Mat4f.h"

namespace nitisa
{
	class CStorePrimitiveMatrix final
	{
	private:
		IRenderer *m_pRenderer;
		const Mat4f *m_pMatrix;
		Mat4f m_sMatrix;
	public:
		CStorePrimitiveMatrix(IRenderer *renderer) :
			m_pRenderer{ renderer },
			m_pMatrix{ renderer->ActivePrimitiveMatrix }
		{
			if (m_pMatrix)
				m_sMatrix = *m_pMatrix;
		}

		~CStorePrimitiveMatrix()
		{
			m_pRenderer->ActivatePrimitiveMatrix(m_pMatrix ? &m_sMatrix : nullptr);
		}

		CStorePrimitiveMatrix(const CStorePrimitiveMatrix&) = delete;
		CStorePrimitiveMatrix(CStorePrimitiveMatrix&&) = delete;
		CStorePrimitiveMatrix &operator=(const CStorePrimitiveMatrix&) = delete;
		CStorePrimitiveMatrix &operator=(CStorePrimitiveMatrix&&) = delete;
	};
}