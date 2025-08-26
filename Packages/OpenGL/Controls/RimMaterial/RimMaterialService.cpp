// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace opengl
	{
	#pragma region Constructor & destructor
		CRimMaterialService::CRimMaterialService(CRimMaterial *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region State change notifications
		void CRimMaterialService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pProgram)
			{
				m_pControl->m_pProgram->Release();
				m_pControl->m_pProgram = nullptr;
				m_pControl->m_bProgramValid = false;
			}
			m_pControl->m_pTexture = nullptr;
		}
	#pragma endregion
	}
}