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
		CSimpleXMLPropertyList::CSimpleXMLPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"Version", false, nullptr,
				[](IClass *parent) {return cast<CSimpleXML*>(parent)->getVersion(); },
				[](IClass *parent, const String value) {return cast<CSimpleXML*>(parent)->setVersion(value); }));
			Add(new CPropertyString(this, component, L"Encoding", false, nullptr,
				[](IClass *parent) {return cast<CSimpleXML*>(parent)->getEncoding(); },
				[](IClass *parent, const String value) {return cast<CSimpleXML*>(parent)->setEncoding(value); }));
			Add(new CPropertyString(this, component, L"DOCTYPE", false, nullptr,
				[](IClass *parent) {return cast<CSimpleXML*>(parent)->getDoctype(); },
				[](IClass *parent, const String value) {return cast<CSimpleXML*>(parent)->setDoctype(value); }));
		}
	}
}