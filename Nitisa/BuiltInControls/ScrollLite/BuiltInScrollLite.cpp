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
#pragma region CTimerListener
	CBuiltInScrollLite::CTimerListener::CTimerListener(CBuiltInScrollLite *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInScrollLite::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		float limit{ m_pControl->PositionToScroll(m_pControl->m_sScrollPosition) };
		IBuiltInScrollListener *listener{ cast<IBuiltInScrollListener*>(m_pControl->m_pListener) };
		switch (m_pControl->m_eScrollBy)
		{
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
	CBuiltInScrollLite::CGradientListener::CGradientListener(CBuiltInScrollLite *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInScrollLite::CGradientListener::NotifyOnChange()
	{
		if (!m_pControl->m_bIgnoreGradient && m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRenderRect());
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInScrollLite::CBuiltInScrollLite() :
		CBuiltInControl(L"ScrollLite", PointF{ 123, 10 }),
		m_cGradientListener{ this },
		m_fMin{ 0 },
		m_fMax{ 100 },
		m_fScroll{ 0 },
		m_fScrollerSize{ 0 },
		m_fDeltaMedium{ 10 },
		m_fDeltaLarge{ 0 },
		m_bVertical{ false },
		m_fScrollInterval{ ScrollInterval },
		m_aShadowRadius{ 1, 1, 1, 1 },
		m_aShadowColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aShadowShift{
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 } },
		m_bBorderRound{ true },
		m_fBorderWidth{ 0 },
		m_aBorderColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aBackgroundColor{
			Color{ 53, 53, 53, 255 },
			Color{ 53, 53, 53, 255 },
			Color{ 53, 53, 53, 255 },
			Color{ 53, 53, 53, 255 } },
		m_aBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_bScrollerRound{ true },
		m_fScrollerBorderWidth{ 1 },
		m_aScrollerBorderColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aScrollerBackgroundColor{
			Color{ 90, 90, 90, 255 },
			Color{ 111, 111, 111, 255 },
			Color{ 61, 123, 173, 255 },
			Color{ 0, 0, 0, 0 } },
		m_aScrollerBackgroundGradient{
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener },
			Gradient{ &m_cGradientListener } },
		m_eHoveredElement{ ElementType::None },
		m_eActiveElement{ ElementType::None },
		m_pListener{ nullptr },
		m_bScrolling{ false },
		m_bHovered{ false },
		m_hTimer{ nullptr },
		m_bIgnoreGradient{ false },
		m_cTimerListener{ this }
	{
		
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInScrollLite::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInScrollLite::isHovered()
	{
		return m_bHovered;
	}

	RectF CBuiltInScrollLite::getRenderRect()
	{
		RectF result{ getRect() }, r{ result };
		for (int i = 0; i <= (int)State::Disabled; i++)
			result += AddShadow(r, m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
		return result;
	}

	bool CBuiltInScrollLite::isDown()
	{
		return m_bScrolling;
	}
#pragma endregion

#pragma region IBuiltInScroll getters
	float CBuiltInScrollLite::getMin()
	{
		return m_fMin;
	}

	float CBuiltInScrollLite::getMax()
	{
		return m_fMax;
	}

	float CBuiltInScrollLite::getScroll()
	{
		return m_fScroll;
	}

	float CBuiltInScrollLite::getScrollerSize()
	{
		return m_fScrollerSize;
	}

	float CBuiltInScrollLite::getDeltaSmall()
	{
		return 0;
	}

	float CBuiltInScrollLite::getDeltaMedium()
	{
		return m_fDeltaMedium;
	}

	float CBuiltInScrollLite::getDeltaLarge()
	{
		return m_fDeltaLarge;
	}

	bool CBuiltInScrollLite::isVertical()
	{
		return m_bVertical;
	}

	bool CBuiltInScrollLite::isArrowsVisible()
	{
		return false;
	}
#pragma endregion

#pragma region Getters
	CBuiltInScrollLite::State CBuiltInScrollLite::getState()
	{
		if (!isEnabled())
			return State::Disabled;
		if (m_bScrolling)
			return State::Active;
		if (m_bHovered)
			return State::Hovered;
		return State::Normal;
	}

	CBuiltInScrollLite::ElementType CBuiltInScrollLite::getHoveredElement() const
	{
		return m_eHoveredElement;
	}

	CBuiltInScrollLite::ElementType CBuiltInScrollLite::getActiveElement() const
	{
		return m_eActiveElement;
	}

	float CBuiltInScrollLite::getScrollInterval() const
	{
		return m_fScrollInterval;
	}

	bool CBuiltInScrollLite::isBorderRound() const
	{
		return m_bBorderRound;
	}

	int CBuiltInScrollLite::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state];
	}

	Color CBuiltInScrollLite::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state];
	}

	PointF CBuiltInScrollLite::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state];
	}

	float CBuiltInScrollLite::getBorderWidth() const
	{
		return m_fBorderWidth;
	}

	Color CBuiltInScrollLite::getBorderColor(const State state) const
	{
		return m_aBorderColor[(int)state];
	}

	Color CBuiltInScrollLite::getBackgroundColor(const State state) const
	{
		return m_aBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScrollLite::getBackgroundGradient(const State state)
	{
		return &m_aBackgroundGradient[(int)state];
	}

	bool CBuiltInScrollLite::isScrollerRound() const
	{
		return m_bScrollerRound;
	}

	float CBuiltInScrollLite::getScrollerBorderWidth() const
	{
		return m_fScrollerBorderWidth;
	}

	Color CBuiltInScrollLite::getScrollerBorderColor(const State state) const
	{
		return m_aScrollerBorderColor[(int)state];
	}

	Color CBuiltInScrollLite::getScrollerBackgroundColor(const State state) const
	{
		return m_aScrollerBackgroundColor[(int)state];
	}

	Gradient *CBuiltInScrollLite::getScrollerBackgroundGradient(const State state)
	{
		return &m_aScrollerBackgroundGradient[(int)state];
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInScrollLite::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInScrollLite::setEnabled(const bool value)
	{
		if (CBuiltInControl::setEnabled(value))
		{
			if (!isEnabled())
				m_bScrolling = false;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
			float avg{ (s.X + s.Y) / 2 };
			m_fScrollerSize *= avg;
			m_fDeltaMedium *= avg;
			m_fDeltaLarge *= avg;
			m_fBorderWidth *= avg;
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
				m_aShadowShift[i] *= s;
			}
			m_fScrollerBorderWidth *= avg;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInScroll setters
	bool CBuiltInScrollLite::setMin(const float value)
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

	bool CBuiltInScrollLite::setMax(const float value)
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

	bool CBuiltInScrollLite::setScroll(const float value)
	{
		float v{ ntl::Clamp<float>(value, m_fMin, m_fMax) };
		if (ntl::IsNotEqual<float>(v, m_fScroll))
		{
			m_fScroll = v;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setScrollerSize(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerSize))
		{
			m_fScrollerSize = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setDeltaSmall(const float value)
	{
		return false;
	}

	bool CBuiltInScrollLite::setDeltaMedium(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDeltaMedium))
		{
			m_fDeltaMedium = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setDeltaLarge(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fDeltaLarge))
		{
			m_fDeltaLarge = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setVertical(const bool value)
	{
		if (value != m_bVertical)
		{
			m_bVertical = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setArrowsVisible(const bool value)
	{
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInScrollLite::setScrollInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
		{
			m_fScrollInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setShadowRadius(const State state, const int value)
	{
		if (value >= 1 && value != m_aShadowRadius[(int)state])
		{
			m_aShadowRadius[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state])
		{
			m_aShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state]))
		{
			m_aShadowShift[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setBorderRound(const bool value)
	{
		if (value != m_bBorderRound)
		{
			m_bBorderRound = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fBorderWidth))
		{
			m_fBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setBorderColor(const State state, const Color &value)
	{
		if (value != m_aBorderColor[(int)state])
		{
			m_aBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aBackgroundColor[(int)state])
		{
			m_aBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setScrollerRound(const bool value)
	{
		if (value != m_bScrollerRound)
		{
			m_bScrollerRound = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setScrollerBorderWidth(const float value)
	{
		if (value >= 0 && ntl::IsNotEqual<float>(value, m_fScrollerBorderWidth))
		{
			m_fScrollerBorderWidth = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setScrollerBorderColor(const State state, const Color &value)
	{
		if (value != m_aScrollerBorderColor[(int)state])
		{
			m_aScrollerBorderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setScrollerBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aScrollerBackgroundColor[(int)state])
		{
			m_aScrollerBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInScrollLite::setShadowRadius(const int value)
	{
		if (value >= 1)
		{
			bool changed{ false };
			for (int i = 0; i <= (int)State::Disabled; i++)
				if (m_aShadowRadius[i] != value)
				{
					m_aShadowRadius[i] = value;
					changed = true;
				}
			return changed;
		}
		return false;
	}

	bool CBuiltInScrollLite::setShadowShift(const PointF &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (IsNotEqual(m_aShadowShift[i], value))
			{
				m_aShadowShift[i] = value;
				changed = true;
			}
		return changed;
	}

	bool CBuiltInScrollLite::setShadowColor(const Color &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (m_aShadowColor[i] != value)
			{
				m_aShadowColor[i] = value;
				changed = true;
			}
		return changed;
	}

	bool CBuiltInScrollLite::setBorderColor(const Color &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (m_aBorderColor[i] != value)
			{
				m_aBorderColor[i] = value;
				changed = true;
			}
		return changed;
	}

	bool CBuiltInScrollLite::setBackgroundColor(const Color &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (m_aBackgroundColor[i] != value)
			{
				m_aBackgroundColor[i] = value;
				changed = true;
			}
		return changed;
	}

	bool CBuiltInScrollLite::setScrollerBorderColor(const Color &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (m_aScrollerBorderColor[i] != value)
			{
				m_aScrollerBorderColor[i] = value;
				changed = true;
			}
		return changed;
	}

	bool CBuiltInScrollLite::setScrollerBackgroundColor(const Color &value)
	{
		bool changed{ false };
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (m_aScrollerBackgroundColor[i] != value)
			{
				m_aScrollerBackgroundColor[i] = value;
				changed = true;
			}
		return changed;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CBuiltInScrollLite::UpdateFromStyle(IStyle *style, const String &class_name)
	{
		m_bIgnoreGradient = true;
		style->getOption(class_name + L".DeltaMedium", m_fDeltaMedium);
		style->getOption(class_name + L".DeltaLarge", m_fDeltaLarge);
		style->getOption(class_name + L".ScrollInterval", m_fScrollInterval);
		style->getOption(class_name + L".BorderWidth", m_fBorderWidth);
		style->getOption(class_name + L".ScrollerBorderWidth", m_fScrollerBorderWidth);
		style->getOption(class_name + L".BorderRound", m_bBorderRound);
		style->getOption(class_name + L".ScrollerRound", m_bScrollerRound);
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

			style->getOption(class_name + L".ScrollerBorderColor[" + state + L"]", m_aScrollerBorderColor[i]);
			style->getOption(class_name + L".ScrollerBackgroundColor[" + state + L"]", m_aScrollerBackgroundColor[i]);
			style->getOption(class_name + L".ScrollerBackgroundGradient[" + state + L"]", m_aScrollerBackgroundGradient[i]);
		}
		m_bIgnoreGradient = false;
	}

	void CBuiltInScrollLite::Update()
	{
		// Not required
	}
#pragma endregion

#pragma region Helpers
	bool CBuiltInScrollLite::UpdateHoveredElement(const PointF &position)
	{
		if (getScrollerRect().is_inside(position))
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

	RectF CBuiltInScrollLite::getScrollerRect()
	{
		float scroller_size, scrolling_area;
		CalculateScroller(scroller_size, scrolling_area);
		float position{ (m_fScroll - m_fMin) * scrolling_area / (m_fMax - m_fMin) };
		RectF result{
			m_bVertical ? m_fBorderWidth : position,
			m_bVertical ? position : m_fBorderWidth,
			m_bVertical ? (getWidth() - m_fBorderWidth) : (position + scroller_size),
			m_bVertical ? (position + scroller_size) : (getHeight() - m_fBorderWidth)
		};
		result.validate();
		return result;
	}

	void CBuiltInScrollLite::CalculateScroller(float &scroller_size, float &scrolling_area)
	{
		float size{ m_bVertical ? getHeight() : getWidth() };
		if (ntl::IsGreater<float>(m_fScrollerSize, 0))
		{
			if (m_bScrollerRound)
				scroller_size = ntl::Max<float>(ntl::Min<float>(getWidth(), getHeight()) * 0.5f, m_fScrollerSize, 2);
			else
				scroller_size = ntl::Max<float>(m_fScrollerSize, 2);
		}
		else
		{
			if (size >= m_fMax - m_fMin)
				scroller_size = 0;
			else
				scroller_size = size * size / (m_fMax - m_fMin);
			if (m_bScrollerRound)
				ntl::Max<float>(ntl::Min<float>(getWidth(), getHeight()) * 0.5f, scroller_size, 2);
			else
				scroller_size = ntl::Max<float>(scroller_size, 2);
		}
		if (scroller_size >= size)
			scroller_size = 0;
		scrolling_area = size - scroller_size;
	}

	float CBuiltInScrollLite::CalculateDeltaLarge()
	{
		if (ntl::IsGreater<float>(m_fDeltaLarge, 0))
			return m_fDeltaLarge;
		float scroller_size, scrolling_area;
		CalculateScroller(scroller_size, scrolling_area);
		if (ntl::IsGreater<float>(scroller_size, 0))
			return scroller_size;
		return m_fMax - m_fMin;
	}

	CBuiltInScrollLite::State CBuiltInScrollLite::getElementState(const ElementType element)
	{
		if (!isEnabled())
			return State::Disabled;
		if (m_bScrolling)
		{
			if (m_eActiveElement == element)
				return State::Active;
			return State::Normal;
		}
		if (m_eHoveredElement == element)
			return State::Hovered;
		return State::Normal;
	}

	CBuiltInScrollLite::ScrollBy CBuiltInScrollLite::getScrollElement(const PointF &position)
	{
		RectF scroller{ getScrollerRect() };
		if (scroller.is_inside(position))
			return ScrollBy::Scroller;
		if (m_bVertical)
		{
			if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < scroller.Top)
				return ScrollBy::BeforeScroller;
			if (position.X >= 0 && position.X < getWidth() && position.Y >= scroller.Bottom && position.Y < getHeight())
				return ScrollBy::AfterScroller;
		}
		else
		{
			if (position.X >= 0 && position.X < scroller.Left && position.Y >= 0 && position.Y < getHeight())
				return ScrollBy::BeforeScroller;
			if (position.X >= scroller.Right && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight())
				return ScrollBy::AfterScroller;
		}
		return ScrollBy::None;
	}

	float CBuiltInScrollLite::PositionToScroll(const PointF &position)
	{
		float scroller_size, scrolling_area;
		CalculateScroller(scroller_size, scrolling_area);
		if (ntl::IsLessOrEqual<float>(scrolling_area, 0))
			return m_fMin;
		float p{ m_bVertical ? (position.Y / scrolling_area) : (position.X / scrolling_area) };
		return ntl::Clamp<float>(m_fMin + p * (m_fMax - m_fMin), m_fMin, m_fMax);
	}

	void CBuiltInScrollLite::SwitchDirection(const bool size)
	{
		// Background gradient types
		m_bIgnoreGradient = true;
		for (int i = 0; i <= (int)State::Disabled; i++)
			if (!isVertical() && getBackgroundGradient((State)i)->Type == GradientType::Vertical)
				getBackgroundGradient((State)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getBackgroundGradient((State)i)->Type == GradientType::Horizontal)
				getBackgroundGradient((State)i)->setType(GradientType::Vertical);
		for (int i = 0; i <= (int)State::Disabled; i++)
		{
			// Scroller gradient type
			if (!isVertical() && getScrollerBackgroundGradient((State)i)->Type == GradientType::Vertical)
				getScrollerBackgroundGradient((State)i)->setType(GradientType::Horizontal);
			else if (isVertical() && getScrollerBackgroundGradient((State)i)->Type == GradientType::Horizontal)
				getScrollerBackgroundGradient((State)i)->setType(GradientType::Vertical);
		}
		m_bIgnoreGradient = false;
		m_bVertical = !m_bVertical;
		if (size)
			setSize(PointF{ getHeight(), getWidth() });
	}
#pragma endregion

#pragma region Paint
	void CBuiltInScrollLite::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
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
					renderer
						->ActivateTarget(canvas)
						->Clear(Color{ 0, 0, 0, 0 });

					RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
					RenderBackground(renderer, state, rect);
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

	void CBuiltInScrollLite::RenderBackground(IRenderer *renderer, const State state, const RectF &rect)
	{
		float radius{ m_bBorderRound ? std::floor(ntl::Min<float>(getWidth(), getHeight()) * 0.5f) : 0 };
		float border{ std::floor(ntl::Min<float>(m_fBorderWidth, getWidth() * 0.5f, getHeight() * 0.5f)) };
		DrawBlockShadow(
			renderer,
			rect,
			RectF{ radius, radius, radius, radius },
			m_aShadowColor[(int)state],
			m_aShadowShift[(int)state],
			m_aShadowRadius[(int)state]);
		DrawSimpleBackground(
			renderer,
			rect,
			RectF{ border, border, border, border },
			RectF{ radius, radius, radius, radius },
			BorderColor{ m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state], m_aBorderColor[(int)state] },
			m_aBackgroundColor[(int)state],
			m_aBackgroundGradient[(int)state]);
	}

	void CBuiltInScrollLite::RenderScroller(IRenderer *renderer, const PointF &disp)
	{
		State state{ getElementState(ElementType::Scroller) };
		RectF rect{ getScrollerRect() };
		if (rect.is_zero())
			return;
		rect += disp;
		float radius{ m_bScrollerRound ? std::floor(ntl::Min<float>(rect.width() * 0.5f, rect.height() * 0.5f)) : 0 };
		float border{ std::floor(ntl::Min<float>(m_fScrollerBorderWidth, getWidth() * 0.5f, getHeight() * 0.5f)) };
		DrawSimpleBackground(
			renderer,
			rect,
			RectF{ border, border, border, border },
			RectF{ radius, radius, radius, radius },
			BorderColor{ m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state], m_aScrollerBorderColor[(int)state] },
			m_aScrollerBackgroundColor[(int)state],
			m_aScrollerBackgroundGradient[(int)state]);
	}
#pragma endregion
}