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
	#pragma region Constructor & destructor
		CScrollBar::CScrollBar() :
			CControl(L"ScrollBar", true, true, false, false, false, false),
			m_pScroll{ nullptr },
			m_pCanvas{ nullptr },
			m_cScrollListener{ this },
			OnScroll{ nullptr }
		{
			setService(new CScrollBarService(this), true);
			setSize(PointF{ 123, 18 });
			setShadowColor(CScroll::State::Normal, Color{ 160, 160, 160, 255 });
			setShadowColor(CScroll::State::Hovered, Color{ 160, 160, 160, 255 });
			setShadowColor(CScroll::State::Active, Color{ 160, 160, 160, 255 });
			setShadowColor(CScroll::State::Disabled, Color{ 160, 160, 160, 255 });
		}

		CScrollBar::CScrollBar(IControl *parent) :CScrollBar()
		{
			setParent(parent);
		}

		CScrollBar::CScrollBar(IForm *parent) : CScrollBar()
		{
			setForm(parent);
		}

		CScrollBar::~CScrollBar()
		{
			if (m_pScroll)
				m_pScroll->Release();
		}
	#pragma endregion

	#pragma region CControl getters
		IFont *CScrollBar::getControlFont()
		{
			return nullptr;
		}

		RectF CScrollBar::getRenderRect()
		{
			RectF result{ getRenderRect(CScroll::State::Normal) };
			for (int i = (int)CScroll::State::Normal + 1; i <= (int)CScroll::State::Disabled; i++)
				result += getRenderRect((CScroll::State)i);
			return result;
		}
	#pragma endregion

	#pragma region CControl setters
		bool CScrollBar::setFont(IFont *value, const bool copy)
		{
			return false;
		}

		bool CScrollBar::setWantTabs(const bool value)
		{
			return false;
		}

		bool CScrollBar::setTabStop(const bool value)
		{
			return false;
		}

		bool CScrollBar::setDeactivateByTab(const bool value)
		{
			return false;
		}

		bool CScrollBar::setUseParentFont(const bool value)
		{
			return false;
		}

		bool CScrollBar::setDPI(const Point &value)
		{
			CLockRepaint lock{ this };
			if (CControl::setDPI(value) && getScroll()->setDPI(value))
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
		IBuiltInScroll *CScrollBar::getScroll()
		{
			if (!m_pScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pScroll = scroll;
				scroll->setBorderWidth(1);
				scroll->setSize(getSize());
			}
			return m_pScroll;
		}
	#pragma endregion

	#pragma region Setters
		bool CScrollBar::setScroll(IBuiltInScroll *scroll)
		{
			if (!scroll || scroll == m_pScroll)
				return false;
			if (m_pScroll)
				m_pScroll->Release();
			m_pScroll = scroll;
			m_pScroll->setListener(&m_cScrollListener);
			m_pScroll->setSize(getSize());
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}
	#pragma endregion

	#pragma region IScroll getters
		float CScrollBar::getMin()
		{
			return getScroll()->getMin();
		}

		float CScrollBar::getMax()
		{
			return getScroll()->getMax();
		}

		float CScrollBar::getPosition()
		{
			return getScroll()->getScroll();
		}

		float CScrollBar::getScrollerSize()
		{
			return getScroll()->getScrollerSize();
		}

		float CScrollBar::getDeltaSmall()
		{
			return getScroll()->getDeltaSmall();
		}

		float CScrollBar::getDeltaMedium()
		{
			return getScroll()->getDeltaMedium();
		}

		float CScrollBar::getDeltaLarge()
		{
			return getScroll()->getDeltaLarge();
		}

		bool CScrollBar::isVertical()
		{
			return getScroll()->isVertical();
		}
	#pragma endregion

	#pragma region IScroll setters
		bool CScrollBar::setMin(const float value)
		{
			if (getScroll()->setMin(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBar::setMax(const float value)
		{
			if (getScroll()->setMax(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBar::setPosition(const float value)
		{
			if (getScroll()->setScroll(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBar::setScrollerSize(const float value)
		{
			if (getScroll()->setScrollerSize(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBar::setDeltaSmall(const float value)
		{
			return getScroll()->setDeltaSmall(value);
		}

		bool CScrollBar::setDeltaMedium(const float value)
		{
			return getScroll()->setDeltaMedium(value);
		}

		bool CScrollBar::setDeltaLarge(const float value)
		{
			return getScroll()->setDeltaLarge(value);
		}

		bool CScrollBar::setVertical(const bool value)
		{
			if (value == getScroll()->isVertical())
				return false;
			CScroll *scroll{ cast<CScroll*>(getScroll()) };
			if (scroll)
			{
				CLockRepaint lock{ this };
				scroll->SwitchDirection(getAlign() == Align::None);
				setSize(scroll->getSize());
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			if (getScroll()->setVertical(value))
			{
				if (getAlign() == Align::None)
					setSize(PointF{ getScroll()->getSize().Y, getScroll()->getSize().X });
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region CScroll getters
		CBuiltInScroll::State CScrollBar::getState()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getState();
			return CScroll::State::Normal;
		}

		CBuiltInScroll::ElementType CScrollBar::getHoveredElement()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getHoveredElement();
			return CScroll::ElementType::None;
		}

		CBuiltInScroll::ElementType CScrollBar::getActiveElement()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getActiveElement();
			return CScroll::ElementType::None;
		}

		float CScrollBar::getScrollInterval()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollInterval();
			return 0;
		}

		float CScrollBar::getArrowSize()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getArrowSize();
			return 0;
		}

		float CScrollBar::getBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBorderWidth();
			return 0;
		}

		float CScrollBar::getBorderRadius()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBorderRadius();
			return 0;
		}

		Color CScrollBar::getBorderColor(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getBackgroundColor(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBar::getBackgroundGradient(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBackgroundGradient(state);
			return nullptr;
		}

		int CScrollBar::getShadowRadius(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowRadius(state);
			return 0;
		}

		PointF CScrollBar::getShadowShift(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		Color CScrollBar::getShadowColor(const CBuiltInScroll::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		float CScrollBar::getStartArrowBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowBorderWidth();
			return 0;
		}

		float CScrollBar::getStartArrowBorderRadius()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowBorderRadius();
			return 0;
		}

		Color CScrollBar::getStartArrowBorderColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getStartArrowBackgroundColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBar::getStartArrowBackgroundGradient(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowBackgroundGradient(state);
			return nullptr;
		}

		Color CScrollBar::getStartArrowColor1(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowColor1(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getStartArrowColor2(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowColor2(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getStartArrowColor3(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getStartArrowColor3(state);
			return Color{ 0, 0, 0, 0 };
		}

		float CScrollBar::getEndArrowBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowBorderWidth();
			return 0;
		}

		float CScrollBar::getEndArrowBorderRadius()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowBorderRadius();
			return 0;
		}

		Color CScrollBar::getEndArrowBorderColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getEndArrowBackgroundColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBar::getEndArrowBackgroundGradient(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowBackgroundGradient(state);
			return nullptr;
		}

		Color CScrollBar::getEndArrowColor1(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowColor1(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getEndArrowColor2(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowColor2(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getEndArrowColor3(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getEndArrowColor3(state);
			return Color{ 0, 0, 0, 0 };
		}

		float CScrollBar::getScrollerBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBorderWidth();
			return 0;
		}

		float CScrollBar::getScrollerBorderRadius()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBorderRadius();
			return 0;
		}

		Color CScrollBar::getScrollerBorderColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getScrollerBackgroundColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBar::getScrollerBackgroundGradient(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBackgroundGradient(state);
			return nullptr;
		}

		Color CScrollBar::getScrollerLinesBorderColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerLinesBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBar::getScrollerLinesBackgroundColor(const CBuiltInScroll::ElementState state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerLinesBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CScrollBar::getScrollerLinesSize()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerLinesSize();
			return PointF{ 0, 0 };
		}

		float CScrollBar::getScrollerLinesDistance()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerLinesDistance();
			return 0;
		}

		float CScrollBar::getScrollerLinesBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerLinesBorderWidth();
			return 0;
		}
	#pragma endregion

	#pragma region CScroll setters
		bool CScrollBar::setScrollInterval(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollInterval(value))
					return true;
			return false;
		}

		bool CScrollBar::setArrowSize(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setArrowSize(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setBorderWidth(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setBorderRadius(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setBorderRadius(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setBorderColor(const CBuiltInScroll::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setBorderColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setBackgroundColor(const CBuiltInScroll::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setBackgroundColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setShadowRadius(const CBuiltInScroll::State state, const int value)
		{
			if (cast<CScroll*>(getScroll()))
			{
				RectF r{ getRenderRect() };
				if (cast<CScroll*>(getScroll())->setShadowRadius(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CScrollBar::setShadowShift(const CBuiltInScroll::State state, const PointF &value)
		{
			if (cast<CScroll*>(getScroll()))
			{
				RectF r{ getRenderRect() };
				if (cast<CScroll*>(getScroll())->setShadowShift(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CScrollBar::setShadowColor(const CBuiltInScroll::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setShadowColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowBorderWidth(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);;
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowBorderRadius(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowBorderRadius(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowBorderColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowBorderColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowBackgroundColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowColor1(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowColor1(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowColor2(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowColor2(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setStartArrowColor3(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setStartArrowColor3(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowBorderWidth(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowBorderRadius(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowBorderRadius(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowBorderColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowBorderColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowBackgroundColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowColor1(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowColor1(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowColor2(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowColor2(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);;
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setEndArrowColor3(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setEndArrowColor3(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerBorderWidth(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerBorderRadius(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerBorderRadius(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerBorderColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerBorderColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerBackgroundColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerLinesBorderColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerLinesBorderColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerLinesBackgroundColor(const CBuiltInScroll::ElementState state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerLinesBackgroundColor(state, value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerLinesSize(const PointF &value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerLinesSize(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerLinesDistance(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerLinesDistance(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
					return true;
				}
			return false;
		}

		bool CScrollBar::setScrollerLinesBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()))
				if (cast<CScroll*>(getScroll())->setScrollerLinesBorderWidth(value))
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
		void CScrollBar::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getScroll()->Refresh();
		}

		RectF CScrollBar::getRenderRect(const CBuiltInScroll::State state)
		{
			return getScroll()->getRenderRect();
		}
	#pragma endregion

	#pragma region Paint
		void CScrollBar::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			CScroll *scroll{ cast<CScroll*>(getScroll()) };
			PointF disp;
			CScroll::State state;
			RectF all_rect;
			if (scroll)
			{
				state = scroll->getState();
				disp = DispOnCanvas(scroll->getShadowColor(state), scroll->getShadowShift(state), scroll->getShadowRadius(state));
				all_rect = AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, scroll->getShadowColor(state), scroll->getShadowShift(state), scroll->getShadowRadius(state));
			}
			else
			{
				disp = PointF{ 0, 0 };
				all_rect = RectF{ 0, 0, getWidth(), getHeight() };
			}
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				getScroll()->Render(false, ntl::Mat4Translate<float>(disp.X, disp.Y, 0), nullptr);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}