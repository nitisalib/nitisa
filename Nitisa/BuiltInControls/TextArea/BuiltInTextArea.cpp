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
#pragma region CTimerListener
	CBuiltInTextArea::CTimerListener::CTimerListener(CBuiltInTextArea *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInTextArea::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		if (m_pControl->m_sMousePosition.X < 0 || m_pControl->m_sMousePosition.X >= m_pControl->getWidth() || m_pControl->m_sMousePosition.Y < 0 || m_pControl->m_sMousePosition.Y >= m_pControl->getHeight())
		{
			int new_caret{ m_pControl->m_iCaretPosition };
			bool changed{ false };
			CaretPosition cp{ m_pControl->FindCaretPosition(m_pControl->m_iCaretPosition) };
			if (m_pControl->m_sMousePosition.X < 0 && cp.Index > 0)
			{
				cp.Index--;
				changed = true;
			}
			else if (m_pControl->m_sMousePosition.X >= m_pControl->getWidth() && cp.Index < (int)m_pControl->m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length())
			{
				cp.Index++;
				changed = true;
			}
			if (m_pControl->m_sMousePosition.Y < 0)
			{
				if (cp.LineIndex > 0 || cp.FakeLineIndex > 0)
				{
					if (cp.FakeLineIndex == 0)
					{
						cp.LineIndex--;
						cp.FakeLineIndex = (int)m_pControl->m_aLines[cp.LineIndex].FakeLines.size() - 1;
					}
					else
						cp.FakeLineIndex--;
					cp.Index = ntl::Min<int>((int)m_pControl->m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length(), cp.Index);
					changed = true;
				}
			}
			else if (m_pControl->m_sMousePosition.Y >= m_pControl->getHeight())
			{
				if (cp.LineIndex < (int)m_pControl->m_aLines.size() - 1 || cp.FakeLineIndex < (int)m_pControl->m_aLines[m_pControl->m_aLines.size() - 1].FakeLines.size() - 1)
				{
					if (cp.FakeLineIndex >= (int)m_pControl->m_aLines[cp.LineIndex].FakeLines.size() - 1)
					{
						cp.FakeLineIndex = 0;
						cp.LineIndex++;
					}
					else
						cp.FakeLineIndex++;
					cp.Index = ntl::Min<int>((int)m_pControl->m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].length(), cp.Index);
					changed = true;
				}
			}
			if (changed)
				new_caret = m_pControl->CaretPositionToCaret(cp);

			if (new_caret != m_pControl->m_iCaretPosition)
			{
				m_pControl->m_iCaretPosition = new_caret;
				if (!m_pControl->m_bMoveSelection)
					m_pControl->m_sSelection.Y = new_caret;
				if (cast<IBuiltInTextAreaListener*>(m_pControl->m_pListener))
					cast<IBuiltInTextAreaListener*>(m_pControl->m_pListener)->NotifyOnChanged(m_pControl);
			}
		}
	}
#pragma endregion

