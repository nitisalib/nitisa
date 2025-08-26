// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "ControlPropertyList.h"

namespace nitisa
{
	class IDialogBox;
	class IPackage;
	class IPackageEntity;

	class CDialogBoxPropertyList :public CControlPropertyList
	{
	public:
		CDialogBoxPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity); // Create with all control properties added
	};
}