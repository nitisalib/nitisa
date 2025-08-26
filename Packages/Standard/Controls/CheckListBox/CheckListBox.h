// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../ListBox/CustomListBox.h"
#include "../ICheckListBox.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class IListItemCheckBox;

		class CCheckListBox :public virtual ICheckListBox, public CCustomListBox
		{
		protected:
			FCompare getCompareItems() override;
			int Search(const String &search) override;
		public:
			CCheckListBox();
			CCheckListBox(IForm *parent);
			CCheckListBox(IControl *parent);

			bool isAcceptItem(IListItem *item) override;
			IListItemCheckBox *getItem(const int index) override;
			int getActiveIndex() override;
			bool isChecked(const int index) override;

			bool setActiveIndex(const int value) override;
			bool setChecked(const int index, const bool value) override;

			bool Add(IListItemCheckBox *item) override;
			bool Insert(IListItemCheckBox *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;

			bool Add(const String &caption); // Add item
			bool Insert(const String &caption, const int before); // Insert item before specified one
			bool Delete(const String &caption); // Delete item by caption
		};
	}
}