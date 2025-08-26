// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/Panel/Panel.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CPanelPropertyList :public CControlPropertyList
		{
		private:
			static StringArray BevelItems();
			static String BevelToString(const CPanel::Bevel value);
			static CPanel::Bevel StringToBevel(const String &value);
		public:
			CPanelPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}