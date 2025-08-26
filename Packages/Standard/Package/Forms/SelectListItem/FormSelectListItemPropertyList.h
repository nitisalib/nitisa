// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/PropertyLists/FormPropertyList.h"

namespace nitisa
{
	class IForm;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CFormSelectListItemPropertyList :public CFormPropertyList
		{
		public:
			CFormSelectListItemPropertyList(IPackage *package, IForm *form, IPackageEntity *entity);
		};
	}
}