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
		CCustomGridService::CCustomGridService(CCustomGrid *control) :
			CControlService(control),
			m_pControl{ control }
		{

		}
	#pragma endregion

	#pragma region Helpers
		bool CCustomGridService::ProcessMouseMove(const PointF &p, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			// Process in "down" mode
			switch (m_pControl->m_eDownElement)
			{
			case CCustomGrid::Element::VScroll:
				return m_pControl->getVScroll()->NotifyOnMouseMove(p, left, middle, right, ctrl, alt, shift);
			case CCustomGrid::Element::HScroll:
				return m_pControl->getHScroll()->NotifyOnMouseMove(p, left, middle, right, ctrl, alt, shift);
			case CCustomGrid::Element::Cell:
				return ProcessMouseMoveDownCell(p);
			case CCustomGrid::Element::RightBorder:
				return ProcessMouseMoveDownRightBorder(p);
			case CCustomGrid::Element::BottomBorder:
				return ProcessMouseMoveDownBottomBorder(p);
			default:
				break;
			}
			// Process in normal mode
			bool changed{ m_pControl->UpdateHoveredElement(p) };
			switch (m_pControl->m_eHoveredElement)
			{
			case CCustomGrid::Element::VScroll:
				return m_pControl->getVScroll()->NotifyOnMouseMove(PointF{ p.X - m_pControl->getVScroll()->getLeft(), p.Y - m_pControl->getVScroll()->getTop() }, left, middle, right, ctrl, alt, shift) || changed;
			case CCustomGrid::Element::HScroll:
				return m_pControl->getHScroll()->NotifyOnMouseMove(PointF{ p.X - m_pControl->getHScroll()->getLeft(), p.Y - m_pControl->getHScroll()->getTop() }, left, middle, right, ctrl, alt, shift) || changed;
			case CCustomGrid::Element::Cell:
				changed = NotifyOnMouseMoveCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, m_pControl->m_aCells[m_pControl->m_sHoveredCell.Y][m_pControl->m_sHoveredCell.X].Item, p, left, middle, right, ctrl, alt, shift) || changed;
				if (m_pControl->OnMouseMoveCell)
				{
					bool repaint_required{ false };
					m_pControl->OnMouseMoveCell(m_pControl, m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, m_pControl->m_aCells[m_pControl->m_sHoveredCell.Y][m_pControl->m_sHoveredCell.X].Item, p, left, middle, right, ctrl, alt, shift, repaint_required);
					changed = repaint_required || changed;
				}
				return changed;
			default:
				break;
			}
			return changed;
		}

		bool CCustomGridService::ProcessMouseMoveDownCell(const PointF &p)
		{
			bool changed{ false };
			if (!m_pControl->m_aColumns[m_pControl->m_sDownCell.X].Fixed && !m_pControl->m_aRows[m_pControl->m_sDownCell.Y].Fixed)
			{
				Point coords{ m_pControl->getCellAtPosition(p, true) };
				if (coords.X >= 0 && coords.Y >= 0)
				{
					Rect cells{ // Cells to be selected(if possible)
						m_pControl->m_bMultiselect ? ntl::Min<int>(coords.X, m_pControl->m_sDownCell.X) : coords.X,
						m_pControl->m_bMultiselect ? ntl::Min<int>(coords.Y, m_pControl->m_sDownCell.Y) : coords.Y,
						m_pControl->m_bMultiselect ? ntl::Max<int>(coords.X, m_pControl->m_sDownCell.X) : coords.X,
						m_pControl->m_bMultiselect ? ntl::Max<int>(coords.Y, m_pControl->m_sDownCell.Y) : coords.Y };
					changed = SelectRange(cells);
					if (!m_pControl->m_bMultiselect && coords != m_pControl->m_sActiveCell &&
						m_pControl->m_aRows[coords.Y].Enabled && !m_pControl->m_aRows[coords.Y].Fixed &&
						m_pControl->m_aColumns[coords.X].Enabled && !m_pControl->m_aColumns[coords.X].Fixed &&
						m_pControl->m_aCells[coords.Y][coords.X].Enabled)
					{
						if (m_pControl->m_sActiveCell.X >= 0)
							changed = m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this) || changed;
						changed = m_pControl->ActivateCell(coords.X, coords.Y, this) || changed;
					}
					m_pControl->m_sSelectTo = coords;
				}
			}
			return changed;
		}

		bool CCustomGridService::SelectRange(const Rect &range)
		{
			bool changed{ false };
			m_pControl->m_bIgnoreItems = true;
			// Select/deselect & activate/deactivate cells
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
				for (int x = 0; x < (int)m_pControl->m_aColumns.size(); x++)
					if (x >= range.Left && x <= range.Right && y >= range.Top && y <= range.Bottom)
					{
						if (m_pControl->m_aCells[y][x].Enabled && !m_pControl->m_aRows[y].Fixed && m_pControl->m_aRows[y].Enabled && !m_pControl->m_aColumns[x].Fixed && m_pControl->m_aColumns[x].Enabled)
							changed = m_pControl->SelectCell(x, y, this) || changed;
					}
					else if (m_pControl->m_aCells[y][x].Enabled && !m_pControl->m_aRows[y].Fixed && m_pControl->m_aRows[y].Enabled && !m_pControl->m_aColumns[x].Fixed && m_pControl->m_aColumns[x].Enabled)
						changed = m_pControl->DeselectCell(x, y, this) || changed;
			m_pControl->m_bIgnoreItems = false;
			return changed;
		}

		bool CCustomGridService::ProcessMouseMoveDownRightBorder(const PointF &p)
		{
			// Find where column is in control coordinate space
			float start_x{ m_pControl->m_sBorderWidth.Left + m_pControl->m_sPadding.Left - (m_pControl->m_aColumns[m_pControl->m_sDownCell.X].Fixed ? 0 : m_pControl->m_sScroll.X) };
			for (int x = 0; x < m_pControl->m_sDownCell.X; x++)
				start_x += m_pControl->m_aColumns[x].Width + m_pControl->m_fGridWidth;
			float expected_width{ ntl::Max<float>(0, p.X - start_x - m_fBorderDownShift) };
			if (ntl::IsNotEqual<float>(expected_width, m_pControl->m_aColumns[m_pControl->m_sDownCell.X].Width))
			{
				m_pControl->m_aColumns[m_pControl->m_sDownCell.X].Width = expected_width;
				m_pControl->Update();
			}
			return false; // Return false because Update() will do repaint itself
		}

		bool CCustomGridService::ProcessMouseMoveDownBottomBorder(const PointF &p)
		{
			// Find where row is in control coordinate space
			float start_y{ m_pControl->m_sBorderWidth.Top + m_pControl->m_sPadding.Top - (m_pControl->m_aRows[m_pControl->m_sDownCell.Y].Fixed ? 0 : m_pControl->m_sScroll.Y) };
			for (int y = 0; y < m_pControl->m_sDownCell.Y; y++)
				start_y += m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
			float expected_height{ ntl::Max<float>(0, p.Y - start_y - m_fBorderDownShift) };
			if (ntl::IsNotEqual<float>(expected_height, m_pControl->m_aRows[m_pControl->m_sDownCell.Y].Height))
			{
				m_pControl->m_aRows[m_pControl->m_sDownCell.Y].Height = expected_height;
				m_pControl->Update();
			}
			return false; // Return false because Update() will do repaint itself
		}

		bool CCustomGridService::isHoveredCellEnabled()
		{
			return
				m_pControl->m_aColumns[m_pControl->m_sHoveredCell.X].Enabled && // Column should be enabled
				m_pControl->m_aRows[m_pControl->m_sHoveredCell.Y].Enabled && // Row should be enabled
				m_pControl->m_aCells[m_pControl->m_sHoveredCell.Y][m_pControl->m_sHoveredCell.X].Enabled; // Cell itself should be enabled
		}

		Point CCustomGridService::FindFirstActivatableCell()
		{
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
				if (m_pControl->m_aRows[y].Enabled && !m_pControl->m_aRows[y].Fixed)
					for (int x = 0; x < (int)m_pControl->m_aColumns.size(); x++)
						if (m_pControl->m_aColumns[x].Enabled && !m_pControl->m_aColumns[x].Fixed && m_pControl->m_aCells[y][x].Enabled)
							return Point{ x, y };
			return Point{ -1, -1 };
		}

		bool CCustomGridService::isCellActivatable(const int column, const int row)
		{
			return
				m_pControl->m_aRows[row].Enabled && !m_pControl->m_aRows[row].Fixed &&
				m_pControl->m_aColumns[column].Enabled && !m_pControl->m_aColumns[column].Fixed &&
				m_pControl->m_aCells[row][column].Enabled;
		}

		bool CCustomGridService::ActivateFirstCell()
		{
			m_pControl->m_sActiveCell = FindFirstActivatableCell();
			if (m_pControl->m_sActiveCell.X < 0) // Exit if there are no available cells to activate
				return false;
			m_pControl->m_bIgnoreItems = true;
			m_pControl->ActivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
			m_pControl->m_sSelectTo = m_pControl->m_sActiveCell;
			SelectRange(Rect{ m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y });
			m_pControl->ScrollToCell(m_pControl->m_sActiveCell);
			m_pControl->m_bIgnoreItems = false;
			return true;
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomGridService::NotifyOnAttach()
		{
			if (m_pControl->getForm())
			{
				if (m_pControl->m_pVScroll)
					m_pControl->m_pVScroll->NotifyOnAttach();
				if (m_pControl->m_pHScroll)
					m_pControl->m_pHScroll->NotifyOnAttach();
				m_pControl->Update();
			}
		}

		void CCustomGridService::NotifyOnDetaching()
		{
			m_pControl->CancelMouseDown(false, this);
		}

		void CCustomGridService::NotifyOnFreeResources()
		{
			if (m_pControl->m_pVScroll)
				m_pControl->m_pVScroll->NotifyOnFreeResources();
			if (m_pControl->m_pHScroll)
				m_pControl->m_pHScroll->NotifyOnFreeResources();
			if (m_pControl->m_pCanvas)
			{
				m_pControl->m_pCanvas->Release();
				m_pControl->m_pCanvas = nullptr;
			}
			if (m_pControl->m_hScrollTimer)
			{
				m_pControl->getForm()->DeleteTimer(m_pControl->m_hScrollTimer);
				m_pControl->m_hScrollTimer = 0;
			}
		}
	#pragma endregion

	#pragma region Notifications from parent control
		void CCustomGridService::NotifyOnParentStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}
	#pragma endregion

	#pragma region State change notifications
		void CCustomGridService::NotifyOnDisable()
		{
			m_pControl->CancelMouseDown(false, this);
			m_pControl->Update();
		}

		void CCustomGridService::NotifyOnResize()
		{
			m_pControl->Update();
		}

		void CCustomGridService::NotifyOnStyleChange()
		{
			if (m_pControl->getStyle())
			{
				m_pControl->UpdateFromStyle(m_pControl->getStyle());
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
			}
		}

		void CCustomGridService::NotifyOnSetFocus(const MessageFocus &m)
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCustomGridService::NotifyOnKillFocus()
		{
			if (m_pControl->m_pCanvas)
				m_pControl->m_pCanvas->setValid(false);
			m_pControl->Repaint(false);
		}

		void CCustomGridService::NotifyOnSetCaptureMouse()
		{
			if (m_pControl->m_eDownElement == CCustomGrid::Element::Cell)
				m_pControl->m_hScrollTimer = m_pControl->getForm()->CreateTimer(this, m_pControl->m_fScrollInterval);
		}

		void CCustomGridService::NotifyOnKillCaptureMouse()
		{
			m_pControl->CancelMouseDown(false, this);
			if (m_pControl->UpdateHoveredElement())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}
	#pragma endregion

	#pragma region Paint notifications
		void CCustomGridService::NotifyOnPaint(const MessagePaint &m, bool &draw_children)
		{
			if (!m.LastPass && ntl::IsGreater<float>(m_pControl->getWidth(), 0) && ntl::IsGreater<float>(m_pControl->getHeight(), 0))
				m_pControl->Render();
		}
	#pragma endregion

	#pragma region Keyboard input notifications
		void CCustomGridService::NotifyOnKeyDown(const MessageKey &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && !m_pControl->isCaptureMouse() && m_pControl->m_aRows.size() > 0 && m_pControl->m_aColumns.size() > 0)
			{
				bool ctrl, alt, shift, numlock{ Application->Keyboard->isToggled(Key::NumLock) };
				Application->Keyboard->getControlKeys(ctrl, alt, shift);
				if (!alt)
				{
					bool changed{ false };
					switch (m.Key)
					{
					case Key::Left:
					case Key::Numpad4:
						if (m.Key == Key::Left || (m.Key == Key::Numpad4 && !numlock))
							if (ProcessKeyLeft(shift))
								changed = true;
						break;
					case Key::Right:
					case Key::Numpad6:
						if (m.Key == Key::Right || (m.Key == Key::Numpad6 && !numlock))
							if (ProcessKeyRight(shift))
								changed = true;
						break;
					case Key::Up:
					case Key::Numpad8:
						if (m.Key == Key::Up || (m.Key == Key::Numpad8 && !numlock))
							if (ProcessKeyUp(shift))
								changed = true;
						break;
					case Key::Down:
					case Key::Numpad2:
						if (m.Key == Key::Down || (m.Key == Key::Numpad2 && !numlock))
							if (ProcessKeyDown(shift))
								changed = true;
						break;
					case Key::Home:
					case Key::Numpad7:
						if (m.Key == Key::Home || (m.Key == Key::Numpad7 && !numlock))
							if (ProcessKeyHome(ctrl, shift))
								changed = true;
						break;
					case Key::End:
					case Key::Numpad1:
						if (m.Key == Key::End || (m.Key == Key::Numpad1 && !numlock))
							if (ProcessKeyEnd(ctrl, shift))
								changed = true;
						break;
					case Key::Prior:
					case Key::Numpad9:
						if (m.Key == Key::Prior || (m.Key == Key::Numpad9 && !numlock))
							if (ProcessKeyPageUp(shift))
								changed = true;
						break;
					case Key::Next:
					case Key::Numpad3:
						if (m.Key == Key::Next || (m.Key == Key::Numpad3 && !numlock))
							if (ProcessKeyPageDown(shift))
								changed = true;
						break;
					case Key::A:
						if (ctrl && !shift && ProcessKeySelectAll())
							changed = true;
						break;
					default:
						break;
					}
					if (changed)
					{
						if (m_pControl->m_pCanvas)
							m_pControl->m_pCanvas->setValid(false);
						m_pControl->Repaint(false);
					}
				}
			}
		}
	#pragma endregion

	#pragma region Mouse input notifications
		void CCustomGridService::NotifyOnMouseHover(const MessagePosition &m)
		{
			if (m_pControl->isEnabled(true) && !m_pControl->isCaptureMouse() && m_pControl->UpdateHoveredElement(m_pControl->FormToLocal(m.Position)))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGridService::NotifyOnMouseLeave()
		{
			if (m_pControl->isEnabled(true) && !m_pControl->isCaptureMouse() && m_pControl->UpdateHoveredElement())
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGridService::NotifyOnMouseMove(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (m_pControl->isEnabled(true) && ProcessMouseMove(m_pControl->FormToLocal(m.Position), m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift))
			{
				if (m_pControl->m_pCanvas)
					m_pControl->m_pCanvas->setValid(false);
				m_pControl->Repaint(false);
			}
		}

		void CCustomGridService::NotifyOnLeftMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			processed = true;
			if (!m.Middle && !m.Right && m_pControl->isEnabled(true) && !m_pControl->isCaptureMouse())
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				bool changed{ false };
				switch (m_pControl->m_eHoveredElement)
				{
				case CCustomGrid::Element::VScroll:
					changed = m_pControl->getVScroll()->NotifyOnMouseLeftDown(PointF{ p.X - m_pControl->getVScroll()->getLeft(), p.Y - m_pControl->getVScroll()->getTop() }, false, false, m.Ctrl, m.Alt, m.Shift);
					break;
				case CCustomGrid::Element::HScroll:
					changed = m_pControl->getHScroll()->NotifyOnMouseLeftDown(PointF{ p.X - m_pControl->getHScroll()->getLeft(), p.Y - m_pControl->getHScroll()->getTop() }, false, false, m.Ctrl, m.Alt, m.Shift);
					break;
				case CCustomGrid::Element::Cell:
					if (isHoveredCellEnabled())
					{
						if (!m_pControl->m_aColumns[m_pControl->m_sHoveredCell.X].Fixed && !m_pControl->m_aRows[m_pControl->m_sHoveredCell.Y].Fixed)
						{
							m_pControl->m_bIgnoreItems = true;
							if (m.Ctrl)
							{
								if (m_pControl->m_aCells[m_pControl->m_sHoveredCell.Y][m_pControl->m_sHoveredCell.X].Selected)
									m_pControl->DeselectCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, this);
								else
								{
									m_pControl->SelectCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, this);
									if (!m_pControl->m_bMultiselect && m_pControl->m_sActiveCell != m_pControl->m_sHoveredCell)
									{
										if (m_pControl->m_sActiveCell.X >= 0)
											m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
										m_pControl->ActivateCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, this);
										m_pControl->m_sSelectTo = m_pControl->m_sActiveCell;
									}
								}
							}
							else if (m.Shift)
							{
								Rect range{
									(m_pControl->m_bMultiselect && !m.Ctrl && m.Shift && m_pControl->m_sActiveCell.X >= 0) ? ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sHoveredCell.X) : m_pControl->m_sHoveredCell.X,
									(m_pControl->m_bMultiselect && !m.Ctrl && m.Shift && m_pControl->m_sActiveCell.X >= 0) ? ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sHoveredCell.Y) : m_pControl->m_sHoveredCell.Y,
									(m_pControl->m_bMultiselect && !m.Ctrl && m.Shift && m_pControl->m_sActiveCell.X >= 0) ? ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sHoveredCell.X) : m_pControl->m_sHoveredCell.X,
									(m_pControl->m_bMultiselect && !m.Ctrl && m.Shift && m_pControl->m_sActiveCell.X >= 0) ? ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sHoveredCell.Y) : m_pControl->m_sHoveredCell.Y };
								SelectRange(range);
								if (!m_pControl->m_bMultiselect && m_pControl->m_sActiveCell != m_pControl->m_sHoveredCell)
								{
									if (m_pControl->m_sActiveCell.X >= 0)
										m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
									m_pControl->ActivateCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, this);
								}
								m_pControl->m_sSelectTo = m_pControl->m_sHoveredCell;
							}
							else
							{
								Rect range{ m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y };
								SelectRange(range);
								if (m_pControl->m_sActiveCell != m_pControl->m_sHoveredCell)
								{
									if (m_pControl->m_sActiveCell.X >= 0)
										m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
									m_pControl->ActivateCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, this);
								}
								m_pControl->m_sSelectTo = m_pControl->m_sHoveredCell;
							}
							m_pControl->m_bIgnoreItems = false;
						}
						NotifyOnMouseDownCell(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y, m_pControl->m_aCells[m_pControl->m_sHoveredCell.Y][m_pControl->m_sHoveredCell.X].Item, p, true, false, false, m.Ctrl, m.Alt, m.Shift);
						changed = true;
					}
					break;
				case CCustomGrid::Element::RightBorder:
					if (m_pControl->m_aColumns[m_pControl->m_sHoveredCell.X].Resizable)
					{
						m_fBorderDownShift = p.X - m_pControl->getCellPosition(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y).X - m_pControl->m_aColumns[m_pControl->m_sHoveredCell.X].Width;
						changed = true;
					}
					break;
				case CCustomGrid::Element::BottomBorder:
					if (m_pControl->m_aRows[m_pControl->m_sHoveredCell.Y].Resizable)
					{
						m_fBorderDownShift = p.Y - m_pControl->getCellPosition(m_pControl->m_sHoveredCell.X, m_pControl->m_sHoveredCell.Y).Y - m_pControl->m_aRows[m_pControl->m_sHoveredCell.Y].Height;
						changed = true;
					}
					break;
				default:
					break;
				}
				if (changed)
				{
					m_pControl->m_eDownElement = m_pControl->m_eHoveredElement;
					m_pControl->m_sDownCell = m_pControl->m_sHoveredCell;
					m_pControl->getForm()->CaptureMouse(m_pControl, true);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
			else
				m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnLeftMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			processed = true;
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnLeftMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnRightMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnRightMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnRightMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnMiddleMouseButtonDown(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnMiddleMouseButtonUp(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnMiddleMouseButtonDoubleClick(const MessageMouse &m, bool &processed)
		{
			m_pControl->CancelMouseDown(true, this);
		}

		void CCustomGridService::NotifyOnMouseVerticalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_eDownElement == CCustomGrid::Element::None && m_pControl->isEnabled(true))
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				bool changed{ false };
				switch (m_pControl->m_eHoveredElement)
				{
				case CCustomGrid::Element::VScroll:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.Y, 0) &&
						m_pControl->getVScroll()->NotifyOnMouseVerticalWheel(PointF{ p.X - m_pControl->getVScroll()->getLeft(), p.Y - m_pControl->getVScroll()->getTop() }, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pControl->m_sScroll.Y = m_pControl->getVScroll()->getScroll();
						changed = true;
					}
					break;
				case CCustomGrid::Element::HScroll:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.X, 0) &&
						m_pControl->getHScroll()->NotifyOnMouseVerticalWheel(PointF{ p.X - m_pControl->getHScroll()->getLeft(), p.Y - m_pControl->getHScroll()->getTop() }, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, -m.Delta))
					{
						m_pControl->m_sScroll.X = m_pControl->getHScroll()->getScroll();
						changed = true;
					}
					break;
				default:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.Y, 0) &&
						m_pControl->getVScroll()->setScroll(m_pControl->getVScroll()->getScroll() + (m.Delta < 0 ? m_pControl->getVScroll()->getDeltaMedium() : -m_pControl->getVScroll()->getDeltaMedium())))
					{
						m_pControl->UpdateHoveredElement(p);
						m_pControl->m_sScroll.Y = m_pControl->getVScroll()->getScroll();
						changed = true;
					}
				}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}

		void CCustomGridService::NotifyOnMouseHorizontalWheel(const MessageMouseWheel &m, bool &processed)
		{
			processed = true;
			if (m_pControl->m_eDownElement == CCustomGrid::Element::None && m_pControl->isEnabled(true))
			{
				PointF p{ m_pControl->FormToLocal(m.Position) };
				bool changed{ false };
				switch (m_pControl->m_eHoveredElement)
				{
				case CCustomGrid::Element::VScroll:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.Y, 0) &&
						m_pControl->getVScroll()->NotifyOnMouseHorizontalWheel(PointF{ p.X - m_pControl->getVScroll()->getLeft(), p.Y - m_pControl->getVScroll()->getTop() }, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pControl->m_sScroll.Y = m_pControl->getVScroll()->getScroll();
						changed = true;
					}
					break;
				case CCustomGrid::Element::HScroll:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.X, 0) &&
						m_pControl->getHScroll()->NotifyOnMouseHorizontalWheel(PointF{ p.X - m_pControl->getHScroll()->getLeft(), p.Y - m_pControl->getHScroll()->getTop() }, m.Left, m.Middle, m.Right, m.Ctrl, m.Alt, m.Shift, m.Delta))
					{
						m_pControl->m_sScroll.X = m_pControl->getHScroll()->getScroll();
						changed = true;
					}
					break;
				default:
					if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.X, 0) &&
						m_pControl->getHScroll()->setScroll(m_pControl->getHScroll()->getScroll() + (m.Delta > 0 ? m_pControl->getHScroll()->getDeltaMedium() : -m_pControl->getHScroll()->getDeltaMedium())))
					{
						m_pControl->UpdateHoveredElement(p);
						m_pControl->m_sScroll.X = m_pControl->getHScroll()->getScroll();
						changed = true;
					}
				}
				if (changed)
				{
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion

	#pragma region Cell status change notifications
		void CCustomGridService::NotifyOnHoverCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnLeaveCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnSelectCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnDeselectCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnActivateCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnDeactivateCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnEnableCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnDisableCell(const int column, const int row, IListItem *item)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnMouseDownCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			// Nothing
		}

		void CCustomGridService::NotifyOnMouseUpCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			// Nothing
		}

		bool CCustomGridService::NotifyOnMouseMoveCell(const int column, const int row, IListItem *item, const PointF &position, const bool left, const bool middle, const bool right, const bool ctrl, const bool alt, const bool shift)
		{
			return false; // No repaint is required
		}

		void CCustomGridService::NotifyOnMouseDownCancel()
		{
			// Nothing
		}
	#pragma endregion

	#pragma region Keys
		bool CCustomGridService::ProcessKeyLeft(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find first unfixed column
			int unfixed_index{ -1 };
			for (int x = 0; x < (int)m_pControl->m_aColumns.size(); x++)
				if (!m_pControl->m_aColumns[x].Fixed)
				{
					unfixed_index = x;
					break;
				}
			if (unfixed_index < 0) // There are no unfixed columns. Nothing can be done
				return false;
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (m_pControl->m_sSelectTo.X > unfixed_index)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo.X--;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo.X = ntl::Max<int>(unfixed_index, m_pControl->m_sSelectTo.X - 1);
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyRight(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find last unfixed column
			int unfixed_index{ -1 };
			for (int x = (int)m_pControl->m_aColumns.size() - 1; x >= 0; x--)
				if (!m_pControl->m_aColumns[x].Fixed)
				{
					unfixed_index = x;
					break;
				}
			if (unfixed_index < 0) // There are no unfixed columns. Nothing can be done
				return false;
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (m_pControl->m_sSelectTo.X < unfixed_index)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo.X++;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo.X = ntl::Max<int>(0, ntl::Min<int>(unfixed_index, m_pControl->m_sSelectTo.X + 1));
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyUp(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find first unfixed row
			int unfixed_index{ -1 };
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed_index = y;
					break;
				}
			if (unfixed_index < 0) // There are no unfixed columns. Nothing can be done
				return false;
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (m_pControl->m_sSelectTo.Y > unfixed_index)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo.Y--;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo.Y = ntl::Max<int>(unfixed_index, m_pControl->m_sSelectTo.Y - 1);
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyDown(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find last unfixed row
			int unfixed_index{ -1 };
			for (int y = (int)m_pControl->m_aRows.size() - 1; y >= 0; y--)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed_index = y;
					break;
				}
			if (unfixed_index < 0) // There are no unfixed columns. Nothing can be done
				return false;
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (m_pControl->m_sSelectTo.Y < unfixed_index)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo.Y++;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo.Y = ntl::Max<int>(0, ntl::Min<int>(unfixed_index, m_pControl->m_sSelectTo.Y + 1));
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyHome(const bool ctrl, const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find unfixed column and row
			Point unfixed{ -1, -1 };
			for (int x = 0; x < (int)m_pControl->m_aColumns.size(); x++)
				if (!m_pControl->m_aColumns[x].Fixed)
				{
					unfixed.X = x;
					break;
				}
			if (unfixed.X < 0)
				return false;
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed.Y = y;
					break;
				}
			if (unfixed.Y < 0)
				return false;
			// Find new scroll to position
			Point new_scroll_to;
			if (ctrl)
				new_scroll_to = unfixed;
			else
				new_scroll_to = { unfixed.X, m_pControl->m_sSelectTo.Y };
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (new_scroll_to != m_pControl->m_sSelectTo)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo = new_scroll_to;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo = new_scroll_to;
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyEnd(const bool ctrl, const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find unfixed column and row
			Point unfixed{ -1, -1 };
			for (int x = (int)m_pControl->m_aColumns.size() - 1; x >= 0; x--)
				if (!m_pControl->m_aColumns[x].Fixed)
				{
					unfixed.X = x;
					break;
				}
			if (unfixed.X < 0)
				return false;
			for (int y = (int)m_pControl->m_aRows.size() - 1; y >= 0; y--)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed.Y = y;
					break;
				}
			if (unfixed.Y < 0)
				return false;
			// Find new scroll to position
			Point select_to;
			if (ctrl)
				select_to = unfixed;
			else
				select_to = { unfixed.X, m_pControl->m_sSelectTo.Y };
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (select_to != m_pControl->m_sSelectTo)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo = select_to;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo = select_to;
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyPageUp(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find unfixed row
			int unfixed{ -1 };
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed = y;
					break;
				}
			if (unfixed < 0)
				return false;
			// Find client heigh
			float client_height{ m_pControl->getClientRect().height() - m_pControl->m_aRows[m_pControl->m_sSelectTo.Y].Height - m_pControl->m_fGridWidth };
			if (m_pControl->m_bHScroll)
				client_height += m_pControl->m_sPadding.Bottom - m_pControl->getHScroll()->getHeight();
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
			{
				if (!m_pControl->m_aRows[y].Fixed)
					break;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
			}
			for (int y = (int)m_pControl->m_aRows.size() - 1; y >= 0; y--)
			{
				if (!m_pControl->m_aRows[y].Fixed)
					break;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
			}
			// Find new select to position
			Point select_to{ m_pControl->m_sSelectTo };
			for (int y = m_pControl->m_sSelectTo.Y; y > unfixed; y--)
			{
				select_to.Y--;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
				if (client_height <= 0)
					break;
			}
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (select_to != m_pControl->m_sSelectTo)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo = select_to;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo = select_to;
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeyPageDown(const bool shift)
		{
			// If there is no active cell, activate first available
			if (m_pControl->m_sActiveCell.X < 0)
				return ActivateFirstCell();
			// Find unfixed row
			int unfixed{ -1 };
			for (int y = (int)m_pControl->m_aRows.size() - 1; y >= 0; y--)
				if (!m_pControl->m_aRows[y].Fixed)
				{
					unfixed = y;
					break;
				}
			if (unfixed < 0)
				return false;
			// Find client heigh
			float client_height{ m_pControl->getClientRect().height() - m_pControl->m_aRows[m_pControl->m_sSelectTo.Y].Height - m_pControl->m_fGridWidth };
			if (m_pControl->m_bHScroll)
				client_height += m_pControl->m_sPadding.Bottom - m_pControl->getHScroll()->getHeight();
			for (int y = 0; y < (int)m_pControl->m_aRows.size(); y++)
			{
				if (!m_pControl->m_aRows[y].Fixed)
					break;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
			}
			for (int y = (int)m_pControl->m_aRows.size() - 1; y >= 0; y--)
			{
				if (!m_pControl->m_aRows[y].Fixed)
					break;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
			}
			// Find new select to position
			Point select_to{ m_pControl->m_sSelectTo };
			for (int y = m_pControl->m_sSelectTo.Y; y < unfixed; y++)
			{
				select_to.Y++;
				client_height -= m_pControl->m_aRows[y].Height + m_pControl->m_fGridWidth;
				if (client_height <= 0)
					break;
			}
			// Active cell exists and Shift key is down and multiselect is allowed
			if (shift && m_pControl->m_bMultiselect)
			{
				bool result{ false };
				if (select_to != m_pControl->m_sSelectTo)
				{
					m_pControl->m_bIgnoreItems = true;
					m_pControl->m_sSelectTo = select_to;
					result = SelectRange(Rect{
						ntl::Min<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Min<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y),
						ntl::Max<int>(m_pControl->m_sActiveCell.X, m_pControl->m_sSelectTo.X),
						ntl::Max<int>(m_pControl->m_sActiveCell.Y, m_pControl->m_sSelectTo.Y) });
					m_pControl->m_bIgnoreItems = false;
				}
				result = m_pControl->ScrollToCell(m_pControl->m_sSelectTo) || result;
				return result;
			}
			// Active cell exists and either Shift key is not down or multiselect is not allowed
			m_pControl->m_bIgnoreItems = true;
			m_pControl->m_sSelectTo = select_to;
			bool result{ SelectRange(Rect{ m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y }) };
			if (isCellActivatable(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y) && m_pControl->m_sActiveCell != m_pControl->m_sSelectTo)
			{
				if (m_pControl->m_sActiveCell.X >= 0)
					m_pControl->DeactivateCell(m_pControl->m_sActiveCell.X, m_pControl->m_sActiveCell.Y, this);
				m_pControl->ActivateCell(m_pControl->m_sSelectTo.X, m_pControl->m_sSelectTo.Y, this);
				result = true;
			}
			m_pControl->m_bIgnoreItems = false;
			result = m_pControl->ScrollToCell(m_pControl->m_sActiveCell) || result;
			return result;
		}

		bool CCustomGridService::ProcessKeySelectAll()
		{
			if (m_pControl->m_bMultiselect)
				return SelectRange(Rect{ 0, 0, (int)m_pControl->m_aColumns.size() - 1, (int)m_pControl->m_aRows.size() - 1 });
			return false;
		}
	#pragma endregion

	#pragma region Timer notification
		void CCustomGridService::NotifyOnTimer(const PlatformHandle id)
		{
			if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.X, 0) || ntl::IsGreater<float>(m_pControl->m_sMaxScroll.Y, 0))
			{
				bool changed{ false };
				PointF p{ m_pControl->FormToLocal((PointF)m_pControl->getForm()->ScreenToClient(Application->Mouse->getPosition())) };
				if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.X, 0))
				{
					if (p.X < 0 && m_pControl->m_sScroll.X > 0)
					{
						m_pControl->m_sScroll.X = ntl::Max<float>(0, m_pControl->m_sScroll.X + p.X);
						if (m_pControl->m_bHScroll)
							m_pControl->getHScroll()->setScroll(m_pControl->m_sScroll.X);
						changed = true;
					}
					else if (p.X >= m_pControl->getWidth() && ntl::IsLess<float>(m_pControl->m_sScroll.X, m_pControl->m_sMaxScroll.X))
					{
						m_pControl->m_sScroll.X = ntl::Min<float>(m_pControl->m_sMaxScroll.X, m_pControl->m_sScroll.X + p.X - m_pControl->getWidth());
						if (m_pControl->m_bHScroll)
							m_pControl->getHScroll()->setScroll(m_pControl->m_sScroll.X);
						changed = true;
					}
				}
				if (ntl::IsGreater<float>(m_pControl->m_sMaxScroll.Y, 0))
				{
					if (p.Y < 0 && m_pControl->m_sScroll.Y > 0)
					{
						m_pControl->m_sScroll.Y = ntl::Max<float>(0, m_pControl->m_sScroll.Y + p.Y);
						if (m_pControl->m_bVScroll)
							m_pControl->getVScroll()->setScroll(m_pControl->m_sScroll.Y);
						changed = true;
					}
					else if (p.Y >= m_pControl->getHeight() && ntl::IsLess<float>(m_pControl->m_sScroll.Y, m_pControl->m_sMaxScroll.Y))
					{
						m_pControl->m_sScroll.Y = ntl::Min<float>(m_pControl->m_sMaxScroll.Y, m_pControl->m_sScroll.Y + p.Y - m_pControl->getHeight());
						if (m_pControl->m_bVScroll)
							m_pControl->getVScroll()->setScroll(m_pControl->m_sScroll.Y);
						changed = true;
					}
				}
				if (changed)
				{
					CLockRepaint lock{ m_pControl };
					ProcessMouseMove(p, true, false, false, false, false, false);
					if (m_pControl->m_pCanvas)
						m_pControl->m_pCanvas->setValid(false);
					m_pControl->Repaint(false);
				}
			}
		}
	#pragma endregion
	}
}