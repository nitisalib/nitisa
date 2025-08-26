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
#include "../../../Controls/ViewV3V1/ViewV3V1.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewV3V1PropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewV3V1::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewV3V1::View StringToView(const String &value);
			static String ViewToString(const CViewV3V1::View value);
		public:
			CViewV3V1PropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}