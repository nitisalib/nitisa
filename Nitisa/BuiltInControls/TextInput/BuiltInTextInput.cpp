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
	CBuiltInTextInput::CTimerListener::CTimerListener(CBuiltInTextInput *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInTextInput::CTimerListener::NotifyOnTimer(const PlatformHandle id)
	{
		int d{ 0 };
		if (ntl::IsLess<float>(m_pControl->m_sMousePosition.X, 0))
			d = -1;
		else if (ntl::IsGreater<float>(m_pControl->m_sMousePosition.X, m_pControl->getWidth()))
			d = 1;
		if (d != 0 && m_pControl->setCaretPosition(m_pControl->m_iCaretPosition + d))
		{
			m_pControl->ScrollToCaret();
			if (!m_pControl->m_bMoveSelection)
				m_pControl->setSelection(Point{ m_pControl->m_sSelection.X, m_pControl->m_iCaretPosition });
			if (m_pControl->m_pListener)
				m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
		}
	}
#pragma endregion

#pragma region CCaretListener
	CBuiltInTextInput::CCaretListener::CCaretListener(CBuiltInTextInput *control) :
		m_pControl{ control }
	{

	}

	void CBuiltInTextInput::CCaretListener::NotifyOnChange()
	{
		if (m_pControl->m_pListener)
			m_pControl->m_pListener->NotifyOnRepaint(m_pControl, m_pControl->getRect());
	}
#pragma endregion

#pragma region Constructor & destructor
	CBuiltInTextInput::CBuiltInTextInput() :
		CBuiltInControl(L"TextInput"),
		m_sSelection{ 0, 0 },
		m_iCaretPosition{ 0 },
		m_iMaxLength{ 0 },
		m_fScroll{ 0 },
		m_eAlign{ TextAlign::Left },
		m_hTimer{ nullptr },
		m_fScrollInterval{ ScrollInterval },
		m_bMouseDown{ false },
		m_bMoveSelection{ false },
		m_bReadOnly{ false },
		m_bReplacing{ false },
		m_bHovered{ false },
		m_aTextColor{
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 0, 0, 0, 0 },
			Color{ 109, 109, 109, 255 } },
		m_aPlaceholderColor{
			Color{ 0, 0, 0, 100 },
			Color{ 0, 0, 0, 100 },
			Color{ 0, 0, 0, 100 },
			Color{ 0, 0, 0, 100 },
			Color{ 0, 0, 0, 0 } },
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
		m_bCopyByMouseEnabled{ true },
		m_bMoveByMouseEnabled{ true },
		m_bSelectWordByDoubleClickEnabled{ true },
		m_bKeyLeftEnabled{ true },
		m_bKeyRightEnabled{ true },
		m_bKeyHomeEnabled{ true },
		m_bKeyEndEnabled{ true },
		m_bKeyDeleteEnabled{ true },
		m_bKeyBackspaceEnabled{ true },
		m_bSelectAllByKeyEnabled{ true },
		m_bPasteByKeyEnabled{ true },
		m_bCopyByKeyEnabled{ true },
		m_bCutByKeyEnabled{ true },
		m_bHistoryByKeyEnabled{ true },
		m_bInsertReplaceChangeByKeyEnabled{ true },
		m_pListener{ nullptr },
		m_cTimerListener{ this },
		m_cCaretListener{ this }
	{
		m_cHistory.setLimitCount(3);
		StoreHistory();
	}
#pragma endregion

#pragma region IBuiltInControl getters
	IBuiltInControlListener *CBuiltInTextInput::getListener()
	{
		return m_pListener;
	}

	bool CBuiltInTextInput::isHovered()
	{
		return m_bHovered;
	}

	CursorType CBuiltInTextInput::getCursor(const PointF &position, const CursorType def)
	{
		if (m_bMouseDown && m_bMoveSelection)
		{
			if (m_iCaretPosition >= m_sSelection.X && m_iCaretPosition <= m_sSelection.Y)
				return CursorType::No;
			return CursorType::Arrow;
		}
		return def;
	}

	bool CBuiltInTextInput::isDown()
	{
		return m_bMouseDown;
	}

	bool CBuiltInTextInput::hasSelection()
	{
		return m_sSelection.X != m_sSelection.Y;
	}
#pragma endregion

