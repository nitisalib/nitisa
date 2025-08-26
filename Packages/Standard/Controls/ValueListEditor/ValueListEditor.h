// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../StringGrid/CustomStringGrid.h"
#include "../IValueListEditor.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CValueListEditorService;

		class CValueListEditor :public virtual IValueListEditor, public CCustomStringGrid
		{
			friend CValueListEditorService;
		private:
			bool m_bKeysUnique;
			bool m_bKeysDeletable;
			bool m_bKeysAddable;
			bool m_bKeysEditable;

			bool isKeyUnique(const String &key, const int skip);
			void DeleteRowInternal(const int row);
		public:
			// ICustomGrid setters
			bool setColumns(const int value) override; // Not allowed. Column count is always two
			bool setRows(const int value) override; // Min value is 2
			bool setColumnFixed(const int index, const bool value) override; // Only column with index = 0 can be changed
			bool setRowFixed(const int index, const bool value) override; // Not allowed. First(index = 0) row is always fixed

			// ICustomGrid methods
			bool DeleteColumn(const int index) override; // Not allowed
			bool DeleteRow(const int index) override; // Only row with index >= 1 can be deleted and only untill there are more than 2 rows left

			// IDrawGrid setters
			bool setFixedColumns(const int value) override; // Only 0 indiex is allowed
			bool setFixedRows(const int value) override; // Not allowed

			// IValueListEditor getters
			String getKeyColumnTitle() override;
			String getValueColumnTitle() override;
			bool isKeyColumnFixed() override;
			bool isKeysEditable() override;
			bool isKeysUnique() override;
			bool isKeysDeletable() override;
			bool isKeysAddable() override;

			// IValueListEditor setters
			bool setKeyColumnTitle(const String &value) override;
			bool setValueColumnTitle(const String &value) override;
			bool setKeyColumnFixed(const bool value) override;
			bool setKeysEditable(const bool value) override;
			bool setKeysUnique(const bool value) override;
			bool setKeysDeletable(const bool value) override;
			bool setKeysAddable(const bool value) override;

			// IValueListEditor methods
			bool Add(const String &key, const String &value) override;
			bool Delete(const String &key) override;
			bool Rename(const String &old_key, const String &new_key) override;
			bool Clear() override;

			CValueListEditor(); // Create
			CValueListEditor(IForm *parent); // Create and put onto the form
			CValueListEditor(IControl *parent); // Create and put onto the parent control
		};
	}
}