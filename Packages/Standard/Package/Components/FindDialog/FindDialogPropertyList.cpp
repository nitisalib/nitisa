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
		CFindDialogPropertyList::CFindDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CFindDialog*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CFindDialog*>(parent)->setText(value); }));
			Add(new CPropertyBool(this, component, L"MatchWholeWords", false, nullptr,
				[](IClass *parent) {return cast<CFindDialog*>(parent)->isMatchWholeWords(); },
				[](IClass *parent, const bool value) {return cast<CFindDialog*>(parent)->setMatchWholeWords(value); }));
			Add(new CPropertyBool(this, component, L"MatchCase", false, nullptr,
				[](IClass *parent) {return cast<CFindDialog*>(parent)->isMatchCase(); },
				[](IClass *parent, const bool value) {return cast<CFindDialog*>(parent)->setMatchCase(value); }));
			Add(new CPropertyEnum(this, component, L"SearchDirection", false, SearchDirectionItems(), ExportPrefixType::Namespace, L"IFormFind::", nullptr,
				[](IClass *parent) {return SearchDirectionToString(cast<CFindDialog*>(parent)->getSearchDirection()); },
				[](IClass *parent, const String value) {return cast<CFindDialog*>(parent)->setSearchDirection(StringToSearchDirection(value)); }))
				->AddHeaderFile(L"Standard/Components/IFindDialog.h");
			Add(new CPropertyBool(this, component, L"UseDialogBox", false, nullptr,
				[](IClass *parent) {return cast<CFindDialog*>(parent)->isUseDialogBox(); },
				[](IClass *parent, const bool value) {return cast<CFindDialog*>(parent)->setUseDialogBox(value); }));
		}

		StringArray CFindDialogPropertyList::SearchDirectionItems()
		{
			return StringArray{
				L"SearchDirection::Up",
				L"SearchDirection::Down" };
		}

		String CFindDialogPropertyList::SearchDirectionToString(IFormFind::SearchDirection value)
		{
			switch (value)
			{
			case IFormFind::SearchDirection::Up:	return L"SearchDirection::Up";
			default:								return L"SearchDirection::Down";
			}
		}

		IFormFind::SearchDirection CFindDialogPropertyList::StringToSearchDirection(const String &value)
		{
			if (value == L"SearchDirection::Up")
				return IFormFind::SearchDirection::Up;
			return IFormFind::SearchDirection::Down;
		}
	}
}