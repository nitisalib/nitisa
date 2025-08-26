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
#pragma region Helpers
	bool CBuiltInMonthCalendar::CancelDown()
	{
		if (m_hTimerScroll)
		{
			getControl()->getForm()->DeleteTimer(m_hTimerScroll);
			m_hTimerScroll = nullptr;
		}
		if (m_eDownElement != ElementType::None)
		{
			m_eDownElement = ElementType::None;
			if (!m_hTimerAnimate && m_pCanvas)
				m_pCanvas->setValid(false);
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region State change notifications
	void CBuiltInMonthCalendar::NotifyOnAttach()
	{
		NotifyOnFreeResources();
		PrepareRendering();
	}

	void CBuiltInMonthCalendar::NotifyOnDeactivate()
	{
		// Nothing
	}

	void CBuiltInMonthCalendar::NotifyOnFreeResources()
	{
		StopAnimation();
		if (m_hTimerScroll)
		{
			getControl()->getForm()->DeleteTimer(m_hTimerScroll);
			m_hTimerScroll = nullptr;
		}
		if (m_pCanvas)
		{
			m_pCanvas->Release();
			m_pCanvas = nullptr;
		}
		m_eDownElement = ElementType::None;
		m_eHoveredElement = ElementType::None;
		m_sInfo.Renderer = nullptr;
		m_sInfo.PlatformFont = nullptr;
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInMonthCalendar::NotifyOnMouseHover(const PointF &position)
	{
		if (!m_hTimerAnimate && UpdateHoveredItem(position))
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseLeave()
	{
		if (!m_hTimerAnimate && UpdateHoveredItem())
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (!m_hTimerAnimate && isEnabled() && UpdateHoveredItem(position))
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (CancelDown())
			return true;
		if (isEnabled())
		{
			if (getPrevRangeState() == TitleState::Hovered)
			{
				m_eDownElement = ElementType::Prev;
				Prev();
				m_hTimerScroll = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
				return true;
			}
			if (getNextRangeState() == TitleState::Hovered)
			{
				m_eDownElement = ElementType::Next;
				Next();
				m_hTimerScroll = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
				return true;
			}
			switch (m_eHoveredElement)
			{
			case ElementType::Title:
				switch (m_eMode)
				{
				case Mode::Month:
					return setMode(Mode::Year);
				case Mode::Year:
					return setMode(Mode::Decade);
				case Mode::Decade:
					return setMode(Mode::Century);
				default:
					break;
				}
				break;
			case ElementType::Today:
				if (Today())
					return true;
				break;
			case ElementType::Day:
				if (getDayState(m_iHoveredYear, m_iHoveredMonth, m_iHoveredDay) != ElementState::Disabled)
				{
					StopAnimation();
					m_cDate.setDate(m_iHoveredYear, m_iHoveredMonth, m_iHoveredDay);
					IBuiltInMonthCalendarListener *listener{ cast<IBuiltInMonthCalendarListener*>(m_pListener) };
					if (listener)
						listener->NotifyOnChange(this);
					return true;
				}
				break;
			case ElementType::Month:
				if (getMonthState(m_iHoveredYear, m_iHoveredMonth) != ElementState::Disabled)
				{
					m_iPageMonth = m_iHoveredMonth;
					ChangeMode(Mode::Year, Mode::Month);
					return true;
				}
			case ElementType::Year:
				if (getYearState(m_iHoveredYear) != ElementState::Disabled)
				{
					m_iPageYear = m_iHoveredYear;
					m_iPageMonth = CDateTime::January;
					ChangeMode(Mode::Decade, Mode::Year);
					return true;
				}
			case ElementType::Decade:
				if (getDecadeState(m_iHoveredYear) != ElementState::Disabled)
				{
					m_iPageYear = m_iHoveredYear - m_iHoveredYear % 10;
					m_iPageMonth = CDateTime::January;
					ChangeMode(Mode::Century, Mode::Decade);
					return true;
				}
			default:
				break;
			}
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return CancelDown();
	}

	void CBuiltInMonthCalendar::NotifyOnMouseDownCancel()
	{
		CancelDown();
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (isEnabled() && m_eDownElement == ElementType::None && !m_hTimerAnimate)
			return delta < 0 ? Prev() : Next();
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (isEnabled() && m_eDownElement == ElementType::None && !m_hTimerAnimate)
			return delta < 0 ? Prev() : Next();
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInMonthCalendar::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInMonthCalendar::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInMonthCalendar::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInMonthCalendar::NotifyOnPasteString(const String &text)
	{
		return false;
	}
#pragma endregion
}