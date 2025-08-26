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
	namespace standard
	{
	#pragma region Constructor & destructor
		CCustomStringGridService::CCustomStringGridService(CCustomStringGrid *control) :
			CCustomDrawGridService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		PointF CCustomStringGridService::FormToTextInput(const PointF &position)
		{
			PointF cell_pos{ m_pControl->getCellPosition(m_pControl->m_sFocusedCell.X, m_pControl->m_sFocusedCell.Y) };
			PointF p{ m_pControl->FormToLocal(position) };
			return PointF{
				p.X - cell_pos.X - m_pControl->m_aCells[m_pControl->m_sFocusedCell.Y][m_pControl->m_sFocusedCell.X].Padding.Left,
				p.Y - cell_pos.Y - m_pControl->m_aCells[m_pControl->m_sFocusedCell.Y][m_pControl->m_sFocusedCell.X].Padding.Top
			};
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomStringGridService::NotifyOnAttach()
		{
			CCustomDrawGridService::NotifyOnAttach();
			if (m_pControl->getForm() && m_pControl->m_pTextInput)
				m_pControl->m_pTextInput->NotifyOnAttach();
		}

		void CCustomStringGridService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pTextInput)
				m_pControl->m_pTextInput->NotifyOnFreeResources();
			CCustomDrawGridService::NotifyOnFreeResources();
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomStringGridService::NotifyOnParentFontChange()
		{
			m_pControl->ForceRepaint();
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomStringGridService::NotifyOnFontChange()
		{
			m_pControl->ForceRepaint();
		}

		void CCustomStringGridService::NotifyOnKillFocus()
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnKillFocus();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CCustomStringGridService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getTextInput()->NotifyOnKeyDown(m.Key, ctrl, alt, shift, numlock))
				{
					m_pControl->ForceRepaint();
					return;
				}
				Point new_active{ m_pControl->m_sFocusedCell.X + 1, m_pControl->m_sFocusedCell.Y };
				switch (m.Key)
				{
				case Key::Escape:
				case Key::Return:
				case Key::Separator:
					m_pControl->CancelFocus(m.Key != Key::Escape, this);
					if ((m.Key == Key::Return || m.Key == Key::Separator) && new_active.X < m_pControl->getColumns())
						if (m_pControl->setCellActive(new_active.X, new_active.Y, true))
						{
							m_pControl->setCellSelected(new_active.X - 1, new_active.Y, false);
							m_pControl->ScrollToActiveCell();
						}
					m_pControl->ForceRepaint();
					break;
				default:
					break;
				}
			}
			if (m_pControl->m_sFocusedCell.X < 0 && m.Key == Key::Delete)
			{
				Point active{ m_pControl->getActiveCell() };
				if (active.X >= 0 && m_pControl->m_aCells[active.Y][active.X].Editable && !m_pControl->m_aCells[active.Y][active.X].Text.empty())
				{
					bool allowed{ true };
					NotifyOnCellChange(active.X, active.Y, L"", allowed);
					if (allowed)
					{
						if (m_pControl->OnChangeCell)
							m_pControl->OnChangeCell(m_pControl, active.X, active.Y, L"", allowed);
						if (allowed)
						{
							m_pControl->m_aCells[active.Y][active.X].Text = L"";
							m_pControl->ForceRepaint();
						}
					}
				}
			}
			CCustomDrawGridService::NotifyOnKeyDown(m, processed);
		}

		void CCustomStringGridService::NotifyOnKeyUp(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getTextInput()->NotifyOnKeyUp(m.Key, ctrl, alt, shift, numlock))
					m_pControl->ForceRepaint();
			}
		}

		void CCustomStringGridService::NotifyOnChar(const MessageChar &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (m_pControl->getTextInput()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock))
					m_pControl->ForceRepaint();
			}
			else
			{
				Point active{ m_pControl->getActiveCell() };
				if (active.X >= 0 && m_pControl->m_aCells[active.Y][active.X].Editable && !std::iscntrl(m.Char, std::locale()))
				{
					m_pControl->ActivateFocus(active, this);
					bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
					Application->Keyboard->getControlKeys(ctrl, alt, shift);
					m_pControl->getTextInput()->NotifyOnChar(m.Char, ctrl, alt, shift, numlock);
					m_pControl->ForceRepaint();
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCustomStringGridService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseHover(FormToTextInput(m.Position)))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnMouseHover(m);
		}

		void CCustomStringGridService::NotifyOnMouseLeave()
		{
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseLeave())
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnMouseLeave();
		}

		void CCustomStringGridService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				if (m_pControl->getTextInput()->NotifyOnMouseMove(FormToTextInput(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pControl->ForceRepaint();
				if (m_pControl->getTextInput()->isDown())
					return;
			}
			CCustomDrawGridService::NotifyOnMouseMove(m, processed);
		}

		void CCustomStringGridService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				if (m_pControl->getTextInput()->NotifyOnMouseLeftDown(FormToTextInput(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pControl->ForceRepaint();
				if (m_pControl->getTextInput()->isDown())
					return;
			}
			CCustomDrawGridService::NotifyOnLeftMouseButtonDown(m, processed);
		}

		void CCustomStringGridService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				if (m_pControl->getTextInput()->NotifyOnMouseLeftUp(FormToTextInput(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
					m_pControl->ForceRepaint();
			}
			CCustomDrawGridService::NotifyOnLeftMouseButtonUp(m, processed);
		}

		void CCustomStringGridService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0)
			{
				if (m_pControl->getTextInput()->NotifyOnMouseLeftDoubleClick(FormToTextInput(m.Position), m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
				{
					m_pControl->ForceRepaint();
					return;
				}
			}
			CCustomDrawGridService::NotifyOnLeftMouseButtonDoubleClick(m, processed);
			if (m_pControl->m_sFocusedCell.X < 0)
			{
				Point active{ m_pControl->getActiveCell() };
				if (active.X >= 0 && m_pControl->m_aCells[active.Y][active.X].Editable)
				{
					m_pControl->ActivateFocus(active, this);
					m_pControl->ForceRepaint();
				}
			}
		}

		void CCustomStringGridService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseRightDown(FormToTextInput(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnRightMouseButtonDown(m, processed);
		}

		void CCustomStringGridService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseRightUp(FormToTextInput(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnRightMouseButtonUp(m, processed);
		}

		void CCustomStringGridService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseRightDoubleClick(FormToTextInput(m.Position), m.Left, m.Middle, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnRightMouseButtonDoubleClick(m, processed);
		}

		void CCustomStringGridService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseMiddleDown(FormToTextInput(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnMiddleMouseButtonDown(m, processed);
		}

		void CCustomStringGridService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseMiddleUp(FormToTextInput(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnMiddleMouseButtonUp(m, processed);
		}

		void CCustomStringGridService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseMiddleDoubleClick(FormToTextInput(m.Position), m.Left, m.Right, m.Ctrl, m.Alt, m.Shift))
				m_pControl->ForceRepaint();
			CCustomDrawGridService::NotifyOnMiddleMouseButtonDoubleClick(m, processed);
		}

		void CCustomStringGridService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseVerticalWheel(FormToTextInput(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
			{
				m_pControl->ForceRepaint();
				return;
			}
			CCustomDrawGridService::NotifyOnMouseVerticalWheel(m, processed);
		}

		void CCustomStringGridService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnMouseHorizontalWheel(FormToTextInput(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
			{
				m_pControl->ForceRepaint();
				return;
			}
			CCustomDrawGridService::NotifyOnMouseHorizontalWheel(m, processed);
		}
	#pragma endregion

	#pragma region Cell status change notifications
		void CCustomStringGridService::NotifyOnSelectCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnSelectCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnDeselectCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnDeselectCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnActivateCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnActivateCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnDeactivateCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnDeactivateCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnEnableCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnEnableCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnDisableCell(const int column, const int row, IListItem *item)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnDisableCell(column, row, item);
		}

		void CCustomStringGridService::NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnMouseDownCell(column, row, item, position, left, middle, right, ctrl, alt, shift);
		}

		void CCustomStringGridService::NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnMouseUpCell(column, row, item, position, left, middle, right, ctrl, alt, shift);
		}

		void CCustomStringGridService::NotifyOnMouseDownCancel()
		{
			m_pControl->CancelFocus(true, this);
			CCustomDrawGridService::NotifyOnMouseDownCancel();
		}

		void CCustomStringGridService::NotifyOnCellChange(const int column, const int row, const String &value, bool &allowed)
		{
			// Nothing
		}

		void CCustomStringGridService::NotifyOnSetFocusCell(const int column, const int row)
		{
			// Nothing
		}

		void CCustomStringGridService::NotifyOnKillFocusCell(const int column, const int row)
		{
			// Nothing
		}
	#pragma endregion

	#pragma region Clipboard notifications
		void CCustomStringGridService::NotifyOnPasteString(const MessagePasteString &m)
		{
			if (m_pControl->m_sFocusedCell.X >= 0 && m_pControl->getTextInput()->NotifyOnPasteString(m.Text))
				m_pControl->ForceRepaint();
		}
	#pragma endregion
	}
}