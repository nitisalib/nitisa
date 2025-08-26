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
		CFormReplaceEventList::CFormReplaceEventList(IPackage *package, IForm *form, IPackageEntity *entity) :CFormEventList(package, form, entity)
		{
			Add(new CEvent(this, form, L"OnReplace", L"{namespace}IFormReplace *sender", L"sender"))
				->AddForwardDeclaration(L"class IFormReplace;", L"Standard/Forms/IFormReplace.h", L"standard");
			Add(new CEvent(this, form, L"OnReplaceAll", L"{namespace}IFormReplace *sender", L"sender"))
				->AddForwardDeclaration(L"class IFormReplace;", L"Standard/Forms/IFormReplace.h", L"standard");
		}
	}
}