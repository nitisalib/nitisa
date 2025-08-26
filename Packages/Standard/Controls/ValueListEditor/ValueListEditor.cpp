// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
	#pragma region Constructor & destructor
		CValueListEditor::CValueListEditor() :
			CCustomStringGrid(L"ValueListEditor"),
			m_bKeysUnique{ false },
			m_bKeysDeletable{ false },
			m_bKeysAddable{ false },
			m_bKeysEditable{ false }
		{
			setService(new CValueListEditorService(this), true);
			LockUpdate();
			setDefaultColumnWidth(150);
			setDefaultRowHeight(18);
			setDefaultColumnResizable(true);
			CCustomStringGrid::setFixedColumns(0);
			CCustomStringGrid::setColumns(2);
			CCustomStringGrid::setRows(2);
			setCell(0, 0, L"Key");
			setCell(1, 0, L"Value");
			setCellEditable(0, 1, m_bKeysEditable);
			setSize(PointF{ 304, 400 });
			UnlockUpdate();
		}

		CValueListEditor::CValueListEditor(IForm *parent) :CValueListEditor()
		{
			setForm(parent);
		}

		CValueListEditor::CValueListEditor(IControl *parent) : CValueListEditor()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region ICustomGrid setters
		bool CValueListEditor::setColumns(const int value)
		{
			return false;
		}

		bool CValueListEditor::setRows(const int value)
		{
			if (value >= 2)
				return CCustomStringGrid::setRows(value);
			return 0;
		}

		bool CValueListEditor::setColumnFixed(const int index, const bool value)
		{
			if (value == 0)
				return CCustomStringGrid::setColumnFixed(index, value);
			return false;
		}

		bool CValueListEditor::setRowFixed(const int index, const bool value)
		{
			return false;
		}
	#pragma endregion

	#pragma region ICustomGrid methods
		bool CValueListEditor::DeleteColumn(const int index)
		{
			return false;
		}

		bool CValueListEditor::DeleteRow(const int index)
		{
			if (index > 0 && getRows() > 2)
				return CCustomStringGrid::DeleteRow(index);
			return false;
		}
	#pragma endregion

	#pragma region IDrawGrid setters
		bool CValueListEditor::setFixedColumns(const int value)
		{
			if (value <= 1)
				return CCustomStringGrid::setFixedColumns(value);
			return false;
		}

		bool CValueListEditor::setFixedRows(const int value)
		{
			return false;
		}
	#pragma endregion

	#pragma region IValueListEditor getters
		String CValueListEditor::getKeyColumnTitle()
		{
			return getCell(0, 0);
		}

		String CValueListEditor::getValueColumnTitle()
		{
			return getCell(1, 0);
		}

		bool CValueListEditor::isKeyColumnFixed()
		{
			return isColumnFixed(0);
		}

		bool CValueListEditor::isKeysEditable()
		{
			return m_bKeysEditable;
		}

		bool CValueListEditor::isKeysUnique()
		{
			return m_bKeysUnique;
		}

		bool CValueListEditor::isKeysDeletable()
		{
			return m_bKeysDeletable;
		}

		bool CValueListEditor::isKeysAddable()
		{
			return m_bKeysAddable;
		}
	#pragma endregion

	#pragma region IValueListEditor setters
		bool CValueListEditor::setKeyColumnTitle(const String &value)
		{
			return setCell(0, 0, value);
		}

		bool CValueListEditor::setValueColumnTitle(const String &value)
		{
			return setCell(1, 0, value);
		}

		bool CValueListEditor::setKeyColumnFixed(const bool value)
		{
			return CCustomStringGrid::setFixedColumns(value ? 1 : 0);
		}

		bool CValueListEditor::setKeysEditable(const bool value)
		{
			if (value != m_bKeysEditable)
			{
				CLockRepaint lock{ this };
				m_bKeysEditable = value;
				for (int y = 0; y < getRows(); y++)
					setCellEditable(0, y, value);
				return true;
			}
			return false;
		}

		bool CValueListEditor::setKeysUnique(const bool value)
		{
			if (value != m_bKeysUnique)
			{
				m_bKeysUnique = value;
				if (m_bKeysUnique && getRows() > 2)
				{
					LockUpdate();
					int y{ getRows() - 1 };
					while (y-- >= 2)
						if (!isKeyUnique(getCell(0, y), y))
							CCustomStringGrid::DeleteRow(y);
					UnlockUpdate();
				}
				return true;
			}
			return false;
		}

		bool CValueListEditor::setKeysDeletable(const bool value)
		{
			if (value != m_bKeysDeletable)
			{
				m_bKeysDeletable = value;
				return true;
			}
			return false;
		}

		bool CValueListEditor::setKeysAddable(const bool value)
		{
			if (value != m_bKeysAddable)
			{
				m_bKeysAddable = value;
				return true;
			}
			return false;
		}
	#pragma endregion

	#pragma region IValueListEditor methods
		bool CValueListEditor::Add(const String &key, const String &value)
		{
			if (!key.empty() && (!m_bKeysUnique || isKeyUnique(key, -1)))
			{
				LockUpdate();
				if (!getCell(0, getRows() - 1).empty())
					setRows(getRows() + 1);
				setCell(0, getRows() - 1, key);
				setCell(1, getRows() - 1, value);
				UnlockUpdate();
				ForceRepaint();
				return true;
			}
			return false;
		}

		bool CValueListEditor::Delete(const String &key)
		{
			LockUpdate();
			bool changed{ false };
			int y{ 1 };
			while (y < getRows())
				if (getCell(0, y) == key)
				{
					if (getRows() > 2)
						changed = CCustomStringGrid::DeleteRow(y) || changed;
					else
					{
						changed = setCell(0, y, L"") || changed;
						changed = setCell(1, y, L"") || changed;
						y++;
					}
				}
				else
					y++;
			UnlockUpdate();
			if (changed)
				ForceRepaint();
			return changed;
		}

		bool CValueListEditor::Rename(const String &old_key, const String &new_key)
		{
			if (!old_key.empty() && !new_key.empty() && new_key != old_key && (!m_bKeysUnique || isKeyUnique(new_key, -1)))
			{
				CLockRepaint lock{ this };
				bool changed{ false };
				for (int y = 1; y < getRows(); y++)
					if (getCell(0, y) == old_key)
						changed = setCell(0, y, new_key) || changed;
				if (changed)
					ForceRepaint();
				return changed;
			}
			return false;
		}

		bool CValueListEditor::Clear()
		{
			CLockRepaint lock{ this };
			bool result{ CCustomStringGrid::setRows(2) };
			result = setCell(0, 1, L"") || result;
			result = setCell(1, 1, L"") || result;
			return result;
		}
	#pragma endregion

	#pragma region Helpers
		bool CValueListEditor::isKeyUnique(const String &key, const int skip)
		{
			for (int y = 1; y < getRows(); y++)
				if (y != skip && getCell(0, y) == key)
					return false;
			return true;
		}

		void CValueListEditor::DeleteRowInternal(const int row)
		{
			CCustomStringGrid::DeleteRow(row);
		}
	#pragma endregion
	}
}