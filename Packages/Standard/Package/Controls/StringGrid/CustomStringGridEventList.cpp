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
		CCustomStringGridEventList::CCustomStringGridEventList(IPackage *package, IControl *control, IPackageEntity *entity) :CCustomDrawGridEventList(package, control, entity)
		{
			Add(new CEvent(this, control, L"OnChangeCell", L"{namespace}IStringGrid *sender, const int column, const int row, const String &value, bool &allowed", L"sender, column, row, value, allowed"))
				->AddForwardDeclaration(L"class IStringGrid;", L"Standard/Controls/IStringGrid.h", L"standard")
				->AddHeaderFile(L"Nitisa/Core/Strings.h");
			Add(new CEvent(this, control, L"OnSetFocusCell", L"{namespace}IStringGrid *sender, const int column, const int row", L"sender, column, row"))
				->AddForwardDeclaration(L"class IStringGrid;", L"Standard/Controls/IStringGrid.h", L"standard");
			Add(new CEvent(this, control, L"OnKillFocusCell", L"{namespace}IStringGrid *sender, const int column, const int row", L"sender, column, row"))
				->AddForwardDeclaration(L"class IStringGrid;", L"Standard/Controls/IStringGrid.h", L"standard");
		}
	}
}