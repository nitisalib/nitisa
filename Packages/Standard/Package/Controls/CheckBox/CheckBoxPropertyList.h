// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/CheckBox/CheckBox.h"
#include "../../../Controls/ICheckBox.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CCheckBoxPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CCheckBox::State StringToState(const String &state);
			static String CheckedToString(const ICheckBox::CheckedState value);
			static ICheckBox::CheckedState StringToChecked(const String &value);
			static StringArray CheckedItems();
		public:
			CCheckBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}