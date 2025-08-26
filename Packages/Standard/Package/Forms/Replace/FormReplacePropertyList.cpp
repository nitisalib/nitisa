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
		CFormReplacePropertyList::CFormReplacePropertyList(IPackage *package, IForm *form, IPackageEntity *entity) :
			CFormPropertyList(package, form, entity)
		{
			Add(new CPropertyString(this, form, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CFormReplace*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CFormReplace*>(parent)->setText(value); }));
			Add(new CPropertyString(this, form, L"Replace", false, nullptr,
				[](IClass *parent) {return cast<CFormReplace*>(parent)->getReplace(); },
				[](IClass *parent, const String value) {return cast<CFormReplace*>(parent)->setReplace(value); }));
			Add(new CPropertyBool(this, form, L"MatchWholeWords", false, nullptr,
				[](IClass *parent) {return cast<CFormReplace*>(parent)->isMatchWholeWords(); },
				[](IClass *parent, const bool value) {return cast<CFormReplace*>(parent)->setMatchWholeWords(value); }));
			Add(new CPropertyBool(this, form, L"MatchCase", false, nullptr,
				[](IClass *parent) {return cast<CFormReplace*>(parent)->isMatchCase(); },
				[](IClass *parent, const bool value) {return cast<CFormReplace*>(parent)->setMatchCase(value); }));
			Add(new CPropertyEnum(this, form, L"SearchDirection", false, SearchDirectionItems(), ExportPrefixType::Namespace, L"IFormReplace::", nullptr,
				[](IClass *parent) {return SearchDirectionToString(cast<CFormReplace*>(parent)->getSearchDirection()); },
				[](IClass *parent, const String value) {return cast<CFormReplace*>(parent)->setSearchDirection(StringToSearchDirection(value)); }))
				->AddHeaderFile(L"Standard/Forms/IFormReplace.h");
		}

		StringArray CFormReplacePropertyList::SearchDirectionItems()
		{
			return StringArray{
				L"SearchDirection::Up",
				L"SearchDirection::Down",
				L"SearchDirection::Selection" };
		}

		String CFormReplacePropertyList::SearchDirectionToString(IFormReplace::SearchDirection value)
		{
			switch (value)
			{
			case IFormReplace::SearchDirection::Up:		return L"SearchDirection::Up";
			case IFormReplace::SearchDirection::Down:	return L"SearchDirection::Down";
			default:									return L"SearchDirection::Selection";
			}
		}

		IFormReplace::SearchDirection CFormReplacePropertyList::StringToSearchDirection(const String &value)
		{
			if (value == L"SearchDirection::Up")
				return IFormReplace::SearchDirection::Up;
			if (value == L"SearchDirection::Down")
				return IFormReplace::SearchDirection::Down;
			return IFormReplace::SearchDirection::Selection;
		}
	}
}