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
	namespace standard
	{
	#pragma region Constructor & destructor
		CListItemMenu::CListItemMenu(const String &class_name, const bool accept_items) :
			CListItem(class_name, accept_items),
			m_fIconWidth{ 0 },
			m_fHotkeyWidth{ 0 },
			m_fArrowWidth{ 0 },
			m_pService{ nullptr },
			m_bDestroying{ false }
		{

		}

		CListItemMenu::~CListItemMenu()
		{
			m_bDestroying = true;
			DeleteHotkeys();
			if (m_pService)
				m_pService->Release();
		}
	#pragma endregion

	#pragma region Getters
		int CListItemMenu::getHotkeyCount()
		{
			return (int)m_aHotkeys.size();
		}

		Hotkey CListItemMenu::getHotkey(const int index)
		{
			if (index >= 0 && index < (int)m_aHotkeys.size())
				return m_aHotkeys[(size_t)index];
			return Hotkey{ Key::Unknown, false, false, false, false };
		}

		IListItemService *CListItemMenu::QueryService()
		{
			if (!m_pService)
				m_pService = new CListItemMenuService(this);
			return m_pService;
		}

		String CListItemMenu::getHotkeys()
		{
			String result;
			if (QueryService()->getOwner() && QueryService()->getOwner()->getControl())
				for (int i = 0; i < getHotkeyCount(); i++)
				{
					if (i > 0)
						result += L", ";
					result += CTranslate::Hotkey(getHotkey(i));
				}
			return result;
		}
	#pragma endregion

	#pragma region Hotkeys
		bool CListItemMenu::AddHotkey(const Key key, const bool ctrl, const bool alt, const bool shift, const bool down)
		{
			if (key != Key::Unknown)
			{
				for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
					if (pos->Key == key && pos->Ctrl == ctrl && pos->Alt == alt && pos->Shift == shift && pos->Down == down)
						return false;
				m_aHotkeys.push_back({ key, ctrl, alt, shift, down });
				IListItemMenuOwner *owner{ cast<IListItemMenuOwner*>(QueryService()->getOwner()) };
				if (owner)
					owner->NotifyOnAddHotkey(this, m_aHotkeys[m_aHotkeys.size() - 1]);
				return true;
			}
			return false;
		}

		bool CListItemMenu::DeleteHotkey(const int index)
		{
			if (index >= 0 && index < (int)m_aHotkeys.size())
			{
				IListItemMenuOwner *owner{ cast<IListItemMenuOwner*>(QueryService()->getOwner()) };
				if (owner)
					owner->NotifyOnDeleteHotkey(this, m_aHotkeys[m_aHotkeys.size() - 1]);
				m_aHotkeys.erase(m_aHotkeys.begin() + index);
				return true;
			}
			return false;
		}

		bool CListItemMenu::DeleteHotkeys()
		{
			if (m_aHotkeys.size() > 0)
			{
				if (!m_bDestroying)
				{
					IListItemMenuOwner *owner{ cast<IListItemMenuOwner*>(QueryService()->getOwner()) };
					if (owner)
						for (auto pos = m_aHotkeys.begin(); pos != m_aHotkeys.end(); pos++)
							owner->NotifyOnDeleteHotkey(this, *pos);
				}
				m_aHotkeys.clear();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IListItem *CListItemMenu::Clone()
		{
			CListItemMenu *result{ new CListItemMenu(m_sClassName, isAcceptItems()) };
			Copy(result);
			return result;
		}

		bool CListItemMenu::Copy(IListItem *dest)
		{
			CListItemMenu *d{ cast<CListItemMenu*>(dest) };
			if (d)
			{
				d->m_fIconWidth = m_fIconWidth;
				d->m_fHotkeyWidth = m_fHotkeyWidth;
				d->m_fArrowWidth = m_fArrowWidth;
				d->m_aHotkeys = m_aHotkeys;
				return CListItem::Copy(dest);
			}
			return false;
		}
	#pragma endregion
	}
}