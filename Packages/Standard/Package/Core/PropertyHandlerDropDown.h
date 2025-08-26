// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/BuiltInControls/IBuiltInDropDownListener.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Math/RectF.h"
#include "Nitisa/Package/Interfaces/IPropertyHandler.h"

namespace nitisa
{
	class IBuiltInControl;
	class IBuiltInControlListener;
	class IBuiltInDropDown;
	class IControl;
	class IListItem;
	class IPackage;

	namespace standard
	{
		class CPropertyHandlerDropDown :public virtual IPropertyHandler, public CBuiltInDropDown
		{
		private:
			class CListener :public virtual IBuiltInDropDownListener
			{
			private:
				CPropertyHandlerDropDown *m_pHandler;
			public:
				CListener(CPropertyHandlerDropDown *handler);

				void NotifyOnRepaint(IBuiltInControl *sender, const RectF &rect) override;
				void NotifyOnTextChange(IBuiltInControl *sender) override;
				void NotifyOnSelect(IBuiltInControl *sender, const int index) override;
				void NotifyOnOpen(IBuiltInControl *sender) override;
				void NotifyOnClose(IBuiltInControl *sender) override;
			};
			IControl *m_pControl;
			IPackage *m_pPackage;

			CListener m_cListener;
			IBuiltInControlListener *m_pListener;

			static bool Compare(IListItem *a, IListItem *b);
			static String GetItemText(IListItem *item);
			static int Search(IBuiltInDropDown *dropdown, const String &search);
		protected:
			virtual void NotifyOnSelect(const int index) = 0; // Called when user selects another item(index specified the index of selected item)
		public:
			IControl *getControl() override;
			IPackage *getPackage() override;
			IBuiltInControlListener *getListener() override;

			bool setControl(IControl *value) override;
			void setListener(IBuiltInControlListener *value) override;

			CPropertyHandlerDropDown(IPackage *package, const String &name);

			bool InsertItem(IListItem *item, const int before) override;

			bool Add(const String &caption); // Add new option in list
			bool Open() override;
		};
	}
}