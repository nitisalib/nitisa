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
#include "../../../Controls/ViewV2/ViewV2.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewV2PropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewV2::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewV2::View StringToView(const String &value);
			static String ViewToString(const CViewV2::View value);
		public:
			CViewV2PropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}