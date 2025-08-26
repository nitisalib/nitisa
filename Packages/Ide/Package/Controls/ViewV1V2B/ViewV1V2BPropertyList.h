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
#include "../../../Controls/ViewV1V2B/ViewV1V2B.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewV1V2BPropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewV1V2B::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewV1V2B::View StringToView(const String &value);
			static String ViewToString(const CViewV1V2B::View value);
		public:
			CViewV1V2BPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}