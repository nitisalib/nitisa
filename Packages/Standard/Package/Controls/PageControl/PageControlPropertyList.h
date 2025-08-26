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
#include "../../../Controls/PageControl/PageControl.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CPageControlPropertyList :public CControlPropertyList
		{
		private:
			static StringArray HeaderPositionItems();
			static String HeaderPositionToString(const CPageControl::HeaderPosition value);
			static CPageControl::HeaderPosition StringToHeaderPosition(const String &value);
			static StringArray TabStateItems();
			static CPageControl::TabState StringToTabState(const String &state);
			static StringArray ScrollStateItems();
			static CPageControl::ScrollState StringToScrollState(const String &state);
		public:
			CPageControlPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}