// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/PropertyLists/ComponentPropertyList.h"

namespace nitisa
{
	class IComponent;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CImageListPropertyList :public CComponentPropertyList
		{
		public:
			CImageListPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity);
		};
	}
}