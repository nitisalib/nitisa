// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/TextInput/BuiltInTextInput.h"
#include "Nitisa/BuiltInControls/IBuiltInTextInputListener.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Core/TextAlign.h"
#include "Nitisa/Core/VerticalAlign.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../DrawGrid/CustomDrawGrid.h"
#include "../IStringGrid.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInTextInput;
	class IControl;
	class IListItem;
	class IRenderer;
	class IStyle;

	struct Block;

	namespace standard
	{
		class CCustomStringGridService;

		class CCustomStringGrid :public virtual IStringGrid, public CCustomDrawGrid
		{
			friend CCustomStringGridService;
		public:
			enum class CellState // Cell states
			{
				Normal, // Normal
				Hovered, // Hovered
				Focused, // Cell is being edited
				FocusedHovered, // Cell is being edited and mouse pointer is over the cell
				Selected, // Selected
				SelectedHovered, // Selected and mouse pointer is over the cell
				Active, // Cell is active
				ActiveHovered, // Cell is active and mouse pointer is over the cell
				ActiveSelected, // Cell is active and selected
				ActiveSelectedHovered, // Cell is active, and selected, and mouse pointer is over the cell
				Disabled // Cell is disabled
			};

			enum class ActiveCellState // Active cell states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over the cell
				Selected, // Selected
				SelectedHovered // Selected and mouse pointer is over the cell
			};
		private:
			class CTextInput :public CBuiltInTextInput
			{
			private:
				CCustomStringGrid * m_pControl;
			public:
				IControl * getControl() override;
				State getState() override;

				CTextInput(CCustomStringGrid *control);
			};

			class CTextInputListener :public virtual IBuiltInTextInputListener
			{
			private:
				CCustomStringGrid * m_pControl;
			public:
				CTextInputListener(CCustomStringGrid *control);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChanged(IBuiltInControl *sender) override;
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomStringGrid *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomStringGrid *control);
			};

			struct CELL
			{
				String Text;
				bool Editable;
				RectF Padding;
				nitisa::TextAlign TextAlign;
				nitisa::VerticalAlign VerticalAlign;
			};
		private:
			CGradientListener m_cGradientListener;
			bool m_bActiveCellDotted;
			bool m_bDefaultCellEditable;
			RectF m_sDefaultCellPadding;
			TextAlign m_eDefaultCellTextAlign;
			VerticalAlign m_eDefaultCellVerticalAlign;
			RectF m_sDefaultFixedCellPadding;
			TextAlign m_eDefaultFixedCellTextAlign;
			VerticalAlign m_eDefaultFixedCellVerticalAlign;
			Color m_aCellBackgroundColor[(int)CellState::Disabled + 1];
			Color m_aCellColor[(int)CellState::Disabled + 1];
			Gradient m_aCellBackgroundGradient[(int)CellState::Disabled + 1];
			Color m_aActiveCellOutlineColor[(int)ActiveCellState::SelectedHovered + 1];
			unsigned int m_aActiveCellOutlineMask[(int)ActiveCellState::SelectedHovered + 1];

			std::vector<std::vector<CELL>> m_aCells;
			Point m_sFocusedCell;
			IBuiltInTextInput *m_pTextInput;
			CTextInputListener m_cListener;
			bool m_bIgnoreGradient;

			CellState getCellState(const int column, const int row);
			ActiveCellState getActiveCellState();
			PointF CalculateTextPosition(const String &text, const PointF &size, const RectF &padding, const TextAlign text_align, const VerticalAlign vertical_align,
				IRenderer *renderer, IPlatformFont *pf, const float distance);
			void ActivateFocus(const Point &coords, IStringGridService *service);
			void CancelFocus(const bool save, IStringGridService *service);
		protected:
			void UpdateFromStyle(IStyle *style) override;
			void RenderCell(const int column, const int row, IListItem *item, const Mat4f &matrix, const Block *block) override;
		protected:
			void BeforeRelease() override;
		public:
			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// ICustomGrid setters
			bool setColumns(const int value) override;
			bool setRows(const int value) override;

			// ICustomGrid methods
			bool DeleteColumn(const int index) override;
			bool DeleteRow(const int index) override;

			// IDrawGrid setters
			bool setFixedColumns(const int value) override;
			bool setFixedRows(const int value) override;

			// IStringGrid getters
			bool isCellEditable(const int column, const int row) override;
			bool isCellFocused(const int column, const int row) override;
			String getCell(const int column, const int row) override;

			// IStringGrid setters
			bool setCellEditable(const int column, const int row, const bool value) override;
			bool setCellFocused(const int column, const int row, const bool value) override;
			bool setCell(const int column, const int row, const String &value) override;

			CCustomStringGrid(const String &class_name);
			~CCustomStringGrid() override;

			IBuiltInTextInput *getTextInput(); // Return text input
			bool isActiveCellDotted() const; // Return whether active cell should have dotted border. Default true
			bool isDefaultCellEditable() const; // Return whether a cell is editable by default. Default true
			RectF getDefaultCellPadding() const; // Return cell default padding. Default { 3, 3, 3, 3 }
			TextAlign getDefaultCellTextAlign() const; // Return cell default text horizontal alignment. Default taLeft
			VerticalAlign getDefaultCellVerticalAlign() const; // Return cell default vertical alignment. Default VerticalAlign::Middle
			RectF getDefaultFixedCellPadding() const; // Return fixed cell default padding. Default { 3, 3, 3, 3 }
			TextAlign getDefaultFixedCellTextAlign() const; // Return fixed cell default text horizontal alignment. Default TextAlign::Center
			VerticalAlign getDefaultFixedCellVerticalAlign() const; // Return fixed cell default text vertical alignment. Default VerticalAlign::Middle
			Color getCellBackgroundColor(const CellState state) const; // Return cell background color
			Color getCellColor(const CellState state) const; // Return cell text color
			Gradient *getCellBackgroundGradient(const CellState state); // Return cell background gradient
			Color getActiveCellOutlineColor(const ActiveCellState state) const; // Return active cell outline border color
			unsigned int getActiveCellOutlineMask(const ActiveCellState state) const; // Return active cell outline mask
			
			bool setTextInput(IBuiltInTextInput *value); // Set new text input
			bool setActiveCellDotted(const bool value); // Set whether active cell should have dotted border
			bool setDefaultCellEditable(const bool value); // Set whether a cell is editable by default
			bool setDefaultCellPadding(const RectF &value); // Set cell default padding
			bool setDefaultCellTextAlign(const TextAlign value); // Set cell default text horizontal alignment
			bool setDefaultCellVerticalAlign(const VerticalAlign value); // Set cell default vertical alignment
			bool setDefaultFixedCellPadding(const RectF &value); // Set fixed cell default padding
			bool setDefaultFixedCellTextAlign(const TextAlign value); // Set fixed cell default text horizontal alignment
			bool setDefaultFixedCellVerticalAlign(const VerticalAlign value); // Set fixed cell default text vertical alignment
			bool setCellBackgroundColor(const CellState state, const Color &value); // Set cell background color
			bool setCellColor(const CellState state, const Color &value); // Set cell text color
			bool setActiveCellOutlineColor(const ActiveCellState state, const Color &value); // Set active cell outline border color
			bool setActiveCellOutlineMask(const ActiveCellState state, const unsigned int value); // Set active cell outline mask
		};
	}
}