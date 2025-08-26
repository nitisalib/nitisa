// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/BuiltInControls/Select/BuiltInSelect.h"
#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ControlPropertyList.h"
#include "../../../Controls/Select/Select.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CSelectPropertyList :public CControlPropertyList
		{
		private:
			static StringArray StateItems();
			static CBuiltInSelect::State StringToState(const String &state);
			static StringArray OpenDirectionItems();
			static String OpenDirectionToString(const CBuiltInSelect::OpenDirection value);
			static CBuiltInSelect::OpenDirection StringToOpenDirection(const String &value);
			static StringArray ArrowAreaItems();
			static String ArrowAreaToString(const CBuiltInSelect::ArrowArea value);
			static CBuiltInSelect::ArrowArea StringToArrowArea(const String &value);
		public:
			CSelectPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}