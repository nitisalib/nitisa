// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../ListBox/CustomListBoxPropertyList.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CColorListBoxPropertyList :public CCustomListBoxPropertyList
		{
		public:
			CColorListBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}