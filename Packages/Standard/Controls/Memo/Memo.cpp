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
		CMemo::CGradientListener::CGradientListener(CMemo *control) :
			m_pControl{ control }
		{

		}

		void CMemo::CGradientListener::NotifyOnChange()
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
		CMemo::CMemo() :
			CControl(L"Memo", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_pTextArea{ nullptr },
			m_pVScroll{ nullptr },
			m_pHScroll{ nullptr },
			m_eVerticalScrollType{ ScrollVisibility::Auto },
			m_eHorizontalScrollType{ ScrollVisibility::Auto },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 4, 4, 4, 4 },
			m_aBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
			m_aBackgroundColor{
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
				Gradient{ &m_cGradientListener } },
			m_aShadowRadius{ 1, 1, 1, 1, 1 },
			m_aShadowShift{
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
				Color{ 0, 0, 0, 0 } },
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_bVScrollEnabled{ false },
			m_bHScrollEnabled{ false },
			m_bVScrollVisible{ false },
			m_bHScrollVisible{ false },
			m_sTextAreaPosition{ 0, 0 },
			m_sVScrollPosition{ 0, 0 },
			m_sHScrollPosition{ 0, 0 },
			m_bIgnoreGradient{ false },
			m_eMouseDownElement{ CMemoService::Element::None },
			m_eHoveredElement{ CMemoService::Element::None },
			m_pCanvas{ nullptr },
			m_bTextChanged{ false },
			m_cScrollListener{ this },
			m_cTextAreaListener{ this },
			OnChange{ nullptr }
		{
			setService(new CMemoService(this), true);
			setSize(PointF{ 121, 89 });
			setCursor(CursorType::IBeam);
		}

		CMemo::CMemo(IControl *parent) :CMemo()
		{
			setParent(parent);
		}

		CMemo::CMemo(IForm *parent) : CMemo()
		{
			setForm(parent);
		}

		CMemo::~CMemo()
		{
			if (m_pVScroll)
				m_pVScroll->Release();
			if (m_pHScroll)
				m_pHScroll->Release();
			if (m_pTextArea)
				m_pTextArea->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CMemo::getClientRect()
		{
			RectF result{
				m_sBorderWidth.Left + m_sPadding.Left,
				m_sBorderWidth.Top + m_sPadding.Top,
				getWidth() - m_sBorderWidth.Right - m_sPadding.Right,
				getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom
			};
			result.validate();
			return result;
		}

		RectF CMemo::getRenderRect()
		{
			RectF result{ getRenderRect(CTextArea::State::Normal) };
			for (int i = (int)CTextArea::State::Normal + 1; i <= (int)CTextArea::State::Disabled; i++)
				result += getRenderRect((CTextArea::State)i);
			return result;
		}

		CursorType CMemo::getCursor()
		{
			if (!isEnabled(false))
				return CursorType::Arrow;
			if (getTextArea()->isMoving())
			{
				if (getTextArea()->getCaretPosition() >= getTextArea()->getSelection().X && getTextArea()->getCaretPosition() <= getTextArea()->getSelection().Y)
					return CursorType::No;
				return CursorType::Arrow;
			}
			if (m_eHoveredElement == CMemoService::Element::Text)
				return CControl::getCursor();
			return CursorType::Arrow;
		}
	#pragma endregion

	#pragma region ITextArea getters
		String CMemo::getText()
		{
			return getTextArea()->getText();
		}

		String CMemo::getSelectedText()
		{
			return getTextArea()->getSelectedText();
		}

		Point CMemo::getSelection()
		{
			return getTextArea()->getSelection();
		}

		int CMemo::getCaretPosition()
		{
			return getTextArea()->getCaretPosition();
		}

		PointF CMemo::getScroll()
		{
			return getTextArea()->getScroll();
		}

		int CMemo::getMaxLength()
		{
			return getTextArea()->getMaxLength();
		}

		int CMemo::getUndoLimitCount()
		{
			return getTextArea()->getUndoLimitCount();
		}

		int CMemo::getUndoLimitSize()
		{
			return getTextArea()->getUndoLimitSize();
		}

		bool CMemo::canUndo()
		{
			return getTextArea()->canUndo();
		}

		bool CMemo::canRedo()
		{
			return getTextArea()->canRedo();
		}

		TextAlign CMemo::getTextAlign()
		{
			return getTextArea()->getAlign();
		}

		bool CMemo::isWordWrap()
		{
			return getTextArea()->isWordWrap();
		}

		bool CMemo::isWordBreak()
		{
			return getTextArea()->isWordBreak();
		}

		int CMemo::getLineCount()
		{
			return getTextArea()->getLineCount();
		}

		String CMemo::getLine(const int index)
		{
			return getTextArea()->getLine(index);
		}
	#pragma endregion

	#pragma region CTextArea getters
		bool CMemo::isReadOnly()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isReadOnly();
			return false;
		}

		bool CMemo::isReplacing()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isReplacing();
			return false;
		}

		float CMemo::getScrollInterval()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getScrollInterval();
			return false;
		}

		CMemo::CTextArea::State CMemo::getState()
		{
			if (!isEnabled(false))
				return CTextArea::State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return CTextArea::State::FocusedHovered;
				return CTextArea::State::Focused;
			}
			if (isHovered())
				return CTextArea::State::Hovered;
			return CTextArea::State::Normal;
		}

		Color CMemo::getTextColor(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMemo::getTextShadowColor(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMemo::getSelectionBackgroundColor(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getSelectionBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMemo::getSelectionTextColor(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getSelectionTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMemo::getSelectionTextShadowColor(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getSelectionShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CMemo::getTextShadowShift(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CMemo::getTextShadowRadius(const CTextArea::State state)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->getShadowRadius(state);
			return 1;
		}

		bool CMemo::isCopyByMouseEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isCopyByMouseEnabled();
			return false;
		}

		bool CMemo::isMoveByMouseEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isMoveByMouseEnabled();
			return false;
		}

		bool CMemo::isSelectWordByDoubleClickEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isSelectWordByDoubleClickEnabled();
			return false;
		}

		bool CMemo::isKeyLeftEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyLeftEnabled();
			return false;
		}

		bool CMemo::isKeyRightEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyRightEnabled();
			return false;
		}

		bool CMemo::isKeyHomeEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyHomeEnabled();
			return false;
		}

		bool CMemo::isKeyEndEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyEndEnabled();
			return false;
		}

		bool CMemo::isKeyDeleteEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyDeleteEnabled();
			return false;
		}

		bool CMemo::isKeyBackspaceEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyBackspaceEnabled();
			return false;
		}

		bool CMemo::isKeyUpEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyUpEnabled();
			return false;
		}

		bool CMemo::isKeyDownEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyDownEnabled();
			return false;
		}

		bool CMemo::isKeyPageUpEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyPageUpEnabled();
			return false;
		}

		bool CMemo::isKeyPageDownEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isKeyPageDownEnabled();
			return false;
		}

		bool CMemo::isSelectAllByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isSelectAllByKeyEnabled();
			return false;
		}

		bool CMemo::isPasteByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isPasteByKeyEnabled();
			return false;
		}

		bool CMemo::isCopyByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isCopyByKeyEnabled();
			return false;
		}

		bool CMemo::isCutByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isCutByKeyEnabled();
			return false;
		}

		bool CMemo::isHistoryByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isHistoryByKeyEnabled();
			return false;
		}

		bool CMemo::isInsertReplaceChangeByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isInsertReplaceChangeByKeyEnabled();
			return false;
		}

		bool CMemo::isWordWrapChangeByKeyEnabled()
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->isWordWrapChangeByKeyEnabled();
			return false;
		}
	#pragma endregion

	#pragma region Getters
		IBuiltInTextArea *CMemo::getTextArea()
		{
			if (!m_pTextArea)
			{
				m_pTextArea = new CTextArea(this);
				m_pTextArea->setListener(&m_cTextAreaListener);
			}
			return m_pTextArea;
		}

		IBuiltInScroll *CMemo::getVScroll()
		{
			if (!m_pVScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pVScroll = scroll;
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pVScroll;
		}

		IBuiltInScroll *CMemo::getHScroll()
		{
			if (!m_pHScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				m_pHScroll = scroll;
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
			}
			return m_pHScroll;
		}

		ScrollVisibility CMemo::getVerticalScrollType() const
		{
			return m_eVerticalScrollType;
		}

		float CMemo::getVerticalScroll()
		{
			return getVScroll()->getScroll();
		}

		float CMemo::getMinVerticalScroll()
		{
			return getVScroll()->getMin();
		}

		float CMemo::getMaxVerticalScroll()
		{
			return getVScroll()->getMax();
		}

		ScrollVisibility CMemo::getHorizontalScrollType() const
		{
			return m_eHorizontalScrollType;
		}

		float CMemo::getHorizontalScroll()
		{
			return getHScroll()->getScroll();
		}

		float CMemo::getMinHorizontalScroll()
		{
			return getHScroll()->getMin();
		}

		float CMemo::getMaxHorizontalScroll()
		{
			return getHScroll()->getMax();
		}

		RectF CMemo::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CMemo::getLeftBorderWidth() const
		{
			return m_sBorderWidth.Left;
		}

		float CMemo::getTopBorderWidth() const
		{
			return m_sBorderWidth.Top;
		}

		float CMemo::getRightBorderWidth() const
		{
			return m_sBorderWidth.Right;
		}

		float CMemo::getBottomBorderWidth() const
		{
			return m_sBorderWidth.Bottom;
		}

		RectF CMemo::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		float CMemo::getLeftBorderRadius() const
		{
			return m_sBorderRadius.Left;
		}

		float CMemo::getTopBorderRadius() const
		{
			return m_sBorderRadius.Top;
		}

		float CMemo::getRightBorderRadius() const
		{
			return m_sBorderRadius.Right;
		}

		float CMemo::getBottomBorderRadius() const
		{
			return m_sBorderRadius.Bottom;
		}

		RectF CMemo::getPadding() const
		{
			return m_sPadding;
		}

		float CMemo::getLeftPadding() const
		{
			return m_sPadding.Left;
		}

		float CMemo::getTopPadding() const
		{
			return m_sPadding.Top;
		}

		float CMemo::getRightPadding() const
		{
			return m_sPadding.Right;
		}

		float CMemo::getBottomPadding() const
		{
			return m_sPadding.Bottom;
		}

		BorderColor CMemo::getBorderColor(const CTextArea::State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CMemo::getLeftBorderColor(const CTextArea::State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CMemo::getTopBorderColor(const CTextArea::State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CMemo::getRightBorderColor(const CTextArea::State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CMemo::getBottomBorderColor(const CTextArea::State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CMemo::getBackgroundColor(const CTextArea::State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CMemo::getBackgroundGradient(const CTextArea::State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CMemo::getShadowRadius(const CTextArea::State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CMemo::getShadowShift(const CTextArea::State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CMemo::getShadowColor(const CTextArea::State state) const
		{
			return m_aShadowColor[(int)state];
		}

		Color CMemo::getCornerColor(const CTextArea::State state) const
		{
			return m_aCornerColor[(int)state];
		}
	#pragma endregion

	#pragma region IControl setters
		bool CMemo::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getTextArea()->setDPI(value);
				getHScroll()->setDPI(value);
				getVScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				for (int i = 0; i <= (int)CTextArea::State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
				}
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextArea setters
		bool CMemo::setText(const String &value)
		{
			m_bTextChanged = true;
			if (getTextArea()->setText(value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setSelection(const Point &value)
		{
			if (getTextArea()->setSelection(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setCaretPosition(const int value)
		{
			if (getTextArea()->setCaretPosition(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CMemo::setScroll(const PointF &value)
		{
			if (getTextArea()->setScroll(value))
			{
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setMaxLength(const int value)
		{
			if (getTextArea()->setMaxLength(value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setUndoLimitCount(const int value)
		{
			return getTextArea()->setUndoLimitCount(value);
		}

		bool CMemo::setUndoLimitSize(const int value)
		{
			return getTextArea()->setUndoLimitSize(value);
		}

		bool CMemo::setTextAlign(const TextAlign value)
		{
			if (getTextArea()->setAlign(value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setWordWrap(const bool value)
		{
			if (getTextArea()->setWordWrap(value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setWordBreak(const bool value)
		{
			if (getTextArea()->setWordBreak(value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setLine(const int index, const String &value)
		{
			if (getTextArea()->setLine(index, value))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region CTextArea setters
		bool CMemo::setReadOnly(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setReadOnly(value);
			return false;
		}

		bool CMemo::setReplacing(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setReplacing(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setScrollInterval(const float value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setScrollInterval(value);
			return false;
		}

		bool CMemo::setTextColor(const CTextArea::State state, const Color &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setTextColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setTextShadowColor(const CTextArea::State state, const Color &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setSelectionBackgroundColor(const CTextArea::State state, const Color &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setSelectionBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setSelectionTextColor(const CTextArea::State state, const Color &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setSelectionTextColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setSelectionTextShadowColor(const CTextArea::State state, const Color &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setSelectionShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setTextShadowShift(const CTextArea::State state, const PointF &value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setShadowShift(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setTextShadowRadius(const CTextArea::State state, const int value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input && input->setShadowRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setCopyByMouseEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setCopyByMouseEnabled(value);
			return false;
		}

		bool CMemo::setMoveByMouseEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setMoveByMouseEnabled(value);
			return false;
		}

		bool CMemo::setSelectWordByDoubleClickEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setSelectWordByDoubleClickEnabled(value);
			return false;
		}

		bool CMemo::setKeyLeftEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyLeftEnabled(value);
			return false;
		}

		bool CMemo::setKeyRightEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyRightEnabled(value);
			return false;
		}

		bool CMemo::setKeyHomeEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyHomeEnabled(value);
			return false;
		}

		bool CMemo::setKeyEndEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyEndEnabled(value);
			return false;
		}

		bool CMemo::setKeyDeleteEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyDeleteEnabled(value);
			return false;
		}

		bool CMemo::setKeyBackspaceEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyBackspaceEnabled(value);
			return false;
		}

		bool CMemo::setKeyUpEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyUpEnabled(value);
			return false;
		}

		bool CMemo::setKeyDownEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyDownEnabled(value);
			return false;
		}

		bool CMemo::setKeyPageUpEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyPageUpEnabled(value);
			return false;
		}

		bool CMemo::setKeyPageDownEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setKeyPageDownEnabled(value);
			return false;
		}

		bool CMemo::setSelectAllByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setSelectAllByKeyEnabled(value);
			return false;
		}

		bool CMemo::setPasteByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setPasteByKeyEnabled(value);
			return false;
		}

		bool CMemo::setCopyByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setCopyByKeyEnabled(value);
			return false;
		}

		bool CMemo::setCutByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setCutByKeyEnabled(value);
			return false;
		}

		bool CMemo::setHistoryByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setHistoryByKeyEnabled(value);
			return false;
		}

		bool CMemo::setInsertReplaceChangeByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setInsertReplaceChangeByKeyEnabled(value);
			return false;
		}

		bool CMemo::setWordWrapChangeByKeyEnabled(const bool value)
		{
			CTextArea *input{ cast<CTextArea*>(getTextArea()) };
			if (input)
				return input->setWordWrapChangeByKeyEnabled(value);
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CMemo::setTextArea(IBuiltInTextArea *value)
		{
			if (!value || value == m_pTextArea)
				return false;
			value->setListener(&m_cTextAreaListener);
			value->NotifyOnFreeResources();
			if (m_pTextArea)
			{
				value->setText(m_pTextArea->getText());
				m_pTextArea->Release();
			}
			m_pTextArea = value;
			AdjustElements();
			m_pTextArea->ScrollToCaret();
			UpdateScrollPositions();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CMemo::setVScroll(IBuiltInScroll *value)
		{
			if (!value || value == m_pVScroll)
				return false;
			value->setListener(&m_cScrollListener);
			value->NotifyOnFreeResources();
			value->setVertical(true);
			if (m_pVScroll)
				m_pVScroll->Release();
			m_pVScroll = value;
			AdjustElements();
			UpdateScrollPositions();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CMemo::setHScroll(IBuiltInScroll *value)
		{
			if (!value || value == m_pHScroll)
				return false;
			value->setListener(&m_cScrollListener);
			value->NotifyOnFreeResources();
			value->setVertical(false);
			if (m_pHScroll)
				m_pHScroll->Release();
			m_pHScroll = value;
			AdjustElements();
			UpdateScrollPositions();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CMemo::setVerticalScrollType(const ScrollVisibility value)
		{
			if (value != m_eVerticalScrollType)
			{
				m_eVerticalScrollType = value;
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setVerticalScroll(const float value)
		{
			if (m_bVScrollEnabled && getVScroll()->setScroll(value))
			{
				getTextArea()->setScroll(PointF{ getTextArea()->getScroll().X, -getVScroll()->getScroll() });
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setHorizontalScrollType(const ScrollVisibility value)
		{
			if (value != m_eHorizontalScrollType)
			{
				m_eHorizontalScrollType = value;
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setHorizontalScroll(const float value)
		{
			if (m_bHScrollEnabled && getHScroll()->setScroll(value))
			{
				getTextArea()->setScroll(PointF{ -getHScroll()->getScroll(), getTextArea()->getScroll().Y });
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setLeftBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CMemo::setTopBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CMemo::setRightBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		bool CMemo::setBottomBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		bool CMemo::setBorderRadius(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderRadius))
			{
				m_sBorderRadius = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setLeftBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ value, m_sBorderRadius.Top, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CMemo::setTopBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, value, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CMemo::setRightBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, value, m_sBorderRadius.Bottom });
		}

		bool CMemo::setBottomBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, m_sBorderRadius.Right, value });
		}

		bool CMemo::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::setLeftPadding(const float value)
		{
			return setPadding(RectF{ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CMemo::setTopPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CMemo::setRightPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		bool CMemo::setBottomPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		bool CMemo::setBorderColor(const CTextArea::State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
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

		bool CMemo::setLeftBorderColor(const CTextArea::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMemo::setTopBorderColor(const CTextArea::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMemo::setRightBorderColor(const CTextArea::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CMemo::setBottomBorderColor(const CTextArea::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CMemo::setBackgroundColor(const CTextArea::State state, const Color &value)
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

		bool CMemo::setShadowRadius(const CTextArea::State state, const int value)
		{
			if (value >= 1 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				if (state == getState())
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
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

		bool CMemo::setShadowShift(const CTextArea::State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				if (state == getState())
					Repaint(false);
				m_aShadowShift[(int)state] = value;
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

		bool CMemo::setShadowColor(const CTextArea::State state, const Color &value)
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

		bool CMemo::setCornerColor(const CTextArea::State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
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

	#pragma region IControl methods
		void CMemo::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getTextArea()->Refresh();
			getVScroll()->Refresh();
			getHScroll()->Refresh();
		}
	#pragma endregion

	#pragma region ITextArea actions
		bool CMemo::DeleteSelection()
		{
			if (getTextArea()->DeleteSelection())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteCharBeforeCaret()
		{
			if (getTextArea()->DeleteCharBeforeCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteCharAfterCaret()
		{
			if (getTextArea()->DeleteCharAfterCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteWordBeforeCaret()
		{
			if (getTextArea()->DeleteWordBeforeCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteWordAfterCaret()
		{
			if (getTextArea()->DeleteWordAfterCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteToLineStart()
		{
			if (getTextArea()->DeleteToLineStart())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteToLineEnd()
		{
			if (getTextArea()->DeleteToLineEnd())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteAllBeforeCaret()
		{
			if (getTextArea()->DeleteAllBeforeCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteAllAfterCaret()
		{
			if (getTextArea()->DeleteAllAfterCaret())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretLeft(const bool select)
		{
			if (getTextArea()->MoveCaretLeft(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretRight(const bool select)
		{
			if (getTextArea()->MoveCaretRight(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretWordLeft(const bool select)
		{
			if (getTextArea()->MoveCaretWordLeft(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretWordRight(const bool select)
		{
			if (getTextArea()->MoveCaretWordRight(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretLineStart(const bool select)
		{
			if (getTextArea()->MoveCaretLineStart(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretLineEnd(const bool select)
		{
			if (getTextArea()->MoveCaretLineEnd(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretLineUp(const bool select)
		{
			if (getTextArea()->MoveCaretLineUp(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretLineDown(const bool select)
		{
			if (getTextArea()->MoveCaretLineDown(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretPageStart(const bool select)
		{
			if (getTextArea()->MoveCaretPageStart(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretPageEnd(const bool select)
		{
			if (getTextArea()->MoveCaretPageEnd(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretPageUp(const bool select)
		{
			if (getTextArea()->MoveCaretPageUp(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretPageDown(const bool select)
		{
			if (getTextArea()->MoveCaretPageDown(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretStart(const bool select)
		{
			if (getTextArea()->MoveCaretStart(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveCaretEnd(const bool select)
		{
			if (getTextArea()->MoveCaretEnd(select))
			{
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Undo()
		{
			bool text_changed;
			if (getTextArea()->Undo(text_changed))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Redo()
		{
			bool text_changed;
			if (getTextArea()->Redo(text_changed))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Insert(const wchar_t chr)
		{
			if (getTextArea()->Insert(chr))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Insert(const String &str)
		{
			if (getTextArea()->Insert(str))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Replace(const wchar_t chr)
		{
			if (getTextArea()->Replace(chr))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Replace(const String &str)
		{
			if (getTextArea()->Replace(str))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::MoveSelection(const int dst_caret_pos)
		{
			if (getTextArea()->MoveSelection(dst_caret_pos))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::CopySelection(const int dst_caret_pos)
		{
			if (getTextArea()->CopySelection(dst_caret_pos))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Copy()
		{
			return getTextArea()->Copy();
		}

		bool CMemo::Cut()
		{
			if (getTextArea()->Cut())
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::Paste()
		{
			return getTextArea()->Paste();
		}

		bool CMemo::ScrollLineUp()
		{
			if (getTextArea()->ScrollLineUp())
			{
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::ScrollLineDown()
		{
			if (getTextArea()->ScrollLineDown())
			{
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::SelectAll()
		{
			if (getTextArea()->SelectAll())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeselectAll()
		{
			if (getTextArea()->DeselectAll())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::AddLine(const String &text)
		{
			if (getTextArea()->AddLine(text))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMemo::DeleteLine(const int index)
		{
			if (getTextArea()->DeleteLine(index))
			{
				AdjustElements();
				getTextArea()->ScrollToCaret();
				UpdateScrollPositions();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CMemo::UpdateFromStyle()
		{
			m_bIgnoreGradient = true;
			getStyle()->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			getStyle()->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			getStyle()->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)CTextArea::State::Disabled; i++)
			{
				String state;
				switch ((CTextArea::State)i)
				{
				case CTextArea::State::Hovered:
					state = L"Hovered";
					break;
				case CTextArea::State::Focused:
					state = L"Focused";
					break;
				case CTextArea::State::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case CTextArea::State::Disabled:
					state = L"Disabled";
					break;
				default:
					state = L"Normal";
				}
				getStyle()->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				getStyle()->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				getStyle()->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				getStyle()->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				getStyle()->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				getStyle()->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
			}
			getTextArea()->UpdateFromStyle(getStyle(), m_sClassName + L".TextArea");
			getHScroll()->UpdateFromStyle(getStyle(), m_sClassName + L".Scroll");
			getVScroll()->UpdateFromStyle(getStyle(), m_sClassName + L".Scroll");
			m_bIgnoreGradient = false;
			AdjustElements();
			getTextArea()->ScrollToCaret();
			UpdateScrollPositions();
		}

		void CMemo::AdjustElements()
		{
			RectF client{ getClientRect() };
			float line_height{ (getForm() && getForm()->getRenderer() && getFont()->getPlatformFont(getForm()->getRenderer())) ? getFont()->getPlatformFont(getForm()->getRenderer())->getStringSize(L"Wy",0).Y : 1 };
			// Calculate whether scrolls should be visible or hiddent
			switch (m_eHorizontalScrollType)
			{
				case ScrollVisibility::Visible:
					m_bHScrollVisible = true;
					break;
				case ScrollVisibility::Auto:
					if (!getTextArea()->isWordWrap())
					{
						PointB required;
						switch (m_eVerticalScrollType)
						{
						case ScrollVisibility::Visible:
							m_bHScrollVisible = getTextArea()->getScrollRequired(PointF{ client.width() - getVScroll()->getSize().X, client.height() }).X;
							m_bVScrollVisible = true;
							break;
						case ScrollVisibility::Auto:
							required = getTextArea()->getScrollRequired(PointF{ client.width(), client.height() });
							if (required.Y)
							{
								if (required.X)
									m_bHScrollVisible = true;
								else
									m_bHScrollVisible = getTextArea()->getScrollRequired(PointF{ client.width() - getVScroll()->getSize().X, client.height() }).X;
								m_bVScrollVisible = true;
							}
							else if (required.X)
							{
								m_bHScrollVisible = true;
								m_bVScrollVisible = getTextArea()->getScrollRequired(PointF{ client.width(), client.height() - getHScroll()->getSize().Y }).Y;
							}
							else
							{
								m_bHScrollVisible = false;
								m_bVScrollVisible = false;
							}
							break;
						default:
							m_bHScrollVisible = getTextArea()->getScrollRequired(PointF{ client.width(), client.height() }).X;
							m_bVScrollVisible = false;
						}
					}
					else
						m_bHScrollVisible = false;
					break;
				default:
					m_bHScrollVisible = false;
			}
			switch (m_eVerticalScrollType)
			{
			case ScrollVisibility::Visible:
				m_bVScrollVisible = true;
				break;
			case ScrollVisibility::Auto:
				if (m_eHorizontalScrollType != ScrollVisibility::Auto || (m_eHorizontalScrollType == ScrollVisibility::Auto && getTextArea()->isWordWrap()))
					m_bVScrollVisible = getTextArea()->getScrollRequired(PointF{ client.width(), client.height() - (m_bHScrollVisible ? getHScroll()->getSize().Y : 0) }).Y;
				break;
			default:
				m_bVScrollVisible = false;
			}
			m_sTextAreaPosition = PointF{ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top };
			// Calculate and set new size of text area
			PointF size{ client.width(), client.height() };
			if (m_bVScrollVisible)
				size.X = ntl::Max<float>(0, size.X - getVScroll()->getSize().X);
			if (m_bHScrollVisible)
				size.Y = ntl::Max<float>(0, size.Y - getHScroll()->getSize().Y);
			getTextArea()->setSize(size);
			// Calculate whether scrolls should be enabled
			m_bHScrollEnabled = !getTextArea()->isWordWrap() && ntl::IsGreater<float>(getTextArea()->getTextSize().X, getTextArea()->getSize().X);
			m_bVScrollEnabled = ntl::IsGreater<float>(getTextArea()->getTextSize().Y, getTextArea()->getSize().Y);
			// Set scrolls parameters(except for position)
			if (m_bHScrollVisible)
			{
				getHScroll()->setSize(PointF{ ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScrollVisible ? getVScroll()->getSize().X : 0)), getHScroll()->getSize().Y });
				m_sHScrollPosition = PointF{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getSize().Y };
			}
			if (m_bVScrollVisible)
			{
				getVScroll()->setSize(PointF{ getVScroll()->getSize().X, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScrollVisible ? getHScroll()->getSize().Y : 0) });
				m_sVScrollPosition = PointF{ getWidth() - m_sBorderWidth.Right - getVScroll()->getSize().X, m_sBorderWidth.Top };
			}
			getHScroll()->setEnabled(m_bHScrollEnabled);
			getVScroll()->setEnabled(m_bVScrollEnabled);
			if (m_bHScrollEnabled)
			{
				PointF range{ getTextArea()->getXScrollRange() };
				switch (getTextArea()->getAlign())
				{
				case TextAlign::Left:
					getHScroll()->setMin(0);
					getHScroll()->setMax(-range.X);
					break;
				case TextAlign::Right:
					getHScroll()->setMin(-range.Y);
					getHScroll()->setMax(0);
					break;
				case TextAlign::Center:
					getHScroll()->setMin(-range.Y);
					getHScroll()->setMax(-range.X);
					break;
				}
				getHScroll()->setDeltaSmall(line_height);
				getHScroll()->setDeltaMedium(3 * line_height);
			}
			if (m_bVScrollEnabled)
			{
				PointF range{ getTextArea()->getYScrollRange() };
				getVScroll()->setMin(0);
				getVScroll()->setMax(-range.X);
				getVScroll()->setDeltaSmall(line_height);
				getVScroll()->setDeltaMedium(3 * line_height);
			}
		}

		void CMemo::UpdateScrollPositions()
		{
			if (m_bHScrollEnabled)
				getHScroll()->setScroll(-getTextArea()->getScroll().X);
			if (m_bVScrollEnabled)
				getVScroll()->setScroll(-getTextArea()->getScroll().Y);
		}
		RectF CMemo::getRenderRect(const CTextArea::State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Paint
		void CMemo::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			CTextArea::State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
				RenderTextArea(rect, disp);
				RenderScrolls(rect, disp, state);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CMemo::RenderTextArea(const RectF &rect, const PointF &disp)
		{
			Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
			if (m_bHScrollVisible)
				b.Border.Bottom += getHScroll()->getSize().Y;
			if (m_bVScrollVisible)
				b.Border.Right += getVScroll()->getSize().X;
			getTextArea()->Render(false, ntl::Mat4Translate<float>(std::round(m_sTextAreaPosition.X + disp.X), std::round(m_sTextAreaPosition.Y + disp.Y), 0), &b);
		}

		void CMemo::RenderScrolls(const RectF &rect, const PointF &disp, const CTextArea::State state)
		{
			Block b{ rect, m_sBorderWidth, m_sBorderRadius, PointLocation::Inside };
			if (m_bVScrollVisible)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(m_sVScrollPosition.X + disp.X, m_sVScrollPosition.Y + disp.Y, 0), &b);
			if (m_bHScrollVisible)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(m_sHScrollPosition.X + disp.X, m_sHScrollPosition.Y + disp.Y, 0), &b);
			if (m_bVScrollVisible && m_bHScrollVisible && m_aCornerColor[(int)state].A > 0)
			{
				RectF rect{
					m_sHScrollPosition.X + getHScroll()->getSize().X + disp.X,
					m_sVScrollPosition.Y + getVScroll()->getSize().Y + disp.Y,
					m_sVScrollPosition.X + getVScroll()->getSize().X + disp.X,
					m_sHScrollPosition.Y + getHScroll()->getSize().Y + disp.Y };
				IRenderer *renderer{ getForm()->getRenderer() };
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(&b)
					->DrawRectangle(rect, m_aCornerColor[(int)state]);
			}
		}
	#pragma endregion
	}
}