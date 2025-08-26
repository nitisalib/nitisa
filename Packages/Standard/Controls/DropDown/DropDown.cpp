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
		CDropDown::CDropDown() :
			CCustomDropDown(L"DropDown", true, true, true, true)
		{
			setCompareFunc(Compare);
			setGetItemTextFunc(GetItemText);
			setSearchFunc(Search);
		}

		CDropDown::CDropDown(IForm *parent) :CDropDown()
		{
			setForm(parent);
		}

		CDropDown::CDropDown(IControl *parent) : CDropDown()
		{
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		bool CDropDown::Compare(IListItem *a, IListItem *b)
		{
			return cast<IListItemLabel*>(a)->getCaption() < cast<IListItemLabel*>(b)->getCaption();
		}

		String CDropDown::GetItemText(IListItem *item)
		{
			return cast<IListItemLabel*>(item)->getCaption();
		}

		int CDropDown::Search(IBuiltInDropDown *dropdown, const String &search)
		{
			for (int i = 0; i < dropdown->getItemCount(); i++)
				if (dropdown->getItem(i)->isEnabled() && ToLower(cast<IListItemLabel*>(dropdown->getItem(i))->getCaption()).find(search, 0) == 0)
					return i;
			return -1;
		}
	#pragma endregion

	#pragma region Items
		IListItemLabel *CDropDown::getItem(const int index)
		{
			return cast<IListItemLabel*>(CCustomDropDown::getItem(index));
		}

		String CDropDown::getText()
		{
			return CCustomDropDown::getText();
		}

		int CDropDown::getActiveIndex()
		{
			return CCustomDropDown::getActiveIndex();
		}

		bool CDropDown::setText(const String &value)
		{
			return CCustomDropDown::setText(value);
		}

		bool CDropDown::setActiveIndex(const int value)
		{
			return CCustomDropDown::setActiveIndex(value);
		}

		bool CDropDown::Add(IListItemLabel *item)
		{
			return AddItem(item);
		}

		bool CDropDown::Add(const String &caption)
		{
			return AddItem(new CListItemLabel(caption));
		}

		bool CDropDown::Insert(IListItemLabel *item, const int before)
		{
			return InsertItem(item, before);
		}

		bool CDropDown::Insert(const String &caption, const int before)
		{
			return InsertItem(new CListItemLabel(caption), before);
		}

		bool CDropDown::Delete(const int index)
		{
			return DeleteItem(index);
		}

		bool CDropDown::Clear()
		{
			return DeleteItems();
		}

		bool CDropDown::Open()
		{
			return CCustomDropDown::Open();
		}

		bool CDropDown::Close()
		{
			return CCustomDropDown::Close();
		}
	#pragma endregion
	}
}