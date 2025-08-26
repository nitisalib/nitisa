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
		CCheckListBox::CCheckListBox() :CCustomListBox(L"CheckListBox", true, true, true)
		{
			CCustomListBox::setMultiselect(false);
		}

		CCheckListBox::CCheckListBox(IForm *parent) : CCheckListBox()
		{
			setForm(parent);
		}

		CCheckListBox::CCheckListBox(IControl *parent) : CCheckListBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		CCustomListBox::FCompare CCheckListBox::getCompareItems()
		{
			return [](IListItem *a, IListItem *b) {return cast<IListItemCheckBox*>(a)->getCaption() < cast<IListItemCheckBox*>(b)->getCaption(); };
		}

		int CCheckListBox::Search(const String &search)
		{
			for (int i = 0; i < getItemCount(); i++)
				if (getItem(i)->isEnabled() && ToLower(getItem(i)->getCaption()).find(search, 0) == 0)
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Items
		bool CCheckListBox::isAcceptItem(IListItem *item)
		{
			return cast<IListItemCheckBox*>(item) != nullptr;
		}

		IListItemCheckBox *CCheckListBox::getItem(const int index)
		{
			return cast<IListItemCheckBox*>(CCustomListBox::getItem(index));
		}

		int CCheckListBox::getActiveIndex()
		{
			return CCustomListBox::getActiveIndex();
		}

		bool CCheckListBox::setActiveIndex(const int value)
		{
			return CCustomListBox::setActiveIndex(value);
		}

		bool CCheckListBox::Add(IListItemCheckBox *item)
		{
			return AddItem(item);
		}

		bool CCheckListBox::Add(const String &caption)
		{
			return AddItem(new CListItemCheckBox(caption));;
		}

		bool CCheckListBox::Insert(IListItemCheckBox *item, const int before)
		{
			return InsertItem(item, before);
		}

		bool CCheckListBox::Insert(const String &caption, const int before)
		{
			return InsertItem(new CListItemCheckBox(caption), before);
		}

		bool CCheckListBox::Delete(const int index)
		{
			return DeleteItem(index);
		}

		bool CCheckListBox::Delete(const String &caption)
		{
			CLockRepaint lock{ this };
			LockUpdate();
			bool result{ false };
			int i{ 0 };
			while (i < getItemCount())
				if (getItem(i)->getCaption() == caption)
					result = DeleteItem(i) || result;
				else
					i++;
			UnlockUpdate();
			return result;
		}

		bool CCheckListBox::Clear()
		{
			return DeleteItems();
		}
	#pragma endregion

	#pragma region Getters
		bool CCheckListBox::isChecked(const int index)
		{
			if (getItem(index))
				return getItem(index)->isChecked();
			return false;
		}
	#pragma endregion

	#pragma region Setters
		bool CCheckListBox::setChecked(const int index, const bool value)
		{
			if (getItem(index))
				return getItem(index)->setChecked(value);
			return false;
		}
	#pragma endregion
	}
}