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
	#pragma region CGradientListener
		CCustomDrawGrid::CGradientListener::CGradientListener(CCustomDrawGrid *control) :
			m_pControl{ control }
		{

		}

		void CCustomDrawGrid::CGradientListener::NotifyOnChange()
		{
			if (!m_pControl->m_bIgnoreGradient && (m_pControl->getFixedColumns() > 0 || m_pControl->getFixedRows() > 0) && m_pControl->getColumns() > 0 && m_pControl->getRows() > 0)
				m_pControl->ForceRepaint();
		}
	#pragma endregion

	#pragma region Constructor & destructor
		CCustomDrawGrid::CCustomDrawGrid(const String &class_name) :
			CCustomGrid(class_name),
			m_cGradientListener{ this },
			m_iFixedColumns{ 1 },
			m_iFixedRows{ 1 },
			m_aFixedCellBackgroundColor{
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 255, 255 },
				Color{ 240, 240, 240, 255 },
				Color{ 240, 240, 240, 255 } },
			m_aFixedCellBackgroundGradient{
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener },
				Gradient{ &m_cGradientListener } },
			m_aFixedCellBorderWidth{
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 1, 1, 1, 1 },
				RectF{ 0, 0, 0, 0 } },
			m_aFixedCellBorderColor{
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 }, Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 } },
				BorderColor{ Color{ 160, 160, 160, 255 }, Color{ 160, 160, 160, 255 }, Color{ 255, 255, 255, 255 }, Color{ 255, 255, 255, 255 } },
				BorderColor{ Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } } },
			m_bIgnoreGradient{ false },
			m_sDownCell{ -1, -1 }
		{
			setService(new CCustomDrawGridService(this), true);
		}
	#pragma endregion

	#pragma region IControl setters
		bool CCustomDrawGrid::setDPI(const Point &value)
		{
			Point old{ getDPI() };
			CLockRepaint lock{ this };
			if (CCustomGrid::setDPI(value))
			{
				PointF s{ (float)value.X / (float)old.X, (float)value.Y / (float)old.Y };
				for (int i = 0; i <= (int)FixedCellState::Disabled; i++)
					m_aFixedCellBorderWidth[i] *= s;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region ICustomGrid setters
		bool CCustomDrawGrid::setCellOverflowHidden(const int column, const int row, const bool value)
		{
			if (column >= m_iFixedColumns || row >= m_iFixedRows)
				return CCustomGrid::setCellOverflowHidden(column, row, value);
			return false;
		}

		bool CCustomDrawGrid::setColumnFixed(const int index, const bool value)
		{
			return false;
		}

		bool CCustomDrawGrid::setColumnOverflowHidden(const int index, const bool value)
		{
			if (index >= m_iFixedColumns)
				return CCustomGrid::setColumnOverflowHidden(index, value);
			return false;
		}

		bool CCustomDrawGrid::setRowFixed(const int index, const bool value)
		{
			return false;
		}

		bool CCustomDrawGrid::setRowOverflowHidden(const int index, const bool value)
		{
			if (index >= m_iFixedRows)
				return CCustomGrid::setRowOverflowHidden(index, value);
			return false;
		}
	#pragma endregion

	#pragma region IDrawGrid getters
		int CCustomDrawGrid::getFixedColumns()
		{
			return m_iFixedColumns;
		}

		int CCustomDrawGrid::getFixedRows()
		{
			return m_iFixedRows;
		}
	#pragma endregion

	#pragma region IDrawGrid setters
		bool CCustomDrawGrid::setFixedColumns(const int value)
		{
			if (value >= 0 && value != m_iFixedColumns)
			{
				CLockRepaint lock{ this };
				for (int x = ntl::Min<int>(m_iFixedColumns, value); x < ntl::Max<int>(m_iFixedColumns, value) && x < getColumns(); x++)
					CCustomGrid::setColumnFixed(x, x < value);
				m_iFixedColumns = value;
				return true;
			}
			return false;
		}

		bool CCustomDrawGrid::setFixedRows(const int value)
		{
			if (value >= 0 && value != m_iFixedRows)
			{
				CLockRepaint lock{ this };
				for (int y = ntl::Min<int>(m_iFixedRows, value); y < ntl::Max<int>(m_iFixedRows, value) && y < getRows(); y++)
					CCustomGrid::setRowFixed(y, y < value);
				m_iFixedRows = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Getters
		Color CCustomDrawGrid::getFixedCellBackgroundColor(const FixedCellState state) const
		{
			return m_aFixedCellBackgroundColor[(int)state];
		}

		Gradient *CCustomDrawGrid::getFixedCellBackgroundGradient(const FixedCellState state)
		{
			return &m_aFixedCellBackgroundGradient[(int)state];
		}

		RectF CCustomDrawGrid::getFixedCellBorderWidth(const FixedCellState state) const
		{
			return m_aFixedCellBorderWidth[(int)state];
		}

		BorderColor CCustomDrawGrid::getFixedCellBorderColor(const FixedCellState state) const
		{
			return m_aFixedCellBorderColor[(int)state];
		}
	#pragma endregion

	#pragma region Setters
		bool CCustomDrawGrid::setFixedCellBackgroundColor(const FixedCellState state, const Color &value)
		{
			if (value != m_aFixedCellBackgroundColor[(int)state])
			{
				m_aFixedCellBackgroundColor[(int)state] = value;
				if ((m_iFixedColumns > 0 || m_iFixedRows > 0) && getColumns() > 0 && getRows() > 0)
					ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomDrawGrid::setFixedCellBorderWidth(const FixedCellState state, const RectF &value)
		{
			if (!value.has_negative() && IsNotEqual(value, m_aFixedCellBorderWidth[(int)state]))
			{
				m_aFixedCellBorderWidth[(int)state] = value;
				if ((m_iFixedColumns > 0 || m_iFixedRows > 0) && getColumns() > 0 && getRows() > 0)
					ForceRepaint();
				return true;
			}
			return false;
		}

		bool CCustomDrawGrid::setFixedCellBorderColor(const FixedCellState state, const BorderColor &value)
		{
			if (value != m_aFixedCellBorderColor[(int)state])
			{
				m_aFixedCellBorderColor[(int)state] = value;
				if ((m_iFixedColumns > 0 || m_iFixedRows > 0) && getColumns() > 0 && getRows() > 0 && m_aFixedCellBorderWidth[(int)state].has_positive())
					ForceRepaint();
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region Helpers
		void CCustomDrawGrid::UpdateFromStyle(IStyle *style)
		{
			m_bIgnoreGradient = true;
			for (int i = 0; i <= (int)FixedCellState::Disabled; i++)
			{
				String state;
				switch ((FixedCellState)i)
				{
				case FixedCellState::Normal:
					state = L"FixedCellState::Normal";
					break;
				case FixedCellState::Hovered:
					state = L"FixedCellState::Hovered";
					break;
				case FixedCellState::Down:
					state = L"FixedCellState::Down";
					break;
				default:
					state = L"FixedCellState::Disabled";
				}
				style->getOption(m_sClassName + L".FixedCellBackgroundColor[" + state + L"]", m_aFixedCellBackgroundColor[i]);
				style->getOption(m_sClassName + L".FixedCellBackgroundGradient[" + state + L"]", m_aFixedCellBackgroundGradient[i]);
				style->getOption(m_sClassName + L".FixedCellBorderWidth[" + state + L"]", m_aFixedCellBorderWidth[i]);
				style->getOption(m_sClassName + L".FixedCellBorderColor[" + state + L"]", m_aFixedCellBorderColor[i]);
			}
			m_bIgnoreGradient = true;
			CCustomGrid::UpdateFromStyle(style);
		}

		void CCustomDrawGrid::CreateColumn(float &width, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden)
		{
			CCustomGrid::CreateColumn(width, resizable, autosize, enabled, fixed, overflow_hidden);
			fixed = getColumns() < m_iFixedColumns;
			if (fixed)
				overflow_hidden = true;
		}

		void CCustomDrawGrid::CreateRow(float &height, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden)
		{
			CCustomGrid::CreateRow(height, resizable, autosize, enabled, fixed, overflow_hidden);
			fixed = getRows() < m_iFixedRows;
			if (fixed)
				overflow_hidden = true;
		}

		IListItem *CCustomDrawGrid::CreateItem(const int column, const int row)
		{
			return nullptr;
		}
	#pragma endregion

	#pragma region Paint
		void CCustomDrawGrid::RenderCell(const int column, const int row, IListItem *item, const Mat4f &matrix, const Block *block)
		{
			if (isColumnFixed(column) || isRowFixed(row))
			{
				IRenderer *renderer{ getForm()->getRenderer() };
				FixedCellState state;
				if (!isColumnEnabled(column) || !isRowEnabled(row) || !isCellEnabled(column, row))
					state = FixedCellState::Disabled;
				else if (column == m_sDownCell.X && row == m_sDownCell.Y)
					state = FixedCellState::Down;
				else if (isCellHovered(column, row))
					state = FixedCellState::Hovered;
				else
					state = FixedCellState::Normal;
				Block b{ RectF{ 0, 0, getColumnWidth(column), getRowHeight(row) }, m_aFixedCellBorderWidth[(int)state], RectF{ 0, 0, 0, 0 }, PointLocation::Inside };
				if (m_aFixedCellBorderWidth[(int)state].has_positive())
				{
					BlockColors colors{
						m_aFixedCellBorderColor[(int)state].Left,
						m_aFixedCellBorderColor[(int)state].Top,
						m_aFixedCellBorderColor[(int)state].Right,
						m_aFixedCellBorderColor[(int)state].Bottom,
						m_aFixedCellBackgroundGradient[(int)state].getPointCount() >= 2 ? Color{ 0, 0, 0, 0 } : m_aFixedCellBackgroundColor[(int)state],
						Color{ 0, 0, 0, 0 }
					};
					if (m_aFixedCellBackgroundGradient[(int)state].getPointCount() >= 2)
						renderer->DrawGradient(b.Rect, m_aFixedCellBackgroundGradient[(int)state]);
					if (colors[0].A > 0 || colors[1].A > 0 || colors[2].A > 0 || colors[3].A > 0 || colors[4].A > 0)
						renderer->DrawBlock(b.Rect, b.Border, b.Radius, colors);
				}
				else
				{
					if (m_aFixedCellBackgroundGradient[(int)state].getPointCount() >= 2)
						renderer->DrawGradient(b.Rect, m_aFixedCellBackgroundGradient[(int)state]);
					else if (m_aFixedCellBackgroundColor[(int)state].A > 0)
						renderer->DrawRectangle(b.Rect, m_aFixedCellBackgroundColor[(int)state]);
				}
			}
			CCustomGrid::RenderCell(column, row, item, matrix, block);
		}
	#pragma endregion
	}
}