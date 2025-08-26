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
		CTimerEventList::CTimerEventList(IPackage *package, IComponent *component, IPackageEntity *entity) :CComponentEventList(package, component, entity)
		{
			Add(new CEvent(this, component, L"OnTimer", L"IComponent *sender", L"sender"))
				->AddForwardDeclaration(L"class IComponent;", L"Nitisa/Interfaces/IComponent.h", L"");
		}
	}
}