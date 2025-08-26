// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "ControlEventList.h"

namespace nitisa
{
	class IDialogBox;
	class IPackage;
	class IPackageEntity;

	class CDialogBoxEventList :public CControlEventList
	{
	public:
		CDialogBoxEventList(IPackage *package, IDialogBox *control, IPackageEntity *entity); // Create event list with all control events
	};
}