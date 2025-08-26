// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/RectF.h"
#include "../IDrawGrid.h"
#include "CustomGrid.h"

namespace nitisa
{
	class IListItem;
	class IStyle;

	struct Block;

	namespace standard
	{
		class CCustomDrawGridService;

		// There is no items associated with cells. Everywhere where item is argument it is always nullptr
		class CCustomDrawGrid :public virtual IDrawGrid, public CCustomGrid
		{
			friend CCustomDrawGridService;
		public:
			enum class FixedCellState // Fixed rows and columns cell states
			{
				Normal, // Normal state
				Hovered, // Mouse pointer is over the cell
				Down, // Mouse button was down over the cell
				Disabled // The cell is disabled
			};
		private:
			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomDrawGrid *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomDrawGrid *control);
			};
		private:
			CGradientListener m_cGradientListener;
			int m_iFixedColumns;
			int m_iFixedRows;
			Color m_aFixedCellBackgroundColor[(int)FixedCellState::Disabled + 1];
			Gradient m_aFixedCellBackgroundGradient[(int)FixedCellState::Disabled + 1];
			RectF m_aFixedCellBorderWidth[(int)FixedCellState::Disabled + 1];
			BorderColor m_aFixedCellBorderColor[(int)FixedCellState::Disabled + 1];

			bool m_bIgnoreGradient;
			Point m_sDownCell;
		protected:
			void UpdateFromStyle(IStyle *style) override;
			void CreateColumn(float &width, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden) override;
			void CreateRow(float &height, bool &resizable, bool &autosize, bool &enabled, bool &fixed, bool &overflow_hidden) override;
			void RenderCell(const int column, const int row, IListItem *item, const Mat4f &matrix, const Block *block) override;
			IListItem * CreateItem(const int column, const int row) override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			// ICustomGrid setters
			bool setCellOverflowHidden(const int column, const int row, const bool value) override; // Only not fixed cells can be adjusted
			bool setColumnFixed(const int index, const bool value) override; // Not allowed. Use setFixedColumns() instead
			bool setColumnOverflowHidden(const int index, const bool value) override; // Only not fixed columns can be adjusted
			bool setRowFixed(const int index, const bool value) override; // Not allowed. Use setFixedRows() instead
			bool setRowOverflowHidden(const int index, const bool value) override; // Only fixed rows can be adjusted

			// IDrawGrid getters
			int getFixedColumns() override;
			int getFixedRows() override;

			// IDrawGrid setters
			bool setFixedColumns(const int value) override;
			bool setFixedRows(const int value) override;

			CCustomDrawGrid(const String &class_name);

			// Getters
			Color getFixedCellBackgroundColor(const FixedCellState state) const; // Return fixed cell background color
			Gradient *getFixedCellBackgroundGradient(const FixedCellState state); // Return fixed cell background gradient
			RectF getFixedCellBorderWidth(const FixedCellState state) const; // Return fixed cell border widths
			BorderColor getFixedCellBorderColor(const FixedCellState state) const; // Return fixed cell border colors

			// Setters
			bool setFixedCellBackgroundColor(const FixedCellState state, const Color &value); // Set fixed cell background color
			bool setFixedCellBorderWidth(const FixedCellState state, const RectF &value); // Set fixed cell border widths
			bool setFixedCellBorderColor(const FixedCellState state, const BorderColor &value); // Set fixed cell border colors
		};
	}
}