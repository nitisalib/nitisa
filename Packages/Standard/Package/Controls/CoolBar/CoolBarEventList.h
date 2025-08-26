// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/EventLists/DialogBoxEventList.h"

namespace nitisa
{
	class IDialogBox;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CCoolBarEventList :public CDialogBoxEventList
		{
		public:
			CCoolBarEventList(IPackage *package, IDialogBox *control, IPackageEntity *entity);
		};
	}
}