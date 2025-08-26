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
		CScrollBarLite::CScrollBarLite() :
			CControl(L"ScrollBarLite", true, true, false, false, false, false),
			m_pScroll{ nullptr },
			m_pCanvas{ nullptr },
			m_cScrollListener{ this },
			OnScroll{ nullptr }
		{
			setService(new CScrollBarLiteService(this), true);
			setSize(PointF{ 123, 10 });
		}

		CScrollBarLite::CScrollBarLite(IControl *parent) :CScrollBarLite()
		{
			setParent(parent);
		}

		CScrollBarLite::CScrollBarLite(IForm *parent) : CScrollBarLite()
		{
			setForm(parent);
		}

		CScrollBarLite::~CScrollBarLite()
		{
			if (m_pScroll)
				m_pScroll->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		IFont *CScrollBarLite::getControlFont()
		{
			return nullptr;
		}

		RectF CScrollBarLite::getRenderRect()
		{
			return getScroll()->getRenderRect();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CScrollBarLite::setFont(IFont *value, const bool copy)
		{
			return false;
		}

		bool CScrollBarLite::setWantTabs(const bool value)
		{
			return false;
		}

		bool CScrollBarLite::setTabStop(const bool value)
		{
			return false;
		}

		bool CScrollBarLite::setDeactivateByTab(const bool value)
		{
			return false;
		}

		bool CScrollBarLite::setUseParentFont(const bool value)
		{
			return false;
		}

		bool CScrollBarLite::setDPI(const Point &value)
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

	#pragma region IControl methods
		void CScrollBarLite::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getScroll()->Refresh();
		}
	#pragma endregion

	#pragma region IScrollBarLite getters
		float CScrollBarLite::getMin()
		{
			return getScroll()->getMin();
		}

		float CScrollBarLite::getMax()
		{
			return getScroll()->getMax();
		}

		float CScrollBarLite::getPosition()
		{
			return getScroll()->getScroll();
		}

		bool CScrollBarLite::isVertical()
		{
			return getScroll()->isVertical();
		}
	#pragma endregion

	#pragma region IScrollBarLite setters
		bool CScrollBarLite::setMin(const float value)
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

		bool CScrollBarLite::setMax(const float value)
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

		bool CScrollBarLite::setPosition(const float value)
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

		bool CScrollBarLite::setVertical(const bool value)
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

	#pragma region Getters
		IBuiltInScroll *CScrollBarLite::getScroll()
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
		bool CScrollBarLite::setScroll(IBuiltInScroll *scroll)
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

	#pragma region Layout getters
		float CScrollBarLite::getScrollerSize()
		{
			return getScroll()->getScrollerSize();
		}

		float CScrollBarLite::getDeltaMedium()
		{
			return getScroll()->getDeltaMedium();
		}

		float CScrollBarLite::getDeltaLarge()
		{
			return getScroll()->getDeltaLarge();
		}

		float CScrollBarLite::getScrollInterval()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollInterval();
			return 0;
		}

		int CScrollBarLite::getShadowRadius(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowRadius(state);
			return 0;
		}

		Color CScrollBarLite::getShadowColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CScrollBarLite::getShadowShift(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		bool CScrollBarLite::isBorderRound()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->isBorderRound();
			return false;
		}

		float CScrollBarLite::getBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBorderWidth();
			return 0;
		}

		Color CScrollBarLite::getBorderColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBarLite::getBackgroundColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBarLite::getBackgroundGradient(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getBackgroundGradient(state);
			return nullptr;
		}

		bool CScrollBarLite::isScrollerRound()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->isScrollerRound();
			return 0;
		}

		float CScrollBarLite::getScrollerBorderWidth()
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBorderWidth();
			return 0;
		}

		Color CScrollBarLite::getScrollerBorderColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollBarLite::getScrollerBackgroundColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollBarLite::getScrollerBackgroundGradient(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScroll()))
				return cast<CScroll*>(getScroll())->getScrollerBackgroundGradient(state);
			return nullptr;
		}
	#pragma endregion

	#pragma region Layout setters
		bool CScrollBarLite::setScrollerSize(const float value)
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

		bool CScrollBarLite::setDeltaMedium(const float value)
		{
			return getScroll()->setDeltaMedium(value);
		}

		bool CScrollBarLite::setDeltaLarge(const float value)
		{
			return getScroll()->setDeltaLarge(value);
		}

		bool CScrollBarLite::setScrollInterval(const float value)
		{
			return cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollInterval(value);
		}

		bool CScrollBarLite::setShadowRadius(const CBuiltInScrollLite::State state, const int value)
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

		bool CScrollBarLite::setShadowColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setShadowShift(const CBuiltInScrollLite::State state, const PointF &value)
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

		bool CScrollBarLite::setBorderRound(const bool value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBorderRound(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBorderWidth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setBorderColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setBackgroundColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerRound(const bool value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerRound(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerBorderWidth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerBorderColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerBackgroundColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setShadowRadius(const int value)
		{
			if (cast<CScroll*>(getScroll()))
			{
				RectF r{ getRenderRect() };
				if (cast<CScroll*>(getScroll())->setShadowRadius(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CScrollBarLite::setShadowShift(const PointF &value)
		{
			if (cast<CScroll*>(getScroll()))
			{
				RectF r{ getRenderRect() };
				if (cast<CScroll*>(getScroll())->setShadowShift(value))
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(r + getRenderRect(), true);
					return true;
				}
			}
			return false;
		}

		bool CScrollBarLite::setShadowColor(const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setShadowColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setBorderColor(const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBorderColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setBackgroundColor(const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setBackgroundColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerBorderColor(const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerBorderColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollBarLite::setScrollerBackgroundColor(const Color &value)
		{
			if (cast<CScroll*>(getScroll()) && cast<CScroll*>(getScroll())->setScrollerBackgroundColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CScrollBarLite::Render()
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