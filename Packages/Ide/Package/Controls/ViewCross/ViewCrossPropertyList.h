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
#include "../../../Controls/ViewCross/ViewCross.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace ide
	{
		class CViewCrossPropertyList :public CControlPropertyList
		{
		private:
			static StringArray States();
			static CViewCross::State StringToState(const String &state);

			static StringArray ViewItems();
			static CViewCross::View StringToView(const String &value);
			static String ViewToString(const CViewCross::View value);
		public:
			CViewCrossPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}