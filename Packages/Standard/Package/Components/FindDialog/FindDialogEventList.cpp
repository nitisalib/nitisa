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
		CFindDialogEventList::CFindDialogEventList(IPackage *package, IComponent *component, IPackageEntity *entity) :CComponentEventList(package, component, entity)
		{
			Add(new CEvent(this, component, L"OnSearch", L"{namespace}IFindDialog *sender", L"sender"))
				->AddForwardDeclaration(L"class IFindDialog;", L"Standard/Components/IFindDialog.h", L"standard");
		}
	}
}