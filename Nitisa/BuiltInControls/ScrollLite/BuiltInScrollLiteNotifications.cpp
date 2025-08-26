// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region State change notifications
	void CBuiltInScrollLite::NotifyOnAttach()
	{
		// No actions
	}

	void CBuiltInScrollLite::NotifyOnDeactivate()
	{
		// Not supported
	}

	void CBuiltInScrollLite::NotifyOnFreeResources()
	{
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
		m_bScrolling = false;
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInScrollLite::NotifyOnMouseHover(const PointF &position)
	{
		bool result{ false };
		if (!m_bHovered)
		{
			m_bHovered = true;
			result = true;
		}
		if (UpdateHoveredElement(position))
			result = true;
		return result;
	}

	bool CBuiltInScrollLite::NotifyOnMouseLeave()
	{
		bool result{ false };
		if (m_bHovered)
		{
			m_bHovered = false;
			result = true;
		}
		if (m_eHoveredElement != ElementType::None)
		{
			m_eHoveredElement = ElementType::None;
			result = true;
		}
		return result;
	}

	bool CBuiltInScrollLite::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		bool result{ false };
		if (!m_bScrolling && UpdateHoveredElement(position))
			result = true;
		if (m_bScrolling)
		{
			if (m_eScrollBy == ScrollBy::Scroller)
			{
				float d{ m_bVertical ? (position.Y - m_sScrollPosition.Y) : (position.X - m_sScrollPosition.X) };
				float scroller_size, scrolling_area;
				CalculateScroller(scroller_size, scrolling_area);
				float ds{ d * (m_fMax - m_fMin) / scrolling_area };
				if (setScroll(m_fScrollPosition + ds))
				{
					IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnScroll(this);
					result = true;
				}
			}
			else
				m_sScrollPosition = position;
		}
		return result;
	}

	bool CBuiltInScrollLite::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (!isEnabled() || m_bScrolling || middle || right || !getControl() || !getControl()->getForm())
			return false;
		m_eScrollBy = getScrollElement(position);
		m_bScrolling = m_eScrollBy != ScrollBy::None;
		m_sScrollPosition = position;
		m_fScrollPosition = m_fScroll;
		m_eActiveElement = ElementType::None;
		switch (m_eScrollBy)
		{
		case ScrollBy::BeforeScroller:
			if (setScroll(m_fScroll - CalculateDeltaLarge()))
			{
				IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pListener) };
				if (listener)
					listener->NotifyOnScroll(this);
			}
			break;
		case ScrollBy::AfterScroller:
			if (setScroll(m_fScroll + CalculateDeltaLarge()))
			{
				IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pListener) };
				if (listener)
					listener->NotifyOnScroll(this);
			}
			break;
		case ScrollBy::Scroller:
			m_eActiveElement = ElementType::Scroller;
			break;
		default:
			break;
		}
		switch (m_eScrollBy)
		{
		case ScrollBy::BeforeScroller:
		case ScrollBy::AfterScroller:
			m_hTimer = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
			break;
		default:
			break;
		}
		return m_bScrolling;
	}

	bool CBuiltInScrollLite::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (m_bScrolling)
		{
			NotifyOnMouseDownCancel();
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, false, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	bool CBuiltInScrollLite::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	void CBuiltInScrollLite::NotifyOnMouseDownCancel()
	{
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
		m_bScrolling = false;
		m_eScrollBy = ScrollBy::None;
		m_eActiveElement = ElementType::None;
	}

	bool CBuiltInScrollLite::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (!isEnabled() || m_bScrolling || delta == 0)
			return false;
		return setScroll(m_fScroll + (delta > 0 ? m_fDeltaMedium : -m_fDeltaMedium));
	}

	bool CBuiltInScrollLite::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (!isEnabled() || m_bScrolling || delta == 0)
			return false;
		return setScroll(m_fScroll + (delta > 0 ? m_fDeltaMedium : -m_fDeltaMedium));
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInScrollLite::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScrollLite::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScrollLite::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScrollLite::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInScrollLite::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInScrollLite::NotifyOnPasteString(const String &text)
	{
		return false;
	}
#pragma endregion
}