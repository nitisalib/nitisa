// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/BuiltInControls/IBuiltInScrollListener.h"
#include "Nitisa/Core/Aliases.h"
#include "Nitisa/Core/Control.h"
#include "Nitisa/Core/CursorType.h"
#include "Nitisa/Core/ListItemOwner.h"
#include "Nitisa/Core/ScrollVisibility.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/BorderColor.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Gradient.h"
#include "Nitisa/Interfaces/IFeedbackListener.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"
#include "Nitisa/Math/RectF.h"
#include "../IDrawGrid.h"
#include <vector>

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInScroll;
	class IControl;
	class IFont;
	class IListItem;
	class IRenderer;
	class IStyle;
	class ITexture;

	struct Block;

	namespace standard
	{
		class CCustomGridService;

		class CCustomGrid :public virtual ICustomGrid, public CControl
		{
			friend CCustomGridService;
		public:
			enum class State // Control states
			{
				Normal, // Normal
				Hovered, // Mouse pointer is over the control
				Focused, // Control is focused
				FocusedHovered, // Control is focused and mouse pointer is over the control
				Disabled // Control is disabled
			};
		private:
			struct COLUMN
			{
				float Width;
				bool Resizable;
				bool Autosize;
				bool Enabled;
				bool Fixed;
				bool OverflowHidden;
			};

			struct ROW
			{
				float Height;
				bool Resizable;
				bool Autosize;
				bool Enabled;
				bool Fixed;
				bool OverflowHidden;
			};

			struct CELL
			{
				IListItem *Item;
				bool Hovered;
				bool Active;
				bool Selected;
				bool Enabled;
				bool OverflowHidden;
			};

			enum class Element
			{
				None,
				VScroll,
				HScroll,
				Cell,
				RightBorder,
				BottomBorder
			};
		private:
			class CScroll :public CBuiltInScroll
			{
			private:
				CCustomGrid * m_pControl;
			public:
				IControl * getControl() override;

				CScroll(CCustomGrid *control);
			};

			class CScrollListener :public virtual IBuiltInScrollListener
			{
			private:
				CCustomGrid * m_pControl;
			public:
				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnScroll(IBuiltInControl *sender) override;

				CScrollListener(CCustomGrid *control);
			};

			class COwner :public CListItemOwner
			{
			private:
				CCustomGrid * m_pControl;
			public:
				IControl *getControl() override;
				IRenderer *getRenderer() override;
				IFont *getFont(IListItem *item) override;
				IStyle *getStyle(IListItem *item) override;

				void NotifyOnSizeChange(IListItem *item) override;
				void NotifyOnRepaintRequired(IListItem *item) override;
				void NotifyOnBeforeAddItem(IListItem *item, IListItem *parent) override;
				void NotifyOnAddItem(IListItem *item) override;
				void NotifyOnBeforeDeleteItem(IListItem *item) override;
				void NotifyOnDeleteItem(IListItem *item, IListItem *parent) override;
				void NotifyOnBeforeDeleteItems(IListItem *parent) override;
				void NotifyOnDeleteItems(IListItem *parent) override;
				void NotifyOnShow(IListItem *item) override;
				void NotifyOnHide(IListItem *item) override;
				void NotifyOnEnable(IListItem *item) override;
				void NotifyOnDisable(IListItem *item) override;
				void NotifyOnSelect(IListItem *item) override;
				void NotifyOnDeselect(IListItem *item) override;
				void NotifyOnActivate(IListItem *item) override;
				void NotifyOnDeactivate(IListItem *item) override;

				COwner(CCustomGrid *control);
			};

			class CGradientListener :public virtual IFeedbackListener
			{
			private:
				CCustomGrid *m_pControl;
			public:
				void NotifyOnChange() override;

				CGradientListener(CCustomGrid *control);
			};
		private:
			CGradientListener m_cGradientListener;
			std::vector<COLUMN> m_aColumns;
			std::vector<ROW> m_aRows;
			std::vector<std::vector<CELL>> m_aCells;
			bool m_bMultiselect;
			ScrollVisibility m_eVerticalScrollVisibility;
			ScrollVisibility m_eHorizontalScrollVisibility;
			float m_fScrollInterval;

			RectF m_sBorderWidth;
			RectF m_sPadding;
			float m_fGridWidth;
			Color m_aGridColor[(int)State::Disabled + 1];
			RectF m_aBorderRadius[(int)State::Disabled + 1];
			Color m_aBackgroundColor[(int)State::Disabled + 1];
			Gradient m_aBackgroundGradient[(int)State::Disabled + 1];
			BorderColor m_aBorderColor[(int)State::Disabled + 1];
			int m_aShadowRadius[(int)State::Disabled + 1];
			PointF m_aShadowShift[(int)State::Disabled + 1];
			Color m_aShadowColor[(int)State::Disabled + 1];
			Color m_aCornerColor[(int)State::Disabled + 1];
			float m_fDefaultColumnWidth;
			float m_fDefaultRowHeight;
			bool m_bDefaultColumnResizable;
			bool m_bDefaultRowResizable;
			bool m_bDefaultColumnAutosize;
			bool m_bDefaultRowAutosize;
			bool m_bDefaultColumnEnabled;
			bool m_bDefaultRowEnabled;
			bool m_bDefaultColumnFixed;
			bool m_bDefaultRowFixed;
			bool m_bDefaultColumnOverflowHidden;
			bool m_bDefaultRowOverflowHidden;

			IBuiltInScroll *m_pVScroll;
			IBuiltInScroll *m_pHScroll;
			Element m_eHoveredElement;
			Element m_eDownElement;
			Point m_sHoveredCell;
			Point m_sDownCell;
			PointF m_sScroll;
			PointF m_sMaxScroll;
			ITexture *m_pCanvas;
			CScrollListener m_cScrollListener;
			bool m_bIgnoreGradient;
			PointF m_sTableSize;
			bool m_bVScroll;
			bool m_bHScroll;
			bool m_bIgnoreItems;
			COwner m_cOwner;
			Point m_sActiveCell;
			Point m_sSelectTo; // For keyboard selection(ranges from this value to active cell)
			int m_iLockUpdate;
			bool m_bUpdateRequired;
			PlatformHandle m_hScrollTimer;

			IBuiltInScroll *getVScroll();
			IBuiltInScroll *getHScroll();
			void Update();
			Point FindItemCoords(IListItem *item);
			bool UpdateHoveredElement();
			bool UpdateHoveredElement(const PointF &pos);
			bool SelectCell(const int column, const int row, ICustomGridService *service);
			bool DeselectCell(const int column, const int row, ICustomGridService *service);
			bool EnableCell(const int column, const int row, ICustomGridService *service);
			bool DisableCell(const int column, const int row, ICustomGridService *service);
			bool ActivateCell(const int column, const int row, ICustomGridService *service);
			bool DeactivateCell(const int column, const int row, ICustomGridService *service);
			bool LeaveCell(const int column, const int row, ICustomGridService *service);
			bool HoverCell(const int column, const int row, ICustomGridService *service);
			void CancelMouseDown(const bool check_capture, ICustomGridService *service);
			void LeaveAll();
			void Render();
			void RenderGrid(IRenderer *renderer, const RectF &rect, const State state, const Block *block);
			void RenderCells(IRenderer *renderer, const RectF &rect, const Block *block);
			void RenderScrolls(IRenderer *renderer, const RectF &rect, const PointF &disp, const State state, const Block *block);
		protected:
			void ForceRepaint(); // Cleanup buffer(canvas) and repaint the control
			bool ScrollToCell(const Point &coords); // Scroll to specified cell
			bool ScrollToActiveCell(); // Scroll to active cell

			virtual void UpdateFromStyle(IStyle *style); // Update stylable properties. If you overwrite this method, call CCustomGrid::UpdateFromStyle(style) in it to apply style to the CCustomGrid properties
			virtual void CreateColumn( // Called when new column is being created
				float &width, // Column width. By default equal to DefaultColumnWidth property value
				bool &resizable, // Whether column should be resizable or not. By default equal to DefaultColumnResizable property value
				bool &autosize, // Whether column width should depend on cell content(associated IListItem). By default equal to DefaultColumnAutosize property value
				bool &enabled, // Whether column enabled or disabled. By default equal to DefaultColumnEnabled property value
				bool &fixed, // Whether column is fixed and could not be scrolled in X direction. By default equal to DefaultColumnFixed property value
				bool &overflow_hidden); // Whether new cells in column should be drawn with cutting areas which are out of cell(could be overwritten by cell settings). By default equal to DefaultColumnOverflowHidden property value
			virtual void CreateRow( // Called when new row is being created
				float &height, // Column height. By default equal to DefaultRowHeight property value
				bool &resizable, // Whether row should be resizable or not. By default equal to DefaultRowResizable property value
				bool &autosize, // Whether row height should depend on cell content(assocciated IListItem). By default equal to DefaultRowAutosize property value
				bool &enabled, // Whether row enabled or disabled. By default equal to DefaultRowEnabled property value
				bool &fixed, // Whether row is fixed and could not be scrolled in Y direction. By default equal to DefaultRowFixed property value
				bool &overflow_hidden); // Whether new cells in row should be drawn with cutting areas which are out of cell(could be overwritten by cell settings). By default equal to DefaultRowOverflowHidden property value
			virtual void RenderCell( // Called when cell content should be drawn. By default calls item render method if item is not empty
				const int column, // Cell column index
				const int row, // Cell row index
				IListItem *item, // Item associated with cell. Can be nullptr
				const Mat4f &matrix, // Transformation matrix to be applied when drawing
				const Block *block); // Block constraints to be applied when rendering
			virtual PointF GetItemRequiredSize( // Should return cell required size. By default get it from item if it is not empty
				const int column, // Cell column index
				const int row, // Cell row index
				IListItem *item); // Associated item. Can be nullptr

			virtual IListItem * CreateItem(const int column, const int row) = 0; // Called to create item for newly created cell with specified coordinates. Can return nullptr if no item should be assigned to the cell
		protected:
			void BeforeRelease() override;
		public:
			// IControl getters
			RectF getClientRect() override;
			RectF getRenderRect() override;
			CursorType getCursor() override;

			// IControl setters
			bool setDPI(const Point &value) override;

			// IControl methods
			void Refresh(const bool refresh_children) override;

			// ICustomGrid getters
			bool isMultiselect() override;
			int getColumns() override;
			int getRows() override;
			bool isCellEnabled(const int column, const int row) override;
			bool isCellHovered(const int column, const int row) override;
			bool isCellActive(const int column, const int row) override;
			bool isCellSelected(const int column, const int row) override;
			bool isCellOverflowHidden(const int column, const int row) override;
			float getColumnWidth(const int index) override;
			bool isColumnResizable(const int index) override;
			bool isColumnAutosize(const int index) override;
			bool isColumnEnabled(const int index) override;
			bool isColumnFixed(const int index) override;
			bool isColumnOverflowHidden(const int index) override;
			float getRowHeight(const int index) override;
			bool isRowResizable(const int index) override;
			bool isRowAutosize(const int index) override;
			bool isRowEnabled(const int index) override;
			bool isRowFixed(const int index) override;
			bool isRowOverflowHidden(const int index) override;
			Point getCellAtPosition(const PointF &position, const bool bound) override;

			// ICustomGrid setters
			bool setMultiselect(const bool value) override;
			bool setColumns(const int value) override;
			bool setRows(const int value) override;
			bool setCellEnabled(const int column, const int row, const bool value) override;
			bool setCellActive(const int column, const int row, const bool value) override;
			bool setCellSelected(const int column, const int row, const bool value) override;
			bool setCellOverflowHidden(const int column, const int row, const bool value) override;
			bool setColumnWidth(const int index, const float value) override;
			bool setColumnResizable(const int index, const bool value) override;
			bool setColumnAutosize(const int index, const bool value) override;
			bool setColumnEnabled(const int index, const bool value) override;
			bool setColumnFixed(const int index, const bool value) override;
			bool setColumnOverflowHidden(const int index, const bool value) override;
			bool setRowHeight(const int index, const float value) override;
			bool setRowResizable(const int index, const bool value) override;
			bool setRowAutosize(const int index, const bool value) override;
			bool setRowEnabled(const int index, const bool value) override;
			bool setRowFixed(const int index, const bool value) override;
			bool setRowOverflowHidden(const int index, const bool value) override;

			// ICustomGrid methods
			bool SelectAllCells() override;
			bool DeselectAllCells() override;
			bool DeleteColumn(const int index) override;
			bool DeleteRow(const int index) override;
			void LockUpdate() override;
			void UnlockUpdate() override;

			CCustomGrid(const String &class_name);
			~CCustomGrid() override;

			// Getters
			State getState(); // Return control state
			ScrollVisibility getVerticalScrollVisibility() const; // Return vertical scroll visibility. Default svAuto
			ScrollVisibility getHorizontalScrollVisibility() const; // Return horizontal scroll visibility. Default svAuto
			RectF getBorderWidth() const; // Return border widths. Default { 1, 1, 1, 1 }
			RectF getPadding() const; // Return padding. Default { 0, 0, 0, 0 }
			float getGridWidth() const; // Return grid line width. Default 1
			Color getGridColor(const State state) const; // Return grid line color
			RectF getBorderRadius(const State state) const; // Return border radius
			Color getBackgroundColor(const State state) const; // Return background color
			Gradient *getBackgroundGradient(const State state); // Return background gradient
			BorderColor getBorderColor(const State state) const; // Return border colors
			int getShadowRadius(const State state) const; // Return shadow radius
			PointF getShadowShift(const State state) const; // Return shadow shift
			Color getShadowColor(const State state) const; // Return shadow color
			Color getCornerColor(const State state) const; // Return rectangle color between scrollbars
			float getScrollInterval() const; // Return scroll interval(in seconds)
			float getDefaultColumnWidth() const; // Return default column width. Default 64
			float getDefaultRowHeight() const; // Return default row height. Default 24
			bool isDefaultColumnResizable() const; // Return whether a column is resizable by default. Default false
			bool isDefaultRowResizable() const; // Return whether a row is resizable by default. Default false
			bool isDefaultColumnAutosize() const; // Return whether a column width is calculated automatically by default. Default false
			bool isDefaultRowAutosize() const; // Return whether a row height is calculated automatically by default. Default false
			bool isDefaultColumnEnabled() const; // Return whether a column is enabled by default. Default true
			bool isDefaultRowEnabled() const; // Return whether a row is enabled by default. Default true
			bool isDefaultColumnFixed() const; // Return whether a column is fixed by default. Default false
			bool isDefaultRowFixed() const; // Return whether a row is fixed by default. Default false
			bool isDefaultColumnOverflowHidden() const; // Return whether a column content should be clipped by default. Default true
			bool isDefaultRowOverflowHidden() const; // Return whether a row content should be clipped by default. Default true
			Point getActiveCell() const; // Return active cell coordinates. Return { -1, -1 } if there is no active cell
			PointF getCellPosition(const int column, const int row); // Return cell position in control coordinate space

			// Setters
			bool setVerticalScroll(IBuiltInScroll *value); // Set new vertical scrollbar
			bool setHorizontalScroll(IBuiltInScroll *value); // Set new horizontal scrollbar
			bool setVerticalScrollVisibility(const ScrollVisibility value); // Set vertical scroll visibility
			bool setHorizontalScrollVisibility(const ScrollVisibility value); // Set horizontal scroll visibility
			bool setBorderWidth(const RectF &value); // Set border widths
			bool setPadding(const RectF &value); // Set padding
			bool setGridWidth(const float value); // Set grid line width
			bool setGridColor(const State state, const Color &value); // Set grid line color
			bool setBorderRadius(const State state, const RectF value); // Set border radius
			bool setBackgroundColor(const State state, const Color &value); // Set background color
			bool setBorderColor(const State state, const BorderColor &value); // Set border colors
			bool setShadowRadius(const State state, const int value); // Set shadow radius
			bool setShadowShift(const State state, const PointF &value); // Set shadow shift
			bool setShadowColor(const State state, const Color &value); // Set shadow color
			bool setCornerColor(const State state, const Color &value); // Set rectangle color between scrollbars
			bool setScrollInterval(const float value); // Set scroll interval(in seconds)
			bool setDefaultColumnWidth(const float value); // Set default column width
			bool setDefaultRowHeight(const float value); // Set default row height
			bool setDefaultColumnResizable(const bool value); // Set whether a column is resizable by default
			bool setDefaultRowResizable(const bool value); // Set whether a row is resizable by default
			bool setDefaultColumnAutosize(const bool value); // Set whether a column width is calculated automatically by default
			bool setDefaultRowAutosize(const bool value); // Set whether a row height is calculated automatically by default
			bool setDefaultColumnEnabled(const bool value); // Set whether a column is enabled by default
			bool setDefaultRowEnabled(const bool value); // Set whether a row is enabled by default
			bool setDefaultColumnFixed(const bool value); // Set whether a column is fixed by default
			bool setDefaultRowFixed(const bool value); // Set whether a row is fixed by default
			bool setDefaultColumnOverflowHidden(const bool value); // Set whether a column content should be clipped by default
			bool setDefaultRowOverflowHidden(const bool value); // Set whether a row content should be clipped by default
		};
	}
}