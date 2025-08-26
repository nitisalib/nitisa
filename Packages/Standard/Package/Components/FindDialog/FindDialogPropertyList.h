// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/ComponentPropertyList.h"
#include "../../../Forms/IFormFind.h"

namespace nitisa
{
	class IComponent;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CFindDialogPropertyList :public CComponentPropertyList
		{
		private:
			static StringArray SearchDirectionItems();
			static String SearchDirectionToString(IFormFind::SearchDirection value);
			static IFormFind::SearchDirection StringToSearchDirection(const String &value);
		public:
			CFindDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity);
		};
	}
}