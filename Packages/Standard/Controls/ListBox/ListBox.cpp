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
		CListBox::CListBox() :CCustomListBox(L"ListBox", true, true, true)
		{

		}

		CListBox::CListBox(IForm *parent) : CListBox()
		{
			setForm(parent);
		}

		CListBox::CListBox(IControl *parent) : CListBox()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		CCustomListBox::FCompare CListBox::getCompareItems()
		{
			return [](IListItem *a, IListItem *b) {return cast<IListItemLabel*>(a)->getCaption() < cast<IListItemLabel*>(b)->getCaption(); };
		}

		int CListBox::Search(const String &search)
		{
			for (int i = 0; i < getItemCount(); i++)
				if (getItem(i)->isEnabled() && ToLower(getItem(i)->getCaption()).find(search, 0) == 0)
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Items
		bool CListBox::isAcceptItem(IListItem *item)
		{
			return cast<IListItemLabel*>(item) != nullptr;
		}

		IListItemLabel *CListBox::getItem(const int index)
		{
			return cast<IListItemLabel*>(CCustomListBox::getItem(index));
		}

		int CListBox::getActiveIndex()
		{
			return CCustomListBox::getActiveIndex();
		}

		bool CListBox::setActiveIndex(const int value)
		{
			return CCustomListBox::setActiveIndex(value);
		}

		bool CListBox::Add(IListItemLabel *item)
		{
			return AddItem(item);
		}

		bool CListBox::Add(const String &caption)
		{
			return AddItem(new CListBoxListItem(caption));
		}

		bool CListBox::Insert(IListItemLabel *item, const int before)
		{
			return InsertItem(item, before);
		}

		bool CListBox::Insert(const String &caption, const int before)
		{
			return InsertItem(new CListBoxListItem(caption), before);
		}

		bool CListBox::Delete(const int index)
		{
			return DeleteItem(index);
		}

		bool CListBox::Clear()
		{
			return DeleteItems();
		}
	#pragma endregion
	}
}