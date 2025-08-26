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
		CLoggerPropertyList::CLoggerPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"FileName", false, nullptr,
				[](IClass *parent) {return cast<CLogger*>(parent)->getFileName(); },
				[](IClass *parent, const String value) {return cast<CLogger*>(parent)->setFileName(value); }));
		}
	}
}