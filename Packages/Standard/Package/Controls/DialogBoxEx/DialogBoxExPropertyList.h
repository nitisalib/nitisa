// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/DialogBoxPropertyList.h"
#include "../../../Controls/DialogBoxEx/DialogBoxEx.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CDialogBoxExPropertyList :public CDialogBoxPropertyList
		{
		private:
			static StringArray StateItems();
			static CDialogBoxEx::State StringToState(const String &state);

			static StringArray ButtonStateItems();
			static CDialogBoxEx::ButtonState StringToButtonState(const String &state);
		public:
			CDialogBoxExPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity);
		};
	}
}