#pragma region CCaretListener
	CBuiltInTextArea::CCaretListener::CCaretListener(CBuiltInTextArea *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInTextArea::CCaretListener::NotifyOnChange()
	{
		if (m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInTextArea::CBuiltInTextArea() :
		CBuiltInControl(L"TextArea"),
		m_cCaretListener{ this },
		m_pListener{ nullptr },
		m_iMaxLength{ 0 },
		m_sScroll{ 0, 0 },
		m_eAlign{ TextAlign::Left },
		m_fScrollInterval{ ScrollInterval },
		m_bWordWrap{ false },
		m_bWordBreak{ false },
		m_aTextColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 109, 109, 109, 255 } },
		m_aShadowColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aSelectionBackgroundColor{
			Color{ 127, 127, 127, 132 },
			Color{ 127, 127, 127, 132 },
			Color{ 51, 153, 255, 200 },
			Color{ 51, 153, 255, 200 },
			Color{ 0, 0, 0, 0 } },
		m_aSelectionTextColor{
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 255, 255, 255, 255 },
			Color{ 109, 109, 109, 255 } },
		m_aSelectionShadowColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 } },
		m_aShadowShift{
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 },
			PointF{ 0, 0 } },
		m_aShadowRadius{ 1, 1, 1, 1, 1 },
		m_bReadOnly{ false },
		m_bReplacing{ false },
		m_bCopyByMouseEnabled{ true },
		m_bMoveByMouseEnabled{ true },
		m_bSelectWordByDoubleClickEnabled{ true },
		m_bKeyLeftEnabled{ true },
		m_bKeyRightEnabled{ true },
		m_bKeyHomeEnabled{ true },
		m_bKeyEndEnabled{ true },
		m_bKeyDeleteEnabled{ true },
		m_bKeyBackspaceEnabled{ true },
		m_bKeyUpEnabled{ true },
		m_bKeyDownEnabled{ true },
		m_bKeyPageUpEnabled{ true },
		m_bKeyPageDownEnabled{ true },
		m_bSelectAllByKeyEnabled{ true },
		m_bPasteByKeyEnabled{ true },
		m_bCopyByKeyEnabled{ true },
		m_bCutByKeyEnabled{ true },
		m_bHistoryByKeyEnabled{ true },
		m_bInsertReplaceChangeByKeyEnabled{ true },
		m_bWordWrapChangeByKeyEnabled{ true },
		m_iCaretPosition{ 0 },
		m_sSelection{ 0, 0 },
		m_sTextSize{ 0, 0 },
		m_iMaxCaretPosition{ 0 },
		m_hTimer{ nullptr },
		m_bMouseDown{ false },
		m_bHovered{ false },
		m_cTimerListener{ this }
	{
		m_cHistory.setLimitCount(3);
		StoreHistory();
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInTextArea::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInTextArea::isHovered()
	{
		return m_bHovered;
	}

	CursorType CBuiltInTextArea::getCursor(const PointF &position, const CursorType def)
	{
		if (m_bMouseDown && m_bMoveSelection)
		{
			if (m_iCaretPosition >= m_sSelection.X && m_iCaretPosition <= m_sSelection.Y)
				return CursorType::No;
			return CursorType::Arrow;
		}
		return def;
	}

	bool CBuiltInTextArea::isDown()
	{
		return m_bMouseDown;
	}

	bool CBuiltInTextArea::hasSelection()
	{
		return m_sSelection.X != m_sSelection.Y;
	}
#pragma endregion

#pragma region IBuiltInTextArea getters
	String CBuiltInTextArea::getText()
	{
		return m_sText;
	}

	String CBuiltInTextArea::getSelectedText()
	{
		if (m_sSelection.X == m_sSelection.Y)
			return L"";
		Point selection{ FakeCaretToReal(m_sSelection.X), FakeCaretToReal(m_sSelection.Y) };
		return m_sText.substr(ntl::Min<int>(selection.X, selection.Y), ntl::Abs<int>(selection.Y - selection.X));
	}

	Point CBuiltInTextArea::getSelection()
	{
		return Point{ FakeCaretToReal(m_sSelection.X), FakeCaretToReal(m_sSelection.Y) };
	}

	int CBuiltInTextArea::getCaretPosition()
	{
		return FakeCaretToReal(m_iCaretPosition);
	}

	PointF CBuiltInTextArea::getScroll()
	{
		return m_sScroll;
	}

	int CBuiltInTextArea::getMaxLength()
	{
		return m_iMaxLength;
	}

	int CBuiltInTextArea::getUndoLimitCount()
	{
		return (int)m_cHistory.getLimitCount();
	}

	int CBuiltInTextArea::getUndoLimitSize()
	{
		return (int)m_cHistory.getLimitSize();
	}

	bool CBuiltInTextArea::canUndo()
	{
		return m_cHistory.getPosition() > 0;
	}

	bool CBuiltInTextArea::canRedo()
	{
		return m_cHistory.getCount() > 0 && m_cHistory.getPosition() < m_cHistory.getCount() - 1;
	}

	TextAlign CBuiltInTextArea::getAlign()
	{
		return m_eAlign;
	}

	PointB CBuiltInTextArea::getScrollRequired(const PointF &size)
	{
		return PointB{ !m_bWordWrap && ntl::IsGreater<float>(m_sTextSize.X, size.X), ntl::IsGreater<float>(m_sTextSize.Y, size.Y) };
	}

	PointF CBuiltInTextArea::getTextSize()
	{
		return m_sTextSize;
	}

	PointF CBuiltInTextArea::getXScrollRange()
	{
		if (m_bWordWrap)
			return PointF{ 0, 0 };
		switch (m_eAlign)
		{
		case TextAlign::Right:
			return PointF{ 0, ntl::Max<float>(0.0f, m_sTextSize.X - getWidth()) };
		case TextAlign::Center:
			return PointF{ -ntl::Max<float>(0.0f, m_sTextSize.X - getWidth()) * 0.5f, ntl::Max<float>(0.0f, m_sTextSize.X - getWidth()) * 0.5f };
		default:
			return PointF{ -ntl::Max<float>(0.0f, m_sTextSize.X - getWidth()), 0 };
		}
	}

	PointF CBuiltInTextArea::getYScrollRange()
	{
		return PointF{ -ntl::Max<float>(0.0f, m_sTextSize.Y - getHeight()), 0 };
	}

	bool CBuiltInTextArea::isWordWrap()
	{
		return m_bWordWrap;
	}

	bool CBuiltInTextArea::isWordBreak()
	{
		return m_bWordBreak;
	}

	bool CBuiltInTextArea::isMoving()
	{
		return m_bMouseDown && m_bMoveSelection;
	}

	int CBuiltInTextArea::getLineCount()
	{
		return (int)m_aLines.size();
	}

	String CBuiltInTextArea::getLine(const int index)
	{
		if (index >= 0 && index < (int)m_aLines.size())
			return m_aLines[index].Text;
		return L"";
	}
#pragma endregion

#pragma region Getters
	bool CBuiltInTextArea::isReadOnly() const
	{
		return m_bReadOnly;
	}

	bool CBuiltInTextArea::isReplacing() const
	{
		return m_bReplacing;
	}

	bool CBuiltInTextArea::isHovered() const
	{
		return m_bHovered;
	}

	float CBuiltInTextArea::getScrollInterval() const
	{
		return m_fScrollInterval;
	}

	CBuiltInTextArea::State CBuiltInTextArea::getState()
	{
		if (!isEnabled())
			return State::Disabled;
		if (isFocused())
		{
			if (m_bHovered)
				return State::FocusedHovered;
			return State::Focused;
		}
		if (m_bHovered)
			return State::Hovered;
		return State::Normal;
	}

	Color CBuiltInTextArea::getTextColor(const State state) const
	{
		return m_aTextColor[(int)state];
	}

	Color CBuiltInTextArea::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state];
	}

	Color CBuiltInTextArea::getSelectionBackgroundColor(const State state) const
	{
		return m_aSelectionBackgroundColor[(int)state];
	}

	Color CBuiltInTextArea::getSelectionTextColor(const State state) const
	{
		return m_aSelectionTextColor[(int)state];
	}

	Color CBuiltInTextArea::getSelectionShadowColor(const State state) const
	{
		return m_aSelectionShadowColor[(int)state];
	}

	PointF CBuiltInTextArea::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state];
	}

	int CBuiltInTextArea::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state];
	}

	bool CBuiltInTextArea::isCopyByMouseEnabled() const
	{
		return m_bCopyByMouseEnabled;
	}

	bool CBuiltInTextArea::isMoveByMouseEnabled() const
	{
		return m_bMoveByMouseEnabled;
	}

	bool CBuiltInTextArea::isSelectWordByDoubleClickEnabled() const
	{
		return m_bSelectWordByDoubleClickEnabled;
	}

	bool CBuiltInTextArea::isKeyLeftEnabled() const
	{
		return m_bKeyLeftEnabled;
	}

	bool CBuiltInTextArea::isKeyRightEnabled() const
	{
		return m_bKeyRightEnabled;
	}

	bool CBuiltInTextArea::isKeyHomeEnabled() const
	{
		return m_bKeyHomeEnabled;
	}

	bool CBuiltInTextArea::isKeyEndEnabled() const
	{
		return m_bKeyEndEnabled;
	}

	bool CBuiltInTextArea::isKeyDeleteEnabled() const
	{
		return m_bKeyDeleteEnabled;
	}

	bool CBuiltInTextArea::isKeyBackspaceEnabled() const
	{
		return m_bKeyBackspaceEnabled;
	}

	bool CBuiltInTextArea::isKeyUpEnabled() const
	{
		return m_bKeyUpEnabled;
	}

	bool CBuiltInTextArea::isKeyDownEnabled() const
	{
		return m_bKeyDownEnabled;
	}

	bool CBuiltInTextArea::isKeyPageUpEnabled() const
	{
		return m_bKeyPageUpEnabled;
	}

	bool CBuiltInTextArea::isKeyPageDownEnabled() const
	{
		return m_bKeyPageDownEnabled;
	}

	bool CBuiltInTextArea::isSelectAllByKeyEnabled() const
	{
		return m_bSelectAllByKeyEnabled;
	}

	bool CBuiltInTextArea::isPasteByKeyEnabled() const
	{
		return m_bPasteByKeyEnabled;
	}

	bool CBuiltInTextArea::isCopyByKeyEnabled() const
	{
		return m_bCopyByKeyEnabled;
	}

	bool CBuiltInTextArea::isCutByKeyEnabled() const
	{
		return m_bCutByKeyEnabled;
	}

	bool CBuiltInTextArea::isHistoryByKeyEnabled() const
	{
		return m_bHistoryByKeyEnabled;
	}

	bool CBuiltInTextArea::isInsertReplaceChangeByKeyEnabled() const
	{
		return m_bInsertReplaceChangeByKeyEnabled;
	}

	bool CBuiltInTextArea::isWordWrapChangeByKeyEnabled() const
	{
		return m_bWordWrapChangeByKeyEnabled;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInTextArea::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInTextArea::setFocused(const bool value)
	{
		if (CBuiltInControl::setFocused(value && isEnabled()))
		{
			if (isFocused())
			{
				if (getControl() && getControl()->getForm() && getControl()->getForm()->getCaret())
				{
					getControl()->getForm()->getCaret()->setListener(&m_cCaretListener);
					getControl()->getForm()->getCaret()->setVisible(true);
				}
			}
			else if (getControl() && getControl()->getForm() && getControl()->getForm()->getCaret())
				getControl()->getForm()->getCaret()->setVisible(false);
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setEnabled(const bool value)
	{
		if (CBuiltInControl::setEnabled(value))
		{
			if (!isEnabled())
				setFocused(false);
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSize(const PointF &value)
	{
		if (CBuiltInControl::setSize(value))
		{
			if (m_bWordWrap)
				Update();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setDPI(const Point &value)
	{
		Point old{ getDPI() };
		if (CBuiltInControl::setDPI(value))
		{
			PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
			float avg{ (s.X + s.Y) * 0.5f };
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				m_aShadowShift[i] *= s;
				m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
			}
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInTextArea setters
	bool CBuiltInTextArea::setText(String value)
	{
		ReplaceAllDirect(value, L"\r\n", L"\n");
		ReplaceAllDirect(value, L"\r", L"\n");
		if (value == m_sText)
			return false;
		if (m_iMaxLength > 0 && (int)value.length() > m_iMaxLength)
		{
			String s{ value.substr(0, m_iMaxLength) };
			if (s == m_sText)
				return false;
			m_sText = s;
		}
		else
			m_sText = value;
		Update();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextArea::setSelection(const Point &value)
	{
		if (value.X < 0 || value.Y < 0 || value.X > (int)m_sText.length() || value.Y > (int)m_sText.length())
			return false;
		Point selection{ RealCaretToFake(value.X), RealCaretToFake(value.Y) };
		if (selection == m_sSelection)
			return false;
		if (m_sSelection.X == m_sSelection.Y && value.X == value.Y)
		{
			m_sSelection = selection;
			return false;
		}
		m_sSelection = selection;
		StoreHistory();
		return true;
	}

	bool CBuiltInTextArea::setCaretPosition(const int value)
	{
		if (value < 0 || value > (int)m_sText.length())
			return false;
		int caret{ RealCaretToFake(value) };
		if (caret == m_iCaretPosition)
			return false;
		m_iCaretPosition = caret;
		StoreHistory();
		return true;
	}

	bool CBuiltInTextArea::setScroll(const PointF &value)
	{
		if (IsNotEqual(value, m_sScroll))
		{
			m_sScroll = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setMaxLength(const int value)
	{
		if (value < 0 || value == m_iMaxLength)
			return false;
		m_iMaxLength = value;
		float line_height, space_width;
		IPlatformFont *pf{ getPlatformFont(line_height, space_width) };
		if (ApplyLengthLimit(pf, space_width, (getControl() && getControl()->getFont()) ? getControl()->getFont()->Distance : 0, getWidth()))
		{
			HelperUpdateVars(line_height, space_width, getWidth());
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setUndoLimitCount(const int value)
	{
		if (value < 0 || value == (int)m_cHistory.getLimitCount())
			return false;
		return m_cHistory.setLimitCount(value);
	}

	bool CBuiltInTextArea::setUndoLimitSize(const int value)
	{
		if (value < 0 || value == (int)m_cHistory.getLimitSize())
			return false;
		return m_cHistory.setLimitSize(value);
	}

	bool CBuiltInTextArea::setAlign(const TextAlign value)
	{
		if (value != m_eAlign)
		{
			m_eAlign = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setWordWrap(const bool value)
	{
		if (value != m_bWordWrap)
		{
			m_bWordWrap = value;
			Update();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setWordBreak(const bool value)
	{
		if (value != m_bWordBreak)
		{
			m_bWordBreak = value;
			if (m_bWordWrap)
				Update();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setLine(const int index, const String &value)
	{
		String s{ ReplaceAll(value, L"\r\n", L"\n") };
		ReplaceAllDirect(s, L"\r", L"\n");
		if (index >= 0 && index < (int)m_aLines.size() && s != m_aLines[index].Text)
		{
			m_sSelection.X = CaretPositionToCaret({ index, 0, 0 });
			m_sSelection.Y = CaretPositionToCaret({ index, (int)m_aLines[index].FakeLines.size() - 1, (int)m_aLines[index].FakeLines[m_aLines[index].FakeLines.size() - 1].length() });
			return HelperInsert(s);
		}
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInTextArea::setReadOnly(const bool value)
	{
		if (value != m_bReadOnly)
		{
			m_bReadOnly = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setReplacing(const bool value)
	{
		if (value != m_bReplacing)
		{
			m_bReplacing = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setScrollInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
		{
			m_fScrollInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setTextColor(const State state, const Color &value)
	{
		if (value != m_aTextColor[(int)state])
		{
			m_aTextColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state])
		{
			m_aShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSelectionBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aSelectionBackgroundColor[(int)state])
		{
			m_aSelectionBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSelectionTextColor(const State state, const Color &value)
	{
		if (value != m_aSelectionTextColor[(int)state])
		{
			m_aSelectionTextColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSelectionShadowColor(const State state, const Color &value)
	{
		if (value != m_aSelectionShadowColor[(int)state])
		{
			m_aSelectionShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state]))
		{
			m_aShadowShift[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setShadowRadius(const State state, const int value)
	{
		if (value >= 1 && value != m_aShadowRadius[(int)state])
		{
			m_aShadowRadius[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setCopyByMouseEnabled(const bool value)
	{
		if (value != m_bCopyByMouseEnabled)
		{
			m_bCopyByMouseEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setMoveByMouseEnabled(const bool value)
	{
		if (value != m_bMoveByMouseEnabled)
		{
			m_bMoveByMouseEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSelectWordByDoubleClickEnabled(const bool value)
	{
		if (value != m_bSelectWordByDoubleClickEnabled)
		{
			m_bSelectWordByDoubleClickEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyLeftEnabled(const bool value)
	{
		if (value != m_bKeyLeftEnabled)
		{
			m_bKeyLeftEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyRightEnabled(const bool value)
	{
		if (value != m_bKeyRightEnabled)
		{
			m_bKeyRightEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyHomeEnabled(const bool value)
	{
		if (value != m_bKeyHomeEnabled)
		{
			m_bKeyHomeEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyEndEnabled(const bool value)
	{
		if (value != m_bKeyEndEnabled)
		{
			m_bKeyEndEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyDeleteEnabled(const bool value)
	{
		if (value != m_bKeyDeleteEnabled)
		{
			m_bKeyDeleteEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyBackspaceEnabled(const bool value)
	{
		if (value != m_bKeyBackspaceEnabled)
		{
			m_bKeyBackspaceEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyUpEnabled(const bool value)
	{
		if (value != m_bKeyUpEnabled)
		{
			m_bKeyUpEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyDownEnabled(const bool value)
	{
		if (value != m_bKeyDownEnabled)
		{
			m_bKeyDownEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyPageUpEnabled(const bool value)
	{
		if (value != m_bKeyPageUpEnabled)
		{
			m_bKeyPageUpEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setKeyPageDownEnabled(const bool value)
	{
		if (value != m_bKeyPageDownEnabled)
		{
			m_bKeyPageDownEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setSelectAllByKeyEnabled(const bool value)
	{
		if (value != m_bSelectAllByKeyEnabled)
		{
			m_bSelectAllByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setPasteByKeyEnabled(const bool value)
	{
		if (value != m_bPasteByKeyEnabled)
		{
			m_bPasteByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setCopyByKeyEnabled(const bool value)
	{
		if (value != m_bCopyByKeyEnabled)
		{
			m_bCopyByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setCutByKeyEnabled(const bool value)
	{
		if (value != m_bCutByKeyEnabled)
		{
			m_bCutByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setHistoryByKeyEnabled(const bool value)
	{
		if (value != m_bHistoryByKeyEnabled)
		{
			m_bHistoryByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setInsertReplaceChangeByKeyEnabled(const bool value)
	{
		if (value != m_bInsertReplaceChangeByKeyEnabled)
		{
			m_bInsertReplaceChangeByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::setWordWrapChangeByKeyEnabled(const bool value)
	{
		if (value != m_bWordWrapChangeByKeyEnabled)
		{
			m_bWordWrapChangeByKeyEnabled = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CBuiltInTextArea::UpdateFromStyle(IStyle *style, const String &class_name)
	{
		style->getOption(class_name + L".ScrollInterval", m_fScrollInterval);
		for (int i = 0; i <= (int)State::Disabled; i++)
		{
			String state;
			switch ((State)i)
			{
			case State::Hovered:
				state = L"Hovered";
				break;
			case State::Focused:
				state = L"Focused";
				break;
			case State::FocusedHovered:
				state = L"FocusedHovered";
				break;
			case State::Disabled:
				state = L"Disabled";
				break;
			default:
				state = L"Normal";
			}
			style->getOption(class_name + L".TextColor[" + state + L"]", m_aTextColor[i]);
			style->getOption(class_name + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
			style->getOption(class_name + L".SelectionBackgroundColor[" + state + L"]", m_aSelectionBackgroundColor[i]);
			style->getOption(class_name + L".SelectionTextColor[" + state + L"]", m_aSelectionTextColor[i]);
			style->getOption(class_name + L".SelectionShadowColor[" + state + L"]", m_aSelectionShadowColor[i]);
			style->getOption(class_name + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
			style->getOption(class_name + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
		}
	}

	void CBuiltInTextArea::Update()
	{
		IPlatformFont *pf;
		float line_height, space_width;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			m_sTextSize.X = 0;
			m_iMaxCaretPosition = 0;
			float distance{ getControl()->getFont()->Distance }, control_width{ getWidth() };
			BuildLines(m_sText, m_aLines);
			for (auto &line : m_aLines)
				BuildFakeLines(line, pf, distance, control_width, space_width);
			HelperUpdateVars(line_height, space_width, control_width);
		}
	}
#pragma endregion

#pragma region IBuiltInTextArea helpers
	bool CBuiltInTextArea::DeleteSelection()
	{
		float line_height, space_width;
		IPlatformFont *pf{ getPlatformFont(line_height, space_width) };
		if (DeleteSelectionInternal(pf, (getControl() && getControl()->getFont()) ? getControl()->getFont()->Distance : 0, getWidth(), space_width, line_height))
		{
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteCharBeforeCaret()
	{
		if (m_sSelection.X == m_sSelection.Y)
		{
			m_sSelection.X = ntl::Max<int>(0, m_iCaretPosition - 1);
			m_sSelection.Y = m_iCaretPosition;
		}
		float line_height, space_width;
		IPlatformFont *pf{ getPlatformFont(line_height, space_width) };
		if (DeleteSelectionInternal(pf, (getControl() && getControl()->getFont()) ? getControl()->getFont()->Distance : 0, getWidth(), space_width, line_height))
		{
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteCharAfterCaret()
	{
		if (m_sSelection.X == m_sSelection.Y)
		{
			m_sSelection.X = m_iCaretPosition;
			m_sSelection.Y = ntl::Min<int>(m_iMaxCaretPosition, m_iCaretPosition + 1);
		}
		float line_height, space_width;
		IPlatformFont *pf{ getPlatformFont(line_height, space_width) };
		if (DeleteSelectionInternal(pf, (getControl() && getControl()->getFont()) ? getControl()->getFont()->Distance : 0, getWidth(), space_width, line_height))
		{
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteWordBeforeCaret()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			if (m_iCaretPosition > 0 && m_sSelection.X == m_sSelection.Y)
			{
				int caret_real{ FakeCaretToReal(m_iCaretPosition) }, prev_word_real{ (int)SearchPrevWord(m_sText, caret_real) };
				if (prev_word_real < caret_real)
				{
					m_sSelection.X = RealCaretToFake(prev_word_real);
					m_sSelection.Y = m_iCaretPosition;
				}
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteWordAfterCaret()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			if (m_iCaretPosition < m_iMaxCaretPosition && m_sSelection.X == m_sSelection.Y)
			{
				int caret_real{ FakeCaretToReal(m_iCaretPosition) }, next_word_real{ (int)SearchNextWord(m_sText, caret_real) };
				if (next_word_real > caret_real)
				{
					m_sSelection.X = m_iCaretPosition;
					m_sSelection.Y = next_word_real;
				}
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteToLineStart()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition position{ FindCaretPosition(m_iCaretPosition) };
			if (position.Index > 0 && m_sSelection.X == m_sSelection.Y)
			{
				m_sSelection.X = CaretPositionToCaret({ position.LineIndex, position.FakeLineIndex, 0 });
				m_sSelection.Y = m_iCaretPosition;
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteToLineEnd()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition position{ FindCaretPosition(m_iCaretPosition) };
			if (position.Index < (int)m_aLines[position.LineIndex].FakeLines[position.FakeLineIndex].length() && m_sSelection.X == m_sSelection.Y)
			{
				m_sSelection.X = m_iCaretPosition;
				m_sSelection.Y = CaretPositionToCaret({ position.LineIndex, position.FakeLineIndex, (int)m_aLines[position.LineIndex].FakeLines[position.FakeLineIndex].length() });
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteAllBeforeCaret()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			if (m_iCaretPosition > 0 && m_sSelection.X == m_sSelection.Y)
			{
				m_sSelection.X = 0;
				m_sSelection.Y = m_iCaretPosition;
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::DeleteAllAfterCaret()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			if (m_iCaretPosition < m_iMaxCaretPosition && m_sSelection.X == m_sSelection.Y)
			{
				m_sSelection.X = m_iCaretPosition;
				m_sSelection.Y = m_iMaxCaretPosition;
			}
			if (DeleteSelectionInternal(pf, getControl()->getFont()->Distance, getWidth(), space_width, line_height))
			{
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretLeft(const bool select)
	{
		if (select && m_iCaretPosition > 0)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition--;
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition > 0 || m_sSelection.X != m_sSelection.Y))
		{
			if (m_iCaretPosition > 0)
				m_iCaretPosition--;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretRight(const bool select)
	{
		if (select && m_iCaretPosition < m_iMaxCaretPosition)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition++;
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition < m_iMaxCaretPosition || m_sSelection.X != m_sSelection.Y))
		{
			if (m_iCaretPosition < m_iMaxCaretPosition)
				m_iCaretPosition++;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretWordLeft(const bool select)
	{
		if (select && m_iCaretPosition > 0)
		{
			int caret_real{ FakeCaretToReal(m_iCaretPosition) }, prev_word_real{ (int)SearchPrevWord(m_sText, caret_real) };
			if (prev_word_real < caret_real)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_iCaretPosition = RealCaretToFake(prev_word_real);
				m_sSelection.Y = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		if (!select && (m_iCaretPosition > 0 || m_sSelection.X != m_sSelection.Y))
		{
			int caret_real{ FakeCaretToReal(m_iCaretPosition) }, prev_word_real{ (int)SearchPrevWord(m_sText, caret_real) };
			if (prev_word_real < caret_real)
			{
				m_iCaretPosition = RealCaretToFake(prev_word_real);
				m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretWordRight(const bool select)
	{
		if (select && m_iCaretPosition < m_iMaxCaretPosition)
		{
			int caret_real{ FakeCaretToReal(m_iCaretPosition) }, next_word_real{ (int)SearchNextWord(m_sText, caret_real) };
			if (next_word_real > caret_real)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_iCaretPosition = ntl::Clamp<int>(RealCaretToFake(next_word_real), 0, m_iMaxCaretPosition);
				m_sSelection.Y = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		if (!select && (m_iCaretPosition < m_iMaxCaretPosition || m_sSelection.X != m_sSelection.Y))
		{
			int caret_real{ FakeCaretToReal(m_iCaretPosition) }, next_word_real{ (int)SearchNextWord(m_sText, caret_real) };
			if (next_word_real > caret_real)
			{
				m_iCaretPosition = ntl::Clamp<int>(RealCaretToFake(next_word_real), 0, m_iMaxCaretPosition);
				m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretLineStart(const bool select)
	{
		CaretPosition p{ FindCaretPosition(m_iCaretPosition) };
		int new_pos{ m_iCaretPosition - p.Index };
		if (select && (new_pos != m_iCaretPosition || m_sSelection.Y != new_pos))
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_sSelection.Y = new_pos;
			m_iCaretPosition = new_pos;
			StoreHistory();
			return true;
		}
		if (!select && (new_pos != m_iCaretPosition || m_sSelection.X != m_sSelection.Y))
		{
			m_iCaretPosition = new_pos;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretLineEnd(const bool select)
	{
		CaretPosition p{ FindCaretPosition(m_iCaretPosition) };
		int new_pos{ ntl::Min<int>(m_iMaxCaretPosition, m_iCaretPosition + (int)m_aLines[p.LineIndex].FakeLines[p.FakeLineIndex].length() - p.Index) };
		if (select && (new_pos != m_iCaretPosition || m_sSelection.Y != new_pos))
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_sSelection.Y = new_pos;
			m_iCaretPosition = new_pos;
			StoreHistory();
			return true;
		}
		if (!select && (new_pos != m_iCaretPosition || m_sSelection.X != m_sSelection.Y))
		{
			m_iCaretPosition = new_pos;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretLineUp(const bool select)
	{
		CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
		if (current.LineIndex == 0 && current.FakeLineIndex == 0)
			return false;
		int line_index, fake_line_index;
		if (current.FakeLineIndex == 0)
		{
			line_index = current.LineIndex - 1;
			fake_line_index = (int)m_aLines[line_index].FakeLines.size() - 1;
		}
		else
		{
			line_index = current.LineIndex;
			fake_line_index = current.FakeLineIndex - 1;
		}
		int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
		if (select && new_pos != m_iCaretPosition)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_sSelection.Y = new_pos;
			m_iCaretPosition = new_pos;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
		{
			m_iCaretPosition = new_pos;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretLineDown(const bool select)
	{
		CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
		if (current.LineIndex == (int)m_aLines.size() - 1 && current.FakeLineIndex == (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1)
			return false;
		int line_index, fake_line_index;
		if (current.FakeLineIndex == (int)m_aLines[current.LineIndex].FakeLines.size() - 1)
		{
			line_index = current.LineIndex + 1;
			fake_line_index = 0;
		}
		else
		{
			line_index = current.LineIndex;
			fake_line_index = current.FakeLineIndex + 1;
		}
		int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
		if (select && new_pos != m_iCaretPosition)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_sSelection.Y = new_pos;
			m_iCaretPosition = new_pos;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
		{
			m_iCaretPosition = new_pos;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretPageStart(const bool select)
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
			if (current.LineIndex == 0 && current.FakeLineIndex == 0)
				return false;
			float y{ m_sScroll.Y };
			int line_index{ 0 }, fake_line_index{ 0 };
			bool found{ false };
			for (auto &line : m_aLines)
			{
				if (ntl::IsGreaterOrEqual<float>(y + (float)line.FakeLines.size() * line_height, line_height))
				{
					fake_line_index = 0;
					for (auto fake_line = line.FakeLines.begin(); fake_line != line.FakeLines.end(); fake_line++)
					{
						if (ntl::IsGreaterOrEqual<float>(y, 0))
						{
							found = true;
							break;
						}
						y += line_height;
						fake_line_index++;
					}
					break;
				}
				y += (float)line.FakeLines.size() * line_height;
				line_index++;
				if (ntl::IsGreaterOrEqual<float>(y, getHeight()))
					break;
			}
			if (found)
			{
				int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
				// Change caret position and/or selection
				if (select && new_pos != m_iCaretPosition)
				{
					if (m_sSelection.X == m_sSelection.Y)
						m_sSelection.X = m_iCaretPosition;
					m_sSelection.Y = new_pos;
					m_iCaretPosition = new_pos;
					StoreHistory();
					return true;
				}
				if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
				{
					m_iCaretPosition = new_pos;
					m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
					StoreHistory();
					return true;
				}
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretPageEnd(const bool select)
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
			if (current.LineIndex == (int)m_aLines.size() - 1 && current.FakeLineIndex == (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1)
				return false;
			float y{ m_sScroll.Y }, h{ getHeight() };
			int line_index{ (int)m_aLines.size() - 1 }, fake_line_index{ (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1 };
			for (auto line : m_aLines)
				y += (float)line.FakeLines.size() * line_height;
			bool found{ false };
			for (auto line = m_aLines.rbegin(); line != m_aLines.rend(); line++)
			{
				if (ntl::IsLessOrEqual<float>(y, h))
				{
					fake_line_index = (int)line->FakeLines.size() - 1;
					for (auto fake_line = line->FakeLines.rbegin(); fake_line != line->FakeLines.rend(); fake_line++)
					{
						if (ntl::IsLessOrEqual<float>(y, h))
						{
							found = true;
							break;
						}
						y -= line_height;
						fake_line_index--;
					}
					break;
				}
				y -= (float)line->FakeLines.size() * line_height;
				line_index--;
				if (ntl::IsLess<float>(y + (float)line->FakeLines.size() * line_height, 0))
					break;
			}
			if (found)
			{
				int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
				// Change caret position and/or selection
				if (select && new_pos != m_iCaretPosition)
				{
					if (m_sSelection.X == m_sSelection.Y)
						m_sSelection.X = m_iCaretPosition;
					m_sSelection.Y = new_pos;
					m_iCaretPosition = new_pos;
					StoreHistory();
					return true;
				}
				if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
				{
					m_iCaretPosition = new_pos;
					m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
					StoreHistory();
					return true;
				}
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretPageUp(const bool select)
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
			if (current.LineIndex == 0 && current.FakeLineIndex == 0)
				return false;
			int line_index{ current.LineIndex }, fake_line_index{ current.FakeLineIndex }, lines{ ntl::Max<int>(1, int(getHeight() / line_height)) };
			while (lines > 0)
			{
				if (line_index == 0 && fake_line_index == 0)
					break;
				lines--;
				fake_line_index--;
				if (fake_line_index < 0)
				{
					line_index--;
					fake_line_index = (int)m_aLines[line_index].FakeLines.size() - 1;
				}
			}
			int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
			// Change caret position and/or selection
			if (select && new_pos != m_iCaretPosition)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_sSelection.Y = new_pos;
				m_iCaretPosition = new_pos;
				StoreHistory();
				return true;
			}
			if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
			{
				m_iCaretPosition = new_pos;
				m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretPageDown(const bool select)
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			CaretPosition current{ FindCaretPosition(m_iCaretPosition) };
			if (current.LineIndex == (int)m_aLines.size() - 1 && current.FakeLineIndex == (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1)
				return false;
			int line_index{ current.LineIndex }, fake_line_index{ current.FakeLineIndex }, lines{ ntl::Max<int>(1, int(getHeight() / line_height)) };
			while (lines > 0)
			{
				if (line_index == (int)m_aLines.size() - 1 && fake_line_index == (int)m_aLines[m_aLines.size() - 1].FakeLines.size() - 1)
					break;
				lines--;
				fake_line_index++;
				if (fake_line_index >= (int)m_aLines[line_index].FakeLines.size())
				{
					line_index++;
					fake_line_index = 0;
				}
			}
			int new_pos{ FindBestPosition(current, line_index, fake_line_index) };
			// Change caret position and/or selection
			if (select && new_pos != m_iCaretPosition)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_sSelection.Y = new_pos;
				m_iCaretPosition = new_pos;
				StoreHistory();
				return true;
			}
			if (!select && (m_iCaretPosition != new_pos || m_sSelection.Y != m_sSelection.X))
			{
				m_iCaretPosition = new_pos;
				m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretStart(const bool select)
	{
		if (select && m_iCaretPosition > 0)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition = 0;
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition > 0 || m_sSelection.X != m_sSelection.Y))
		{
			m_iCaretPosition = 0;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::MoveCaretEnd(const bool select)
	{
		if (select && m_iCaretPosition < m_iMaxCaretPosition)
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition = m_iMaxCaretPosition;
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition < m_iMaxCaretPosition || m_sSelection.X != m_sSelection.Y))
		{
			m_iCaretPosition = m_iMaxCaretPosition;
			m_sSelection.Y = m_sSelection.X = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::Undo(bool &text_changed)
	{
		if (m_cHistory.getPosition() == 0)
			return false;
		History h{ m_cHistory.getItem(m_cHistory.getPosition() - 1) };
		m_sSelection = h.Selection;
		m_iCaretPosition = h.CaretPosition;
		if (m_sText != h.Text)
		{
			m_sText = h.Text;
			text_changed = true;
			Update();
		}
		m_cHistory.setPosition(m_cHistory.getPosition() - 1);
		return true;
	}

	bool CBuiltInTextArea::Redo(bool &text_changed)
	{
		if (m_cHistory.getPosition() >= m_cHistory.getCount() - 1)
			return false;
		History h{ m_cHistory.getItem(m_cHistory.getPosition() + 1) };
		m_sSelection = h.Selection;
		m_iCaretPosition = h.CaretPosition;
		if (m_sText != h.Text)
		{
			m_sText = h.Text;
			text_changed = true;
			Update();
		}
		m_cHistory.setPosition(m_cHistory.getPosition() + 1);
		return true;
	}

	bool CBuiltInTextArea::Insert(const wchar_t chr)
	{
		String s{ chr };
		return HelperInsert(s);
	}

	bool CBuiltInTextArea::Insert(String str)
	{
		return HelperInsert(str);
	}

	bool CBuiltInTextArea::Replace(const wchar_t chr)
	{
		if (m_sSelection.X == m_sSelection.Y)
		{
			m_sSelection.X = m_sSelection.Y = m_iCaretPosition;
			if (m_iCaretPosition < m_iMaxCaretPosition)
				m_sSelection.Y++;
		}
		String s{ chr };
		return HelperInsert(s);
	}

	bool CBuiltInTextArea::Replace(String str)
	{
		return HelperInsert(str);
	}

	bool CBuiltInTextArea::MoveSelection(const int dst_caret_pos)
	{
		Point selection{ NormalizeSelection() };
		if (selection.X == selection.Y || dst_caret_pos < 0 || dst_caret_pos > m_iMaxCaretPosition || (dst_caret_pos >= selection.X && dst_caret_pos < selection.Y))
			return false;
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			String s{ getSelectedText() };
			return HelperInsert(s);
		}
		return false;
	}

	bool CBuiltInTextArea::CopySelection(const int dst_caret_pos)
	{
		Point selection{ NormalizeSelection() };
		if (selection.X == selection.Y || dst_caret_pos < 0 || dst_caret_pos > m_iMaxCaretPosition || (dst_caret_pos >= selection.X && dst_caret_pos < selection.Y))
			return false;
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			String s{ getSelectedText() };
			m_sSelection.Y = m_sSelection.X;
			return HelperInsert(s);
		}
		return false;
	}

	bool CBuiltInTextArea::ScrollToCaret()
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			PointF pos{ CaretToClient(m_iCaretPosition, pf, line_height, space_width) };
			bool result{ false };
			if (ntl::IsGreater<float>(pos.X + space_width, getWidth()))
			{
				m_sScroll.X -= pos.X + space_width - getWidth();
				result = true;
			}
			if (ntl::IsLess<float>(pos.X, 0))
			{
				m_sScroll.X -= pos.X;
				result = true;
			}
			if (ntl::IsGreater<float>(pos.Y + line_height, getHeight()))
			{
				m_sScroll.Y -= pos.Y + line_height - getHeight();
				result = true;
			}
			if (ntl::IsLess<float>(pos.Y, 0))
			{
				m_sScroll.Y -= pos.Y;
				result = true;
			}
			return result;
		}
		return false;
	}

	bool CBuiltInTextArea::ScrollLineUp()
	{
		if (m_sScroll.Y < 0)
		{
			float line_height, space_width;
			IPlatformFont *pf;
			if ((pf = getPlatformFont(line_height, space_width)))
			{
				m_sScroll.Y = ntl::Min<float>(0.0f, m_sScroll.Y + line_height);
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::ScrollLineDown()
	{
		float min_scroll{ getYScrollRange().X };
		if (ntl::IsGreater<float>(m_sScroll.Y, min_scroll))
		{
			float line_height, space_width;
			IPlatformFont *pf;
			if ((pf = getPlatformFont(line_height, space_width)))
			{
				m_sScroll.Y = ntl::Max<float>(min_scroll, m_sScroll.Y - line_height);
				return true;
			}
		}
		return false;
	}

	bool CBuiltInTextArea::Copy()
	{
		String text{ getSelectedText() };
		if (!text.empty() && getControl()->getForm())
			return getControl()->getForm()->CopyStringToClipboard(text);
		return false;
	}

	bool CBuiltInTextArea::Cut()
	{
		String text{ getSelectedText() };
		float line_height, space_width;
		IPlatformFont *pf{ getPlatformFont(line_height, space_width) };
		if (!text.empty() && DeleteSelectionInternal(pf, pf ? getControl()->getFont()->Distance : 0, getWidth(), space_width, line_height))
		{
			ScrollToCaret();
			if (getControl()->getForm())
				getControl()->getForm()->CopyStringToClipboard(text);
			return true;
		}
		return false;
	}

	bool CBuiltInTextArea::Paste()
	{
		if (getControl()->getForm())
			return getControl()->getForm()->CopyStringFromClipboard();
		return false;
	}

	bool CBuiltInTextArea::SelectAll()
	{
		return setSelection(Point{ 0, (int)m_sText.length() });
	}

	bool CBuiltInTextArea::DeselectAll()
	{
		return setSelection(Point{ 0, 0 });
	}

	bool CBuiltInTextArea::AddLine(const String &text)
	{
		if (text.empty())
			return false;
		m_iCaretPosition = m_iMaxCaretPosition;
		m_sSelection.Y = m_sSelection.X;
		return HelperInsert(m_sText.empty() ? text : (L"\n" + text));
	}

	bool CBuiltInTextArea::DeleteLine(const int index)
	{
		if (index >= 0 && index < (int)m_aLines.size())
		{
			m_sSelection.X = CaretPositionToCaret(CaretPosition{ index, 0, 0 });
			m_sSelection.Y = CaretPositionToCaret(CaretPosition{ index, (int)m_aLines[index].FakeLines.size() - 1, (int)m_aLines[index].FakeLines[m_aLines[index].FakeLines.size() - 1].length() + 1 });
			if (m_sSelection.X > 0 && index == (int)m_aLines.size() - 1)
				m_sSelection.X--;
			return DeleteSelection();
		}
		return false;
	}
#pragma endregion

#pragma region Helpers
	IPlatformFont *CBuiltInTextArea::getPlatformFont(float &line_height, float &space_width)
	{
		if (getControl() && getControl()->getForm() && getControl()->getFont() && getControl()->getForm()->getRenderer())
		{
			IPlatformFont *pf{ getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()) };
			if (pf)
			{
				line_height = pf->getStringSize(L"Wy", 0).Y;
				space_width = pf->getStringSize(L" ", 0).X;
			}
			return pf;
		}
		return nullptr;
	}

	void CBuiltInTextArea::BuildLines(const String &text, Lines &lines)
	{
		lines.clear();
		String::size_type offset{ 0 }, pos;
		while ((pos = text.find(L'\n', offset)) != String::npos)
		{
			lines.push_back({ text.substr(offset, pos - offset) });
			offset = pos + 1;
		}
		if (offset < text.length() || text.empty()) // Second conditions is required when text is empty because fake lines should never be empty
			lines.push_back({ text.substr(offset, text.length() - offset) });
	}

	void CBuiltInTextArea::BuildFakeLines(Line &line, IPlatformFont *pf, const float distance, const float control_width, const float space_width)
	{
		line.FakeLines.clear();
		line.Width = 0;
		if (m_bWordWrap)
		{
			String::size_type line_start{ 0 }, word_start{ 0 }, index{ 0 };
			float char_width, line_width{ 0 };
			String chr;
			bool is_prev_space{ true };
			while (index < line.Text.length())
			{
				char_width = pf->getStringSize(line.Text.substr(index, 1), 0).X;
				if (ntl::IsGreater<float>(line_width + char_width + space_width, control_width) && index > line_start) // Check out of controls width and at least one character was processed
				{
					if (m_bWordBreak || word_start == line_start) // If words could be broken or current word is too long
					{
						line.FakeLines.push_back(line.Text.substr(line_start, index - line_start));
						line.Width = ntl::Max<float>(line.Width, pf->getStringSize(line.FakeLines[line.FakeLines.size() - 1], distance).X);
						line_start = index;
						word_start = index;
						line_width = char_width;
						index++;
					}
					else // Break before word start
					{
						line.FakeLines.push_back(line.Text.substr(line_start, word_start - line_start));
						line.Width = ntl::Max<float>(line.Width, pf->getStringSize(line.FakeLines[line.FakeLines.size() - 1], distance).X);
						line_start = word_start;
						line_width = 0;
						index = word_start;
					}
					is_prev_space = true;
				}
				else
				{
					if (index > line_start)
					{
						bool is_space{ !std::isalnum(line.Text[index], std::locale()) };
						if (!is_space && is_prev_space)
							word_start = index;
						is_prev_space = is_space;
					}
					line_width += char_width;
					index++;
				}
			}
			if (line_start <= line.Text.length())
			{
				line.FakeLines.push_back(line.Text.substr(line_start, line.Text.length() - line_start));
				line.Width = ntl::Max<float>(line.Width, pf->getStringSize(line.FakeLines[line.FakeLines.size() - 1], distance).X);
			}
		}
		else
		{
			line.FakeLines.push_back(line.Text);
			line.Width = ntl::Max<float>(line.Width, pf->getStringSize(line.Text, distance).X);
		}
	}

	int CBuiltInTextArea::FakeCaretToReal(const int value) const
	{
		int real{ 0 }, fake{ 0 };
		for (auto &line : m_aLines)
		{
			int fake_max{ fake + (int)line.Text.length() + (int)line.FakeLines.size() }; // Find fake position of line end
			if (value < fake_max) // Check if required position is some where inside current line
			{
				for (auto &fake_line : line.FakeLines)
				{
					fake_max = fake + (int)fake_line.length();
					if (value <= fake_max)
					{
						real += value - fake;
						break;
					}
					fake = fake_max + 1;
					real += (int)fake_line.length();
				}
				break;
			}
			fake = fake_max;
			real += (int)line.Text.length() + 1;
		}
		return real;
	}

	int CBuiltInTextArea::RealCaretToFake(const int value) const
	{
		int fake{ 0 }, real{ 0 };
		for (auto &line : m_aLines)
		{
			int real_max{ real + (int)line.Text.length() + 1 };
			if (value < real_max)
			{
				for (auto &fake_line : line.FakeLines)
				{
					real_max = real + (int)fake_line.length();
					if (value < real_max)
					{
						fake += value - real;
						break;
					}
					real = real_max;
					fake += (int)fake_line.length() + 1;
				}
				break;
			}
			real = real_max;
			fake += (int)line.Text.length() + (int)line.FakeLines.size();
		}
		return fake;
	}

	CBuiltInTextArea::TextPosition CBuiltInTextArea::CalculateTextPosition(const int caret_fake, IPlatformFont *pf, const float distance, const float line_height, const float space_width)
	{
		CaretPosition cp{ FindCaretPosition(caret_fake) };
		TextPosition result;
		result.LineIndex = cp.LineIndex;
		result.FakeLineIndex = cp.FakeLineIndex;
		result.Index = cp.Index;
		result.Position = { 0, m_sScroll.Y };
		int line_index{ 0 };
		for (auto &line : m_aLines)
		{
			if (line_index == result.LineIndex)
			{
				switch (m_eAlign)
				{
				case TextAlign::Right:
					result.Position.X = getWidth() - pf->getStringSize(line.FakeLines[result.FakeLineIndex], distance).X - space_width + m_sScroll.X;
					break;
				case TextAlign::Center:
					result.Position.X = (getWidth() - pf->getStringSize(line.FakeLines[result.FakeLineIndex], distance).X - space_width) * 0.5f + m_sScroll.X;
				default:
					result.Position.X = m_sScroll.X;
				}
				result.Position.Y += (float)result.FakeLineIndex * line_height;
				break;
			}
			else
				result.Position.Y += (float)line.FakeLines.size() * line_height;
			line_index++;
		}
		return result;
	}

	PointF CBuiltInTextArea::CaretToClient(const int caret_fake, IPlatformFont *pf, const float line_height, const float space_width)
	{
		int caret{ ntl::Clamp<int>(m_iMaxCaretPosition, 0, caret_fake) };
		float distance{ getControl()->getFont()->Distance };
		TextPosition result{ CalculateTextPosition(caret, pf, distance, line_height, space_width) };
		if (m_sText.length() > 0)
			result.Position.X += pf->getStringSize(m_aLines[result.LineIndex].FakeLines[result.FakeLineIndex].substr(0, result.Index), distance).X;
		return result.Position;
	}

	CBuiltInTextArea::CaretPosition CBuiltInTextArea::FindCaretPosition(const int caret_fake)
	{
		int caret{ ntl::Clamp<int>(m_iMaxCaretPosition, 0, caret_fake) };
		CaretPosition result{ 0, 0, 0 };
		int fake{ 0 }, fake_max;
		for (auto line = m_aLines.begin(); line != m_aLines.end(); line++)
		{
			fake_max = fake + (int)line->Text.length() + (int)line->FakeLines.size();
			if (caret < fake_max)
			{
				for (auto fake_line = line->FakeLines.begin(); fake_line != line->FakeLines.end(); fake_line++)
				{
					fake_max = fake + (int)fake_line->length();
					if (caret <= fake_max)
					{
						result.FakeLineIndex = int(fake_line - line->FakeLines.begin());
						result.Index = caret - fake;
						break;
					}
					fake = fake_max + 1;
				}
				result.LineIndex = int(line - m_aLines.begin());
				break;
			}
			fake = fake_max;
		}
		return result;
	}

	bool CBuiltInTextArea::DeleteSelectionInternal(IPlatformFont *pf, const float distance, const float control_width, const float space_width, const float line_height)
	{
		int changed{ HelperDeleteSelection() };
		if (changed >= 0 && pf)
		{
			BuildFakeLines(m_aLines[changed], pf, distance, control_width, space_width);
			HelperUpdateVars(line_height, space_width, control_width);
			return true;
		}
		return false;
	}

	int CBuiltInTextArea::CaretPositionToCaret(const CaretPosition &position)
	{
		int result{ 0 }, line_index{ 0 }, fake_line_index{ 0 };
		for (auto &line : m_aLines)
		{
			if (line_index == position.LineIndex)
			{
				fake_line_index = 0;
				for (auto &fake_line : line.FakeLines)
				{
					if (fake_line_index == position.FakeLineIndex)
					{
						result += position.Index;
						break;
					}
					result += (int)fake_line.length() + 1;
					fake_line_index++;
				}
				break;
			}
			result += (int)line.Text.length() + (int)line.FakeLines.size();
			line_index++;
		}
		return result;
	}

	int CBuiltInTextArea::FindBestPosition(const CaretPosition &current, const int line_index, const int fake_line_index)
	{
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			float distance{ getControl()->getFont()->Distance };
			float width{ pf->getStringSize(m_aLines[current.LineIndex].FakeLines[current.FakeLineIndex].substr(0, current.Index), distance).X }, w{ 0 }, char_w;
			int index{ 0 };
			for (int i = 0; i < (int)m_aLines[line_index].FakeLines[fake_line_index].length(); i++)
			{
				char_w = pf->getStringSize(m_aLines[line_index].FakeLines[fake_line_index].substr(i, 1), distance).X;
				if (ntl::IsLess<float>(width - w, char_w * 0.5f))
					break;
				w += char_w + distance;
				index++;
			}
			return CaretPositionToCaret(CaretPosition{ line_index, fake_line_index, index });
		}
		return CaretPositionToCaret(CaretPosition{ line_index, fake_line_index, ntl::Clamp<int>(current.Index, 0, (int)m_aLines[line_index].FakeLines[fake_line_index].length()) });
	}

	int CBuiltInTextArea::ClientToCaret(const PointF value)
	{
		float line_height, space_width;
		int result{ 0 };
		bool after_end{ true };
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, max_y, text_x, char_w;
			int i, fake_line_index;
			for (auto &line : m_aLines)
			{
				if (ntl::IsLess<float>(value.Y, y))
				{
					after_end = false;
					break;
				}
				max_y = y + (float)line.FakeLines.size() * line_height;
				if (ntl::IsGreaterOrEqual<float>(value.Y, y) && ntl::IsLess<float>(value.Y, max_y))
				{
					fake_line_index = int((value.Y - y) / line_height);
					switch (m_eAlign)
					{
					case TextAlign::Right:
						text_x = getWidth() - pf->getStringSize(line.FakeLines[fake_line_index], distance).X - space_width + m_sScroll.X;
						break;
					case TextAlign::Center:
						text_x = (getWidth() - pf->getStringSize(line.FakeLines[fake_line_index], distance).X - space_width) * 0.5f + m_sScroll.X;
					default:
						text_x = m_sScroll.X;
					}
					for (i = 0; i < fake_line_index; i++)
						result += (int)line.FakeLines[i].length() + 1;
					if (ntl::IsGreater<float>(value.X, text_x))
					{
						for (i = 0; i < (int)line.FakeLines[fake_line_index].length(); i++)
						{
							char_w = pf->getStringSize(line.FakeLines[fake_line_index].substr(i, 1), distance).X;
							if (ntl::IsLess<float>(value.X - text_x, char_w * 0.5f))
								return result + i;
							text_x += char_w + distance;
						}
						return result + (int)line.FakeLines[fake_line_index].length();
					}
					return result;
				}
				y += (float)line.FakeLines.size() * line_height;
				result += (int)line.Text.length() + (int)line.FakeLines.size();
			}
		}
		if (after_end && result > 0)
			result--;
		return result;
	}

	int CBuiltInTextArea::HelperDeleteSelection()
	{
		if (m_sSelection.X == m_sSelection.Y)
			return -1;
		Point selection{ NormalizeSelection() };
		// Start line is the first one and second line is the last one. Require complete recalculation
		CaretPosition start{ FindCaretPosition(selection.X) }, end{ FindCaretPosition(selection.Y) };
		Point selection_real{ FakeCaretToReal(selection.X), FakeCaretToReal(selection.Y) };
		m_sText.erase(selection_real.X, selection_real.Y - selection_real.X);
		if (m_iCaretPosition > selection.X && m_iCaretPosition < selection.Y)
			m_iCaretPosition = selection.X;
		else if (m_iCaretPosition >= selection.Y)
			m_iCaretPosition -= selection.Y - selection.X;
		m_sSelection.Y = m_sSelection.X;
		// Update lines' texts
		int index_start{ start.Index }, index_end{ end.Index };
		for (int i = 0; i < start.FakeLineIndex; i++)
			index_start += (int)m_aLines[start.LineIndex].FakeLines[i].length();
		for (int i = 0; i < end.FakeLineIndex; i++)
			index_end += (int)m_aLines[end.LineIndex].FakeLines[i].length();
		if (start.LineIndex != end.LineIndex) // Delete from different lines
		{
			m_aLines[start.LineIndex].Text.erase(index_start, m_aLines[start.LineIndex].Text.length() - index_start);
			m_aLines[end.LineIndex].Text.erase(0, index_end);
		}
		else // Delete from same line
			m_aLines[start.LineIndex].Text.erase(index_start, index_end - index_start);
		// Remove intermediate lines and connect first and last lines
		if (end.LineIndex > start.LineIndex)
		{
			m_aLines[start.LineIndex].Text += m_aLines[end.LineIndex].Text;
			m_aLines.erase(m_aLines.begin() + (start.LineIndex + 1), m_aLines.begin() + end.LineIndex+ 1);
		}
		return start.LineIndex;
	}

	void CBuiltInTextArea::HelperUpdateVars(const float line_height, const float space_width, const float control_width)
	{
		m_sTextSize = { 0, 0 };
		m_iMaxCaretPosition = 0;
		int line_count{ 0 };
		for (auto &line : m_aLines)
		{
			for (auto &fake_line : line.FakeLines)
				m_iMaxCaretPosition += (int)fake_line.length() + 1;
			m_sTextSize.X = ntl::Max<float>(m_sTextSize.X, line.Width + space_width);
			line_count += (int)line.FakeLines.size();
		}
		if (m_iMaxCaretPosition > 0)
			m_iMaxCaretPosition--;
		m_sTextSize.Y = (float)line_count * line_height;
		if (m_sTextSize.X <= control_width)
			m_sScroll.X = 0;
		else
			m_sScroll.X = ntl::Max<float>(m_sScroll.X, control_width - m_sTextSize.X);
		if (m_sTextSize.Y <= getHeight())
			m_sScroll.Y = 0;
		else
			m_sScroll.Y = ntl::Max<float>(m_sScroll.Y, getHeight() - m_sTextSize.Y);
		m_iCaretPosition = ntl::Min<int>(m_iMaxCaretPosition, m_iCaretPosition);
		m_sSelection.X = ntl::Min<int>(m_sSelection.X, m_iMaxCaretPosition);
		m_sSelection.Y = ntl::Min<int>(m_sSelection.Y, m_iMaxCaretPosition);
	}

	bool CBuiltInTextArea::HelperInsert(String str)
	{
		ReplaceAllDirect(str, L"\r\n", L"\n");
		ReplaceAllDirect(str, L"\r", L"\n");
		if (str.empty())
			return false;
		float line_height, space_width;
		IPlatformFont *pf;
		if ((pf = getPlatformFont(line_height, space_width)))
		{
			float distance{ getControl()->getFont()->Distance }, control_width{ getWidth() };
			int changed_line_index{ HelperDeleteSelection() }, caret_real{ FakeCaretToReal(m_iCaretPosition) };
			m_sText.insert(caret_real, str.c_str());
			CaretPosition caret_position_start{ FindCaretPosition(m_iCaretPosition) }, new_pos{ caret_position_start };
			if (changed_line_index >= 0 && caret_position_start.LineIndex != changed_line_index)
				BuildFakeLines(m_aLines[changed_line_index], pf, distance, control_width, space_width);
			StringArray lines{ Explode(str, L"\n", false) };
			int in_line_index{ caret_position_start.Index };
			for (int i = 0; i < caret_position_start.FakeLineIndex; i++)
				in_line_index += (int)m_aLines[caret_position_start.LineIndex].FakeLines[i].length();
			if (lines.size() > 1) // Insert several lines
			{
				// Make last line
				m_aLines.insert(m_aLines.begin() + caret_position_start.LineIndex + 1, {
					lines[lines.size() - 1] +
					m_aLines[caret_position_start.LineIndex].Text.substr(in_line_index, m_aLines[caret_position_start.LineIndex].Text.length() - in_line_index)
				});
				BuildFakeLines(m_aLines[caret_position_start.LineIndex + 1], pf, distance, control_width, space_width);

				// Make firs line
				m_aLines[caret_position_start.LineIndex].Text.erase(in_line_index, m_aLines[caret_position_start.LineIndex].Text.length() - in_line_index);
				m_aLines[caret_position_start.LineIndex].Text += lines[0];

				// Make intermediate lines
				for (int i = 1; i < (int)lines.size() - 1; i++)
				{
					m_aLines.insert(m_aLines.begin() + caret_position_start.LineIndex + i, { lines[i] });
					BuildFakeLines(m_aLines[caret_position_start.LineIndex + i], pf, distance, control_width, space_width);
				}
			}
			else // Insert simple string
				m_aLines[caret_position_start.LineIndex].Text.insert(in_line_index, str.c_str());
			BuildFakeLines(m_aLines[caret_position_start.LineIndex], pf, distance, control_width, space_width);

			ApplyLengthLimit(pf, space_width, distance, control_width);
			HelperUpdateVars(line_height, space_width, control_width);

			new_pos.LineIndex += (int)lines.size() - 1;
			new_pos.FakeLineIndex = 0;
			int index_in_line{ lines.size() > 1 ? (int)lines[lines.size() - 1].length() : (in_line_index + (int)lines[0].length()) }, counter{ 0 };
			for (auto &fake_line : m_aLines[new_pos.LineIndex].FakeLines)
			{
				if (counter + (int)fake_line.length() >= index_in_line)
				{
					new_pos.Index = index_in_line - counter;
					break;
				}
				counter += (int)fake_line.length();
				new_pos.FakeLineIndex++;
			}
			m_iCaretPosition = CaretPositionToCaret(new_pos);
			StoreHistory();
			return true;
		}
		return false;
	}

	void CBuiltInTextArea::StoreHistory()
	{
		m_cHistory.Store(History{ m_sText, m_sSelection, m_iCaretPosition }, m_sText.length() * 2 + sizeof(History));
	}

	bool CBuiltInTextArea::ApplyLengthLimit(IPlatformFont *pf, const float space_width, const float distance, const float control_width)
	{
		if (m_iMaxLength > 0 && (int)m_sText.length() > m_iMaxLength)
		{
			int old_length{ (int)m_sText.length() };
			m_sText = m_sText.substr(0, m_iMaxLength);
			if (pf)
			{
				int to_delete{ old_length - (int)m_sText.length() };
				while (to_delete > 0)
				{
					if ((int)m_aLines[m_aLines.size() - 1].Text.length() > to_delete)
					{
						m_aLines[m_aLines.size() - 1].Text.erase(m_aLines[m_aLines.size() - 1].Text.length() - to_delete, to_delete);
						BuildFakeLines(m_aLines[m_aLines.size() - 1], pf, distance, control_width, space_width);
						break;
					}
					to_delete -= (int)m_aLines[m_aLines.size() - 1].Text.length() + 1;
					m_aLines.pop_back();
				}
			}
			return true;
		}
		return false;
	}

	Point CBuiltInTextArea::NormalizeSelection()
	{
		return Point{ ntl::Min<int>(m_sSelection.X, m_sSelection.Y), ntl::Max<int>(m_sSelection.X, m_sSelection.Y) };
	}
#pragma endregion

#pragma region Paint
	void CBuiltInTextArea::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		IPlatformFont *pf;
		float line_height, space_width;
		if (ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && (pf = getPlatformFont(line_height, space_width)))
		{
			IRenderer *renderer{ getControl()->getForm()->getRenderer() };
			ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true) };
			if (clip)
			{
				State state{ getState() };
				
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer->ActivateTarget(clip);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				if (!m_sText.empty())
				{
					RenderShadow(renderer, state, clip, line_height, space_width, pf);
					RenderText(renderer, state, line_height, space_width, pf);
					RenderSelectionBackground(renderer, state, line_height, space_width, pf);
					RenderSelectionShadow(renderer, state, clip, line_height, space_width, pf);
					RenderSelectionText(renderer, state, line_height, space_width, pf);
				}
				if (old)
				{
					renderer
						->ActivateTarget(old)
						->ActivatePrimitiveMatrix(matrix)
						->DrawImage(clip, 1)
						->ActivateTarget(clip)
						->Clear(Color{ 0, 0, 0, 0 })
						->ActivatePrimitiveMatrix(ntl::Inversed<float>(matrix))
						->DrawImage(old, 1)
						->ActivatePrimitiveMatrix(nullptr);
					RenderCaret(state, pf, line_height, space_width);
				}
				else
					RenderCaret(state, pf, line_height, space_width);
				renderer
					->ActivateTarget(old)
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(clip, 1);
				clip->Release();
			}
		}
	}

	void CBuiltInTextArea::RenderShadow(IRenderer *renderer, const State state, ITexture *clip, const float line_height, const float space_width, IPlatformFont *pf)
	{
		Color color{ m_aShadowColor[(int)state].A > 0 ? m_aShadowColor[(int)state] : getControl()->getFont()->ShadowColor };
		if (color.A > 0)
		{
			ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(getWidth() + float(2 * m_aShadowRadius[(int)state])), ntl::Round<int>(getHeight() + float(2 * m_aShadowRadius[(int)state])), 1, TextureFormat::RGBA, true) };
			if (shadow)
			{
				renderer->ActivateTarget(shadow);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				{
					CStorePrimitiveMatrix s_matrix{ renderer };
					PointF control_size{ getSize() };
					float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, x;
					for (auto &line : m_aLines)
					{
						if (y >= control_size.Y)
							break;
						if (y + (float)line.FakeLines.size() * line_height >= 0)
						{
							for (auto &fake_line : line.FakeLines)
							{
								switch (m_eAlign)
								{
								case TextAlign::Right:
									x = getWidth() - pf->getStringSize(fake_line, distance).X - space_width + m_sScroll.X;
									break;
								case TextAlign::Center:
									x = (getWidth() - pf->getStringSize(fake_line, distance).X - space_width) * 0.5f + m_sScroll.X;
								default:
									x = m_sScroll.X;
								}
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x + (float)m_aShadowRadius[(int)state]), std::round(y + (float)m_aShadowRadius[(int)state]), 0))
									->DrawText(fake_line, pf, distance, color);
								y += line_height;
							}
						}
						else
							y += (float)line.FakeLines.size() * line_height;
					}
				}

				renderer
					->BlurImage(shadow, m_aShadowRadius[(int)state], BlurType::Gaussian)
					// Draw shadow into clip texture
					->ActivateTarget(clip)
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_aShadowShift[(int)state].X - (float)m_aShadowRadius[(int)state], m_aShadowShift[(int)state].Y - (float)m_aShadowRadius[(int)state], 0))
					->DrawImage(shadow, 1);

				shadow->Release();
			}
		}
	}

	void CBuiltInTextArea::RenderText(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf)
	{
		Color color{ m_aTextColor[(int)state].A > 0 ? m_aTextColor[(int)state] : getControl()->getFont()->Color };
		if (color.A > 0)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			PointF control_size{ getSize() };
			float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, x;
			for (auto &line : m_aLines)
			{
				if (y >= control_size.Y)
					break;
				if (y + (float)line.FakeLines.size() * line_height >= 0)
				{
					for (auto &fake_line : line.FakeLines)
					{
						switch (m_eAlign)
						{
						case TextAlign::Right:
							x = getWidth() - pf->getStringSize(fake_line, distance).X - space_width + m_sScroll.X;
							break;
						case TextAlign::Center:
							x = (getWidth() - pf->getStringSize(fake_line, distance).X - space_width) * 0.5f + m_sScroll.X;
						default:
							x = m_sScroll.X;
						}
						renderer
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x), std::round(y), 0))
							->DrawText(fake_line, pf, distance, color);
						y += line_height;
					}
				}
				else
					y += (float)line.FakeLines.size() * line_height;
			}
		}
	}

	void CBuiltInTextArea::RenderSelectionBackground(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf)
	{
		if (m_sSelection.X != m_sSelection.Y && m_aSelectionBackgroundColor[(int)state].A > 0)
		{
			Point selection{ NormalizeSelection() };
			PointF control_size{ getSize() };
			CaretPosition selection_start{ FindCaretPosition(selection.X) }, selection_end{ FindCaretPosition(selection.Y) };
			float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, x, x1, x2, w, y1, y2;
			int line_index{ 0 }, fake_line_index;
			for (auto &line : m_aLines)
			{
				if (y >= control_size.Y)
					break;
				if (y + (float)line.FakeLines.size() * line_height >= 0 && line_index >= selection_start.LineIndex && line_index <= selection_end.LineIndex)
				{
					fake_line_index = 0;
					for (auto &fake_line : line.FakeLines)
					{
						if ((line_index > selection_start.LineIndex || fake_line_index >= selection_start.FakeLineIndex) &&
							(line_index < selection_end.LineIndex || fake_line_index <= selection_end.FakeLineIndex))
						{
							switch (m_eAlign)
							{
							case TextAlign::Right:
								x1 = x = getWidth() - pf->getStringSize(fake_line, distance).X - space_width + m_sScroll.X;
								x2 = control_size.X;
								break;
							case TextAlign::Center:
								w = pf->getStringSize(fake_line, distance).X;
								x1 = x = (getWidth() - w - space_width) * 0.5f + m_sScroll.X;
								x2 = x + w;
							default:
								x1 = x = m_sScroll.X;
								x2 = x1 + pf->getStringSize(fake_line, distance).X;
							}
							if (line_index == selection_start.LineIndex && fake_line_index == selection_start.FakeLineIndex)
								x1 += pf->getStringSize(fake_line.substr(0, selection_start.Index), distance).X;
							if (line_index == selection_end.LineIndex && fake_line_index == selection_end.FakeLineIndex)
								x2 = x + pf->getStringSize(fake_line.substr(0, selection_end.Index), distance).X;
							x1 = ntl::Clamp<float>(x1, 0.0f, control_size.X);
							x2 = ntl::Clamp<float>(x2, 0.0f, control_size.X);
							y1 = ntl::Clamp<float>(y, 0.0f, control_size.Y);
							y2 = ntl::Clamp<float>(y + line_height, 0.0f, control_size.Y);
							renderer->DrawRectangle(RectF{ x1, y1, x2, y2 }, m_aSelectionBackgroundColor[(int)state]);
						}
						y += line_height;
						fake_line_index++;
					}
				}
				else
					y += (float)line.FakeLines.size() * line_height;
				line_index++;
			}
		}
	}

	void CBuiltInTextArea::RenderSelectionShadow(IRenderer *renderer, const State state, ITexture *clip, const float line_height, const float space_width, IPlatformFont *pf)
	{
		if (m_sSelection.X != m_sSelection.Y)
		{
			Color color{ m_aSelectionShadowColor[(int)state].A > 0 ? m_aSelectionShadowColor[(int)state] : getControl()->getFont()->ShadowColor };
			if (color.A > 0)
			{
				ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(getWidth() + float(2 * m_aShadowRadius[(int)state])), ntl::Round<int>(getHeight() + float(2 * m_aShadowRadius[(int)state])), 1, TextureFormat::RGBA, true) };
				if (shadow)
				{
					renderer->ActivateTarget(shadow);
					renderer->Clear(Color{ 0, 0, 0, 0 });

					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						Point selection{ NormalizeSelection() };
						PointF control_size{ getSize() };
						CaretPosition selection_start{ FindCaretPosition(selection.X) }, selection_end{ FindCaretPosition(selection.Y) };
						float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, x;
						int line_index{ 0 }, fake_line_index, s1, s2;
						for (auto &line : m_aLines)
						{
							if (y >= control_size.Y)
								break;
							if (y + (float)line.FakeLines.size() * line_height >= 0 && line_index >= selection_start.LineIndex && line_index <= selection_end.LineIndex)
							{
								fake_line_index = 0;
								for (auto &fake_line : line.FakeLines)
								{
									if ((line_index > selection_start.LineIndex || fake_line_index >= selection_start.FakeLineIndex) &&
										(line_index < selection_end.LineIndex || fake_line_index <= selection_end.FakeLineIndex))
									{
										switch (m_eAlign)
										{
										case TextAlign::Right:
											x = getWidth() - pf->getStringSize(fake_line, distance).X - space_width + m_sScroll.X;
											break;
										case TextAlign::Center:
											x = (getWidth() - pf->getStringSize(fake_line, distance).X - space_width) * 0.5f + m_sScroll.X;
										default:
											x = m_sScroll.X;
										}
										s1 = 0;
										s2 = (int)fake_line.length();
										if (line_index == selection_start.LineIndex && fake_line_index == selection_start.FakeLineIndex)
										{
											x += pf->getStringSize(fake_line.substr(0, selection_start.Index), distance).X;
											s1 = selection_start.Index;
										}
										if (line_index == selection_end.LineIndex && fake_line_index == selection_end.FakeLineIndex)
											s2 = selection_end.Index;
										renderer
											->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x + (float)m_aShadowRadius[(int)state]), std::round(y + (float)m_aShadowRadius[(int)state]), 0))
											->DrawText(fake_line.substr(s1, s2 - s1), pf, distance, color);
									}
									y += line_height;
									fake_line_index++;
								}
							}
							else
								y += (float)line.FakeLines.size() * line_height;
							line_index++;
						}
					}
					renderer
						->BlurImage(shadow, m_aShadowRadius[(int)state], BlurType::Gaussian)
						// Draw shadow into clip texture
						->ActivateTarget(clip)
						->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_aShadowShift[(int)state].X - (float)m_aShadowRadius[(int)state], m_aShadowShift[(int)state].Y - (float)m_aShadowRadius[(int)state], 0))
						->DrawImage(shadow, 1);
					shadow->Release();
				}
			}
		}
	}

	void CBuiltInTextArea::RenderSelectionText(IRenderer *renderer, const State state, const float line_height, const float space_width, IPlatformFont *pf)
	{
		if (m_sSelection.X != m_sSelection.Y)
		{
			Color color{ m_aSelectionTextColor[(int)state].A > 0 ? m_aSelectionTextColor[(int)state] : getControl()->getFont()->Color };
			if (color.A > 0)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				Point selection{ NormalizeSelection() };
				PointF control_size{ getSize() };
				CaretPosition selection_start{ FindCaretPosition(selection.X) }, selection_end{ FindCaretPosition(selection.Y) };
				float y{ m_sScroll.Y }, distance{ getControl()->getFont()->Distance }, x;
				int line_index{ 0 }, fake_line_index, s1, s2;
				for (auto &line : m_aLines)
				{
					if (y >= control_size.Y)
						break;
					if (y + (float)line.FakeLines.size() * line_height >= 0 && line_index >= selection_start.LineIndex && line_index <= selection_end.LineIndex)
					{
						fake_line_index = 0;
						for (auto &fake_line : line.FakeLines)
						{
							if ((line_index > selection_start.LineIndex || fake_line_index >= selection_start.FakeLineIndex) &&
								(line_index < selection_end.LineIndex || fake_line_index <= selection_end.FakeLineIndex))
							{
								switch (m_eAlign)
								{
								case TextAlign::Right:
									x = getWidth() - pf->getStringSize(fake_line, distance).X - space_width + m_sScroll.X;
									break;
								case TextAlign::Center:
									x = (getWidth() - pf->getStringSize(fake_line, distance).X - space_width) * 0.5f + m_sScroll.X;
								default:
									x = m_sScroll.X;
								}
								s1 = 0;
								s2 = (int)fake_line.length();
								if (line_index == selection_start.LineIndex && fake_line_index == selection_start.FakeLineIndex)
								{
									x += pf->getStringSize(fake_line.substr(0, selection_start.Index), distance).X;
									s1 = selection_start.Index;
								}
								if (line_index == selection_end.LineIndex && fake_line_index == selection_end.FakeLineIndex)
									s2 = selection_end.Index;
								renderer
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(x), std::round(y), 0))
									->DrawText(fake_line.substr(s1, s2 - s1), pf, distance, color);
							}
							y += line_height;
							fake_line_index++;
						}
					}
					else
						y += (float)line.FakeLines.size() * line_height;
					line_index++;
				}
			}
		}
	}

	void CBuiltInTextArea::RenderCaret(const State state, IPlatformFont *pf, const float line_height, const float space_width)
	{
		if ((state == State::Focused || state == State::FocusedHovered) && getControl()->getForm()->getCaret())
		{
			PointF size{ 1, line_height };
			if (m_bReplacing)
			{
				if (getControl()->getForm()->getCaret()->isInversed())
				{
					CaretPosition cp{ FindCaretPosition(m_iCaretPosition) };
					String s{ m_aLines[cp.LineIndex].FakeLines[cp.FakeLineIndex].substr(cp.Index, 1) };
					if (s.empty())
						size.X = space_width;
					else
						size.X = pf->getStringSize(s, 0).X;
				}
				else
					size.X = 2;
			}
			getControl()->getForm()->getCaret()->setSize(size);
			PointF caret_pos{ CaretToClient(m_iCaretPosition, pf, line_height, space_width) };
			getControl()->getForm()->getCaret()->Render(ntl::Mat4Translate<float>(std::round(caret_pos.X), std::round(caret_pos.Y), 0));
		}
	}
#pragma endregion
}