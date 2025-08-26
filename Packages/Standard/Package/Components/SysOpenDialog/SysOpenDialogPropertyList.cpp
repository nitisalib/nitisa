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
		CSysOpenDialogPropertyList::CSysOpenDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyText(this, component, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CSysOpenDialog*>(parent)->setFilter(value); }));
			Add(new CPropertyInteger(this, component, L"FilterIndex", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->getFilterIndex(); },
				[](IClass *parent, const int value) {return cast<CSysOpenDialog*>(parent)->setFilterIndex(value); }));
			Add(new CPropertyString(this, component, L"FileName", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->getFileName(); },
				[](IClass *parent, const String value) {return cast<CSysOpenDialog*>(parent)->setFileName(value); }));
			Add(new CPropertyBool(this, component, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setMultiselect(value); }));
			Add(new CPropertyBool(this, component, L"CreatePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isCreatePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setCreatePrompt(value); }));
			Add(new CPropertyBool(this, component, L"MustExists", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isMustExists(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setMustExists(value); }));
			Add(new CPropertyBool(this, component, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, component, L"HideReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isHideReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setHideReadOnly(value); }));
			Add(new CPropertyBool(this, component, L"NoNetwork", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenDialog*>(parent)->isNoNetwork(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenDialog*>(parent)->setNoNetwork(value); }));
		}
	}
}