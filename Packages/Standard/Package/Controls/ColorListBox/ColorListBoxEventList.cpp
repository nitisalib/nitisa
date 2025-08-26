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
		CColorListBoxEventList::CColorListBoxEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CCustomListBoxEventList(package, control, entity)
		{
			// Clipboard events
			Delete(L"OnPasteString");
		}
	}
}