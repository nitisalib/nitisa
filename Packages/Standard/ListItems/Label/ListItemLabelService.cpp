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
		CListItemLabelService::CListItemLabelService(CListItemLabel *listitem) :
			CListItemService(listitem),
			m_pListItem{ listitem },
			m_bDown{ false },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemLabelService::getRequiredSize()
		{
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pListItem) && getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()))
			{
				IPlatformFont *pf{ getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()) };
				PointF size{ pf->getStringSize(m_pListItem->m_sCaption, getOwner()->getFont(m_pListItem)->Distance) };
				if (m_pListItem->m_sCaption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				size.X += m_pListItem->m_sPadding.Left + m_pListItem->m_sPadding.Right;
				size.Y += m_pListItem->m_sPadding.Top + m_pListItem->m_sPadding.Bottom;
				return size;
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemLabelService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				m_pListItem->m_sPadding *= s;
				for (int i = 0; i <= (int)CListItemLabel::State::Disabled; i++)
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
		void CListItemLabelService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pListItem))
				m_pListItem->UpdateFromStyle(getOwner()->getStyle(m_pListItem));
		}

		void CListItemLabelService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pListItem->Render(matrix, block, clip);
		}
	#pragma endregion

	#pragma region Input
		bool CListItemLabelService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (!m_bDown && left && !middle && !right)
			{
				m_bDown = true;
				return true;
			}
			else
				m_bDown = false;
			return false;
		}

		bool CListItemLabelService::NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			if (m_bDown)
			{
				if (m_pListItem->OnClick)
					m_pListItem->OnClick(m_pListItem);
				m_bDown = false;
				return true;
			}
			return false;
		}

		void CListItemLabelService::NotifyOnMouseDownCancel()
		{
			m_bDown = false;
		}
	#pragma endregion
	}
}