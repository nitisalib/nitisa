// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace fb
	{
		CApplication::CApplication() :
			nitisa::CApplication()
		{
		#if defined(VS_INTEGRATION) || defined(USE_DIALOGBOXES)
			m_bDialogBoxes = true;
		#endif
		#ifdef VS_INTEGRATION
			m_bGlobal = false;
		#endif
		}

		CApplication::~CApplication()
		{
			if (m_pEditor)
				m_pEditor->Release();
		}

		void CApplication::setEditor(IEditor *editor)
		{
			m_pEditor = editor;
		}
	}
}