#pragma region IBuiltInTextInput getters
	String CBuiltInTextInput::getText()
	{
		return m_sText;
	}

	String CBuiltInTextInput::getSelectedText()
	{
		if (m_sSelection.X == m_sSelection.Y)
			return L"";
		return m_sText.substr(ntl::Min<int>(m_sSelection.X, m_sSelection.Y), ntl::Abs<int>(m_sSelection.Y - m_sSelection.X));
	}

	Point CBuiltInTextInput::getSelection()
	{
		return m_sSelection;
	}

	int CBuiltInTextInput::getCaretPosition()
	{
		return m_iCaretPosition;
	}

	float CBuiltInTextInput::getScroll()
	{
		return m_fScroll;
	}

	int CBuiltInTextInput::getMaxLength()
	{
		return m_iMaxLength;
	}

	int CBuiltInTextInput::getUndoLimitCount()
	{
		return (int)m_cHistory.getLimitCount();
	}

	int CBuiltInTextInput::getUndoLimitSize()
	{
		return (int)m_cHistory.getLimitSize();
	}

	bool CBuiltInTextInput::canUndo()
	{
		return m_cHistory.getPosition() > 0;
	}

	bool CBuiltInTextInput::canRedo()
	{
		return m_cHistory.getCount() > 0 && m_cHistory.getPosition() < m_cHistory.getCount() - 1;
	}

	TextAlign CBuiltInTextInput::getAlign()
	{
		return m_eAlign;
	}

	bool CBuiltInTextInput::isMoving()
	{
		return m_bMouseDown && m_bMoveSelection;
	}
#pragma endregion

#pragma region Getters
	String CBuiltInTextInput::getPlaceholder() const
	{
		return m_sPlaceholder;
	}

	bool CBuiltInTextInput::isReadOnly() const
	{
		return m_bReadOnly;
	}

	bool CBuiltInTextInput::isReplacing() const
	{
		return m_bReplacing;
	}

	float CBuiltInTextInput::getScrollInterval() const
	{
		return m_fScrollInterval;
	}

	CBuiltInTextInput::State CBuiltInTextInput::getState()
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

	Color CBuiltInTextInput::getTextColor(const State state) const
	{
		return m_aTextColor[(int)state];
	}

	Color CBuiltInTextInput::getPlaceholderColor(const State state) const
	{
		return m_aPlaceholderColor[(int)state];
	}

	Color CBuiltInTextInput::getShadowColor(const State state) const
	{
		return m_aShadowColor[(int)state];
	}

	Color CBuiltInTextInput::getSelectionBackgroundColor(const State state) const
	{
		return m_aSelectionBackgroundColor[(int)state];
	}

	Color CBuiltInTextInput::getSelectionTextColor(const State state) const
	{
		return m_aSelectionTextColor[(int)state];
	}

	Color CBuiltInTextInput::getSelectionShadowColor(const State state) const
	{
		return m_aSelectionShadowColor[(int)state];
	}

	PointF CBuiltInTextInput::getShadowShift(const State state) const
	{
		return m_aShadowShift[(int)state];
	}

	int CBuiltInTextInput::getShadowRadius(const State state) const
	{
		return m_aShadowRadius[(int)state];
	}

	bool CBuiltInTextInput::isCopyByMouseEnabled() const
	{
		return m_bCopyByMouseEnabled;
	}

	bool CBuiltInTextInput::isMoveByMouseEnabled() const
	{
		return m_bMoveByMouseEnabled;
	}

	bool CBuiltInTextInput::isSelectWordByDoubleClickEnabled() const
	{
		return m_bSelectWordByDoubleClickEnabled;
	}

	bool CBuiltInTextInput::isKeyLeftEnabled() const
	{
		return m_bKeyLeftEnabled;
	}

	bool CBuiltInTextInput::isKeyRightEnabled() const
	{
		return m_bKeyRightEnabled;
	}

	bool CBuiltInTextInput::isKeyHomeEnabled() const
	{
		return m_bKeyHomeEnabled;
	}

	bool CBuiltInTextInput::isKeyEndEnabled() const
	{
		return m_bKeyEndEnabled;
	}

	bool CBuiltInTextInput::isKeyDeleteEnabled() const
	{
		return m_bKeyDeleteEnabled;
	}

	bool CBuiltInTextInput::isKeyBackspaceEnabled() const
	{
		return m_bKeyBackspaceEnabled;
	}

	bool CBuiltInTextInput::isSelectAllByKeyEnabled() const
	{
		return m_bSelectAllByKeyEnabled;
	}

	bool CBuiltInTextInput::isPasteByKeyEnabled() const
	{
		return m_bPasteByKeyEnabled;
	}

	bool CBuiltInTextInput::isCopyByKeyEnabled() const
	{
		return m_bCopyByKeyEnabled;
	}

	bool CBuiltInTextInput::isCutByKeyEnabled() const
	{
		return m_bCutByKeyEnabled;
	}

	bool CBuiltInTextInput::isHistoryByKeyEnabled() const
	{
		return m_bHistoryByKeyEnabled;
	}

	bool CBuiltInTextInput::isInsertReplaceChangeByKeyEnabled() const
	{
		return m_bInsertReplaceChangeByKeyEnabled;
	}
#pragma endregion

