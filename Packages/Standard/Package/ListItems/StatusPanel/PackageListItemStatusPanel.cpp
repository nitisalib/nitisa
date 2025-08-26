// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
		CPackageListItemStatusPanel::CPackageListItemStatusPanel(IPackage *package, const String &ns) : CPackageListItem(package, ns)
		{

		}

		String CPackageListItemStatusPanel::getCategory()
		{
			return L"Standard";
		}
	}
}