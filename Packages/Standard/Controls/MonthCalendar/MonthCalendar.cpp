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
	namespace standard
	{
	#pragma region CGradientListener
		CMonthCalendar::CGradientListener::CGradientListener(CMonthCalendar *control) :
			m_pControl{ control }
		{

		}

		void CMonthCalendar::CGradientListener::NotifyOnChange()
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
		CMonthCalendar::CMonthCalendar():
			CControl(L"MonthCalendar", true, true, false, false, false, false),
			m_cGradientListener{ this },
			m_sOuterBorderWidth{ 1, 1, 1, 1 },
			m_sInnerBorderWidth{ 0, 0, 0, 0 },
			m_sPadding{ 5, 3, 5, 3 },
			m_aShadowRadius{ 1, 1, 1 },
			m_aShadowShift{
				PointF{ 0, 0 },
				PointF{ 0, 0 },
				PointF{ 0, 0 } },
			m_aShadowColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 } },
			m_aBorderRadius{
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 },
				RectF{ 0, 0, 0, 0 } },
			m_aOuterBorderColor{
				BorderColor{ Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 } },
				BorderColor{ Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 } },
				BorderColor{ Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 }, Color{ 151, 151, 151, 255 } } },
			m_aInnerBorderColor{
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_pCanvas{ nullptr },
			m_pMonthCalendar{ nullptr },
			m_bIgnoreGradient{ false },
			m_cListener{ this }
		{
			OnChange = nullptr;
			setService(new CMonthCalendarService(this), true);
		}

		CMonthCalendar::CMonthCalendar(IForm *parent) :CMonthCalendar()
		{
			setForm(parent);
		}

		CMonthCalendar::CMonthCalendar(IControl *parent) : CMonthCalendar()
		{
			setParent(parent);
		}

		CMonthCalendar::~CMonthCalendar()
		{
			if (m_pMonthCalendar)
				m_pMonthCalendar->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CMonthCalendar::getClientRect()
		{
			RectF result{
				m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left,
				m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sInnerBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Bottom - m_sPadding.Bottom
			};
			result.validate();
			return result;
		}

		RectF CMonthCalendar::getRenderRect()
		{
			RectF result{ AddShadow(getRect(), m_aShadowColor[0], m_aShadowShift[0], m_aShadowRadius[0]) };
			for (int i = 1; i <= (int)State::Disabled; i++)
				result += AddShadow(getRect(), m_aShadowColor[i], m_aShadowShift[i], m_aShadowRadius[i]);
			return result;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CMonthCalendar::setAlign(const Align value)
		{
			return false;
		}

		bool CMonthCalendar::setConstraints(const RectF &value)
		{
			return false;
		}

		bool CMonthCalendar::setSize(const PointF &value)
		{
			return false;
		}

		bool CMonthCalendar::setDPI(const Point &value)
		{
			CLockRepaint lock{ this };
			Point old{ getDPI() };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sOuterBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_sPadding *= s;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
					m_aBorderRadius[i] *= avg;
				}
				getMonthCalendar()->setDPI(value);
				UpdateSize();
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CMonthCalendar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getMonthCalendar()->Refresh();
		}
	#pragma endregion

	#pragma region IMonthCalendar getters
		int CMonthCalendar::getYear()
		{
			return getMonthCalendar()->getYear();
		}

		int CMonthCalendar::getMonth()
		{
			return getMonthCalendar()->getMonth();
		}

		int CMonthCalendar::getDay()
		{
			return getMonthCalendar()->getDay();
		}

		int CMonthCalendar::getMinYear()
		{
			return getMonthCalendar()->getMinYear();
		}

		int CMonthCalendar::getMinMonth()
		{
			return getMonthCalendar()->getMinMonth();
		}

		int CMonthCalendar::getMinDay()
		{
			return getMonthCalendar()->getMinDay();
		}

		int CMonthCalendar::getMaxYear()
		{
			return getMonthCalendar()->getMaxYear();
		}

		int CMonthCalendar::getMaxMonth()
		{
			return getMonthCalendar()->getMaxMonth();
		}

		int CMonthCalendar::getMaxDay()
		{
			return getMonthCalendar()->getMaxDay();
		}
	#pragma endregion

	#pragma region IMonthCalendar setters
		bool CMonthCalendar::setYear(const int value)
		{
			if (getMonthCalendar()->setYear(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMonth(const int value)
		{
			if (getMonthCalendar()->setMonth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDay(const int value)
		{
			if (getMonthCalendar()->setDay(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMinYear(const int value)
		{
			if (getMonthCalendar()->setMinYear(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMinMonth(const int value)
		{
			if (getMonthCalendar()->setMinMonth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMinDay(const int value)
		{
			if (getMonthCalendar()->setMinDay(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMaxYear(const int value)
		{
			if (getMonthCalendar()->setMaxYear(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMaxMonth(const int value)
		{
			if (getMonthCalendar()->setMaxMonth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setMaxDay(const int value)
		{
			if (getMonthCalendar()->setMaxDay(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IMonthCalendar methods
		bool CMonthCalendar::Next()
		{
			if (getMonthCalendar()->Next())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::Prev()
		{
			if (getMonthCalendar()->Prev())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::Today()
		{
			if (getMonthCalendar()->Today())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		CMonthCalendar::State CMonthCalendar::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		RectF CMonthCalendar::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		RectF CMonthCalendar::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		RectF CMonthCalendar::getPadding() const
		{
			return m_sPadding;
		}

		int CMonthCalendar::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CMonthCalendar::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CMonthCalendar::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		RectF CMonthCalendar::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		BorderColor CMonthCalendar::getOuterBorderColor(const State state) const
		{
			return m_aOuterBorderColor[(int)state];
		}

		BorderColor CMonthCalendar::getInnerBorderColor(const State state) const
		{
			return m_aInnerBorderColor[(int)state];
		}

		Color CMonthCalendar::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CMonthCalendar::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CMonthCalendar::setMonthCalendar(IBuiltInMonthCalendar *value)
		{
			if (value && value != m_pMonthCalendar)
			{
				if (m_pMonthCalendar)
					m_pMonthCalendar->Release();
				m_pMonthCalendar = value;
				m_pMonthCalendar->setListener(&m_cListener);
				UpdateSize();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setOuterBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBorderWidth))
			{
				m_sOuterBorderWidth = value;
				UpdateSize();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setInnerBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBorderWidth))
			{
				m_sInnerBorderWidth = value;
				UpdateSize();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				UpdateSize();
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setShadowRadius(const State state, const int value)
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
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setShadowShift(const State state, const PointF &value)
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
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setShadowColor(const State state, const Color &value)
		{
			if (value != m_aShadowColor[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				m_aShadowColor[(int)state] = value;
				if (state == s && m_aShadowColor[(int)state].A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setBorderRadius(const State state, const RectF &value)
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

		bool CMonthCalendar::setOuterBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aOuterBorderColor[(int)state])
			{
				m_aOuterBorderColor[(int)state] = value;
				if (m_sOuterBorderWidth.has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setInnerBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aInnerBorderColor[(int)state])
			{
				m_aInnerBorderColor[(int)state] = value;
				if (m_sInnerBorderWidth.has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setBackgroundColor(const State state, const Color &value)
		{
			if (value != m_aBackgroundColor[(int)state])
			{
				m_aBackgroundColor[(int)state] = value;
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
	#pragma endregion

	#pragma region CBuiltInMonthCalendar getters
		CBuiltInMonthCalendar::Mode CMonthCalendar::getMode()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getMode();
			return CBuiltInMonthCalendar::Mode::Month;
		}

		bool CMonthCalendar::isShowToday()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->isShowToday();
			return false;
		}

		RectF CMonthCalendar::getTitlePadding()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTodayPadding()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getElementPadding()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getDayPadding()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayPadding();
			return RectF{ 0, 0, 0, 0 };
		}

		float CMonthCalendar::getTodayMargin()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayMargin();
			return 0;
		}

		float CMonthCalendar::getTodayRectWidth()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectWidth();
			return 0;
		}

		bool CMonthCalendar::isAnimate()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->isAnimate();
			return false;
		}

		float CMonthCalendar::getAnimateInterval()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getAnimateInterval();
			return 0;
		}

		float CMonthCalendar::getAnimateMinScale()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getAnimateMinScale();
			return 0;
		}

		float CMonthCalendar::getAnimateTime()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getAnimateTime();
			return 0;
		}

		float CMonthCalendar::getScrollInterval()
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getScrollInterval();
			return 0;
		}

		TextAlign CMonthCalendar::getTitleAlign(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleAlign(state);
			return TextAlign::Left;
		}

		RectF CMonthCalendar::getTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getTitleBorderColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getTitleBackgroundGradient(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleBackgroundGradient(state);
			return nullptr;
		}

		Color CMonthCalendar::getTitleColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getTitlePrevRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeBackgroundGradient(state);
			return nullptr;
		}

		RectF CMonthCalendar::getTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangePadding(state);
			return RectF{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeColor1(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeColor2(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitlePrevRangeColor3(state);
			return Color{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getTitleNextRangeBackgroundGradient(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeBackgroundGradient(state);
			return nullptr;
		}

		RectF CMonthCalendar::getTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangePadding(state);
			return RectF{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeColor1(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeColor2(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTitleNextRangeColor3(state);
			return Color{ 0, 0, 0, 0 };
		}

		TextAlign CMonthCalendar::getTodayAlign(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayAlign(state);
			return TextAlign::Left;
		}

		RectF CMonthCalendar::getTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getTodayBorderColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getTodayBackgroundGradient(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayBackgroundGradient(state);
			return nullptr;
		}

		Color CMonthCalendar::getTodayColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getTodayRectBackgroundGradient(const CBuiltInMonthCalendar::TitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getTodayRectBackgroundGradient(state);
			return nullptr;
		}

		TextAlign CMonthCalendar::getElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementHorizontalAlign(state);
			return TextAlign::Left;
		}

		VerticalAlign CMonthCalendar::getElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementVerticalAlign(state);
			return VerticalAlign::Top;
		}

		RectF CMonthCalendar::getElementBorderRadius(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getElementBorderWidth(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getElementBorderColor(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getElementBackgroundGradient(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementBackgroundGradient(state);
			return nullptr;
		}

		Color CMonthCalendar::getElementColor(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMonthCalendar::getElementOutlineColor(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementOutlineColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		unsigned int CMonthCalendar::getElementOutlineMask(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getElementOutlineMask(state);
			return 0;
		}

		TextAlign CMonthCalendar::getDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayHorizontalAlign(state);
			return TextAlign::Left;
		}

		VerticalAlign CMonthCalendar::getDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayVerticalAlign(state);
			return VerticalAlign::Top;
		}

		TextAlign CMonthCalendar::getDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleHorizontalAlign(state);
			return TextAlign::Left;
		}

		VerticalAlign CMonthCalendar::getDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleVerticalAlign(state);
			return VerticalAlign::Top;
		}

		RectF CMonthCalendar::getDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleBorderRadius(state);
			return RectF{ 0, 0, 0, 0 };
		}

		RectF CMonthCalendar::getDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleBorderWidth(state);
			return RectF{ 0, 0, 0, 0 };
		}

		BorderColor CMonthCalendar::getDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleBorderColor(state);
			return BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } };
		}

		Color CMonthCalendar::getDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CMonthCalendar::getDayTitleBackgroundGradient(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleBackgroundGradient(state);
			return nullptr;
		}

		Color CMonthCalendar::getDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->getDayTitleColor(state);
			return Color{ 0, 0, 0, 0 };
		}
	#pragma endregion

	#pragma region CBuiltInMonthCalendar setters
		bool CMonthCalendar::setMode(const CBuiltInMonthCalendar::Mode value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setMode(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setShowToday(const bool value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setShowToday(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setTitlePadding(const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setTitlePadding(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setTodayPadding(const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setTodayPadding(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setElementPadding(const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setElementPadding(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setDayPadding(const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setDayPadding(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setTodayMargin(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setTodayMargin(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setTodayRectWidth(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
			{
				RectF r{ getRenderRect() };
				if (b->setTodayRectWidth(value))
				{
					UpdateSize();
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CMonthCalendar::setAnimate(const bool value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->setAnimate(value);
			return false;
		}

		bool CMonthCalendar::setAnimateInterval(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->setAnimateInterval(value);
			return false;
		}

		bool CMonthCalendar::setAnimateMinScale(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->setAnimateMinScale(value);
			return false;
		}

		bool CMonthCalendar::setAnimateTime(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->setAnimateTime(value);
			return false;
		}

		bool CMonthCalendar::setScrollInterval(const float value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b)
				return b->setScrollInterval(value);
			return false;
		}

		bool CMonthCalendar::setTitleAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangePadding(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeColor1(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeColor2(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitlePrevRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitlePrevRangeColor3(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangePadding(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangePadding(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeColor1(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeColor1(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeColor2(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeColor2(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTitleNextRangeColor3(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTitleNextRangeColor3(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayAlign(const CBuiltInMonthCalendar::TitleState state, const TextAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayRectBorderRadius(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayRectBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayRectBorderWidth(const CBuiltInMonthCalendar::TitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayRectBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayRectBorderColor(const CBuiltInMonthCalendar::TitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayRectBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setTodayRectBackgroundColor(const CBuiltInMonthCalendar::TitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setTodayRectBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementHorizontalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementVerticalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementBorderRadius(const CBuiltInMonthCalendar::ElementState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementBorderWidth(const CBuiltInMonthCalendar::ElementState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementBorderColor(const CBuiltInMonthCalendar::ElementState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementBackgroundColor(const CBuiltInMonthCalendar::ElementState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementColor(const CBuiltInMonthCalendar::ElementState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementOutlineColor(const CBuiltInMonthCalendar::ElementState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementOutlineColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setElementOutlineMask(const CBuiltInMonthCalendar::ElementState state, const unsigned int value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setElementOutlineMask(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayHorizontalAlign(const CBuiltInMonthCalendar::ElementState state, const TextAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayHorizontalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayVerticalAlign(const CBuiltInMonthCalendar::ElementState state, const VerticalAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayVerticalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleHorizontalAlign(const CBuiltInMonthCalendar::DayTitleState state, const TextAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleHorizontalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleVerticalAlign(const CBuiltInMonthCalendar::DayTitleState state, const VerticalAlign value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleVerticalAlign(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleBorderRadius(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleBorderRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleBorderWidth(const CBuiltInMonthCalendar::DayTitleState state, const RectF &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleBorderWidth(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleBorderColor(const CBuiltInMonthCalendar::DayTitleState state, const BorderColor &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleBackgroundColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMonthCalendar::setDayTitleColor(const CBuiltInMonthCalendar::DayTitleState state, const Color &value)
		{
			CBuiltInMonthCalendar *b{ cast<CBuiltInMonthCalendar*>(getMonthCalendar()) };
			if (b && b->setDayTitleColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		IBuiltInMonthCalendar *CMonthCalendar::getMonthCalendar()
		{
			if (!m_pMonthCalendar)
			{
				m_pMonthCalendar = new CBuiltIn(this);
				m_pMonthCalendar->setListener(&m_cListener);
			}
			return m_pMonthCalendar;
		}

		void CMonthCalendar::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L".InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Hovered:
					state = L"Hovered";
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
				style->getOption(m_sClassName + L".OuterBorderColor[" + state + L"]", m_aOuterBorderColor[i]);
				style->getOption(m_sClassName + L".InnerBorderColor[" + state + L"]", m_aInnerBorderColor[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
			}
			getMonthCalendar()->UpdateFromStyle(style, m_sClassName + L".MonthCalendar");
			UpdateSize();
			m_bIgnoreGradient = false;
		}

		void CMonthCalendar::UpdateSize()
		{
			PointF calendar_size{ getMonthCalendar()->getRequiredSize() };
			PointF size{
				calendar_size.X + m_sOuterBorderWidth.Left + m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Left + m_sInnerBorderWidth.Right + m_sPadding.Left + m_sPadding.Right,
				calendar_size.Y + m_sOuterBorderWidth.Top + m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Top + m_sInnerBorderWidth.Bottom + m_sPadding.Top + m_sPadding.Bottom };
			CControl::setSize(size);
			getMonthCalendar()->setSize(calendar_size);
			getMonthCalendar()->setPosition(PointF{ m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left + m_sPadding.Left, m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top + m_sPadding.Top });
			getMonthCalendar()->Update();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
		}
	#pragma endregion

	#pragma region Paint
		void CMonthCalendar::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (!m_pCanvas || !m_pCanvas->isValid() || getMonthCalendar()->isAnimating())
			{
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
						m_sOuterBorderWidth,
						m_sInnerBorderWidth,
						m_aBorderRadius[(int)state],
						m_aOuterBorderColor[(int)state],
						m_aInnerBorderColor[(int)state],
						m_aBackgroundColor[(int)state],
						m_aBackgroundGradient[(int)state]);

					Mat4f t;
					ntl::Translate<float>(t, getMonthCalendar()->getLeft(), getMonthCalendar()->getTop(), 0);
					if (m_aBorderRadius[(int)state].has_positive() || m_sInnerBorderWidth.has_positive() || m_sOuterBorderWidth.has_positive())
					{
						Block b{ rect, AddElements(m_sOuterBorderWidth, m_sInnerBorderWidth, m_sPadding), m_aBorderRadius[(int)state], PointLocation::Inside };
						getMonthCalendar()->Render(false, t, &b);
					}
					else
						getMonthCalendar()->Render(false, t, nullptr);

					m_pCanvas->setValid(true);
				}
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}