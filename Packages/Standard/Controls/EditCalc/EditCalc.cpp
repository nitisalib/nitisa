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
		CEditCalc::CGradientListener::CGradientListener(CEditCalc *control) :
			m_pControl{ control }
		{

		}

		void CEditCalc::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region CTextInput
		CEditCalc::CTextInput::CTextInput(CEditCalc *control) :
			CBuiltInTextInput(),
			m_pControl{ control }
		{

		}

		IControl *CEditCalc::CTextInput::getControl()
		{
			return m_pControl;
		}

		CBuiltInTextInput::State CEditCalc::CTextInput::getState()
		{
			return m_pControl->getState();
		}
	#pragma endregion

	#pragma region CTextInputListener
		CEditCalc::CTextInputListener::CTextInputListener(CEditCalc *control) :
			m_pControl{ control }
		{

		}

		void CEditCalc::CTextInputListener::NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(rect, true);
		}

		void CEditCalc::CTextInputListener::NotifyOnTextChanged(IBuiltInControl *sender)
		{
			if (m_pControl->OnChange)
				m_pControl->OnChange(m_pControl);
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CEditCalc::CEditCalc() :
			CControl(L"EditCalc", true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_cTextInputListener{ this },
			m_bAutoCalculate{ true },
			m_bCalculateOnReturn{ true },
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
			OnChange{ nullptr }
		{
			setService(new CEditCalcService(this), true);
			setSize(PointF{ 120, 21 });
			setCursor(CursorType::IBeam);
		}

		CEditCalc::CEditCalc(IControl *parent) :
			CEditCalc()
		{
			setParent(parent);
		}

		CEditCalc::CEditCalc(IForm *parent) :
			CEditCalc()
		{
			setForm(parent);
		}

		CEditCalc::~CEditCalc()
		{
			if (m_pTextInput)
				m_pTextInput->Release();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CEditCalc::getClientRect()
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

		RectF CEditCalc::getRenderRect()
		{
			RectF result{ getRenderRect(CBuiltInTextInput::State::Normal) };
			for (int i = (int)CBuiltInTextInput::State::Normal + 1; i <= (int)CBuiltInTextInput::State::Disabled; i++)
				result += getRenderRect((CBuiltInTextInput::State)i);
			return result;
		}

		CursorType CEditCalc::getCursor()
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
	#pragma endregion

	#pragma region IControl setters
		bool CEditCalc::setDPI(const Point &value)
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
	#pragma endregion

	#pragma region IControl methods
		void CEditCalc::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			getTextInput()->Refresh();
		}
	#pragma endregion

	#pragma region IEdit getters
		String CEditCalc::getText()
		{
			return getTextInput()->getText();
		}
	#pragma endregion

	#pragma region IEdit setters
		bool CEditCalc::setText(const String &value)
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

	#pragma region IEditCalc getters
		bool CEditCalc::isAutoCalculate()
		{
			return m_bAutoCalculate;
		}

		bool CEditCalc::isCalculateOnReturn()
		{
			return m_bCalculateOnReturn;
		}
	#pragma endregion

	#pragma region IEditCalc setters
		bool CEditCalc::setAutoCalculate(const bool value)
		{
			if (value != m_bAutoCalculate)
			{
				m_bAutoCalculate = value;
				return true;
			}
			return false;
		}

		bool CEditCalc::setCalculateOnReturn(const bool value)
		{
			if (value != m_bCalculateOnReturn)
			{
				m_bCalculateOnReturn = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IEditCalc methods
		bool CEditCalc::Calculate()
		{
			if (m_cExpressionRunner.Prepare(getText()) && m_cExpressionRunner.Run())
			{
				setText(m_cExpressionRunner.Result.toString());
				m_cExpressionRunner.DeleteVariables();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ITextInput getters
		String CEditCalc::getSelectedText()
		{
			return getTextInput()->getSelectedText();
		}

		Point CEditCalc::getSelection()
		{
			return getTextInput()->getSelection();
		}

		int CEditCalc::getCaretPosition()
		{
			return getTextInput()->getCaretPosition();
		}

		float CEditCalc::getScroll()
		{
			return getTextInput()->getScroll();
		}

		int CEditCalc::getMaxLength()
		{
			return getTextInput()->getMaxLength();
		}

		int CEditCalc::getUndoLimitCount()
		{
			return getTextInput()->getUndoLimitCount();
		}

		int CEditCalc::getUndoLimitSize()
		{
			return getTextInput()->getUndoLimitSize();
		}

		bool CEditCalc::canUndo()
		{
			return getTextInput()->canUndo();
		}

		bool CEditCalc::canRedo()
		{
			return getTextInput()->canRedo();
		}

		TextAlign CEditCalc::getTextAlign()
		{
			return getTextInput()->getAlign();
		}

		CBuiltInTextInput::State CEditCalc::getState()
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

	#pragma region ITextInput setters
		bool CEditCalc::setSelection(const Point &value)
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

		bool CEditCalc::setCaretPosition(const int value)
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

		bool CEditCalc::setScroll(const float value)
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

		bool CEditCalc::setMaxLength(const int value)
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

		bool CEditCalc::setUndoLimitCount(const int value)
		{
			return getTextInput()->setUndoLimitCount(value);
		}

		bool CEditCalc::setUndoLimitSize(const int value)
		{
			return getTextInput()->setUndoLimitSize(value);
		}

		bool CEditCalc::setTextAlign(const TextAlign value)
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
		bool CEditCalc::DeleteSelection()
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

		bool CEditCalc::DeleteCharBeforeCaret()
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

		bool CEditCalc::DeleteCharAfterCaret()
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

		bool CEditCalc::DeleteWordBeforeCaret()
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

		bool CEditCalc::DeleteWordAfterCaret()
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

		bool CEditCalc::DeleteAllBeforeCaret()
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

		bool CEditCalc::DeleteAllAfterCaret()
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

		bool CEditCalc::MoveCaretLeft(const bool select)
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

		bool CEditCalc::MoveCaretRight(const bool select)
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

		bool CEditCalc::MoveCaretWordLeft(const bool select)
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

		bool CEditCalc::MoveCaretWordRight(const bool select)
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

		bool CEditCalc::MoveCaretStart(const bool select)
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

		bool CEditCalc::MoveCaretEnd(const bool select)
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

		bool CEditCalc::Undo()
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

		bool CEditCalc::Redo()
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

		bool CEditCalc::Insert(const wchar_t chr)
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

		bool CEditCalc::Insert(const String &str)
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

		bool CEditCalc::Replace(const wchar_t chr)
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

		bool CEditCalc::Replace(const String &str)
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

		bool CEditCalc::MoveSelection(const int dst_caret_pos)
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

		bool CEditCalc::CopySelection(const int dst_caret_pos)
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

		bool CEditCalc::Copy()
		{
			return getTextInput()->Copy();
		}

		bool CEditCalc::Cut()
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

		bool CEditCalc::Paste()
		{
			return getTextInput()->Paste();
		}

		bool CEditCalc::SelectAll()
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

		bool CEditCalc::DeselectAll()
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

	#pragma region TextInput getters
		String CEditCalc::getPlaceholder()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholder();
			return L"";
		}

		bool CEditCalc::isReadOnly()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReadOnly();
			return false;
		}

		bool CEditCalc::isReplacing()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isReplacing();
			return false;
		}

		float CEditCalc::getScrollInterval()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getScrollInterval();
			return 0;
		}

		Color CEditCalc::getTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEditCalc::getPlaceholderColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getPlaceholderColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEditCalc::getTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEditCalc::getSelectionBackgroundColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionBackgroundColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEditCalc::getSelectionTextColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionTextColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		Color CEditCalc::getSelectionTextShadowColor(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getSelectionShadowColor(state);
			return Color{ 0, 0, 0, 0 };
		}

		PointF CEditCalc::getTextShadowShift(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowShift(state);
			return PointF{ 0, 0 };
		}

		int CEditCalc::getTextShadowRadius(const CBuiltInTextInput::State state)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->getShadowRadius(state);
			return 1;
		}

		bool CEditCalc::isCopyByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByMouseEnabled();
			return false;
		}

		bool CEditCalc::isMoveByMouseEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isMoveByMouseEnabled();
			return false;
		}

		bool CEditCalc::isSelectWordByDoubleClickEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectWordByDoubleClickEnabled();
			return false;
		}

		bool CEditCalc::isKeyLeftEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyLeftEnabled();
			return false;
		}

		bool CEditCalc::isKeyRightEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyRightEnabled();
			return false;
		}

		bool CEditCalc::isKeyHomeEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyHomeEnabled();
			return false;
		}

		bool CEditCalc::isKeyEndEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyEndEnabled();
			return false;
		}

		bool CEditCalc::isKeyDeleteEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyDeleteEnabled();
			return false;
		}

		bool CEditCalc::isKeyBackspaceEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isKeyBackspaceEnabled();
			return false;
		}

		bool CEditCalc::isSelectAllByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isSelectAllByKeyEnabled();
			return false;
		}

		bool CEditCalc::isPasteByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isPasteByKeyEnabled();
			return false;
		}

		bool CEditCalc::isCopyByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCopyByKeyEnabled();
			return false;
		}

		bool CEditCalc::isCutByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isCutByKeyEnabled();
			return false;
		}

		bool CEditCalc::isHistoryByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isHistoryByKeyEnabled();
			return false;
		}

		bool CEditCalc::isInsertReplaceChangeByKeyEnabled()
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->isInsertReplaceChangeByKeyEnabled();
			return false;
		}
	#pragma endregion

	#pragma region TextInput setters
		bool CEditCalc::setPlaceholder(const String &value)
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

		bool CEditCalc::setReadOnly(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setReadOnly(value);
			return false;
		}

		bool CEditCalc::setReplacing(const bool value)
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

		bool CEditCalc::setScrollInterval(const float value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setScrollInterval(value);
			return false;
		}

		bool CEditCalc::setTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setPlaceholderColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setSelectionBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setSelectionTextColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setSelectionTextShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setTextShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CEditCalc::setTextShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CEditCalc::setCopyByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByMouseEnabled(value);
			return false;
		}

		bool CEditCalc::setMoveByMouseEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setMoveByMouseEnabled(value);
			return false;
		}

		bool CEditCalc::setSelectWordByDoubleClickEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectWordByDoubleClickEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyLeftEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyLeftEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyRightEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyRightEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyHomeEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyHomeEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyEndEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyEndEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyDeleteEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyDeleteEnabled(value);
			return false;
		}

		bool CEditCalc::setKeyBackspaceEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setKeyBackspaceEnabled(value);
			return false;
		}

		bool CEditCalc::setSelectAllByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setSelectAllByKeyEnabled(value);
			return false;
		}

		bool CEditCalc::setPasteByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setPasteByKeyEnabled(value);
			return false;
		}

		bool CEditCalc::setCopyByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCopyByKeyEnabled(value);
			return false;
		}

		bool CEditCalc::setCutByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setCutByKeyEnabled(value);
			return false;
		}

		bool CEditCalc::setHistoryByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setHistoryByKeyEnabled(value);
			return false;
		}

		bool CEditCalc::setInsertReplaceChangeByKeyEnabled(const bool value)
		{
			CBuiltInTextInput *input{ cast<CBuiltInTextInput*>(getTextInput()) };
			if (input)
				return input->setInsertReplaceChangeByKeyEnabled(value);
			return false;
		}
	#pragma endregion

	#pragma region Layout getters
		RectF CEditCalc::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		float CEditCalc::getLeftBorderWidth() const
		{
			return m_sBorderWidth.Left;
		}

		float CEditCalc::getTopBorderWidth() const
		{
			return m_sBorderWidth.Top;
		}

		float CEditCalc::getRightBorderWidth() const
		{
			return m_sBorderWidth.Right;
		}

		float CEditCalc::getBottomBorderWidth() const
		{
			return m_sBorderWidth.Bottom;
		}

		RectF CEditCalc::getBorderRadius() const
		{
			return m_sBorderRadius;
		}

		float CEditCalc::getLeftBorderRadius() const
		{
			return m_sBorderRadius.Left;
		}

		float CEditCalc::getTopBorderRadius() const
		{
			return m_sBorderRadius.Top;
		}

		float CEditCalc::getRightBorderRadius() const
		{
			return m_sBorderRadius.Right;
		}

		float CEditCalc::getBottomBorderRadius() const
		{
			return m_sBorderRadius.Bottom;
		}

		RectF CEditCalc::getPadding() const
		{
			return m_sPadding;
		}

		float CEditCalc::getLeftPadding() const
		{
			return m_sPadding.Left;
		}

		float CEditCalc::getTopPadding() const
		{
			return m_sPadding.Top;
		}

		float CEditCalc::getRightPadding() const
		{
			return m_sPadding.Right;
		}

		float CEditCalc::getBottomPadding() const
		{
			return m_sPadding.Bottom;
		}

		BorderColor CEditCalc::getBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state];
		}

		Color CEditCalc::getLeftBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Left;
		}

		Color CEditCalc::getTopBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Top;
		}

		Color CEditCalc::getRightBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Right;
		}

		Color CEditCalc::getBottomBorderColor(const CBuiltInTextInput::State state) const
		{
			return m_aBorderColor[(int)state].Bottom;
		}

		Color CEditCalc::getBackgroundColor(const CBuiltInTextInput::State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CEditCalc::getBackgroundGradient(const CBuiltInTextInput::State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		int CEditCalc::getShadowRadius(const CBuiltInTextInput::State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CEditCalc::getShadowShift(const CBuiltInTextInput::State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CEditCalc::getShadowColor(const CBuiltInTextInput::State state) const
		{
			return m_aShadowColor[(int)state];
		}
	#pragma endregion

	#pragma region Layout setters
		bool CEditCalc::setTextInput(IBuiltInTextInput *value)
		{
			if (!value || value == m_pTextInput)
				return false;
			value->setListener(&m_cTextInputListener);
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

		bool CEditCalc::setBorderWidth(const RectF &value)
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

		bool CEditCalc::setLeftBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ value, m_sBorderWidth.Top, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CEditCalc::setTopBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, value, m_sBorderWidth.Right, m_sBorderWidth.Bottom });
		}

		bool CEditCalc::setRightBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, value, m_sBorderWidth.Bottom });
		}

		bool CEditCalc::setBottomBorderWidth(const float value)
		{
			return setBorderWidth(RectF{ m_sBorderWidth.Left, m_sBorderWidth.Top, m_sBorderWidth.Right, value });
		}

		bool CEditCalc::setBorderRadius(const RectF &value)
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

		bool CEditCalc::setLeftBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ value, m_sBorderRadius.Top, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CEditCalc::setTopBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, value, m_sBorderRadius.Right, m_sBorderRadius.Bottom });
		}

		bool CEditCalc::setRightBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, value, m_sBorderRadius.Bottom });
		}

		bool CEditCalc::setBottomBorderRadius(const float value)
		{
			return setBorderRadius(RectF{ m_sBorderRadius.Left, m_sBorderRadius.Top, m_sBorderRadius.Right, value });
		}

		bool CEditCalc::setPadding(const RectF &value)
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

		bool CEditCalc::setLeftPadding(const float value)
		{
			return setPadding(RectF{ value, m_sPadding.Top, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CEditCalc::setTopPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, value, m_sPadding.Right, m_sPadding.Bottom });
		}

		bool CEditCalc::setRightPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, value, m_sPadding.Bottom });
		}

		bool CEditCalc::setBottomPadding(const float value)
		{
			return setPadding(RectF{ m_sPadding.Left, m_sPadding.Top, m_sPadding.Right, value });
		}

		bool CEditCalc::setBorderColor(const CBuiltInTextInput::State state, const BorderColor &value)
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

		bool CEditCalc::setLeftBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ value, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CEditCalc::setTopBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, value, m_aBorderColor[(int)state].Right, m_aBorderColor[(int)state].Bottom });
		}

		bool CEditCalc::setRightBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, value, m_aBorderColor[(int)state].Bottom });
		}

		bool CEditCalc::setBottomBorderColor(const CBuiltInTextInput::State state, const Color &value)
		{
			return setBorderColor(state, BorderColor{ m_aBorderColor[(int)state].Left, m_aBorderColor[(int)state].Top, m_aBorderColor[(int)state].Right, value });
		}

		bool CEditCalc::setBackgroundColor(const CBuiltInTextInput::State state, const Color &value)
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

		bool CEditCalc::setShadowRadius(const CBuiltInTextInput::State state, const int value)
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

		bool CEditCalc::setShadowShift(const CBuiltInTextInput::State state, const PointF &value)
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

		bool CEditCalc::setShadowColor(const CBuiltInTextInput::State state, const Color &value)
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

	#pragma region Helpers
		void CEditCalc::UpdateFromStyle()
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

		void CEditCalc::AdjustTextInputSize()
		{
			getTextInput()->setSize(PointF{
				ntl::Max<float>(0, getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - m_sPadding.Left - m_sPadding.Right),
				ntl::Max<float>(0, getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - m_sPadding.Top - m_sPadding.Bottom) });
			getTextInput()->setPosition({ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top });
		}

		IBuiltInTextInput *CEditCalc::getTextInput()
		{
			if (!m_pTextInput)
			{
				m_pTextInput = new CTextInput(this);
				m_pTextInput->setListener(&m_cTextInputListener);
			}
			return m_pTextInput;
		}

		RectF CEditCalc::getRenderRect(const CBuiltInTextInput::State state)
		{
			return AddShadow(RectF{ 0, 0, getWidth(), getHeight() }, m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}
	#pragma endregion

	#pragma region Render
		void CEditCalc::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			int state{ (int)getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[state], m_aShadowShift[state], m_aShadowRadius[state]) };
			RectF all_rect{ AddShadow(getRect(), m_aShadowColor[state], m_aShadowShift[state], m_aShadowRadius[state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() };
				DrawBlockShadow(renderer, rect, m_sBorderRadius, m_aShadowColor[state], m_aShadowShift[state], m_aShadowRadius[state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_sBorderRadius, m_aBorderColor[state], m_aBackgroundColor[state], m_aBackgroundGradient[state]);
				Block b{ rect, AddElements(m_sBorderWidth, m_sPadding), m_sBorderRadius, PointLocation::Inside };
				getTextInput()->Render(false, ntl::Mat4Translate<float>(m_sBorderWidth.Left + m_sPadding.Left + disp.X, m_sBorderWidth.Top + m_sPadding.Top + disp.Y, 0), &b);

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}
	#pragma endregion
	}
}