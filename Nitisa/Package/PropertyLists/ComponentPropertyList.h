// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/PropertyList.h"

namespace nitisa
{
	class IComponent;
	class IPackage;
	class IPackageEntity;

	class CComponentPropertyList :public CPropertyList
	{
	public:
		CComponentPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity); // Create property list with all component properties
	};
}