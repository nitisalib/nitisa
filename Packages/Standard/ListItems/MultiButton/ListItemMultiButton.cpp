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
		CListItemMultiButton::CListItemMultiButton():
			CListItem(L"ListItemMultiButton", false),
			m_iImageIndex{ -1 },
			m_iImageIndexHovered{ -1 },
			m_iImageIndexFocused{ -1 },
			m_iImageIndexFocusedHovered{ -1 },
			m_iImageIndexDown{ -1 },
			m_iImageIndexDownHovered{ -1 },
			m_iImageIndexDownFocused{ -1 },
			m_iImageIndexDownFocusedHovered{ -1 },
			m_iImageIndexActive{ -1 },
			m_iImageIndexActiveHovered{ -1 },
			m_iImageIndexInactive{ -1 },
			m_iImageIndexInactiveHovered{ -1 },
			m_iImageIndexDisabled{ -1 }
		{

		}

		CListItemMultiButton::CListItemMultiButton(const String &caption) :
			CListItemMultiButton()
		{
			m_sCaption = caption;
		}
	#pragma endregion

	#pragma region IListItemCaption getters
		String CListItemMultiButton::getCaption()
		{
			return m_sCaption;
		}
	#pragma endregion

	#pragma region IListItemCaption setters
		bool CListItemMultiButton::setCaption(const String &value)
		{
			if (value != m_sCaption)
			{
				m_sCaption = value;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IListItemMultiButton getters
		int CListItemMultiButton::getImageIndex() const
		{
			return m_iImageIndex;
		}
	#pragma endregion

	#pragma region IListItemMultiButton setters
		bool CListItemMultiButton::setImageIndex(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			bool changed{ false };
			if (v != m_iImageIndex)
			{
				m_iImageIndex = v;
				changed = true;
			}
			if (v != m_iImageIndexHovered)
			{
				m_iImageIndexHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexFocused)
			{
				m_iImageIndexFocused = v;
				changed = true;
			}
			if (v != m_iImageIndexFocusedHovered)
			{
				m_iImageIndexFocusedHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexDown)
			{
				m_iImageIndexDown = v;
				changed = true;
			}
			if (v != m_iImageIndexDownHovered)
			{
				m_iImageIndexDownHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexDownFocused)
			{
				m_iImageIndexDownFocused = v;
				changed = true;
			}
			if (v != m_iImageIndexDownFocusedHovered)
			{
				m_iImageIndexDownFocusedHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexActive)
			{
				m_iImageIndexActive = v;
				changed = true;
			}
			if (v != m_iImageIndexActiveHovered)
			{
				m_iImageIndexActiveHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexInactive)
			{
				m_iImageIndexInactive = v;
				changed = true;
			}
			if (v != m_iImageIndexInactiveHovered)
			{
				m_iImageIndexInactiveHovered = v;
				changed = true;
			}
			if (v != m_iImageIndexDisabled)
			{
				m_iImageIndexDisabled = v;
				changed = true;
			}
			if (changed)
			{
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		int CListItemMultiButton::getImageIndexNormal() const
		{
			return m_iImageIndex;
		}

		int CListItemMultiButton::getImageIndexHovered() const
		{
			return m_iImageIndexHovered;
		}

		int CListItemMultiButton::getImageIndexFocused() const
		{
			return m_iImageIndexFocused;
		}

		int CListItemMultiButton::getImageIndexFocusedHovered() const
		{
			return m_iImageIndexFocusedHovered;
		}

		int CListItemMultiButton::getImageIndexDown() const
		{
			return m_iImageIndexDown;
		}

		int CListItemMultiButton::getImageIndexDownHovered() const
		{
			return m_iImageIndexDownHovered;
		}

		int CListItemMultiButton::getImageIndexDownFocused() const
		{
			return m_iImageIndexDownFocused;
		}

		int CListItemMultiButton::getImageIndexDownFocusedHovered() const
		{
			return m_iImageIndexDownFocusedHovered;
		}

		int CListItemMultiButton::getImageIndexActive() const
		{
			return m_iImageIndexActive;
		}

		int CListItemMultiButton::getImageIndexActiveHovered() const
		{
			return m_iImageIndexActiveHovered;
		}

		int CListItemMultiButton::getImageIndexInactive() const
		{
			return m_iImageIndexInactive;
		}

		int CListItemMultiButton::getImageIndexInactiveHovered() const
		{
			return m_iImageIndexInactiveHovered;
		}

		int CListItemMultiButton::getImageIndexDisabled() const
		{
			return m_iImageIndexDisabled;
		}
	#pragma endregion

	#pragma region Setters
		bool CListItemMultiButton::setImageIndexNormal(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndex)
			{
				m_iImageIndex = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexHovered)
			{
				m_iImageIndexHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexFocused(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexFocused)
			{
				m_iImageIndexFocused = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexFocusedHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexFocusedHovered)
			{
				m_iImageIndexFocusedHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexDown(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexDown)
			{
				m_iImageIndexDown = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexDownHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexDownHovered)
			{
				m_iImageIndexDownHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexDownFocused(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexDownFocused)
			{
				m_iImageIndexDownFocused = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexDownFocusedHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexDownFocusedHovered)
			{
				m_iImageIndexDownFocusedHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexActive(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexActive)
			{
				m_iImageIndexActive = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexActiveHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexActiveHovered)
			{
				m_iImageIndexActiveHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexInactive(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexInactive)
			{
				m_iImageIndexInactive = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexInactiveHovered(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexInactiveHovered)
			{
				m_iImageIndexInactiveHovered = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}

		bool CListItemMultiButton::setImageIndexDisabled(const int value)
		{
			int v{ ntl::Max<int>(-1, value) };
			if (v != m_iImageIndexDisabled)
			{
				m_iImageIndexDisabled = v;
				if (isVisible() && QueryService()->getOwner())
					QueryService()->getOwner()->NotifyOnRepaintRequired(this);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IListItem methods
		IListItem *CListItemMultiButton::Clone()
		{
			CListItemMultiButton *result{ new CListItemMultiButton() };
			Copy(result);
			return result;
		}

		bool CListItemMultiButton::Copy(IListItem *dest)
		{
			CListItemMultiButton *d{ cast<CListItemMultiButton*>(dest) };
			if (d)
			{
				d->m_sCaption = m_sCaption;
				d->m_iImageIndex = m_iImageIndex;
				d->m_iImageIndexHovered = m_iImageIndexHovered;
				d->m_iImageIndexFocused = m_iImageIndexFocused;
				d->m_iImageIndexFocusedHovered = m_iImageIndexFocusedHovered;
				d->m_iImageIndexDown = m_iImageIndexDown;
				d->m_iImageIndexDownHovered = m_iImageIndexDownHovered;
				d->m_iImageIndexDownFocused = m_iImageIndexDownFocused;
				d->m_iImageIndexDownFocusedHovered = m_iImageIndexDownFocusedHovered;
				d->m_iImageIndexActive = m_iImageIndexActive;
				d->m_iImageIndexActiveHovered = m_iImageIndexActiveHovered;
				d->m_iImageIndexInactive = m_iImageIndexInactive;
				d->m_iImageIndexInactiveHovered = m_iImageIndexInactiveHovered;
				d->m_iImageIndexDisabled = m_iImageIndexDisabled;
				return CListItem::Copy(dest);
			}
			return false;
		}
	#pragma endregion
	}
}