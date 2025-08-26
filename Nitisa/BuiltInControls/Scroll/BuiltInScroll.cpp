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
	CBuiltInScroll::CTimerListener::CTimerListener(CBuiltInScroll *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInScroll::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		float limit{ m_pControl->PositionToScroll(m_pControl->m_sScrollPosition) };
		IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pControl->m_pListener) };
		switch (m_pControl->m_eScrollBy)
		{
		case ScrollBy::StartArrow:
			if (m_pControl->setScroll(m_pControl->m_fScroll - m_pControl->m_fDeltaSmall) && listener)
				listener->NotifyOnScroll(m_pControl);
			break;
		case ScrollBy::EndArrow:
			if (m_pControl->setScroll(m_pControl->m_fScroll + m_pControl->m_fDeltaSmall) && listener)
				listener->NotifyOnScroll(m_pControl);
			break;
		case ScrollBy::BeforeScroller:
			if (ntl::IsGreater<float>(m_pControl->m_fScroll, limit) && m_pControl->setScroll(m_pControl->m_fScroll - m_pControl->CalculateDeltaLarge()) && listener)
				listener->NotifyOnScroll(m_pControl);
			break;
		case ScrollBy::AfterScroller:
			if (ntl::IsLess<float>(m_pControl->m_fScroll, limit) && m_pControl->setScroll(m_pControl->m_fScroll + m_pControl->CalculateDeltaLarge()) && listener)
				listener->NotifyOnScroll(m_pControl);
			break;
		default:
			break;
		}
	}
#pragma endregion

