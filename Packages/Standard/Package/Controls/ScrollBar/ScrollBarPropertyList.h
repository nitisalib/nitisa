// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Scroll/BuiltInScroll.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CScrollBarPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBuiltInScroll::State StringToState(const String &state);
			static StringArray ElementStateItems();
			static CBuiltInScroll::ElementState StringToElementState(const String &state);
		public:
			CScrollBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}