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
#pragma region CTimerListener
	CBuiltInMonthCalendar::CTimerListener::CTimerListener(CBuiltInMonthCalendar *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInMonthCalendar::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		if (id == m_pControl->m_hTimerAnimate)
		{
			std::chrono::steady_clock::time_point now{ std::chrono::steady_clock::now() };
			float elapsed{ (float)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_pControl->m_sAnimationStart).count() * 0.001f };
			if (elapsed > m_pControl->m_fAnimateTime)
			{
				m_pControl->StopAnimation();
				m_pControl->UpdateHoveredItem();
			}
			if (m_pControl->m_pListener)
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
		}
		else
		{
			if (!m_pControl->m_hTimerAnimate)
			{
				if (m_pControl->m_eDownElement == ElementType::Next && m_pControl->Next() && m_pControl->m_pListener)
					m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
				else if (m_pControl->m_eDownElement == ElementType::Prev && m_pControl->Prev() && m_pControl->m_pListener)
					m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
			}
		}
	}
#pragma endregion

#pragma region CGradientListener
	CBuiltInMonthCalendar::CGradientListener::CGradientListener(CBuiltInMonthCalendar *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInMonthCalendar::CGradientListener::NotifyOnChange()
	{
		if (!m_pControl->m_bIgnoreGradient && m_pControl->m_pListener)
		{
			m_pControl->StopAnimation();
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
		}
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInMonthCalendar::CBuiltInMonthCalendar() :
		CBuiltInControl(L"MonthCalendar"),
		m_cGradientListener{ this },
		m_cMinDate{ 1600, CDateTime::January, 1, 0, 0, 0 },
		m_cMaxDate{ 3000, CDateTime::December, 31, 23, 59, 59 },
		// General
		m_eMode{ Mode::Month },
		m_bShowToday{ true },
		m_sTitlePadding{ 4, 7, 4, 7 },
		m_sTodayPadding{ 4, 3, 4, 3 },
		m_fTodayMargin{ 5 },
		m_fTodayRectWidth{ 20 },
		m_sElementPadding{ 4, 4, 4, 4 },
		m_sDayPadding{ 4, 2, 4, 2 },
		// Animation
		m_bAnimate{ true },
		m_fAnimateInterval{ 0.025f },
		m_fAnimateMinScale{ 0.3f },
		m_fAnimateTime{ 0.5f },
		m_fScrollInterval{ ScrollInterval },
		// Title
		m_aTitleAlign{ TextAlign::Center, TextAlign::Center, TextAlign::Center, TextAlign::Center, TextAlign::Center },
		m_aTitleBorderRadius{ 0, 0, 0, 0, 0 },
		m_aTitleBorderWidth{ 0, 0, 0, 0, 0 },
		m_aTitleBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aTitleBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aTitleBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aTitleColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 100, 100, 100, 255 } },
		m_aTitlePrevRangeBorderRadius{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTitlePrevRangeBorderWidth{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTitlePrevRangeBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aTitlePrevRangeBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aTitlePrevRangeBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aTitlePrevRangePadding{
			RectF{ 4, 9, 19, 10 },
			RectF{ 4, 9, 19, 10 },
			RectF{ 4, 9, 19, 10 },
			RectF{ 4, 9, 19, 10 },
			RectF{ 4, 9, 19, 10 } },
		m_aTitlePrevRangeColor1{
			Color{ 11, 11, 11, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 11, 11, 11, 255 },
			Color{ 11, 11, 11, 255 },
			Color{ 175, 175, 175, 255 } },
		m_aTitlePrevRangeColor2{
			Color{ 59, 59, 59, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 59, 59, 59, 255 },
			Color{ 59, 59, 59, 255 },
			Color{ 175, 175, 175, 255 } },
		m_aTitlePrevRangeColor3{
			Color{ 49, 49, 49, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 49, 49, 49, 255 },
			Color{ 49, 49, 49, 255 },
			Color{ 175, 175, 175, 255 } },
		m_aTitleNextRangeBorderRadius{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTitleNextRangeBorderWidth{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTitleNextRangeBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aTitleNextRangeBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aTitleNextRangeBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aTitleNextRangePadding{
			RectF{ 19, 9, 3, 10 },
			RectF{ 19, 9, 3, 10 },
			RectF{ 19, 9, 3, 10 },
			RectF{ 19, 9, 3, 10 },
			RectF{ 19, 9, 3, 10 } },
		m_aTitleNextRangeColor1{
			Color{ 59, 59, 59, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 59, 59, 59, 255 },
			Color{ 59, 59, 59, 255 },
			Color{ 175, 175, 175, 255 } },
		m_aTitleNextRangeColor2{
			Color{ 11, 11, 11, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 11, 11, 11, 255 },
			Color{ 11, 11, 11, 255 },
			Color{ 175, 175, 175, 255 } },
		m_aTitleNextRangeColor3{
			Color{ 49, 49, 49, 255 },
			Color{ 0, 102, 204, 255 },
			Color{ 49, 49, 49, 255 },
			Color{ 49, 49, 49, 255 },
			Color{ 175, 175, 175, 255 } },
		// Today link
		m_aTodayAlign{ TextAlign::Right, TextAlign::Right, TextAlign::Right, TextAlign::Right, TextAlign::Right },
		m_aTodayBorderRadius{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTodayBorderWidth{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aTodayBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aTodayBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aTodayBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aTodayColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 100, 100, 100, 255 } },
		m_aTodayRectBorderRadius{
			RectF{ 2, 2, 2, 2 },
			RectF{ 2, 2, 2, 2 },
			RectF{ 2, 2, 2, 2 },
			RectF{ 2, 2, 2, 2 },
			RectF{ 2, 2, 2, 2 } },
		m_aTodayRectBorderWidth{
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 } },
		m_aTodayRectBorderColor{
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 100, 100, 100, 255 }, Color{ 100, 100, 100, 255 }, Color{ 100, 100, 100, 255 }, Color{ 100, 100, 100, 255 } } },
		m_aTodayRectBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aTodayRectBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		// Elements
		m_aElementHorizontalAlign{
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center,
			TextAlign::Center },
		m_aElementVerticalAlign{
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle },
		m_aElementBorderRadius{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aElementBorderWidth{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 1, 1, 1, 1 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aElementBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 }, Color{ 0, 102, 204, 255 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
		m_aElementBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 229, 243, 255, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 229, 243, 255, 255 },
			Color{ 205, 232, 255, 255 },
			Color{ 205, 232, 255, 255 },
			Color{ 205, 232, 255, 255 },
			Color{ 205, 232, 255, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 229, 243, 255, 255 },
			Color{ 0, 0, 0, 0 } },
		m_aElementBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aElementColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 102, 204, 255 },
			Color{ 100, 100, 100, 255 },
			Color{ 177, 197, 252, 255 },
			Color{ 100, 100, 100, 255 } },
		m_aElementOutlineColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 255 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aElementOutlineMask{
			0b00000000000000000000000000000000,
			0b00000000000000000000000000000000,
			0b00000000000000000000000000000000,
			0b00000000000000000000000000000000,
			0b01010101010101010101010101010101,
			0b01010101010101010101010101010101,
			0b01010101010101010101010101010101,
			0b01010101010101010101010101010101,
			0b00000000000000000000000000000000,
			0b00000000000000000000000000000000,
			0b00000000000000000000000000000000 },
		m_aDayHorizontalAlign{
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right,
				TextAlign::Right },
		m_aDayVerticalAlign{
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle,
			VerticalAlign::Middle },
		// Day title
		m_aDayTitleHorizontalAlign{ TextAlign::Right, TextAlign::Right },
		m_aDayTitleVerticalAlign{ VerticalAlign::Middle, VerticalAlign::Middle },
		m_aDayTitleBorderRadius{
			RectF{ 0, 0, 0, 0 },
			RectF{ 0, 0, 0, 0 } },
		m_aDayTitleBorderWidth{
			RectF{ 0, 0, 0, 1 },
			RectF{ 0, 0, 0, 1 } },
		m_aDayTitleBorderColor{
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 245, 245, 245, 255 } },
			BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 245, 245, 245, 255 } } },
		m_aDayTitleBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aDayTitleBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aDayTitleColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_pListener{ nullptr },
		m_pCanvas{ nullptr },
		m_pCanvas1{ nullptr },
		m_pCanvas2{ nullptr },
		m_hTimerAnimate{ nullptr },
		m_hTimerScroll{ nullptr },
		m_bIgnoreGradient{ true },
		m_eHoveredElement{ ElementType::None },
		m_eDownElement{ ElementType::None },
		m_sInfo{ 0, PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 }, PointF{ 0, 0 }, nullptr, nullptr, nullptr, 0 },
		m_cTimerListener{ this }
	{
		// Set current date
		m_iPageYear = m_cDate.getYear();
		m_iPageMonth = m_cDate.getMonth();
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInMonthCalendar::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInMonthCalendar::isDown()
	{
		return m_hTimerScroll != nullptr;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInMonthCalendar::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInMonthCalendar::setSize(const PointF &value)
	{
		if (CBuiltInControl::setSize(value))
		{
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
			float avg{ (s.X + s.Y) * 0.5f };
			m_sTitlePadding *= s;
			m_sTodayPadding *= s;
			m_sElementPadding *= s;
			m_sDayPadding *= s;
			m_fTodayMargin *= s.X;
			m_fTodayRectWidth *= s.X;
			for (int i = 0; i <= (int)TitleState::Disabled; i++)
			{
				m_aTitleBorderRadius[i] *= avg;
				m_aTitleBorderWidth[i] *= s;
				m_aTitlePrevRangeBorderRadius[i] *= avg;
				m_aTitlePrevRangeBorderWidth[i] *= s;
				m_aTitlePrevRangePadding[i] *= s;
				m_aTitleNextRangeBorderRadius[i] *= avg;
				m_aTitleNextRangeBorderWidth[i] *= s;
				m_aTitleNextRangePadding[i] *= s;
				m_aTodayBorderRadius[i] *= avg;
				m_aTodayBorderWidth[i] *= s;
				m_aTodayRectBorderRadius[i] *= avg;
				m_aTodayRectBorderWidth[i] *= s;
			}
			for (int i = 0; i <= (int)ElementState::Disabled; i++)
			{
				m_aElementBorderRadius[i] *= avg;
				m_aElementBorderWidth[i] *= s;
			}
			for (int i = 0; i <= (int)DayTitleState::Disabled; i++)
			{
				m_aDayTitleBorderRadius[i] *= avg;
				m_aDayTitleBorderWidth[i] *= s;
			}
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl methods
	void CBuiltInMonthCalendar::Refresh()
	{
		if (!m_hTimerAnimate && m_pCanvas)
			m_pCanvas->setValid(false);
	}
#pragma endregion

#pragma region IBuiltInMonthCalendar getters
	PointF CBuiltInMonthCalendar::getRequiredSize()
	{
		PointF result{ 0, 0 };
		if (PrepareRendering())
			result = m_sInfo.Size;
		return result;
	}

	int CBuiltInMonthCalendar::getYear()
	{
		return m_cDate.getYear();
	}

	int CBuiltInMonthCalendar::getMonth()
	{
		return m_cDate.getMonth();
	}

	int CBuiltInMonthCalendar::getDay()
	{
		return m_cDate.getDay();
	}

	int CBuiltInMonthCalendar::getMinYear()
	{
		return m_cMinDate.getYear();
	}

	int CBuiltInMonthCalendar::getMinMonth()
	{
		return m_cMinDate.getMonth();
	}

	int CBuiltInMonthCalendar::getMinDay()
	{
		return m_cMinDate.getDay();
	}

	int CBuiltInMonthCalendar::getMaxYear()
	{
		return m_cMaxDate.getYear();
	}

	int CBuiltInMonthCalendar::getMaxMonth()
	{
		return m_cMaxDate.getMonth();
	}

	int CBuiltInMonthCalendar::getMaxDay()
	{
		return m_cMaxDate.getDay();
	}

	bool CBuiltInMonthCalendar::isAnimating()
	{
		return m_hTimerAnimate != nullptr;
	}
#pragma endregion

#pragma region IBuiltInMonthCalendar setters
	bool CBuiltInMonthCalendar::setYear(const int value)
	{
		return setDate(value, m_cDate.getMonth(), m_cDate.getDay());
	}

	bool CBuiltInMonthCalendar::setMonth(const int value)
	{
		return setDate(m_cDate.getYear(), value, m_cDate.getDay());
	}

	bool CBuiltInMonthCalendar::setDay(const int value)
	{
		return setDate(m_cDate.getYear(), m_cDate.getMonth(), value);
	}

	bool CBuiltInMonthCalendar::setMinYear(const int value)
	{
		return setMinDate(value, m_cMinDate.getMonth(), m_cMinDate.getDay());
	}

	bool CBuiltInMonthCalendar::setMinMonth(const int value)
	{
		return setMinDate(m_cMinDate.getYear(), value, m_cMinDate.getDay());
	}

	bool CBuiltInMonthCalendar::setMinDay(const int value)
	{
		return setMinDate(m_cMinDate.getYear(), m_cMinDate.getMonth(), value);
	}

	bool CBuiltInMonthCalendar::setMaxYear(const int value)
	{
		return setMaxDate(value, m_cMaxDate.getMonth(), m_cMaxDate.getDay());
	}

	bool CBuiltInMonthCalendar::setMaxMonth(const int value)
	{
		return setMaxDate(m_cMaxDate.getYear(), value, m_cMaxDate.getDay());
	}

	bool CBuiltInMonthCalendar::setMaxDay(const int value)
	{
		return setMaxDate(m_cMaxDate.getYear(), m_cMaxDate.getMonth(), value);
	}
#pragma endregion

#pragma region IBuiltInMonthCalendar methods
	bool CBuiltInMonthCalendar::Next()
	{
		switch (m_eMode)
		{
		case Mode::Month:
			return NextMonth();
		case Mode::Year:
			return NextYear();
		case Mode::Decade:
			return NextDecade();
		case Mode::Century:
			return NextCentury();
		default:
			return false;
		}
	}

	bool CBuiltInMonthCalendar::Prev()
	{
		switch (m_eMode)
		{
		case Mode::Month:
			return PrevMonth();
		case Mode::Year:
			return PrevYear();
		case Mode::Decade:
			return PrevDecade();
		case Mode::Century:
			return PrevCentury();
		default:
			return false;
		}
	}

	bool CBuiltInMonthCalendar::Today()
	{
		CDateTime date;
		date.setTime(0, 0, 0);
		bool need_change{ m_iPageYear != date.getYear() || (m_eMode == Mode::Month && m_iPageMonth != date.getMonth()) };
		if (date >= m_cMinDate && date <= m_cMaxDate && (m_cDate != date || need_change) && setDate(date.getYear(), date.getMonth(), date.getDay()))
		{
			StopAnimation();
			int new_year;
			switch (m_eMode)
			{
			case Mode::Month:
				if (m_iPageYear != m_cDate.getYear() || m_iPageMonth != m_cDate.getMonth())
				{
					if (m_cDate.getYear() < m_iPageYear || (m_cDate.getYear() == m_iPageYear && m_cDate.getMonth() < m_iPageMonth))
					{
						ChangePage(m_cDate.getYear(), m_cDate.getMonth(), AnimateType::SlideRight);
					}
					else
					{
						if (m_cDate.getYear() > m_iPageYear || (m_cDate.getYear() == m_iPageYear && m_cDate.getMonth() > m_iPageMonth))
							ChangePage(m_cDate.getYear(), m_cDate.getMonth(), AnimateType::SlideLeft);
					}
				}
				break;
			case Mode::Year:
				if (m_iPageYear != m_cDate.getYear())
				{
					if (m_cDate.getYear() < m_iPageYear)
					{
						ChangePage(m_cDate.getYear(), CDateTime::January, AnimateType::SlideRight);
					}
					else
					{
						if (m_cDate.getYear() > m_iPageYear)
							ChangePage(m_cDate.getYear(), CDateTime::January, AnimateType::SlideLeft);
					}
				}
				break;
			case Mode::Decade:
				new_year = m_cDate.getYear() - m_cDate.getYear() % 10;
				if (m_iPageYear != new_year)
				{
					if (new_year < m_iPageYear)
					{
						ChangePage(new_year, CDateTime::January, AnimateType::SlideRight);
					}
					else
					{
						if (new_year > m_iPageYear)
							ChangePage(new_year, CDateTime::January, AnimateType::SlideLeft);
					}
				}
				break;
			case Mode::Century:
				new_year = m_cDate.getYear() - m_cDate.getYear() % 100;
				if (m_iPageYear != new_year)
				{
					if (new_year < m_iPageYear)
					{
						ChangePage(new_year, CDateTime::January, AnimateType::SlideRight);
					}
					else
					{
						if (new_year > m_iPageYear)
							ChangePage(new_year, CDateTime::January, AnimateType::SlideLeft);
					}
				}
				break;
			}
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Getters
	CBuiltInMonthCalendar::Mode CBuiltInMonthCalendar::getMode() const
	{
		return m_eMode;
	}

	bool CBuiltInMonthCalendar::isShowToday() const
	{
		return m_bShowToday;
	}

	RectF CBuiltInMonthCalendar::getTitlePadding() const
	{
		return m_sTitlePadding;
	}

	RectF CBuiltInMonthCalendar::getTodayPadding() const
	{
		return m_sTodayPadding;
	}

	RectF CBuiltInMonthCalendar::getElementPadding() const
	{
		return m_sElementPadding;
	}

	RectF CBuiltInMonthCalendar::getDayPadding() const
	{
		return m_sDayPadding;
	}

	float CBuiltInMonthCalendar::getTodayMargin() const
	{
		return m_fTodayMargin;
	}

	float CBuiltInMonthCalendar::getTodayRectWidth() const
	{
		return m_fTodayRectWidth;
	}

	bool CBuiltInMonthCalendar::isAnimate() const
	{
		return m_bAnimate;
	}

	float CBuiltInMonthCalendar::getAnimateInterval() const
	{
		return m_fAnimateInterval;
	}

	float CBuiltInMonthCalendar::getAnimateMinScale() const
	{
		return m_fAnimateMinScale;
	}

	float CBuiltInMonthCalendar::getAnimateTime() const
	{
		return m_fAnimateTime;
	}

	float CBuiltInMonthCalendar::getScrollInterval() const
	{
		return m_fScrollInterval;
	}

	TextAlign CBuiltInMonthCalendar::getTitleAlign(const TitleState state) const
	{
		return m_aTitleAlign[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitleBorderRadius(const TitleState state) const
	{
		return m_aTitleBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitleBorderWidth(const TitleState state) const
	{
		return m_aTitleBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getTitleBorderColor(const TitleState state) const
	{
		return m_aTitleBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleBackgroundColor(const TitleState state) const
	{
		return m_aTitleBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getTitleBackgroundGradient(const TitleState state)
	{
		return &m_aTitleBackgroundGradient[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleColor(const TitleState state) const
	{
		return m_aTitleColor[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitlePrevRangeBorderRadius(const TitleState state) const
	{
		return m_aTitlePrevRangeBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitlePrevRangeBorderWidth(const TitleState state) const
	{
		return m_aTitlePrevRangeBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getTitlePrevRangeBorderColor(const TitleState state) const
	{
		return m_aTitlePrevRangeBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitlePrevRangeBackgroundColor(const TitleState state) const
	{
		return m_aTitlePrevRangeBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getTitlePrevRangeBackgroundGradient(const TitleState state)
	{
		return &m_aTitlePrevRangeBackgroundGradient[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitlePrevRangePadding(const TitleState state) const
	{
		return m_aTitlePrevRangePadding[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitlePrevRangeColor1(const TitleState state) const
	{
		return m_aTitlePrevRangeColor1[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitlePrevRangeColor2(const TitleState state) const
	{
		return m_aTitlePrevRangeColor2[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitlePrevRangeColor3(const TitleState state) const
	{
		return m_aTitlePrevRangeColor3[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitleNextRangeBorderRadius(const TitleState state) const
	{
		return m_aTitleNextRangeBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitleNextRangeBorderWidth(const TitleState state) const
	{
		return m_aTitleNextRangeBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getTitleNextRangeBorderColor(const TitleState state) const
	{
		return m_aTitleNextRangeBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleNextRangeBackgroundColor(const TitleState state) const
	{
		return m_aTitleNextRangeBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getTitleNextRangeBackgroundGradient(const TitleState state)
	{
		return &m_aTitleNextRangeBackgroundGradient[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTitleNextRangePadding(const TitleState state) const
	{
		return m_aTitleNextRangePadding[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleNextRangeColor1(const TitleState state) const
	{
		return m_aTitleNextRangeColor1[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleNextRangeColor2(const TitleState state) const
	{
		return m_aTitleNextRangeColor2[(int)state];
	}

	Color CBuiltInMonthCalendar::getTitleNextRangeColor3(const TitleState state) const
	{
		return m_aTitleNextRangeColor3[(int)state];
	}

	TextAlign CBuiltInMonthCalendar::getTodayAlign(const TitleState state) const
	{
		return m_aTodayAlign[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTodayBorderRadius(const TitleState state) const
	{
		return m_aTodayBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTodayBorderWidth(const TitleState state) const
	{
		return m_aTodayBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getTodayBorderColor(const TitleState state) const
	{
		return m_aTodayBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getTodayBackgroundColor(const TitleState state) const
	{
		return m_aTodayBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getTodayBackgroundGradient(const TitleState state)
	{
		return &m_aTodayBackgroundGradient[(int)state];
	}

	Color CBuiltInMonthCalendar::getTodayColor(const TitleState state) const
	{
		return m_aTodayColor[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTodayRectBorderRadius(const TitleState state) const
	{
		return m_aTodayRectBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getTodayRectBorderWidth(const TitleState state) const
	{
		return m_aTodayRectBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getTodayRectBorderColor(const TitleState state) const
	{
		return m_aTodayRectBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getTodayRectBackgroundColor(const TitleState state) const
	{
		return m_aTodayRectBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getTodayRectBackgroundGradient(const TitleState state)
	{
		return &m_aTodayRectBackgroundGradient[(int)state];
	}

	TextAlign CBuiltInMonthCalendar::getElementHorizontalAlign(const ElementState state) const
	{
		return m_aElementHorizontalAlign[(int)state];
	}

	VerticalAlign CBuiltInMonthCalendar::getElementVerticalAlign(const ElementState state) const
	{
		return m_aElementVerticalAlign[(int)state];
	}

	RectF CBuiltInMonthCalendar::getElementBorderRadius(const ElementState state) const
	{
		return m_aElementBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getElementBorderWidth(const ElementState state) const
	{
		return m_aElementBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getElementBorderColor(const ElementState state) const
	{
		return m_aElementBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getElementBackgroundColor(const ElementState state) const
	{
		return m_aElementBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getElementBackgroundGradient(const ElementState state)
	{
		return &m_aElementBackgroundGradient[(int)state];
	}

	Color CBuiltInMonthCalendar::getElementColor(const ElementState state) const
	{
		return m_aElementColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getElementOutlineColor(const ElementState state) const
	{
		return m_aElementOutlineColor[(int)state];
	}

	unsigned int CBuiltInMonthCalendar::getElementOutlineMask(const ElementState state) const
	{
		return m_aElementOutlineMask[(int)state];
	}

	TextAlign CBuiltInMonthCalendar::getDayHorizontalAlign(const ElementState state) const
	{
		return m_aDayHorizontalAlign[(int)state];
	}

	VerticalAlign CBuiltInMonthCalendar::getDayVerticalAlign(const ElementState state) const
	{
		return m_aDayVerticalAlign[(int)state];
	}

	TextAlign CBuiltInMonthCalendar::getDayTitleHorizontalAlign(const DayTitleState state) const
	{
		return m_aDayTitleHorizontalAlign[(int)state];
	}

	VerticalAlign CBuiltInMonthCalendar::getDayTitleVerticalAlign(const DayTitleState state) const
	{
		return m_aDayTitleVerticalAlign[(int)state];
	}

	RectF CBuiltInMonthCalendar::getDayTitleBorderRadius(const DayTitleState state) const
	{
		return m_aDayTitleBorderRadius[(int)state];
	}

	RectF CBuiltInMonthCalendar::getDayTitleBorderWidth(const DayTitleState state) const
	{
		return m_aDayTitleBorderWidth[(int)state];
	}

	BorderColor CBuiltInMonthCalendar::getDayTitleBorderColor(const DayTitleState state) const
	{
		return m_aDayTitleBorderColor[(int)state];
	}

	Color CBuiltInMonthCalendar::getDayTitleBackgroundColor(const DayTitleState state) const
	{
		return m_aDayTitleBackgroundColor[(int)state];
	}

	Gradient *CBuiltInMonthCalendar::getDayTitleBackgroundGradient(const DayTitleState state)
	{
		return &m_aDayTitleBackgroundGradient[(int)state];
	}

	Color CBuiltInMonthCalendar::getDayTitleColor(const DayTitleState state) const
	{
		return m_aDayTitleColor[(int)state];
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInMonthCalendar::setMode(const Mode value)
	{
		if (value != m_eMode)
		{
			ChangeMode(m_eMode, value);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setShowToday(const bool value)
	{
		if (value != m_bShowToday)
		{
			m_bShowToday = value;
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sTitlePadding))
		{
			m_sTitlePadding = value;
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sTodayPadding))
		{
			m_sTodayPadding = value;
			if (m_bShowToday)
				NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sElementPadding))
		{
			m_sElementPadding = value;
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayPadding(const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_sDayPadding))
		{
			m_sDayPadding = value;
			NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayMargin(const float value)
	{
		if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTodayMargin))
		{
			m_fTodayMargin = value;
			if (m_bShowToday)
				NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayRectWidth(const float value)
	{
		if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTodayRectWidth))
		{
			m_fTodayRectWidth = value;
			if (m_bShowToday)
				NotifyOnFreeResources();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setAnimate(const bool value)
	{
		if (value != m_bAnimate)
		{
			m_bAnimate = value;
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setAnimateInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fAnimateInterval))
		{
			m_fAnimateInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setAnimateMinScale(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsLess<float>(value, 1) && ntl::IsNotEqual<float>(value, m_fAnimateMinScale))
		{
			m_fAnimateMinScale = value;
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setAnimateTime(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fAnimateTime))
		{
			m_fAnimateTime = value;
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setScrollInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
		{
			m_fScrollInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleAlign(const TitleState state, const TextAlign value)
	{
		if (value != m_aTitleAlign[(int)state])
		{
			m_aTitleAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleBorderRadius(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitleBorderRadius[(int)state]))
		{
			m_aTitleBorderRadius[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleBorderWidth(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitleBorderWidth[(int)state]))
		{
			m_aTitleBorderWidth[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleBorderColor(const TitleState state, const BorderColor &value)
	{
		if (value != m_aTitleBorderColor[(int)state])
		{
			m_aTitleBorderColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleBackgroundColor(const TitleState state, const Color &value)
	{
		if (value != m_aTitleBackgroundColor[(int)state])
		{
			m_aTitleBackgroundColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleColor(const TitleState state, const Color &value)
	{
		if (value != m_aTitleColor[(int)state])
		{
			m_aTitleColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeBorderRadius(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitlePrevRangeBorderRadius[(int)state]))
		{
			m_aTitlePrevRangeBorderRadius[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeBorderWidth(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitlePrevRangeBorderWidth[(int)state]))
		{
			m_aTitlePrevRangeBorderWidth[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeBorderColor(const TitleState state, const BorderColor &value)
	{
		if (value != m_aTitlePrevRangeBorderColor[(int)state])
		{
			m_aTitlePrevRangeBorderColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeBackgroundColor(const TitleState state, const Color &value)
	{
		if (value != m_aTitlePrevRangeBackgroundColor[(int)state])
		{
			m_aTitlePrevRangeBackgroundColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangePadding(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitlePrevRangePadding[(int)state]))
		{
			m_aTitlePrevRangePadding[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeColor1(const TitleState state, const Color &value)
	{
		if (value != m_aTitlePrevRangeColor1[(int)state])
		{
			m_aTitlePrevRangeColor1[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeColor2(const TitleState state, const Color &value)
	{
		if (value != m_aTitlePrevRangeColor2[(int)state])
		{
			m_aTitlePrevRangeColor2[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitlePrevRangeColor3(const TitleState state, const Color &value)
	{
		if (value != m_aTitlePrevRangeColor3[(int)state])
		{
			m_aTitlePrevRangeColor3[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeBorderRadius(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitleNextRangeBorderRadius[(int)state]))
		{
			m_aTitleNextRangeBorderRadius[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeBorderWidth(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitleNextRangeBorderWidth[(int)state]))
		{
			m_aTitleNextRangeBorderWidth[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeBorderColor(const TitleState state, const BorderColor &value)
	{
		if (value != m_aTitleNextRangeBorderColor[(int)state])
		{
			m_aTitleNextRangeBorderColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeBackgroundColor(const TitleState state, const Color &value)
	{
		if (value != m_aTitleNextRangeBackgroundColor[(int)state])
		{
			m_aTitleNextRangeBackgroundColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangePadding(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTitleNextRangePadding[(int)state]))
		{
			m_aTitleNextRangePadding[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeColor1(const TitleState state, const Color &value)
	{
		if (value != m_aTitleNextRangeColor1[(int)state])
		{
			m_aTitleNextRangeColor1[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeColor2(const TitleState state, const Color &value)
	{
		if (value != m_aTitleNextRangeColor2[(int)state])
		{
			m_aTitleNextRangeColor2[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTitleNextRangeColor3(const TitleState state, const Color &value)
	{
		if (value != m_aTitleNextRangeColor3[(int)state])
		{
			m_aTitleNextRangeColor3[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayAlign(const TitleState state, const TextAlign value)
	{
		if (value != m_aTodayAlign[(int)state])
		{
			m_aTodayAlign[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayBorderRadius(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTodayBorderRadius[(int)state]))
		{
			m_aTodayBorderRadius[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayBorderWidth(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTodayBorderWidth[(int)state]))
		{
			m_aTodayBorderWidth[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayBorderColor(const TitleState state, const BorderColor &value)
	{
		if (value != m_aTodayBorderColor[(int)state])
		{
			m_aTodayBorderColor[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayBackgroundColor(const TitleState state, const Color &value)
	{
		if (value != m_aTodayBackgroundColor[(int)state])
		{
			m_aTodayBackgroundColor[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayColor(const TitleState state, const Color &value)
	{
		if (value != m_aTodayColor[(int)state])
		{
			m_aTodayColor[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayRectBorderRadius(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTodayRectBorderRadius[(int)state]))
		{
			m_aTodayRectBorderRadius[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayRectBorderWidth(const TitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aTodayRectBorderWidth[(int)state]))
		{
			m_aTodayRectBorderWidth[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayRectBorderColor(const TitleState state, const BorderColor &value)
	{
		if (value != m_aTodayRectBorderColor[(int)state])
		{
			m_aTodayRectBorderColor[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setTodayRectBackgroundColor(const TitleState state, const Color &value)
	{
		if (value != m_aTodayRectBackgroundColor[(int)state])
		{
			m_aTodayRectBackgroundColor[(int)state] = value;
			if (m_bShowToday)
				StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementHorizontalAlign(const ElementState state, const TextAlign value)
	{
		if (value != m_aElementHorizontalAlign[(int)state])
		{
			m_aElementHorizontalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementVerticalAlign(const ElementState state, const VerticalAlign value)
	{
		if (value != m_aElementVerticalAlign[(int)state])
		{
			m_aElementVerticalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementBorderRadius(const ElementState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aElementBorderRadius[(int)state]))
		{
			m_aElementBorderRadius[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementBorderWidth(const ElementState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aElementBorderWidth[(int)state]))
		{
			m_aElementBorderWidth[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementBorderColor(const ElementState state, const BorderColor &value)
	{
		if (value != m_aElementBorderColor[(int)state])
		{
			m_aElementBorderColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementBackgroundColor(const ElementState state, const Color &value)
	{
		if (value != m_aElementBackgroundColor[(int)state])
		{
			m_aElementBackgroundColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementColor(const ElementState state, const Color &value)
	{
		if (value != m_aElementColor[(int)state])
		{
			m_aElementColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementOutlineColor(const ElementState state, const Color &value)
	{
		if (value != m_aElementOutlineColor[(int)state])
		{
			m_aElementOutlineColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setElementOutlineMask(const ElementState state, const unsigned int value)
	{
		if (value != m_aElementOutlineMask[(int)state])
		{
			m_aElementOutlineMask[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayHorizontalAlign(const ElementState state, const TextAlign value)
	{
		if (value != m_aDayHorizontalAlign[(int)state])
		{
			m_aDayHorizontalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayVerticalAlign(const ElementState state, const VerticalAlign value)
	{
		if (value != m_aDayVerticalAlign[(int)state])
		{
			m_aDayVerticalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleHorizontalAlign(const DayTitleState state, const TextAlign value)
	{
		if (value != m_aDayTitleHorizontalAlign[(int)state])
		{
			m_aDayTitleHorizontalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleVerticalAlign(const DayTitleState state, const VerticalAlign value)
	{
		if (value != m_aDayTitleVerticalAlign[(int)state])
		{
			m_aDayTitleVerticalAlign[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleBorderRadius(const DayTitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aDayTitleBorderRadius[(int)state]))
		{
			m_aDayTitleBorderRadius[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleBorderWidth(const DayTitleState state, const RectF &value)
	{
		if (!value.has_negative() && IsNotEqual(value, m_aDayTitleBorderWidth[(int)state]))
		{
			m_aDayTitleBorderWidth[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleBorderColor(const DayTitleState state, const BorderColor &value)
	{
		if (value != m_aDayTitleBorderColor[(int)state])
		{
			m_aDayTitleBorderColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleBackgroundColor(const DayTitleState state, const Color &value)
	{
		if (value != m_aDayTitleBackgroundColor[(int)state])
		{
			m_aDayTitleBackgroundColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setDayTitleColor(const DayTitleState state, const Color &value)
	{
		if (value != m_aDayTitleColor[(int)state])
		{
			m_aDayTitleColor[(int)state] = value;
			StopAnimation();
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	void CBuiltInMonthCalendar::UpdateFromStyle(IStyle *style, const String &class_name)
	{
		m_bIgnoreGradient = true;
		style->getOption(class_name + L".TitlePadding", m_sTitlePadding);
		style->getOption(class_name + L".TodayPadding", m_sTodayPadding);
		style->getOption(class_name + L".TodayMargin", m_fTodayMargin);
		style->getOption(class_name + L".TodayRectWidth", m_fTodayRectWidth);
		style->getOption(class_name + L".ElementPadding", m_sElementPadding);
		style->getOption(class_name + L".DayPadding", m_sDayPadding);
		for (int i = 0; i <= (int)TitleState::Disabled; i++)
		{
			String state;
			switch ((TitleState)i)
			{
			case TitleState::Hovered:
				state = L"Hovered";
				break;
			case TitleState::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			style->getOption(class_name + L".TitleBorderRadius[" + state + L"]", m_aTitleBorderRadius[i]);
			style->getOption(class_name + L".TitleBorderWidth[" + state + L"]", m_aTitleBorderWidth[i]);
			style->getOption(class_name + L".TitleBorderColor[" + state + L"]", m_aTitleBorderColor[i]);
			style->getOption(class_name + L".TitleBackgroundColor[" + state + L"]", m_aTitleBackgroundColor[i]);
			style->getOption(class_name + L".TitleBackgroundGradient[" + state + L"]", m_aTitleBackgroundGradient[i]);
			style->getOption(class_name + L".TitleColor[" + state + L"]", m_aTitleColor[i]);
			style->getOption(class_name + L".TitleLeftArrowBorderRadius[" + state + L"]", m_aTitlePrevRangeBorderRadius[i]);
			style->getOption(class_name + L".TitleLeftArrowBorderWidth[" + state + L"]", m_aTitlePrevRangeBorderWidth[i]);
			style->getOption(class_name + L".TitleLeftArrowBorderColor[" + state + L"]", m_aTitlePrevRangeBorderColor[i]);
			style->getOption(class_name + L".TitleLeftArrowBackgroundColor[" + state + L"]", m_aTitlePrevRangeBackgroundColor[i]);
			style->getOption(class_name + L".TitleLeftArrowBackgroundGradient[" + state + L"]", m_aTitlePrevRangeBackgroundGradient[i]);
			style->getOption(class_name + L".TitleLeftArrowPadding[" + state + L"]", m_aTitlePrevRangePadding[i]);
			style->getOption(class_name + L".TitleLeftArrowColor1[" + state + L"]", m_aTitlePrevRangeColor1[i]);
			style->getOption(class_name + L".TitleLeftArrowColor2[" + state + L"]", m_aTitlePrevRangeColor2[i]);
			style->getOption(class_name + L".TitleLeftArrowColor3[" + state + L"]", m_aTitlePrevRangeColor3[i]);
			style->getOption(class_name + L".TitleRightArrowBorderRadius[" + state + L"]", m_aTitleNextRangeBorderRadius[i]);
			style->getOption(class_name + L".TitleRightArrowBorderWidth[" + state + L"]", m_aTitleNextRangeBorderWidth[i]);
			style->getOption(class_name + L".TitleRightArrowBorderColor[" + state + L"]", m_aTitleNextRangeBorderColor[i]);
			style->getOption(class_name + L".TitleRightArrowBackgroundColor[" + state + L"]", m_aTitleNextRangeBackgroundColor[i]);
			style->getOption(class_name + L".TitleRightArrowBackgroundGradient[" + state + L"]", m_aTitleNextRangeBackgroundGradient[i]);
			style->getOption(class_name + L".TitleRightArrowPadding[" + state + L"]", m_aTitleNextRangePadding[i]);
			style->getOption(class_name + L".TitleRightArrowColor1[" + state + L"]", m_aTitleNextRangeColor1[i]);
			style->getOption(class_name + L".TitleRightArrowColor2[" + state + L"]", m_aTitleNextRangeColor2[i]);
			style->getOption(class_name + L".TitleRightArrowColor3[" + state + L"]", m_aTitleNextRangeColor3[i]);
			style->getOption(class_name + L".TodayBorderRadius[" + state + L"]", m_aTodayBorderRadius[i]);
			style->getOption(class_name + L".TodayBorderWidth[" + state + L"]", m_aTodayBorderWidth[i]);
			style->getOption(class_name + L".TodayBorderColor[" + state + L"]", m_aTodayBorderColor[i]);
			style->getOption(class_name + L".TodayBackgroundColor[" + state + L"]", m_aTodayBackgroundColor[i]);
			style->getOption(class_name + L".TodayBackgroundGradient[" + state + L"]", m_aTodayBackgroundGradient[i]);
			style->getOption(class_name + L".TodayColor[" + state + L"]", m_aTodayColor[i]);
			style->getOption(class_name + L".TodayRectBorderRadius[" + state + L"]", m_aTodayRectBorderRadius[i]);
			style->getOption(class_name + L".TodayRectBorderWidth[" + state + L"]", m_aTodayRectBorderWidth[i]);
			style->getOption(class_name + L".TodayRectBorderColor[" + state + L"]", m_aTodayRectBorderColor[i]);
			style->getOption(class_name + L".TodayRectBackgroundColor[" + state + L"]", m_aTodayRectBackgroundColor[i]);
			style->getOption(class_name + L".TodayRectBackgroundGradient[" + state + L"]", m_aTodayRectBackgroundGradient[i]);
		}
		for (int i = 0; i <= (int)ElementState::Disabled; i++)
		{
			String state;
			switch ((ElementState)i)
			{
			case ElementState::Hovered:
				state = L"Hovered";
				break;
			case ElementState::Today:
				state = L"Today";
				break;
			case ElementState::TodayHovered:
				state = L"TodayHovered";
				break;
			case ElementState::Active:
				state = L"Active";
				break;
			case ElementState::ActiveHovered:
				state = L"ActiveHovered";
				break;
			case ElementState::TodayActive:
				state = L"TodayActive";
				break;
			case ElementState::TodayActiveHovered:
				state = L"TodayActiveHovered";
				break;
			case ElementState::OtherRange:
				state = L"OtherRange";
				break;
			case ElementState::OtherRangeHovered:
				state = L"OtherRangeHovered";
				break;
			case ElementState::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			style->getOption(class_name + L".ElementBorderRadius[" + state + L"]", m_aElementBorderRadius[i]);
			style->getOption(class_name + L".ElementBorderWidth[" + state + L"]", m_aElementBorderWidth[i]);
			style->getOption(class_name + L".ElementBorderColor[" + state + L"]", m_aElementBorderColor[i]);
			style->getOption(class_name + L".ElementBackgroundColor[" + state + L"]", m_aElementBackgroundColor[i]);
			style->getOption(class_name + L".ElementBackgroundGradient[" + state + L"]", m_aElementBackgroundGradient[i]);
			style->getOption(class_name + L".ElementColor[" + state + L"]", m_aElementColor[i]);
			style->getOption(class_name + L".ElementOutlineColor[" + state + L"]", m_aElementOutlineColor[i]);
			style->getOption(class_name + L".ElementOutlineMask[" + state + L"]", m_aElementOutlineMask[i]);
		}
		for (int i = 0; i <= (int)DayTitleState::Disabled; i++)
		{
			String state;
			switch ((DayTitleState)i)
			{
			case DayTitleState::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			style->getOption(class_name + L".DayTitleBorderRadius[" + state + L"]", m_aDayTitleBorderRadius[i]);
			style->getOption(class_name + L".DayTitleBorderWidth[" + state + L"]", m_aDayTitleBorderWidth[i]);
			style->getOption(class_name + L".DayTitleBorderColor[" + state + L"]", m_aDayTitleBorderColor[i]);
			style->getOption(class_name + L".DayTitleBackgroundColor[" + state + L"]", m_aDayTitleBackgroundColor[i]);
			style->getOption(class_name + L".DayTitleBackgroundGradient[" + state + L"]", m_aDayTitleBackgroundGradient[i]);
			style->getOption(class_name + L".DayTitleColor[" + state + L"]", m_aDayTitleColor[i]);
		}
		NotifyOnFreeResources();
		PrepareRendering();
		m_bIgnoreGradient = false;
	}

	void CBuiltInMonthCalendar::Update()
	{
		NotifyOnFreeResources();
		PrepareRendering();
	}

	void CBuiltInMonthCalendar::StopAnimation()
	{
		if (m_hTimerAnimate)
		{
			getControl()->getForm()->DeleteTimer(m_hTimerAnimate);
			m_hTimerAnimate = nullptr;
		}
		if (m_pCanvas)
			m_pCanvas->setValid(false);
		if (m_pCanvas1)
		{
			m_pCanvas1->Release();
			m_pCanvas1 = nullptr;
		}
		if (m_pCanvas2)
		{
			m_pCanvas2->Release();
			m_pCanvas2 = nullptr;
		}
	}

	bool CBuiltInMonthCalendar::PrepareRendering()
	{
		if ((!m_sInfo.Renderer || !m_sInfo.PlatformFont) && getControl() && getControl()->getForm())
		{
			m_sInfo.Renderer = getControl()->getForm()->getRenderer();
			m_sInfo.Font = getControl()->getFont();
			m_sInfo.PlatformFont = m_sInfo.Font->getPlatformFont(m_sInfo.Renderer);
			if (m_sInfo.Renderer && m_sInfo.PlatformFont)
			{
				m_sInfo.Distance = m_sInfo.Font->Distance;
				m_sInfo.LineHeight = m_sInfo.PlatformFont->getStringSize(L"Wy", 0).Y;
				// Title
				m_sInfo.TitleSize.Y = m_sInfo.LineHeight + m_sTitlePadding.Top + m_sTitlePadding.Bottom;
				m_sInfo.TitleSize.X = m_sInfo.PlatformFont->getStringSize(L"2000-2000", m_sInfo.Distance).X;
				for (auto month : months::Names)
					m_sInfo.TitleSize.X = ntl::Max<float>(m_sInfo.TitleSize.X, m_sInfo.PlatformFont->getStringSize(CTranslate::Month(month) + L" 2000", m_sInfo.Distance).X);
				m_sInfo.TitleSize.X += 2 * m_sInfo.TitleSize.Y + m_sTitlePadding.Left + m_sTitlePadding.Right;
				// Days
				m_sInfo.DaySize.X = m_sInfo.PlatformFont->getStringSize(L"20", m_sInfo.Distance).X;
				for (auto day : days::ShortNames)
					m_sInfo.DaySize.X = ntl::Max<float>(m_sInfo.DaySize.X, m_sInfo.PlatformFont->getStringSize(CTranslate::Day(day), m_sInfo.Distance).X);
				m_sInfo.DaySize.X += m_sDayPadding.Left + m_sDayPadding.Right;
				m_sInfo.DaySize.Y = m_sInfo.LineHeight + m_sDayPadding.Top + m_sDayPadding.Bottom;
				m_sInfo.DaysSize.X = m_sInfo.DaySize.X * 7;
				m_sInfo.DaysSize.Y = m_sInfo.DaySize.Y * 7;
				// Elements
				m_sInfo.ElementSize.X = m_sInfo.PlatformFont->getStringSize(L"2000-", m_sInfo.Distance).X;
				for (auto month : months::ShortNames)
					m_sInfo.ElementSize.X = ntl::Max<float>(m_sInfo.ElementSize.X, m_sInfo.PlatformFont->getStringSize(CTranslate::Month(month), m_sInfo.Distance).X);
				m_sInfo.ElementSize.X += m_sElementPadding.Left + m_sElementPadding.Right;
				m_sInfo.ElementSize.Y = 2 * m_sInfo.LineHeight + m_sElementPadding.Top + m_sElementPadding.Right;
				m_sInfo.ElementsSize.X = m_sInfo.ElementSize.X * 4;
				m_sInfo.ElementsSize.Y = m_sInfo.ElementSize.Y * 3;
				if (m_sInfo.ElementsSize.X > m_sInfo.DaysSize.X)
				{
					m_sInfo.DaySize.X = m_sInfo.ElementsSize.X / 7;
					m_sInfo.DaysSize.X = m_sInfo.ElementsSize.X;
				}
				else if (m_sInfo.DaysSize.X > m_sInfo.ElementsSize.X)
				{
					m_sInfo.ElementSize.X = m_sInfo.DaysSize.X / 4;
					m_sInfo.ElementsSize.X = m_sInfo.DaysSize.X;
				}
				if (m_sInfo.ElementsSize.Y > m_sInfo.DaysSize.Y)
				{
					m_sInfo.DaySize.Y = m_sInfo.ElementsSize.Y / 7;
					m_sInfo.DaysSize.Y = m_sInfo.ElementsSize.Y;
				}
				else if (m_sInfo.DaysSize.Y > m_sInfo.ElementsSize.Y)
				{
					m_sInfo.ElementSize.Y = m_sInfo.DaysSize.Y / 3;
					m_sInfo.ElementsSize.Y = m_sInfo.DaysSize.Y;
				}
				// Today
				if (m_bShowToday)
				{
					m_sInfo.TodaySize.Y = m_sInfo.LineHeight + m_sTodayPadding.Top + m_sTodayPadding.Bottom;
					m_sInfo.TodaySize.X = m_fTodayMargin + m_fTodayRectWidth + m_sTodayPadding.Left + m_sTodayPadding.Right +
						m_sInfo.PlatformFont->getStringSize(CTranslate::Day(days::Today) + L": 20.20.2000", m_sInfo.Distance).X;
				}
				// Size
				m_sInfo.Size.X = ntl::Max<float>(m_sInfo.TitleSize.X, m_sInfo.ElementsSize.X);
				m_sInfo.Size.Y = m_sInfo.TitleSize.Y + m_sInfo.ElementsSize.Y;
				if (m_bShowToday)
				{
					m_sInfo.Size.X = ntl::Max<float>(m_sInfo.Size.X, m_sInfo.TodaySize.X);
					m_sInfo.Size.Y += m_sInfo.TodaySize.Y;
				}
			}
		}
		return m_sInfo.Renderer && m_sInfo.PlatformFont;
	}

	bool CBuiltInMonthCalendar::setDate(const int year, const int month, const int day)
	{
		CDateTime d{ year, month, day, 0, 0, 0 };
		if (d < m_cMinDate)
			d = m_cMinDate;
		else if (d > m_cMaxDate)
			d = m_cMaxDate;
		if (d != m_cDate)
		{
			m_cDate = d;
			StopAnimation();
			IBuiltInMonthCalendarListener *listener{ cast<IBuiltInMonthCalendarListener*>(m_pListener) };
			if (listener)
				listener->NotifyOnChange(this);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setMinDate(const int year, const int month, const int day)
	{
		CDateTime d{ year, month, day, 0, 0, 0 };
		if (d != m_cMinDate)
		{
			m_cMinDate = d;
			if (m_cMaxDate < m_cMinDate)
				m_cMaxDate = m_cMinDate;
			setDate(m_cDate.getYear(), m_cDate.getMonth(), m_cDate.getDay());
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::setMaxDate(const int year, const int month, const int day)
	{
		CDateTime d{ year, month, day, 0, 0, 0 };
		if (d != m_cMaxDate)
		{
			m_cMaxDate = d;
			if (m_cMinDate > m_cMaxDate)
				m_cMinDate = m_cMaxDate;
			setDate(m_cDate.getYear(), m_cDate.getMonth(), m_cDate.getDay());
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NextMonth()
	{
		int next_year, next_month;
		if (m_iPageMonth == CDateTime::December)
		{
			next_year = m_iPageYear + 1;
			next_month = CDateTime::January;
		}
		else
		{
			next_year = m_iPageYear;
			next_month = m_iPageMonth + 1;
		}
		CDateTime next{ next_year, next_month, 1, 0, 0, 0 };
		if (next <= m_cMaxDate)
		{
			ChangePage(next_year, next_month, AnimateType::SlideLeft);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NextYear()
	{
		CDateTime next{ m_iPageYear + 1, CDateTime::January, 1, 0, 0, 0 };
		if (next > m_cMaxDate)
			next = m_cMaxDate;
		if (next.getYear() != m_iPageYear)
		{
			ChangePage(next.getYear(), CDateTime::January, AnimateType::SlideLeft);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NextDecade()
	{
		CDateTime next{ m_iPageYear + 10, CDateTime::January, 1, 0, 0, 0 };
		if (next > m_cMaxDate)
			next = m_cMaxDate;
		if (next.getYear() != m_iPageYear)
		{
			int next_year{ next.getYear() - next.getYear() % 10 };
			if (next_year != m_iPageYear)
				ChangePage(next_year, CDateTime::January, AnimateType::SlideLeft);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::NextCentury()
	{
		CDateTime next{ m_iPageYear + 100, CDateTime::January, 1, 0, 0, 0 };
		if (next > m_cMaxDate)
			next = m_cMaxDate;
		if (next.getYear() != m_iPageYear)
		{
			int next_year{ next.getYear() - next.getYear() % 100 };
			if (next_year != m_iPageYear)
				ChangePage(next_year, CDateTime::January, AnimateType::SlideLeft);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::PrevMonth()
	{
		int prev_year, prev_month;
		if (m_iPageMonth == CDateTime::January)
		{
			prev_year = m_iPageYear - 1;
			prev_month = CDateTime::December;
		}
		else
		{
			prev_year = m_iPageYear;
			prev_month = m_iPageMonth - 1;
		}
		CDateTime prev{prev_year, prev_month, 1, 0, 0, 0 };
		if (prev >= m_cMinDate)
		{
			ChangePage(prev_year, prev_month, AnimateType::SlideRight);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::PrevYear()
	{
		CDateTime prev{ m_iPageYear - 1, CDateTime::January, 1, 0, 0, 0 };
		if (prev < m_cMinDate)
			prev = m_cMinDate;
		if (prev.getYear() != m_iPageYear)
		{
			ChangePage(prev.getYear(), CDateTime::January, AnimateType::SlideRight);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::PrevDecade()
	{
		CDateTime prev{ m_iPageYear - 10, CDateTime::January, 1, 0, 0, 0 };
		if (prev < m_cMinDate)
			prev = m_cMinDate;
		if (prev.getYear() != m_iPageYear)
		{
			int prev_year{ prev.getYear() - prev.getYear() % 10 };
			if (prev_year != m_iPageYear)
				ChangePage(prev_year, CDateTime::January, AnimateType::SlideRight);
			return true;
		}
		return false;
	}

	bool CBuiltInMonthCalendar::PrevCentury()
	{
		CDateTime prev{ m_iPageYear - 100, CDateTime::January, 1, 0, 0, 0 };
		if (prev < m_cMinDate)
			prev = m_cMinDate;
		if (prev.getYear() != m_iPageYear)
		{
			int prev_year{ prev.getYear() - prev.getYear() % 100 };
			if (prev_year != m_iPageYear)
				ChangePage(prev_year, CDateTime::January, AnimateType::SlideRight);
			return true;
		}
		return false;
	}

	void CBuiltInMonthCalendar::ChangePage(const int new_year, const int new_month, const AnimateType type)
	{
		StopAnimation();
		if (m_bAnimate && ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && PrepareRendering())
		{
			if (m_pCanvas)
				m_pCanvas->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas1)
				m_pCanvas1->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas1 = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas2)
				m_pCanvas2->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas2 = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas && m_pCanvas1 && m_pCanvas2)
			{
				CStoreTarget s_target{ m_sInfo.Renderer };
				m_sInfo.Renderer->ActivateTarget(m_pCanvas1);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				switch (m_eMode)
				{
				case Mode::Month:
					RenderModeMonth(m_iPageYear, m_iPageMonth);
					break;
				case Mode::Year:
					RenderModeYear(m_iPageYear);
					break;
				case Mode::Decade:
					RenderModeDecade(m_iPageYear);
					break;
				case Mode::Century:
					RenderModeCentury(m_iPageYear);
					break;
				}

				m_iPageYear = new_year;
				m_iPageMonth = new_month;
				m_sInfo.Renderer->ActivateTarget(m_pCanvas2);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				switch (m_eMode)
				{
				case Mode::Month:
					RenderModeMonth(m_iPageYear, m_iPageMonth);
					break;
				case Mode::Year:
					RenderModeYear(m_iPageYear);
					break;
				case Mode::Decade:
					RenderModeDecade(m_iPageYear);
					break;
				case Mode::Century:
					RenderModeCentury(m_iPageYear);
					break;
				}

				m_sInfo.Renderer->ActivateTarget(m_pCanvas);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				RenderTitle(m_iPageYear, m_iPageMonth);
				if (m_bShowToday)
					RenderToday();

				m_eAnimateType = type;
				m_sAnimationStart = std::chrono::steady_clock::now();
				m_hTimerAnimate = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fAnimateInterval);
				if (!m_hTimerAnimate)
					NotifyOnFreeResources();
			}
			else
				NotifyOnFreeResources();
		}
		m_iPageYear = new_year;
		m_iPageMonth = new_month;
	}

	void CBuiltInMonthCalendar::ChangeMode(const Mode old_mode, const Mode new_mode)
	{
		StopAnimation();
		m_eMode = new_mode;
		if (m_bAnimate && ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && PrepareRendering())
		{
			if (m_pCanvas)
				m_pCanvas->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas1)
				m_pCanvas1->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas1 = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas2)
				m_pCanvas2->setSize(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()));
			else
				m_pCanvas2 = m_sInfo.Renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true);
			if (m_pCanvas && m_pCanvas1 && m_pCanvas2)
			{
				CStoreTarget s_target{ m_sInfo.Renderer };
				m_sInfo.Renderer->ActivateTarget(m_pCanvas1);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				switch (old_mode)
				{
				case Mode::Month:
					RenderModeMonth(m_iPageYear, m_iPageMonth);
					break;
				case Mode::Year:
					RenderModeYear(m_iPageYear);
					break;
				case Mode::Decade:
					RenderModeDecade(m_iPageYear);
					break;
				case Mode::Century:
					RenderModeCentury(m_iPageYear);
					break;
				}

				m_sInfo.Renderer->ActivateTarget(m_pCanvas2);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				switch (new_mode)
				{
				case Mode::Month:
					RenderModeMonth(m_iPageYear, m_iPageMonth);
					break;
				case Mode::Year:
					RenderModeYear(m_iPageYear);
					break;
				case Mode::Decade:
					m_iPageYear -= m_iPageYear % 10;
					RenderModeDecade(m_iPageYear);
					break;
				case Mode::Century:
					m_iPageYear -= m_iPageYear % 100;
					RenderModeCentury(m_iPageYear);
					break;
				}

				m_sInfo.Renderer->ActivateTarget(m_pCanvas);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				RenderTitle(m_iPageYear, m_iPageMonth);
				if (m_bShowToday)
					RenderToday();

				m_eAnimateType = AnimateType::Fade;
				m_sAnimationStart = std::chrono::steady_clock::now();
				m_hTimerAnimate = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fAnimateInterval);
				if (!m_hTimerAnimate)
					NotifyOnFreeResources();
			}
			else
				NotifyOnFreeResources();
		}
		switch (m_eMode)
		{
		case Mode::Decade:
			m_iPageYear -= m_iPageYear % 10;
			break;
		case Mode::Century:
			m_iPageYear -= m_iPageYear % 100;
			break;
		default:
			break;
		}
	}

	bool CBuiltInMonthCalendar::UpdateHoveredItem()
	{
		return UpdateHoveredItem(getControl()->FormToLocal((PointF)getControl()->getForm()->ScreenToClient(Application->Mouse->getPosition())) - getPosition());
	}

	bool CBuiltInMonthCalendar::UpdateHoveredItem(const PointF &pos)
	{
		if (m_hTimerAnimate)
			return false;
		ElementType el{ ElementType::None };
		bool changed{ false };
		if (pos.X >= 0 && pos.X < getWidth() && pos.Y >= 0 && pos.Y < getHeight())
		{
			// Title
			if (pos.Y < m_sInfo.TitleSize.Y)
			{
				if (pos.X < m_sInfo.TitleSize.Y)
					el = ElementType::Prev;
				else if (pos.X >= getWidth() - m_sInfo.TitleSize.Y)
					el = ElementType::Next;
				else
					el = ElementType::Title;
			}
			// Today
			if (el == ElementType::None && m_bShowToday && pos.Y >= m_sInfo.TitleSize.Y + m_sInfo.ElementsSize.Y)
				el = ElementType::Today;
			// Element
			if (el == ElementType::None && pos.Y >= m_sInfo.TitleSize.Y && pos.Y < m_sInfo.TitleSize.Y + m_sInfo.ElementsSize.Y)
			{
				Point p;
				switch (m_eMode)
				{
				case Mode::Month:
					p.X = int(pos.X / m_sInfo.DaySize.X);
					p.Y = int((pos.Y - m_sInfo.TitleSize.Y) / m_sInfo.DaySize.Y);
					if (p.X >= 0 && p.X < 7 && p.Y > 0 && p.Y < 7)
					{
						CDateTime first{ m_iPageYear, m_iPageMonth, 1, 0, 0, 0 };
						if (first.getDayOfWeek() > 0)
							first -= CInterval{ 0, 0, first.getDayOfWeek(), 0, 0, 0 };
						first += CInterval(0, 0, (p.Y - 1) * 7 + p.X, 0, 0, 0);
						if (m_iHoveredYear != first.getYear())
						{
							m_iHoveredYear = first.getYear();
							changed = true;
						}
						if (m_iHoveredMonth != first.getMonth())
						{
							m_iHoveredMonth = first.getMonth();
							changed = true;
						}
						if (m_iHoveredDay != first.getDay())
						{
							m_iHoveredDay = first.getDay();
							changed = true;
						}
						el = ElementType::Day;
					}
					break;
				case Mode::Year:
					p.X = int(pos.X / m_sInfo.ElementSize.X);
					p.Y = int((pos.Y - m_sInfo.TitleSize.Y) / m_sInfo.ElementSize.Y);
					if (p.X >= 0 && p.X < 4 && p.Y >= 0 && p.Y < 4)
					{
						if (m_iHoveredYear != m_iPageYear)
						{
							m_iHoveredYear = m_iPageYear;
							changed = true;
						}
						if (m_iHoveredMonth != p.Y * 4 + p.X + 1)
						{
							m_iHoveredMonth = p.Y * 4 + p.X + 1;
							changed = true;
						}
						m_iHoveredDay = 0;
						el = ElementType::Month;
					}
					break;
				case Mode::Decade:
					p.X = int(pos.X / m_sInfo.ElementSize.X);
					p.Y = int((pos.Y - m_sInfo.TitleSize.Y) / m_sInfo.ElementSize.Y);
					if (p.X >= 0 && p.X < 4 && p.Y >= 0 && p.Y < 4)
					{
						if (m_iHoveredYear != m_iPageYear - 1 + p.Y * 4 + p.X)
						{
							m_iHoveredYear = m_iPageYear - 1 + p.Y * 4 + p.X;
							changed = true;
						}
						m_iHoveredMonth = 0;
						m_iHoveredDay = 0;
						el = ElementType::Year;
					}
					break;
				case Mode::Century:
					p.X = int(pos.X / m_sInfo.ElementSize.X);
					p.Y = int((pos.Y - m_sInfo.TitleSize.Y) / m_sInfo.ElementSize.Y);
					if (p.X >= 0 && p.X < 4 && p.Y >= 0 && p.Y < 4)
					{
						if (m_iHoveredYear != m_iPageYear - 10 + (p.Y * 4 + p.X) * 10)
						{
							m_iHoveredYear = m_iPageYear - 10 + (p.Y * 4 + p.X) * 10;
							changed = true;
						}
						m_iHoveredMonth = 0;
						m_iHoveredDay = 0;
						el = ElementType::Decade;
					}
					break;
				}
			}
		}
		if (el != m_eHoveredElement || changed)
		{
			m_eHoveredElement = el;
			return true;
		}
		return false;
	}

	CBuiltInMonthCalendar::ElementState CBuiltInMonthCalendar::getDayState(const int year, const int month, const int day)
	{
		if (!isEnabled())
			return ElementState::Disabled;
		CDateTime date{ year, month, day, 0, 0, 0 };
		// Check out of constraints
		if (date < m_cMinDate)
			return ElementState::Disabled;
		if (date > m_cMaxDate)
			return ElementState::Disabled;
		// Check for active & today
		CDateTime today;
		if (year == today.getYear() && month == today.getMonth() && day == today.getDay())
		{
			if (year == m_cDate.getYear() && month == m_cDate.getMonth() && day == m_cDate.getDay())
			{
				if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
					return ElementState::TodayActiveHovered;
				return ElementState::TodayActive;
			}
			if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
				return ElementState::TodayHovered;
			return ElementState::Today;
		}
		if (year == m_cDate.getYear() && month == m_cDate.getMonth() && day == m_cDate.getDay())
		{
			if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
				return ElementState::ActiveHovered;
			return ElementState::Active;
		}
		// Check out of current range
		CDateTime start{ m_iPageYear, m_iPageMonth, 1, 0, 0, 0 }, end{ m_iPageYear, m_iPageMonth, CDateTime::getDaysInMonth(m_iPageYear, m_iPageMonth), 0, 0, 0 };
		if (date < start)
		{
			if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
				return ElementState::OtherRangeHovered;
			return ElementState::OtherRange;
		}
		if (date > end)
		{
			if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
				return ElementState::OtherRangeHovered;
			return ElementState::OtherRange;
		}
		// In range
		if (m_eHoveredElement == ElementType::Day && m_iHoveredYear == year && m_iHoveredMonth == month && m_iHoveredDay == day)
			return ElementState::Hovered;
		return ElementState::Normal;
	}

	CBuiltInMonthCalendar::ElementState CBuiltInMonthCalendar::getMonthState(const int year, const int month)
	{
		if (!isEnabled())
			return ElementState::Disabled;
		CDateTime date{ year, month, 1, 0, 0, 0 };
		if (date < m_cMinDate)
			return ElementState::Disabled;
		date.setDay(date.getDaysInMonth());
		if (date > m_cMaxDate)
			return ElementState::Disabled;
		CDateTime today;
		if (year == today.getYear() && month == today.getMonth())
		{
			if (year == m_cDate.getYear() && month == m_cDate.getMonth())
			{
				if (m_eHoveredElement == ElementType::Month && m_iHoveredYear == year && m_iHoveredMonth == month)
					return ElementState::TodayActiveHovered;
				return ElementState::TodayActive;
			}
			if (m_eHoveredElement == ElementType::Month && m_iHoveredYear == year && m_iHoveredMonth == month)
				return ElementState::TodayHovered;
			return ElementState::Today;
		}
		if (year == m_cDate.getYear() && month == m_cDate.getMonth())
		{
			if (m_eHoveredElement == ElementType::Month && m_iHoveredYear == year && m_iHoveredMonth == month)
				return ElementState::ActiveHovered;
			return ElementState::Active;
		}
		if (m_eHoveredElement == ElementType::Month && m_iHoveredYear == year && m_iHoveredMonth == month)
			return ElementState::Hovered;
		return ElementState::Normal;
	}

	CBuiltInMonthCalendar::ElementState CBuiltInMonthCalendar::getYearState(const int year)
	{
		if (!isEnabled())
			return ElementState::Disabled;
		CDateTime date{ year, CDateTime::January, 1, 0, 0, 0 };
		if (date < m_cMinDate)
			return ElementState::Disabled;
		date.setMonth(CDateTime::December);
		date.setDay(date.getDaysInMonth());
		if (date > m_cMaxDate)
			return ElementState::Disabled;
		CDateTime today;
		if (year == today.getYear())
		{
			if (year == m_cDate.getYear())
			{
				if (m_eHoveredElement == ElementType::Year && m_iHoveredYear == year)
					return ElementState::TodayActiveHovered;
				return ElementState::TodayActive;
			}
			if (m_eHoveredElement == ElementType::Year && m_iHoveredYear == year)
				return ElementState::TodayHovered;
			return ElementState::Today;
		}
		if (year == m_cDate.getYear())
		{
			if (m_eHoveredElement == ElementType::Year && m_iHoveredYear == year)
				return ElementState::ActiveHovered;
			return ElementState::Active;
		}
		if (year < m_iPageYear || year >= m_iPageYear + 10)
		{
			if (m_eHoveredElement == ElementType::Year && m_iHoveredYear == year)
				return ElementState::OtherRangeHovered;
			return ElementState::OtherRange;
		}
		if (m_eHoveredElement == ElementType::Year && m_iHoveredYear == year)
			return ElementState::Hovered;
		return ElementState::Normal;
	}

	CBuiltInMonthCalendar::ElementState CBuiltInMonthCalendar::getDecadeState(const int year)
	{
		if (!isEnabled())
			return ElementState::Disabled;
		int year_min{ year - year % 10 }, year_max{ year + 10 };
		CDateTime date{ year, CDateTime::January, 1, 0, 0, 0 };
		if (date < m_cMinDate)
			return ElementState::Disabled;
		date.setDate(year, CDateTime::December, 31);
		if (date > m_cMaxDate)
			return ElementState::Disabled;
		if (year_min < m_iPageYear || year_max > m_iPageYear + 100)
		{
			if (m_eHoveredElement == ElementType::Decade && m_iHoveredYear == year_min)
				return ElementState::OtherRangeHovered;
			return ElementState::OtherRange;
		}
		CDateTime today;
		if (today.getYear() >= year_min && today.getYear() < year_max)
		{
			if (m_cDate.getYear() >= year_min && m_cDate.getYear() < year_max)
			{
				if (m_eHoveredElement == ElementType::Decade && m_iHoveredYear == year_min)
					return ElementState::TodayActiveHovered;
				return ElementState::TodayActive;
			}
			if (m_eHoveredElement == ElementType::Decade && m_iHoveredYear == year_min)
				return ElementState::TodayHovered;
			return ElementState::Today;
		}
		if (m_cDate.getYear() >= year_min && m_cDate.getYear() < year_max)
		{
			if (m_eHoveredElement == ElementType::Decade && m_iHoveredYear == year_min)
				return ElementState::ActiveHovered;
			return ElementState::Active;
		}
		if (m_eHoveredElement == ElementType::Decade && m_iHoveredYear == year_min)
			return ElementState::Hovered;
		return ElementState::Normal;
	}

	CBuiltInMonthCalendar::TitleState CBuiltInMonthCalendar::getPrevRangeState()
	{
		if (!isEnabled())
			return TitleState::Disabled;
		switch (m_eMode)
		{
		case Mode::Month:
		{
			CDateTime date{ m_iPageYear, m_iPageMonth, 1, 0, 0, 0 };
			if (date.getDayOfWeek() > 0)
				date -= CInterval{ 0, 0, date.getDayOfWeek(), 0, 0, 0 };
			if (date <= m_cMinDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Year:
		{
			CDateTime date{ m_iPageYear, CDateTime::January, 1, 0, 0, 0 };
			if (date <= m_cMinDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Decade:
		{
			CDateTime date{ m_iPageYear - 1, CDateTime::January, 1, 0, 0, 0 };
			if (date <= m_cMinDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Century:
		{
			CDateTime date{ m_iPageYear - 10, CDateTime::January, 1, 0, 0, 0 };
			if (date <= m_cMinDate)
				return TitleState::Disabled;
			break;
		}
		}
		if (m_eDownElement == ElementType::Prev)
		{
			if (m_eHoveredElement == ElementType::Prev)
				return TitleState::ActiveHovered;
			return TitleState::Active;
		}
		if (m_eHoveredElement == ElementType::Prev)
			return TitleState::Hovered;
		return TitleState::Normal;
	}

	CBuiltInMonthCalendar::TitleState CBuiltInMonthCalendar::getNextRangeState()
	{
		if (!isEnabled())
			return TitleState::Disabled;
		switch (m_eMode)
		{
		case Mode::Month:
		{
			CDateTime date{ m_iPageYear, m_iPageMonth, 1, 0, 0, 0 };
			if (date.getDayOfWeek() > 0)
				date -= CInterval{ 0, 0, date.getDayOfWeek(), 0, 0, 0 };
			date += CInterval{ 0, 0, 42, 0, 0, 0 };
			if (date >= m_cMaxDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Year:
		{
			CDateTime date{ m_iPageYear, CDateTime::December, 1, 0, 0, 0 };
			if (date >= m_cMaxDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Decade:
		{
			CDateTime date{ m_iPageYear + 11, CDateTime::December, 1, 0, 0, 0 };
			if (date >= m_cMaxDate)
				return TitleState::Disabled;
			break;
		}
		case Mode::Century:
		{
			CDateTime date{ m_iPageYear + 110, CDateTime::December, 1, 0, 0, 0 };
			if (date >= m_cMaxDate)
				return TitleState::Disabled;
			break;
		}
		}
		if (m_eDownElement == ElementType::Next)
		{
			if (m_eHoveredElement == ElementType::Next)
				return TitleState::ActiveHovered;
			return TitleState::Active;
		}
		if (m_eHoveredElement == ElementType::Next)
			return TitleState::Hovered;
		return TitleState::Normal;
	}

	CBuiltInMonthCalendar::TitleState CBuiltInMonthCalendar::getTitleState()
	{
		if (!isEnabled())
			return TitleState::Disabled;
		if (m_eMode == Mode::Century)
			return TitleState::Normal;
		if (m_eDownElement == ElementType::Prev || m_eDownElement == ElementType::Next)
		{
			if (m_eHoveredElement == ElementType::Title)
				return TitleState::ActiveHovered;
			return TitleState::Active;
		}
		if (m_eHoveredElement == ElementType::Title)
			return TitleState::Hovered;
		return TitleState::Normal;
	}

	CBuiltInMonthCalendar::TitleState CBuiltInMonthCalendar::getTodayState()
	{
		if (!isEnabled())
			return TitleState::Disabled;
		if (m_eDownElement == ElementType::Today)
		{
			if (m_eHoveredElement == ElementType::Today)
				return TitleState::ActiveHovered;
			return TitleState::Active;
		}
		if (m_eHoveredElement == ElementType::Today)
			return TitleState::Hovered;
		return TitleState::Normal;
	}

	CBuiltInMonthCalendar::DayTitleState CBuiltInMonthCalendar::getDayTitleState()
	{
		if (!isEnabled())
			return DayTitleState::Disabled;
		return DayTitleState::Normal;
	}
#pragma endregion

#pragma region Paint
	void CBuiltInMonthCalendar::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && PrepareRendering())
		{
			if (m_hTimerAnimate)
			{
				RenderAnimation(matrix, block);
				return;
			}
			if (PrepareCanvas(m_sInfo.Renderer, &m_pCanvas, getSize()))
			{
				CStoreTarget s_target{ m_sInfo.Renderer };
				m_sInfo.Renderer->ActivateTarget(m_pCanvas);
				m_sInfo.Renderer->Clear(Color{ 0, 0, 0, 0 });
				RenderTitle(m_iPageYear, m_iPageMonth);
				switch (m_eMode)
				{
				case Mode::Month:
					RenderModeMonth(m_iPageYear, m_iPageMonth);
					break;
				case Mode::Year:
					RenderModeYear(m_iPageYear);
					break;
				case Mode::Decade:
					RenderModeDecade(m_iPageYear);
					break;
				case Mode::Century:
					RenderModeCentury(m_iPageYear);
					break;
				}
				if (m_bShowToday)
					RenderToday();
				m_pCanvas->setValid(true);
			}
			DrawCanvas(m_sInfo.Renderer, matrix, m_pCanvas, PointF{ 0, 0 });
		}
	}

	void CBuiltInMonthCalendar::RenderAnimation(const Mat4f &matrix, const Block *block)
	{
		CStoreBlock s_block{ m_sInfo.Renderer };
		CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
		float elapsed{ (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_sAnimationStart).count() * 0.001f };
		float factor{ ntl::Min<float>(1.0f, elapsed / m_fAnimateTime) }, t1{ 1 }, t2{ 1 }, s;
		m_sInfo.Renderer
			->ActivateBlock(block)
			->ActivatePrimitiveMatrix(matrix)
			->DrawImage(m_pCanvas, 1);
		Mat4f m1, m2, x1, x2;
		switch (m_eAnimateType)
		{
		case AnimateType::SlideLeft:
			ntl::Translate<float>(m1, -factor * getWidth(), 0, 0);
			ntl::Translate<float>(m2, (1 - factor) * getWidth(), 0, 0);
			break;
		case AnimateType::SlideRight:
			ntl::Translate<float>(m1, factor * getWidth(), 0, 0);
			ntl::Translate<float>(m2, (factor - 1) * getWidth(), 0, 0);
			break;
		case AnimateType::Fade:
			s = 1 - factor * (1 - m_fAnimateMinScale);
			ntl::Scale<float>(m1, s, s, 1);
			s = 1 - (1 - factor) * (1 - m_fAnimateMinScale);
			ntl::Scale<float>(m2, s, s, 1);
			ntl::Translate<float>(x1, float(-m_pCanvas1->Width) * 0.5f, float(-m_pCanvas1->Height) * 0.5f, 0);
			ntl::Translate<float>(x2, (float)m_pCanvas1->Width * 0.5f, (float)m_pCanvas1->Height * 0.5f, 0);
			m1 = x2 * m1 * x1;
			m2 = x2 * m2 * x1;
			t1 = 1 - factor;
			t2 = factor;
			break;
		}
		m_sInfo.Renderer
			->ActivatePrimitiveMatrix(matrix * m1)
			->DrawImage(m_pCanvas1, t1)
			->ActivatePrimitiveMatrix(matrix * m2)
			->DrawImage(m_pCanvas2, t2);
	}

	void CBuiltInMonthCalendar::RenderTitle(const int page_year, const int page_month)
	{
		TitleState state{ getTitleState() };
		// Background
		DrawSimpleBackground(
			m_sInfo.Renderer,
			RectF{ 0, 0, m_sInfo.TitleSize.X, m_sInfo.TitleSize.Y },
			m_aTitleBorderWidth[(int)state],
			m_aTitleBorderRadius[(int)state], 
			m_aTitleBorderColor[(int)state],
			m_aTitleBackgroundColor[(int)state],
			m_aTitleBackgroundGradient[(int)state]);
		// Title
		Color color{ m_aTitleColor[(int)state].A > 0 ? m_aTitleColor[(int)state] : m_sInfo.Font->Color };
		if (color.A > 0)
		{
			String title;
			switch (m_eMode)
			{
			case Mode::Month:
				title = CTranslate::Month(months::Names[page_month - 1]) + L" " + ToString(page_year);
				break;
			case Mode::Year:
				title = ToString(page_year);
				break;
			case Mode::Decade:
				title = ToString(page_year) + L"-" + ToString(page_year + 10);
				break;
			case Mode::Century:
				title = ToString(page_year) + L"-" + ToString(page_year + 100);
				break;
			}
			if (!title.empty())
			{
				PointF size{ m_sInfo.PlatformFont->getStringSize(title, m_sInfo.Distance) };
				float x;
				switch (m_aTitleAlign[(int)state])
				{
				case TextAlign::Right:
					x = m_sInfo.ElementsSize.X - m_sInfo.TitleSize.Y - m_sTitlePadding.Right - size.X;
					break;
				case TextAlign::Center:
					x = (m_sInfo.ElementsSize.X - size.X) * 0.5f;
					break;
				default:
					x = m_sInfo.TitleSize.Y + m_sTitlePadding.Left;
				}
				CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
				m_sInfo.Renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x), std::round(m_sTitlePadding.Top), 0))
					->DrawText(title, m_sInfo.PlatformFont, m_sInfo.Distance, color);
			}
		}
		// Previous range
		RectF r{ 0, 0, m_sInfo.TitleSize.Y, m_sInfo.TitleSize.Y };
		state = getPrevRangeState();
		DrawSimpleBackground(
			m_sInfo.Renderer,
			r,
			m_aTitlePrevRangeBorderWidth[(int)state],
			m_aTitlePrevRangeBorderRadius[(int)state],
			m_aTitlePrevRangeBorderColor[(int)state],
			m_aTitlePrevRangeBackgroundColor[(int)state],
			m_aTitlePrevRangeBackgroundGradient[(int)state]);
		r.Left += m_aTitlePrevRangePadding[(int)state].Left;
		r.Top += m_aTitlePrevRangePadding[(int)state].Top;
		r.Right -= m_aTitlePrevRangePadding[(int)state].Right;
		r.Bottom -= m_aTitlePrevRangePadding[(int)state].Bottom;
		if (r.is_valid() && !r.is_zero() && (m_aTitlePrevRangeColor1[(int)state].A > 0 || m_aTitlePrevRangeColor2[(int)state].A > 0 || m_aTitlePrevRangeColor3[(int)state].A > 0))
		{
			m_sInfo.Renderer->DrawTriangle(PointF{ r.Right, r.Bottom }, PointF{ r.Left, (r.Top + r.Bottom) * 0.5f }, PointF{ r.Right, r.Top },
				m_aTitlePrevRangeColor1[(int)state], m_aTitlePrevRangeColor2[(int)state], m_aTitlePrevRangeColor3[(int)state]);
		}
		// Next range
		r = RectF{ m_sInfo.ElementsSize.X - m_sInfo.TitleSize.Y, 0, m_sInfo.ElementsSize.X, m_sInfo.TitleSize.Y };
		state = getNextRangeState();
		DrawSimpleBackground(
			m_sInfo.Renderer,
			r,
			m_aTitleNextRangeBorderWidth[(int)state],
			m_aTitleNextRangeBorderRadius[(int)state],
			m_aTitleNextRangeBorderColor[(int)state],
			m_aTitleNextRangeBackgroundColor[(int)state],
			m_aTitleNextRangeBackgroundGradient[(int)state]);
		r.Left += m_aTitleNextRangePadding[(int)state].Left;
		r.Top += m_aTitleNextRangePadding[(int)state].Top;
		r.Right -= m_aTitleNextRangePadding[(int)state].Right;
		r.Bottom -= m_aTitleNextRangePadding[(int)state].Bottom;
		if (r.is_valid() && !r.is_zero() && (m_aTitleNextRangeColor1[(int)state].A > 0 || m_aTitleNextRangeColor2[(int)state].A > 0 || m_aTitleNextRangeColor3[(int)state].A > 0))
		{
			m_sInfo.Renderer->DrawTriangle(PointF{ r.Left, r.Top }, PointF{ r.Right, (r.Top + r.Bottom) * 0.5f }, PointF{ r.Left, r.Bottom },
				m_aTitleNextRangeColor1[(int)state], m_aTitleNextRangeColor2[(int)state], m_aTitleNextRangeColor3[(int)state]);
		}
	}

	void CBuiltInMonthCalendar::RenderToday()
	{
		TitleState state{ getTodayState() };
		// Background
		RectF r{ 0, m_sInfo.TitleSize.Y + m_sInfo.ElementsSize.Y, m_sInfo.ElementsSize.X, m_sInfo.TitleSize.Y + m_sInfo.ElementsSize.Y + m_sInfo.TodaySize.Y };
		DrawSimpleBackground(
			m_sInfo.Renderer,
			r,
			m_aTodayBorderWidth[(int)state],
			m_aTodayBorderRadius[(int)state],
			m_aTodayBorderColor[(int)state],
			m_aTodayBackgroundColor[(int)state],
			m_aTodayBackgroundGradient[(int)state]);
		// Title
		CDateTime today;
		String day{ (today.getDay() < 10 ? L"0" : L"") + ToString(today.getDay()) };
		String month{ (today.getMonth() < 10 ? L"0" : L"") + ToString(today.getMonth()) };
		String year{ (today.getYear() < 1000 ? L"0" : L"") + ToString(today.getYear()) };
		String title{ CTranslate::Day(days::Today) + L": " + day + L"." + month + L"." + year };
		PointF title_size{ m_sInfo.PlatformFont->getStringSize(title, m_sInfo.Distance) };
		float x;
		switch (m_aTodayAlign[(int)state])
		{
		case TextAlign::Right:
			x = m_sInfo.ElementsSize.X - m_sTodayPadding.Right - title_size.X;
			break;
		case TextAlign::Center:
			if (ntl::IsGreater<float>(m_fTodayRectWidth, 0))
				x = m_sTodayPadding.Left + (m_sInfo.ElementsSize.X - m_sTodayPadding.Left - m_sTodayPadding.Right - title_size.X - m_fTodayMargin - m_fTodayRectWidth) * 0.5f + m_fTodayRectWidth + m_fTodayMargin;
			else
				x = m_sTodayPadding.Left + (m_sInfo.ElementsSize.X - m_sTodayPadding.Left - m_sTodayPadding.Right - title_size.X) * 0.5f;
			break;
		default:
			x = m_sTodayPadding.Left;
		}
		Color color{ m_aTodayColor[(int)state].A > 0 ? m_aTodayColor[(int)state] : m_sInfo.Font->Color };
		if (color.A > 0)
		{
			CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
			m_sInfo.Renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x), std::round(r.Top + m_sTodayPadding.Top), 0))
				->DrawText(title, m_sInfo.PlatformFont, m_sInfo.Distance, color);
		}
		if (ntl::IsGreater<float>(m_fTodayRectWidth, 0))
		{
			r.Top += m_sTodayPadding.Top;
			r.Bottom -= m_sTodayPadding.Bottom;
			switch (m_aTodayAlign[(int)state])
			{
			case TextAlign::Right:
			case TextAlign::Center:
				r.Left = x - m_fTodayMargin - m_fTodayRectWidth;
				break;
			default:
				r.Left = x + title_size.X + m_fTodayMargin;
			}
			r.Right = r.Left + m_fTodayRectWidth;
			if (r.is_valid() && !r.is_zero())
			{
				DrawSimpleBackground(
					m_sInfo.Renderer,
					r,
					m_aTodayRectBorderWidth[(int)state],
					m_aTodayRectBorderRadius[(int)state],
					m_aTodayRectBorderColor[(int)state],
					m_aTodayRectBackgroundColor[(int)state],
					m_aTodayRectBackgroundGradient[(int)state]);
			}
		}
	}

	void CBuiltInMonthCalendar::RenderModeMonth(const int page_year, const int page_month)
	{
		// Day of week
		DayTitleState state_title{ getDayTitleState() };
		RectF rect{ 0, m_sInfo.TitleSize.Y, m_sInfo.DaySize.X, m_sInfo.TitleSize.Y + m_sInfo.DaySize.Y };
		PointF pos, size;
		Color color;
		String text;
		for (int i = 0; i < (int)days::ShortNames.size(); i++)
		{
			DrawSimpleBackground(
				m_sInfo.Renderer,
				rect,
				m_aDayTitleBorderWidth[(int)state_title],
				m_aDayTitleBorderRadius[(int)state_title],
				m_aDayTitleBorderColor[(int)state_title],
				m_aDayTitleBackgroundColor[(int)state_title],
				m_aDayTitleBackgroundGradient[(int)state_title]);
			color = m_aDayTitleColor[(int)state_title].A > 0 ? m_aDayTitleColor[(int)state_title] : m_sInfo.Font->Color;
			if (color.A > 0)
			{
				text = CTranslate::Day(days::ShortNames[i]);
				size = m_sInfo.PlatformFont->getStringSize(text, m_sInfo.Distance);
				switch (m_aDayTitleHorizontalAlign[(int)state_title])
				{
				case TextAlign::Right:
					pos.X = rect.Right - size.X - m_sDayPadding.Right;
					break;
				case TextAlign::Center:
					pos.X = rect.Left + m_sDayPadding.Left + (rect.width() - m_sDayPadding.Left - m_sDayPadding.Right - size.X) * 0.5f;
					break;
				default:
					pos.X = rect.Left + m_sDayPadding.Left;
				}
				switch (m_aDayTitleVerticalAlign[(int)state_title])
				{
				case VerticalAlign::Bottom:
					pos.Y = rect.Bottom - size.Y - m_sDayPadding.Bottom;
					break;
				case VerticalAlign::Middle:
					pos.Y = rect.Top + m_sDayPadding.Top + (rect.height() - m_sDayPadding.Top - m_sDayPadding.Bottom - size.Y) * 0.5f;
					break;
				default:
					pos.Y = rect.Top + m_sDayPadding.Top;
				}
				CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
				m_sInfo.Renderer
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
					->DrawText(text, m_sInfo.PlatformFont, m_sInfo.Distance, color);
			}
			rect.Left += m_sInfo.DaySize.X;
			rect.Right += m_sInfo.DaySize.X;
		}
		// Days
		CDateTime date{ page_year, page_month, 1, 0, 0, 0 };
		if (date.getDayOfWeek() > 0)
			date -= CInterval(0, 0, date.getDayOfWeek(), 0, 0, 0);
		rect.Top = m_sInfo.TitleSize.Y + m_sInfo.DaySize.Y;
		rect.Bottom = rect.Top + m_sInfo.DaySize.Y;
		for (int y = 0; y < 6; y++)
		{
			rect.Left = 0;
			rect.Right = rect.Left + m_sInfo.DaySize.X;
			for (int x = 0; x < 7; x++)
			{
				ElementState state{ getDayState(date.getYear(), date.getMonth(), date.getDay()) };
				DrawSimpleBackground(
					m_sInfo.Renderer,
					rect,
					m_aElementBorderWidth[(int)state],
					m_aElementBorderRadius[(int)state],
					m_aElementBorderColor[(int)state],
					m_aElementBackgroundColor[(int)state],
					m_aElementBackgroundGradient[(int)state]);
				color = m_aElementColor[(int)state].A > 0 ? m_aElementColor[(int)state] : m_sInfo.Font->Color;
				if (color.A > 0)
				{
					text = ToString(date.getDay());
					size = m_sInfo.PlatformFont->getStringSize(text, m_sInfo.Distance);
					switch (m_aElementHorizontalAlign[(int)state])
					{
					case TextAlign::Right:
						pos.X = rect.Right - size.X - m_sDayPadding.Right;
						break;
					case TextAlign::Center:
						pos.X = rect.Left + m_sDayPadding.Left + (rect.width() - m_sDayPadding.Left - m_sDayPadding.Right - size.X) * 0.5f;
						break;
					default:
						pos.X = rect.Left + m_sDayPadding.Left;
					}
					switch (m_aElementVerticalAlign[(int)state])
					{
					case VerticalAlign::Bottom:
						pos.Y = rect.Bottom - size.Y - m_sDayPadding.Bottom;
						break;
					case VerticalAlign::Middle:
						pos.Y = rect.Top + m_sDayPadding.Top + (rect.height() - m_sDayPadding.Top - m_sDayPadding.Bottom - size.Y) * 0.5f;
						break;
					default:
						pos.Y = rect.Top + m_sDayPadding.Top;
					}
					CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
					m_sInfo.Renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawText(text, m_sInfo.PlatformFont, m_sInfo.Distance, color);
				}
				if (m_aElementOutlineMask[(int)state] != 0 && m_aElementOutlineColor[(int)state].A > 0)
				{
					RectF r{
						rect.Left + m_aElementBorderWidth[(int)state].Left,
						rect.Top + m_aElementBorderWidth[(int)state].Top,
						rect.Right - m_aElementBorderWidth[(int)state].Right,
						rect.Bottom - m_aElementBorderWidth[(int)state].Bottom };
					if (r.is_valid() && !r.is_zero())
					{
						CStoreBitmask s_bitmask{ m_sInfo.Renderer };
						m_sInfo.Renderer
							->ActivateBitmask(Bitmask{ m_aElementOutlineMask[(int)state], 0, true, false })
							->DrawLines(
								{ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom - 1 }, PointF{ r.Left + 1, r.Bottom - 1 }, PointF{ r.Left + 1, r.Top } },
								m_aElementOutlineColor[(int)state], false);
					}
				}
				rect.Left += m_sInfo.DaySize.X;
				rect.Right += m_sInfo.DaySize.X;
				date += CInterval{ 0, 0, 1, 0, 0, 0 };
			}
			rect.Top += m_sInfo.DaySize.Y;
			rect.Bottom += m_sInfo.DaySize.Y;
		}
	}

	void CBuiltInMonthCalendar::RenderModeYear(const int page_year)
	{
		CDateTime date{ page_year, CDateTime::January, 1, 0, 0, 0 };
		RectF rect;
		rect.Top = m_sInfo.TitleSize.Y;
		rect.Bottom = rect.Top + m_sInfo.ElementSize.Y;
		for (int y = 0; y < 3; y++)
		{
			rect.Left = 0;
			rect.Right = rect.Left + m_sInfo.ElementSize.X;
			for (int x = 0; x < 4; x++)
			{
				ElementState state{ getMonthState(date.getYear(), date.getMonth()) };
				DrawSimpleBackground(
					m_sInfo.Renderer,
					rect,
					m_aElementBorderWidth[(int)state],
					m_aElementBorderRadius[(int)state],
					m_aElementBorderColor[(int)state],
					m_aElementBackgroundColor[(int)state],
					m_aElementBackgroundGradient[(int)state]);
				Color color{ m_aElementColor[(int)state].A > 0 ? m_aElementColor[(int)state] : m_sInfo.Font->Color };
				if (color.A > 0)
				{
					String text{ CTranslate::Month(months::ShortNames[y * 4 + x]) };
					PointF size{ m_sInfo.PlatformFont->getStringSize(text, m_sInfo.Distance) }, pos;
					switch (m_aElementHorizontalAlign[(int)state])
					{
					case TextAlign::Right:
						pos.X = rect.Right - size.X - m_sElementPadding.Right;
						break;
					case TextAlign::Center:
						pos.X = rect.Left + m_sElementPadding.Left + (rect.width() - m_sElementPadding.Left - m_sElementPadding.Right - size.X) * 0.5f;
						break;
					default:
						pos.X = rect.Left + m_sElementPadding.Left;
					}
					switch (m_aElementVerticalAlign[(int)state])
					{
					case VerticalAlign::Bottom:
						pos.Y = rect.Bottom - size.Y - m_sElementPadding.Bottom;
						break;
					case VerticalAlign::Middle:
						pos.Y = rect.Top + m_sElementPadding.Top + (rect.height() - m_sElementPadding.Top - m_sElementPadding.Bottom - size.Y) * 0.5f;
						break;
					default:
						pos.Y = rect.Top + m_sElementPadding.Top;
					}
					CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
					m_sInfo.Renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawText(text, m_sInfo.PlatformFont, m_sInfo.Distance, color);
				}
				if (m_aElementOutlineMask[(int)state] != 0 && m_aElementOutlineColor[(int)state].A > 0)
				{
					RectF r{
						rect.Left + m_aElementBorderWidth[(int)state].Left,
						rect.Top + m_aElementBorderWidth[(int)state].Top,
						rect.Right - m_aElementBorderWidth[(int)state].Right,
						rect.Bottom - m_aElementBorderWidth[(int)state].Bottom };
					if (r.is_valid() && !r.is_zero())
					{
						CStoreBitmask s_bitmask{ m_sInfo.Renderer };
						m_sInfo.Renderer
							->ActivateBitmask(Bitmask{ m_aElementOutlineMask[(int)state] , 0, true, false })
							->DrawLines(
								{ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom - 1 }, PointF{ r.Left + 1, r.Bottom - 1 }, PointF{ r.Left + 1, r.Top } },
								m_aElementOutlineColor[(int)state], false);
					}
				}
				rect.Left += m_sInfo.ElementSize.X;
				rect.Right += m_sInfo.ElementSize.X;
				date += CInterval{ 0, 1, 0, 0, 0, 0 };
			}
			rect.Top += m_sInfo.ElementSize.Y;
			rect.Bottom += m_sInfo.ElementSize.Y;
		}
	}

	void CBuiltInMonthCalendar::RenderModeDecade(const int page_year)
	{
		CDateTime date{ page_year - 1, CDateTime::January, 1, 0, 0, 0 };
		RectF rect;
		rect.Top = m_sInfo.TitleSize.Y;
		rect.Bottom = rect.Top + m_sInfo.ElementSize.Y;
		for (int y = 0; y < 3; y++)
		{
			rect.Left = 0;
			rect.Right = rect.Left + m_sInfo.ElementSize.X;
			for (int x = 0; x < 4; x++)
			{
				ElementState state{ getYearState(date.getYear()) };
				DrawSimpleBackground(
					m_sInfo.Renderer,
					rect,
					m_aElementBorderWidth[(int)state],
					m_aElementBorderRadius[(int)state],
					m_aElementBorderColor[(int)state],
					m_aElementBackgroundColor[(int)state],
					m_aElementBackgroundGradient[(int)state]);
				Color color{ m_aElementColor[(int)state].A > 0 ? m_aElementColor[(int)state] : m_sInfo.Font->Color };
				if (color.A > 0)
				{
					String text{ ToString(date.getYear()) };
					PointF size{ m_sInfo.PlatformFont->getStringSize(text, m_sInfo.Distance) }, pos;
					switch (m_aElementHorizontalAlign[(int)state])
					{
					case TextAlign::Right:
						pos.X = rect.Right - size.X - m_sElementPadding.Right;
						break;
					case TextAlign::Center:
						pos.X = rect.Left + m_sElementPadding.Left + (rect.width() - m_sElementPadding.Left - m_sElementPadding.Right - size.X) * 0.5f;
						break;
					default:
						pos.X = rect.Left + m_sElementPadding.Left;
					}
					switch (m_aElementVerticalAlign[(int)state])
					{
					case VerticalAlign::Bottom:
						pos.Y = rect.Bottom - size.Y - m_sElementPadding.Bottom;
						break;
					case VerticalAlign::Middle:
						pos.Y = rect.Top + m_sElementPadding.Top + (rect.height() - m_sElementPadding.Top - m_sElementPadding.Bottom - size.Y) * 0.5f;
						break;
					default:
						pos.Y = rect.Top + m_sElementPadding.Top;
					}
					CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
					m_sInfo.Renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawText(text, m_sInfo.PlatformFont, m_sInfo.Distance, color);
				}
				if (m_aElementOutlineMask[(int)state] != 0 && m_aElementOutlineColor[(int)state].A > 0)
				{
					RectF r{
						rect.Left + m_aElementBorderWidth[(int)state].Left,
						rect.Top + m_aElementBorderWidth[(int)state].Top,
						rect.Right - m_aElementBorderWidth[(int)state].Right,
						rect.Bottom - m_aElementBorderWidth[(int)state].Bottom };
					if (r.is_valid() && !r.is_zero())
					{
						CStoreBitmask s_bitmask{ m_sInfo.Renderer };
						m_sInfo.Renderer
							->ActivateBitmask(Bitmask{ m_aElementOutlineMask[(int)state] , 0, true, false })
							->DrawLines(
								{ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom - 1 }, PointF{ r.Left + 1, r.Bottom - 1 }, PointF{ r.Left + 1, r.Top } },
								m_aElementOutlineColor[(int)state], false);
					}
				}
				rect.Left += m_sInfo.ElementSize.X;
				rect.Right += m_sInfo.ElementSize.X;
				date.setYear(date.getYear() + 1);
			}
			rect.Top += m_sInfo.ElementSize.Y;
			rect.Bottom += m_sInfo.ElementSize.Y;
		}
	}

	void CBuiltInMonthCalendar::RenderModeCentury(const int page_year)
	{
		CDateTime date{ page_year - 10, CDateTime::January, 1, 0, 0, 0 };
		RectF rect;
		rect.Top = m_sInfo.TitleSize.Y;
		rect.Bottom = rect.Top + m_sInfo.ElementSize.Y;
		for (int y = 0; y < 3; y++)
		{
			rect.Left = 0;
			rect.Right = rect.Left + m_sInfo.ElementSize.X;
			for (int x = 0; x < 4; x++)
			{
				ElementState state{ getDecadeState(date.getYear()) };
				DrawSimpleBackground(
					m_sInfo.Renderer,
					rect,
					m_aElementBorderWidth[(int)state],
					m_aElementBorderRadius[(int)state],
					m_aElementBorderColor[(int)state],
					m_aElementBackgroundColor[(int)state],
					m_aElementBackgroundGradient[(int)state]);
				Color color{ m_aElementColor[(int)state].A > 0 ? m_aElementColor[(int)state] : m_sInfo.Font->Color };
				if (color.A > 0)
				{
					String text{ ToString(date.getYear()) + L"-" };
					PointF size{ m_sInfo.PlatformFont->getStringSize(text, m_sInfo.Distance) }, pos;
					switch (m_aElementHorizontalAlign[(int)state])
					{
					case TextAlign::Right:
						pos.X = rect.Right - size.X - m_sElementPadding.Right;
						break;
					case TextAlign::Center:
						pos.X = rect.Left + m_sElementPadding.Left + (rect.width() - m_sElementPadding.Left - m_sElementPadding.Right - size.X) * 0.5f;
						break;
					default:
						pos.X = rect.Left + m_sElementPadding.Left;
					}
					switch (m_aElementVerticalAlign[(int)state])
					{
					case VerticalAlign::Bottom:
						pos.Y = rect.Bottom - 2 * size.Y - m_sElementPadding.Bottom;
						break;
					case VerticalAlign::Middle:
						pos.Y = rect.Top + m_sElementPadding.Top + (rect.height() - m_sElementPadding.Top - m_sElementPadding.Bottom - 2 * size.Y) * 0.5f;
						break;
					default:
						pos.Y = rect.Top + m_sElementPadding.Top;
					}
					CStorePrimitiveMatrix s_matrix{ m_sInfo.Renderer };
					m_sInfo.Renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawText(text, m_sInfo.PlatformFont, m_sInfo.Distance, color);
					pos.Y += size.Y;
					m_sInfo.Renderer
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(pos.X), std::round(pos.Y), 0))
						->DrawText(ToString(date.getYear() + 10), m_sInfo.PlatformFont, m_sInfo.Distance, color);
				}
				if (m_aElementOutlineMask[(int)state] != 0 && m_aElementOutlineColor[(int)state].A > 0)
				{
					RectF r{
						rect.Left + m_aElementBorderWidth[(int)state].Left,
						rect.Top + m_aElementBorderWidth[(int)state].Top,
						rect.Right - m_aElementBorderWidth[(int)state].Right,
						rect.Bottom - m_aElementBorderWidth[(int)state].Bottom };
					if (r.is_valid() && !r.is_zero())
					{
						CStoreBitmask s_bitmask{ m_sInfo.Renderer };
						m_sInfo.Renderer
							->ActivateBitmask(Bitmask{ m_aElementOutlineMask[(int)state] , 0, true, false })
							->DrawLines(
								{ PointF{ r.Left, r.Top }, PointF{ r.Right, r.Top }, PointF{ r.Right, r.Bottom - 1 }, PointF{ r.Left + 1, r.Bottom - 1 }, PointF{ r.Left + 1, r.Top } },
								m_aElementOutlineColor[(int)state], false);
					}
				}
				rect.Left += m_sInfo.ElementSize.X;
				rect.Right += m_sInfo.ElementSize.X;
				date.setYear(date.getYear() + 10);
			}
			rect.Top += m_sInfo.ElementSize.Y;
			rect.Bottom += m_sInfo.ElementSize.Y;
		}
	}
#pragma endregion
}