// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace standard
	{
		CPackageCustomStringGrid::CPackageCustomStringGrid(IPackage *package, const String &ns) : CPackageCustomDrawGrid(package, ns)
		{
			AddHeaderFile(L"Standard/Controls/StringGrid/CustomStringGrid.h");
		}
	}
}