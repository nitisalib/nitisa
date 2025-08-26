// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
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
		CTabSheetPropertyList::CTabSheetPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Transform");
			Delete(L"Align");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"ZIndex");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Visible");
			Delete(L"Enabled");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) { return cast<CTabSheet*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CTabSheet*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyInteger(this, control, L"IconIndex", false, nullptr,
				[](IClass *parent) { return cast<CTabSheet*>(parent)->getIconIndex(); },
				[](IClass *parent, const int value) {return cast<CTabSheet*>(parent)->setIconIndex(value); }))
				->setMin(-1);
		}
	}
}