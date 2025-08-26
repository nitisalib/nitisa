// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/PropertyLists/FormPropertyList.h"
#include "../../../Forms/IFormFind.h"

namespace nitisa
{
	class IForm;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CFormFindPropertyList :public CFormPropertyList
		{
		private:
			static StringArray SearchDirectionItems();
			static String SearchDirectionToString(IFormFind::SearchDirection value);
			static IFormFind::SearchDirection StringToSearchDirection(const String &value);
		public:
			CFormFindPropertyList(IPackage *package, IForm *form, IPackageEntity *entity);
		};
	}
}