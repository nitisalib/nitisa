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
		CListItemMenuSeparatorService::CListItemMenuSeparatorService(CListItemMenuSeparator *item) :
			CListItemMenuService{ item },
			m_pItem{ item }
		{

		}
	#pragma endregion

	#pragma region Getters
		PointF CListItemMenuSeparatorService::getRequiredSize()
		{
			return PointF{ 1, m_pItem->m_fHeight };
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMenuSeparatorService::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			if (CListItemMenuService::setDPI(value))
			{
				m_pItem->m_fHeight *= (float)value.Y / (float)old.Y;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CListItemMenuSeparatorService::UpdateFromStyle()
		{
			if (getOwner() && getOwner()->getStyle(m_pItem))
				m_pItem->UpdateFromStyle(getOwner()->getStyle(m_pItem));
		}

		void CListItemMenuSeparatorService::Render(const Mat4f &matrix, const Block *block, const bool last_pass, ITexture **clip)
		{
			m_pItem->Render(matrix, block);
		}
	#pragma endregion
	}
}