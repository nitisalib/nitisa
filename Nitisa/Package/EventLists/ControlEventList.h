// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "ComponentEventList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	class CControlEventList :public CComponentEventList
	{
	public:
		CControlEventList(IPackage *package, IControl *control, IPackageEntity *entity); // Create event list with all control events
	};
}