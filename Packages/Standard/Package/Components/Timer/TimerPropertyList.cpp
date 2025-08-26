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
		CTimerPropertyList::CTimerPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyFloat(this, component, L"Interval", true, nullptr,
				[](IClass *parent) {return cast<CTimer*>(parent)->getInterval(); },
				[](IClass *parent, const float value) {return cast<CTimer*>(parent)->setInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyBool(this, component, L"Enabled", false, nullptr,
				[](IClass *parent) {return cast<CTimer*>(parent)->isEnabled(); },
				[](IClass *parent, const bool value) {return cast<CTimer*>(parent)->setEnabled(value); }));
		}
	}
}