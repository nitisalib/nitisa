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
		CTCPClientPropertyList::CTCPClientPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyBool(this, component, L"Active", true, nullptr,
				[](IClass *parent) {return cast<CTCPClient*>(parent)->isActive(); },
				[](IClass *parent, const bool value) {return cast<CTCPClient*>(parent)->setActive(value); }));
			Add(new CPropertyFloat(this, component, L"ConnectTimeout", false, nullptr,
				[](IClass *parent) {return cast<CTCPClient*>(parent)->getConnectTimeout(); },
				[](IClass *parent, const float value) {return cast<CTCPClient*>(parent)->setConnectTimeout(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, component, L"Timeout", false, nullptr,
				[](IClass *parent) {return cast<CTCPClient*>(parent)->getTimeout(); },
				[](IClass *parent, const float value) {return cast<CTCPClient*>(parent)->setTimeout(value); }))
				->setMin(0.001f);
			Add(new CPropertyString(this, component, L"Server", false, nullptr,
				[](IClass *parent) {return cast<CTCPClient*>(parent)->getServer(); },
				[](IClass *parent, const String value) {return cast<CTCPClient*>(parent)->setServer(value); }));
			Add(new CPropertyInteger(this, component, L"Port", false, nullptr,
				[](IClass *parent) {return cast<CTCPClient*>(parent)->getPort(); },
				[](IClass *parent, const int value) {return cast<CTCPClient*>(parent)->setPort(value); }))
				->setMin(0);
		}
	}
}