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
#include "../../../Controls/ToolBar/ToolBar.h"
#include "../../../Controls/IToolBar.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CToolBarPropertyList :public CControlPropertyList
		{
		private:
			static StringArray ScrollerStateItems();
			static CToolBar::ScrollerState StringToScrollerState(const String &state);
			static StringArray AlignToItems();
			static String AlignToToString(const IToolBar::AlignTo value);
			static IToolBar::AlignTo StringToAlignTo(const String &value);
		public:
			CToolBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}