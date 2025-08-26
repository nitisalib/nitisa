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
#include "../../../Forms/IFormReplace.h"

namespace nitisa
{
	class IComponent;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CReplaceDialogPropertyList :public CComponentPropertyList
		{
		private:
			static StringArray SearchDirectionItems();
			static String SearchDirectionToString(IFormReplace::SearchDirection value);
			static IFormReplace::SearchDirection StringToSearchDirection(const String &value);
		public:
			CReplaceDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity);
		};
	}
}