#pragma region IBuiltInControl setters
	void CBuiltInTextInput::setListener(IBuiltInControlListener *value)
	{
		m_pListener = value;
	}

	bool CBuiltInTextInput::setFocused(const bool value)
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

	bool CBuiltInTextInput::setEnabled(const bool value)
	{
		if (CBuiltInControl::setEnabled(value))
		{
			if (!isEnabled())
				setFocused(false);
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setDPI(const Point &value)
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

#pragma region IBuiltInTextInput setters
	bool CBuiltInTextInput::setText(const String &value)
	{
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
		m_iCaretPosition = ntl::Min<int>(m_iCaretPosition, (int)m_sText.length());
		m_sSelection.X = ntl::Min<int>(m_sSelection.X, (int)m_sText.length());
		m_sSelection.Y = ntl::Min<int>(m_sSelection.Y, (int)m_sText.length());
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::setSelection(const Point &value)
	{
		if (value == m_sSelection || value.X < 0 || value.Y < 0 || value.X >(int)m_sText.length() || value.Y >(int)m_sText.length())
			return false;
		if (m_sSelection.X == m_sSelection.Y && value.X == value.Y)
		{
			m_sSelection = value;
			return false;
		}
		m_sSelection = value;
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::setCaretPosition(const int value)
	{
		if (value == m_iCaretPosition || value < 0 || value >(int)m_sText.length())
			return false;
		m_iCaretPosition = value;
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::setScroll(const float value)
	{
		if (ntl::IsNotEqual<float>(value, m_fScroll))
		{
			m_fScroll = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setMaxLength(const int value)
	{
		if (value < 0 || value == m_iMaxLength)
			return false;
		m_iMaxLength = value;
		if (ApplyLengthLimit())
		{
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setUndoLimitCount(const int value)
	{
		if (value < 0 || value == (int)m_cHistory.getLimitCount())
			return false;
		return m_cHistory.setLimitCount(value);
	}

	bool CBuiltInTextInput::setUndoLimitSize(const int value)
	{
		if (value < 0 || value == (int)m_cHistory.getLimitSize())
			return false;
		return m_cHistory.setLimitSize(value);
	}

	bool CBuiltInTextInput::setAlign(const TextAlign value)
	{
		if (value != m_eAlign)
		{
			m_eAlign = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region Setters
	bool CBuiltInTextInput::setPlaceholder(const String &value)
	{
		if (value != m_sPlaceholder)
		{
			m_sPlaceholder = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setReadOnly(const bool value)
	{
		if (value != m_bReadOnly)
		{
			m_bReadOnly = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setReplacing(const bool value)
	{
		if (value != m_bReplacing)
		{
			m_bReplacing = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setScrollInterval(const float value)
	{
		if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
		{
			m_fScrollInterval = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setTextColor(const State state, const Color &value)
	{
		if (value != m_aTextColor[(int)state])
		{
			m_aTextColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setPlaceholderColor(const State state, const Color &value)
	{
		if (value != m_aPlaceholderColor[(int)state])
		{
			m_aPlaceholderColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setShadowColor(const State state, const Color &value)
	{
		if (value != m_aShadowColor[(int)state])
		{
			m_aShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setSelectionBackgroundColor(const State state, const Color &value)
	{
		if (value != m_aSelectionBackgroundColor[(int)state])
		{
			m_aSelectionBackgroundColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setSelectionTextColor(const State state, const Color &value)
	{
		if (value != m_aSelectionTextColor[(int)state])
		{
			m_aSelectionTextColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setSelectionShadowColor(const State state, const Color &value)
	{
		if (value != m_aSelectionShadowColor[(int)state])
		{
			m_aSelectionShadowColor[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setShadowShift(const State state, const PointF &value)
	{
		if (IsNotEqual(value, m_aShadowShift[(int)state]))
		{
			m_aShadowShift[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setShadowRadius(const State state, const int value)
	{
		if (value >= 1 && value != m_aShadowRadius[(int)state])
		{
			m_aShadowRadius[(int)state] = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setCopyByMouseEnabled(const bool value)
	{
		if (value != m_bCopyByMouseEnabled)
		{
			m_bCopyByMouseEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setMoveByMouseEnabled(const bool value)
	{
		if (value != m_bMoveByMouseEnabled)
		{
			m_bMoveByMouseEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setSelectWordByDoubleClickEnabled(const bool value)
	{
		if (value != m_bSelectWordByDoubleClickEnabled)
		{
			m_bSelectWordByDoubleClickEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyLeftEnabled(const bool value)
	{
		if (value != m_bKeyLeftEnabled)
		{
			m_bKeyLeftEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyRightEnabled(const bool value)
	{
		if (value != m_bKeyRightEnabled)
		{
			m_bKeyRightEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyHomeEnabled(const bool value)
	{
		if (value != m_bKeyHomeEnabled)
		{
			m_bKeyHomeEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyEndEnabled(const bool value)
	{
		if (value != m_bKeyEndEnabled)
		{
			m_bKeyEndEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyDeleteEnabled(const bool value)
	{
		if (value != m_bKeyDeleteEnabled)
		{
			m_bKeyDeleteEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setKeyBackspaceEnabled(const bool value)
	{
		if (value != m_bKeyBackspaceEnabled)
		{
			m_bKeyBackspaceEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setSelectAllByKeyEnabled(const bool value)
	{
		if (value != m_bSelectAllByKeyEnabled)
		{
			m_bSelectAllByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setPasteByKeyEnabled(const bool value)
	{
		if (value != m_bPasteByKeyEnabled)
		{
			m_bPasteByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setCopyByKeyEnabled(const bool value)
	{
		if (value != m_bCopyByKeyEnabled)
		{
			m_bCopyByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setCutByKeyEnabled(const bool value)
	{
		if (value != m_bCutByKeyEnabled)
		{
			m_bCutByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setHistoryByKeyEnabled(const bool value)
	{
		if (value != m_bHistoryByKeyEnabled)
		{
			m_bHistoryByKeyEnabled = value;
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::setInsertReplaceChangeByKeyEnabled(const bool value)
	{
		if (value != m_bInsertReplaceChangeByKeyEnabled)
		{
			m_bInsertReplaceChangeByKeyEnabled = value;
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region IBuiltInControl helpers
	void CBuiltInTextInput::UpdateFromStyle(IStyle *style, const String &class_name)
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
#pragma endregion

#pragma region IBuiltInTextInput helpers
	bool CBuiltInTextInput::DeleteSelection()
	{
		if (DeleteSelectionInternal())
		{
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::DeleteCharBeforeCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition > 0)
		{
			m_sText.erase(m_iCaretPosition - 1, 1);
			m_iCaretPosition--;
			result = true;
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::DeleteCharAfterCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition < (int)m_sText.length())
		{
			m_sText.erase(m_iCaretPosition, 1);
			result = true;
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::DeleteWordBeforeCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition > 0)
		{
			int i{ (int)SearchPrevWord(m_sText, m_iCaretPosition) };
			if (i < m_iCaretPosition)
			{
				m_sText.erase(i, m_iCaretPosition - i);
				m_iCaretPosition = i;
				result = true;
			}
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::DeleteWordAfterCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition < (int)m_sText.length())
		{
			int i{ (int)SearchNextWord(m_sText, m_iCaretPosition) };
			if (i > m_iCaretPosition)
			{
				m_sText.erase(m_iCaretPosition, i - m_iCaretPosition);
				result = true;
			}
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::DeleteAllBeforeCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition > 0)
		{
			m_sText.erase(0, m_iCaretPosition);
			m_iCaretPosition = 0;
			result = true;
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::DeleteAllAfterCaret()
	{
		bool result{ DeleteSelectionInternal() };
		if (!result && m_iCaretPosition < (int)m_sText.length())
		{
			m_sText.erase(m_iCaretPosition, m_sText.length() - m_iCaretPosition);
			result = true;
		}
		if (result)
			StoreHistory();
		return result;
	}

	bool CBuiltInTextInput::MoveCaretLeft(const bool select)
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
			m_sSelection.Y = m_sSelection.X;
			if (m_iCaretPosition > 0)
				m_iCaretPosition--;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::MoveCaretRight(const bool select)
	{
		if (select && m_iCaretPosition < (int)m_sText.length())
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition++;
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition < (int)m_sText.length() || m_sSelection.X != m_sSelection.Y))
		{
			m_sSelection.Y = m_sSelection.X;
			if (m_iCaretPosition < (int)m_sText.length())
				m_iCaretPosition++;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::MoveCaretWordLeft(const bool select)
	{
		if (select && m_iCaretPosition > 0)
		{
			int i{ (int)SearchPrevWord(m_sText, m_iCaretPosition) };
			if (i < m_iCaretPosition)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_iCaretPosition = i;
				m_sSelection.Y = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		if (!select && (m_iCaretPosition > 0 || m_sSelection.X != m_sSelection.Y))
		{
			int i{ (int)SearchPrevWord(m_sText, m_iCaretPosition) };
			m_sSelection.Y = m_sSelection.X;
			if (i < m_iCaretPosition)
				m_iCaretPosition = i;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::MoveCaretWordRight(const bool select)
	{
		if (select && m_iCaretPosition < (int)m_sText.length())
		{
			int i{ (int)SearchNextWord(m_sText, m_iCaretPosition) };
			if (i > m_iCaretPosition)
			{
				if (m_sSelection.X == m_sSelection.Y)
					m_sSelection.X = m_iCaretPosition;
				m_iCaretPosition = i;
				m_sSelection.Y = m_iCaretPosition;
				StoreHistory();
				return true;
			}
		}
		if (!select && (m_iCaretPosition < (int)m_sText.length() || m_sSelection.X != m_sSelection.Y))
		{
			int i{ (int)SearchNextWord(m_sText, m_iCaretPosition) };
			m_sSelection.Y = m_sSelection.X;
			if (i > m_iCaretPosition)
				m_iCaretPosition = i;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::MoveCaretStart(const bool select)
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
			m_sSelection.Y = m_sSelection.X;
			m_iCaretPosition = 0;
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::MoveCaretEnd(const bool select)
	{
		if (select && m_iCaretPosition < (int)m_sText.length())
		{
			if (m_sSelection.X == m_sSelection.Y)
				m_sSelection.X = m_iCaretPosition;
			m_iCaretPosition = (int)m_sText.length();
			m_sSelection.Y = m_iCaretPosition;
			StoreHistory();
			return true;
		}
		if (!select && (m_iCaretPosition < (int)m_sText.length() || m_sSelection.X != m_sSelection.Y))
		{
			m_sSelection.Y = m_sSelection.X;
			m_iCaretPosition = (int)m_sText.length();
			StoreHistory();
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::Undo(bool &text_changed)
	{
		if (m_cHistory.getPosition() == 0)
			return false;
		History h = m_cHistory.getItem(m_cHistory.getPosition() - 1);
		if (m_sText != h.Text)
		{
			m_sText = h.Text;
			text_changed = true;
		}
		m_sSelection = h.Selection;
		m_iCaretPosition = h.CaretPosition;
		m_cHistory.setPosition(m_cHistory.getPosition() - 1);
		return true;
	}

	bool CBuiltInTextInput::Redo(bool &text_changed)
	{
		if (m_cHistory.getPosition() >= m_cHistory.getCount() - 1)
			return false;
		History h = m_cHistory.getItem(m_cHistory.getPosition() + 1);
		if (m_sText != h.Text)
		{
			m_sText = h.Text;
			text_changed = true;
		}
		m_sSelection = h.Selection;
		m_iCaretPosition = h.CaretPosition;
		m_cHistory.setPosition(m_cHistory.getPosition() + 1);
		return true;
	}

	bool CBuiltInTextInput::Insert(const wchar_t chr)
	{
		DeleteSelectionInternal();
		m_sText.insert(m_sText.begin() + m_iCaretPosition, chr);
		m_iCaretPosition++;
		ApplyLengthLimit();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::Insert(const String &str)
	{
		if (str.empty())
			return false;
		DeleteSelectionInternal();
		m_sText.insert(m_iCaretPosition, str);
		m_iCaretPosition += (int)str.length();
		ApplyLengthLimit();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::Replace(const wchar_t chr)
	{
		if (DeleteSelectionInternal())
			m_sText.insert(m_sText.begin() + m_iCaretPosition, chr);
		else
		{
			if (m_iCaretPosition == (int)m_sText.length())
				return Insert(chr);
			m_sText.replace(m_iCaretPosition, 1, 1, chr);
		}
		m_iCaretPosition++;
		ApplyLengthLimit();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::Replace(const String &str)
	{
		if (str.empty())
			return false;
		DeleteSelectionInternal();
		m_sText.insert(m_iCaretPosition, str);
		m_iCaretPosition += (int)str.length();
		ApplyLengthLimit();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::MoveSelection(const int dst_caret_pos)
	{
		Point selection{ NormalizeSelection() };
		if (selection.X == selection.Y || dst_caret_pos < 0 || dst_caret_pos >(int)m_sText.length() || (dst_caret_pos >= selection.X && dst_caret_pos < selection.Y))
			return false;
		int dst{ dst_caret_pos > selection.X ? (dst_caret_pos - selection.Y + selection.X) : dst_caret_pos };
		String s{ m_sText.substr(selection.X, selection.Y - selection.X) };
		DeleteSelectionInternal();
		m_sText.insert(dst, s);
		m_iCaretPosition = dst + (int)s.length();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::CopySelection(const int dst_caret_pos)
	{
		Point selection{ NormalizeSelection() };
		if (selection.X == selection.Y || dst_caret_pos < 0 || dst_caret_pos >(int)m_sText.length() || (dst_caret_pos >= selection.X && dst_caret_pos < selection.Y))
			return false;
		String s{ m_sText.substr(selection.X, selection.Y - selection.X) };
		m_sSelection.Y = m_sSelection.X;
		m_sText.insert(dst_caret_pos, s);
		m_iCaretPosition = dst_caret_pos + (int)s.length();
		ApplyLengthLimit();
		StoreHistory();
		return true;
	}

	bool CBuiltInTextInput::Copy()
	{
		String text{ getSelectedText() };
		if (!text.empty() && getControl()->getForm())
			return getControl()->getForm()->CopyStringToClipboard(text);
		return false;
	}

	bool CBuiltInTextInput::Cut()
	{
		String text{ getSelectedText() };
		if (!text.empty() && DeleteSelection())
		{
			ScrollToCaret();
			if (getControl()->getForm())
				getControl()->getForm()->CopyStringToClipboard(text);
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::Paste()
	{
		if (getControl()->getForm())
			return getControl()->getForm()->CopyStringFromClipboard();
		return false;
	}

	bool CBuiltInTextInput::ScrollToCaret()
	{
		if (ntl::IsEqual<float>(getWidth(), 0) || !getControl() || !getControl()->getFont() || !getControl()->getForm() || !getControl()->getForm()->getRenderer() ||
			!getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
			return false;
		IFont *font{ getControl()->getFont() };
		float pos{ CaretToClient(m_iCaretPosition) };
		float char_width{
			(m_iCaretPosition >= (int)m_sText.length()) ?
			font->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(L" ", font->Distance).X :
			font->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(m_sText.substr(m_iCaretPosition, 1), font->Distance).X };
		if (ntl::IsGreaterOrEqual<float>(pos, 0) && ntl::IsLess<float>(pos + char_width, getWidth()))
			return false;
		bool result{ false };
		if (ntl::IsGreater<float>(pos + char_width, getWidth()))
		{
			m_fScroll -= pos + char_width - getWidth();
			result = true;
		}
		if (ntl::IsLess<float>(pos, 0))
		{
			m_fScroll -= pos;
			result = true;
		}
		return result;
	}

	bool CBuiltInTextInput::SelectAll()
	{
		return setSelection(Point{ 0, (int)m_sText.length() });
	}

	bool CBuiltInTextInput::DeselectAll()
	{
		return setSelection(Point{ 0, 0 });
	}
#pragma endregion

#pragma region Helpers
	void CBuiltInTextInput::StoreHistory()
	{
		m_cHistory.Store(History{ m_sText, m_sSelection, m_iCaretPosition }, m_sText.length() * 2 + sizeof(History));
	}

	bool CBuiltInTextInput::ApplyLengthLimit()
	{
		if (m_iMaxLength > 0 && (int)m_sText.length() > m_iMaxLength)
		{
			m_sText = m_sText.substr(0, m_iMaxLength);
			m_iCaretPosition = ntl::Min<int>(m_iCaretPosition, (int)m_sText.length());
			m_sSelection.X = ntl::Min<int>(m_sSelection.X, (int)m_sText.length());
			m_sSelection.Y = ntl::Min<int>(m_sSelection.Y, (int)m_sText.length());
			return true;
		}
		return false;
	}

	bool CBuiltInTextInput::DeleteSelectionInternal()
	{
		if (m_sSelection.X == m_sSelection.Y)
			return false;
		Point selection{ NormalizeSelection() };
		m_sText.erase(selection.X, selection.Y - selection.X);
		if (m_iCaretPosition > selection.X && m_iCaretPosition < selection.Y)
			m_iCaretPosition = selection.X;
		else if (m_iCaretPosition >= selection.Y)
			m_iCaretPosition -= selection.Y - selection.X;
		m_sSelection.Y = m_sSelection.X;
		return true;
	}

	Point CBuiltInTextInput::NormalizeSelection()
	{
		return Point{ ntl::Min<int>(m_sSelection.X, m_sSelection.Y), ntl::Max<int>(m_sSelection.X, m_sSelection.Y) };
	}

	float CBuiltInTextInput::CaretToClient(const int value)
	{
		if (value < 0 || !getControl() || !getControl()->getFont() || !getControl()->getForm() || !getControl()->getForm()->getRenderer() ||
			!getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
			return 0;
		IFont *font{ getControl()->getFont() };
		IPlatformFont *pf{ font->getPlatformFont(getControl()->getForm()->getRenderer()) };
		int m{ ntl::Min<int>(value, (int)m_sText.length()) };
		float result{ CalculateTextX() };
		for (int i = 1; i <= m; i++)
			result += pf->getStringSize(m_sText.substr(i - 1, 1), font->Distance).X + font->Distance;
		return result;
	}

	int CBuiltInTextInput::ClientToCaret(const float value)
	{
		if (!getControl() || !getControl()->getFont() || !getControl()->getForm() || !getControl()->getForm()->getRenderer() ||
			!getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
			return 0;
		IFont *font{ getControl()->getFont() };
		IPlatformFont *pf{ font->getPlatformFont(getControl()->getForm()->getRenderer()) };
		float x{ CalculateTextX() };
		if (ntl::IsLessOrEqual<float>(value, x))
			return 0;
		for (int index = 0; index < (int)m_sText.length(); index++)
		{
			float char_w{ pf->getStringSize(m_sText.substr(index, 1), font->Distance).X };
			if (ntl::IsLess<float>(value - x, char_w * 0.5f))
				return index;
			x += char_w;
		}
		return (int)m_sText.length();
	}

	float CBuiltInTextInput::CalculateTextX()
	{
		float x;
		switch (m_eAlign)
		{
		case TextAlign::Left:
			x = m_fScroll;
			break;
		case TextAlign::Right:
			x = getWidth() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(m_sText, getControl()->getFont()->Distance).X + m_fScroll;
			break;
		default:
			x = (getWidth() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(m_sText, getControl()->getFont()->Distance).X) * 0.5f + m_fScroll;
			break;
		}
		return x;
	}

	float CBuiltInTextInput::CalculateTextY()
	{
		return (getHeight() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(L"Wy", getControl()->getFont()->Distance).Y) * 0.5f;
	}

	float CBuiltInTextInput::CalculatePlaceholderX()
	{
		float x;
		switch (m_eAlign)
		{
		case TextAlign::Left:
			x = m_fScroll;
			break;
		case TextAlign::Right:
			x = getWidth() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(m_sPlaceholder, getControl()->getFont()->Distance).X + m_fScroll;
			break;
		default:
			x = (getWidth() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(m_sPlaceholder, getControl()->getFont()->Distance).X) * 0.5f + m_fScroll;
			break;
		}
		return x;
	}

	float CBuiltInTextInput::CalculatePlaceholderY()
	{
		return (getHeight() - getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer())->getStringSize(L"Wy", getControl()->getFont()->Distance).Y) * 0.5f;
	}
#pragma endregion

#pragma region Paint
	void CBuiltInTextInput::Render(const bool last_pass, const Mat4f &matrix, const Block *block)
	{
		if (!last_pass && ntl::IsGreater<float>(getWidth(), 0) && ntl::IsGreater<float>(getHeight(), 0) && getControl() && getControl()->getFont() && getControl()->getForm() &&
			getControl()->getForm()->getRenderer() && getControl()->getFont()->getPlatformFont(getControl()->getForm()->getRenderer()))
		{
			IRenderer *renderer{ getControl()->getForm()->getRenderer() };
			ITexture *clip{ renderer->CreateTexture(ntl::Round<int>(getWidth()), ntl::Round<int>(getHeight()), 1, TextureFormat::RGBA, true) };
			if (clip)
			{
				CStoreBlock s_block{ renderer };
				CStorePrimitiveMatrix s_matrix{ renderer };
				IBaseTexture *old{ renderer->ActiveTarget };
				renderer->ActivateTarget(clip);
				renderer->Clear(Color{ 0, 0, 0, 0 });

				IFont *font{ getControl()->getFont() };
				State state{ getState() };
				if (!m_sText.empty())
				{
					RenderShadow(renderer, state, clip, block, font);
					RenderText(renderer, state, clip, block, font);
					RenderSelection(renderer, state, clip, block, font);
				}
				else if (!m_sPlaceholder.empty())
					RenderPlaceholder(renderer, state, clip, block, font);
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
					RenderCaret(renderer, state, clip, block, font);
				}
				else
					RenderCaret(renderer, state, clip, block, font);
				renderer
					->ActivateTarget(old)
					->ActivateBlock(block)
					->ActivatePrimitiveMatrix(matrix)
					->DrawImage(clip, 1);
				clip->Release();
			}
		}
	}

	void CBuiltInTextInput::RenderShadow(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font)
	{
		if (m_aShadowColor[(int)state].A > 0 || font->ShadowColor.A > 0)
		{
			ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(getWidth() + float(2 * m_aShadowRadius[(int)state])), ntl::Round<int>(getHeight() + float(2 * m_aShadowRadius[(int)state])), 1, TextureFormat::RGBA, true) };
			if (shadow)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				// Draw into shadow texture
				renderer
					->ActivateTarget(shadow)
					->Clear(Color{ 0, 0, 0, 0 })
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(CalculateTextX() + (float)m_aShadowRadius[(int)state]), std::round(CalculateTextY() + (float)m_aShadowRadius[(int)state]), 0))
					->DrawText(m_sText, font->getPlatformFont(renderer), font->Distance, m_aShadowColor[(int)state].A > 0 ? m_aShadowColor[(int)state] : font->ShadowColor)
					->ActivatePrimitiveMatrix(nullptr)
					->BlurImage(shadow, m_aShadowRadius[(int)state], BlurType::Gaussian)
					// Draw shadow into clip texture
					->ActivateTarget(clip)
					->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_aShadowShift[(int)state].X - (float)m_aShadowRadius[(int)state], m_aShadowShift[(int)state].Y - (float)m_aShadowRadius[(int)state], 0))
					->DrawImage(shadow, 1);
				shadow->Release();
			}
		}
	}

	void CBuiltInTextInput::RenderText(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font)
	{
		if (m_aTextColor[(int)state].A > 0 || font->Color.A > 0)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(CalculateTextX()), std::round(CalculateTextY()), 0))
				->DrawText(m_sText, font->getPlatformFont(renderer), font->Distance, m_aTextColor[(int)state].A > 0 ? m_aTextColor[(int)state] : font->Color);
		}
	}

	void CBuiltInTextInput::RenderPlaceholder(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font)
	{
		if (m_aPlaceholderColor[(int)state].A > 0)
		{
			CStorePrimitiveMatrix s_matrix{ renderer };
			renderer
				->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(CalculatePlaceholderX()), std::round(CalculatePlaceholderY()), 0))
				->DrawText(m_sPlaceholder, font->getPlatformFont(renderer), font->Distance, m_aPlaceholderColor[(int)state]);
		}
	}

	void CBuiltInTextInput::RenderSelection(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font)
	{
		if (m_sSelection.X != m_sSelection.Y)
		{
			Point selection{ NormalizeSelection() };
			RectF rect_selection{ CaretToClient(selection.X), 0, CaretToClient(selection.Y), getHeight() };
			if (rect_selection.Right >= 0 && rect_selection.Left < getWidth())
			{
				if (m_aSelectionBackgroundColor[(int)state].A > 0)
					renderer->DrawRectangle(rect_selection, m_aSelectionBackgroundColor[(int)state]);
				if (m_aSelectionShadowColor[(int)state].A > 0 || m_aSelectionTextColor[(int)state].A > 0 || font->Color.A > 0)
				{
					ITexture *text{ renderer->CreateTexture(ntl::Round<int>(rect_selection.width()), ntl::Round<int>(rect_selection.height()), 1, TextureFormat::RGBA, true) };
					if (text)
					{
						CStorePrimitiveMatrix s_matrix{ renderer };
						if (m_aSelectionShadowColor[(int)state].A > 0 || font->ShadowColor.A > 0)
						{
							ITexture *shadow{ renderer->CreateTexture(ntl::Round<int>(rect_selection.width() + float(2 * m_aShadowRadius[(int)state])), ntl::Round<int>(rect_selection.height() + float(2 * m_aShadowRadius[(int)state])), 1, TextureFormat::RGBA, true) };
							if (shadow)
							{
								// Draw shadow
								renderer
									->ActivateTarget(shadow)
									->Clear(Color{ 0, 0, 0, 0 })
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(CalculateTextX() - rect_selection.Left + (float)m_aShadowRadius[(int)state]), std::round(CalculateTextY() + (float)m_aShadowRadius[(int)state]), 0))
									->DrawText(m_sText, font->getPlatformFont(renderer), font->Distance, m_aSelectionShadowColor[(int)state].A > 0 ? m_aSelectionShadowColor[(int)state] : font->ShadowColor)
									->ActivatePrimitiveMatrix(nullptr)
									->BlurImage(shadow, m_aShadowRadius[(int)state], BlurType::Gaussian)
									// Draw shadow image to selection rectangle image
									->ActivateTarget(text)
									->Clear(Color{ 0, 0, 0, 0 })
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(m_aShadowShift[(int)state].X - (float)m_aShadowRadius[(int)state], m_aShadowShift[(int)state].Y - (float)m_aShadowRadius[(int)state], 0))
									->DrawImage(shadow, 1);
								shadow->Release();
								// Draw selection rectangle image to clip
								renderer
									->ActivateTarget(clip)
									->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect_selection.Left, rect_selection.Top, 0))
									->DrawImage(text, 1);
							}
						}

						// Render text to selection image
						renderer
							->ActivateTarget(text)
							->Clear(Color{ 0, 0, 0, 0 })
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(std::round(CalculateTextX() - rect_selection.Left), std::round(CalculateTextY()), 0))
							->DrawText(m_sText, font->getPlatformFont(renderer), font->Distance, m_aSelectionTextColor[(int)state].A > 0 ? m_aSelectionTextColor[(int)state] : font->Color)
							// Render selection image into clip
							->ActivateTarget(clip)
							->ActivatePrimitiveMatrix(ntl::Mat4Translate<float>(rect_selection.Left, rect_selection.Top, 0))
							->DrawImage(text, 1);

						text->Release();
					}
				}
			}
		}
	}

	void CBuiltInTextInput::RenderCaret(IRenderer *renderer, const State state, ITexture *clip, const Block *block, IFont *font)
	{
		if ((state == State::Focused || state == State::FocusedHovered) && getControl()->getForm()->getCaret())
		{
			PointF size{ 1, getHeight() };
			if (m_bReplacing)
			{
				if (getControl()->getForm()->getCaret()->isInversed())
				{
					String s{ m_sText.substr(m_iCaretPosition, 1) };
					size.X = font->getPlatformFont(renderer)->getStringSize(s.empty() ? L" " : s, 0).X;
				}
				else
					size.X = 2;
			}
			getControl()->getForm()->getCaret()->setSize(size);
			getControl()->getForm()->getCaret()->Render(ntl::Mat4Translate<float>(CaretToClient(m_iCaretPosition), 0, 0));
		}
	}
#pragma endregion
}