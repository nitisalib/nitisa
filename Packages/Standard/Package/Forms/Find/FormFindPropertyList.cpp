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
		CFormFindPropertyList::CFormFindPropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyString(this, form, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CFormFind*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CFormFind*>(parent)->setText(value); }));
			Add(new CPropertyBool(this, form, L"MatchWholeWords", false, nullptr,
				[](IClass *parent) {return cast<CFormFind*>(parent)->isMatchWholeWords(); },
				[](IClass *parent, const bool value) {return cast<CFormFind*>(parent)->setMatchWholeWords(value); }));
			Add(new CPropertyBool(this, form, L"MatchCase", false, nullptr,
				[](IClass *parent) {return cast<CFormFind*>(parent)->isMatchCase(); },
				[](IClass *parent, const bool value) {return cast<CFormFind*>(parent)->setMatchCase(value); }));
			Add(new CPropertyEnum(this, form, L"SearchDirection", false, SearchDirectionItems(), ExportPrefixType::Namespace, L"IFormFind::", nullptr,
				[](IClass *parent) {return SearchDirectionToString(cast<CFormFind*>(parent)->getSearchDirection()); },
				[](IClass *parent, const String value) {return cast<CFormFind*>(parent)->setSearchDirection(StringToSearchDirection(value)); }))
				->AddHeaderFile(L"Standard/Forms/IFormFind.h");
		}

		StringArray CFormFindPropertyList::SearchDirectionItems()
		{
			return StringArray{
				L"SearchDirection::Up",
				L"SearchDirection::Down" };
		}

		String CFormFindPropertyList::SearchDirectionToString(IFormFind::SearchDirection value)
		{
			switch (value)
			{
			case IFormFind::SearchDirection::Up:	return L"SearchDirection::Up";
			default:								return L"SearchDirection::Down";
			}
		}

		IFormFind::SearchDirection CFormFindPropertyList::StringToSearchDirection(const String &value)
		{
			if (value == L"SearchDirection::Up")
				return IFormFind::SearchDirection::Up;
			return IFormFind::SearchDirection::Down;
		}
	}
}