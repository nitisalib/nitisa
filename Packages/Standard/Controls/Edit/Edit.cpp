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
		CEdit::CGradientListener::CGradientListener(CEdit *control) :
			m_pControl{ control }
		{

		}

		void CEdit::CGradientListener::NotifyOnChange()
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
		CEdit::CEdit() :
			CControl(L"Edit", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_pTextInput{ nullptr },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sBorderRadius{ 0, 0, 0, 0 },
			m_sPadding{ 2, 2, 2, 2 },
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
			m_bIgnoreGradient{ false },
			m_pCanvas{ nullptr },
			m_bTextChanged{ false },
			m_cListener{ this },
			OnChange{ nullptr }
		{
			setService(new CEditService(this), true);
			setSize(PointF{ 120, 21 });
			setCursor(CursorType::IBeam);
		}

		CEdit::CEdit(IControl *parent) : CEdit()
		{
			setParent(parent);
		}

		CEdit::CEdit(IForm *parent) : CEdit()
		{
			setForm(parent);
		}

		CEdit::~CEdit()
		{
			if (m_pTextInput)
				m_pTextInput->Release();
		}
	#pragma endregion

	#pragma region Helpers
		void CEdit::UpdateFromStyle()
		{
			m_bIgnoreGradient = true;
			getStyle()->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			getStyle()->getOption(m_sClassName + L".BorderRadius", m_sBorderRadius);
			getStyle()->getOption(m_sClassName + L".Padding", m_sPadding);
			for (int i = 0; i <= (int)CBuiltInTextInput::State::Disabled; i++)
			{
				String state;
				switch ((CBuiltInTextInput::State)i)
				{
				case CBuiltInTextInput::State::Hovered:
					state = L"Hovered";
					break;
				case CBuiltInTextInput::State::Focused:
					state = L"Focused";
					break;
				case CBuiltInTextInput::State::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case CBuiltInTextInput::State::Disabled:
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
			getTextInput()->UpdateFromStyle(getStyle(), m_sClassName + L".TextInput");
			m_bIgnoreGradient = false;
			AdjustTextInputSize();
		}

		void CEdit::AdjustTextInputSize()
		{
			getTextInput()->setSize(PointF{
				ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right),
				ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom) });
			getTextInput()->setPosition({ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top });
		}

		RectF CEdit::getRenderRect(const CBuiltInTextInput::State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		void CEdit::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getTextInput()->Refresh();
		}
	#pragma endregion

	#pragma region Getters
		RectF CEdit::getClientRect()
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

		RectF CEdit::getRenderRect()
		{
			RectF result{ getRenderRect(CBuiltInTextInput::State::Normal) };
			for (int i = (int)CBuiltInTextInput::State::Normal + 1; i <= (int)CBuiltInTextInput::State::Disabled; i++)
				result += getRenderRect((CBuiltInTextInput::State)i);
			return result;
		}

		CursorType CEdit::getCursor()
		{
			if (!isEnabled(false))
				return CursorType::Arrow;
			if (getTextInput()->isMoving())
			{
				if (getTextInput()->getCaretPosition() >= getTextInput()->getSelection().X && getTextInput()->getCaretPosition() <= getTextInput()->getSelection().Y)
					return CursorType::No;
				return CursorType::Arrow;
			}
			return CControl::getCursor();
		}

		IBuiltInTextInput *CEdit::getTextInput()
		{
			if (!m_pTextInput)
			{
				m_pTextInput = new CEditTextInput(this);
				m_pTextInput->setListener(&m_cListener);
			}
			return m_pTextInput;
		}

		RectF CEdit::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CEdit::getLeftBorderWidth() const
		{
			return m_sBorderWidth.Left;
		}

		float CEdit::getTopBorderWidth() const
		{
			return m_sBorderWidth.Top;
		}

		float CEdit::getRightBorderWidth() const
		{
			return m_sBorderWidth.Right;
		}

		float CEdit::getBottomBorderWidth() const
		{
			return m_sBorderWidth.Bottom;
		}

		RectF CEdit::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		float CEdit::getLeftBorderRadius() const
		{
			return m_sBorderRadius.Left;
		}

		float CEdit::getTopBorderRadius() const
		{
			return m_sBorderRadius.Top;
		}

		float CEdit::getRightBorderRadius() const
		{
			return m_sBorderRadius.Right;
		}

		float CEdit::getBottomBorderRadius() const
		{
			return m_sBorderRadius.Bottom;
		}

		RectF CEdit::getPadding() const
		{
			return m_sPadding;
		}

		float CEdit::getLeftPadding() const
		{
			return m_sPadding.Left;
		}

		float CEdit::getTopPadding() const
		{
			return m_sPadding.Top;
		}

		float CEdit::getRightPadding() const
		{
			return m_sPadding.Right;
		}

		float CEdit::getBottomPadding() const
		{
			return m_sPadding.Bottom;
		}

		BorderColor CEdit::getBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CEdit::getLeftBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CEdit::getTopBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CEdit::getRightBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CEdit::getBottomBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CEdit::getBackgroundColor(const CBuiltInTextInput::State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CEdit::getBackgroundGradient(const CBuiltInTextInput::State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CEdit::getShadowRadius(const CBuiltInTextInput::State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CEdit::getShadowShift(const CBuiltInTextInput::State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CEdit::getShadowColor(const CBuiltInTextInput::State state) const
		{
			return m_aShadowColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CEdit::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getTextInput()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sBorderRadius *= avg;
				m_sPadding *= s;
				for (int i = 0; i <= (int)CBuiltInTextInput::State::Disabled; i++)
				{
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
				}
				AdjustTextInputSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setTextInput(IBuiltInTextInput *value)
		{
			if (!value || value == m_pTextInput)
				return false;
			value->setListener(&m_cListener);
			if (m_pTextInput)
			{
				value->setText(m_pTextInput->getText());
				m_pTextInput->Release();
			}
			m_pTextInput = value;
			AdjustTextInputSize();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
			return true;
		}

		bool CEdit::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				AdjustTextInputSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setLeftBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CEdit::setTopBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CEdit::setRightBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		bool CEdit::setBottomBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		bool CEdit::setBorderRadius(const RectF &value)
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

		bool CEdit::setLeftBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ value, m_sBorderRadius.Top, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CEdit::setTopBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, value, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CEdit::setRightBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, value, m_sBorderRadius.Bottom });
		}

		bool CEdit::setBottomBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, m_sBorderRadius.Right, value });
		}

		bool CEdit::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				AdjustTextInputSize();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setLeftPadding(const float value)
		{
			return setPadding(RectF{ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CEdit::setTopPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CEdit::setRightPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		bool CEdit::setBottomPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		bool CEdit::setBorderColor(const CBuiltInTextInput::State state, const BorderColor &value)
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

		bool CEdit::setLeftBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CEdit::setTopBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CEdit::setRightBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CEdit::setBottomBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CEdit::setBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEdit::setShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CEdit::setShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CEdit::setShadowColor(const CBuiltInTextInput::State state, const Color &value)
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
	#pragma endregion

	#pragma region IEdit getters
		String CEdit::getText()
		{
			return getTextInput()->getText();
		}
	#pragma endregion

	#pragma region ITextInput getters
		String CEdit::getSelectedText()
		{
			return getTextInput()->getSelectedText();
		}

		Point CEdit::getSelection()
		{
			return getTextInput()->getSelection();
		}

		int CEdit::getCaretPosition()
		{
			return getTextInput()->getCaretPosition();
		}

		float CEdit::getScroll()
		{
			return getTextInput()->getScroll();
		}

		int CEdit::getMaxLength()
		{
			return getTextInput()->getMaxLength();
		}

		int CEdit::getUndoLimitCount()
		{
			return getTextInput()->getUndoLimitCount();
		}

		int CEdit::getUndoLimitSize()
		{
			return getTextInput()->getUndoLimitSize();
		}

		bool CEdit::canUndo()
		{
			return getTextInput()->canUndo();
		}

		bool CEdit::canRedo()
		{
			return getTextInput()->canRedo();
		}

		TextAlign CEdit::getTextAlign()
		{
			return getTextInput()->getAlign();
		}

		CBuiltInTextInput::State CEdit::getState()
		{
			if (!isEnabled(false))
				return CBuiltInTextInput::State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return CBuiltInTextInput::State::FocusedHovered;
				return CBuiltInTextInput::State::Focused;
			}
			if (isHovered())
				return CBuiltInTextInput::State::Hovered;
			return CBuiltInTextInput::State::Normal;
		}
	#pragma endregion

	#pragma region IEdit setters
		bool CEdit::setText(const String &value)
		{
			m_bTextChanged = true;
			if (getTextInput()->setText(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextInput setters
		bool CEdit::setSelection(const Point &value)
		{
			if (getTextInput()->setSelection(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setCaretPosition(const int value)
		{
			if (getTextInput()->setCaretPosition(value))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(true);
				return true;
			}
			return false;
		}

		bool CEdit::setScroll(const float value)
		{
			if (getTextInput()->setScroll(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setMaxLength(const int value)
		{
			if (getTextInput()->setMaxLength(value))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setUndoLimitCount(const int value)
		{
			return getTextInput()->setUndoLimitCount(value);
		}

		bool CEdit::setUndoLimitSize(const int value)
		{
			return getTextInput()->setUndoLimitSize(value);
		}

		bool CEdit::setTextAlign(const TextAlign value)
		{
			if (getTextInput()->setAlign(value))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextInput actions
		bool CEdit::DeleteSelection()
		{
			if (getTextInput()->DeleteSelection())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteCharBeforeCaret()
		{
			if (getTextInput()->DeleteCharBeforeCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteCharAfterCaret()
		{
			if (getTextInput()->DeleteCharAfterCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteWordBeforeCaret()
		{
			if (getTextInput()->DeleteWordBeforeCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteWordAfterCaret()
		{
			if (getTextInput()->DeleteWordAfterCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteAllBeforeCaret()
		{
			if (getTextInput()->DeleteAllBeforeCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeleteAllAfterCaret()
		{
			if (getTextInput()->DeleteAllAfterCaret())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretLeft(const bool select)
		{
			if (getTextInput()->MoveCaretLeft(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretRight(const bool select)
		{
			if (getTextInput()->MoveCaretRight(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretWordLeft(const bool select)
		{
			if (getTextInput()->MoveCaretWordLeft(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretWordRight(const bool select)
		{
			if (getTextInput()->MoveCaretWordRight(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretStart(const bool select)
		{
			if (getTextInput()->MoveCaretStart(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveCaretEnd(const bool select)
		{
			if (getTextInput()->MoveCaretEnd(select))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Undo()
		{
			bool text_changed;
			if (getTextInput()->Undo(text_changed))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Redo()
		{
			bool text_changed;
			if (getTextInput()->Redo(text_changed))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Insert(const wchar_t chr)
		{
			if (getTextInput()->Insert(chr))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Insert(const String &str)
		{
			if (getTextInput()->Insert(str))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Replace(const wchar_t chr)
		{
			if (getTextInput()->Replace(chr))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Replace(const String &str)
		{
			if (getTextInput()->Replace(str))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::MoveSelection(const int dst_caret_pos)
		{
			if (getTextInput()->MoveSelection(dst_caret_pos))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::CopySelection(const int dst_caret_pos)
		{
			if (getTextInput()->CopySelection(dst_caret_pos))
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Copy()
		{
			return getTextInput()->Copy();
		}

		bool CEdit::Cut()
		{
			if (getTextInput()->Cut())
			{
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::Paste()
		{
			return getTextInput()->Paste();
		}

		bool CEdit::SelectAll()
		{
			if (getTextInput()->SelectAll())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::DeselectAll()
		{
			if (getTextInput()->DeselectAll())
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region CTextInput getters
		String CEdit::getPlaceholder()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholder();
			return L"";
		}

		bool CEdit::isReadOnly()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReadOnly();
			return false;
		}

		bool CEdit::isReplacing()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReplacing();
			return false;
		}

		float CEdit::getScrollInterval()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getScrollInterval();
			return 0;
		}

		Color CEdit::getTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEdit::getPlaceholderColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEdit::getTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEdit::getSelectionBackgroundColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEdit::getSelectionTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEdit::getSelectionTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CEdit::getTextShadowShift(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CEdit::getTextShadowRadius(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowRadius(state);
			return 1;
		}

		bool CEdit::isCopyByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByMouseEnabled();
			return false;
		}

		bool CEdit::isMoveByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isMoveByMouseEnabled();
			return false;
		}

		bool CEdit::isSelectWordByDoubleClickEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectWordByDoubleClickEnabled();
			return false;
		}

		bool CEdit::isKeyLeftEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyLeftEnabled();
			return false;
		}

		bool CEdit::isKeyRightEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyRightEnabled();
			return false;
		}

		bool CEdit::isKeyHomeEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyHomeEnabled();
			return false;
		}

		bool CEdit::isKeyEndEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyEndEnabled();
			return false;
		}

		bool CEdit::isKeyDeleteEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyDeleteEnabled();
			return false;
		}

		bool CEdit::isKeyBackspaceEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyBackspaceEnabled();
			return false;
		}

		bool CEdit::isSelectAllByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectAllByKeyEnabled();
			return false;
		}

		bool CEdit::isPasteByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isPasteByKeyEnabled();
			return false;
		}

		bool CEdit::isCopyByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByKeyEnabled();
			return false;
		}

		bool CEdit::isCutByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCutByKeyEnabled();
			return false;
		}

		bool CEdit::isHistoryByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isHistoryByKeyEnabled();
			return false;
		}

		bool CEdit::isInsertReplaceChangeByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isInsertReplaceChangeByKeyEnabled();
			return false;
		}
	#pragma endregion

	#pragma region CTextInput setters
		bool CEdit::setPlaceholder(const String &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setPlaceholder(value))
			{
				if (input->getText().empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEdit::setReadOnly(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setReadOnly(value);
			return false;
		}

		bool CEdit::setReplacing(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setReplacing(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setScrollInterval(const float value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setScrollInterval(value);
			return false;
		}

		bool CEdit::setTextColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setTextColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setPlaceholderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setPlaceholderColor(state, value))
			{
				if (input->getText().empty() && !input->getPlaceholder().empty())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CEdit::setTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setSelectionBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setSelectionBackgroundColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setSelectionTextColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setSelectionTextColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setSelectionTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setSelectionShadowColor(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setTextShadowShift(const CBuiltInTextInput::State state, const PointF &value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setShadowShift(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setTextShadowRadius(const CBuiltInTextInput::State state, const int value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input && input->setShadowRadius(state, value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CEdit::setCopyByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByMouseEnabled(value);
			return false;
		}

		bool CEdit::setMoveByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setMoveByMouseEnabled(value);
			return false;
		}

		bool CEdit::setSelectWordByDoubleClickEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectWordByDoubleClickEnabled(value);
			return false;
		}

		bool CEdit::setKeyLeftEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyLeftEnabled(value);
			return false;
		}

		bool CEdit::setKeyRightEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyRightEnabled(value);
			return false;
		}

		bool CEdit::setKeyHomeEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyHomeEnabled(value);
			return false;
		}

		bool CEdit::setKeyEndEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyEndEnabled(value);
			return false;
		}

		bool CEdit::setKeyDeleteEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyDeleteEnabled(value);
			return false;
		}

		bool CEdit::setKeyBackspaceEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyBackspaceEnabled(value);
			return false;
		}

		bool CEdit::setSelectAllByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectAllByKeyEnabled(value);
			return false;
		}

		bool CEdit::setPasteByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setPasteByKeyEnabled(value);
			return false;
		}

		bool CEdit::setCopyByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByKeyEnabled(value);
			return false;
		}

		bool CEdit::setCutByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCutByKeyEnabled(value);
			return false;
		}

		bool CEdit::setHistoryByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setHistoryByKeyEnabled(value);
			return false;
		}

		bool CEdit::setInsertReplaceChangeByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setInsertReplaceChangeByKeyEnabled(value);
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CEdit::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			CBuiltInTextInput::State state{ getState() };
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
				Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				getTextInput()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + m_sPadding.Left + disp.X, m_sBorderWidth.Top + m_sPadding.Top + disp.Y, 0), &b);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}