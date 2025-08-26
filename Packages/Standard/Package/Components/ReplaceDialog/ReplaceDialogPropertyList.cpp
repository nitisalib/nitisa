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
		CReplaceDialogPropertyList::CReplaceDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CReplaceDialog*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CReplaceDialog*>(parent)->setText(value); }));
			Add(new CPropertyString(this, component, L"Replace", false, nullptr,
				[](IClass *parent) {return cast<CReplaceDialog*>(parent)->getReplace(); },
				[](IClass *parent, const String value) {return cast<CReplaceDialog*>(parent)->setReplace(value); }));
			Add(new CPropertyBool(this, component, L"MatchWholeWords", false, nullptr,
				[](IClass *parent) {return cast<CReplaceDialog*>(parent)->isMatchWholeWords(); },
				[](IClass *parent, const bool value) {return cast<CReplaceDialog*>(parent)->setMatchWholeWords(value); }));
			Add(new CPropertyBool(this, component, L"MatchCase", false, nullptr,
				[](IClass *parent) {return cast<CReplaceDialog*>(parent)->isMatchCase(); },
				[](IClass *parent, const bool value) {return cast<CReplaceDialog*>(parent)->setMatchCase(value); }));
			Add(new CPropertyEnum(this, component, L"SearchDirection", false, SearchDirectionItems(), ExportPrefixType::Namespace, L"IFormReplace::", nullptr,
				[](IClass *parent) {return SearchDirectionToString(cast<CReplaceDialog*>(parent)->getSearchDirection()); },
				[](IClass *parent, const String value) {return cast<CReplaceDialog*>(parent)->setSearchDirection(StringToSearchDirection(value)); }))
				->AddHeaderFile(L"Standard/Components/IReplaceDialog.h");
			Add(new CPropertyBool(this, component, L"UseDialogBox", false, nullptr,
				[](IClass *parent) {return cast<CReplaceDialog*>(parent)->isUseDialogBox(); },
				[](IClass *parent, const bool value) {return cast<CReplaceDialog*>(parent)->setUseDialogBox(value); }));
		}

		StringArray CReplaceDialogPropertyList::SearchDirectionItems()
		{
			return StringArray{
				L"SearchDirection::Up",
				L"SearchDirection::Down",
				L"SearchDirection::Selection" };
		}

		String CReplaceDialogPropertyList::SearchDirectionToString(IFormReplace::SearchDirection value)
		{
			switch (value)
			{
			case IFormReplace::SearchDirection::Up:		return L"SearchDirection::Up";
			case IFormReplace::SearchDirection::Down:	return L"SearchDirection::Down";
			default:									return L"SearchDirection::Selection";
			}
		}

		IFormReplace::SearchDirection CReplaceDialogPropertyList::StringToSearchDirection(const String &value)
		{
			if (value == L"SearchDirection::Up")
				return IFormReplace::SearchDirection::Up;
			if (value == L"SearchDirection::Down")
				return IFormReplace::SearchDirection::Down;
			return IFormReplace::SearchDirection::Selection;
		}
	}
}