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
#include "../../../Controls/ViewH1H2R/ViewH1H2R.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewH1H2RPropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewH1H2R::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewH1H2R::View StringToView(const String &value);
			static String ViewToString(const CViewH1H2R::View value);
		public:
			CViewH1H2RPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}