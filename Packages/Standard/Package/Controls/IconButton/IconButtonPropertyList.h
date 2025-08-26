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
#include "../../../Controls/IconButton/IconButton.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CIconButtonPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CIconButton::State StringToState(const String &state);

			static StringArray IconSizeItems();
			static CIconButton::IconSize StringToIconSize(const String &state);
			static String IconSizeToString(const CIconButton::IconSize value);
		public:
			CIconButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}