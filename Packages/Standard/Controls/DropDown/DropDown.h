// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../IDropDown.h"
#include "CustomDropDown.h"

namespace nitisa
{
	class IBuiltInDropDown;
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class IListItemLabel;

		class CDropDown :public virtual IDropDown, public CCustomDropDown
		{
		private:
			static bool Compare(IListItem *a, IListItem *b);
			static String GetItemText(IListItem *item);
			static int Search(IBuiltInDropDown *dropdown, const String &search);
		public:
			CDropDown();
			CDropDown(IForm *parent);
			CDropDown(IControl *parent);

			IListItemLabel *getItem(const int index) override;
			String getText() override;
			int getActiveIndex() override;

			bool setText(const String &value) override;
			bool setActiveIndex(const int value) override;

			bool Add(IListItemLabel *item) override;
			bool Insert(IListItemLabel *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;
			bool Open() override;
			bool Close() override;

			bool Add(const String &caption); // Add item
			bool Insert(const String &caption, const int before); // Insert item before specified one
		};
	}
}