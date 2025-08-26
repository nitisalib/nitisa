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
		CSysPageSetupDialogPropertyList::CSysPageSetupDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyBool(this, component, L"DisableMargins", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->isDisableMargins(); },
				[](IClass *parent, const bool value) {return cast<CSysPageSetupDialog*>(parent)->setDisableMargins(value); }));
			Add(new CPropertyBool(this, component, L"DisableOrientation", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->isDisableOrientation(); },
				[](IClass *parent, const bool value) {return cast<CSysPageSetupDialog*>(parent)->setDisableOrientation(value); }));
			Add(new CPropertyBool(this, component, L"DisablePagePainting", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->isDisablePagePainting(); },
				[](IClass *parent, const bool value) {return cast<CSysPageSetupDialog*>(parent)->setDisablePagePainting(value); }));
			Add(new CPropertyBool(this, component, L"DisablePaper", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->isDisablePaper(); },
				[](IClass *parent, const bool value) {return cast<CSysPageSetupDialog*>(parent)->setDisablePaper(value); }));
			Add(new CPropertyBool(this, component, L"NoNetworkButton", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->isNoNetworkButton(); },
				[](IClass *parent, const bool value) {return cast<CSysPageSetupDialog*>(parent)->setNoNetworkButton(value); }));
			Add(new CPropertyRectF(this, component, L"MinMargins", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->getMinMargins(); },
				[](IClass *parent, const RectF value) {return cast<CSysPageSetupDialog*>(parent)->setMinMargins(value); }));
			Add(new CPropertyRectF(this, component, L"Margins", false, nullptr,
				[](IClass *parent) {return cast<CSysPageSetupDialog*>(parent)->getMargins(); },
				[](IClass *parent, const RectF value) {return cast<CSysPageSetupDialog*>(parent)->setMargins(value); }));
		}
	}
}