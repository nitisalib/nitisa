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
	namespace standard
	{
	#pragma region Constructor & destructor
		CValueListEditorService::CValueListEditorService(CValueListEditor *control) :
			CCustomStringGridService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CValueListEditorService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::Separator) };
			Application->Keyboard->getControlKeys(ctrl, alt, shift);
			if (
				(m.Key == Key::Down || (m.Key == Key::Numpad2 && !numlock)) && !ctrl && !alt && !shift && // Down key may require new row adding
				m_pControl->m_bKeysEditable && m_pControl->m_bKeysAddable && !m_pControl->isKeyColumnFixed() && // Setting allow new row adding
				m_pControl->getActiveCell().Y == m_pControl->getRows() - 1) // Current active cell is in last row
			{
				// New row can be added is current active one has unempty key or unempty key will be set after defocusing the cell(key) being edited
				Point active{ m_pControl->getActiveCell() };
				String key{ m_pControl->isCellFocused(0, active.Y) ? m_pControl->getTextInput()->getText() : m_pControl->getCell(0, active.Y) };
				if (!key.empty() && (!m_pControl->m_bKeysUnique || m_pControl->isKeyUnique(key, active.Y)))
				{
					m_pControl->setRows(m_pControl->getRows() + 1);
					m_pControl->setCellEditable(0, m_pControl->getRows() - 1, true);
				}
			}
			CCustomStringGridService::NotifyOnKeyDown(m, processed);
		}
	#pragma endregion

	#pragma region Cell status change notifications
		void CValueListEditorService::NotifyOnActivateCell(const int column, const int row, IListItem *item)
		{
			CCustomStringGridService::NotifyOnActivateCell(column, row, item);
			if (m_pControl->m_bKeysDeletable && m_pControl->m_bKeysEditable && !m_pControl->isKeyColumnFixed())
			{
				m_pControl->LockUpdate();
				int y{ m_pControl->getRows() - 1 };
				while (y > 0 && m_pControl->getRows() >= 2)
				{
					if (y != row && m_pControl->getCell(0, y).empty())
						m_pControl->DeleteRowInternal(y);
					y--;
				}
				m_pControl->UnlockUpdate();
			}
		}

		void CValueListEditorService::NotifyOnCellChange(const int column, const int row, const String &value, bool &allowed)
		{
			if (column == 0 && m_pControl->m_bKeysUnique && !m_pControl->isKeyUnique(value, row))
				allowed = false;
		}
	#pragma endregion
	}
}