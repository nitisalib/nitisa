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
		CListItemMenuService::CListItemMenuService(CListItemMenu *listitem) :
			CListItemService(listitem),
			m_pListItem{ listitem },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		float CListItemMenuService::getIconWidth()
		{
			return m_pListItem->m_fIconWidth;
		}

		float CListItemMenuService::getHotkeyWidth()
		{
			return m_pListItem->m_fHotkeyWidth;
		}

		float CListItemMenuService::getArrowWidth()
		{
			return m_pListItem->m_fArrowWidth;
		}

		Point CListItemMenuService::getDPI() const
		{
			return m_sDPI;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				float s{ (float)value.X / (float)m_sDPI.X };
				m_sDPI = value;
				m_pListItem->m_fIconWidth *= s;
				m_pListItem->m_fHotkeyWidth *= s;
				m_pListItem->m_fArrowWidth *= s;
				return true;
			}
			return false;
		}

		bool CListItemMenuService::setIconWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_pListItem->m_fIconWidth))
			{
				m_pListItem->m_fIconWidth = value;
				return true;
			}
			return false;
		}

		bool CListItemMenuService::setHotkeyWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_pListItem->m_fHotkeyWidth))
			{
				m_pListItem->m_fHotkeyWidth = value;
				return true;
			}
			return false;
		}

		bool CListItemMenuService::setArrowWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_pListItem->m_fArrowWidth))
			{
				m_pListItem->m_fArrowWidth = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Notifications
		bool CListItemMenuService::NotifyOnHotkey()
		{
			return false;
		}
	#pragma endregion
	}
}