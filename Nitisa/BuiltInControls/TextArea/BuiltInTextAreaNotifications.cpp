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
	void CBuiltInTextArea::NotifyOnAttach()
	{
		Update();
	}

	void CBuiltInTextArea::NotifyOnDeactivate()
	{
		// Not supported
	}

	void CBuiltInTextArea::NotifyOnFreeResources()
	{
		m_bMouseDown = false;
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
	}
#pragma endregion

#pragma region Mouse input notifications
	bool CBuiltInTextArea::NotifyOnMouseHover(const PointF &position)
	{
		if (!m_bHovered)
		{
			m_bHovered = true;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseLeave()
	{
		if (m_bHovered)
		{
			m_bHovered = false;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseMove(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		m_sMousePosition = position;
		if (m_bMouseDown)
		{
			int new_caret{ ClientToCaret(position) };
			if (position.X < 0 || position.X >= getWidth() || position.Y < 0 || position.Y >= getHeight())
			{
				bool changed{ false };
				CaretPosition cp{ FindCaretPosition(m_iCaretPosition) };
				if (position.X < 0 && cp.Index > 0)
				{
					cp.Index--;
					changed = true;
				}
				else if (position.X >= getWidth() && cp.Index < (int)m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length())
				{
					cp.Index++;
					changed = true;
				}
				if (position.Y < 0)
				{
					if (cp.LineIndex > 0 || cp.FakeLineIndex > 0)
					{
						if (cp.FakeLineIndex == 0)
						{
							cp.LineIndex--;
							cp.FakeLineIndex = (int)m_aLines[cp.LineIndex].FakeLines.size() - 1;
						}
						else
							cp.FakeLineIndex--;
						cp.Index = ntl::Min<int>((int)m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length(), cp.Index);
						changed = true;
					}
				}
				else if (position.Y >= getHeight())
				{
					if (cp.LineIndex < (int)m_aLines.size() - 1 || cp.FakeLineIndex < (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1)
					{
						if (cp.FakeLineIndex >= (int)m_aLines[cp.LineIndex].FakeLines.size() - 1)
						{
							cp.FakeLineIndex = 0;
							cp.LineIndex++;
						}
						else
							cp.FakeLineIndex++;
						cp.Index = ntl::Min<int>((int)m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length(), cp.Index);
						changed = true;
					}
				}
				if (changed)
					new_caret = CaretPositionToCaret(cp);
			}
			if (new_caret != m_iCaretPosition)
			{
				m_iCaretPosition = new_caret;
				if (!m_bMoveSelection)
					m_sSelection.Y = new_caret;
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseLeftDown(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		if (isEnabled() && !m_bMouseDown && !middle && !right && position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight() && getControl() && getControl()->getForm())
		{
			int new_caret{ ClientToCaret(position) };
			m_iMouseDownCaretPosition = new_caret;
			m_bMouseDown = true;
			m_bMoveSelection = (m_sSelection.X != m_sSelection.Y) && new_caret >= ntl::Min<int>(m_sSelection.X, m_sSelection.Y) && new_caret < ntl::Max<int>(m_sSelection.X, m_sSelection.Y);
			m_hTimer = getControl()->getForm()->CreateTimer(&m_cTimerListener, m_fScrollInterval);
			bool result{ new_caret != m_iCaretPosition };
			m_iCaretPosition = new_caret;
			if (!m_bMoveSelection && shift && m_sSelection.Y != new_caret)
			{
				m_sSelection.Y = new_caret;
				return true;
			}
			if (!m_bMoveSelection && !shift && (m_sSelection.X != new_caret || m_sSelection.Y != new_caret))
			{
				m_sSelection.X = m_sSelection.Y = new_caret;
				return true;
			}
			return result;
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseLeftUp(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
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
							if (cast<IBuiltInTextAreaListener*>(m_pListener))
								cast<IBuiltInTextAreaListener*>(m_pListener)->NotifyOnTextChanged(this);
							return true;
						}
						return false;
					}
					if (m_bMoveByMouseEnabled && MoveSelection(m_iCaretPosition))
					{
						if (cast<IBuiltInTextAreaListener*>(m_pListener))
							cast<IBuiltInTextAreaListener*>(m_pListener)->NotifyOnTextChanged(this);
						return true;
					}
					return false;
				}
				return setSelection({ 0, 0 });
			}
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseLeftDoubleClick(const PointF &position, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		int caret_real{ FakeCaretToReal(m_iCaretPosition) };
		if (
			m_bSelectWordByDoubleClickEnabled &&
			isEnabled() &&
			m_sText.length() > 0 &&
			!m_bMouseDown &&
			m_iCaretPosition <= m_iMaxCaretPosition &&
			std::isalnum(m_sText[ntl::Min<int>(caret_real, (int)m_sText.length() - 1)], std::locale()))
		{
			Point selection{ caret_real, ntl::Min<int>(caret_real + 1, m_iMaxCaretPosition) };
			while (selection.X > 0 && std::isalnum(m_sText[selection.X - 1], std::locale()))
				selection.X--;
			while (selection.Y < (int)m_sText.length() && std::isalnum(m_sText[selection.Y], std::locale()))
				selection.Y++;
			return setSelection(selection);
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseMiddleDown(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseMiddleUp(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseMiddleDoubleClick(const PointF &position, const bool left, const bool right, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseRightDown(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseRightUp(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseRightDoubleClick(const PointF &position, const bool left, const bool middle, const bool ctrl, const bool alt, const bool shift)
	{
		NotifyOnMouseDownCancel();
		return false;
	}

	void CBuiltInTextArea::NotifyOnMouseDownCancel()
	{
		m_bMouseDown = false;
		if (m_hTimer && getControl() && getControl()->getForm())
		{
			getControl()->getForm()->DeleteTimer(m_hTimer);
			m_hTimer = nullptr;
		}
	}

	bool CBuiltInTextArea::NotifyOnMouseVerticalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight() && !m_bMouseDown && getControl() && getControl()->getForm() &&
			getControl()->getForm()->getRenderer() && getControl()->getFont() && getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
		{
			float line_height{ getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(L"Wy", 0).Y };
			PointF range{ getYScrollRange() };
			float old{ m_sScroll.Y };
			{
				if (delta > 0)
					m_sScroll.Y = ntl::Max<float>(range.X, m_sScroll.Y - line_height);
				else
					m_sScroll.Y = ntl::Min<float>(range.Y, m_sScroll.Y + line_height);
				return ntl::IsNotEqual<float>(m_sScroll.Y, old);
			}
		}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnMouseHorizontalWheel(const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift, const int delta)
	{
		if (position.X >= 0 && position.X < getWidth() && position.Y >= 0 && position.Y < getHeight() && !m_bMouseDown && getControl() && getControl()->getForm() &&
			getControl()->getForm()->getRenderer() && getControl()->getFont() && getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
		{
			float line_height{ getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(L"Wy", 0).Y };
			PointF range{ getXScrollRange() };
			float old{ m_sScroll.X };
			{
				if (delta > 0)
					m_sScroll.X = ntl::Max<float>(range.X, m_sScroll.X - line_height);
				else
					m_sScroll.X = ntl::Min<float>(range.Y, m_sScroll.X + line_height);
				return ntl::IsNotEqual<float>(m_sScroll.X, old);
			}
		}
		return false;
	}
#pragma endregion

#pragma region Keyboard input notifications
	bool CBuiltInTextArea::NotifyOnKeyDown(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (!isEnabled())
			return false;
		bool changed{ false }, text_changed{ false };
		switch (key)
		{
		case Key::Left:
		case Key::Numpad4:
			if (m_bKeyLeftEnabled && (key == Key::Left || (key == Key::Numpad4 && !numlock)))
				if ((ctrl && MoveCaretWordLeft(shift)) || (!ctrl && MoveCaretLeft(shift)))
					changed = true;
			break;
		case Key::Right:
		case Key::Numpad6:
			if (m_bKeyRightEnabled && (key == Key::Right || (key == Key::Numpad6 && !numlock)))
				if ((ctrl && MoveCaretWordRight(shift)) || (!ctrl && MoveCaretRight(shift)))
					changed = true;
			break;
		case Key::Home:
		case Key::Numpad7:
			if (m_bKeyHomeEnabled && (key == Key::Home || (key == Key::Numpad7 && !numlock)))
				if ((ctrl && MoveCaretStart(shift)) || (!ctrl && MoveCaretLineStart(shift)))
					changed = true;
			break;
		case Key::End:
		case Key::Numpad1:
			if (m_bKeyEndEnabled && (key == Key::End || (key == Key::Numpad1 && !numlock)))
				if ((ctrl && MoveCaretEnd(shift)) || (!ctrl && MoveCaretLineEnd(shift)))
					changed = true;
			break;
		case Key::Delete:
		case Key::Decimal:
			if (m_bKeyDeleteEnabled && (key == Key::Delete || (key == Key::Decimal && !numlock)))
				if (!m_bReadOnly && ((ctrl && DeleteWordAfterCaret()) || (!ctrl && DeleteCharAfterCaret())))
					changed = text_changed = true;
			break;
		case Key::Backspace:
			if (m_bKeyBackspaceEnabled && (!m_bReadOnly && ((ctrl && DeleteWordBeforeCaret()) || (!ctrl && DeleteCharBeforeCaret()))))
				changed = text_changed = true;
			break;
		case Key::Up:
		case Key::Numpad8:
			if (m_bKeyUpEnabled && (key == Key::Up || (key == Key::Numpad8 && !numlock)))
				if ((ctrl && ScrollLineUp()) || (!ctrl && MoveCaretLineUp(shift)))
					changed = true;
			break;
		case Key::Down:
		case Key::Numpad2:
			if (m_bKeyDownEnabled && (key == Key::Down || (key == Key::Numpad2 && !numlock)))
				if ((ctrl && ScrollLineDown()) || (!ctrl && MoveCaretLineDown(shift)))
					changed = true;
			break;
		case Key::Prior:
		case Key::Numpad9:
			if (m_bKeyPageUpEnabled && (key == Key::Prior || (key == Key::Numpad9 && !numlock)))
				if ((ctrl && MoveCaretPageStart(shift)) || (!ctrl && MoveCaretPageUp(shift)))
					changed = true;
			break;
		case Key::Next:
		case Key::Numpad3:
			if (m_bKeyPageDownEnabled && (key == Key::Next || (key == Key::Numpad3 && !numlock)))
				if ((ctrl && MoveCaretPageEnd(shift)) || (!ctrl && MoveCaretPageDown(shift)))
					changed = true;
			break;
		case Key::A:
			if (m_bSelectAllByKeyEnabled && ctrl && !shift && !alt)
				if (setSelection({ 0, (int)m_sText.length() }))
					changed = true;
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
			if (m_bCutByKeyEnabled && ctrl && !shift && !alt && Cut())
				changed = text_changed = true;
			break;
		case Key::Z:
			if (m_bHistoryByKeyEnabled && ctrl && !alt)
				if (shift ? Redo(text_changed) : Undo(text_changed))
					changed = text_changed = true;
			break;
		case Key::Insert:
		case Key::Numpad0:
			if (m_bInsertReplaceChangeByKeyEnabled && (key == Key::Insert || (key == Key::Numpad0 && !numlock)))
				if (!m_bReadOnly)
				{
					m_bReplacing = !m_bReplacing;
					changed = true;
				}
		case Key::W:
			if (m_bWordWrapChangeByKeyEnabled && ctrl && !shift && !alt)
			{
				setWordWrap(!m_bWordWrap);
				changed = text_changed = true;
			}
			break;
		default:
			break;
		}
		if (text_changed)
		{
			IBuiltInTextAreaListener *listener{ cast<IBuiltInTextAreaListener*>(m_pListener) };
			if (listener)
				listener->NotifyOnTextChanged(this);
		}
		return text_changed || changed;
	}

	bool CBuiltInTextArea::NotifyOnKeyUp(const Key key, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}

	bool CBuiltInTextArea::NotifyOnChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		if (isEnabled() && !m_bReadOnly && (!std::iscntrl(chr, std::locale()) || chr == L'\n' || chr == L'\r'))
			if (!ctrl && !alt && ((m_bReplacing && Replace(chr)) || (!m_bReplacing && Insert(chr))))
			{
				if (cast<IBuiltInTextAreaListener*>(m_pListener))
					cast<IBuiltInTextAreaListener*>(m_pListener)->NotifyOnTextChanged(this);
				return true;
			}
		return false;
	}

	bool CBuiltInTextArea::NotifyOnDeadChar(const wchar_t chr, const bool ctrl, const bool alt, const bool shift, const bool numlock)
	{
		return false;
	}
#pragma endregion

#pragma region Other input notifications
	bool CBuiltInTextArea::NotifyOnDropFiles(const PointF &position, const StringArray &filenames)
	{
		return false;
	}
#pragma endregion

#pragma region Clipboard notifications
	bool CBuiltInTextArea::NotifyOnPasteString(const String &text)
	{
		if (!text.empty() && HelperInsert(text))
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