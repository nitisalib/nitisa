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
		CSysBrowseFolderDialogPropertyList::CSysBrowseFolderDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyString(this, component, L"Title", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->getTitle(); },
				[](IClass *parent, const String value) {return cast<CSysBrowseFolderDialog*>(parent)->setTitle(value); }));
			Add(new CPropertyBool(this, component, L"OnlyFileSystem", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isOnlyFileSystem(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setOnlyFileSystem(value); }));
			Add(new CPropertyBool(this, component, L"NoNetwork", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isNoNetwork(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setNoNetwork(value); }));
			Add(new CPropertyBool(this, component, L"NoAncestors", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isNoAncestors(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setNoAncestors(value); }));
			Add(new CPropertyBool(this, component, L"ShowEditBox", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isShowEditBox(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setShowEditBox(value); }));
			Add(new CPropertyBool(this, component, L"NewStyle", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isNewStyle(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setNewStyle(value); }));
			Add(new CPropertyBool(this, component, L"ShowHint", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isShowHint(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setShowHint(value); }));
			Add(new CPropertyBool(this, component, L"HideNewFolder", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isHideNewFolder(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setHideNewFolder(value); }));
			Add(new CPropertyBool(this, component, L"DontTranslateTargets", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isDontTranslateTargets(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setDontTranslateTargets(value); }));
			Add(new CPropertyBool(this, component, L"OnlyComputers", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isOnlyComputers(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setOnlyComputers(value); }));
			Add(new CPropertyBool(this, component, L"OnlyPrinters", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isOnlyPrinters(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setOnlyPrinters(value); }));
			Add(new CPropertyBool(this, component, L"ShowFiles", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isShowFiles(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setShowFiles(value); }));
			Add(new CPropertyBool(this, component, L"ShowShareable", false, nullptr,
				[](IClass *parent) {return cast<CSysBrowseFolderDialog*>(parent)->isShowShareable(); },
				[](IClass *parent, const bool value) {return cast<CSysBrowseFolderDialog*>(parent)->setShowShareable(value); }));
		}
	}
}