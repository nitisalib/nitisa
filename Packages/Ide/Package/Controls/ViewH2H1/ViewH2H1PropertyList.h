// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/ViewH2H1/ViewH2H1.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewH2H1PropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewH2H1::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewH2H1::View StringToView(const String &value);
			static String ViewToString(const CViewH2H1::View value);
		public:
			CViewH2H1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}