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
		CListItemIconService::CListItemIconService(CListItemIcon *listitem) :
			CListItemService(listitem),
			m_pListItem{ listitem },
			m_bMouseDown{ false },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemIconService::getRequiredSize()
		{
			PointF result{ 0, 0 };
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pListItem) && getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()))
			{
				result = getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer())->getStringSize(m_pListItem->m_sCaption, getOwner()->getFont(m_pListItem)->Distance);
				PointF icon_size{ 0, 0 };
				IListItemIconOwner *owner{ cast<IListItemIconOwner*>(getOwner()) };
				RectF part;
				if (owner && owner->getIcon(m_pListItem, part))
					icon_size = PointF{ part.width(), part.height() };
				result.X += icon_size.X + m_pListItem->m_fIconPadding + m_pListItem->m_sCaptionPadding.Left + m_pListItem->m_sCaptionPadding.Right;
				result.Y = ntl::Max<float>(result.Y + m_pListItem->m_sCaptionPadding.Top + m_pListItem->m_sCaptionPadding.Bottom, icon_size.Y);
				
			}
			return result;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemIconService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				m_pListItem->m_fIconPadding *= s.X;
				m_pListItem->m_sCaptionPadding *= s;
				for (int i = 0; i <= (int)CListItemIcon::State::Disabled; i++)
				{
					m_pListItem->m_aShadowRadius[i] = ntl::Round<int>((float)m_pListItem->m_aShadowRadius[i] * avg);
					m_pListItem->m_aShadowShift[i] *= s;
					m_pListItem->m_aBorderWidth[i] *= s;
					m_pListItem->m_aBorderRadius[i] *= avg;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemIconService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pListItem))
				m_pListItem->UpdateFromStyle(getOwner()->getStyle(m_pListItem));
		}

		void CListItemIconService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pListItem->Render(matrix, block, clip);
		}
	#pragma endregion

	#pragma region Input
		bool CListItemIconService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			m_bMouseDown = left && !middle && !right;
			return false;
		}

		void CListItemIconService::NotifyOnMouseDownCancel()
		{
			m_bMouseDown = false;
		}

		bool CListItemIconService::NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bMouseDown && left && !middle && !right)
			{
				if (m_pListItem->OnClick)
					m_pListItem->OnClick(m_pListItem);
				m_bMouseDown = false;
				return true;
			}
			m_bMouseDown = false;
			return false;
		}

		bool CListItemIconService::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift)
		{
			if (key == Key::Return || key == Key::Separator)
			{
				if (m_pListItem->OnClick)
					m_pListItem->OnClick(m_pListItem);
				return true;
			}
			return false;
		}
	#pragma endregion
	}
}