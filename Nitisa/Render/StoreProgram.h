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
	class IProgram;

	class CStoreProgram final
	{
	private:
		IRenderer *m_pRenderer;
		IProgram *m_pProgram;
	public:
		CStoreProgram(IRenderer *renderer):
			m_pRenderer{ renderer },
			m_pProgram{ renderer->ActiveProgram }
		{

		}

		~CStoreProgram()
		{
			m_pRenderer->ActivateProgram(m_pProgram);
		}

		CStoreProgram(const CStoreProgram&) = delete;
		CStoreProgram(CStoreProgram&&) = delete;
		CStoreProgram &operator=(const CStoreProgram&) = delete;
		CStoreProgram &operator=(CStoreProgram&&) = delete;
	};
}