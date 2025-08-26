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
		CListItemTreeViewLabelService::CListItemTreeViewLabelService(CListItemTreeViewLabel *listitem) :
			CListItemService(listitem),
			m_pListItem{ listitem },
			m_sDPI{ DesignDPI }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemTreeViewLabelService::getRequiredSize()
		{
			if (getOwner() && getOwner()->getFont(m_pListItem) && getOwner()->getRenderer() && getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()))
			{
				CListItemTreeViewLabel::State state{ m_pListItem->getState() };
				IPlatformFont *pf{ getOwner()->getFont(m_pListItem)->getPlatformFont(getOwner()->getRenderer()) };
				PointF size{ m_pListItem->m_sCaption.empty() ? pf->getStringSize(L"Wy", getOwner()->getFont(m_pListItem)->Distance) : pf->getStringSize(m_pListItem->m_sCaption, getOwner()->getFont(m_pListItem)->Distance) };
				float height{ size.Y + m_pListItem->m_aPadding[(int)state].Top + m_pListItem->m_aPadding[(int)state].Bottom };
				float width{ size.X + m_pListItem->m_aPadding[(int)state].Left + m_pListItem->m_aPadding[(int)state].Right };
				IListItemOwnerTreeViewLabel *owner{ cast<IListItemOwnerTreeViewLabel*>(getOwner()) };
				if (owner && owner->getImageList())
					width += height;
				return { width, height };
			}
			return PointF{ 0, 0 };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemTreeViewLabelService::setDPI(const Point &value)
		{
			if (value.X > 0 && value.Y > 0 && value != m_sDPI)
			{
				PointF s{ (float)value.X / (float)m_sDPI.X, (float)value.Y / (float)m_sDPI.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sDPI = value;
				for (int i = 0; i <= (int)CListItemTreeViewLabel::State::Disabled; i++)
				{
					m_pListItem->m_aBorderWidth[i] *= s;
					m_pListItem->m_aBorderRadius[i] *= avg;
					m_pListItem->m_aPadding[i] *= s;
					m_pListItem->m_aIconPadding[i] *= s;
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemTreeViewLabelService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pListItem))
				m_pListItem->UpdateFromStyle(getOwner()->getStyle(m_pListItem));
		}

		void CListItemTreeViewLabelService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			if (ntl::IsGreater<float>(m_pListItem->getSize().X, 0) && ntl::IsGreater<float>(m_pListItem->getSize().Y, 0) && getOwner() && getOwner()->getRenderer())
				m_pListItem->Render(matrix, block, clip);
		}
	#pragma endregion
	}
}