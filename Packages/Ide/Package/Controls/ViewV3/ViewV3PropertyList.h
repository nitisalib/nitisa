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
#include "../../../Controls/ViewV3/ViewV3.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewV3PropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewV3::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewV3::View StringToView(const String &value);
			static String ViewToString(const CViewV3::View value);
		public:
			CViewV3PropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}