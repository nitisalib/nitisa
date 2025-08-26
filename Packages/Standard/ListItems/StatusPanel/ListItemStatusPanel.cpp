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
		CListItemStatusPanel::CListItemStatusPanel(const String &class_name) :
			CListItem(class_name, false),
			m_fWidth{ -1 }
		{

		}
	#pragma endregion

	#pragma region Getters
		float CListItemStatusPanel::getWidth()
		{
			return m_fWidth;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemStatusPanel::setWidth(const float value)
		{
			if (ntl::IsNotEqual<float>(value, m_fWidth))
			{
				m_fWidth = value;
				if (QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnSizeChange(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		bool CListItemStatusPanel::Copy(IListItem *dest)
		{
			CListItemStatusPanel *d{ cast<CListItemStatusPanel*>(dest) };
			if (d)
			{
				d->m_fWidth = m_fWidth;
				return CListItem::Copy(dest);
			}
			return false;
		}
	#pragma endregion
	}
}