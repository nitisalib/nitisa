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
		CScrollList::CGradientListener::CGradientListener(CScrollList *control) :
			m_pControl{ control }
		{

		}

		void CScrollList::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(true);
			}
		}
	#pragma endregion

	#pragma region CScroll
		CScrollList::CScroll::CScroll(CScrollList *control) :
			CBuiltInScrollLite(),
			m_pControl{ control }
		{

		}

		IControl *CScrollList::CScroll::getControl()
		{
			return m_pControl;
		}
	#pragma endregion

	#pragma region CScrollListener
		CScrollList::CScrollListener::CScrollListener(CScrollList *control) :
			m_pControl{ control }
		{

		}

		void CScrollList::CScrollListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CScrollList::CScrollListener::NotifyOnScroll(IBuiltInControl *sender)
		{
			CLockRepaint lock{ m_pControl };
			m_pControl->m_fScroll = cast<IBuiltInScroll*>(sender)->getScroll();
			m_pControl->QueryService()->AlignControls();
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CScrollList::CScrollList():
			CControl(L"ScrollList", true, true, true, false, false, false),
			m_cGradientListener{ this },
			m_cScrollListener{ this },
			m_eOrientation{ Orientation::LeftToRight },
			m_fScroll{ 0 },
			m_fScrollMax{ 0 },
			m_fScrollSize{ 6 },
			m_eScrollVisibility{ ScrollVisibility::Auto },
			m_pScroll{ nullptr },
			m_iShadowRadius{ 1 },
			m_sShadowColor{ 0, 0, 0, 0 },
			m_sShadowShift{ 0, 0 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 2, 2, 2, 8 },
			m_sScrollPadding{ 0, 0 },
			m_sOuterBorderWidth{ 1, 1, 1, 1 },
			m_sInnerBorderWidth{ 0, 0, 0, 0 },
			m_sOuterBorderColor{ Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 }, Color{ 213, 223, 229, 255 } },
			m_sInnerBorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
			m_sBackgroundColor{ 240, 240, 240, 255 },
			m_cBackgroundGradient{ &m_cGradientListener },
			m_fMargin{ 0 },
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_pMask{ nullptr }
		{
			setService(new CScrollListService(this), true);
			setSize(PointF{ 185, 105 });
		}

		CScrollList::CScrollList(IControl *parent) :
			CScrollList()
		{
			setParent(parent);
		}

		CScrollList::CScrollList(IForm *parent) :
			CScrollList()
		{
			setForm(parent);
		}

		CScrollList::~CScrollList()
		{
			if (m_pScroll)
				m_pScroll->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		IControl *CScrollList::getControl(const int index)
		{
			return CControl::getControl(index);
		}

		IControl *CScrollList::getControl(const String &name)
		{
			return CControl::getControl(name);
		}

		IControl *CScrollList::getControl(const PointF &position)
		{
			IControl *result{ CControl::getControl(position) };
			if (result && result != this)
			{
				Vec4f v{ ntl::Inversed<float>(getTransformMatrix()) * Vec4f { position.X, position.Y, 0, 1 } };
				if (getClientRect().is_outside(PointF{ v.X, v.Y }))
					result = this;
			}
			return result;
		}

		RectF CScrollList::getClientRect()
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

		RectF CScrollList::getRenderRect()
		{
			return AddShadow(getRect(), m_sShadowColor, m_sShadowShift, m_iShadowRadius);
		}

		bool CScrollList::isAcceptBubbledEvents()
		{
			return true;
		}
	#pragma endregion

	#pragma region IControl setters
		bool CScrollList::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_fScrollSize *= (m_eOrientation == Orientation::LeftToRight) ? s.Y : s.X;
				m_iShadowRadius = ntl::Round<int>((float)m_iShadowRadius * avg);
				m_sShadowShift *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				m_sScrollPadding *= s;
				m_sOuterBorderWidth *= s;
				m_sInnerBorderWidth *= s;
				m_fMargin *= (m_eOrientation == Orientation::LeftToRight) ? s.X : s.Y;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CScrollList::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region IScrollList getters
		IScrollList::Orientation CScrollList::getOrientation()
		{
			return m_eOrientation;
		}

		IBuiltInScroll *CScrollList::getScrollBar()
		{
			if (!m_pScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				m_pScroll = scroll;
				UpdateScrollBar();
				scroll->setListener(&m_cScrollListener);
			}
			return m_pScroll;
		}

		float CScrollList::getScroll()
		{
			return m_fScroll;
		}

		float CScrollList::getScrollMax()
		{
			return m_fScrollMax;
		}
	#pragma endregion

	#pragma region IScrollList setters
		bool CScrollList::setOrientation(const Orientation value)
		{
			if (value != m_eOrientation)
			{
				CLockRepaint lock{ this };
				m_eOrientation = value;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBar(IBuiltInScroll *value)
		{
			if (value != m_pScroll)
			{
				CLockRepaint lock{ this };
				if (m_pScroll)
					m_pScroll->Release();
				if ((m_pScroll = value))
					m_pScroll->setListener(&m_cScrollListener);
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScroll(const float value)
		{
			float v{ ntl::Clamp<float>(value, 0, m_fScrollMax) };
			if (ntl::IsNotEqual<float>(v, m_fScroll))
			{
				CLockRepaint lock{ this };
				m_fScroll = value;
				getScrollBar()->setScroll(m_fScroll);
				QueryService()->AlignControls();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ScrollBar layout getters
		float CScrollList::getScrollBarDeltaMedium()
		{
			return getScrollBar()->getDeltaMedium();
		}

		float CScrollList::getScrollBarDeltaLarge()
		{
			return getScrollBar()->getDeltaLarge();
		}

		float CScrollList::getScrollBarScrollInterval()
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getScrollInterval();
			return 0;
		}

		int CScrollList::getScrollBarShadowRadius(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getShadowRadius(state);
			return 0;
		}

		Color CScrollList::getScrollBarShadowColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CScrollList::getScrollBarShadowShift(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		bool CScrollList::isScrollBarBorderRound()
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->isBorderRound();
			return false;
		}

		float CScrollList::getScrollBarBorderWidth()
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getBorderWidth();
			return 0;
		}

		Color CScrollList::getScrollBarBorderColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollList::getScrollBarBackgroundColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollList::getScrollBarBackgroundGradient(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getBackgroundGradient(state);
			return nullptr;
		}

		bool CScrollList::isScrollBarScrollerRound()
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->isScrollerRound();
			return 0;
		}

		float CScrollList::getScrollBarScrollerBorderWidth()
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getScrollerBorderWidth();
			return 0;
		}

		Color CScrollList::getScrollBarScrollerBorderColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getScrollerBorderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CScrollList::getScrollBarScrollerBackgroundColor(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getScrollerBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Gradient *CScrollList::getScrollBarScrollerBackgroundGradient(const CBuiltInScrollLite::State state)
		{
			if (cast<CScroll*>(getScrollBar()))
				return cast<CScroll*>(getScrollBar())->getScrollerBackgroundGradient(state);
			return nullptr;
		}
	#pragma endregion

	#pragma region ScrollBar layout setters
		bool CScrollList::setScrollBarDeltaMedium(const float value)
		{
			return getScrollBar()->setDeltaMedium(value);
		}

		bool CScrollList::setScrollBarDeltaLarge(const float value)
		{
			return getScrollBar()->setDeltaLarge(value);
		}

		bool CScrollList::setScrollBarScrollInterval(const float value)
		{
			return cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollInterval(value);
		}

		bool CScrollList::setScrollBarShadowRadius(const CBuiltInScrollLite::State state, const int value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarShadowColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarShadowShift(const CBuiltInScrollLite::State state, const PointF &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowShift(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBorderRound(const bool value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBorderRound(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBorderWidth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBorderColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBackgroundColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerRound(const bool value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerRound(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerBorderWidth(const float value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerBorderWidth(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerBorderColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerBorderColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerBackgroundColor(const CBuiltInScrollLite::State state, const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarShadowRadius(const int value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowRadius(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarShadowShift(const PointF &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowShift(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarShadowColor(const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setShadowColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBorderColor(const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBorderColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarBackgroundColor(const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setBackgroundColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerBorderColor(const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerBorderColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollBarScrollerBackgroundColor(const Color &value)
		{
			if (cast<CScroll*>(getScrollBar()) && cast<CScroll*>(getScrollBar())->setScrollerBackgroundColor(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Layout getters
		float CScrollList::getScrollSize() const
		{
			return m_fScrollSize;
		}

		ScrollVisibility CScrollList::getScrollVisibility() const
		{
			return m_eScrollVisibility;
		}

		int CScrollList::getShadowRadius() const
		{
			return m_iShadowRadius;
		}

		Color CScrollList::getShadowColor() const
		{
			return m_sShadowColor;
		}

		PointF CScrollList::getShadowShift() const
		{
			return m_sShadowShift;
		}

		RectF CScrollList::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		RectF CScrollList::getPadding() const
		{
			return m_sPadding;
		}

		PointF CScrollList::getScrollPadding() const
		{
			return m_sScrollPadding;
		}

		RectF CScrollList::getOuterBorderWidth() const
		{
			return m_sOuterBorderWidth;
		}

		RectF CScrollList::getInnerBorderWidth() const
		{
			return m_sInnerBorderWidth;
		}

		BorderColor CScrollList::getOuterBorderColor() const
		{
			return m_sOuterBorderColor;
		}

		BorderColor CScrollList::getInnerBorderColor() const
		{
			return m_sInnerBorderColor;
		}

		Color CScrollList::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		Gradient *CScrollList::getBackgroundGradient()
		{
			return &m_cBackgroundGradient;
		}

		float CScrollList::getMargin() const
		{
			return m_fMargin;
		}
	#pragma endregion

	#pragma region Layout setters
		bool CScrollList::setScrollSize(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 2) && ntl::IsNotEqual<float>(value, m_fScrollSize))
			{
				m_fScrollSize = value;
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eScrollVisibility)
			{
				m_eScrollVisibility = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setShadowRadius(const int value)
		{
			if (value >= 1 && value != m_iShadowRadius)
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_iShadowRadius = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollList::setShadowColor(const Color &value)
		{
			if (value != m_sShadowColor)
			{
				CLockRepaint lock{ this };
				Repaint(false);
				m_sShadowColor = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setShadowShift(const PointF &value)
		{
			if (IsNotEqual(value, m_sShadowShift))
			{
				CLockRepaint lock{ this };
				if (m_sShadowColor.A > 0)
					Repaint(false);
				m_sShadowShift = value;
				if (m_sShadowColor.A > 0)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollList::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				CLockRepaint lock{ this };
				m_sPadding = value;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setScrollPadding(const PointF &value)
		{
			if (ntl::IsPositive<float>(value.X) && ntl::IsPositive<float>(value.Y) && IsNotEqual(value, m_sScrollPadding))
			{
				m_sScrollPadding = value;
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setOuterBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sOuterBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sOuterBorderWidth = value;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setInnerBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sInnerBorderWidth))
			{
				CLockRepaint lock{ this };
				m_sInnerBorderWidth = value;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				if (m_pMask)
					m_pMask->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CScrollList::setOuterBorderColor(const BorderColor &value)
		{
			if (value != m_sOuterBorderColor)
			{
				m_sOuterBorderColor = value;
				if (m_sOuterBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollList::setInnerBorderColor(const BorderColor &value)
		{
			if (value != m_sInnerBorderColor)
			{
				m_sInnerBorderColor = value;
				if (m_sInnerBorderWidth.has_positive())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollList::setBackgroundColor(const Color &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				if (m_cBackgroundGradient.getPointCount() < 2)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CScrollList::setMargin(const float value)
		{
			if (ntl::IsPositive<float>(value) && ntl::IsNotEqual<float>(value, m_fMargin))
			{
				CLockRepaint lock{ this };
				m_fMargin = value;
				QueryService()->AlignControls();
				UpdateScrollBar();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CScrollList::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".ScrollSize", m_fScrollSize);
			style->getOption(m_sClassName + L".ShadowRadius", m_iShadowRadius);
			style->getOption(m_sClassName + L".ShadowColor", m_sShadowColor);
			style->getOption(m_sClassName + L".ShadowShift", m_sShadowShift);
			style->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".ScrollPadding", m_sScrollPadding);
			style->getOption(m_sClassName + L".OuterBorderWidth", m_sOuterBorderWidth);
			style->getOption(m_sClassName + L".InnerBorderWidth", m_sInnerBorderWidth);
			style->getOption(m_sClassName + L".OuterBorderColor", m_sOuterBorderColor);
			style->getOption(m_sClassName + L".InnerBorderColor", m_sInnerBorderColor);
			style->getOption(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			style->getOption(m_sClassName + L".BackgroundGradient", m_cBackgroundGradient);
			style->getOption(m_sClassName + L".Margin", m_fMargin);
			m_bIgnoreGradient = false;
			QueryService()->AlignControls();
			UpdateScrollBar();
			getScrollBar()->UpdateFromStyle(style, m_sClassName + L".Scroll");
		}

		void CScrollList::UpdateScrollBar()
		{
			IBuiltInScroll *scroll{ getScrollBar() };
			RectF rect{ CalculateScrollBarRect() };
			scroll->setVertical(m_eOrientation == Orientation::TopToBottom);
			scroll->setSize(PointF{ rect.width(), rect.height() });
			scroll->setPosition(rect.LeftTop);
			scroll->setMax(ntl::Max<float>(1, m_fScrollMax));
			scroll->setScroll(m_fScroll);
			scroll->setEnabled(ntl::IsGreater<float>(m_fScrollMax, 0));
			if (scroll->isEnabled())
			{
				RectF client{ getClientRect() };
				if (m_eOrientation == Orientation::TopToBottom)
					scroll->setScrollerSize(rect.height() * client.height() / (client.height() + m_fScrollMax));
				else
					scroll->setScrollerSize(rect.width() * client.width() / (client.width() + m_fScrollMax));
			}
			else
				scroll->setScrollerSize((m_eOrientation == Orientation::TopToBottom) ? scroll->getHeight() : scroll->getWidth());
		}

		RectF CScrollList::CalculateScrollBarRect()
		{
			RectF client{
				m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left,
				m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top,
				getWidth() - m_sOuterBorderWidth.Right - m_sInnerBorderWidth.Right,
				getHeight() - m_sOuterBorderWidth.Bottom - m_sInnerBorderWidth.Bottom
			};
			if (!client.is_valid() || client.is_zero())
				return RectF{ 0, 0, 0, 0 };
			RectF result{ 0, 0, 0, 0 };
			if (m_eOrientation == Orientation::TopToBottom)
			{
				if (client.width() >= m_fScrollSize + m_sScrollPadding.Y && client.height() > 2 * m_sScrollPadding.X)
				{
					result.Right = client.Right - m_sScrollPadding.Y;
					result.Left = result.Right - m_fScrollSize;
					result.Top = client.Top + m_sScrollPadding.X;
					result.Bottom = client.Bottom - m_sScrollPadding.X;
				}
			}
			else
			{
				if (client.width() > 2 * m_sScrollPadding.X && client.height() >= m_fScrollSize + m_sScrollPadding.Y)
				{
					result.Left = client.Left + m_sScrollPadding.X;
					result.Right = client.Right - m_sScrollPadding.X;
					result.Bottom = client.Bottom - m_sScrollPadding.Y;
					result.Top = result.Bottom - m_fScrollSize;
				}
			}
			return result;
		}

		bool CScrollList::NeedBlock() const
		{
			return
				m_sBorderRadius.Left > m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left || m_sBorderRadius.Left > m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top ||
				m_sBorderRadius.Top > m_sOuterBorderWidth.Top + m_sInnerBorderWidth.Top || m_sBorderRadius.Top > m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right ||
				m_sBorderRadius.Right > m_sOuterBorderWidth.Right + m_sInnerBorderWidth.Right || m_sBorderRadius.Right > m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom ||
				m_sBorderRadius.Bottom > m_sOuterBorderWidth.Bottom + m_sInnerBorderWidth.Bottom || m_sBorderRadius.Bottom > m_sOuterBorderWidth.Left + m_sInnerBorderWidth.Left;
		}

		bool CScrollList::isScrollBarVisible() const
		{
			return (m_eScrollVisibility == ScrollVisibility::Auto && ntl::IsGreater<float>(m_fScrollMax, 0)) || m_eScrollVisibility == ScrollVisibility::Visible;
		}
	#pragma endregion

	#pragma region Render
		void CScrollList::Render(IRenderer *renderer, const Mat4f &matrix)
		{
			PointF disp{ DispOnCanvas(m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_sShadowColor, m_sShadowShift, m_iShadowRadius) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_sShadowColor, m_sShadowShift, m_iShadowRadius);
				DrawDoubleBackground(renderer, rect, m_sOuterBorderWidth, m_sInnerBorderWidth, m_sBorderRadius, m_sOuterBorderColor, m_sInnerBorderColor, m_sBackgroundColor, m_cBackgroundGradient);
				if (isScrollBarVisible())
				{
					IBuiltInScroll *scroll{ getScrollBar() };
					if (ntl::IsGreater<float>(scroll->getWidth(), 0) && ntl::IsGreater<float>(scroll->getHeight(), 0))
					{
						if (NeedBlock())
						{
							Block b{ rect, AddElements(m_sOuterBorderWidth, m_sInnerBorderWidth), m_sBorderRadius, PointLocation::Inside };
							scroll->Render(false, ntl::Mat4Translate<float>(disp.X + scroll->getPosition().X, disp.Y + scroll->getPosition().Y, 0), &b);
						}
						else
							scroll->Render(false, ntl::Mat4Translate<float>(disp.X + scroll->getPosition().X, disp.Y + scroll->getPosition().Y, 0), nullptr);
					}
				}
				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, matrix, m_pCanvas, disp);
		}

		void CScrollList::RenderMask(IRenderer *renderer)
		{
			if (PrepareCanvas(renderer, &m_pMask, getSize()))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pMask)
					->Clear(Color{ 0, 0, 0, 0 });
				Block b{ getRect(), AddElements(m_sOuterBorderWidth, m_sInnerBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				if (m_sBorderRadius.has_positive())
				{
					CStoreBlock s_block{ renderer };
					renderer
						->ActivateBlock(&b)
						->DrawRectangle(b.Rect, Color{ 0, 0, 0, 255 });
				}
				else
					renderer->DrawRectangle(RectF{ b.Border.Left, b.Border.Top, b.Rect.Right - b.Border.Right, b.Rect.Bottom - b.Border.Bottom } * b.Rect, Color{ 0, 0, 0, 255 });
				m_pMask->setValid(true);
			}
		}
	#pragma endregion
	}
}