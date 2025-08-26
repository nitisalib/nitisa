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
	#pragma region CTimerListener
		CTimePicker::CTimerListener::CTimerListener(CTimePicker *control) :
			m_pControl{ control }
		{

		}

		void CTimePicker::CTimerListener::NotifyOnTimer(const PlatformHandle id)
		{
			bool changed{ false };
			if (m_pControl->m_eDownElement == Element::UpArrow)
			{
				switch (m_pControl->m_eActiveElement)
				{
				case Element::Hours:
					changed = m_pControl->setTime(m_pControl->m_iHour + 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
					break;
				case Element::Minutes:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute + 1, m_pControl->m_iSecond);
					break;
				case Element::Seconds:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond + 1);
					break;
				default:
					break;
				}
			}
			else if (m_pControl->m_eDownElement == Element::DownArrow)
			{
				switch (m_pControl->m_eActiveElement)
				{
				case Element::Hours:
					changed = m_pControl->setTime(m_pControl->m_iHour - 1, m_pControl->m_iMinute, m_pControl->m_iSecond);
					break;
				case Element::Minutes:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute - 1, m_pControl->m_iSecond);
					break;
				case Element::Seconds:
					changed = m_pControl->setTime(m_pControl->m_iHour, m_pControl->m_iMinute, m_pControl->m_iSecond - 1);
					break;
				default:
					break;
				}
			}
			m_pControl->m_bFirstDigit = true;
			if (changed)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region CGradientListener
		CTimePicker::CGradientListener::CGradientListener(CTimePicker *control) :
			m_pControl{ control }
		{

		}

		void CTimePicker::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CTimePicker::CTimePicker():
			CControl(L"TimePicker", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_iHour{ 0 },
			m_iMinute{ 0 },
			m_iSecond{ 0 },
			m_iMinHour{ 0 },
			m_iMinMinute{ 0 },
			m_iMinSecond{ 0 },
			m_iMaxHour{ 23 },
			m_iMaxMinute{ 59 },
			m_iMaxSecond{ 59 },
			m_fTimerInterval{ ScrollInterval },
			m_bShowSeconds{ true },
			m_bShowArrows{ true },
			m_bArrowsAtRight{ true },
			m_eContentAlign{ TextAlign::Left },
			m_aShadowRadius{ 1, 1, 1, 1, 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aOuterBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aInnerBorderWidth{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aUpArrowBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aUpArrowOuterBorderWidth{
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 },
				RectF{ 1, 1, 1, 0 } },
			m_aUpArrowInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aUpArrowOuterBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } } },
			m_aUpArrowInnerBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 } } },
			m_aUpArrowBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 238, 238, 238, 255 } },
			m_aUpArrowBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aUpArrowPadding{
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 } },
			m_aUpArrowColor1{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aUpArrowColor2{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aUpArrowColor3{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aDownArrowBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aDownArrowOuterBorderWidth{
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 },
				RectF{ 1, 0, 1, 1 } },
			m_aDownArrowInnerBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 } },
			m_aDownArrowOuterBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } } },
			m_aDownArrowInnerBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 }, Color{ 60, 127, 177, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 }, Color{ 44, 98, 139, 255 } },
				BorderColor{ Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 }, Color{ 191, 191, 191, 255 } } },
			m_aDownArrowBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 238, 238, 238, 255 } },
			m_aDownArrowBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aDownArrowPadding{
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 },
				RectF{ 3, 1, 3, 1 } },
			m_aDownArrowColor1{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aDownArrowColor2{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aDownArrowColor3{
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 95, 110, 165, 255 },
				Color{ 159, 160, 165, 255 } },
			m_aArrowDistance{ 1, 1, 1, 1, 1, 1, 1 },
			m_aElementBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 32 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 32 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aElementBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aElementColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aPadding{ 2, 2, 2, 2, 2, 2, 2 },
			m_pCanvas{ nullptr },
			m_bIgnoreGradient{ true },
			m_eActiveElement{ Element::Hours },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_sDigitSize{ 0, 0 },
			m_fSeparatorWidth{ 0 },
			m_hTimer{ nullptr },
			m_bFirstDigit{ true },
			m_cTimerListener{ this }
		{
			OnChange = nullptr;
			setService(new CTimePickerService(this), true);

			m_aUpArrowBackgroundGradient[(int)State::Normal].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Focused].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::Focused].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Focused].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Focused].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::FocusedHovered].setPointCount(3);
			m_aUpArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPointCount(4);
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::Active].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::ActiveHovered].setPointCount(4);
			m_aUpArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aUpArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });

			m_aDownArrowBackgroundGradient[(int)State::Normal].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Normal].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Hovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Focused].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::Focused].setPoint(0, Color1D{ 0.0f, Color{ 242, 242, 242, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Focused].setPoint(1, Color1D{ 0.7f, Color{ 232, 232, 232, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Focused].setPoint(2, Color1D{ 1.0f, Color{ 209, 209, 209, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::FocusedHovered].setPointCount(3);
			m_aDownArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(0, Color1D{ 0.0f, Color{ 233, 236, 253, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(1, Color1D{ 0.7f, Color{ 210, 237, 252, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::FocusedHovered].setPoint(2, Color1D{ 1.0f, Color{ 169, 219, 245, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPointCount(4);
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::Active].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::ActiveHovered].setPointCount(4);
			m_aDownArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(0, Color1D{ 0.0f, Color{ 166, 199, 217, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(1, Color1D{ 0.3f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(2, Color1D{ 0.7f, Color{ 194, 228, 246, 255 } });
			m_aDownArrowBackgroundGradient[(int)State::ActiveHovered].setPoint(3, Color1D{ 1.0f, Color{ 145, 204, 235, 255 } });

			setSize(PointF{ 120, 21 });
			m_bIgnoreGradient = false;
		}

		CTimePicker::CTimePicker(IForm *parent) :CTimePicker()
		{
			setForm(parent);
		}

		CTimePicker::CTimePicker(IControl *parent) : CTimePicker()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CTimePicker::getRenderRect()
		{
			RectF result{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)State::Normal], m_aShadowShift[(int)State::Normal], m_aShadowRadius[(int)State::Normal]) };
			for (int i = (int)State::Normal + 1; i <= (int)State::Disabled; i++)
				result += AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CTimePicker::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aBorderRadius[i] *= avg;
					m_aOuterBorderWidth[i] *= s;
					m_aInnerBorderWidth[i] *= s;
					m_aUpArrowBorderRadius[i] *= avg;
					m_aUpArrowOuterBorderWidth[i] *= s;
					m_aUpArrowInnerBorderWidth[i] *= s;
					m_aUpArrowPadding[i] *= s;
					m_aDownArrowBorderRadius[i] *= avg;
					m_aDownArrowOuterBorderWidth[i] *= s;
					m_aDownArrowInnerBorderWidth[i] *= s;
					m_aDownArrowPadding[i] *= s;
					m_aArrowDistance[i] *= s.Y;
					m_aPadding[i] *= s.X;
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CTimePicker::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region ITimePicker getters
		int CTimePicker::getHour()
		{
			return m_iHour;
		}

		int CTimePicker::getMinute()
		{
			return m_iMinute;
		}

		int CTimePicker::getSecond()
		{
			return m_iSecond;
		}

		int CTimePicker::getMinHour()
		{
			return m_iMinHour;
		}

		int CTimePicker::getMinMinute()
		{
			return m_iMinMinute;
		}

		int CTimePicker::getMinSecond()
		{
			return m_iMinSecond;
		}

		int CTimePicker::getMaxHour()
		{
			return m_iMaxHour;
		}

		int CTimePicker::getMaxMinute()
		{
			return m_iMaxMinute;
		}

		int CTimePicker::getMaxSecond()
		{
			return m_iMaxSecond;
		}
	#pragma endregion

	#pragma region ITimePicker setters
		bool CTimePicker::setHour(const int value)
		{
			if (value >= 0 && value <= 23 && value != m_iHour && setTime(value, m_iMinute, m_iSecond))
			{
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::setMinute(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iMinute && setTime(m_iHour, value, m_iSecond))
			{
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::setSecond(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iSecond && setTime(m_iHour, m_iMinute, value))
			{
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::setMinHour(const int value)
		{
			if (value >= 0 && value <= 23 && value != m_iMinHour)
			{
				m_iMinHour = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setMinMinute(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iMinMinute)
			{
				m_iMinMinute = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setMinSecond(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iMinSecond)
			{
				m_iMinSecond = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setMaxHour(const int value)
		{
			if (value >= 0 && value <= 23 && value != m_iMaxHour)
			{
				m_iMaxHour = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setMaxMinute(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iMaxMinute)
			{
				m_iMaxMinute = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setMaxSecond(const int value)
		{
			if (value >= 0 && value <= 59 && value != m_iMaxSecond)
			{
				m_iMaxSecond = value;
				m_bFirstDigit = true;
				if (setTime(m_iHour, m_iMinute, m_iSecond))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CTimePicker::State CTimePicker::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement != Element::None)
			{
				if (isHovered())
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (isHovered())
					return State::FocusedHovered;
				return State::Focused;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		float CTimePicker::getTimerInterval() const
		{
			return m_fTimerInterval;
		}

		bool CTimePicker::isShowSeconds() const
		{
			return m_bShowSeconds;
		}

		bool CTimePicker::isShowArrows() const
		{
			return m_bShowArrows;
		}

		bool CTimePicker::isArrowsAtRight() const
		{
			return m_bArrowsAtRight;
		}

		TextAlign CTimePicker::getContentAlign() const
		{
			return m_eContentAlign;
		}

		int CTimePicker::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CTimePicker::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CTimePicker::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		RectF CTimePicker::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		RectF CTimePicker::getOuterBorderWidth(const State state) const
		{
			return m_aOuterBorderWidth[(int)state];
		}

		BorderColor CTimePicker::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		RectF CTimePicker::getInnerBorderWidth(const State state) const
		{
			return m_aInnerBorderWidth[(int)state];
		}

		BorderColor CTimePicker::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CTimePicker::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CTimePicker::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		RectF CTimePicker::getUpArrowBorderRadius(const State state) const
		{
			return m_aUpArrowBorderRadius[(int)state];
		}

		RectF CTimePicker::getUpArrowOuterBorderWidth(const State state) const
		{
			return m_aUpArrowOuterBorderWidth[(int)state];
		}

		RectF CTimePicker::getUpArrowInnerBorderWidth(const State state) const
		{
			return m_aUpArrowInnerBorderWidth[(int)state];
		}

		BorderColor CTimePicker::getUpArrowOuterBorderColor(const State state) const
		{
			return m_aUpArrowOuterBorderColor[(int)state];
		}

		BorderColor CTimePicker::getUpArrowInnerBorderColor(const State state) const
		{
			return m_aUpArrowInnerBorderColor[(int)state];
		}

		Color CTimePicker::getUpArrowBackgroundColor(const State state) const
		{
			return m_aUpArrowBackgroundColor[(int)state];
		}

		Gradient *CTimePicker::getUpArrowBackgroundGradient(const State state)
		{
			return &m_aUpArrowBackgroundGradient[(int)state];
		}

		RectF CTimePicker::getUpArrowPadding(const State state) const
		{
			return m_aUpArrowPadding[(int)state];
		}

		Color CTimePicker::getUpArrowColor1(const State state) const
		{
			return m_aUpArrowColor1[(int)state];
		}

		Color CTimePicker::getUpArrowColor2(const State state) const
		{
			return m_aUpArrowColor2[(int)state];
		}

		Color CTimePicker::getUpArrowColor3(const State state) const
		{
			return m_aUpArrowColor3[(int)state];
		}

		RectF CTimePicker::getDownArrowBorderRadius(const State state) const
		{
			return m_aDownArrowBorderRadius[(int)state];
		}

		RectF CTimePicker::getDownArrowOuterBorderWidth(const State state) const
		{
			return m_aDownArrowOuterBorderWidth[(int)state];
		}

		RectF CTimePicker::getDownArrowInnerBorderWidth(const State state) const
		{
			return m_aDownArrowInnerBorderWidth[(int)state];
		}

		BorderColor CTimePicker::getDownArrowOuterBorderColor(const State state) const
		{
			return m_aDownArrowOuterBorderColor[(int)state];
		}

		BorderColor CTimePicker::getDownArrowInnerBorderColor(const State state) const
		{
			return m_aDownArrowInnerBorderColor[(int)state];
		}

		Color CTimePicker::getDownArrowBackgroundColor(const State state) const
		{
			return m_aDownArrowBackgroundColor[(int)state];
		}

		Gradient *CTimePicker::getDownArrowBackgroundGradient(const State state)
		{
			return &m_aDownArrowBackgroundGradient[(int)state];
		}

		RectF CTimePicker::getDownArrowPadding(const State state) const
		{
			return m_aDownArrowPadding[(int)state];
		}

		Color CTimePicker::getDownArrowColor1(const State state) const
		{
			return m_aDownArrowColor1[(int)state];
		}

		Color CTimePicker::getDownArrowColor2(const State state) const
		{
			return m_aDownArrowColor2[(int)state];
		}

		Color CTimePicker::getDownArrowColor3(const State state) const
		{
			return m_aDownArrowColor3[(int)state];
		}

		float CTimePicker::getArrowDistance(const State state) const
		{
			return m_aArrowDistance[(int)state];
		}

		Color CTimePicker::getElementBackgroundColor(const State state) const
		{
			return m_aElementBackgroundColor[(int)state];
		}

		Gradient *CTimePicker::getElementBackgroundGradient(const State state)
		{
			return &m_aElementBackgroundGradient[(int)state];
		}

		Color CTimePicker::getElementColor(const State state) const
		{
			return m_aElementColor[(int)state];
		}

		float CTimePicker::getPadding(const State state) const
		{
			return m_aPadding[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CTimePicker::setTimerInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fTimerInterval))
			{
				m_fTimerInterval = value;
				return true;
			}
			return false;
		}

		bool CTimePicker::setShowSeconds(const bool value)
		{
			if (value != m_bShowSeconds)
			{
				m_bShowSeconds = value;
				m_bFirstDigit = true;
				if (!m_bShowSeconds)
				{
					if (m_eActiveElement == Element::Seconds)
						m_eActiveElement = Element::Minutes;
					if (m_eDownElement == Element::Seconds)
						getForm()->ReleaseCaptureMouse();
					if (m_eHoveredElement == Element::Seconds)
						UpdateHoveredElement();
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::setShowArrows(const bool value)
		{
			if (value != m_bShowArrows)
			{
				m_bShowArrows = value;
				m_bFirstDigit = true;
				if (!m_bShowArrows)
				{
					if (m_eDownElement == Element::UpArrow || m_eDownElement == Element::DownArrow)
						getForm()->ReleaseCaptureMouse();
					if (m_eHoveredElement == Element::UpArrow || m_eHoveredElement == Element::DownArrow)
						UpdateHoveredElement();
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setArrowsAtRight(const bool value)
		{
			if (value != m_bArrowsAtRight)
			{
				m_bArrowsAtRight = value;
				m_bFirstDigit = true;
				if (m_bShowArrows)
				{
					if (m_eDownElement == Element::UpArrow || m_eDownElement == Element::DownArrow)
						getForm()->ReleaseCaptureMouse();
					if (m_eHoveredElement == Element::UpArrow || m_eHoveredElement == Element::DownArrow)
						UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setContentAlign(const TextAlign value)
		{
			if (value != m_eContentAlign)
			{
				m_eContentAlign = value;
				m_bFirstDigit = true;
				if (m_eDownElement != Element::None)
					getForm()->ReleaseCaptureMouse();
				UpdateHoveredElement();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (state == s && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (state == s && m_aShadowColor[(int)state].A > 0)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				m_aShadowColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aOuterBorderWidth[(int)state]))
			{
				m_aOuterBorderWidth[(int)state] = value;
				if (state == getState())
				{
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
				if (m_aOuterBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aInnerBorderWidth[(int)state]))
			{
				m_aInnerBorderWidth[(int)state] = value;
				if (state == getState())
				{
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
				if (m_aInnerBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;

		}

		bool CTimePicker::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
				if (m_aBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowBorderRadius[(int)state]))
			{
				m_aUpArrowBorderRadius[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowOuterBorderWidth[(int)state]))
			{
				m_aUpArrowOuterBorderWidth[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowInnerBorderWidth[(int)state]))
			{
				m_aUpArrowInnerBorderWidth[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aUpArrowOuterBorderColor[(int)state])
			{
				m_aUpArrowOuterBorderColor[(int)state] = value;
				if (m_bShowArrows && m_aUpArrowOuterBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aUpArrowInnerBorderColor[(int)state])
			{
				m_aUpArrowInnerBorderColor[(int)state] = value;
				if (m_bShowArrows && m_aUpArrowInnerBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aUpArrowBackgroundColor[(int)state])
			{
				m_aUpArrowBackgroundColor[(int)state] = value;
				if (m_bShowArrows && m_aUpArrowBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aUpArrowPadding[(int)state]))
			{
				m_aUpArrowPadding[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowColor1(const State state, const Color &value)
		{
			if (value != m_aUpArrowColor1[(int)state])
			{
				m_aUpArrowColor1[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowColor2(const State state, const Color &value)
		{
			if (value != m_aUpArrowColor2[(int)state])
			{
				m_aUpArrowColor2[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setUpArrowColor3(const State state, const Color &value)
		{
			if (value != m_aUpArrowColor3[(int)state])
			{
				m_aUpArrowColor3[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowBorderRadius(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowBorderRadius[(int)state]))
			{
				m_aDownArrowBorderRadius[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowOuterBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowOuterBorderWidth[(int)state]))
			{
				m_aDownArrowOuterBorderWidth[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowInnerBorderWidth(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowInnerBorderWidth[(int)state]))
			{
				m_aDownArrowInnerBorderWidth[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aDownArrowOuterBorderColor[(int)state])
			{
				m_aDownArrowOuterBorderColor[(int)state] = value;
				if (m_bShowArrows && m_aDownArrowOuterBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aDownArrowInnerBorderColor[(int)state])
			{
				m_aDownArrowInnerBorderColor[(int)state] = value;
				if (m_bShowArrows && m_aDownArrowInnerBorderWidth[(int)state].has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aDownArrowBackgroundColor[(int)state])
			{
				m_aDownArrowBackgroundColor[(int)state] = value;
				if (m_bShowArrows && m_aDownArrowBackgroundGradient[(int)state].getPointCount() < 2 && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowPadding(const State state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aDownArrowPadding[(int)state]))
			{
				m_aDownArrowPadding[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowColor1(const State state, const Color &value)
		{
			if (value != m_aDownArrowColor1[(int)state])
			{
				m_aDownArrowColor1[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowColor2(const State state, const Color &value)
		{
			if (value != m_aDownArrowColor2[(int)state])
			{
				m_aDownArrowColor2[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setDownArrowColor3(const State state, const Color &value)
		{
			if (value != m_aDownArrowColor3[(int)state])
			{
				m_aDownArrowColor3[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setArrowDistance(const State state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aArrowDistance[(int)state]))
			{
				m_aArrowDistance[(int)state] = value;
				if (m_bShowArrows && state == getState())
				{
					if (m_eDownElement == Element::UpArrow || m_eDownElement == Element::DownArrow)
						getForm()->ReleaseCaptureMouse();
					if (m_eHoveredElement == Element::UpArrow || m_eHoveredElement == Element::DownArrow)
						UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setElementBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aElementBackgroundColor[(int)state])
			{
				m_aElementBackgroundColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setElementColor(const State state, const Color &value)
		{
			if (value != m_aElementColor[(int)state])
			{
				m_aElementColor[(int)state] = value;
				if (state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CTimePicker::setPadding(const State state, const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_aPadding[(int)state]))
			{
				m_aPadding[(int)state] = value;
				if (state == getState())
				{
					if (m_eDownElement != Element::None)
						getForm()->ReleaseCaptureMouse();
					UpdateHoveredElement();
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CTimePicker::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			int t;
			m_bFirstDigit = true;
			style->getOption(m_sClassName + L".ShowArrows", m_bShowArrows);
			style->getOption(m_sClassName + L".ArrowsAtRight", m_bArrowsAtRight);
			style->getOption(m_sClassName + L".ContentAlign", t); m_eContentAlign = (TextAlign)t;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
					break;
				case State::Focused:
					state = L"Focused";
					break;
				case State::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case State::Active:
					state = L"Active";
					break;
				case State::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".OuterBorderWidth[" + state + L"]", m_aOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderWidth[" + state + L"]", m_aInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".UpArrowBorderRadius[" + state + L"]", m_aUpArrowBorderRadius[i]);
				style->getOption(m_sClassName + L".UpArrowOuterBorderWidth[" + state + L"]", m_aUpArrowOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".UpArrowInnerBorderWidth[" + state + L"]", m_aUpArrowInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".UpArrowOuterBorderColor[" + state + L"]", m_aUpArrowOuterBorderColor[i]);
				style->getOption(m_sClassName + L".UpArrowInnerBorderColor[" + state + L"]", m_aUpArrowInnerBorderColor[i]);
				style->getOption(m_sClassName + L".UpArrowBackgroundColor[" + state + L"]", m_aUpArrowBackgroundColor[i]);
				style->getOption(m_sClassName + L".UpArrowBackgroundGradient[" + state + L"]", m_aUpArrowBackgroundGradient[i]);
				style->getOption(m_sClassName + L".UpArrowPadding[" + state + L"]", m_aUpArrowPadding[i]);
				style->getOption(m_sClassName + L".UpArrowColor1[" + state + L"]", m_aUpArrowColor1[i]);
				style->getOption(m_sClassName + L".UpArrowColor2[" + state + L"]", m_aUpArrowColor2[i]);
				style->getOption(m_sClassName + L".UpArrowColor3[" + state + L"]", m_aUpArrowColor3[i]);
				style->getOption(m_sClassName + L".DownArrowBorderRadius[" + state + L"]", m_aDownArrowBorderRadius[i]);
				style->getOption(m_sClassName + L".DownArrowOuterBorderWidth[" + state + L"]", m_aDownArrowOuterBorderWidth[i]);
				style->getOption(m_sClassName + L".DownArrowInnerBorderWidth[" + state + L"]", m_aDownArrowInnerBorderWidth[i]);
				style->getOption(m_sClassName + L".DownArrowOuterBorderColor[" + state + L"]", m_aDownArrowOuterBorderColor[i]);
				style->getOption(m_sClassName + L".DownArrowInnerBorderColor[" + state + L"]", m_aDownArrowInnerBorderColor[i]);
				style->getOption(m_sClassName + L".DownArrowBackgroundColor[" + state + L"]", m_aDownArrowBackgroundColor[i]);
				style->getOption(m_sClassName + L".DownArrowBackgroundGradient[" + state + L"]", m_aDownArrowBackgroundGradient[i]);
				style->getOption(m_sClassName + L".DownArrowPadding[" + state + L"]", m_aDownArrowPadding[i]);
				style->getOption(m_sClassName + L".DownArrowColor1[" + state + L"]", m_aDownArrowColor1[i]);
				style->getOption(m_sClassName + L".DownArrowColor2[" + state + L"]", m_aDownArrowColor2[i]);
				style->getOption(m_sClassName + L".DownArrowColor3[" + state + L"]", m_aDownArrowColor3[i]);
				style->getOption(m_sClassName + L".ArrowDistance[" + state + L"]", m_aArrowDistance[i]);
				style->getOption(m_sClassName + L".ElementBackgroundColor[" + state + L"]", m_aElementBackgroundColor[i]);
				style->getOption(m_sClassName + L".ElementBackgroundGradient[" + state + L"]", m_aElementBackgroundGradient[i]);
				style->getOption(m_sClassName + L".ElementColor[" + state + L"]", m_aElementColor[i]);
				style->getOption(m_sClassName + L".Padding[" + state + L"]", m_aPadding[i]);
			}
			m_bIgnoreGradient = false;
		}

		int CTimePicker::PackTime(const int hour, const int minute, const int second)
		{
			return ntl::Clamp<int>(hour * 3600 + minute * 60 + second, 0, 86399);
		}

		void CTimePicker::UnpackTime(const int value, int &hour, int &minute, int &second)
		{
			hour = value / 3600;
			minute = (value - hour * 3600) / 60;
			second = value % 60;
		}

		bool CTimePicker::setTime(const int hour, const int minute, const int second)
		{
			int v{ ntl::Max<int>(PackTime(m_iMinHour, m_iMinMinute, m_iMinSecond), ntl::Min<int>(PackTime(m_iMaxHour, m_iMaxMinute, m_iMaxSecond), PackTime(hour, minute, second))) }, h, m, s;
			UnpackTime(v, h, m, s);
			if (h != m_iHour || m != m_iMinute || s != m_iSecond)
			{
				m_iHour = h;
				m_iMinute = m;
				m_iSecond = s;
				if (OnChange)
					OnChange(this);
				return true;
			}
			return false;
		}

		bool CTimePicker::UpdateHoveredElement()
		{
			return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
		}

		bool CTimePicker::UpdateHoveredElement(const PointF &pos)
		{
			Element el{ Element::None };
			if (isEnabled(true))
			{
				State state{ getState() };
				if (m_bShowArrows)
				{
					RectF arrows_rect{ getArrowsRect(state) };
					RectF r{ getUpArrowRect(arrows_rect, state) };
					if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
						el = Element::UpArrow;
					if (el == Element::None)
					{
						r = getDownArrowRect(arrows_rect, state);
						if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
							el = Element::DownArrow;
					}
				}
				if (el == Element::None)
				{
					RectF content_rect{ getContentRect(state) };
					RectF r{ getHoursRect(content_rect) };
					if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
						el = Element::Hours;
					if (el == Element::None)
					{
						r = getMinutesRect(content_rect);
						if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
							el = Element::Minutes;
					}
					if (el == Element::None && m_bShowSeconds)
					{
						r = getSecondsRect(content_rect);
						if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
							el = Element::Seconds;
					}
				}
			}
			if (el != m_eHoveredElement)
			{
				m_eHoveredElement = el;
				return true;
			}
			return false;
		}

		void CTimePicker::UpdateMetrics()
		{
			if (getForm())
			{
				IPlatformFont *pf{ getFont()->getPlatformFont(getForm()->getRenderer()) };
				if (pf)
				{
					m_sDigitSize = pf->getStringSize(L"01234567890", 0);
					m_sDigitSize.X = m_sDigitSize.X * 0.1f + getFont()->Distance;
					m_fSeparatorWidth = pf->getStringSize(L":", 0).X + getFont()->Distance;
				}
			}
		}

		RectF CTimePicker::getArrowsRect(const State state)
		{
			float w{ getHeight() - m_aOuterBorderWidth[(int)state].Top - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Top - m_aInnerBorderWidth[(int)state].Bottom };
			RectF result;
			result.Top = m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top;
			result.Bottom = getHeight() - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Bottom;
			if (m_bArrowsAtRight)
			{
				result.Right = getWidth() - m_aOuterBorderWidth[(int)state].Right - m_aInnerBorderWidth[(int)state].Right;
				result.Left = result.Right - w;
			}
			else
			{
				result.Left = m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left;
				result.Right = result.Left + w;
			}
			if (result.has_negative() || result.is_zero() || result.Right >= getWidth() || result.Bottom >= getHeight())
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CTimePicker::getUpArrowRect(const RectF &rect, const State state)
		{
			if (rect.is_zero())
				return RectF{ 0, 0, 0, 0 };
			RectF result{ rect.Left, rect.Top, rect.Right, rect.Top + (rect.height() - m_aArrowDistance[(int)state]) * 0.5f };
			if (!result.is_valid())
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CTimePicker::getDownArrowRect(const RectF &rect, const State state)
		{
			if (rect.is_zero())
				return RectF{ 0, 0, 0, 0 };
			RectF result{ rect.Left, rect.Top + (rect.height() - m_aArrowDistance[(int)state]) * 0.5f + m_aArrowDistance[(int)state], rect.Right, rect.Bottom };
			if (!result.is_valid())
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CTimePicker::getContentRect(const State state)
		{
			RectF result;
			result.Left = m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left;
			if (m_bShowArrows && !m_bArrowsAtRight)
				result.Left += getHeight() - m_aOuterBorderWidth[(int)state].Top - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Top - m_aInnerBorderWidth[(int)state].Bottom;
			result.Right = getWidth() - m_aOuterBorderWidth[(int)state].Right - m_aInnerBorderWidth[(int)state].Right;
			if (m_bShowArrows && m_bArrowsAtRight)
				result.Right -= getHeight() - m_aOuterBorderWidth[(int)state].Top - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Top - m_aInnerBorderWidth[(int)state].Bottom;
			result.Top = m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top;
			result.Bottom = getHeight() - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Bottom;
			result.Top = (result.Top + result.Bottom - m_sDigitSize.Y) * 0.5f;
			result.Bottom = result.Top + m_sDigitSize.Y;
			float w{ m_sDigitSize.X * 4 + m_fSeparatorWidth + (m_bShowSeconds ? (2 * m_sDigitSize.X + m_fSeparatorWidth) : 0) };
			switch (m_eContentAlign)
			{
			case TextAlign::Right:
				result.Right -= m_aPadding[(int)state];
				result.Left = result.Right - w;
				break;
			case TextAlign::Center:
				result.Left = (result.Left + result.Right - w) * 0.5f;
				result.Right = result.Left + w;
				break;
			default:
				result.Left += m_aPadding[(int)state];
				result.Right = result.Left + w;
			}
			if (!result.is_valid() || result.has_negative() || result.is_zero() || result.Left >= getWidth() || result.Right >= getWidth() || result.Bottom >= getHeight())
				return RectF{ 0, 0, 0, 0 };
			return result;
		}

		RectF CTimePicker::getHoursRect(const RectF &rect)
		{
			if (rect.is_zero())
				return RectF{ 0, 0, 0, 0 };
			return RectF{ rect.Left, rect.Top, rect.Left + 2 * m_sDigitSize.X, rect.Bottom };
		}

		RectF CTimePicker::getMinutesRect(const RectF &rect)
		{
			if (rect.is_zero())
				return RectF{ 0, 0, 0, 0 };
			return RectF{ rect.Left + 2 * m_sDigitSize.X + m_fSeparatorWidth, rect.Top, rect.Left + 4 * m_sDigitSize.X + m_fSeparatorWidth, rect.Bottom };
		}

		RectF CTimePicker::getSecondsRect(const RectF &rect)
		{
			if (rect.is_zero())
				return RectF{ 0, 0, 0, 0 };
			return RectF{ rect.Left + 4 * m_sDigitSize.X + 2 * m_fSeparatorWidth, rect.Top, rect.Left + 6 * m_sDigitSize.X + 2 * m_fSeparatorWidth, rect.Bottom };
		}

		CTimePicker::State CTimePicker::getHoursState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (m_eActiveElement == Element::Hours)
				{
					if (m_eHoveredElement == Element::Hours)
						return State::ActiveHovered;
					return State::Active;
				}
				if (m_eHoveredElement == Element::Hours)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Hours)
				return State::Hovered;
			return State::Normal;
		}

		CTimePicker::State CTimePicker::getMinutesState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (m_eActiveElement == Element::Minutes)
				{
					if (m_eHoveredElement == Element::Minutes)
						return State::ActiveHovered;
					return State::Active;
				}
				if (m_eHoveredElement == Element::Minutes)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Minutes)
				return State::Hovered;
			return State::Normal;
		}

		CTimePicker::State CTimePicker::getSecondsState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (m_eActiveElement == Element::Seconds)
				{
					if (m_eHoveredElement == Element::Seconds)
						return State::ActiveHovered;
					return State::Active;
				}
				if (m_eHoveredElement == Element::Seconds)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::Seconds)
				return State::Hovered;
			return State::Normal;
		}

		CTimePicker::State CTimePicker::getUpArrowState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::UpArrow)
			{
				if (m_eHoveredElement == Element::UpArrow)
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (m_eHoveredElement == Element::UpArrow)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::UpArrow)
				return State::Hovered;
			return State::Normal;
		}

		CTimePicker::State CTimePicker::getDownArrowState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (m_eDownElement == Element::DownArrow)
			{
				if (m_eHoveredElement == Element::DownArrow)
					return State::ActiveHovered;
				return State::Active;
			}
			if (isFocused())
			{
				if (m_eHoveredElement == Element::DownArrow)
					return State::FocusedHovered;
				return State::Focused;
			}
			if (m_eHoveredElement == Element::DownArrow)
				return State::Hovered;
			return State::Normal;
		}

		Color CTimePicker::CalculateElementColor(const State state)
		{
			if (m_aElementColor[(int)state].A > 0)
				return m_aElementColor[(int)state];
			return getFont()->Color;
		}

		String CTimePicker::NumberToString(const int value)
		{
			if (value < 10)
				return L"0" + ToString(value);
			return ToString(value);
		}

		RectF CTimePicker::CalculateClientRect(const State state)
		{
			RectF result{
				m_aOuterBorderWidth[(int)state].Left + m_aInnerBorderWidth[(int)state].Left,
				m_aOuterBorderWidth[(int)state].Top + m_aInnerBorderWidth[(int)state].Top,
				getWidth() - m_aOuterBorderWidth[(int)state].Right - m_aInnerBorderWidth[(int)state].Right,
				getHeight() - m_aOuterBorderWidth[(int)state].Bottom - m_aInnerBorderWidth[(int)state].Bottom
			};
			result.validate();
			return result;
		}

		bool CTimePicker::ActivateHours()
		{
			if (m_eActiveElement != Element::Hours)
			{
				m_eActiveElement = Element::Hours;
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::ActivateMinutes()
		{
			if (m_eActiveElement != Element::Minutes)
			{
				m_eActiveElement = Element::Minutes;
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CTimePicker::ActivateSeconds()
		{
			if (m_eActiveElement != Element::Seconds && m_bShowSeconds)
			{
				m_eActiveElement = Element::Seconds;
				m_bFirstDigit = true;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CTimePicker::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
					
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };

				DrawBlockShadow(
					renderer,
					rect,
					m_aBorderRadius[(int)state],
					m_aShadowColor[(int)state],
					m_aShadowShift[(int)state],
					m_aShadowRadius[(int)state]);
				DrawDoubleBackground(
					renderer,
					rect,
					m_aOuterBorderWidth[(int)state],
					m_aInnerBorderWidth[(int)state],
					m_aBorderRadius[(int)state],
					m_aOuterBorderColor[(int)state],
					m_aInnerBorderColor[(int)state],
					m_aBackgroundColor[(int)state],
					m_aBackgroundGradient[(int)state]);

				RectF client{ CalculateClientRect(state) };
				if (!client.is_zero())
				{
					ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(client.width()), ntl::Round<int>(client.height()), 1, TextureFormat::RGBA, true) };
					if (clip)
					{
						renderer
							->ActivateTarget(clip)
							->Clear(Color{ 0, 0, 0, 0 });
						RenderContent(renderer, state, PointF{ -client.Left, -client.Top });
						RenderArrows(renderer, state, PointF{ -client.Left, -client.Top });
						renderer->ActivateTarget(m_pCanvas);
						CStorePrimitiveMatrix s_matrix{ renderer };
						renderer->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(client.Left + disp.X, client.Top + disp.Y, 0));
						if (m_aBorderRadius[(int)state].has_positive())
						{
							Block b{ rect - disp, AddElements(m_aOuterBorderWidth[(int)state], m_aInnerBorderWidth[(int)state]), m_aBorderRadius[(int)state], PointLocation::Inside };
							CStoreBlock s_block{ renderer };
							renderer
								->ActivateBlock(&b)
								->DrawImage(clip, 1);
						}
						else
							renderer->DrawImage(clip, 1);
						clip->Release();
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CTimePicker::RenderContent(IRenderer *renderer, const State state, const PointF &disp)
		{
			RectF content_rect{ getContentRect(state) };
			if (!content_rect.is_zero())
			{
				IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
				float distance{ getFont()->Distance };
				// Hours
				RectF r{ getHoursRect(content_rect) + disp };
				if (!r.is_zero())
				{
					State st{ getHoursState() };
					if (m_aElementBackgroundGradient[(int)st].getPointCount() >= 2)
						renderer->DrawGradient(r, m_aElementBackgroundGradient[(int)st]);
					else if (m_aElementBackgroundColor[(int)st].A > 0)
						renderer->DrawRectangle(r, m_aElementBackgroundColor[(int)st]);
					Color c{ CalculateElementColor(st) };
					CStorePrimitiveMatrix s_matrix{ renderer };
					if (c.A > 0)
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Left), std::round(r.Top), 0))
							->DrawText(NumberToString(m_iHour), pf, distance, c);
					}
					if (getFont()->Color.A > 0)
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Right), std::round(r.Top), 0))
							->DrawText(L":", pf, 0, getFont()->Color);
					}
				}
				// Minutes
				r = getMinutesRect(content_rect) + disp;
				if (!r.is_zero())
				{
					State st{ getMinutesState() };
					if (m_aElementBackgroundGradient[(int)st].getPointCount() >= 2)
						renderer->DrawGradient(r, m_aElementBackgroundGradient[(int)st]);
					else if (m_aElementBackgroundColor[(int)st].A > 0)
						renderer->DrawRectangle(r, m_aElementBackgroundColor[(int)st]);
					Color c{ CalculateElementColor(st) };
					CStorePrimitiveMatrix s_matrix{ renderer };
					if (c.A > 0)
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Left), std::round(r.Top), 0))
							->DrawText(NumberToString(m_iMinute), pf, distance, c);
					}
					if (m_bShowSeconds && getFont()->Color.A > 0)
					{
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Right), std::round(r.Top), 0))
							->DrawText(L":", pf, 0, getFont()->Color);
					}
				}
				// Seconds
				if (m_bShowSeconds)
				{
					r = getSecondsRect(content_rect) + disp;
					if (!r.is_zero())
					{
						State st{ getSecondsState() };
						if (m_aElementBackgroundGradient[(int)st].getPointCount() >= 2)
							renderer->DrawGradient(r, m_aElementBackgroundGradient[(int)st]);
						else if (m_aElementBackgroundColor[(int)st].A > 0)
							renderer->DrawRectangle(r, m_aElementBackgroundColor[(int)st]);
						Color c{ CalculateElementColor(st) };
						if (c.A > 0)
						{
							CStorePrimitiveMatrix s_matrix{ renderer };
							renderer
								->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(r.Left), std::round(r.Top), 0))
								->DrawText(NumberToString(m_iSecond), pf, distance, c);
						}
					}
				}
			}
		}

		void CTimePicker::RenderArrows(IRenderer *renderer, const State state, const PointF &disp)
		{
			if (m_bShowArrows)
			{
				RectF arrows_rect{ getArrowsRect(state) };
				if (!arrows_rect.is_zero())
				{
					// Up arrow
					RectF r{ getUpArrowRect(arrows_rect, state) + disp };
					if (!r.is_zero())
					{
						State st{ getUpArrowState() };
						DrawDoubleBackground(
							renderer,
							r,
							m_aUpArrowOuterBorderWidth[(int)st],
							m_aUpArrowInnerBorderWidth[(int)st],
							m_aUpArrowBorderRadius[(int)st],
							m_aUpArrowOuterBorderColor[(int)st],
							m_aUpArrowInnerBorderColor[(int)st],
							m_aUpArrowBackgroundColor[(int)st],
							m_aUpArrowBackgroundGradient[(int)st]);
						r.Left += m_aUpArrowOuterBorderWidth[(int)st].Left + m_aUpArrowInnerBorderWidth[(int)st].Left + m_aUpArrowPadding[(int)st].Left;
						r.Top += m_aUpArrowOuterBorderWidth[(int)st].Top + m_aUpArrowInnerBorderWidth[(int)st].Top + m_aUpArrowPadding[(int)st].Top;
						r.Right -= m_aUpArrowOuterBorderWidth[(int)st].Right + m_aUpArrowInnerBorderWidth[(int)st].Right + m_aUpArrowPadding[(int)st].Right;
						r.Bottom -= m_aUpArrowOuterBorderWidth[(int)st].Bottom + m_aUpArrowInnerBorderWidth[(int)st].Bottom + m_aUpArrowPadding[(int)st].Bottom;
						if (r.is_valid() && !r.is_zero())
						{
							if (m_aUpArrowColor1[(int)st].A > 0 || m_aUpArrowColor2[(int)st].A > 0 || m_aUpArrowColor3[(int)st].A > 0)
							{
								renderer->DrawTriangle(
									PointF{ r.Left, r.Bottom },
									PointF{ (r.Left + r.Right) * 0.5f, r.Top },
									PointF{ r.Right, r.Bottom },
									m_aUpArrowColor1[(int)st],
									m_aUpArrowColor2[(int)st],
									m_aUpArrowColor3[(int)st]);
							}
						}
					}
					// Down arrow
					r = getDownArrowRect(arrows_rect, state) + disp;
					if (!r.is_zero())
					{
						State st{ getDownArrowState() };
						DrawDoubleBackground(
							renderer,
							r,
							m_aDownArrowOuterBorderWidth[(int)st],
							m_aDownArrowInnerBorderWidth[(int)st],
							m_aDownArrowBorderRadius[(int)st],
							m_aDownArrowOuterBorderColor[(int)st],
							m_aDownArrowInnerBorderColor[(int)st],
							m_aDownArrowBackgroundColor[(int)st],
							m_aDownArrowBackgroundGradient[(int)st]);
						r.Left += m_aDownArrowOuterBorderWidth[(int)st].Left + m_aDownArrowInnerBorderWidth[(int)st].Left + m_aDownArrowPadding[(int)st].Left;
						r.Top += m_aDownArrowOuterBorderWidth[(int)st].Top + m_aDownArrowInnerBorderWidth[(int)st].Top + m_aDownArrowPadding[(int)st].Top;
						r.Right -= m_aDownArrowOuterBorderWidth[(int)st].Right + m_aDownArrowInnerBorderWidth[(int)st].Right + m_aDownArrowPadding[(int)st].Right;
						r.Bottom -= m_aDownArrowOuterBorderWidth[(int)st].Bottom + m_aDownArrowInnerBorderWidth[(int)st].Bottom + m_aDownArrowPadding[(int)st].Bottom;
						if (r.is_valid() && !r.is_zero())
						{
							if (m_aDownArrowColor1[(int)st].A > 0 || m_aDownArrowColor2[(int)st].A > 0 || m_aDownArrowColor3[(int)st].A > 0)
							{
								renderer->DrawTriangle(
									PointF{ r.Right, r.Top },
									PointF{ (r.Left + r.Right) * 0.5f, r.Bottom },
									PointF{ r.Left, r.Top },
									m_aDownArrowColor1[(int)st],
									m_aDownArrowColor2[(int)st],
									m_aDownArrowColor3[(int)st]);
							}
						}
					}
				}
			}
		}
	#pragma endregion
	}
}