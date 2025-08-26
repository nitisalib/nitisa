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
#include "../../../Controls/IScrollList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CScrollListPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBuiltInScrollLite::State StringToState(const String &state);
			static StringArray OrientationItems();
			static String OrientationToString(const IScrollList::Orientation value);
			static IScrollList::Orientation StringToOrientation(const String &value);
		public:
			CScrollListPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}