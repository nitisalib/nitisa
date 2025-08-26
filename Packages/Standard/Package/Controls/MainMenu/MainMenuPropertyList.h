// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Align.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/MainMenu/MainMenu.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CMainMenuPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CMainMenu::State StringToState(const String &state);

			static StringArray AlignItems();
			static Align StringToAlign(const String &align);
			static String AlignToString(const Align align);
		public:
			CMainMenuPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}