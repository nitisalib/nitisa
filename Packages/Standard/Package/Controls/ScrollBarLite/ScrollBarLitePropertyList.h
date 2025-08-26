// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CScrollBarLitePropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBuiltInScrollLite::State StringToState(const String &state);
		public:
			CScrollBarLitePropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}