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
		CTCPServerPropertyList::CTCPServerPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyBool(this, component, L"Active", true, nullptr,
				[](IClass *parent) {return cast<CTCPServer*>(parent)->isActive(); },
				[](IClass *parent, const bool value) {return cast<CTCPServer*>(parent)->setActive(value); }));
			Add(new CPropertyInteger(this, component, L"Port", false, nullptr,
				[](IClass *parent) {return cast<CTCPServer*>(parent)->getPort(); },
				[](IClass *parent, const int value) {return cast<CTCPServer*>(parent)->setPort(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, component, L"Timeout", false, nullptr,
				[](IClass *parent) {return cast<CTCPServer*>(parent)->getTimeout(); },
				[](IClass *parent, const float value) {return cast<CTCPServer*>(parent)->setTimeout(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, component, L"StopTimeout", false, nullptr,
				[](IClass *parent) {return cast<CTCPServer*>(parent)->getStopTimeout(); },
				[](IClass *parent, const float value) {return cast<CTCPServer*>(parent)->setStopTimeout(value); }))
				->setMin(0.001f);
			Add(new CPropertyInteger(this, component, L"MaxConnectionCount", false, nullptr,
				[](IClass *parent) {return cast<CTCPServer*>(parent)->getMaxConnectionCount(); },
				[](IClass *parent, const int value) {return cast<CTCPServer*>(parent)->setMaxConnectionCount(value); }))
				->setMin(0);
		}
	}
}