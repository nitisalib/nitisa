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
#include "../ListBox/CustomListBox.h"
#include "../IColorListBox.h"

namespace nitisa
{
	class IControl;
	class IForm;
	class IListItem;

	namespace standard
	{
		class IListItemColor;

		class CColorListBox :public virtual IColorListBox, public CCustomListBox
		{
		private:
			bool m_bHasStandardColors;
			bool m_bHasExtendedColors;
			bool m_bHasNoneColor;
			bool m_bIsCustomItems;

			void BuildList();
		protected:
			FCompare getCompareItems() override;
			int Search(const String &search) override;
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

			CColorListBox();
			CColorListBox(IForm *parent);
			CColorListBox(IControl *parent);

			bool hasStandardColors() const; // Whether standard colors included
			bool hasExtendedColors() const; // Whether extended colors included
			bool hasNoneColor() const; // Whether none color included
			bool isCustomItems() const; // Return whether list has been modified manually(via Add, Insert, Delete, Clear methods)

			bool setStandardColors(const bool value); // Set whether standard colors included
			bool setExtendedColors(const bool value); // Set whether extended colors included
			bool setNoneColor(const bool value); // Set whether none color included

			bool Add(const Color &color, const String &caption); // Add color
			bool Add(const CColor &color); // Add color
			bool Insert(const Color &color, const String &caption, const int before); // Insert color before specified one
			bool Insert(const CColor &color, const int before); // Insert color before specified one
			bool Delete(const String &caption); // Delete color by name
			bool Delete(const CColor &color); // Delete color by value
		};
	}
}