// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Image/Color.h"
#include "Nitisa/Image/Colors.h"
#include "../DropDown/CustomDropDown.h"
#include "../IColorBox.h"

namespace nitisa
{
	class IBuiltInDropDown;
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class IListItemColor;

		class CColorBox :public virtual IColorBox, public CCustomDropDown
		{
		private:
			bool m_bHasStandardColors;
			bool m_bHasExtendedColors;
			bool m_bHasNoneColor;
			bool m_bIsCustomItems;

			void BuildList();
			static bool Compare(IListItem *a, IListItem *b);
			static String GetItemText(IListItem *item);
			static int Search(IBuiltInDropDown *dropdown, const String &search);
		public:
			bool isAcceptItem(IListItem *item) override;
			IListItemColor *getItem(const int index) override;
			int getActiveIndex() override;

			bool setActiveIndex(const int value) override;

			bool AddItem(IListItem *item) override;
			bool InsertItem(IListItem *item, const int before) override;
			bool DeleteItem(const int index) override;
			bool DeleteItem(IListItem *item) override;
			bool DeleteItems() override;

			bool Add(IListItemColor *item) override;
			bool Insert(IListItemColor *item, const int before) override;
			bool Delete(const int index) override;
			bool Clear() override;
			bool Open() override;
			bool Close() override;

			CColorBox();
			CColorBox(IForm *parent);
			CColorBox(IControl *parent);

			bool hasStandardColors() const; // Return whether standard colors are included in list
			bool hasExtendedColors() const; // Return whether extended colors are included in list
			bool hasNoneColor() const; // Return whether transparent color is included in list
			bool isCustomItems() const; // Return whether list has been modified manually(via Add, Insert, Delete, Clear methods)

			bool setStandardColors(const bool value); // Set whether standard colors are included in list
			bool setExtendedColors(const bool value); // Set whether extended colors are included in list
			bool setNoneColor(const bool value); // Set whether transparent color is included in list

			bool Add(const Color &color, const String &caption); // Add color
			bool Add(const CColor &color); // Add color
			bool Insert(const Color &color, const String &caption, const int before); // Insert color before specified one
			bool Insert(const CColor &color, const int before); // Insert color before specified one
			bool Delete(const String &caption); // Delete by color name
			bool Delete(const CColor &color); // Delete by color value
		};
	}
}