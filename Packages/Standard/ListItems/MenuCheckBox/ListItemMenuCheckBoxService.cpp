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
		CListItemMenuCheckBoxService::CListItemMenuCheckBoxService(CListItemMenuCheckBox *item) :
			CListItemMenuService{ item },
			m_pItem{ item },
			m_bMouseDown{ false }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemMenuCheckBoxService::getRequiredSize()
		{
			PointF result{ 0, 0 };
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pItem) && getOwner()->getFont(m_pItem)->getPlatformFont(getOwner()->getRenderer()))
			{
				result = getOwner()->getFont(m_pItem)->getPlatformFont(getOwner()->getRenderer())->getStringSize(m_pItem->m_sCaption, getOwner()->getFont(m_pItem)->Distance);
				result.X += getIconWidth() + getHotkeyWidth() + getArrowWidth() + m_pItem->m_sCaptionPadding.Left + m_pItem->m_sCaptionPadding.Right;
				result.Y += ntl::Max<float>(m_pItem->m_sCaptionPadding.Top, m_pItem->m_sHotkeyPadding.Top) + ntl::Max<float>(m_pItem->m_sCaptionPadding.Bottom, m_pItem->m_sHotkeyPadding.Bottom);
			}
			return result;
		}

		float CListItemMenuCheckBoxService::getIconWidth()
		{
			return ntl::Max<float>(m_pItem->m_fIconWidth, m_pItem->m_sIconPadding.Left + m_pItem->m_sIconPadding.Right);
		}

		float CListItemMenuCheckBoxService::getHotkeyWidth()
		{
			float result{ m_pItem->m_sHotkeyPadding.Left + m_pItem->m_sHotkeyPadding.Top };
			if (m_pItem->getHotkeyCount() > 0 && getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pItem) && getOwner()->getFont(m_pItem)->getPlatformFont(getOwner()->getRenderer()))
				result += getOwner()->getFont(m_pItem)->getPlatformFont(getOwner()->getRenderer())->getStringSize(m_pItem->getHotkeys(), getOwner()->getFont(m_pItem)->Distance).X;
			return ntl::Max<float>(result, m_pItem->m_fHotkeyWidth);
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuCheckBoxService::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CListItemMenuService::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_pItem->m_sIconPadding *= s;
				m_pItem->m_sCaptionPadding *= s;
				m_pItem->m_sHotkeyPadding *= s;
				for (int i = 0; i <= (int)CListItemMenuCheckBox::State::Disabled; i++)
				{
					m_pItem->m_aShadowRadius[i] = ntl::Round<int>((float)m_pItem->m_aShadowRadius[i] * avg);
					m_pItem->m_aShadowShift[i] *= s;
					m_pItem->m_aBorderWidth[i] *= s;
					m_pItem->m_aBorderRadius[i] *= avg;
				}
				return true;
			}
			return false;
		}

		bool CListItemMenuCheckBoxService::setIconWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_pItem->m_fIconWidth))
			{
				m_pItem->m_fIconWidth = value;
				return true;
			}
			return false;
		}

		bool CListItemMenuCheckBoxService::setHotkeyWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_pItem->m_fHotkeyWidth))
			{
				m_pItem->m_fHotkeyWidth = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemMenuCheckBoxService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pItem))
				m_pItem->UpdateFromStyle(getOwner()->getStyle(m_pItem));
		}

		void CListItemMenuCheckBoxService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pItem->Render(matrix, block, clip);
		}
	#pragma endregion

	#pragma region Notifications
		bool CListItemMenuCheckBoxService::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift)
		{
			if (key == Key::Return || key == Key::Separator)
			{
				m_pItem->m_bChecked = !m_pItem->m_bChecked;
				if (m_pItem->OnChange)
					m_pItem->OnChange(m_pItem);
				return true;
			}
			if (key == Key::Space)
				m_pItem->setChecked(!m_pItem->m_bChecked);
			return false;
		}

		bool CListItemMenuCheckBoxService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			m_bMouseDown = (left && !middle && !right) || (!left && !middle && right);
			return false;
		}

		void CListItemMenuCheckBoxService::NotifyOnMouseDownCancel()
		{
			m_bMouseDown = false;
		}

		bool CListItemMenuCheckBoxService::NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bMouseDown && ((left && !middle && !right) || (!left && !middle && right)))
			{
				m_pItem->m_bChecked = !m_pItem->m_bChecked;
				if (m_pItem->OnChange)
					m_pItem->OnChange(m_pItem);
				m_bMouseDown = false;
				return true;
			}
			else
				m_bMouseDown = false;
			return false;
		}
	
		bool CListItemMenuCheckBoxService::NotifyOnHotkey()
		{
			m_pItem->m_bChecked = !m_pItem->m_bChecked;
			if (m_pItem->OnChange)
				m_pItem->OnChange(m_pItem);
			return true;
		}
	#pragma endregion
	}
}