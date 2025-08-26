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
		CListItemColorService::CListItemColorService(CListItemColor *listitem) :
			CListItemService(listitem),
			m_pListItem{ listitem },
			m_bDown{ false },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemColorService::getRequiredSize()
		{
			if (getOwner() && getOwner()->getRenderer() && getOwner()->getFont(m_pListItem) && getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()))
			{
				IPlatformFont *pf{ getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()) };
				String caption{ Application->Translate->t(TranslateCategoryColors, m_pListItem->m_sCaption) };
				PointF size{ pf->getStringSize(caption, getOwner()->getFont(m_pListItem)->Distance) };
				if (caption.empty())
					size.Y = pf->getStringSize(L"Wy", 0).Y;
				size.Y += m_pListItem->m_sPadding.Top + m_pListItem->m_sPadding.Bottom;
				size.X += m_pListItem->m_sPadding.Left + m_pListItem->m_sPadding.Right + size.Y;
				return size;
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemColorService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				m_pListItem->m_sPadding *= s;
				for (int i = 0; i <= (int)CListItemColor::State::Disabled; i++)
				{
					m_pListItem->m_aColorBorderWidth[i] *= s;
					m_pListItem->m_aColorBorderRadius[i] *= avg;
					m_pListItem->m_aColorPadding[i] *= s;
					m_pListItem->m_aCaptionShadowRadius[i] = ntl::Round<int>((float)m_pListItem->m_aCaptionShadowRadius[i] * avg);
					m_pListItem->m_aCaptionShadowShift[i] *= s;
					m_pListItem->m_aBorderWidth[i] *= s;
					m_pListItem->m_aBorderRadius[i] *= avg;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemColorService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pListItem))
				m_pListItem->UpdateFromStyle(getOwner()->getStyle(m_pListItem));
		}

		void CListItemColorService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pListItem->Render(matrix, block, clip);
		}
	#pragma endregion

	#pragma region Input
		bool CListItemColorService::NotifyOnMouseDown(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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

		bool CListItemColorService::NotifyOnMouseUp(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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

		void CListItemColorService::NotifyOnMouseDownCancel()
		{
			m_bDown = false;
		}
	#pragma endregion
	}
}