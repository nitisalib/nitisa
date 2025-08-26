// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace ide
	{
	#pragma region Constructor & destructor
		CHierarchyEditorService::CHierarchyEditorService(CHierarchyEditor *editor) :
			CCustomTreeViewService(editor),
			m_pEditor{ editor }
		{

		}
	#pragma endregion

	#pragma region Component notifications
		void CHierarchyEditorService::NotifyOnComponentDetach(IComponent *component)
		{
			if (m_pEditor->m_pImageList == component)
			{
				m_pEditor->m_pImageList = nullptr;
				m_pEditor->LockUpdate();
				m_pEditor->UnlockUpdate();
			}
		}

		void CHierarchyEditorService::NotifyOnComponentChange(IComponent *component)
		{
			if (m_pEditor->m_pImageList == component)
			{
				m_pEditor->LockUpdate();
				m_pEditor->UnlockUpdate();
			}
		}
	#pragma endregion
	}
}