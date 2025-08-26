// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "IDrawGrid.h"

namespace nitisa
{
	namespace standard
	{
		class IStringGridService :public virtual ICustomGridService
		{
		protected:
			IStringGridService() = default;
			~IStringGridService() = default;
			IStringGridService(const IStringGridService &other) = delete;
			IStringGridService(IStringGridService &&other) = delete;
			IStringGridService &operator=(const IStringGridService &other) = delete;
			IStringGridService &operator=(IStringGridService &&other) = delete;
		public:
			virtual void NotifyOnCellChange( // Called when cell text is about to be changed manually
				const int column, const int row, // Cell coordinates
				const String &value, // New cell value
				bool &allowed) = 0; // Whether the change is allowed. Default true. Set it to false, to prevent change
			virtual void NotifyOnSetFocusCell( // Called when cell becomes focused(enters editing mode)
				const int column, const int row) = 0; // Cell coordinates
			virtual void NotifyOnKillFocusCell( // Called when cell becomes unfocused(exits editing mode)
				const int column, const int row) = 0; // Cell coordinates
		};

		// IStringGrid cells can be edited directly using built-in text editor
		class IStringGrid :public virtual IDrawGrid
		{
		protected:
			IStringGrid() = default;
			~IStringGrid() = default;
			IStringGrid(const IStringGrid &other) = delete;
			IStringGrid(IStringGrid &&other) = delete;
			IStringGrid &operator=(const IStringGrid &other) = delete;
			IStringGrid &operator=(IStringGrid &&other) = delete;
		public:
			void(*OnChangeCell)( // Called when cell text is about to be changed manually
				IStringGrid *sender, // Control where the event was triggered
				const int column, const int row, // Cell coordinates
				const String &value, // New cell value
				bool &allowed); // Whether the change is allowed. Default true. Set it to false, to prevent change
			void(*OnSetFocusCell)( // Called when cell becomes focused(enters editing mode)
				IStringGrid *sender, // Control where the event was triggered
				const int column, const int row); // Cell coordinates
			void(*OnKillFocusCell)( // Called when cell becomes unfocused(exits editing mode)
				IStringGrid *sender, // Control where the event was triggered
				const int column, const int row); // Cell coordinates

			virtual bool isCellEditable(const int column, const int row) = 0; // Return whether the cell is editable
			virtual bool isCellFocused(const int column, const int row) = 0; // Return whether the cell is focused(is being edited)
			virtual String getCell(const int column, const int row) = 0; // Return cell text

			virtual bool setCellEditable(const int column, const int row, const bool value) = 0; // Set whether the cell is editable
			virtual bool setCellFocused(const int column, const int row, const bool value) = 0; // Set whether the cell is focused(is being edited)
			virtual bool setCell(const int column, const int row, const String &value) = 0; // Set cell text
		};
	}
}