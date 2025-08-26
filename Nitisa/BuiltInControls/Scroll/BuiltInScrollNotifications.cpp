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
#pragma region State change notifications
	void CBuiltInScroll::NotifyOnAttach()
	{
		// No actions
	}

	void CBuiltInScroll::NotifyOnDeactivate()
	{
		// Not supported
	}

	void CBuiltInScroll::NotifyOnFreeResources()
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
	bool CBuiltInScroll::NotifyOnMouseHover(const PointF &position)
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

	bool CBuiltInScroll::NotifyOnMouseLeave()
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

	bool CBuiltInScroll::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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

	bool CBuiltInScroll::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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
		case ScrollBy::StartArrow:
			if (setScroll(m_fScroll - m_fDeltaSmall))
			{
				IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pListener) };
				if (listener)
					listener->NotifyOnScroll(this);
			}
			m_eActiveElement = ElementType::StartArrow;
			break;
		case ScrollBy::EndArrow:
			if (setScroll(m_fScroll + m_fDeltaSmall))
			{
				IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pListener) };
				if (listener)
					listener->NotifyOnScroll(this);
			}
			m_eActiveElement = ElementType::EndArrow;
			break;
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
		case ScrollBy::StartArrow:
		case ScrollBy::EndArrow:
		case ScrollBy::BeforeScroller:
		case ScrollBy::AfterScroller:
			m_hTimer = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
			break;
		default:
			break;
		}
		return m_bScrolling;
	}

	bool CBuiltInScroll::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (m_bScrolling)
		{
			NotifyOnMouseDownCancel();
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, false, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, false, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	bool CBuiltInScroll::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, false, true, ctrl, alt, shift);
	}

	void CBuiltInScroll::NotifyOnMouseDownCancel()
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

	bool CBuiltInScroll::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (!isEnabled() || m_bScrolling || delta == 0)
			return false;
		return setScroll(m_fScroll + (delta > 0 ? m_fDeltaMedium : -m_fDeltaMedium));
	}

	bool CBuiltInScroll::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (!isEnabled() || m_bScrolling || delta == 0)
			return false;
		return setScroll(m_fScroll + (delta > 0 ? m_fDeltaMedium : -m_fDeltaMedium));
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInScroll::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScroll::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScroll::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInScroll::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInScroll::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInScroll::NotifyOnPasteString(const String &text)
	{
		return false;
	}
#pragma endregion
}