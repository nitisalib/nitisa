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
		CSysOpenPictureDialogPropertyList::CSysOpenPictureDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyText(this, component, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CSysOpenPictureDialog*>(parent)->setFilter(value); }));
			Add(new CPropertyInteger(this, component, L"FilterIndex", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->getFilterIndex(); },
				[](IClass *parent, const int value) {return cast<CSysOpenPictureDialog*>(parent)->setFilterIndex(value); }));
			Add(new CPropertyString(this, component, L"FileName", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->getFileName(); },
				[](IClass *parent, const String value) {return cast<CSysOpenPictureDialog*>(parent)->setFileName(value); }));
			Add(new CPropertyBool(this, component, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setMultiselect(value); }));
			Add(new CPropertyBool(this, component, L"CreatePrompt", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isCreatePrompt(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setCreatePrompt(value); }));
			Add(new CPropertyBool(this, component, L"MustExists", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isMustExists(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setMustExists(value); }));
			Add(new CPropertyBool(this, component, L"ShowHidden", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isShowHidden(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setShowHidden(value); }));
			Add(new CPropertyBool(this, component, L"HideReadOnly", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isHideReadOnly(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setHideReadOnly(value); }));
			Add(new CPropertyBool(this, component, L"NoNetwork", false, nullptr,
				[](IClass *parent) {return cast<CSysOpenPictureDialog*>(parent)->isNoNetwork(); },
				[](IClass *parent, const bool value) {return cast<CSysOpenPictureDialog*>(parent)->setNoNetwork(value); }));
		}
	}
}