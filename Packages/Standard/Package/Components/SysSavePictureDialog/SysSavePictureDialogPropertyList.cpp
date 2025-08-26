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
		CSysSavePictureDialogPropertyList::CSysSavePictureDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyText(this, component, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CSysSavePictureDialog*>(parent)->setFilter(value); }));
			Add(new CPropertyInteger(this, component, L"FilterIndex", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->getFilterIndex(); },
				[](IClass *parent, const int value) {return cast<CSysSavePictureDialog*>(parent)->setFilterIndex(value); }));
			Add(new CPropertyString(this, component, L"FileName", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->getFileName(); },
				[](IClass *parent, const String value) {return cast<CSysSavePictureDialog*>(parent)->setFileName(value); }));
			Add(new CPropertyString(this, component, L"DefaultExtension", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->getDefaultExtension(); },
				[](IClass *parent, const String value) {return cast<CSysSavePictureDialog*>(parent)->setDefaultExtension(value); }));
			Add(new CPropertyBool(this, component, L"CreatePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isCreatePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setCreatePrompt(value); }));
			Add(new CPropertyBool(this, component, L"MustExists", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isMustExists(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setMustExists(value); }));
			Add(new CPropertyBool(this, component, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, component, L"HideReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isHideReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setHideReadOnly(value); }));
			Add(new CPropertyBool(this, component, L"NoNetwork", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isNoNetwork(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setNoNetwork(value); }));
			Add(new CPropertyBool(this, component, L"OverwritePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysSavePictureDialog*>(parent)->isOverwritePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysSavePictureDialog*>(parent)->setOverwritePrompt(value); }));
		}
	}
}