// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
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

	namespace charts
	{
		class CFormLineInterpolationPositionArrayPropertyList :public CFormPropertyList
		{
		public:
			CFormLineInterpolationPositionArrayPropertyList(IPackage *package, IForm *form, IPackageEntity *entity);
		};
	}
}