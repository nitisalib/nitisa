// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "CustomListBox.h"
#include "../IListBox.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class IListItemLabel;

		class CListBox :public virtual IListBox, public CCustomListBox
		{
		protected:
			FCompare getCompareItems() override;
			int Search(const String &search) override;
		public:
			CListBox();
			CListBox(IForm *parent);
			CListBox(IControl *parent);

			bool isAcceptItem(IListItem *item) override;
			IListItemLabel *getItem(const int index) override;
			int getActiveIndex() override;

			bool setActiveIndex(const int value) override;

			bool Add(IListItemLabel *item) override;
			bool Insert(IListItemLabel *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;

			bool Add(const String &caption); // Add item
			bool Insert(const String &caption, const int before); // Insert item before specified one
		};
	}
}