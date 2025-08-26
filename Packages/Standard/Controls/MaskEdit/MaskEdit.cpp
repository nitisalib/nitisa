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
		CMaskEdit::CGradientListener::CGradientListener(CMaskEdit *control) :
			m_pControl{ control }
		{

		}

		void CMaskEdit::CGradientListener::NotifyOnChange()
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
		CMaskEdit::CMaskEdit() :
			CControl(L"MaskEdit", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_sMask{ L"###-###-####" },
			m_pValidator{ nullptr },
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
			m_bIgnoreText{ false },
			m_pCanvas{ nullptr },
			m_cListener{ this },
			OnChange{ nullptr }
		{
			setService(new CMaskEditService(this), true);
			setSize(PointF{ 120, 21 });
			setCursor(CursorType::IBeam);
			setPlaceholder(m_sMask);
		}

		CMaskEdit::CMaskEdit(IControl *parent) : CMaskEdit()
		{
			setParent(parent);
		}

		CMaskEdit::CMaskEdit(IForm *parent) : CMaskEdit()
		{
			setForm(parent);
		}

		CMaskEdit::~CMaskEdit()
		{
			if (m_pTextInput)
				m_pTextInput->Release();
		}
	#pragma endregion

	#pragma region Getters
		RectF CMaskEdit::getClientRect()
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

		RectF CMaskEdit::getRenderRect()
		{
			RectF result{ getRenderRect(CBuiltInTextInput::State::Normal) };
			for (int i = (int)CBuiltInTextInput::State::Normal + 1; i <= (int)CBuiltInTextInput::State::Disabled; i++)
				result += getRenderRect((CBuiltInTextInput::State)i);
			return result;
		}

		CursorType CMaskEdit::getCursor()
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

		IBuiltInTextInput *CMaskEdit::getTextInput()
		{
			if (!m_pTextInput)
			{
				m_pTextInput = new CMaskEditTextInput(this);
				m_pTextInput->setUndoLimitCount(0);
				m_pTextInput->setListener(&m_cListener);
			}
			return m_pTextInput;
		}

		RectF CMaskEdit::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CMaskEdit::getLeftBorderWidth() const
		{
			return m_sBorderWidth.Left;
		}

		float CMaskEdit::getTopBorderWidth() const
		{
			return m_sBorderWidth.Top;
		}

		float CMaskEdit::getRightBorderWidth() const
		{
			return m_sBorderWidth.Right;
		}

		float CMaskEdit::getBottomBorderWidth() const
		{
			return m_sBorderWidth.Bottom;
		}

		RectF CMaskEdit::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		float CMaskEdit::getLeftBorderRadius() const
		{
			return m_sBorderRadius.Left;
		}

		float CMaskEdit::getTopBorderRadius() const
		{
			return m_sBorderRadius.Top;
		}

		float CMaskEdit::getRightBorderRadius() const
		{
			return m_sBorderRadius.Right;
		}

		float CMaskEdit::getBottomBorderRadius() const
		{
			return m_sBorderRadius.Bottom;
		}

		RectF CMaskEdit::getPadding() const
		{
			return m_sPadding;
		}

		float CMaskEdit::getLeftPadding() const
		{
			return m_sPadding.Left;
		}

		float CMaskEdit::getTopPadding() const
		{
			return m_sPadding.Top;
		}

		float CMaskEdit::getRightPadding() const
		{
			return m_sPadding.Right;
		}

		float CMaskEdit::getBottomPadding() const
		{
			return m_sPadding.Bottom;
		}

		BorderColor CMaskEdit::getBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CMaskEdit::getLeftBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CMaskEdit::getTopBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CMaskEdit::getRightBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CMaskEdit::getBottomBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CMaskEdit::getBackgroundColor(const CBuiltInTextInput::State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CMaskEdit::getBackgroundGradient(const CBuiltInTextInput::State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CMaskEdit::getShadowRadius(const CBuiltInTextInput::State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CMaskEdit::getShadowShift(const CBuiltInTextInput::State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CMaskEdit::getShadowColor(const CBuiltInTextInput::State state) const
		{
			return m_aShadowColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CMaskEdit::setDPI(const Point &value)
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

		bool CMaskEdit::setTextInput(IBuiltInTextInput *value)
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

		bool CMaskEdit::setBorderWidth(const RectF &value)
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

		bool CMaskEdit::setLeftBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CMaskEdit::setTopBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CMaskEdit::setRightBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		bool CMaskEdit::setBottomBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		bool CMaskEdit::setBorderRadius(const RectF &value)
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

		bool CMaskEdit::setLeftBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ value, m_sBorderRadius.Top, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CMaskEdit::setTopBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, value, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CMaskEdit::setRightBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, value, m_sBorderRadius.Bottom });
		}

		bool CMaskEdit::setBottomBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, m_sBorderRadius.Right, value });
		}

		bool CMaskEdit::setPadding(const RectF &value)
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

		bool CMaskEdit::setLeftPadding(const float value)
		{
			return setPadding(RectF{ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CMaskEdit::setTopPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CMaskEdit::setRightPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		bool CMaskEdit::setBottomPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		bool CMaskEdit::setBorderColor(const CBuiltInTextInput::State state, const BorderColor &value)
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

		bool CMaskEdit::setLeftBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMaskEdit::setTopBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CMaskEdit::setRightBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CMaskEdit::setBottomBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CMaskEdit::setBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CMaskEdit::setShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CMaskEdit::setShadowColor(const CBuiltInTextInput::State state, const Color &value)
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
		String CMaskEdit::getText()
		{
			return getTextInput()->getText();
		}

		String CMaskEdit::getMask()
		{
			return m_sMask;
		}

		IMaskValidator *CMaskEdit::getValidator()
		{
			return m_pValidator;
		}
	#pragma endregion

	#pragma region ITextInput getters
		String CMaskEdit::getSelectedText()
		{
			return getTextInput()->getSelectedText();
		}

		Point CMaskEdit::getSelection()
		{
			return getTextInput()->getSelection();
		}

		int CMaskEdit::getCaretPosition()
		{
			return getTextInput()->getCaretPosition();
		}

		float CMaskEdit::getScroll()
		{
			return getTextInput()->getScroll();
		}

		int CMaskEdit::getMaxLength()
		{
			return getTextInput()->getMaxLength();
		}

		TextAlign CMaskEdit::getTextAlign()
		{
			return getTextInput()->getAlign();
		}

		CBuiltInTextInput::State CMaskEdit::getState()
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
		bool CMaskEdit::setText(const String &value)
		{
			if (ValidateAndSet(getTextInput()->getText(), value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::setMask(const String &value)
		{
			if (value != m_sMask)
			{
				m_sMask = value;
				if (!ValidateAndSet(getTextInput()->getText(), getTextInput()->getText()))
					getTextInput()->setText(L"");
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::setValidator(IMaskValidator *value)
		{
			if (value != m_pValidator)
			{
				m_pValidator = value;
				if (!ValidateAndSet(getTextInput()->getText(), getTextInput()->getText()))
					getTextInput()->setText(L"");
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextInput setters
		bool CMaskEdit::setSelection(const Point &value)
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

		bool CMaskEdit::setCaretPosition(const int value)
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

		bool CMaskEdit::setScroll(const float value)
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

		bool CMaskEdit::setMaxLength(const int value)
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

		bool CMaskEdit::setTextAlign(const TextAlign value)
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
		bool CMaskEdit::DeleteSelection()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteSelection() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteCharBeforeCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteCharBeforeCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteCharAfterCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteCharAfterCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteWordBeforeCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteWordBeforeCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteWordAfterCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteWordAfterCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteAllBeforeCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteAllBeforeCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::DeleteAllAfterCaret()
		{
			CAttempt attempt{ this };
			if (getTextInput()->DeleteAllAfterCaret() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::MoveCaretLeft(const bool select)
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

		bool CMaskEdit::MoveCaretRight(const bool select)
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

		bool CMaskEdit::MoveCaretWordLeft(const bool select)
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

		bool CMaskEdit::MoveCaretWordRight(const bool select)
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

		bool CMaskEdit::MoveCaretStart(const bool select)
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

		bool CMaskEdit::MoveCaretEnd(const bool select)
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

		bool CMaskEdit::Insert(const wchar_t chr)
		{
			CAttempt attempt{ this };
			if (getTextInput()->Insert(chr) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::Insert(const String &str)
		{
			CAttempt attempt{ this };
			if (getTextInput()->Insert(str) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::Replace(const wchar_t chr)
		{
			CAttempt attempt{ this };
			if (getTextInput()->Replace(chr) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::Replace(const String &str)
		{
			CAttempt attempt{ this };
			if (getTextInput()->Replace(str) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::MoveSelection(const int dst_caret_pos)
		{
			CAttempt attempt{ this };
			if (getTextInput()->MoveSelection(dst_caret_pos) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::CopySelection(const int dst_caret_pos)
		{
			CAttempt attempt{ this };
			if (getTextInput()->CopySelection(dst_caret_pos) && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::Copy()
		{
			return getTextInput()->Copy();
		}

		bool CMaskEdit::Cut()
		{
			CAttempt attempt{ this };
			if (getTextInput()->Cut() && ValidateAndSet(attempt.Text(), getTextInput()->getText()))
			{
				attempt.Success();
				getTextInput()->ScrollToCaret();
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CMaskEdit::Paste()
		{
			return getTextInput()->Paste();
		}

		bool CMaskEdit::SelectAll()
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

		bool CMaskEdit::DeselectAll()
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
		String CMaskEdit::getPlaceholder()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholder();
			return L"";
		}

		bool CMaskEdit::isReadOnly()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReadOnly();
			return false;
		}

		bool CMaskEdit::isReplacing()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReplacing();
			return false;
		}

		float CMaskEdit::getScrollInterval()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getScrollInterval();
			return 0;
		}

		Color CMaskEdit::getTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMaskEdit::getPlaceholderColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMaskEdit::getTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMaskEdit::getSelectionBackgroundColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMaskEdit::getSelectionTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CMaskEdit::getSelectionTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CMaskEdit::getTextShadowShift(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CMaskEdit::getTextShadowRadius(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowRadius(state);
			return 1;
		}

		bool CMaskEdit::isCopyByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByMouseEnabled();
			return false;
		}

		bool CMaskEdit::isMoveByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isMoveByMouseEnabled();
			return false;
		}

		bool CMaskEdit::isSelectWordByDoubleClickEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectWordByDoubleClickEnabled();
			return false;
		}

		bool CMaskEdit::isKeyLeftEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyLeftEnabled();
			return false;
		}

		bool CMaskEdit::isKeyRightEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyRightEnabled();
			return false;
		}

		bool CMaskEdit::isKeyHomeEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyHomeEnabled();
			return false;
		}

		bool CMaskEdit::isKeyEndEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyEndEnabled();
			return false;
		}

		bool CMaskEdit::isKeyDeleteEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyDeleteEnabled();
			return false;
		}

		bool CMaskEdit::isKeyBackspaceEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyBackspaceEnabled();
			return false;
		}

		bool CMaskEdit::isSelectAllByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectAllByKeyEnabled();
			return false;
		}

		bool CMaskEdit::isPasteByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isPasteByKeyEnabled();
			return false;
		}

		bool CMaskEdit::isCopyByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByKeyEnabled();
			return false;
		}

		bool CMaskEdit::isCutByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCutByKeyEnabled();
			return false;
		}

		bool CMaskEdit::isInsertReplaceChangeByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isInsertReplaceChangeByKeyEnabled();
			return false;
		}
	#pragma endregion

	#pragma region CTextInput setters
		bool CMaskEdit::setPlaceholder(const String &value)
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

		bool CMaskEdit::setReadOnly(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setReadOnly(value);
			return false;
		}

		bool CMaskEdit::setReplacing(const bool value)
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

		bool CMaskEdit::setScrollInterval(const float value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setScrollInterval(value);
			return false;
		}

		bool CMaskEdit::setTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setPlaceholderColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setSelectionBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setSelectionTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setSelectionTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CMaskEdit::setTextShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CMaskEdit::setTextShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CMaskEdit::setCopyByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByMouseEnabled(value);
			return false;
		}

		bool CMaskEdit::setMoveByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setMoveByMouseEnabled(value);
			return false;
		}

		bool CMaskEdit::setSelectWordByDoubleClickEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectWordByDoubleClickEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyLeftEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyLeftEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyRightEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyRightEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyHomeEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyHomeEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyEndEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyEndEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyDeleteEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyDeleteEnabled(value);
			return false;
		}

		bool CMaskEdit::setKeyBackspaceEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyBackspaceEnabled(value);
			return false;
		}

		bool CMaskEdit::setSelectAllByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectAllByKeyEnabled(value);
			return false;
		}

		bool CMaskEdit::setPasteByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setPasteByKeyEnabled(value);
			return false;
		}

		bool CMaskEdit::setCopyByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByKeyEnabled(value);
			return false;
		}

		bool CMaskEdit::setCutByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCutByKeyEnabled(value);
			return false;
		}

		bool CMaskEdit::setInsertReplaceChangeByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setInsertReplaceChangeByKeyEnabled(value);
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CMaskEdit::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getTextInput()->Refresh();
		}

		void CMaskEdit::UpdateFromStyle()
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

		void CMaskEdit::AdjustTextInputSize()
		{
			getTextInput()->setSize(PointF{
				ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right),
				ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom) });
			getTextInput()->setPosition(PointF{ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top });
		}

		RectF CMaskEdit::getRenderRect(const CBuiltInTextInput::State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		bool CMaskEdit::ValidateAndSet(const String &original, const String &text)
		{
			String s{ text };
			int caret_position{ getTextInput()->getCaretPosition() };
			IMaskValidator *validator{ m_pValidator ? m_pValidator : &m_cDefaultValidator };
			if (validator->Validate(this, m_sMask, original, s, caret_position))
			{
				getTextInput()->setText(s);
				getTextInput()->setCaretPosition(caret_position);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CMaskEdit::Render()
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