#pragma region CGradientListener
	CBuiltInScroll::CGradientListener::CGradientListener(CBuiltInScroll *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInScroll::CGradientListener::NotifyOnChange()
	{
		if (!m_pControl->m_bIgnoreGradient && m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRenderRect());
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInScroll::CBuiltInScroll() :
		CBuiltInControl(L"Scroll", PointF{ 123, 16 }),
		m_cGradientListener{ this },
		m_fMin{ 0 },
		m_fMax{ 100 },
		m_fScroll{ 0 },
		m_fScrollerSize{ 0 },
		m_fDeltaSmall{ 1 },
		m_fDeltaMedium{ 10 },
		m_fDeltaLarge{ 0 },
		m_bVertical{ false },
		m_bArrowsVisible{ true },
		m_eHoveredElement{ ElementType::None },
		m_eActiveElement{ ElementType::None },
		m_fScrollInterval{ ScrollInterval },
		m_fArrowSize{ 0.7f },
		m_fBorderWidth{ 0 },
		m_fBorderRadius{ 0 },
		m_aBorderColor{
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 234, 234, 234, 255 } },
		m_aBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aShadowRadius{ 1, 1, 1, 1 },
		m_aShadowShift{
			PointF{ -1, -1 },
			PointF{ -1, -1 },
			PointF{ -1, -1 },
			PointF{ -1, -1 } },
		m_aShadowColor{
			Color{ 160, 160, 160, 0 },
			Color{ 160, 160, 160, 0 },
			Color{ 160, 160, 160, 0 },
			Color{ 160, 160, 160, 0 } },
		m_fStartArrowBorderWidth{ 1 },
		m_fStartArrowBorderRadius{ 2 },
		m_aStartArrowBorderColor{
			Color{ 0, 0, 0, 0 },
			Color{ 155, 155, 155, 255 },
			Color{ 52, 110, 153, 255 },
			Color{ 155, 155, 155, 255 },
			Color{ 24, 89, 138, 255 },
			Color{ 0, 0, 0, 0 } },
		m_aStartArrowBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aStartArrowBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aStartArrowColor1{
			Color{ 85, 85, 85, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 141, 198, 229, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 143, 184, 206, 255 },
			Color{ 191, 191, 191, 255 } },
		m_aStartArrowColor2{
			Color{ 45, 45, 45, 255 },
			Color{ 45, 45, 45, 255 },
			Color{ 17, 56, 76, 255 },
			Color{ 45, 45, 45, 255 },
			Color{ 18, 46, 61, 255 },
			Color{ 123, 123, 123, 255 } },
		m_aStartArrowColor3{
			Color{ 85, 85, 85, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 32, 106, 145, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 35, 88, 116, 255 },
			Color{ 143, 143, 143, 255 } },
		m_fEndArrowBorderWidth{ 1 },
		m_fEndArrowBorderRadius{ 2 },
		m_aEndArrowBorderColor{
			Color{ 0, 0, 0, 0 },
			Color{ 155, 155, 155, 255 },
			Color{ 52, 110, 153, 255 },
			Color{ 155, 155, 155, 255 },
			Color{ 24, 89, 138, 255 },
			Color{ 0, 0, 0, 0 } },
		m_aEndArrowBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aEndArrowBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aEndArrowColor1{
			Color{ 85, 85, 85, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 141, 198, 229, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 143, 184, 206, 255 },
			Color{ 191, 191, 191, 255 } },
		m_aEndArrowColor2{
			Color{ 45, 45, 45, 255 },
			Color{ 45, 45, 45, 255 },
			Color{ 17, 56, 76, 255 },
			Color{ 45, 45, 45, 255 },
			Color{ 18, 46, 61, 255 },
			Color{ 123, 123, 123, 255 } },
		m_aEndArrowColor3{
			Color{ 85, 85, 85, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 32, 106, 145, 255 },
			Color{ 85, 85, 85, 255 },
			Color{ 35, 88, 116, 255 },
			Color{ 143, 143, 143, 255 } },
		m_fScrollerBorderWidth{ 1 },
		m_fScrollerBorderRadius{ 2 },
		m_aScrollerBorderColor{
			Color{ 155, 155, 155, 255 },
			Color{ 130, 129, 129, 255 },
			Color{ 52, 110, 153, 255 },
			Color{ 130, 129, 129, 255 },
			Color{ 24, 89, 138, 255 },
			Color{ 0, 0, 0, 0 } },
		m_aScrollerBackgroundColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aScrollerBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener }, 
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_aScrollerLinesBorderColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aScrollerLinesBackgroundColor{
			Color{ 150, 150, 150, 255 },
			Color{ 150, 150, 150, 255 },
			Color{ 55, 125, 163, 255 },
			Color{ 150, 150, 150, 255 },
			Color{ 46, 115, 151, 255 },
			Color{ 0, 0, 0, 0 } },
		m_sScrollerLinesSize{ 0.5f, 2 },
		m_fScrollerLinesDistance{ 1 },
		m_fScrollerLinesBorderWidth{ 0 },
		m_pListener{ nullptr },
		m_bScrolling{ false },
		m_bHovered{ false },
		m_hTimer{ nullptr },
		m_bIgnoreGradient{ true },
		m_cTimerListener{ this }
	{
		m_aBackgroundGradient[(int)State::Normal].setPointCount(3);
		m_aBackgroundGradient[(int)State::Normal].setType(GradientType::Vertical);
		m_aBackgroundGradient[(int)State::Normal].setPointColor(0, Color{ 225, 225, 225, 255 });
		m_aBackgroundGradient[(int)State::Normal].setPointColor(1, Color{ 237, 237, 237, 255 });
		m_aBackgroundGradient[(int)State::Normal].setPointColor(2, Color{ 233, 233, 233, 255 });

		m_aBackgroundGradient[(int)State::Hovered].setPointCount(3);
		m_aBackgroundGradient[(int)State::Hovered].setType(GradientType::Vertical);
		m_aBackgroundGradient[(int)State::Hovered].setPointColor(0, Color{ 225, 225, 225, 255 });
		m_aBackgroundGradient[(int)State::Hovered].setPointColor(1, Color{ 237, 237, 237, 255 });
		m_aBackgroundGradient[(int)State::Hovered].setPointColor(2, Color{ 233, 233, 233, 255 });

		m_aBackgroundGradient[(int)State::Active].setPointCount(3);
		m_aBackgroundGradient[(int)State::Active].setType(GradientType::Vertical);
		m_aBackgroundGradient[(int)State::Active].setPointColor(0, Color{ 225, 225, 225, 255 });
		m_aBackgroundGradient[(int)State::Active].setPointColor(1, Color{ 237, 237, 237, 255 });
		m_aBackgroundGradient[(int)State::Active].setPointColor(2, Color{ 233, 233, 233, 255 });

		m_aBackgroundGradient[(int)State::Disabled].setPointCount(3);
		m_aBackgroundGradient[(int)State::Disabled].setType(GradientType::Vertical);
		m_aBackgroundGradient[(int)State::Disabled].setPointColor(0, Color{ 229, 229, 229, 255 });
		m_aBackgroundGradient[(int)State::Disabled].setPointColor(1, Color{ 237, 237, 237, 255 });
		m_aBackgroundGradient[(int)State::Disabled].setPointColor(2, Color{ 240, 240, 240, 255 });

		// NormalNormal
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointCount(4);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setType(GradientType::Vertical);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		// HoveredNormal
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointCount(4);
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setType(GradientType::Vertical);
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointCount(4);
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setType(GradientType::Vertical);
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointCount(4);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setType(GradientType::Vertical);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		// HoveredHovered
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointCount(4);
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setType(GradientType::Vertical);
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(0, Color{ 227, 244, 252, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(1, 0.499f, Color{ 214, 238, 251, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(2, 0.500f, Color{ 169, 219, 246, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(3, Color{ 156, 202, 227, 255 });

		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointCount(4);
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setType(GradientType::Vertical);
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(0, Color{ 227, 244, 252, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(1, 0.499f, Color{ 214, 238, 251, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(2, 0.500f, Color{ 169, 219, 246, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(3, Color{ 156, 202, 227, 255 });

		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setPointCount(4);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setType(GradientType::Vertical);
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(0, Color{ 227, 244, 252, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(1, 0.499f, Color{ 214, 238, 251, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setPoint(2, 0.500f, Color{ 169, 219, 246, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::HoveredHovered].setPointColor(3, Color{ 156, 202, 227, 255 });

		// ActiveNormal
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointCount(4);
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setType(GradientType::Vertical);
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointCount(4);
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setType(GradientType::Vertical);
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setPointCount(4);
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setType(GradientType::Vertical);
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(0, Color{ 243, 243, 243, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(1, 0.499f, Color{ 232, 232, 233, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setPoint(2, 0.500f, Color{ 214, 214, 216, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveNormal].setPointColor(3, Color{ 188, 189, 192, 255 });

		// ActiveActive
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointCount(4);
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setType(GradientType::Vertical);
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(0, Color{ 201, 235, 249, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setPoint(1, 0.499f, Color{ 175, 225, 247, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setPoint(2, 0.500f, Color{ 111, 202, 240, 255 });
		m_aStartArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(3, Color{ 102, 186, 221, 255 });

		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointCount(4);
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setType(GradientType::Vertical);
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(0, Color{ 201, 235, 249, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setPoint(1, 0.499f, Color{ 175, 225, 247, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setPoint(2, 0.500f, Color{ 111, 202, 240, 255 });
		m_aEndArrowBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(3, Color{ 102, 186, 221, 255 });

		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setPointCount(4);
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setType(GradientType::Vertical);
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(0, Color{ 206, 237, 250, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setPoint(1, 0.499f, Color{ 181, 228, 247, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setPoint(2, 0.500f, Color{ 111, 202, 240, 255 });
		m_aScrollerBackgroundGradient[(int)ElementState::ActiveActive].setPointColor(3, Color{ 102, 185, 220, 255 });

		m_bIgnoreGradient = false;
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInScroll::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInScroll::isHovered()
	{
		return m_bHovered;
	}

	RectF CBuiltInScroll::getRenderRect()
	{
		RectF result{ getRect() }, r{ result };
		for (int i = 0; i <= (int)State::Disabled; i++)
			result += AddShadow(r, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
		return result;
	}

	bool CBuiltInScroll::isDown()
	{
		return m_bScrolling;
	}
#pragma endregion

#pragma region IBuiltInScroll getters
	float CBuiltInScroll::getMin()
	{
		return m_fMin;
	}

	float CBuiltInScroll::getMax()
	{
		return m_fMax;
	}

	float CBuiltInScroll::getScroll()
	{
		return m_fScroll;
	}

	float CBuiltInScroll::getScrollerSize()
	{
		return m_fScrollerSize;
	}

	float CBuiltInScroll::getDeltaSmall()
	{
		return m_fDeltaSmall;
	}

	float CBuiltInScroll::getDeltaMedium()
	{
		return m_fDeltaMedium;
	}

	float CBuiltInScroll::getDeltaLarge()
	{
		return m_fDeltaLarge;
	}

	bool CBuiltInScroll::isVertical()
	{
		return m_bVertical;
	}

	bool CBuiltInScroll::isArrowsVisible()
	{
		return m_bArrowsVisible;
	}
#pragma endregion

#pragma region Getters
	CBuiltInScroll::State CBuiltInScroll::getState()
	{
		if (!isEnabled())
			return State::Disabled;
		if (m_bScrolling)
			return State::Active;
		if (m_bHovered)
			return State::Hovered;
		return State::Normal;
	}

	CBuiltInScroll::ElementType CBuiltInScroll::getHoveredElement() const
	{
		return m_eHoveredElement;
	}

	CBuiltInScroll::ElementType CBuiltInScroll::getActiveElement() const
	{
		return m_eActiveElement;
	}

	float CBuiltInScroll::getScrollInterval() const
	{
		return m_fScrollInterval;
	}

	float CBuiltInScroll::getArrowSize() const
	{
		return m_fArrowSize;
	}

	float CBuiltInScroll::getBorderWidth() const
	{
		return m_fBorderWidth;
	}

	float CBuiltInScroll::getBorderRadius() const
	{
		return m_fBorderRadius;
	}

	Color CBuiltInScroll::getBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state];
	}

	Color CBuiltInScroll::getBackgroundColor(const State state) const
	{
		return m_aBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScroll::getBackgroundGradient(const State state)
	{
		return &m_aBackgroundGradient[(int)state];
	}

	int CBuiltInScroll::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state];
	}

	PointF CBuiltInScroll::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state];
	}

	Color CBuiltInScroll::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state];
	}

	float CBuiltInScroll::getStartArrowBorderWidth() const
	{
		return m_fStartArrowBorderWidth;
	}

	float CBuiltInScroll::getStartArrowBorderRadius() const
	{
		return m_fStartArrowBorderRadius;
	}

	Color CBuiltInScroll::getStartArrowBorderColor(const ElementState state) const
	{
		return m_aStartArrowBorderColor[(int)state];
	}

	Color CBuiltInScroll::getStartArrowBackgroundColor(const ElementState state) const
	{
		return m_aStartArrowBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScroll::getStartArrowBackgroundGradient(const ElementState state)
	{
		return &m_aStartArrowBackgroundGradient[(int)state];
	}

	Color CBuiltInScroll::getStartArrowColor1(const ElementState state) const
	{
		return m_aStartArrowColor1[(int)state];
	}

	Color CBuiltInScroll::getStartArrowColor2(const ElementState state) const
	{
		return m_aStartArrowColor2[(int)state];
	}

	Color CBuiltInScroll::getStartArrowColor3(const ElementState state) const
	{
		return m_aStartArrowColor3[(int)state];
	}

	float CBuiltInScroll::getEndArrowBorderWidth() const
	{
		return m_fEndArrowBorderWidth;
	}

	float CBuiltInScroll::getEndArrowBorderRadius() const
	{
		return m_fEndArrowBorderRadius;
	}

	Color CBuiltInScroll::getEndArrowBorderColor(const ElementState state) const
	{
		return m_aEndArrowBorderColor[(int)state];
	}

	Color CBuiltInScroll::getEndArrowBackgroundColor(const ElementState state) const
	{
		return m_aEndArrowBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScroll::getEndArrowBackgroundGradient(const ElementState state)
	{
		return &m_aEndArrowBackgroundGradient[(int)state];
	}

	Color CBuiltInScroll::getEndArrowColor1(const ElementState state) const
	{
		return m_aEndArrowColor1[(int)state];
	}

	Color CBuiltInScroll::getEndArrowColor2(const ElementState state) const
	{
		return m_aEndArrowColor2[(int)state];
	}

	Color CBuiltInScroll::getEndArrowColor3(const ElementState state) const
	{
		return m_aEndArrowColor3[(int)state];
	}

	float CBuiltInScroll::getScrollerBorderWidth() const
	{
		return m_fScrollerBorderWidth;
	}

	float CBuiltInScroll::getScrollerBorderRadius() const
	{
		return m_fScrollerBorderRadius;
	}

	Color CBuiltInScroll::getScrollerBorderColor(const ElementState state) const
	{
		return m_aScrollerBorderColor[(int)state];
	}

	Color CBuiltInScroll::getScrollerBackgroundColor(const ElementState state) const
	{
		return m_aScrollerBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScroll::getScrollerBackgroundGradient(const ElementState state)
	{
		return &m_aScrollerBackgroundGradient[(int)state];
	}

	Color CBuiltInScroll::getScrollerLinesBorderColor(const ElementState state) const
	{
		return m_aScrollerLinesBorderColor[(int)state];
	}

	Color CBuiltInScroll::getScrollerLinesBackgroundColor(const ElementState state) const
	{
		return m_aScrollerLinesBackgroundColor[(int)state];
	}

	PointF CBuiltInScroll::getScrollerLinesSize() const
	{
		return m_sScrollerLinesSize;
	}

	float CBuiltInScroll::getScrollerLinesDistance() const
	{
		return m_fScrollerLinesDistance;
	}

	float CBuiltInScroll::getScrollerLinesBorderWidth() const
	{
		return m_fScrollerLinesBorderWidth;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInScroll::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInScroll::setEnabled(const bool value)
	{
		if (CBuiltInControl::setEnabled(value))
		{
			if (!isEnabled())
				m_bScrolling = false;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
			float avg{ (s.X + s.Y) / 2 };
			m_fScrollerSize *= avg;
			m_fDeltaSmall *= avg;
			m_fDeltaMedium *= avg;
			m_fDeltaLarge *= avg;
			m_fBorderWidth *= avg;
			m_fBorderRadius *= avg;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				m_aShadowShift[i] *= s;
			}
			m_fEndArrowBorderWidth *= avg;
			m_fEndArrowBorderRadius *= avg;
			m_fScrollerBorderWidth *= avg;
			m_fScrollerBorderRadius *= avg;
			m_sScrollerLinesSize.Y *= avg;
			m_fScrollerLinesDistance *= avg;
			m_fScrollerLinesBorderWidth *= avg;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInScroll setters
	bool CBuiltInScroll::setMin(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_fMin))
		{
			m_fMin = value;
			if (m_fMax <= m_fMin)
				m_fMax = m_fMin + 1;
			if (m_fScroll < m_fMin)
				m_fScroll = m_fMin;
			else if (m_fScroll > m_fMax)
				m_fScroll = m_fMax;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setMax(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_fMax))
		{
			m_fMax = value;
			if (m_fMin >= m_fMax)
				m_fMin = m_fMax - 1;
			if (m_fScroll < m_fMin)
				m_fScroll = m_fMin;
			else if (m_fScroll > m_fMax)
				m_fScroll = m_fMax;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScroll(const float value)
	{
		float v{ ntl::Clamp<float>(value, m_fMin, m_fMax) };
		if (ntl::IsNotEqual<float>(v, m_fScroll))
		{
			m_fScroll = v;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerSize(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerSize))
		{
			m_fScrollerSize = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setDeltaSmall(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaSmall))
		{
			m_fDeltaSmall = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setDeltaMedium(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaMedium))
		{
			m_fDeltaMedium = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setDeltaLarge(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fDeltaLarge))
		{
			m_fDeltaLarge = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setVertical(const bool value)
	{
		if (value != m_bVertical)
		{
			m_bVertical = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setArrowsVisible(const bool value)
	{
		if (value != m_bArrowsVisible)
		{
			m_bArrowsVisible = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInScroll::setScrollInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
		{
			m_fScrollInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setArrowSize(const float value)
	{
		if (value >= 0 && value <= 1 && ntl::IsNotEqual<float>(value, m_fArrowSize))
		{
			m_fArrowSize = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fBorderWidth))
		{
			m_fBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setBorderRadius(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fBorderRadius))
		{
			m_fBorderRadius = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state])
		{
			m_aBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aBackgroundColor[(int)state])
		{
			m_aBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setShadowRadius(const State state, const int value)
	{
		if (value >= 1 && value != m_aShadowRadius[(int)state])
		{
			m_aShadowRadius[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state]))
		{
			m_aShadowShift[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state])
		{
			m_aShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fStartArrowBorderWidth))
		{
			m_fStartArrowBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowBorderRadius(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fStartArrowBorderRadius))
		{
			m_fStartArrowBorderRadius = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowBorderColor(const ElementState state, const Color &value)
	{
		if (value != m_aStartArrowBorderColor[(int)state])
		{
			m_aStartArrowBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowBackgroundColor(const ElementState state, const Color &value)
	{
		if (value != m_aStartArrowBackgroundColor[(int)state])
		{
			m_aStartArrowBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowColor1(const ElementState state, const Color &value)
	{
		if (value != m_aStartArrowColor1[(int)state])
		{
			m_aStartArrowColor1[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowColor2(const ElementState state, const Color &value)
	{
		if (value != m_aStartArrowColor2[(int)state])
		{
			m_aStartArrowColor2[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setStartArrowColor3(const ElementState state, const Color &value)
	{
		if (value != m_aStartArrowColor3[(int)state])
		{
			m_aStartArrowColor3[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fEndArrowBorderWidth))
		{
			m_fEndArrowBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowBorderRadius(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fEndArrowBorderRadius))
		{
			m_fEndArrowBorderRadius = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowBorderColor(const ElementState state, const Color &value)
	{
		if (value != m_aEndArrowBorderColor[(int)state])
		{
			m_aEndArrowBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowBackgroundColor(const ElementState state, const Color &value)
	{
		if (value != m_aEndArrowBackgroundColor[(int)state])
		{
			m_aEndArrowBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowColor1(const ElementState state, const Color &value)
	{
		if (value != m_aEndArrowColor1[(int)state])
		{
			m_aEndArrowColor1[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowColor2(const ElementState state, const Color &value)
	{
		if (value != m_aEndArrowColor2[(int)state])
		{
			m_aEndArrowColor2[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setEndArrowColor3(const ElementState state, const Color &value)
	{
		if (value != m_aEndArrowColor3[(int)state])
		{
			m_aEndArrowColor3[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerBorderWidth))
		{
			m_fScrollerBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerBorderRadius(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerBorderRadius))
		{
			m_fScrollerBorderRadius = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerBorderColor(const ElementState state, const Color &value)
	{
		if (value != m_aScrollerBorderColor[(int)state])
		{
			m_aScrollerBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerBackgroundColor(const ElementState state, const Color &value)
	{
		if (value != m_aScrollerBackgroundColor[(int)state])
		{
			m_aScrollerBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerLinesBorderColor(const ElementState state, const Color &value)
	{
		if (value != m_aScrollerLinesBorderColor[(int)state])
		{
			m_aScrollerLinesBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerLinesBackgroundColor(const ElementState state, const Color &value)
	{
		if (value != m_aScrollerLinesBackgroundColor[(int)state])
		{
			m_aScrollerLinesBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerLinesSize(const PointF &value)
	{
		if (value.X >= 0 && value.X <= 1 && value.Y >= 0 && IsNotEqual(value, m_sScrollerLinesSize))
		{
			m_sScrollerLinesSize = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerLinesDistance(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerLinesDistance))
		{
			m_fScrollerLinesDistance = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScroll::setScrollerLinesBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerLinesBorderWidth))
		{
			m_fScrollerLinesBorderWidth = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CBuiltInScroll::UpdateFromStyle(IStyle *style, const String &class_name)
	{
		m_bIgnoreGradient = true;
		style->getOption(class_name + L".DeltaSmall", m_fDeltaSmall);
		style->getOption(class_name + L".DeltaMedium", m_fDeltaMedium);
		style->getOption(class_name + L".DeltaLarge", m_fDeltaLarge);
		style->getOption(class_name + L".ScrollInterval", m_fScrollInterval);
		style->getOption(class_name + L".BorderWidth", m_fBorderWidth);
		style->getOption(class_name + L".BorderRadius", m_fBorderRadius);
		style->getOption(class_name + L".StartArrowBorderWidth", m_fStartArrowBorderWidth);
		style->getOption(class_name + L".StartArrowBorderRadius", m_fStartArrowBorderRadius);
		style->getOption(class_name + L".EndArrowBorderWidth", m_fEndArrowBorderWidth);
		style->getOption(class_name + L".EndArrowBorderRadius", m_fEndArrowBorderRadius);
		style->getOption(class_name + L".ScrollerBorderWidth", m_fScrollerBorderWidth);
		style->getOption(class_name + L".ScrollerBorderRadius", m_fScrollerBorderRadius);
		for (int i = 0; i <= (int)State::Disabled; i++)
		{
			String state;
			switch ((State)i)
			{
			case State::Hovered:
				state = L"Hovered";
				break;
			case State::Active:
				state = L"Active";
				break;
			case State::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			style->getOption(class_name + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
			style->getOption(class_name + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
			style->getOption(class_name + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
			style->getOption(class_name + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
			style->getOption(class_name + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
			style->getOption(class_name + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);

			style->getOption(class_name + L".StartArrowBorderColor[" + state + L"]", m_aStartArrowBorderColor[i]);
			style->getOption(class_name + L".StartArrowBackgroundColor[" + state + L"]", m_aStartArrowBackgroundColor[i]);
			style->getOption(class_name + L".StartArrowBackgroundGradient[" + state + L"]", m_aStartArrowBackgroundGradient[i]);
			style->getOption(class_name + L".StartArrowColor1[" + state + L"]", m_aStartArrowColor1[i]);
			style->getOption(class_name + L".StartArrowColor2[" + state + L"]", m_aStartArrowColor2[i]);
			style->getOption(class_name + L".StartArrowColor3[" + state + L"]", m_aStartArrowColor3[i]);

			style->getOption(class_name + L".EndArrowBorderColor[" + state + L"]", m_aEndArrowBorderColor[i]);
			style->getOption(class_name + L".EndArrowBackgroundColor[" + state + L"]", m_aEndArrowBackgroundColor[i]);
			style->getOption(class_name + L".EndArrowBackgroundGradient[" + state + L"]", m_aEndArrowBackgroundGradient[i]);
			style->getOption(class_name + L".EndArrowColor1[" + state + L"]", m_aEndArrowColor1[i]);
			style->getOption(class_name + L".EndArrowColor2[" + state + L"]", m_aEndArrowColor2[i]);
			style->getOption(class_name + L".EndArrowColor3[" + state + L"]", m_aEndArrowColor3[i]);

			style->getOption(class_name + L".ScrollerBorderColor[" + state + L"]", m_aScrollerBorderColor[i]);
			style->getOption(class_name + L".ScrollerBackgroundColor[" + state + L"]", m_aScrollerBackgroundColor[i]);
			style->getOption(class_name + L".ScrollerBackgroundGradient[" + state + L"]", m_aScrollerBackgroundGradient[i]);
			style->getOption(class_name + L".ScrollerLinesBorderColor[" + state + L"]", m_aScrollerLinesBorderColor[i]);
			style->getOption(class_name + L".ScrollerLinesBackgroundColor[" + state + L"]", m_aScrollerLinesBackgroundColor[i]);
		}
		m_bIgnoreGradient = false;
	}

	void CBuiltInScroll::Update()
	{
		// Not required
	}
#pragma endregion

#pragma region Helpers
	bool CBuiltInScroll::UpdateHoveredElement(const PointF &position)
	{
		RectF r{ getStartArrowRect() };
		if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
		{
			if (m_eHoveredElement == ElementType::StartArrow)
				return false;
			m_eHoveredElement = ElementType::StartArrow;
			return true;
		}
		r = getEndArrowRect();
		if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
		{
			if (m_eHoveredElement == ElementType::EndArrow)
				return false;
			m_eHoveredElement = ElementType::EndArrow;
			return true;
		}
		r = getScrollerRect();
		if (position.X >= r.Left && position.X < r.Right && position.Y >= r.Top && position.Y < r.Bottom)
		{
			if (m_eHoveredElement == ElementType::Scroller)
				return false;
			m_eHoveredElement = ElementType::Scroller;
			return true;
		}
		if (m_eHoveredElement == ElementType::None)
			return false;
		m_eHoveredElement = ElementType::None;
		return true;
	}

	RectF CBuiltInScroll::getStartArrowRect()
	{
		if (m_bArrowsVisible)
		{
			RectF result{
				m_fBorderWidth,
				m_fBorderWidth,
				m_bVertical ? (getWidth() - m_fBorderWidth) : (getHeight() - m_fBorderWidth),
				m_bVertical ? (getWidth() - m_fBorderWidth) : (getHeight() - m_fBorderWidth)
			};
			result.validate();
			return result;
		}
		if (m_bVertical)
			return RectF{ 0, 0, getWidth(), 0 };
		return RectF{ 0, 0, 0, getHeight() };
	}

	RectF CBuiltInScroll::getEndArrowRect()
	{
		if (m_bArrowsVisible)
		{
			RectF result{
				m_bVertical ? m_fBorderWidth : (getWidth() - getHeight() + m_fBorderWidth),
				m_bVertical ? (getHeight() - getWidth() + m_fBorderWidth) : m_fBorderWidth,
				getWidth() - m_fBorderWidth,
				getHeight() - m_fBorderWidth
			};
			result.validate();
			return result;
		}
		if (m_bVertical)
			return RectF{ 0, getHeight(), getWidth(), getHeight() };
		return RectF{ getWidth(), 0, getWidth(), getHeight() };
	}

	RectF CBuiltInScroll::getScrollerRect()
	{
		float scroller_size, scrolling_area, arrow_size{ m_bArrowsVisible ? (m_bVertical ? getWidth() : getHeight()) : 0 };
		CalculateScroller(scroller_size, scrolling_area);
		float position{ (m_fScroll - m_fMin) * scrolling_area / (m_fMax - m_fMin) };
		RectF result{
			m_bVertical ? m_fBorderWidth : (arrow_size + position),
			m_bVertical ? (arrow_size + position) : m_fBorderWidth,
			m_bVertical ? (getWidth() - m_fBorderWidth): (arrow_size + position + scroller_size),
			m_bVertical ? (arrow_size + position + scroller_size) : (getHeight() - m_fBorderWidth)
		};
		result.validate();
		return result;
	}

	void CBuiltInScroll::CalculateScroller(float &scroller_size, float &scrolling_area)
	{
		float area_between_arrows;
		if (m_bVertical)
		{
			float arrow_size{ m_bArrowsVisible ? getWidth() : 0 };
			area_between_arrows = ntl::Max<float>(0.0f, getHeight() - 2 * arrow_size);
			if (ntl::IsGreater<float>(m_fScrollerSize, 0))
				scroller_size = ntl::Clamp<float>(area_between_arrows, 0.0f, m_fScrollerSize);
			else
				scroller_size = area_between_arrows * area_between_arrows / (m_fMax - m_fMin + area_between_arrows);
		}
		else
		{
			float arrow_size{ m_bArrowsVisible ? getHeight() : 0 };
			area_between_arrows = ntl::Max<float>(0.0f, getWidth() - 2 * arrow_size);
			if (ntl::IsGreater<float>(m_fScrollerSize, 0))
				scroller_size = ntl::Clamp<float>(area_between_arrows, 0.0f, m_fScrollerSize);
			else
				scroller_size = area_between_arrows * area_between_arrows / (m_fMax - m_fMin + area_between_arrows);
		}
		scrolling_area = area_between_arrows - scroller_size;
	}

	float CBuiltInScroll::CalculateDeltaLarge()
	{
		if (ntl::IsGreater<float>(m_fDeltaLarge, 0))
			return m_fDeltaLarge;
		float scroller_size, scrolling_area;
		CalculateScroller(scroller_size, scrolling_area);
		if (ntl::IsGreater<float>(scrolling_area, 0))
			return ntl::Max<float>(1.0f, (m_fMax - m_fMin) * ntl::Min<float>(1.0f, scroller_size / (scrolling_area)));
		return m_fMax - m_fMin;
	}

	CBuiltInScroll::ElementState CBuiltInScroll::getElementState(const ElementType element)
	{
		if (!isEnabled())
			return ElementState::DisabledDisabled;
		if (m_bScrolling)
		{
			if (m_eActiveElement == element)
				return ElementState::ActiveActive;
			return ElementState::ActiveNormal;
		}
		if (m_eHoveredElement == element)
			return ElementState::HoveredHovered;
		if (m_bHovered)
			return ElementState::HoveredNormal;
		return ElementState::HoveredNormal;
	}

	CBuiltInScroll::ScrollBy CBuiltInScroll::getScrollElement(const PointF &position)
	{
		RectF start{ getStartArrowRect() };
		if (position.X >= start.Left && position.X < start.Right && position.Y >= start.Top && position.Y < start.Bottom)
			return ScrollBy::StartArrow;
		RectF end{ getEndArrowRect() };
		if (position.X >= end.Left && position.X < end.Right && position.Y >= end.Top && position.Y < end.Bottom)
			return ScrollBy::EndArrow;
		RectF scroller{ getScrollerRect() };
		if (position.X >= scroller.Left && position.X < scroller.Right && position.Y >= scroller.Top && position.Y < scroller.Bottom)
			return ScrollBy::Scroller;
		if (m_bVertical)
		{
			if (position.X >= start.Left && position.X < start.Right && position.Y >= start.Bottom && position.Y < scroller.Top)
				return ScrollBy::BeforeScroller;
			if (position.X >= start.Left && position.X < start.Right && position.Y >= scroller.Bottom && position.Y < end.Top)
				return ScrollBy::AfterScroller;
		}
		else
		{
			if (position.X >= start.Right && position.X < scroller.Left && position.Y >= start.Top && position.Y < start.Bottom)
				return ScrollBy::BeforeScroller;
			if (position.X >= scroller.Right && position.X < end.Left && position.Y >= start.Top && position.Y < start.Bottom)
				return ScrollBy::AfterScroller;
		}
		return ScrollBy::None;
	}

	float CBuiltInScroll::PositionToScroll(const PointF &position)
	{
		float scroller_size, scrolling_area;
		CalculateScroller(scroller_size, scrolling_area);
		if (ntl::IsLessOrEqual<float>(scrolling_area, 0))
			return m_fMin;
		float arrow_size{ m_bArrowsVisible ? (m_bVertical ? (getWidth() - m_fBorderWidth) : (getHeight() - m_fBorderWidth)) : 0 };
		float p{ m_bVertical ? ((position.Y - arrow_size) / scrolling_area) : ((position.X - arrow_size) / scrolling_area) };
		return ntl::Clamp<float>(m_fMin + p * (m_fMax - m_fMin), m_fMin, m_fMax);
	}

	void CBuiltInScroll::SwitchDirection(const bool size)
	{
		// Background gradient types
		m_bIgnoreGradient = true;
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (!isVertical() && getBackgroundGradient((State)i)->Type == GradientType::Vertical)
				getBackgroundGradient((State)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getBackgroundGradient((State)i)->Type == GradientType::Horizontal)
				getBackgroundGradient((State)i)->setType(GradientType::Vertical);
		for (int i = 0; i <= (int)ElementState::DisabledDisabled; i++)
		{
			// Start arrow gradient type
			if (!isVertical() && getStartArrowBackgroundGradient((ElementState)i)->Type == GradientType::Vertical)
				getStartArrowBackgroundGradient((ElementState)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getStartArrowBackgroundGradient((ElementState)i)->Type == GradientType::Horizontal)
				getStartArrowBackgroundGradient((ElementState)i)->setType(GradientType::Vertical);
			// End arrow gradient type
			if (!isVertical() && getEndArrowBackgroundGradient((ElementState)i)->Type == GradientType::Vertical)
				getEndArrowBackgroundGradient((ElementState)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getEndArrowBackgroundGradient((ElementState)i)->Type == GradientType::Horizontal)
				getEndArrowBackgroundGradient((ElementState)i)->setType(GradientType::Vertical);
			// Scroller gradient type
			if (!isVertical() && getScrollerBackgroundGradient((ElementState)i)->Type == GradientType::Vertical)
				getScrollerBackgroundGradient((ElementState)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getScrollerBackgroundGradient((ElementState)i)->Type == GradientType::Horizontal)
				getScrollerBackgroundGradient((ElementState)i)->setType(GradientType::Vertical);
		}
		m_bIgnoreGradient = false;
		m_bVertical = !m_bVertical;
		if (size)
			setSize(PointF{ getHeight(), getWidth() });
	}
#pragma endregion

#pragma region Paint
	void CBuiltInScroll::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (getControl() && getControl()->getForm() && getControl()->getForm()->getRenderer())
		{
			IRenderer *renderer{ getControl()->getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			ITexture *canvas{ renderer->CreateTexture(ntl::Round<int>(all_rect.width()), ntl::Round<int>(all_rect.height()), 1, TextureFormat::RGBA, true) };
			if (canvas)
			{
				{
					CStoreTarget s_target{ renderer };
					renderer->ActivateTarget(canvas);
					renderer->Clear(Color{ 0, 0, 0, 0 });

					RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
					RenderBackground(renderer, state, rect);
					RenderStartArrow(renderer, disp);
					RenderEndArrow(renderer, disp);
					RenderScroller(renderer, disp);
				}
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(-disp.X, -disp.Y, 0))
					->DrawImage(canvas, 1);
				canvas->Release();
			}
		}
	}

	void CBuiltInScroll::RenderBackground(IRenderer *renderer, const State state, const RectF &rect)
	{
		DrawBlockShadow(
			renderer,
			rect,
			RectF{ m_fBorderRadius, m_fBorderRadius, m_fBorderRadius, m_fBorderRadius },
			m_aShadowColor[(int)state],
			m_aShadowShift[(int)state],
			m_aShadowRadius[(int)state]);
		DrawSimpleBackground(
			renderer,
			rect,
			RectF{ m_fBorderWidth, m_fBorderWidth, m_fBorderWidth, m_fBorderWidth },
			RectF{ m_fBorderRadius, m_fBorderRadius, m_fBorderRadius, m_fBorderRadius },
			BorderColor{ m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state] }, m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
	}

	void CBuiltInScroll::RenderStartArrow(IRenderer *renderer, const PointF &disp)
	{
		ElementState state{ getElementState(ElementType::StartArrow) };
		RectF rect{ getStartArrowRect() };
		if (rect.is_zero())
			return;
		rect += disp;
		Block b{
			rect,
			RectF{ m_fStartArrowBorderWidth, m_fStartArrowBorderWidth, m_fStartArrowBorderWidth, m_fStartArrowBorderWidth },
			RectF{ m_fStartArrowBorderRadius, m_fStartArrowBorderRadius, m_fStartArrowBorderRadius, m_fStartArrowBorderRadius },
			PointLocation::Inside };
		DrawSimpleBackground(
			renderer,
			rect,
			b.Border,
			b.Radius,
			BorderColor{ m_aStartArrowBorderColor[(int)state], m_aStartArrowBorderColor[(int)state], m_aStartArrowBorderColor[(int)state], m_aStartArrowBorderColor[(int)state] }, m_aStartArrowBackgroundColor[(int)state], m_aStartArrowBackgroundGradient[(int)state]);
		// Arrow
		if (m_aStartArrowColor1[(int)state].A > 0 || m_aStartArrowColor2[(int)state].A > 0 || m_aStartArrowColor3[(int)state].A > 0)
		{
			PointF center{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
			if (m_bVertical)
			{
				float size{ (rect.width() - 2 * m_fStartArrowBorderWidth) * m_fArrowSize };
				if (ntl::IsGreater<float>(size, 0))
				{
					PointF pos1{ center.X - size * 0.5f, center.Y + size * 0.25f };
					PointF pos2{ center.X, center.Y - size * 0.25f };
					PointF pos3{ center.X + size * 0.5f, center.Y + size * 0.25f };
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawTriangle(pos1, pos2, pos3, m_aStartArrowColor1[(int)state], m_aStartArrowColor2[(int)state], m_aStartArrowColor3[(int)state]);
				}
			}
			else
			{
				float size{ (rect.height() - 2 * m_fStartArrowBorderWidth) * m_fArrowSize };
				if (ntl::IsGreater<float>(size, 0))
				{
					PointF pos1{ center.X + size * 0.25f, center.Y + size * 0.5f };
					PointF pos2{ center.X - size * 0.25f, center.Y };
					PointF pos3{ center.X + size * 0.25f, center.Y - size * 0.5f };
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawTriangle(pos1, pos2, pos3, m_aStartArrowColor1[(int)state], m_aStartArrowColor2[(int)state], m_aStartArrowColor3[(int)state]);
				}
			}
		}
	}

	void CBuiltInScroll::RenderEndArrow(IRenderer *renderer, const PointF &disp)
	{
		ElementState state{ getElementState(ElementType::EndArrow) };
		RectF rect{ getEndArrowRect() };
		if (rect.is_zero())
			return;
		rect += disp;
		Block b{
			rect,
			RectF{ m_fEndArrowBorderWidth, m_fEndArrowBorderWidth, m_fEndArrowBorderWidth, m_fEndArrowBorderWidth },
			RectF{ m_fEndArrowBorderRadius, m_fEndArrowBorderRadius, m_fEndArrowBorderRadius, m_fEndArrowBorderRadius },
			PointLocation::Inside };
		DrawSimpleBackground(
			renderer,
			rect,
			b.Border,
			b.Radius,
			BorderColor{ m_aEndArrowBorderColor[(int)state], m_aEndArrowBorderColor[(int)state], m_aEndArrowBorderColor[(int)state], m_aEndArrowBorderColor[(int)state] }, m_aEndArrowBackgroundColor[(int)state], m_aEndArrowBackgroundGradient[(int)state]);
		// Arrow
		if (m_aEndArrowColor1[(int)state].A > 0 || m_aEndArrowColor2[(int)state].A > 0 || m_aEndArrowColor3[(int)state].A > 0)
		{
			PointF center{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
			if (m_bVertical)
			{
				float size{ (rect.width() - 2 * m_fEndArrowBorderWidth) * m_fArrowSize };
				if (ntl::IsGreater<float>(size,0))
				{
					PointF pos1{ center.X + size * 0.5f, center.Y - size * 0.25f };
					PointF pos2{ center.X, center.Y + size * 0.25f };
					PointF pos3{ center.X - size * 0.5f, center.Y - size * 0.25f };
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawTriangle(pos1, pos2, pos3, m_aEndArrowColor1[(int)state], m_aEndArrowColor2[(int)state], m_aEndArrowColor3[(int)state]);
				}
			}
			else
			{
				float size{ (rect.height() - 2 * m_fEndArrowBorderWidth) * m_fArrowSize };
				if (ntl::IsGreater<float>(size, 0))
				{
					PointF pos1{ center.X + size * 0.25f, center.Y };
					PointF pos2{ center.X - size * 0.25f, center.Y + size * 0.5f };
					PointF pos3{ center.X - size * 0.25f, center.Y - size * 0.5f };
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawTriangle(pos1, pos2, pos3, m_aEndArrowColor1[(int)state], m_aEndArrowColor2[(int)state], m_aEndArrowColor3[(int)state]);
				}
			}
		}
	}

	void CBuiltInScroll::RenderScroller(IRenderer *renderer, const PointF &disp)
	{
		ElementState state{ getElementState(ElementType::Scroller) };
		RectF rect{ getScrollerRect() };
		if (rect.is_zero())
			return;
		rect += disp;
		Block b{
			rect,
			RectF{ m_fScrollerBorderWidth, m_fScrollerBorderWidth, m_fScrollerBorderWidth, m_fScrollerBorderWidth },
			RectF{ m_fScrollerBorderRadius, m_fScrollerBorderRadius, m_fScrollerBorderRadius, m_fScrollerBorderRadius },
			PointLocation::Inside };
		DrawSimpleBackground(
			renderer,
			rect,
			b.Border,
			b.Radius,
			BorderColor{ m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state] }, m_aScrollerBackgroundColor[(int)state], m_aScrollerBackgroundGradient[(int)state]);
		// Rectangles
		if (m_bVertical)
		{
			float w{ (rect.width() - 2 * m_fScrollerBorderWidth) * m_sScrollerLinesSize.X };
			float h{ m_sScrollerLinesSize.Y };
			float sh{ rect.height() - 2 * m_fScrollerBorderWidth };
			if (ntl::IsGreater<float>(sh, (h + m_fScrollerLinesDistance) * 3))
			{
				PointF center{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
				Color colors[(int)PointLocation::Outside + 1]{
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBackgroundColor[(int)state],
					Color{ 0, 0, 0, 0 }
				};
				RectF borders{ m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth };
				renderer->DrawBlock(
					RectF{ center.X - w * 0.5f, center.Y - h * 1.5f - m_fScrollerLinesDistance, center.X + w * 0.5f, center.Y - h * 0.5f - m_fScrollerLinesDistance },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
				renderer->DrawBlock(
					RectF{ center.X - w * 0.5f, center.Y - h * 0.5f, center.X + w * 0.5f, center.Y + h * 0.5f },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
				renderer->DrawBlock(
					RectF{ center.X - w * 0.5f, center.Y + h * 0.5f + m_fScrollerLinesDistance, center.X + w * 0.5f, center.Y + h * 1.5f + m_fScrollerLinesDistance },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
			}
		}
		else
		{
			float w{ m_sScrollerLinesSize.Y };
			float h{ (rect.height() - 2 * m_fScrollerBorderWidth) * m_sScrollerLinesSize.X };
			float sw{ rect.width() - 2 * m_fScrollerBorderWidth };
			if (ntl::IsGreater<float>(sw, (w + m_fScrollerLinesDistance) * 3))
			{
				PointF center{ (rect.Left + rect.Right) * 0.5f, (rect.Top + rect.Bottom) * 0.5f };
				Color colors[(int)PointLocation::Outside + 1]{
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBorderColor[(int)state],
					m_aScrollerLinesBackgroundColor[(int)state],
					Color{ 0, 0, 0, 0 }
				};
				RectF borders{ m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth, m_fScrollerLinesBorderWidth };
				renderer->DrawBlock(
					RectF{ center.X - w * 1.5f - m_fScrollerLinesDistance, center.Y - h * 0.5f, center.X - w * 0.5f - m_fScrollerLinesDistance, center.Y + h * 0.5f },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
				renderer->DrawBlock(
					RectF{ center.X - w * 0.5f, center.Y - h * 0.5f, center.X + w * 0.5f, center.Y + h * 0.5f },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
				renderer->DrawBlock(
					RectF{ center.X + w * 0.5f + m_fScrollerLinesDistance, center.Y - h * 0.5f, center.X + w * 1.5f + m_fScrollerLinesDistance, center.Y + h * 0.5f },
					borders,
					RectF{ 0, 0, 0, 0 },
					colors);
			}
		}
	}
#pragma endregion
}