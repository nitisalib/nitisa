// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Interfaces/IControl.h"
#include "Nitisa/Interfaces/IControlService.h"
#include "Nitisa/Math/Mat4f.h"
#include "Nitisa/Math/Point.h"
#include "Nitisa/Math/PointF.h"

namespace nitisa
{
	class IListItem;

	struct Block;

	namespace standard
	{
		class ICustomGridService :public virtual IControlService
		{
		protected:
			ICustomGridService() = default;
			~ICustomGridService() = default;
			ICustomGridService(const ICustomGridService &other) = delete;
			ICustomGridService(ICustomGridService &&other) = delete;
			ICustomGridService &operator=(const ICustomGridService &other) = delete;
			ICustomGridService &operator=(ICustomGridService &&other) = delete;
		public:
			// Cell status change notifications. "item" can be nullptr if no item is assigned to cell. No notifications are sent when cells are being deleted
			virtual void NotifyOnHoverCell( // Called when mouse appears over the cell
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnLeaveCell( // Called when mouse pointer leaves the cell
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnSelectCell( // Called when cell becomes selected
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnDeselectCell( // Called when selected cell becomes unselected
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnActivateCell( // Called when cell becomes active
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnDeactivateCell( // Called when active cell becomes inactive
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnEnableCell( // Called when cell becomes enabled
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnDisableCell( // Called when cell becomes disabled
				const int column, const int row, // Cell coordinates
				IListItem *item) = 0; // Associated item. Can be nullptr
			virtual void NotifyOnMouseDownCell( // Called when mouse button was down over the cell
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr
				const PointF &position, // Down position in control coordinates
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift) = 0; // Control key states
			virtual void NotifyOnMouseUpCell( // Called when mouse button was release over the cell
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr. Can be different from "down" notification cell
				const PointF &position, // Release position in control coordinates
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift) = 0; // Control key states
			virtual bool NotifyOnMouseMoveCell( // Called when mouse pointer is moving over the cell. Return true if repaint is required or false if not
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr
				const PointF &position, // New mouse pointer position
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift) = 0; // Control key states
			virtual void NotifyOnMouseDownCancel() = 0; // Called when mouse down state should be reset to normal one. Could be triggered alone or after "NotifyOnMouseUpCell" notification
		};

		// Only one cell can be hovered at the same time
		// Only one cell can be active at the same time. Cells in disabled or fixed columns and rows cannot be activated as well as disabled cells itself
		class ICustomGrid :public virtual IControl
		{
		protected:
			ICustomGrid() = default;
			~ICustomGrid() = default;
			ICustomGrid(const ICustomGrid &other) = delete;
			ICustomGrid(ICustomGrid &&other) = delete;
			ICustomGrid &operator=(const ICustomGrid &other) = delete;
			ICustomGrid &operator=(ICustomGrid &&other) = delete;
		public:
			// Events
			void(*OnRenderCell)( // Called when cell should be rendered
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr
				const Mat4f &matrix, // Transform matrix to be applied when rendering cell
				const Block *block); // Clipping block to be applied when rendering cell
			void(*OnHoverCell)( // Called when mouse pointer appears over the cell
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnLeaveCell)( // Called when mouse pointer leaves the cell
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnSelectCell)( // Called when cell becomes selected
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnDeselectCell)( // Called when cell becomes unselected
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnActivateCell)( // Called when cell becomes active
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnDeactivateCell)( // Called when cell becomes inactive
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnEnableCell)( // Called when cell becomes enabled
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnDisableCell)( // Called when cell becomes disabled
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item); // Associated item. Can be nullptr
			void(*OnMouseDownCell)( // Called when mouse button was down over the cell
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr
				const PointF &position, // Down position in control coordinates
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift); // Control key states
			void(*OnMouseUpCell)( // Called when mouse button was release over the cell
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row,  // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr. Can be different from "down" event cell
				const PointF &position, // Release position in control coordinates
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift); // Control key states
			void(*OnMouseMoveCell)( // Called when mouse pointer is moving over the cell. Return true if repaint is required or false if not
				ICustomGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				IListItem *item, // Associated item. Can be nullptr
				const PointF &position, // New mouse pointer position
				const bool left, const bool middle, const bool right, // Mouse button states
				const bool ctrl, const bool alt, const bool shift, // Control key states
				bool &repaint_required); // Set to true to call repaint the control

			// Getters
			virtual bool isMultiselect() = 0; // Return whether multiple cells can be selected at the same time
			virtual int getColumns() = 0; // Return column count
			virtual int getRows() = 0; // Return row count
			virtual bool isCellEnabled(const int column, const int row) = 0; // Return whether the cell is enabled
			virtual bool isCellHovered(const int column, const int row) = 0; // Return whether the cell is hovered
			virtual bool isCellActive(const int column, const int row) = 0; // Return whether the cell is active
			virtual bool isCellSelected(const int column, const int row) = 0; // Return whether the cell is selected
			virtual bool isCellOverflowHidden(const int column, const int row) = 0; // Return whether the cell should not be drawn outside cell rectangle
			virtual float getColumnWidth(const int index) = 0; // Return column width
			virtual bool isColumnResizable(const int index) = 0; // Return whether the column is resizable
			virtual bool isColumnAutosize(const int index) = 0; // Return whether the column width should be calculated automatically using cells associated item(if exists)
			virtual bool isColumnEnabled(const int index) = 0; // Return whether the column is enabled
			virtual bool isColumnFixed(const int index) = 0; // Return whether the column is fixed. If column is fixed, it can be scrolled only in Y-direction
			virtual bool isColumnOverflowHidden(const int index) = 0; // Return whether the column cells should not be drawn outside cell rectangles. Can be overwritten by corresponding cell setting
			virtual float getRowHeight(const int index) = 0; // Return row height
			virtual bool isRowResizable(const int index) = 0; // Return whether the row is resizable
			virtual bool isRowAutosize(const int index) = 0; // Return whether the row height should be calculated automatically using cells associated item(if exists)
			virtual bool isRowEnabled(const int index) = 0; // Return whether the row is enabled
			virtual bool isRowFixed(const int index) = 0; // Return whether the row is fixed. If row is fixed, it can be scrolled only in X-direction
			virtual bool isRowOverflowHidden(const int index) = 0; // Return whether the row cells should not be drawn outside cell rectangles. Can be overwritten by corresponding cell setting
			virtual Point getCellAtPosition( // Return coordinates(column and row) of found cell. If not found, return { -1, -1 }. Borders(right and bottom) are included into a cell
				const PointF &position, // Coordinates in control space(in pixels)
				const bool bound) = 0; // If bound is true and there are cells, the closest one will always be returned(for example with x = 0 if position.X is less than zero)

			// Setters
			virtual bool setMultiselect(const bool value) = 0; // Set whether multiple cells can be selected at the same time
			virtual bool setColumns(const int value) = 0; // Set column count
			virtual bool setRows(const int value) = 0; // Set row count
			virtual bool setCellEnabled(const int column, const int row, const bool value) = 0; // Set whether the cell is enabled
			virtual bool setCellActive(const int column, const int row, const bool value) = 0; // Set whether the cell is active
			virtual bool setCellSelected(const int column, const int row, const bool value) = 0; // Set whether the cell is selected
			virtual bool setCellOverflowHidden(const int column, const int row, const bool value) = 0; // Set whether the cell should not be drawn outside cell rectangle
			virtual bool setColumnWidth(const int index, const float value) = 0; // Set column width
			virtual bool setColumnResizable(const int index, const bool value) = 0; // Set whether the column is resizable
			virtual bool setColumnAutosize(const int index, const bool value) = 0; // Set whether the column width should be calculated automatically using cells associated item(if exists)
			virtual bool setColumnEnabled(const int index, const bool value) = 0; // Set whether the column is enabled
			virtual bool setColumnFixed(const int index, const bool value) = 0; // Set whether the column is fixed. If column is fixed, it can be scrolled only in Y-direction
			virtual bool setColumnOverflowHidden(const int index, const bool value) = 0; // Set whether the column cells should not be drawn outside cell rectangles. Can be overwritten by corresponding cell setting
			virtual bool setRowHeight(const int index, const float value) = 0; // Set row height
			virtual bool setRowResizable(const int index, const bool value) = 0; // Set whether the row is resizable
			virtual bool setRowAutosize(const int index, const bool value) = 0; // Set whether the row height should be calculated automatically using cells associated item(if exists)
			virtual bool setRowEnabled(const int index, const bool value) = 0; // Set whether the row is enabled
			virtual bool setRowFixed(const int index, const bool value) = 0; // Set whether the row is fixed. If row is fixed, it can be scrolled only in X-direction
			virtual bool setRowOverflowHidden(const int index, const bool value) = 0; // Set whether the row cells should not be drawn outside cell rectangles. Can be overwritten by corresponding cell setting

			// Helpers
			virtual bool SelectAllCells() = 0; // Select all cells
			virtual bool DeselectAllCells() = 0; // Unselect all selected cells
			virtual bool DeleteColumn(const int index) = 0; // Delete specified column
			virtual bool DeleteRow(const int index) = 0; // Delete specified row
			virtual void LockUpdate() = 0; // Between this and next function any updates won't happen
			virtual void UnlockUpdate() = 0; // Should be called the same time as LockUpdate()
		};

		// The difference between the ICustomGrid is that fixed columns and rows cannot be separated by not-fixed ones. For example, the ICustomGrid allows the columns 0 and 2 be fixed while others aren't.
		// In the IDrawGrid no gaps exist between fixed columns and rows. So you have to specified how much columns/rows should be fixed starting from 0.
		class IDrawGrid :public virtual ICustomGrid
		{
		protected:
			IDrawGrid() = default;
			~IDrawGrid() = default;
			IDrawGrid(const IDrawGrid &other) = delete;
			IDrawGrid(IDrawGrid &&other) = delete;
			IDrawGrid &operator=(const IDrawGrid &other) = delete;
			IDrawGrid &operator=(IDrawGrid &&other) = delete;
		public:
			virtual int getFixedColumns() = 0; // Return fixed column count
			virtual int getFixedRows() = 0; // Return fixed row count

			virtual bool setFixedColumns(const int value) = 0; // Set fixed column count
			virtual bool setFixedRows(const int value) = 0; // Set fixed row count
		};
	}
}