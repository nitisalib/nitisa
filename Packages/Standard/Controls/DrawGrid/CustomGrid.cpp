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
		CCustomGrid::CGradientListener::CGradientListener(CCustomGrid *control) :
			m_pControl{ control }
		{

		}

		void CCustomGrid::CGradientListener::NotifyOnChange()
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
		CCustomGrid::CCustomGrid(const String &class_name):
			CControl(class_name, true, true, false, true, false, true),
			m_cGradientListener{ this },
			m_bMultiselect{ true },
			m_eVerticalScrollVisibility{ ScrollVisibility::Auto },
			m_eHorizontalScrollVisibility{ ScrollVisibility::Auto },
			m_fScrollInterval{ ScrollInterval },
			m_sBorderWidth{ 1, 1, 1, 1 },
			m_sPadding{ 0, 0, 0, 0 },
			m_fGridWidth{ 1 },
			m_aGridColor{
				Color{ 192, 192, 192, 255 },
				Color{ 192, 192, 192, 255 },
				Color{ 192, 192, 192, 255 },
				Color{ 192, 192, 192, 255 },
				Color{ 192, 192, 192, 255 } },
			m_aBorderRadius{ 0, 0, 0, 0, 0 },
			m_aBackgroundColor{
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 244, 244, 244, 255 } },
			m_aBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aBorderColor{
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } },
				BorderColor{ Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 }, Color{ 87, 148, 191, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 }, Color{ 61, 123, 173, 255 } },
				BorderColor{ Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 }, Color{ 171, 173, 179, 255 } } },
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
			m_aCornerColor{
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 },
				Color{ 234, 234, 234, 255 } },
			m_fDefaultColumnWidth{ 64 },
			m_fDefaultRowHeight{ 24 },
			m_bDefaultColumnResizable{ false },
			m_bDefaultRowResizable{ false },
			m_bDefaultColumnAutosize{ false },
			m_bDefaultRowAutosize{ false },
			m_bDefaultColumnEnabled{ true },
			m_bDefaultRowEnabled{ true },
			m_bDefaultColumnFixed{ false },
			m_bDefaultRowFixed{ false },
			m_bDefaultColumnOverflowHidden{ true },
			m_bDefaultRowOverflowHidden{ true },
			m_pVScroll{ nullptr },
			m_pHScroll{ nullptr },
			m_eHoveredElement{ Element::None },
			m_eDownElement{ Element::None },
			m_sScroll{ 0, 0 },
			m_sMaxScroll{ 0, 0 },
			m_pCanvas{ nullptr },
			m_cScrollListener{ this },
			m_bIgnoreGradient{ false },
			m_bVScroll{ false },
			m_bHScroll{ false },
			m_bIgnoreItems{ false },
			m_cOwner{ this },
			m_sActiveCell{ -1, -1 },
			m_sSelectTo{ 0, 0 },
			m_iLockUpdate{ 0 },
			m_bUpdateRequired{ false },
			m_hScrollTimer{ 0 }
		{
			// Events
			OnRenderCell = nullptr;
			OnHoverCell = nullptr;
			OnLeaveCell = nullptr;
			OnSelectCell = nullptr;
			OnDeselectCell = nullptr;
			OnActivateCell = nullptr;
			OnDeactivateCell = nullptr;
			OnEnableCell = nullptr;
			OnDisableCell = nullptr;
			OnMouseDownCell = nullptr;
			OnMouseUpCell = nullptr;
			OnMouseMoveCell = nullptr;

			setService(new CCustomGridService(this), true);
		}

		CCustomGrid::~CCustomGrid()
		{
			if (m_pVScroll)
				m_pVScroll->Release();
			if (m_pHScroll)
				m_pHScroll->Release();
		}

		void CCustomGrid::BeforeRelease()
		{
			for (auto &row : m_aCells)
				for (auto &cell : row)
					if (cell.Item)
						cell.Item->Release();
			m_aCells.clear();
			m_aColumns.clear();
			m_aRows.clear();
			CControl::BeforeRelease();
		}
	#pragma endregion

	#pragma region IControl getters
		RectF CCustomGrid::getClientRect()
		{
			RectF result{ getRect() };
			result.Left += m_sBorderWidth.Left + m_sPadding.Left;
			result.Top += m_sBorderWidth.Top + m_sPadding.Top;
			result.Right -= m_sBorderWidth.Right + m_sPadding.Right;
			result.Bottom -= m_sBorderWidth.Bottom + m_sPadding.Bottom;
			result.validate();
			return result;
		}

		RectF CCustomGrid::getRenderRect()
		{
			State state{ getState() };
			return AddShadow(getRect(), m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
		}

		CursorType CCustomGrid::getCursor()
		{
			if (isEnabled(true))
				switch (m_eDownElement)
				{
				case Element::RightBorder:
					return CursorType::SizeWestEast;
				case Element::BottomBorder:
					return CursorType::SizeNorthSouth;
				case Element::None:
					if (m_eHoveredElement == Element::RightBorder && m_aColumns[m_sHoveredCell.X].Enabled && m_aColumns[m_sHoveredCell.X].Resizable)
						return CursorType::SizeWestEast;
					if (m_eHoveredElement == Element::BottomBorder && m_aRows[m_sHoveredCell.Y].Enabled && m_aRows[m_sHoveredCell.Y].Resizable)
						return CursorType::SizeNorthSouth;
				default:
					break;
				}
			return CControl::getCursor();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CCustomGrid::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CControl::setDPI(value))
			{
				getHScroll()->setDPI(value);
				getVScroll()->setDPI(value);
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				float avg{ (s.X + s.Y) * 0.5f };
				m_sBorderWidth *= s;
				m_sPadding *= s;
				m_fGridWidth *= avg;
				for (int i = 0; i <= (int)State::Disabled; i++)
				{
					m_aBorderRadius[i] *= avg;
					m_aShadowRadius[i] = ntl::Round<int>((float)m_aShadowRadius[i] * avg);
					m_aShadowShift[i] *= s;
				}
				m_fDefaultColumnWidth *= s.X;
				m_fDefaultRowHeight *= s.Y;
				for (auto &column : m_aColumns)
					column.Width *= s.X;
				for (auto &row : m_aRows)
					row.Height *= s.Y;
				Update();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CCustomGrid::Refresh(const bool refresh_children)
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			CControl::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region ICustomGrid getters
		bool CCustomGrid::isMultiselect()
		{
			return m_bMultiselect;
		}

		int CCustomGrid::getColumns()
		{
			return (int)m_aColumns.size();
		}

		int CCustomGrid::getRows()
		{
			return (int)m_aRows.size();
		}

		bool CCustomGrid::isCellEnabled(const int column, const int row)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
				return m_aCells[row][column].Enabled;
			return false;
		}

		bool CCustomGrid::isCellHovered(const int column, const int row)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
				return m_aCells[row][column].Hovered;
			return false;
		}

		bool CCustomGrid::isCellActive(const int column, const int row)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
				return m_aCells[row][column].Active;
			return false;
		}

		bool CCustomGrid::isCellSelected(const int column, const int row)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
				return m_aCells[row][column].Selected;
			return false;
		}

		bool CCustomGrid::isCellOverflowHidden(const int column, const int row)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
				return m_aCells[row][column].OverflowHidden;
			return true;
		}

		float CCustomGrid::getColumnWidth(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].Width;
			return 0;
		}

		bool CCustomGrid::isColumnResizable(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].Resizable;
			return false;
		}

		bool CCustomGrid::isColumnAutosize(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].Autosize;
			return false;
		}

		bool CCustomGrid::isColumnEnabled(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].Enabled;
			return false;
		}

		bool CCustomGrid::isColumnFixed(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].Fixed;
			return false;
		}

		bool CCustomGrid::isColumnOverflowHidden(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
				return m_aColumns[index].OverflowHidden;
			return true;
		}

		float CCustomGrid::getRowHeight(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].Height;
			return 0;
		}

		bool CCustomGrid::isRowResizable(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].Resizable;
			return false;
		}

		bool CCustomGrid::isRowAutosize(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].Autosize;
			return false;
		}

		bool CCustomGrid::isRowEnabled(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].Enabled;
			return false;
		}

		bool CCustomGrid::isRowFixed(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].Fixed;
			return false;
		}

		bool CCustomGrid::isRowOverflowHidden(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
				return m_aRows[index].OverflowHidden;
			return true;
		}

		Point CCustomGrid::getCellAtPosition(const PointF &position, const bool bound)
		{
			if (m_aRows.size() == 0 || m_aColumns.size() == 0)
				return Point{ -1, -1 };
			// Find cell exactly under the point
			PointF p{ 0, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
			Point result{ -1, -1 };
			for (int y = 0; y < (int)m_aRows.size(); y++)
			{
				p.X = m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X;
				if (m_aRows[y].Fixed)
					p.Y += m_sScroll.Y;
				if (position.Y >= p.Y && position.Y < p.Y + m_aRows[y].Height + m_fGridWidth)
				{
					result.Y = y;
					for (int x = 0; x < (int)m_aColumns.size(); x++)
					{
						if (m_aColumns[x].Fixed)
							p.X += m_sScroll.X;
						if (position.X >= p.X && position.X < p.X + m_aColumns[x].Width + m_fGridWidth)
						{
							result.X = x;
							break;
						}
						if (m_aColumns[x].Fixed)
							p.X -= m_sScroll.X;
						p.X += m_aColumns[x].Width + m_fGridWidth;
					}
					if (result.X >= 0)
						break;
				}
				if (m_aRows[y].Fixed)
					p.Y -= m_sScroll.Y;
				p.Y += m_aRows[y].Height + m_fGridWidth;
			}
			// If cell is not found and bound is on, find closest one
			if (bound && (result.X < 0 || result.Y < 0))
			{
				p = PointF{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
				if (position.X < p.X)
					result.X = 0;
				else if (position.X >= p.X + m_sTableSize.X)
					result.X = (int)m_aColumns.size() - 1;
				else
					for (int x = 0; x < (int)m_aColumns.size(); x++)
					{
						if (position.X >= p.X && position.X < p.X + m_aColumns[x].Width + m_fGridWidth)
						{
							result.X = x;
							break;
						}
						p.X += m_aColumns[x].Width + m_fGridWidth;
					}
				if (position.Y < p.Y)
					result.Y = 0;
				else if (position.Y >= p.Y + m_sTableSize.Y)
					result.Y = (int)m_aRows.size() - 1;
				else
					for (int y = 0; y < (int)m_aRows.size(); y++)
					{
						if (position.Y >= p.Y && position.Y < p.Y + m_aRows[y].Height + m_fGridWidth)
						{
							result.Y = y;
							break;
						}
						p.Y += m_aRows[y].Height + m_fGridWidth;
					}
			}
			if (result.X < 0 || result.Y < 0)
				return Point{ -1, -1 };
			return result;
		}
	#pragma endregion

	#pragma region ICustomGrid setters
		bool CCustomGrid::setMultiselect(const bool value)
		{
			if (value != m_bMultiselect)
			{
				m_bMultiselect = value;
				if (!m_bMultiselect)
				{
					bool result{ false }, found{ false };
					CLockRepaint lock{ this };
					ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
					m_bIgnoreItems = true;
					for (int y = 0; y < (int)m_aRows.size(); y++)
						for (int x = 0; x < (int)m_aColumns.size(); x++)
							if (m_aCells[y][x].Selected)
							{
								if (found)
									result = DeselectCell(x, y, service) || result;
								else
									found = true;
							}
					m_bIgnoreItems = false;
					if (result)
					{
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
					}
				}
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumns(const int value)
		{
			if (value >= 0 && value != (int)m_aColumns.size())
			{
				CLockRepaint lock{ this };
				if (value > (int)m_aColumns.size()) // Add columns
				{
					while ((int)m_aColumns.size() < value)
					{
						// Add column
						COLUMN column;
						CreateColumn(column.Width, column.Resizable, column.Autosize, column.Enabled, column.Fixed, column.OverflowHidden);
						m_aColumns.push_back(column);
						// Add cell to each row
						int row_index{ 0 };
						for (auto &row : m_aCells)
						{
							CELL cell{ CreateItem((int)m_aColumns.size() - 1, row_index), false, false, false, column.Enabled && m_aRows[row_index].Enabled, column.OverflowHidden };
							if (cell.Item)
							{
								cell.Item->setActive(false);
								cell.Item->setEnabled(cell.Enabled);
								cell.Item->setSelected(false);
								cell.Item->setVisible(true);
								cell.Item->QueryService()->setHovered(false);
								cell.Item->QueryService()->setOwner(&m_cOwner);
							}
							row.push_back(cell);
							row_index++;
						}
					}
				}
				else // Delete columns
				{
					LeaveAll();
					CancelMouseDown(true, cast<ICustomGridService*>(QueryService()));
					// Destroy items and remove cells from each row
					for (auto &row : m_aCells)
					{
						for (int i = value; i < (int)m_aColumns.size(); i++)
							if (row[i].Item)
								row[i].Item->Release();
						row.erase(row.begin() + value, row.end());
					}
					// Remove columns
					m_aColumns.erase(m_aColumns.begin() + value, m_aColumns.end());
					// Update active and selectTo cell coordinates
					if (m_sActiveCell.X >= value)
						m_sActiveCell = Point{ -1, -1 };
					if (m_sSelectTo.X >= value)
						m_sSelectTo = Point{ -1, -1 };
				}
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRows(const int value)
		{
			if (value >= 0 && value != (int)m_aRows.size())
			{
				CLockRepaint lock{ this };
				if (value > (int)m_aRows.size()) // Add rows
				{
					while ((int)m_aRows.size() < value)
					{
						// Add row
						ROW row;
						CreateRow(row.Height, row.Resizable, row.Autosize, row.Enabled, row.Fixed, row.OverflowHidden);
						m_aRows.push_back(row);
						// Add row of cells
						m_aCells.push_back({});
						for (int i = 0; i < (int)m_aColumns.size(); i++)
						{
							CELL cell{ CreateItem(i, (int)m_aRows.size() - 1), false, false, false, row.Enabled && m_aColumns[i].Enabled, row.OverflowHidden };
							if (cell.Item)
							{
								cell.Item->setActive(false);
								cell.Item->setEnabled(cell.Enabled);
								cell.Item->setSelected(false);
								cell.Item->setVisible(true);
								cell.Item->QueryService()->setHovered(false);
								cell.Item->QueryService()->setOwner(&m_cOwner);
							}
							m_aCells[m_aCells.size() - 1].push_back(cell);
						}
					}
				}
				else // Delete rows
				{
					LeaveAll();
					CancelMouseDown(true, cast<ICustomGridService*>(QueryService()));
					// Destroy items
					for (int i = value; i < (int)m_aRows.size(); i++)
						for (auto &cell : m_aCells[i])
							if (cell.Item)
								cell.Item->Release();
					m_aCells.erase(m_aCells.begin() + value, m_aCells.end());
					// Remove rows
					m_aRows.erase(m_aRows.begin() + value, m_aRows.end());
					// Update active and selectTo cell coordinates
					if (m_sActiveCell.Y >= value)
						m_sActiveCell = Point{ -1, -1 };
					if (m_sSelectTo.Y >= value)
						m_sSelectTo = Point{ -1, -1 };
				}
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setCellEnabled(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size() && value != m_aCells[row][column].Enabled)
			{
				m_bIgnoreItems = true;
				ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
				if (value)
					EnableCell(column, row, service);
				else
				{
					DisableCell(column, row, service);
					if (DeactivateCell(column, row, service))
						m_sActiveCell = Point{ -1, -1 };
				}
				m_bIgnoreItems = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setCellActive(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size())
			{
				if (value)
				{
					if (
						m_aColumns[column].Enabled && !m_aColumns[column].Fixed &&
						m_aRows[row].Enabled && !m_aRows[row].Fixed &&
						m_aCells[row][column].Enabled &&
						(column != m_sActiveCell.X || row != m_sActiveCell.Y))
					{
						m_bIgnoreItems = true;
						ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
						if (m_sActiveCell.X >= 0)
							DeactivateCell(m_sActiveCell.X, m_sActiveCell.Y, service);
						ActivateCell(column, row, service);
						m_bIgnoreItems = false;
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
						return true;
					}
				}
				else
				{
					if (column == m_sActiveCell.X && row == m_sActiveCell.Y)
					{
						m_bIgnoreItems = true;
						DeactivateCell(m_sActiveCell.X, m_sActiveCell.Y, cast<ICustomGridService*>(QueryService()));
						m_sActiveCell = Point{ -1, -1 };
						m_bIgnoreItems = false;
						if (m_pCanvas)
							m_pCanvas->setValid(false);
						Repaint(false);
						return true;
					}
				}
			}
			return false;
		}

		bool CCustomGrid::setCellSelected(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size() && value != m_aCells[row][column].Selected)
			{
				m_bIgnoreItems = true;
				ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
				if (value)
				{
					if (!m_bMultiselect)
						for (int y = 0; y < (int)m_aRows.size(); y++)
							for (int x = 0; x < (int)m_aColumns.size(); x++)
								if (x != column && y != row)
									DeselectCell(x, y, service);
					SelectCell(column, row, service);
				}
				else
					DeselectCell(column, row, service);
				m_bIgnoreItems = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setCellOverflowHidden(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < (int)m_aColumns.size() && row >= 0 && row < (int)m_aRows.size() && value != m_aCells[row][column].OverflowHidden)
			{
				m_aCells[row][column].OverflowHidden = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnWidth(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && ntl::IsGreater<float>(value, 0) && (ntl::IsNotEqual<float>(value, m_aColumns[index].Width) || m_aColumns[index].Autosize))
			{
				m_aColumns[index].Width = value;
				m_aColumns[index].Autosize = false;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnResizable(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && value != m_aColumns[index].Resizable)
			{
				m_aColumns[index].Resizable = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnAutosize(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && value != m_aColumns[index].Autosize)
			{
				m_aColumns[index].Autosize = value;
				if (value)
					Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnEnabled(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && value != m_aColumns[index].Enabled)
			{
				m_bIgnoreItems = true;
				m_aColumns[index].Enabled = value;
				ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
				for (int y = 0; y < (int)m_aRows.size(); y++)
					if (value)
						EnableCell(index, y, service);
					else
					{
						DisableCell(index, y, service);
						if (DeactivateCell(index, y, service))
							m_sActiveCell = Point{ -1, -1 };
					}
				m_bIgnoreItems = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnFixed(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && value != m_aColumns[index].Fixed)
			{
				m_aColumns[index].Fixed = value;
				if (value)
				{
					m_bIgnoreItems = true;
					ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
					for (int y = 0; y < (int)m_aRows.size(); y++)
					{
						DeselectCell(index, y, service);
						if (DeactivateCell(index, y, service))
							m_sActiveCell = Point{ -1, -1 };
					}
					m_bIgnoreItems = false;
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setColumnOverflowHidden(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aColumns.size() && value != m_aColumns[index].OverflowHidden)
			{
				m_aColumns[index].OverflowHidden = value;
				for (auto &row : m_aCells)
					row[index].OverflowHidden = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowHeight(const int index, const float value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && ntl::IsGreater<float>(value, 0) && (ntl::IsNotEqual<float>(value, m_aRows[index].Height) || m_aRows[index].Autosize))
			{
				m_aRows[index].Height = value;
				m_aRows[index].Autosize = false;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowResizable(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && value != m_aRows[index].Resizable)
			{
				m_aRows[index].Resizable = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowAutosize(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && value != m_aRows[index].Autosize)
			{
				m_aRows[index].Autosize = value;
				if (value)
					Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowEnabled(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && value != m_aRows[index].Enabled)
			{
				m_bIgnoreItems = true;
				m_aRows[index].Enabled = value;
				ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
				for (int x = 0; x < (int)m_aColumns.size(); x++)
					if (value)
						EnableCell(x, index, service);
					else
					{
						DisableCell(x, index, service);
						if (DeactivateCell(x, index, service))
							m_sActiveCell = Point{ -1, -1 };
					}
				m_bIgnoreItems = false;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowFixed(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && value != m_aRows[index].Fixed)
			{
				m_aRows[index].Fixed = value;
				if (value)
				{
					m_bIgnoreItems = true;
					ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
					for (int x = 0; x < (int)m_aColumns.size(); x++)
					{
						DeselectCell(x, index, service);
						if (DeactivateCell(x, index, service))
							m_sActiveCell = Point{ -1, -1 };
					}
					m_bIgnoreItems = false;
				}
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}

		bool CCustomGrid::setRowOverflowHidden(const int index, const bool value)
		{
			if (index >= 0 && index < (int)m_aRows.size() && value != m_aRows[index].OverflowHidden)
			{
				m_aRows[index].OverflowHidden = value;
				for (auto &cell : m_aCells[index])
					cell.OverflowHidden = value;
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICustom grid methods
		bool CCustomGrid::SelectAllCells()
		{
			bool result{ false };
			CLockRepaint lock{ this };
			ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
			m_bIgnoreItems = true;
			for (int y = 0; y < (int)m_aRows.size(); y++)
				for (int x = 0; x < (int)m_aColumns.size(); x++)
				{
					bool v{ m_bMultiselect || !result };
					if (m_aCells[y][x].Selected != v)
					{
						v ? SelectCell(x, y, service) : DeselectCell(x, y, service);
						result = true;
					}
				}
			m_bIgnoreItems = false;
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CCustomGrid::DeselectAllCells()
		{
			bool result{ false };
			CLockRepaint lock{ this };
			ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
			m_bIgnoreItems = true;
			for (int y = 0; y < (int)m_aRows.size(); y++)
				for (int x = 0; x < (int)m_aColumns.size(); x++)
					result = DeselectCell(x, y, service) || result;
			m_bIgnoreItems = false;
			if (result)
			{
				if (m_pCanvas)
					m_pCanvas->setValid(false);
				Repaint(false);
			}
			return result;
		}

		bool CCustomGrid::DeleteColumn(const int index)
		{
			if (index >= 0 && index < (int)m_aColumns.size())
			{
				CLockRepaint lock{ this };
				LeaveAll();
				CancelMouseDown(true, cast<ICustomGridService*>(QueryService()));
				for (int y = 0; y < (int)m_aRows.size(); y++)
				{
					if (m_aCells[y][index].Item)
						m_aCells[y][index].Item->Release();
					m_aCells[y].erase(m_aCells[y].begin() + index);
				}
				m_aColumns.erase(m_aColumns.begin() + index);
				if (m_sActiveCell.X == index)
				{
					m_sActiveCell = Point{ -1, -1 };
					m_sSelectTo = Point{ -1, -1 };
				}
				else
				{
					if (m_sActiveCell.X > index)
						m_sActiveCell.X--;
					if (m_sSelectTo.X == index)
						m_sSelectTo = m_sActiveCell;
					else if (m_sSelectTo.X > index)
						m_sSelectTo.X--;
				}
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::DeleteRow(const int index)
		{
			if (index >= 0 && index < (int)m_aRows.size())
			{
				CLockRepaint lock{ this };
				LeaveAll();
				CancelMouseDown(true, cast<ICustomGridService*>(QueryService()));
				for (int x = 0; x < (int)m_aColumns.size(); x++)
					if (m_aCells[index][x].Item)
						m_aCells[index][x].Item->Release();
				m_aCells.erase(m_aCells.begin() + index);
				m_aRows.erase(m_aRows.begin() + index);
				if (m_sActiveCell.Y == index)
				{
					m_sActiveCell = Point{ -1, -1 };
					m_sSelectTo = Point{ -1, -1 };
				}
				else
				{
					if (m_sActiveCell.Y > index)
						m_sActiveCell.Y--;
					if (m_sSelectTo.Y == index)
						m_sSelectTo = m_sActiveCell;
					else if (m_sSelectTo.Y > index)
						m_sSelectTo.Y--;
				}
				Update();
				return true;
			}
			return false;
		}

		void CCustomGrid::LockUpdate()
		{
			m_iLockUpdate++;
			if (m_iLockUpdate == 1)
				m_bUpdateRequired = false;
		}

		void CCustomGrid::UnlockUpdate()
		{
			if (m_iLockUpdate > 0)
			{
				m_iLockUpdate--;
				if (m_iLockUpdate == 0 && m_bUpdateRequired)
					Update();
			}
		}
	#pragma endregion

	#pragma region Getters
		CCustomGrid::State CCustomGrid::getState()
		{
			if (!isEnabled(false))
				return State::Disabled;
			if (isFocused())
			{
				if (isHovered())
					return State::FocusedHovered;
				return State::Focused;
			}
			if (isHovered())
				return State::Hovered;
			return State::Normal;
		}

		ScrollVisibility CCustomGrid::getVerticalScrollVisibility() const
		{
			return m_eVerticalScrollVisibility;
		}

		ScrollVisibility CCustomGrid::getHorizontalScrollVisibility() const
		{
			return m_eHorizontalScrollVisibility;
		}

		RectF CCustomGrid::getBorderWidth() const
		{
			return m_sBorderWidth;
		}

		RectF CCustomGrid::getPadding() const
		{
			return m_sPadding;
		}

		float CCustomGrid::getGridWidth() const
		{
			return m_fGridWidth;
		}

		Color CCustomGrid::getGridColor(const State state) const
		{
			return m_aGridColor[(int)state];
		}

		RectF CCustomGrid::getBorderRadius(const State state) const
		{
			return m_aBorderRadius[(int)state];
		}

		Color CCustomGrid::getBackgroundColor(const State state) const
		{
			return m_aBackgroundColor[(int)state];
		}

		Gradient *CCustomGrid::getBackgroundGradient(const State state)
		{
			return &m_aBackgroundGradient[(int)state];
		}

		BorderColor CCustomGrid::getBorderColor(const State state) const
		{
			return m_aBorderColor[(int)state];
		}

		int CCustomGrid::getShadowRadius(const State state) const
		{
			return m_aShadowRadius[(int)state];
		}

		PointF CCustomGrid::getShadowShift(const State state) const
		{
			return m_aShadowShift[(int)state];
		}

		Color CCustomGrid::getShadowColor(const State state) const
		{
			return m_aShadowColor[(int)state];
		}

		Color CCustomGrid::getCornerColor(const State state) const
		{
			return m_aCornerColor[(int)state];
		}

		float CCustomGrid::getScrollInterval() const
		{
			return m_fScrollInterval;
		}

		float CCustomGrid::getDefaultColumnWidth() const
		{
			return m_fDefaultColumnWidth;
		}

		float CCustomGrid::getDefaultRowHeight() const
		{
			return m_fDefaultRowHeight;
		}

		bool CCustomGrid::isDefaultColumnResizable() const
		{
			return m_bDefaultColumnResizable;
		}

		bool CCustomGrid::isDefaultRowResizable() const
		{
			return m_bDefaultRowResizable;
		}

		bool CCustomGrid::isDefaultColumnAutosize() const
		{
			return m_bDefaultColumnAutosize;
		}

		bool CCustomGrid::isDefaultRowAutosize() const
		{
			return m_bDefaultRowAutosize;
		}

		bool CCustomGrid::isDefaultColumnEnabled() const
		{
			return m_bDefaultColumnEnabled;
		}

		bool CCustomGrid::isDefaultRowEnabled() const
		{
			return m_bDefaultRowEnabled;
		}

		bool CCustomGrid::isDefaultColumnFixed() const
		{
			return m_bDefaultColumnFixed;
		}

		bool CCustomGrid::isDefaultRowFixed() const
		{
			return m_bDefaultRowFixed;
		}

		bool CCustomGrid::isDefaultColumnOverflowHidden() const
		{
			return m_bDefaultColumnOverflowHidden;
		}

		bool CCustomGrid::isDefaultRowOverflowHidden() const
		{
			return m_bDefaultRowOverflowHidden;
		}

		Point CCustomGrid::getActiveCell() const
		{
			return m_sActiveCell;
		}

		PointF CCustomGrid::getCellPosition(const int column, const int row)
		{
			PointF p{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
			// Find Y position
			for (int y = 0; y < row; y++)
				p.Y += m_aRows[y].Height + m_fGridWidth;
			if (m_aRows[row].Fixed)
				p.Y += m_sScroll.Y;
			// Find X position
			for (int x = 0; x < column; x++)
				p.X += m_aColumns[x].Width + m_fGridWidth;
			if (m_aColumns[column].Fixed)
				p.X += m_sScroll.X;
			return p;
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomGrid::setVerticalScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pVScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				value->setVertical(true);
				if (m_pVScroll)
					m_pVScroll->Release();
				m_pVScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setHorizontalScroll(IBuiltInScroll *value)
		{
			if (value && value != m_pHScroll)
			{
				value->setListener(&m_cScrollListener);
				value->NotifyOnFreeResources();
				value->setVertical(false);
				if (m_pHScroll)
					m_pHScroll->Release();
				m_pHScroll = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setVerticalScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eVerticalScrollVisibility)
			{
				m_eVerticalScrollVisibility = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setHorizontalScrollVisibility(const ScrollVisibility value)
		{
			if (value != m_eHorizontalScrollVisibility)
			{
				m_eHorizontalScrollVisibility = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setBorderWidth(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sBorderWidth))
			{
				m_sBorderWidth = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sPadding))
			{
				m_sPadding = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setGridWidth(const float value)
		{
			if (ntl::IsGreaterOrEqual<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fGridWidth))
			{
				m_fGridWidth = value;
				Update();
				return true;
			}
			return false;
		}

		bool CCustomGrid::setGridColor(const State state, const Color &value)
		{
			if (value != m_aGridColor[(int)state])
			{
				m_aGridColor[(int)state] = value;
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

		bool CCustomGrid::setBorderRadius(const State state, const RectF value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aBorderRadius[(int)state]))
			{
				m_aBorderRadius[(int)state] = value;
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

		bool CCustomGrid::setBackgroundColor(const State state, const Color &value)
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

		bool CCustomGrid::setBorderColor(const State state, const BorderColor &value)
		{
			if (value != m_aBorderColor[(int)state])
			{
				m_aBorderColor[(int)state] = value;
				if (m_sBorderWidth.has_positive() && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomGrid::setShadowRadius(const State state, const int value)
		{
			if (value > 0 && value != m_aShadowRadius[(int)state])
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (m_aShadowColor[(int)state].A && s == state)
					Repaint(false);
				m_aShadowRadius[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && state == s)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomGrid::setShadowShift(const State state, const PointF &value)
		{
			if (IsNotEqual(value, m_aShadowShift[(int)state]))
			{
				CLockRepaint lock{ this };
				State s{ getState() };
				if (m_aShadowColor[(int)state].A && s == state)
					Repaint(false);
				m_aShadowShift[(int)state] = value;
				if (m_aShadowColor[(int)state].A > 0 && state == s)
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomGrid::setShadowColor(const State state, const Color &value)
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

		bool CCustomGrid::setCornerColor(const State state, const Color &value)
		{
			if (value != m_aCornerColor[(int)state])
			{
				m_aCornerColor[(int)state] = value;
				if (m_bVScroll && m_bHScroll && state == getState())
				{
					if (m_pCanvas)
						m_pCanvas->setValid(false);
					Repaint(false);
				}
				return true;
			}
			return false;
		}

		bool CCustomGrid::setScrollInterval(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fScrollInterval))
			{
				m_fScrollInterval = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnWidth(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDefaultColumnWidth))
			{
				m_fDefaultColumnWidth = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowHeight(const float value)
		{
			if (ntl::IsGreater<float>(value, 0) && ntl::IsNotEqual<float>(value, m_fDefaultRowHeight))
			{
				m_fDefaultRowHeight = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnResizable(const bool value)
		{
			if (value != m_bDefaultColumnResizable)
			{
				m_bDefaultColumnResizable = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowResizable(const bool value)
		{
			if (value != m_bDefaultRowResizable)
			{
				m_bDefaultRowResizable = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnAutosize(const bool value)
		{
			if (value != m_bDefaultColumnAutosize)
			{
				m_bDefaultColumnAutosize = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowAutosize(const bool value)
		{
			if (value != m_bDefaultRowAutosize)
			{
				m_bDefaultRowAutosize = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnEnabled(const bool value)
		{
			if (value != m_bDefaultColumnEnabled)
			{
				m_bDefaultColumnEnabled = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowEnabled(const bool value)
		{
			if (value != m_bDefaultRowEnabled)
			{
				m_bDefaultRowEnabled = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnFixed(const bool value)
		{
			if (value != m_bDefaultColumnFixed)
			{
				m_bDefaultColumnFixed = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowFixed(const bool value)
		{
			if (value != m_bDefaultRowFixed)
			{
				m_bDefaultRowFixed = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultColumnOverflowHidden(const bool value)
		{
			if (value != m_bDefaultColumnOverflowHidden)
			{
				m_bDefaultColumnOverflowHidden = value;
				return true;
			}
			return false;
		}

		bool CCustomGrid::setDefaultRowOverflowHidden(const bool value)
		{
			if (value != m_bDefaultRowOverflowHidden)
			{
				m_bDefaultRowOverflowHidden = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomGrid::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = m_bIgnoreItems = true;
			style->getOption(m_sClassName + L".BorderWidth", m_sBorderWidth);
			style->getOption(m_sClassName + L".Padding", m_sPadding);
			style->getOption(m_sClassName + L".GridWidth", m_fGridWidth);
			style->getOption(m_sClassName + L".DefaultColumnWidth", m_fDefaultColumnWidth);
			style->getOption(m_sClassName + L".DefaultRowHeight", m_fDefaultRowHeight);
			for (int i = 0; i <= (int)State::Disabled; i++)
			{
				String state;
				switch ((State)i)
				{
				case State::Normal:
					state = L"State::Normal";
					break;
				case State::Hovered:
					state = L"State::Hovered";
					break;
				case State::Focused:
					state = L"State::Focused";
					break;
				case State::FocusedHovered:
					state = L"State::FocusedHovered";
					break;
				default:
					state = L"State::Disabled";
					break;
				}
				style->getOption(m_sClassName + L".GridColor[" + state + L"]", m_aGridColor[i]);
				style->getOption(m_sClassName + L".BorderRadius[" + state + L"]", m_aBorderRadius[i]);
				style->getOption(m_sClassName + L".BackgroundColor[" + state + L"]", m_aBackgroundColor[i]);
				style->getOption(m_sClassName + L".BackgroundGradient[" + state + L"]", m_aBackgroundGradient[i]);
				style->getOption(m_sClassName + L".BorderColor[" + state + L"]", m_aBorderColor[i]);
				style->getOption(m_sClassName + L".ShadowRadius[" + state + L"]", m_aShadowRadius[i]);
				style->getOption(m_sClassName + L".ShadowShift[" + state + L"]", m_aShadowShift[i]);
				style->getOption(m_sClassName + L".ShadowColor[" + state + L"]", m_aShadowColor[i]);
				style->getOption(m_sClassName + L".CornerColor[" + state + L"]", m_aCornerColor[i]);
			}
			getVScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			getHScroll()->UpdateFromStyle(style, m_sClassName + L".Scroll");
			for (auto &row : m_aCells)
				for (auto &cell : row)
					if (cell.Item)
						cell.Item->QueryService()->UpdateFromStyle();
			m_bIgnoreGradient = m_bIgnoreItems = false;
			Update();
		}

		void CCustomGrid::CreateColumn(float &width, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden)
		{
			width = m_fDefaultColumnWidth;
			resizable = m_bDefaultColumnResizable;
			autosize = m_bDefaultColumnAutosize;
			enabled = m_bDefaultColumnEnabled;
			fixed = m_bDefaultColumnFixed;
			overflow_hidden = m_bDefaultColumnOverflowHidden;
		}

		void CCustomGrid::CreateRow(float &height, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden)
		{
			height = m_fDefaultRowHeight;
			resizable = m_bDefaultRowResizable;
			autosize = m_bDefaultRowAutosize;
			enabled = m_bDefaultRowEnabled;
			fixed = m_bDefaultRowFixed;
			overflow_hidden = m_bDefaultRowOverflowHidden;
		}

		IBuiltInScroll *CCustomGrid::getVScroll()
		{
			if (!m_pVScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				if (!scroll->isVertical())
					scroll->SwitchDirection(true);
				m_pVScroll = scroll;
			}
			return m_pVScroll;
		}

		IBuiltInScroll *CCustomGrid::getHScroll()
		{
			if (!m_pHScroll)
			{
				CScroll *scroll{ new CScroll(this) };
				scroll->setListener(&m_cScrollListener);
				if (scroll->isVertical())
					scroll->SwitchDirection(true);
				m_pHScroll = scroll;
			}
			return m_pHScroll;
		}

		PointF CCustomGrid::GetItemRequiredSize(const int column, const int row, IListItem *item)
		{
			if (item)
				return item->QueryService()->getRequiredSize();
			return PointF{ 0, 0 };
		}

		void CCustomGrid::Update()
		{
			if (m_iLockUpdate > 0)
			{
				m_bUpdateRequired = true;
				return;
			}
			// Calculate column widths
			for (int x = 0; x < (int)m_aColumns.size(); x++)
				if (m_aColumns[x].Autosize)
				{
					m_aColumns[x].Width = 0;
					int row_index{ 0 };
					for (auto &row : m_aCells)
						m_aColumns[x].Width = ntl::Max<float>(m_aColumns[x].Width, GetItemRequiredSize(x, row_index++, row[x].Item).X);
				}
			// Calculate row heights
			for (int y = 0; y < (int)m_aRows.size(); y++)
				if (m_aRows[y].Autosize)
				{
					m_aRows[y].Height = 0;
					int column_index{ 0 };
					for (auto &cell : m_aCells[y])
						m_aRows[y].Height = ntl::Max<float>(m_aRows[y].Height, GetItemRequiredSize(column_index++, y, cell.Item).Y);
				}
			// Set cell positions and sizes
			m_bIgnoreItems = true;
			PointF p{ 0, m_sBorderWidth.Top + m_sPadding.Top };
			for (int y = 0; y < (int)m_aRows.size(); y++)
			{
				p.X = m_sBorderWidth.Left + m_sPadding.Left;
				for (int x = 0; x < (int)m_aColumns.size(); x++)
				{
					if (m_aCells[y][x].Item)
					{
						m_aCells[y][x].Item->QueryService()->setPosition(p);
						m_aCells[y][x].Item->QueryService()->setSize(PointF{ m_aColumns[x].Width, m_aRows[y].Height });
					}
					p.X += m_aColumns[x].Width + m_fGridWidth;
				}
				p.Y += m_aRows[y].Height + m_fGridWidth;
			}
			m_bIgnoreItems = false;
			// Calculate table size
			m_sTableSize = PointF{ m_fGridWidth * (float)m_aColumns.size(), m_fGridWidth * (float)m_aRows.size() };
			for (int x = 0; x < (int)m_aColumns.size(); x++)
				m_sTableSize.X += m_aColumns[x].Width;
			for (int y = 0; y < (int)m_aRows.size(); y++)
				m_sTableSize.Y += m_aRows[y].Height;
			// Calculate client area
			RectF client{ getClientRect() };
			if (client.is_empty() || ntl::IsLess<float>(client.width(), getVScroll()->getWidth() - m_sPadding.Right) || ntl::IsLess<float>(client.height(), getHScroll()->getHeight() - m_sPadding.Bottom))
			{
				m_sMaxScroll = PointF{ 0, 0 };
				m_sScroll = PointF{ 0, 0 };
				getVScroll()->setEnabled(false);
				getHScroll()->setEnabled(false);
				m_bVScroll = m_bHScroll = false;
			}
			else
			{
				// Calculate scrollbars visibility
				switch (m_eVerticalScrollVisibility)
				{
				case ScrollVisibility::None:
					m_bVScroll = false;
					break;
				case ScrollVisibility::Visible:
					m_bVScroll = true;
					break;
				default:
					switch (m_eHorizontalScrollVisibility)
					{
					case ScrollVisibility::None:
						m_bVScroll = ntl::IsGreater<float>(m_sTableSize.Y, client.height());
						break;
					case ScrollVisibility::Visible:
						m_bVScroll = ntl::IsGreater<float>(m_sTableSize.Y, client.height() - getHScroll()->getHeight() + m_sPadding.Bottom);
						break;
					default:
						m_bVScroll = ntl::IsGreater<float>(m_sTableSize.Y, (client.height() - (ntl::IsGreater<float>(m_sTableSize.X, client.width()) ? (getHScroll()->getHeight() - m_sPadding.Bottom) : 0)));
					}
				}
				switch (m_eHorizontalScrollVisibility)
				{
				case ScrollVisibility::None:
					m_bHScroll = false;
					break;
				case ScrollVisibility::Visible:
					m_bHScroll = true;
					break;
				default:
					if (m_bVScroll)
						m_bHScroll = ntl::IsGreater<float>(m_sTableSize.X, client.width() - getVScroll()->getWidth() + m_sPadding.Right);
					else
						m_bHScroll = ntl::IsGreater<float>(m_sTableSize.X, client.width());
				}
				// Calculate max scroll
				if (m_bVScroll)
					client.Right += m_sPadding.Right - getVScroll()->getWidth();
				if (m_bHScroll)
					client.Bottom += m_sPadding.Bottom - getHScroll()->getHeight();
				m_sMaxScroll.X = ntl::IsGreater<float>(m_sTableSize.X, client.width()) ? (m_sTableSize.X - client.width()) : 0;
				m_sMaxScroll.Y = ntl::IsGreater<float>(m_sTableSize.Y, client.height()) ? (m_sTableSize.Y - client.height()) : 0;
				// Update scroll
				m_sScroll.X = ntl::Min<float>(m_sScroll.X, m_sMaxScroll.X);
				m_sScroll.Y = ntl::Min<float>(m_sScroll.Y, m_sMaxScroll.Y);
				// Update scrollbars
				if (m_bHScroll)
				{
					getHScroll()->setPosition(PointF{ m_sBorderWidth.Left, getHeight() - m_sBorderWidth.Bottom - getHScroll()->getHeight() });
					getHScroll()->setSize(PointF{ getWidth() - m_sBorderWidth.Left - m_sBorderWidth.Right - (m_bVScroll ? getVScroll()->getWidth() : 0), getHScroll()->getHeight() });
					getHScroll()->setEnabled(ntl::IsGreater<float>(m_sMaxScroll.X, 0) && isEnabled(false));
					if (ntl::IsGreater<float>(m_sMaxScroll.X, 0))
					{
						getHScroll()->setMax(m_sMaxScroll.X);
						getHScroll()->setScroll(m_sScroll.X);
					}
				}
				if (m_bVScroll)
				{
					getVScroll()->setPosition(PointF{ getWidth() - m_sBorderWidth.Right - getVScroll()->getWidth(), m_sBorderWidth.Top });
					getVScroll()->setSize(PointF{ getVScroll()->getWidth(), getHeight() - m_sBorderWidth.Top - m_sBorderWidth.Bottom - (m_bHScroll ? getHScroll()->getHeight() : 0) });
					getVScroll()->setEnabled(ntl::IsGreater<float>(m_sMaxScroll.Y, 0) && isEnabled(false));
					if (ntl::IsGreater<float>(m_sMaxScroll.Y, 0))
					{
						getVScroll()->setMax(m_sMaxScroll.Y);
						getVScroll()->setScroll(m_sScroll.Y);
					}
				}
			}
			UpdateHoveredElement();
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}

		Point CCustomGrid::FindItemCoords(IListItem *item)
		{
			for (int y = 0; y < (int)m_aRows.size(); y++)
				for (int x = 0; x < (int)m_aColumns.size(); x++)
					if (m_aCells[y][x].Item == item)
						return Point{ x, y };
			return Point{ -1, -1 };
		}

		bool CCustomGrid::UpdateHoveredElement()
		{
			if (getForm())
				return UpdateHoveredElement(FormToLocal((PointF)getForm()->ScreenToClient(Application->Mouse->getPosition())));
			return false;
		}

		bool CCustomGrid::UpdateHoveredElement(const PointF &pos)
		{
			Element el{ Element::None };
			Point coords{ -1, -1 };
			if (isEnabled(true))
			{
				RectF client{ getClientRect() };
				// Vertical scrollbar
				if (m_bVScroll)
				{
					RectF r{ getVScroll()->getLeft(), getVScroll()->getTop(), getVScroll()->getLeft() + getVScroll()->getWidth(), getVScroll()->getTop() + getVScroll()->getHeight() };
					if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
						el = Element::VScroll;
					client.Right += m_sPadding.Right - getVScroll()->getWidth();
				}
				// Horizontal scrollbar
				if (el == Element::None && m_bHScroll)
				{
					RectF r{ getHScroll()->getLeft(), getHScroll()->getTop(), getHScroll()->getLeft() + getHScroll()->getWidth(), getHScroll()->getTop() + getHScroll()->getHeight() };
					if (pos.X >= r.Left && pos.X < r.Right && pos.Y >= r.Top && pos.Y < r.Bottom)
						el = Element::HScroll;
					client.Bottom += m_sPadding.Bottom - getHScroll()->getHeight();
				}
				if (pos.X >= client.Left && pos.X < client.Right && pos.Y >= client.Top && pos.Y < client.Bottom)
				{
					// Row bottom borders
					if (el == Element::None && ntl::IsGreater<float>(m_fGridWidth, 0)) // Fixed rows
					{
						PointF p{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X, m_sBorderWidth.Top + m_sPadding.Top };
						if (pos.X >= p.X && pos.X < p.X + m_sTableSize.X)
							for (int y = 0; y < (int)m_aRows.size(); y++)
							{
								p.Y += m_aRows[y].Height;
								if (m_aRows[y].Resizable && m_aRows[y].Fixed && pos.Y >= p.Y && pos.Y < p.Y + m_fGridWidth)
								{
									el = Element::BottomBorder;
									coords = Point{ 0, y };
									break;
								}
								p.Y += m_fGridWidth;
							}
					}
					if (el == Element::None && ntl::IsGreater<float>(m_fGridWidth, 0)) // Not fixed rows
					{
						PointF p{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
						if (pos.X >= p.X && pos.X < p.X + m_sTableSize.X)
							for (int y = 0; y < (int)m_aRows.size(); y++)
							{
								p.Y += m_aRows[y].Height;
								if (m_aRows[y].Resizable && !m_aRows[y].Fixed && pos.Y >= p.Y && pos.Y < p.Y + m_fGridWidth)
								{
									el = Element::BottomBorder;
									coords = Point{ 0, y };
									break;
								}
								p.Y += m_fGridWidth;
							}
					}
					// Column right borders
					if (el == Element::None && ntl::IsGreater<float>(m_fGridWidth, 0)) // Fixed columns
					{
						PointF p{ m_sBorderWidth.Left + m_sPadding.Left, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
						if (pos.Y >= p.Y && pos.Y < p.Y + m_sTableSize.Y)
							for (int x = 0; x < (int)m_aColumns.size(); x++)
							{
								p.X += m_aColumns[x].Width;
								if (m_aColumns[x].Resizable && m_aColumns[x].Fixed && pos.X >= p.X && pos.X < p.X + m_fGridWidth)
								{
									el = Element::RightBorder;
									coords = Point{ x, 0 };
									break;
								}
								p.X += m_fGridWidth;
							}
					}
					if (el == Element::None && ntl::IsGreater<float>(m_fGridWidth, 0)) // Not fixed columns
					{
						PointF p{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
						if (pos.Y >= p.Y && pos.Y < p.Y + m_sTableSize.Y)
							for (int x = 0; x < (int)m_aColumns.size(); x++)
							{
								p.X += m_aColumns[x].Width;
								if (m_aColumns[x].Resizable && !m_aColumns[x].Fixed && pos.X >= p.X && pos.X < p.X + m_fGridWidth)
								{
									el = Element::RightBorder;
									coords = Point{ x, 0 };
									break;
								}
								p.X += m_fGridWidth;
							}
					}
					// Cell
					if (el == Element::None) // Fixed rows
					{
						PointF p{ 0, m_sBorderWidth.Top + m_sPadding.Top };
						for (int y = 0; y < (int)m_aRows.size(); y++)
						{
							if (m_aRows[y].Fixed && pos.Y >= p.Y && pos.Y < p.Y + m_aRows[y].Height)
							{
								p.X = m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X;
								for (int x = 0; x < (int)m_aColumns.size(); x++)
								{
									if (m_aColumns[x].Fixed)
										p.X += m_sScroll.X;
									if (pos.X >= p.X && pos.X < p.X + m_aColumns[x].Width)
									{
										el = Element::Cell;
										coords = Point{ x, y };
										break;
									}
									if (m_aColumns[x].Fixed)
										p.X -= m_sScroll.X;
									p.X += m_aColumns[x].Width + m_fGridWidth;
								}
								if (el != Element::None)
									break;
							}
							p.Y += m_aRows[y].Height + m_fGridWidth;
						}
					}
					if (el == Element::None) // Fixed columns
					{
						PointF p{ m_sBorderWidth.Left + m_sPadding.Left, 0 };
						for (int x = 0; x < (int)m_aColumns.size(); x++)
						{
							if (m_aColumns[x].Fixed && pos.X >= p.X && pos.X < p.X + m_aColumns[x].Width)
							{
								p.Y = m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y;
								for (int y = 0; y < (int)m_aRows.size(); y++)
								{
									if (m_aRows[y].Fixed)
										p.Y += m_sScroll.Y;
									if (pos.Y >= p.Y && pos.Y < p.Y + m_aRows[y].Height)
									{
										el = Element::Cell;
										coords = Point{ x, y };
										break;
									}
									if (m_aRows[y].Fixed)
										p.Y -= m_sScroll.Y;
									p.Y += m_aRows[y].Height + m_fGridWidth;
								}
								if (el != Element::None)
									break;
							}
							p.X += m_aColumns[x].Width + m_fGridWidth;
						}
					}
					if (el == Element::None) // Not fixed rows and columns
					{
						PointF p{ 0, m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y };
						for (int y = 0; y < (int)m_aRows.size(); y++)
						{
							if (!m_aRows[y].Fixed && pos.Y >= p.Y && pos.Y < p.Y + m_aRows[y].Height)
							{
								p.X = m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X;
								for (int x = 0; x < (int)m_aColumns.size(); x++)
								{
									if (!m_aColumns[x].Fixed && pos.X >= p.X && pos.X < p.X + m_aColumns[x].Width)
									{
										el = Element::Cell;
										coords = Point{ x, y };
										break;
									}
									p.X += m_aColumns[x].Width + m_fGridWidth;
								}
								if (el != Element::None)
									break;
							}
							p.Y += m_aRows[y].Height + m_fGridWidth;
						}
					}
				}
			}
			if (el != m_eHoveredElement || coords != m_sHoveredCell)
			{
				ICustomGridService *service{ cast<ICustomGridService*>(QueryService()) };
				switch (m_eHoveredElement)
				{
				case Element::VScroll:
					getVScroll()->NotifyOnMouseLeave();
					break;
				case Element::HScroll:
					getHScroll()->NotifyOnMouseLeave();
					break;
				case Element::Cell:
					LeaveCell(m_sHoveredCell.X, m_sHoveredCell.Y, service);
					break;
				default:
					break;
				}
				m_eHoveredElement = el;
				m_sHoveredCell = coords;
				switch (m_eHoveredElement)
				{
				case Element::VScroll:
					getVScroll()->NotifyOnMouseHover(PointF{ pos.X - getVScroll()->getLeft(), pos.Y - getVScroll()->getTop() });
					break;
				case Element::HScroll:
					getHScroll()->NotifyOnMouseHover(PointF{ pos.X - getHScroll()->getLeft(), pos.Y - getHScroll()->getTop() });
					break;
				case Element::Cell:
					HoverCell(m_sHoveredCell.X, m_sHoveredCell.Y, service);
					break;
				default:
					break;
				}
				return true;
			}
			return false;
		}

		void CCustomGrid::ForceRepaint()
		{
			if (m_pCanvas)
				m_pCanvas->setValid(false);
			Repaint(false);
		}

		bool CCustomGrid::SelectCell(const int column, const int row, ICustomGridService *service)
		{
			if (!m_aCells[row][column].Selected)
			{
				m_aCells[row][column].Selected = true;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setSelected(true);
				if (service)
					service->NotifyOnSelectCell(column, row, m_aCells[row][column].Item);
				if (OnSelectCell)
					OnSelectCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::DeselectCell(const int column, const int row, ICustomGridService *service)
		{
			if (m_aCells[row][column].Selected)
			{
				m_aCells[row][column].Selected = false;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setSelected(false);
				if (service)
					service->NotifyOnDeselectCell(column, row, m_aCells[row][column].Item);
				if (OnDeselectCell)
					OnDeselectCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::EnableCell(const int column, const int row, ICustomGridService *service)
		{
			if (!m_aCells[row][column].Enabled)
			{
				m_aCells[row][column].Enabled = true;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setEnabled(true);
				if (service)
					service->NotifyOnEnableCell(column, row, m_aCells[row][column].Item);
				if (OnEnableCell)
					OnEnableCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::DisableCell(const int column, const int row, ICustomGridService *service)
		{
			if (m_aCells[row][column].Enabled)
			{
				m_aCells[row][column].Enabled = false;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setEnabled(false);
				if (service)
					service->NotifyOnDisableCell(column, row, m_aCells[row][column].Item);
				if (OnDisableCell)
					OnDisableCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::ActivateCell(const int column, const int row, ICustomGridService *service)
		{
			if (!m_aCells[row][column].Active)
			{
				m_sActiveCell = { column, row };
				m_aCells[row][column].Active = true;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setActive(true);
				if (service)
					service->NotifyOnActivateCell(column, row, m_aCells[row][column].Item);
				if (OnActivateCell)
					OnActivateCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::DeactivateCell(const int column, const int row, ICustomGridService *service)
		{
			if (m_aCells[row][column].Active)
			{
				m_aCells[row][column].Active = false;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->setActive(false);
				if (service)
					service->NotifyOnDeactivateCell(column, row, m_aCells[row][column].Item);
				if (OnDeactivateCell)
					OnDeactivateCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::LeaveCell(const int column, const int row, ICustomGridService *service)
		{
			if (m_aCells[row][column].Hovered)
			{
				m_aCells[row][column].Hovered = false;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->QueryService()->setHovered(false);
				if (service)
					service->NotifyOnLeaveCell(column, row, m_aCells[row][column].Item);
				if (OnLeaveCell)
					OnLeaveCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::HoverCell(const int column, const int row, ICustomGridService *service)
		{
			if (!m_aCells[row][column].Hovered)
			{
				m_aCells[row][column].Hovered = true;
				if (m_aCells[row][column].Item)
					m_aCells[row][column].Item->QueryService()->setHovered(true);
				if (service)
					service->NotifyOnHoverCell(column, row, m_aCells[row][column].Item);
				if (OnHoverCell)
					OnHoverCell(this, column, row, m_aCells[row][column].Item);
				return true;
			}
			return false;
		}

		bool CCustomGrid::ScrollToCell(const Point &coords)
		{
			bool result{ false };
			PointF p{ getCellPosition(coords.X, coords.Y) };
			RectF client{ getClientRect() };
			if (m_bVScroll)
				client.Right += m_sPadding.Right - getVScroll()->getWidth();
			if (m_bHScroll)
				client.Bottom += m_sPadding.Bottom - getHScroll()->getHeight();
			if (client.is_valid() && !client.is_zero())
			{
				if (ntl::IsGreater<float>(m_sMaxScroll.X, 0))
				{
					for (int x = 0; x < (int)m_aColumns.size(); x++)
					{
						if (!m_aColumns[x].Fixed)
							break;
						client.Left += m_aColumns[x].Width + m_fGridWidth;
						if (ntl::IsLessOrEqual<float>(client.width(), 0))
							break;
					}
					if (ntl::IsGreater<float>(client.width(), 0))
					{
						float delta{ 0 };
						if (p.X < client.Left)
							delta = p.X - client.Left;
						else if (p.X + m_aColumns[coords.X].Width + m_fGridWidth >= client.Right)
						{
							delta = p.X + m_aColumns[coords.X].Width + m_fGridWidth - client.Right;
							if (p.X + delta < client.Left)
								delta = p.X + delta - client.Left;
						}
						if (ntl::IsNotEqual<float>(delta, 0))
						{
							m_sScroll.X = ntl::Clamp<float>(m_sScroll.X + delta, 0, m_sMaxScroll.X);
							if (m_bHScroll)
								getHScroll()->setScroll(m_sScroll.X);
							result = true;
						}
					}
				}
				if (ntl::IsGreater<float>(m_sMaxScroll.Y, 0))
				{
					for (int y = 0; y < (int)m_aRows.size(); y++)
					{
						if (!m_aRows[y].Fixed)
							break;
						client.Top += m_aRows[y].Height + m_fGridWidth;
						if (ntl::IsLessOrEqual<float>(client.height(), 0))
							break;
					}
					if (ntl::IsGreater<float>(client.height(), 0))
					{
						float delta{ 0 };
						if (p.Y < client.Top)
							delta = p.Y - client.Top;
						else if (p.Y + m_aRows[coords.Y].Height + m_fGridWidth >= client.Bottom)
						{
							delta = p.Y + m_aRows[coords.Y].Height + m_fGridWidth - client.Bottom;
							if (p.Y + delta < client.Top)
								delta = p.Y + delta - client.Top;
						}
						if (ntl::IsNotEqual<float>(delta, 0))
						{
							m_sScroll.Y = ntl::Clamp<float>(m_sScroll.Y + delta, 0, m_sMaxScroll.Y);
							if (m_bVScroll)
								getVScroll()->setScroll(m_sScroll.Y);
							result = true;
						}
					}
				}
			}
			return result;
		}

		bool CCustomGrid::ScrollToActiveCell()
		{
			if (m_sActiveCell.X >= 0)
				return ScrollToCell(m_sActiveCell);
			return false;
		}

		void CCustomGrid::CancelMouseDown(const bool check_capture, ICustomGridService *service)
		{
			if (m_eDownElement != Element::None)
			{
				switch (m_eDownElement)
				{
				case Element::VScroll:
					getVScroll()->NotifyOnMouseDownCancel();
					break;
				case Element::HScroll:
					getHScroll()->NotifyOnMouseDownCancel();
					break;
				default:
					break;
				}
				m_eDownElement = Element::None;
				/*if (m_hScrollTimer)
				{
					getForm()->DeleteTimer(m_hScrollTimer);
					m_hScrollTimer = 0;
				}*/
				if (check_capture && isCaptureMouse())
					getForm()->ReleaseCaptureMouse();
				if (service)
					service->NotifyOnMouseDownCancel();
			}
		}

		void CCustomGrid::LeaveAll()
		{
			switch (m_eHoveredElement)
			{
			case Element::VScroll:
				getVScroll()->NotifyOnMouseLeave();
				break;
			case Element::HScroll:
				getHScroll()->NotifyOnMouseLeave();
				break;
			case Element::Cell:
				LeaveCell(m_sHoveredCell.X, m_sHoveredCell.Y, cast<ICustomGridService*>(QueryService()));
				break;
			default:
				break;
			}
			m_eHoveredElement = Element::None;
		}
	#pragma endregion

	#pragma region Paint
		void CCustomGrid::Render()
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			State state{ getState() };
			PointF disp{ DispOnCanvas(m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			RectF all_rect{ AddShadow(getRect(), m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]) };
			if (PrepareCanvas(renderer, &m_pCanvas, all_rect))
			{
				CStoreTarget s_target{ renderer };
				renderer
					->ActivateTarget(m_pCanvas)
					->Clear(Color{ 0, 0, 0, 0 });

				// Background
				RectF rect{ disp.X, disp.Y, disp.X + getWidth(), disp.Y + getHeight() }, client{ getClientRect() };
				if (m_bVScroll)
					client.Right += m_sPadding.Right - getVScroll()->getWidth();
				if (m_bHScroll)
					client.Bottom += m_sPadding.Bottom - getHScroll()->getHeight();

				DrawBlockShadow(renderer, rect, m_aBorderRadius[(int)state], m_aShadowColor[(int)state], m_aShadowShift[(int)state], m_aShadowRadius[(int)state]);
				DrawSimpleBackground(renderer, rect, m_sBorderWidth, m_aBorderRadius[(int)state], m_aBorderColor[(int)state], m_aBackgroundColor[(int)state], m_aBackgroundGradient[(int)state]);
					
				if (client.is_valid() && !client.is_zero())
				{
					Block b1{ rect, m_sBorderWidth, m_aBorderRadius[(int)state], PointLocation::Inside };
					Block b2{ rect, AddElements(m_sBorderWidth, m_sPadding), m_aBorderRadius[(int)state], PointLocation::Inside };
					if (m_bVScroll)
						b2.Border.Right += getVScroll()->getWidth() - m_sPadding.Right;
					if (m_bHScroll)
						b2.Border.Bottom += getHScroll()->getHeight() - m_sPadding.Bottom;

					RenderGrid(renderer, rect, state, m_aBorderRadius[(int)state].has_positive() ? &b1 : nullptr);
					RenderCells(renderer, rect, &b2);
					RenderScrolls(renderer, rect, disp, state, &b1);
				}

				m_pCanvas->setValid(true);
			}
			DrawCanvas(renderer, getTransformMatrix(), m_pCanvas, disp);
		}

		void CCustomGrid::RenderGrid(IRenderer *renderer, const RectF &rect, const State state, const Block *block)
		{
			if (ntl::IsGreater<float>(m_fGridWidth, 0) && m_aGridColor[(int)state].A > 0 && m_aColumns.size() > 1 && m_aRows.size() > 1)
			{
				CStoreBlock s_block{ renderer };
				renderer->ActivateBlock(block);
				// Grid for common columns and rows
				RectF table_rect{
					m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X + rect.Left,
					m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y + rect.Top,
					m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X + m_sTableSize.X + rect.Left,
					m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y + m_sTableSize.Y + rect.Top
				};
				RectF client{
					m_sBorderWidth.Left + m_sPadding.Left + rect.Left,
					m_sBorderWidth.Top + m_sPadding.Top + rect.Top,
					getWidth() - m_sBorderWidth.Right - m_sPadding.Left + rect.Left,
					getHeight() - m_sBorderWidth.Bottom - m_sPadding.Bottom + rect.Top
				};
				RectF limit{ table_rect * client };
				if (limit.is_valid() && !limit.is_zero())
				{
					// Horizontal lines
					float y{ m_sBorderWidth.Top + m_sPadding.Top - m_sScroll.Y + rect.Top };
					for (auto &row : m_aRows)
					{
						y += row.Height;
						if (!row.Fixed && y < limit.Bottom && y + m_fGridWidth >= limit.Top)
						{
							RectF r{ RectF{ limit.Left, y, limit.Right, y + m_fGridWidth } * client };
							if (r.is_valid() && !r.is_zero())
								renderer->DrawRectangle(r, m_aGridColor[(int)state]);
						}
						y += m_fGridWidth;
					}
					// Vertical lines
					float x{ m_sBorderWidth.Left + m_sPadding.Left - m_sScroll.X + rect.Left };
					for (auto &column : m_aColumns)
					{
						x += column.Width;
						if (!column.Fixed && x < limit.Right && x + m_fGridWidth >= limit.Left)
						{
							RectF r{ RectF{ x, limit.Top, x + m_fGridWidth, limit.Bottom } * client };
							if (r.is_valid() && !r.is_zero())
								renderer->DrawRectangle(r, m_aGridColor[(int)state]);
						}
						x += m_fGridWidth;
					}
				}
				// Grid for fixed columns and rows
				table_rect = {
					m_sBorderWidth.Left + m_sPadding.Left + rect.Left,
					m_sBorderWidth.Top + m_sPadding.Top + rect.Top,
					m_sBorderWidth.Left + m_sPadding.Left + m_sTableSize.X + rect.Left,
					m_sBorderWidth.Top + m_sPadding.Top + m_sTableSize.Y + rect.Top
				};
				limit = table_rect * client;
				if (limit.is_valid() && !limit.is_zero())
				{
					// Horizontal lines(fixed rows)
					float y{ m_sBorderWidth.Top + m_sPadding.Top + rect.Top - m_sScroll.Y };
					for (auto &row : m_aRows)
					{
						y += row.Height;
						if (row.Fixed && y < limit.Bottom && y + m_fGridWidth >= limit.Top)
						{
							RectF r{ RectF{ limit.Left, y, limit.Right, y + m_fGridWidth } * client };
							if (r.is_valid() && !r.is_zero())
								renderer->DrawRectangle(r, m_aGridColor[(int)state]);
						}
						y += m_fGridWidth;
					}
					// Vertical lines(fixed columns)
					float x{ m_sBorderWidth.Left + m_sPadding.Left + rect.Left - m_sScroll.X };
					for (auto &column : m_aColumns)
					{
						x += column.Width;
						if (!column.Fixed && x < limit.Right && x + m_fGridWidth >= limit.Left)
						{
							RectF r{ RectF{ x, limit.Top, x + m_fGridWidth, limit.Bottom } * client };
							if (r.is_valid() && !r.is_zero())
								renderer->DrawRectangle(r, m_aGridColor[(int)state]);
						}
						x += m_fGridWidth;
					}
				}
			}
		}

		void CCustomGrid::RenderCells(IRenderer *renderer, const RectF &rect, const Block *block)
		{
			if (m_aColumns.size() > 0 && m_aRows.size() > 0)
			{
				ITexture *clip{ nullptr };
				PointF p{ 0, m_sBorderWidth.Top + m_sPadding.Top + rect.Top - m_sScroll.Y + m_sTableSize.Y };
				Mat4f m;
				for (int row_index = (int)m_aRows.size() - 1; row_index >= 0; row_index--)
				{
					p.Y -= m_aRows[row_index].Height + m_fGridWidth;
					if (m_aRows[row_index].Fixed)
						p.Y += m_sScroll.Y;
					if (p.Y < rect.Bottom && p.Y + m_aRows[row_index].Height >= rect.Top)
					{
						p.X = m_sBorderWidth.Left + m_sPadding.Left + rect.Left - m_sScroll.X + m_sTableSize.X;
						for (int column_index = (int)m_aColumns.size() - 1; column_index >= 0; column_index--)
						{
							p.X -= m_aColumns[column_index].Width + m_fGridWidth;
							if (m_aColumns[column_index].Fixed)
								p.X += m_sScroll.X;
							if (p.X < rect.Right && p.X + m_aColumns[column_index].Width >= rect.Left)
							{
								ntl::Translate<float>(m, std::round(p.X), std::round(p.Y), 0);
								CELL &cell{ m_aCells[row_index][column_index] };
								if (cell.OverflowHidden)
								{
									if (!clip)
										clip = renderer->CreateTexture(ntl::Round<int>(m_aColumns[column_index].Width), ntl::Round<int>(m_aRows[row_index].Height), 1, TextureFormat::RGBA, true);
									else
										clip->setSize(ntl::Round<int>(m_aColumns[column_index].Width), ntl::Round<int>(m_aRows[row_index].Height));
									if (clip)
									{
										CStorePrimitiveMatrix s_matrix{ renderer };
										renderer
											->ActivateTarget(clip)
											->Clear(Color{ 0, 0, 0, 0 })
											->ActivatePrimitiveMatrix(ntl::Inversed<float>(m))
											->DrawImage(m_pCanvas, 1)
											->ActivatePrimitiveMatrix(nullptr);
										RenderCell(column_index, row_index, cell.Item, Identity, nullptr);
										if (OnRenderCell)
											OnRenderCell(this, column_index, row_index, cell.Item, Identity, nullptr);
										CStoreBlock s_block{ renderer };
										renderer
											->ActivateTarget(m_pCanvas)
											->ActivateBlock(block)
											->ActivatePrimitiveMatrix(m)
											->DrawImage(clip, 1);
									}
								}
								else
								{
									RenderCell(column_index, row_index, cell.Item, m, block);
									if (OnRenderCell)
										OnRenderCell(this, column_index, row_index, cell.Item, m, block);
								}
							}
							if (m_aColumns[column_index].Fixed)
								p.X -= m_sScroll.X;
						}
					}
					if (m_aRows[row_index].Fixed)
						p.Y -= m_sScroll.Y;
				}
				if (clip)
					clip->Release();
			}
		}

		void CCustomGrid::RenderCell(const int column, const int row, IListItem *item, const Mat4f &matrix, const Block *block)
		{
			if (item)
				item->QueryService()->Render(matrix, block, false, nullptr);
		}

		void CCustomGrid::RenderScrolls(IRenderer *renderer, const RectF &rect, const PointF &disp, const State state, const Block *block)
		{
			if (m_bVScroll)
				getVScroll()->Render(false, ntl::Mat4Translate<float>(getVScroll()->getLeft() + disp.X, getVScroll()->getTop() + disp.Y, 0), block);
			if (m_bHScroll)
				getHScroll()->Render(false, ntl::Mat4Translate<float>(getHScroll()->getLeft() + disp.X, getHScroll()->getTop() + disp.Y, 0), block);
			if (m_bVScroll && m_bHScroll && m_aCornerColor[(int)state].A > 0)
			{
				RectF rect{
					getHScroll()->getLeft() + getHScroll()->getWidth() + disp.X,
					getVScroll()->getTop() + getVScroll()->getHeight() + disp.Y,
					getVScroll()->getLeft() + getVScroll()->getWidth() + disp.X,
					getHScroll()->getTop() + getHScroll()->getHeight() + disp.Y };
				CStoreBlock s_block{ renderer };
				renderer
					->ActivateBlock(block)
					->DrawRectangle(rect, m_aCornerColor[(int)state]);
			}
		}
	#pragma endregion
	}
}