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
		CPasswordEdit::CGradientListener::CGradientListener(CPasswordEdit *control) :
			m_pControl{ control }
		{

		}

		void CPasswordEdit::CGradientListener::NotifyOnChange()
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
		CPasswordEdit::CPasswordEdit() :
			CControl(L"PasswordEdit", true, true, false, true, false, true),
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
			m_cReplaceSymbol{ L'*' },
			m_bIgnoreGradient{ false },
			m_bIgnoreTextInput{ false },
			m_pCanvas{ nullptr },
			m_cListener{ this },
			OnChange{ nullptr }
		{
			setService(new CPasswordEditService(this), true);
			setSize(PointF{ 120, 21 });
			setCursor(CursorType::IBeam);
		}

		CPasswordEdit::CPasswordEdit(IControl *parent) : CPasswordEdit()
		{
			setParent(parent);
		}

		CPasswordEdit::CPasswordEdit(IForm *parent) : CPasswordEdit()
		{
			setForm(parent);
		}

		CPasswordEdit::~CPasswordEdit()
		{
			if (m_pTextInput)
				m_pTextInput->Release();
		}
	#pragma endregion

	#pragma region Helpers
		void CPasswordEdit::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getTextInput()->Refresh();
		}

		void CPasswordEdit::UpdateFromStyle()
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

		void CPasswordEdit::AdjustTextInputSize()
		{
			getTextInput()->setSize(PointF{
				ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right),
				ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom) });
			getTextInput()->setPosition(PointF{ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top });
		}

		RectF CPasswordEdit::getRenderRect(const CBuiltInTextInput::State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		String CPasswordEdit::getDisguisedText(const String &txt)
		{
			String result;
			result.resize(txt.length(), m_cReplaceSymbol);
			return result;
		}
	#pragma endregion

	#pragma region Getters
		RectF CPasswordEdit::getClientRect()
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

		RectF CPasswordEdit::getRenderRect()
		{
			RectF result{ getRenderRect(CBuiltInTextInput::State::Normal) };
			for (int i = (int)CBuiltInTextInput::State::Normal + 1; i <= (int)CBuiltInTextInput::State::Disabled; i++)
				result += getRenderRect((CBuiltInTextInput::State)i);
			return result;
		}

		CursorType CPasswordEdit::getCursor()
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

		IBuiltInTextInput *CPasswordEdit::getTextInput()
		{
			if (!m_pTextInput)
			{
				m_pTextInput = new CPasswordEditTextInput(this);
				m_pTextInput->setListener(&m_cListener);
			}
			return m_pTextInput;
		}

		RectF CPasswordEdit::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CPasswordEdit::getLeftBorderWidth() const
		{
			return m_sBorderWidth.Left;
		}

		float CPasswordEdit::getTopBorderWidth() const
		{
			return m_sBorderWidth.Top;
		}

		float CPasswordEdit::getRightBorderWidth() const
		{
			return m_sBorderWidth.Right;
		}

		float CPasswordEdit::getBottomBorderWidth() const
		{
			return m_sBorderWidth.Bottom;
		}

		RectF CPasswordEdit::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		float CPasswordEdit::getLeftBorderRadius() const
		{
			return m_sBorderRadius.Left;
		}

		float CPasswordEdit::getTopBorderRadius() const
		{
			return m_sBorderRadius.Top;
		}

		float CPasswordEdit::getRightBorderRadius() const
		{
			return m_sBorderRadius.Right;
		}

		float CPasswordEdit::getBottomBorderRadius() const
		{
			return m_sBorderRadius.Bottom;
		}

		RectF CPasswordEdit::getPadding() const
		{
			return m_sPadding;
		}

		float CPasswordEdit::getLeftPadding() const
		{
			return m_sPadding.Left;
		}

		float CPasswordEdit::getTopPadding() const
		{
			return m_sPadding.Top;
		}

		float CPasswordEdit::getRightPadding() const
		{
			return m_sPadding.Right;
		}

		float CPasswordEdit::getBottomPadding() const
		{
			return m_sPadding.Bottom;
		}

		BorderColor CPasswordEdit::getBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CPasswordEdit::getLeftBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CPasswordEdit::getTopBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CPasswordEdit::getRightBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CPasswordEdit::getBottomBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CPasswordEdit::getBackgroundColor(const CBuiltInTextInput::State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CPasswordEdit::getBackgroundGradient(const CBuiltInTextInput::State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CPasswordEdit::getShadowRadius(const CBuiltInTextInput::State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CPasswordEdit::getShadowShift(const CBuiltInTextInput::State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CPasswordEdit::getShadowColor(const CBuiltInTextInput::State state) const
		{
			return m_aShadowColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CPasswordEdit::setDPI(const Point &value)
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

		bool CPasswordEdit::setTextInput(IBuiltInTextInput *value)
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

		bool CPasswordEdit::setBorderWidth(const RectF &value)
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

		bool CPasswordEdit::setLeftBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CPasswordEdit::setTopBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CPasswordEdit::setRightBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		bool CPasswordEdit::setBottomBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		bool CPasswordEdit::setBorderRadius(const RectF &value)
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

		bool CPasswordEdit::setLeftBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ value, m_sBorderRadius.Top, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CPasswordEdit::setTopBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, value, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CPasswordEdit::setRightBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, value, m_sBorderRadius.Bottom });
		}

		bool CPasswordEdit::setBottomBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, m_sBorderRadius.Right, value });
		}

		bool CPasswordEdit::setPadding(const RectF &value)
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

		bool CPasswordEdit::setLeftPadding(const float value)
		{
			return setPadding(RectF{ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CPasswordEdit::setTopPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CPasswordEdit::setRightPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		bool CPasswordEdit::setBottomPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		bool CPasswordEdit::setBorderColor(const CBuiltInTextInput::State state, const BorderColor &value)
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

		bool CPasswordEdit::setLeftBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CPasswordEdit::setTopBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CPasswordEdit::setRightBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CPasswordEdit::setBottomBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CPasswordEdit::setBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CPasswordEdit::setShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CPasswordEdit::setShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

	#pragma region IPasswordEdit getters
		String CPasswordEdit::getPassword()
		{
			return getTextInput()->getText();
		}

		wchar_t CPasswordEdit::getReplaceSymbol()
		{
			return m_cReplaceSymbol;
		}
	#pragma endregion

	#pragma region ITextInput getters
		String CPasswordEdit::getSelectedText()
		{
			return getTextInput()->getSelectedText();
		}

		Point CPasswordEdit::getSelection()
		{
			return getTextInput()->getSelection();
		}

		int CPasswordEdit::getCaretPosition()
		{
			return getTextInput()->getCaretPosition();
		}

		float CPasswordEdit::getScroll()
		{
			return getTextInput()->getScroll();
		}

		int CPasswordEdit::getMaxLength()
		{
			return getTextInput()->getMaxLength();
		}

		int CPasswordEdit::getUndoLimitCount()
		{
			return getTextInput()->getUndoLimitCount();
		}

		int CPasswordEdit::getUndoLimitSize()
		{
			return getTextInput()->getUndoLimitSize();
		}

		bool CPasswordEdit::canUndo()
		{
			return getTextInput()->canUndo();
		}

		bool CPasswordEdit::canRedo()
		{
			return getTextInput()->canRedo();
		}

		TextAlign CPasswordEdit::getTextAlign()
		{
			return getTextInput()->getAlign();
		}

		CBuiltInTextInput::State CPasswordEdit::getState()
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

	#pragma region IPasswordEdit setters
		bool CPasswordEdit::setPassword(const String &value)
		{
			if (getTextInput()->setText(value))
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CPasswordEdit::setReplaceSymbol(const wchar_t value)
		{
			if (value != m_cReplaceSymbol)
			{
				m_cReplaceSymbol = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextInput setters
		bool CPasswordEdit::setSelection(const Point &value)
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

		bool CPasswordEdit::setCaretPosition(const int value)
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

		bool CPasswordEdit::setScroll(const float value)
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

		bool CPasswordEdit::setMaxLength(const int value)
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

		bool CPasswordEdit::setUndoLimitCount(const int value)
		{
			return getTextInput()->setUndoLimitCount(value);
		}

		bool CPasswordEdit::setUndoLimitSize(const int value)
		{
			return getTextInput()->setUndoLimitSize(value);
		}

		bool CPasswordEdit::setTextAlign(const TextAlign value)
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
		bool CPasswordEdit::DeleteSelection()
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

		bool CPasswordEdit::DeleteCharBeforeCaret()
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

		bool CPasswordEdit::DeleteCharAfterCaret()
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

		bool CPasswordEdit::DeleteWordBeforeCaret()
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

		bool CPasswordEdit::DeleteWordAfterCaret()
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

		bool CPasswordEdit::DeleteAllBeforeCaret()
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

		bool CPasswordEdit::DeleteAllAfterCaret()
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

		bool CPasswordEdit::MoveCaretLeft(const bool select)
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

		bool CPasswordEdit::MoveCaretRight(const bool select)
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

		bool CPasswordEdit::MoveCaretWordLeft(const bool select)
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

		bool CPasswordEdit::MoveCaretWordRight(const bool select)
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

		bool CPasswordEdit::MoveCaretStart(const bool select)
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

		bool CPasswordEdit::MoveCaretEnd(const bool select)
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

		bool CPasswordEdit::Undo()
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

		bool CPasswordEdit::Redo()
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

		bool CPasswordEdit::Insert(const wchar_t chr)
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

		bool CPasswordEdit::Insert(const String &str)
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

		bool CPasswordEdit::Replace(const wchar_t chr)
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

		bool CPasswordEdit::Replace(const String &str)
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

		bool CPasswordEdit::MoveSelection(const int dst_caret_pos)
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

		bool CPasswordEdit::CopySelection(const int dst_caret_pos)
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

		bool CPasswordEdit::Copy()
		{
			return getTextInput()->Copy();
		}

		bool CPasswordEdit::Cut()
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

		bool CPasswordEdit::Paste()
		{
			return getTextInput()->Paste();
		}

		bool CPasswordEdit::SelectAll()
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

		bool CPasswordEdit::DeselectAll()
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
		String CPasswordEdit::getPlaceholder()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholder();
			return L"";
		}

		bool CPasswordEdit::isReadOnly()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReadOnly();
			return false;
		}

		bool CPasswordEdit::isReplacing()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReplacing();
			return false;
		}

		float CPasswordEdit::getScrollInterval()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getScrollInterval();
			return 0;
		}

		Color CPasswordEdit::getTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CPasswordEdit::getPlaceholderColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CPasswordEdit::getTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CPasswordEdit::getSelectionBackgroundColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CPasswordEdit::getSelectionTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CPasswordEdit::getSelectionTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CPasswordEdit::getTextShadowShift(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CPasswordEdit::getTextShadowRadius(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowRadius(state);
			return 1;
		}

		bool CPasswordEdit::isCopyByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByMouseEnabled();
			return false;
		}

		bool CPasswordEdit::isMoveByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isMoveByMouseEnabled();
			return false;
		}

		bool CPasswordEdit::isSelectWordByDoubleClickEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectWordByDoubleClickEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyLeftEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyLeftEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyRightEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyRightEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyHomeEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyHomeEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyEndEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyEndEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyDeleteEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyDeleteEnabled();
			return false;
		}

		bool CPasswordEdit::isKeyBackspaceEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyBackspaceEnabled();
			return false;
		}

		bool CPasswordEdit::isSelectAllByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectAllByKeyEnabled();
			return false;
		}

		bool CPasswordEdit::isPasteByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isPasteByKeyEnabled();
			return false;
		}

		bool CPasswordEdit::isCopyByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByKeyEnabled();
			return false;
		}

		bool CPasswordEdit::isCutByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCutByKeyEnabled();
			return false;
		}

		bool CPasswordEdit::isHistoryByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isHistoryByKeyEnabled();
			return false;
		}

		bool CPasswordEdit::isInsertReplaceChangeByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isInsertReplaceChangeByKeyEnabled();
			return false;
		}
	#pragma endregion

	#pragma region CTextInput setters
		bool CPasswordEdit::setPlaceholder(const String &value)
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

		bool CPasswordEdit::setReadOnly(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setReadOnly(value);
			return false;
		}

		bool CPasswordEdit::setReplacing(const bool value)
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

		bool CPasswordEdit::setScrollInterval(const float value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setScrollInterval(value);
			return false;
		}

		bool CPasswordEdit::setTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setPlaceholderColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setSelectionBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setSelectionTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setSelectionTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CPasswordEdit::setTextShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CPasswordEdit::setTextShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CPasswordEdit::setCopyByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByMouseEnabled(value);
			return false;
		}

		bool CPasswordEdit::setMoveByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setMoveByMouseEnabled(value);
			return false;
		}

		bool CPasswordEdit::setSelectWordByDoubleClickEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectWordByDoubleClickEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyLeftEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyLeftEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyRightEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyRightEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyHomeEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyHomeEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyEndEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyEndEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyDeleteEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyDeleteEnabled(value);
			return false;
		}

		bool CPasswordEdit::setKeyBackspaceEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyBackspaceEnabled(value);
			return false;
		}

		bool CPasswordEdit::setSelectAllByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectAllByKeyEnabled(value);
			return false;
		}

		bool CPasswordEdit::setPasteByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setPasteByKeyEnabled(value);
			return false;
		}

		bool CPasswordEdit::setCopyByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByKeyEnabled(value);
			return false;
		}

		bool CPasswordEdit::setCutByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCutByKeyEnabled(value);
			return false;
		}

		bool CPasswordEdit::setHistoryByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setHistoryByKeyEnabled(value);
			return false;
		}

		bool CPasswordEdit::setInsertReplaceChangeByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setInsertReplaceChangeByKeyEnabled(value);
			return false;
		}
	#pragma endregion

	#pragma region Paint
		void CPasswordEdit::Render()
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
					
				IBuiltInTextInput *input{ getTextInput() };
				String txt{ input->getText() };
				m_bIgnoreTextInput = true;
				input->setText(getDisguisedText(txt));
				input->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + m_sPadding.Left + disp.X, m_sBorderWidth.Top + m_sPadding.Top + disp.Y, 0), &b);
				input->setText(txt);
				m_bIgnoreTextInput = false;

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}