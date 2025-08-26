// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "IStringGrid.h"

namespace nitisa
{
	namespace standard
	{
		class IValueListEditor :public virtual IStringGrid
		{
		protected:
			IValueListEditor() = default;
			~IValueListEditor() = default;
			IValueListEditor(const IValueListEditor &other) = delete;
			IValueListEditor(IValueListEditor &&other) = delete;
			IValueListEditor &operator=(const IValueListEditor &other) = delete;
			IValueListEditor &operator=(IValueListEditor &&other) = delete;
		public:
			virtual String getKeyColumnTitle() = 0; // Return keys column title
			virtual String getValueColumnTitle() = 0; // Return values column title
			virtual bool isKeyColumnFixed() = 0; // Return whether keys column is fixed
			virtual bool isKeysEditable() = 0; // Return whether keys could be edited
			virtual bool isKeysUnique() = 0; // Return whether only unique keys are acceptable
			virtual bool isKeysDeletable() = 0; // Return whether rows with empty keys will be deleted automatically
			virtual bool isKeysAddable() = 0; // Return whether new empty row will be added to the table end when pressing down arrow key

			virtual bool setKeyColumnTitle(const String &value) = 0; // Set keys column title
			virtual bool setValueColumnTitle(const String &value) = 0; // Set values column title
			virtual bool setKeyColumnFixed(const bool value) = 0; // Set whether keys column is fixed
			virtual bool setKeysEditable(const bool value) = 0; // Set whether keys could be edited
			virtual bool setKeysUnique(const bool value) = 0; // Set whether only unique keys are acceptable
			virtual bool setKeysDeletable(const bool value) = 0; // Set whether rows with empty keys will be deleted automatically
			virtual bool setKeysAddable(const bool value) = 0; // Set whether new empty row will be added to the table end when pressing down arrow key

			virtual bool Add(const String &key, const String &value) = 0; // Add new row with specified key and value
			virtual bool Delete(const String &key) = 0; // Delete all rows with specified key
			virtual bool Rename(const String &old_key, const String &new_key) = 0; // Rename all rows having key equal to "old_key" into a "new_key"
			virtual bool Clear() = 0; // Set row count to 2 and remove values from second row
		};
	}
}