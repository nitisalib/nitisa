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
		CCustomStringGrid::CGradientListener::CGradientListener(CCustomStringGrid *control) :
			m_pControl{ control }
		{

		}

		void CCustomStringGrid::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient)
				m_pControl->ForceRepaint();
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CCustomStringGrid::CCustomStringGrid(const String &class_name) :
			CCustomDrawGrid(class_name),
			m_cGradientListener{ this },
			m_bActiveCellDotted{ true },
			m_bDefaultCellEditable{ true },
			m_sDefaultCellPadding{ 3, 3, 3, 3 },
			m_eDefaultCellTextAlign{ TextAlign::Left },
			m_eDefaultCellVerticalAlign{ VerticalAlign::Middle },
			m_sDefaultFixedCellPadding{ 3, 3, 3, 3 },
			m_eDefaultFixedCellTextAlign{ TextAlign::Center },
			m_eDefaultFixedCellVerticalAlign{ VerticalAlign::Middle },
			m_aCellBackgroundColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 64 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aCellColor{
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 0, 0, 0, 0 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 0, 0, 0, 0 } },
			m_aCellBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aActiveCellOutlineColor{
				Color{ 0, 0, 0, 255 },
				Color{ 0, 0, 0, 255 },
				Color{ 255, 255, 255, 255 },
				Color{ 255, 255, 255, 255 } },
			m_aActiveCellOutlineMask{
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100,
				0b11001100110011001100110011001100 },
			m_sFocusedCell{ -1, -1 },
			m_pTextInput{ nullptr },
			m_cListener{ this },
			m_bIgnoreGradient{ false }
		{
			OnChangeCell = nullptr;
			OnSetFocusCell = nullptr;
			OnKillFocusCell = nullptr;
			setService(new CCustomStringGridService(this), true);
		}

		CCustomStringGrid::~CCustomStringGrid()
		{
			if (m_pTextInput)
				m_pTextInput->Release();
		}

		void CCustomStringGrid::BeforeRelease()
		{
			m_aCells.clear();
			CCustomDrawGrid::BeforeRelease();
		}
	#pragma endregion

	#pragma region IControl setters
		bool CCustomStringGrid::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CCustomDrawGrid::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				m_sDefaultCellPadding *= s;
				m_sDefaultFixedCellPadding *= s;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IControl methods
		void CCustomStringGrid::Refresh(const bool refresh_children)
		{
			getTextInput()->Refresh();
			CCustomDrawGrid::Refresh(refresh_children);
		}
	#pragma endregion

	#pragma region ICustomGrid setters
		bool CCustomStringGrid::setColumns(const int value)
		{
			int old{ getColumns() };
			CLockRepaint lock{ this };
			if (CCustomDrawGrid::setColumns(value))
			{
				if (value > old) // Add columns
				{
					for (int x = old; x < value; x++)
						for (int y = 0; y < getRows(); y++)
						{
							CELL cell;
							cell.Text = L"";
							cell.Editable = m_bDefaultCellEditable;
							if (isColumnFixed(x) || isRowFixed(y))
							{
								cell.Padding = m_sDefaultFixedCellPadding;
								cell.TextAlign = m_eDefaultFixedCellTextAlign;
								cell.VerticalAlign = m_eDefaultFixedCellVerticalAlign;
							}
							else
							{
								cell.Padding = m_sDefaultCellPadding;
								cell.TextAlign = m_eDefaultCellTextAlign;
								cell.VerticalAlign = m_eDefaultCellVerticalAlign;
							}
							m_aCells[y].push_back(cell);
						}
				}
				else // Delete columns
				{
					for (auto &row : m_aCells)
						row.erase(row.begin() + value, row.end());
					if (m_sFocusedCell.X >= value)
						CancelFocus(false, nullptr);
				}
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setRows(const int value)
		{
			int old{ getRows() };
			CLockRepaint lock{ this };
			if (CCustomDrawGrid::setRows(value))
			{
				if (value > old) // Add columns
				{
					for (int y = old; y < value; y++)
					{
						m_aCells.push_back({});
						for (int x = 0; x < getColumns(); x++)
						{
							CELL cell;
							cell.Text = L"";
							cell.Editable = m_bDefaultCellEditable;
							if (isColumnFixed(x) || isRowFixed(y))
							{
								cell.Padding = m_sDefaultFixedCellPadding;
								cell.TextAlign = m_eDefaultFixedCellTextAlign;
								cell.VerticalAlign = m_eDefaultFixedCellVerticalAlign;
							}
							else
							{
								cell.Padding = m_sDefaultCellPadding;
								cell.TextAlign = m_eDefaultCellTextAlign;
								cell.VerticalAlign = m_eDefaultCellVerticalAlign;
							}
							m_aCells[y].push_back(cell);
						}
					}
				}
				else // Delete columns
				{
					m_aCells.erase(m_aCells.begin() + value, m_aCells.end());
					if (m_sFocusedCell.Y >= value)
						CancelFocus(false, nullptr);
				}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICustomGrid methods
		bool CCustomStringGrid::DeleteColumn(const int index)
		{
			if (index >= 0 && index < getColumns())
			{
				CLockRepaint lock{ this };
				if (index == m_sFocusedCell.X)
					CancelFocus(false, cast<IStringGridService*>(QueryService()));
				else if (m_sFocusedCell.X > index)
					m_sFocusedCell.X--;
				if (CCustomDrawGrid::DeleteColumn(index))
					for (int y = 0; y < getRows(); y++)
						m_aCells[y].erase(m_aCells[y].begin() + index);
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::DeleteRow(const int index)
		{
			if (index >= 0 && index < getRows())
			{
				CLockRepaint lock{ this };
				if (index == m_sFocusedCell.Y)
					CancelFocus(false, cast<IStringGridService*>(QueryService()));
				else if (m_sFocusedCell.Y > index)
					m_sFocusedCell.Y--;
				if (CCustomDrawGrid::DeleteRow(index))
					m_aCells.erase(m_aCells.begin() + index);
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IDrawGrid setters
		bool CCustomStringGrid::setFixedColumns(const int value)
		{
			int old{ getFixedColumns() };
			if (CCustomDrawGrid::setFixedColumns(value))
			{
				int columns{ ntl::Min<int>(ntl::Max<int>(old, getFixedColumns()), getColumns()) };
				for (int row = 0; row < getRows(); row++)
					for (int col = 0; col < columns; col++)
					{
						m_aCells[row][col].Text = L"";
						m_aCells[row][col].Editable = m_bDefaultCellEditable;
						if (isColumnFixed(col) || isRowFixed(row))
						{
							m_aCells[row][col].Padding = m_sDefaultFixedCellPadding;
							m_aCells[row][col].TextAlign = m_eDefaultFixedCellTextAlign;
							m_aCells[row][col].VerticalAlign = m_eDefaultFixedCellVerticalAlign;
						}
						else
						{
							m_aCells[row][col].Padding = m_sDefaultCellPadding;
							m_aCells[row][col].TextAlign = m_eDefaultCellTextAlign;
							m_aCells[row][col].VerticalAlign = m_eDefaultCellVerticalAlign;
						}
					}
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setFixedRows(const int value)
		{
			int old{ getFixedRows() };
			if (CCustomDrawGrid::setFixedRows(value))
			{
				int rows{ ntl::Min<int>(ntl::Max<int>(old, getFixedRows()), getRows()) };
				for (int row = 0; row < rows; row++)
					for (int col = 0; col < getColumns(); col++)
					{
						m_aCells[row][col].Text = L"";
						m_aCells[row][col].Editable = m_bDefaultCellEditable;
						if (isColumnFixed(col) || isRowFixed(row))
						{
							m_aCells[row][col].Padding = m_sDefaultFixedCellPadding;
							m_aCells[row][col].TextAlign = m_eDefaultFixedCellTextAlign;
							m_aCells[row][col].VerticalAlign = m_eDefaultFixedCellVerticalAlign;
						}
						else
						{
							m_aCells[row][col].Padding = m_sDefaultCellPadding;
							m_aCells[row][col].TextAlign = m_eDefaultCellTextAlign;
							m_aCells[row][col].VerticalAlign = m_eDefaultCellVerticalAlign;
						}
					}
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IStringGrid getters
		bool CCustomStringGrid::isCellEditable(const int column, const int row)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows())
				return m_aCells[row][column].Editable;
			return false;
		}

		bool CCustomStringGrid::isCellFocused(const int column, const int row)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows())
				return column == m_sFocusedCell.X && row == m_sFocusedCell.Y;
			return false;
		}

		String CCustomStringGrid::getCell(const int column, const int row)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows())
				return m_aCells[row][column].Text;
			return L"";
		}
	#pragma endregion

	#pragma region IStringGrid setters
		bool CCustomStringGrid::setCellEditable(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows() && value != m_aCells[row][column].Editable)
			{
				m_aCells[row][column].Editable = value;
				if (!value && column == m_sFocusedCell.X && row == m_sFocusedCell.Y)
				{
					CancelFocus(true, cast<IStringGridService*>(QueryService()));
					ForceRepaint();
				}
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setCellFocused(const int column, const int row, const bool value)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows() && isFocused() && isEnabled(true))
			{
				if (value)
				{
					CLockRepaint lock{ this };
					if ((column != m_sFocusedCell.X || row != m_sFocusedCell.Y) && m_aCells[row][column].Editable && setCellActive(column, row, true))
					{
						CancelFocus(true, cast<IStringGridService*>(QueryService()));
						ActivateFocus({ column, row }, cast<IStringGridService*>(QueryService()));
						return true;
					}
				}
				else
				{
					if (column == m_sFocusedCell.X && row == m_sFocusedCell.Y)
					{
						CancelFocus(true, cast<IStringGridService*>(QueryService()));
						ForceRepaint();
						return true;
					}
				}
			}
			return false;
		}

		bool CCustomStringGrid::setCell(const int column, const int row, const String &value)
		{
			if (column >= 0 && column < getColumns() && row >= 0 && row < getRows() && value != m_aCells[row][column].Text)
			{
				CancelFocus(true, cast<IStringGridService*>(QueryService()));
				m_aCells[row][column].Text = value;
				ForceRepaint();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		IBuiltInTextInput *CCustomStringGrid::getTextInput()
		{
			if (!m_pTextInput)
			{
				m_pTextInput = new CTextInput(this);
				m_pTextInput->setListener(&m_cListener);
			}
			return m_pTextInput;
		}

		bool CCustomStringGrid::isActiveCellDotted() const
		{
			return m_bActiveCellDotted;
		}

		bool CCustomStringGrid::isDefaultCellEditable() const
		{
			return m_bDefaultCellEditable;
		}

		RectF CCustomStringGrid::getDefaultCellPadding() const
		{
			return m_sDefaultCellPadding;
		}

		TextAlign CCustomStringGrid::getDefaultCellTextAlign() const
		{
			return m_eDefaultCellTextAlign;
		}

		VerticalAlign CCustomStringGrid::getDefaultCellVerticalAlign() const
		{
			return m_eDefaultCellVerticalAlign;
		}

		RectF CCustomStringGrid::getDefaultFixedCellPadding() const
		{
			return m_sDefaultFixedCellPadding;
		}

		TextAlign CCustomStringGrid::getDefaultFixedCellTextAlign() const
		{
			return m_eDefaultFixedCellTextAlign;
		}

		VerticalAlign CCustomStringGrid::getDefaultFixedCellVerticalAlign() const
		{
			return m_eDefaultFixedCellVerticalAlign;
		}

		Color CCustomStringGrid::getCellBackgroundColor(const CellState state) const
		{
			return m_aCellBackgroundColor[(int)state];
		}

		Color CCustomStringGrid::getCellColor(const CellState state) const
		{
			return m_aCellColor[(int)state];
		}

		Gradient *CCustomStringGrid::getCellBackgroundGradient(const CellState state)
		{
			return &m_aCellBackgroundGradient[(int)state];
		}

		Color CCustomStringGrid::getActiveCellOutlineColor(const ActiveCellState state) const
		{
			return m_aActiveCellOutlineColor[(int)state];
		}

		unsigned int CCustomStringGrid::getActiveCellOutlineMask(const ActiveCellState state) const
		{
			return m_aActiveCellOutlineMask[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomStringGrid::setTextInput(IBuiltInTextInput *value)
		{
			if (value && value != m_pTextInput)
			{
				if (m_sFocusedCell.X >= 0)
					CancelFocus(true, cast<IStringGridService*>(QueryService()));
				if (m_pTextInput)
					m_pTextInput->Release();
				m_pTextInput = value;
				m_pTextInput->setListener(&m_cListener);
				ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setActiveCellDotted(const bool value)
		{
			if (value != m_bActiveCellDotted)
			{
				m_bActiveCellDotted = value;
				if (getActiveCell().X >= 0)
					ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultCellEditable(const bool value)
		{
			if (value != m_bDefaultCellEditable)
			{
				m_bDefaultCellEditable = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultCellPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sDefaultCellPadding))
			{
				m_sDefaultCellPadding = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultCellTextAlign(const TextAlign value)
		{
			if (value != m_eDefaultCellTextAlign)
			{
				m_eDefaultCellTextAlign = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultCellVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eDefaultCellVerticalAlign)
			{
				m_eDefaultCellVerticalAlign = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultFixedCellPadding(const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_sDefaultFixedCellPadding))
			{
				m_sDefaultFixedCellPadding = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultFixedCellTextAlign(const TextAlign value)
		{
			if (value != m_eDefaultFixedCellTextAlign)
			{
				m_eDefaultFixedCellTextAlign = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setDefaultFixedCellVerticalAlign(const VerticalAlign value)
		{
			if (value != m_eDefaultFixedCellVerticalAlign)
			{
				m_eDefaultFixedCellVerticalAlign = value;
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setCellBackgroundColor(const CellState state, const Color &value)
		{
			if (value != m_aCellBackgroundColor[(int)state])
			{
				m_aCellBackgroundColor[(int)state] = value;
				if (m_aCellBackgroundGradient[(int)state].getPointCount() < 2)
					ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setCellColor(const CellState state, const Color &value)
		{
			if (value != m_aCellColor[(int)state])
			{
				m_aCellColor[(int)state] = value;
				ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setActiveCellOutlineColor(const ActiveCellState state, const Color &value)
		{
			if (value != m_aActiveCellOutlineColor[(int)state])
			{
				m_aActiveCellOutlineColor[(int)state] = value;
				if (getActiveCell().X >= 0 && m_bActiveCellDotted && m_aActiveCellOutlineMask[(int)state] > 0)
					ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomStringGrid::setActiveCellOutlineMask(const ActiveCellState state, const unsigned int value)
		{
			if (value != m_aActiveCellOutlineMask[(int)state])
			{
				m_aActiveCellOutlineMask[(int)state] = value;
				if (getActiveCell().X >= 0 && m_bActiveCellDotted && m_aActiveCellOutlineColor[(int)state].A > 0)
					ForceRepaint();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomStringGrid::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			style->getOption(m_sClassName + L".ActiveCellDotted", m_bActiveCellDotted);
			for (int i = 0; i <= (int)CellState::Disabled; i++)
			{
				String state;
				switch ((CellState)i)
				{
				case CellState::Normal:
					state = L"Normal";
					break;
				case CellState::Hovered:
					state = L"Hovered";
					break;
				case CellState::Focused:
					state = L"Focused";
					break;
				case CellState::FocusedHovered:
					state = L"FocusedHovered";
					break;
				case CellState::Selected:
					state = L"Selected";
					break;
				case CellState::SelectedHovered:
					state = L"SelectedHovered";
					break;
				case CellState::Active:
					state = L"Active";
					break;
				case CellState::ActiveHovered:
					state = L"ActiveHovered";
					break;
				case CellState::ActiveSelected:
					state = L"ActiveSelected";
					break;
				case CellState::ActiveSelectedHovered:
					state = L"ActiveSelectedHovered";
					break;
				default:
					state = L"Disabled";
				}
				style->getOption(m_sClassName + L".CellBackgroundColor[" + state + L"]", m_aCellBackgroundColor[i]);
				style->getOption(m_sClassName + L".CellColor[" + state + L"]", m_aCellColor[i]);
				style->getOption(m_sClassName + L".CellBackgroundGradient[" + state + L"]", m_aCellBackgroundGradient[i]);
			}
			for (int i = 0; i <= (int)ActiveCellState::SelectedHovered; i++)
			{
				String state;
				switch ((ActiveCellState)i)
				{
				case ActiveCellState::Hovered:
					state = L"Hovered";
					break;
				case ActiveCellState::Selected:
					state = L"Selected";
					break;
				case ActiveCellState::SelectedHovered:
					state = L"SelectedHovered";
					break;
				default:
					state = L"Normal";
				}
				style->getOption(m_sClassName + L".ActiveCellOutlineColor[" + state + L"]", m_aActiveCellOutlineColor[i]);
				style->getOption(m_sClassName + L".ActiveCellOutlineMask[" + state + L"]", m_aActiveCellOutlineMask[i]);
			}
			m_bIgnoreGradient = false;
			CCustomDrawGrid::UpdateFromStyle(style);
		}

		CCustomStringGrid::CellState CCustomStringGrid::getCellState(const int column, const int row) // Only for regular cells
		{
			if (!isColumnEnabled(column) || !isRowEnabled(row) || !isCellEnabled(column, row))
				return CellState::Disabled;
			// Focused
			if (column == m_sFocusedCell.X && row == m_sFocusedCell.Y)
			{
				if (isCellHovered(column, row))
					return CellState::FocusedHovered;
				return CellState::Focused;
			}
			// Active
			if (isCellActive(column, row))
			{
				if (isCellSelected(column, row))
				{
					if (isCellHovered(column, row))
						return CellState::ActiveSelectedHovered;
					return CellState::ActiveSelected;
				}
				if (isCellHovered(column, row))
					return CellState::ActiveHovered;
				return CellState::Active;
			}
			// Selected
			if (isCellSelected(column, row))
			{
				if (isCellHovered(column, row))
					return CellState::SelectedHovered;
				return CellState::Selected;
			}
			// Hovered
			if (isCellHovered(column, row))
				return CellState::Hovered;
			// Normal
			return CellState::Normal;
		}

		CCustomStringGrid::ActiveCellState CCustomStringGrid::getActiveCellState()
		{
			Point p{ getActiveCell() };
			if (isCellSelected(p.X, p.Y))
			{
				if (isCellHovered(p.X, p.Y))
					return ActiveCellState::SelectedHovered;
				return ActiveCellState::Selected;
			}
			if (isCellHovered(p.X, p.Y))
				return ActiveCellState::Hovered;
			return ActiveCellState::Normal;
		}

		PointF CCustomStringGrid::CalculateTextPosition(const String &text, const PointF &size, const RectF &padding, const TextAlign text_align, const VerticalAlign vertical_align,
			IRenderer *renderer, IPlatformFont *pf, const float distance)
		{
			PointF result, text_size{ pf->getStringSize(text, distance) };
			switch (text_align)
			{
			case TextAlign::Center:
				result.X = (padding.Left + size.X - padding.Right - text_size.X) * 0.5f;
				break;
			case TextAlign::Right:
				result.X = size.X - padding.Right - text_size.X;
				break;
			default:
				result.X = padding.Left;
			}
			switch (vertical_align)
			{
			case VerticalAlign::Middle:
				result.Y = (padding.Top + size.Y - padding.Bottom - text_size.Y) * 0.5f;
				break;
			case VerticalAlign::Bottom:
				result.Y = size.Y - padding.Bottom - text_size.Y;
				break;
			default:
				result.Y = padding.Top;
			}
			return result;
		}

		void CCustomStringGrid::ActivateFocus(const Point &coords, IStringGridService *service)
		{
			m_sFocusedCell = coords;
			getTextInput()->setText(m_aCells[coords.Y][coords.X].Text);
			getTextInput()->SelectAll();
			getTextInput()->setFocused(true);
			if (service)
				service->NotifyOnSetFocusCell(coords.X, coords.Y);
			if (OnSetFocusCell)
				OnSetFocusCell(this, coords.X, coords.Y);
		}

		void CCustomStringGrid::CancelFocus(const bool save, IStringGridService *service)
		{
			if (m_sFocusedCell.X >= 0)
			{
				if (save && m_aCells[m_sFocusedCell.Y][m_sFocusedCell.X].Text != getTextInput()->getText())
				{
					bool allowed{ true };
					if (service)
						service->NotifyOnCellChange(m_sFocusedCell.X, m_sFocusedCell.Y, getTextInput()->getText(), allowed);
					if (allowed)
					{
						if (OnChangeCell)
							OnChangeCell(this, m_sFocusedCell.X, m_sFocusedCell.Y, getTextInput()->getText(), allowed);
						if (allowed)
							m_aCells[m_sFocusedCell.Y][m_sFocusedCell.X].Text = getTextInput()->getText();
					}
				}
				if (service)
					service->NotifyOnKillFocusCell(m_sFocusedCell.X, m_sFocusedCell.Y);
				if (OnKillFocusCell)
					OnKillFocusCell(this, m_sFocusedCell.X, m_sFocusedCell.Y);
				m_sFocusedCell = { -1, -1 };
				getTextInput()->setFocused(false);
			}
		}
	#pragma endregion

	#pragma region Paint
		void CCustomStringGrid::RenderCell(const int column, const int row, IListItem *item, const Mat4f &matrix, const Block *block)
		{
			IRenderer *renderer{ getForm()->getRenderer() };
			// Fixed. Background is handled by parent, render only caption
			if (isColumnFixed(column) || isRowFixed(row))
			{
				CCustomDrawGrid::RenderCell(column, row, item, matrix, block);
				if (!m_aCells[row][column].Text.empty() && getFont()->Color.A > 0)
				{
					IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
					float distance{ getFont()->Distance };
					PointF p{ CalculateTextPosition(m_aCells[row][column].Text, PointF{ getColumnWidth(column), getRowHeight(row) }, m_aCells[row][column].Padding, m_aCells[row][column].TextAlign,
						m_aCells[row][column].VerticalAlign, renderer, pf, distance) };
					CStoreBlock s_block{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBlock(block)
						->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(std::round(p.X), std::round(p.Y), 0))
						->DrawText(m_aCells[row][column].Text, pf, distance, getFont()->Color);
				}
				return;
			}
			// Background
			CStoreBlock s_block{ renderer };
			renderer->ActivateBlock(block);
			CellState cell_state{ getCellState(column, row) };
			if (m_aCellBackgroundGradient[(int)cell_state].getPointCount() >= 2)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&matrix)
					->DrawGradient(RectF{ 0, 0, getColumnWidth(column), getRowHeight(row) }, m_aCellBackgroundGradient[(int)cell_state]);
			}
			else if (m_aCellBackgroundColor[(int)cell_state].A > 0)
			{
				CStorePrimitiveMatrix s_matrix{ renderer };
				renderer
					->ActivatePrimitiveMatrix(&matrix)
					->DrawRectangle(RectF{ 0, 0, getColumnWidth(column), getRowHeight(row) }, m_aCellBackgroundColor[(int)cell_state]);
			}
			// Cell content
			if (column == m_sFocusedCell.X && row == m_sFocusedCell.Y && isEnabled(true))
			{
				PointF size{
					getColumnWidth(column) - m_aCells[row][column].Padding.Left - m_aCells[row][column].Padding.Right,
					getRowHeight(row) - m_aCells[row][column].Padding.Top - m_aCells[row][column].Padding.Bottom };
				if (ntl::IsGreater<float>(size.X, 0) && ntl::IsGreater<float>(size.Y, 0))
				{
					getTextInput()->setSize(size);
					getTextInput()->Render(false, matrix * ntl::Mat4Translate<float>(m_aCells[row][column].Padding.Left, m_aCells[row][column].Padding.Top, 0), block);
				}
				return;
			}
			else if (!m_aCells[row][column].Text.empty())
			{
				Color color{ m_aCellColor[(int)cell_state].A > 0 ? m_aCellColor[(int)cell_state] : getFont()->Color };
				if (color.A > 0)
				{
					IPlatformFont *pf{ getFont()->getPlatformFont(renderer) };
					float distance{ getFont()->Distance };
					PointF p{ CalculateTextPosition(m_aCells[row][column].Text,{ getColumnWidth(column), getRowHeight(row) }, m_aCells[row][column].Padding, m_aCells[row][column].TextAlign,
						m_aCells[row][column].VerticalAlign, renderer, pf, distance) };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivatePrimitiveMatrix(matrix * ntl::Mat4Translate<float>(std::round(p.X), std::round(p.Y), 0))
						->DrawText(m_aCells[row][column].Text, pf, distance, color);
				}
			}
			// Active cell dotted borders
			if (isCellActive(column, row) && m_bActiveCellDotted)
			{
				ActiveCellState active_cell_state{ getActiveCellState() };
				if (m_aActiveCellOutlineColor[(int)active_cell_state].A > 0 && m_aActiveCellOutlineMask[(int)active_cell_state])
				{
					CStoreBitmask s_bitmask{ renderer };
					CStorePrimitiveMatrix s_matrix{ renderer };
					renderer
						->ActivateBitmask(Bitmask{ m_aActiveCellOutlineMask[(int)active_cell_state], 0, true, false })
						->ActivatePrimitiveMatrix(&matrix)
						->DrawLines({
							PointF{ 1, 0 },
							PointF{ getColumnWidth(column), 0 },
							PointF{ getColumnWidth(column), getRowHeight(row) - 1 },
							PointF{ 1, getRowHeight(row) - 1 },
							PointF{ 1, 0 } },
							m_aActiveCellOutlineColor[(int)active_cell_state],
							false);
				}
			}
		}
	#pragma endregion
	}
}