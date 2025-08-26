// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/DriveDropDown/DriveDropDown.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CDriveDropDownPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBuiltInDropDown::State StringToState(const String &state);
			static StringArray OpenDirectionItems();
			static String OpenDirectionToString(const CBuiltInDropDown::OpenDirection value);
			static CBuiltInDropDown::OpenDirection StringToOpenDirection(const String &value);
			static StringArray ArrowAreaItems();
			static String ArrowAreaToString(const CBuiltInDropDown::ArrowArea value);
			static CBuiltInDropDown::ArrowArea StringToArrowArea(const String &value);
		public:
			CDriveDropDownPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}