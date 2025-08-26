// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../DropDown/CustomDropDownEventList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CColorBoxEventList :public CCustomDropDownEventList
		{
		public:
			CColorBoxEventList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}