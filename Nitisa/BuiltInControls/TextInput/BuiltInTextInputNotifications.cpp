// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region State change notifications
	void CBuiltInTextInput::NotifyOnAttach()
	{
		// No action required
	}

	void CBuiltInTextInput::NotifyOnDeactivate()
	{
		// Not supported
	}

	void CBuiltInTextInput::NotifyOnFreeResources()
	{
		m_bMouseDown = false;
		setFocused(false);
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInTextInput::NotifyOnMouseHover(const PointF &position)
	{
		if (!m_bHovered)
		{
			m_bHovered = true;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseLeave()
	{
		if (m_bHovered)
		{
			m_bHovered = false;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		m_sMousePosition = position;
		if (m_bMouseDown)
		{
			int new_caret{ ClientToCaret(position.X) };
			bool scroll_required{ false };
			if (position.X < 0 || position.X >= getWidth() || position.Y < 0 || position.Y >= getHeight())
			{
				if (new_caret > m_iCaretPosition)
					new_caret = m_iCaretPosition + 1;
				else if (new_caret < m_iCaretPosition)
					new_caret = m_iCaretPosition - 1;
				scroll_required = true;
			}
			if (setCaretPosition(new_caret))
			{
				if (!m_bMoveSelection)
					setSelection({ m_sSelection.X, new_caret });
				if (scroll_required)
					ScrollToCaret();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (isEnabled() && !m_bMouseDown && !middle && !right && position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight() && getControl() && getControl()->getForm())
		{
			int new_caret{ ClientToCaret(position.X) };
			m_iMouseDownCaretPosition = new_caret;
			m_bMouseDown = true;
			m_bMoveSelection = (m_sSelection.X != m_sSelection.Y) && new_caret >= ntl::Min<int>(m_sSelection.X, m_sSelection.Y) && new_caret < ntl::Max<int>(m_sSelection.X, m_sSelection.Y);
			m_hTimer = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
			bool result{ setCaretPosition(new_caret) };
			if (!m_bMoveSelection && shift && setSelection({ m_sSelection.X, new_caret }))
				return true;
			if (!m_bMoveSelection && !shift && setSelection({ new_caret, new_caret }))
				return true;
			return result;
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (m_bMouseDown)
		{
			m_bMouseDown = false;
			if (m_hTimer && getControl() && getControl()->getForm())
			{
				getControl()->getForm()->DeleteTimer(m_hTimer);
				m_hTimer = nullptr;
			}
			if (!m_bReadOnly && m_bMoveSelection)
			{
				if (m_iMouseDownCaretPosition != m_iCaretPosition)
				{
					if (ctrl)
					{
						if (m_bCopyByMouseEnabled && CopySelection(m_iCaretPosition))
						{
							if (cast<IBuiltInTextInputListener*>(m_pListener))
								cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
							return true;
						}
						return false;
					}
					if (m_bMoveByMouseEnabled && MoveSelection(m_iCaretPosition))
					{
						if (cast<IBuiltInTextInputListener*>(m_pListener))
							cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
						return true;
					}
					return false;
				}
				return setSelection({ 0, 0 });
			}
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (
			m_bSelectWordByDoubleClickEnabled &&
			isEnabled() &&
			m_sText.length() > 0 &&
			!m_bMouseDown &&
			m_iCaretPosition <= (int)m_sText.length() &&
			std::isalnum(m_sText[ntl::Min<int>(m_iCaretPosition, (int)m_sText.length() - 1)], std::locale()))
		{
			Point selection{ m_iCaretPosition, ntl::Min<int>(m_iCaretPosition + 1, (int)m_sText.length()) };
			while (selection.X > 0 && std::isalnum(m_sText[selection.X - 1], std::locale()))
				selection.X--;
			while (selection.Y < (int)m_sText.length() && std::isalnum(m_sText[selection.Y], std::locale()))
				selection.Y++;
			return setSelection(selection);
		}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, true, right, ctrl, alt, shift);
	}

	bool CBuiltInTextInput::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return NotifyOnMouseLeftUp(position, middle, true, ctrl, alt, shift);
	}

	bool CBuiltInTextInput::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		return false;
	}

	void CBuiltInTextInput::NotifyOnMouseDownCancel()
	{
		m_bMouseDown = false;
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
	}

	bool CBuiltInTextInput::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}

	bool CBuiltInTextInput::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInTextInput::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (!isEnabled())
			return false;
		bool changed{ false };
		switch (key)
		{
		case Key::Left:
		case Key::Numpad4:
			if (m_bKeyLeftEnabled && (key == Key::Left || (key == Key::Numpad4 && !numlock)))
				if ((ctrl && MoveCaretWordLeft(shift)) || (!ctrl && MoveCaretLeft(shift)))
				{
					ScrollToCaret();
					changed = true;
				}
			break;
		case Key::Right:
		case Key::Numpad6:
			if (m_bKeyRightEnabled && (key == Key::Right || (key == Key::Numpad6 && !numlock)))
				if ((ctrl && MoveCaretWordRight(shift)) || (!ctrl && MoveCaretRight(shift)))
				{
					ScrollToCaret();
					changed = true;
				}
			break;
		case Key::Home:
		case Key::Numpad7:
			if (m_bKeyHomeEnabled && (key == Key::Home || (key == Key::Numpad7 && !numlock)))
				if (MoveCaretStart(shift))
				{
					ScrollToCaret();
					changed = true;
				}
			break;
		case Key::End:
		case Key::Numpad1:
			if (m_bKeyEndEnabled && (key == Key::End || (key == Key::Numpad1 && !numlock)))
				if (MoveCaretEnd(shift))
				{
					ScrollToCaret();
					changed = true;
				}
			break;
		case Key::Delete:
		case Key::Decimal:
			if (m_bKeyDeleteEnabled && (key == Key::Delete || (key == Key::Decimal && !numlock)))
				if (!m_bReadOnly && ((ctrl && DeleteWordAfterCaret()) || (!ctrl && DeleteCharAfterCaret())))
				{
					ScrollToCaret();
					if (cast<IBuiltInTextInputListener*>(m_pListener))
						cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
					changed = true;
				}
			break;
		case Key::Backspace:
			if (m_bKeyBackspaceEnabled && (!m_bReadOnly && ((ctrl && DeleteWordBeforeCaret()) || (!ctrl && DeleteCharBeforeCaret()))))
			{
				ScrollToCaret();
				if (cast<IBuiltInTextInputListener*>(m_pListener))
					cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
				changed = true;
			}
			break;
		case Key::A:
			if (m_bSelectAllByKeyEnabled && ctrl && !shift && !alt)
				if (setSelection({ 0, (int)m_sText.length() }))
				{
					ScrollToCaret();
					changed = true;
				}
			break;
		case Key::V:
			if (m_bPasteByKeyEnabled && ctrl && !shift && !alt && Paste())
				changed = true;
			break;
		case Key::C:
			if (m_bCopyByKeyEnabled && ctrl && !shift && !alt)
				Copy();
			break;
		case Key::X:
			if (m_bCutByKeyEnabled && ctrl && !shift && !alt)
				if (Cut())
				{
					ScrollToCaret();
					if (cast<IBuiltInTextInputListener*>(m_pListener))
						cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
					changed = true;
				}
			break;
		case Key::Z:
			if (m_bHistoryByKeyEnabled && ctrl && !alt)
			{
				bool text_changed{ false };
				if (shift ? Redo(text_changed) : Undo(text_changed))
				{
					ScrollToCaret();
					if (text_changed && cast<IBuiltInTextInputListener*>(m_pListener))
						cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
					changed = true;
				}
			}
			break;
		case Key::Insert:
		case Key::Numpad0:
			if (m_bInsertReplaceChangeByKeyEnabled && (key == Key::Insert || (key == Key::Numpad0 && !numlock)))
				if (!m_bReadOnly)
				{
					m_bReplacing = !m_bReplacing;
					changed = true;
				}
			break;
		default:
			break;
		}
		return changed;
	}

	bool CBuiltInTextInput::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInTextInput::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (isEnabled() && !m_bReadOnly && !std::iscntrl(chr, std::locale()))
			if (!ctrl && !alt && ((m_bReplacing && Replace(chr)) || (!m_bReplacing && Insert(chr))))
			{
				ScrollToCaret();
				if (cast<IBuiltInTextInputListener*>(m_pListener))
					cast<IBuiltInTextInputListener*>(m_pListener)->NotifyOnTextChanged(this);
				return true;
			}
		return false;
	}

	bool CBuiltInTextInput::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInTextInput::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInTextInput::NotifyOnPasteString(const String &text)
	{
		if (!text.empty() && Insert(text))
		{
			ScrollToCaret();
			IBuiltInTextAreaListener *listener{ cast<IBuiltInTextAreaListener*>(m_pListener) };
			if (listener)
				listener->NotifyOnTextChanged(this);
			return true;
		}
		return false;
	}
#pragma endregion
}