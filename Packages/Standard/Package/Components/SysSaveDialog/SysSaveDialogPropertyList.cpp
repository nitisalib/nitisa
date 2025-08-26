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
		CSysSaveDialogPropertyList::CSysSaveDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyText(this, component, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CSysSaveDialog*>(parent)->setFilter(value); }));
			Add(new CPropertyInteger(this, component, L"FilterIndex", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->getFilterIndex(); },
				[](IClass *parent, const int value) {return cast<CSysSaveDialog*>(parent)->setFilterIndex(value); }));
			Add(new CPropertyString(this, component, L"FileName", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->getFileName(); },
				[](IClass *parent, const String value) {return cast<CSysSaveDialog*>(parent)->setFileName(value); }));
			Add(new CPropertyString(this, component, L"DefaultExtension", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->getDefaultExtension(); },
				[](IClass *parent, const String value) {return cast<CSysSaveDialog*>(parent)->setDefaultExtension(value); }));
			Add(new CPropertyBool(this, component, L"CreatePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isCreatePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setCreatePrompt(value); }));
			Add(new CPropertyBool(this, component, L"MustExists", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isMustExists(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setMustExists(value); }));
			Add(new CPropertyBool(this, component, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, component, L"HideReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isHideReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setHideReadOnly(value); }));
			Add(new CPropertyBool(this, component, L"NoNetwork", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isNoNetwork(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setNoNetwork(value); }));
			Add(new CPropertyBool(this, component, L"OverwritePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysSaveDialog*>(parent)->isOverwritePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysSaveDialog*>(parent)->setOverwritePrompt(value); }));
		}
	}
}