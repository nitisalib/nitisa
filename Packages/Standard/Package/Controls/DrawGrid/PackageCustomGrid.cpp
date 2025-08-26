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
		CPackageCustomGrid::CPackageCustomGrid(IPackage *package, const String &ns) : CPackageControl(package, ns)
		{
			AddHeaderFile(L"Standard/Controls/DrawGrid/CustomGrid.h");
		}
	}
}