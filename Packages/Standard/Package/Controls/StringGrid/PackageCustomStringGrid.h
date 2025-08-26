// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../DrawGrid/PackageCustomDrawGrid.h"

namespace nitisa
{
	class IPackage;

	namespace standard
	{
		class CPackageCustomStringGrid :public CPackageCustomDrawGrid
		{
		public:
			CPackageCustomStringGrid(IPackage *package, const String &ns);
		};
	}
}