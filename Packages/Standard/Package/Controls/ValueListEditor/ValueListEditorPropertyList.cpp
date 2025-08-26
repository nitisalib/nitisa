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
		CValueListEditorPropertyList::CValueListEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomStringGridPropertyList(package, control, entity)
		{
			Delete(L"Columns");
			Delete(L"FixedRows");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"KeyColumnTitle", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->getKeyColumnTitle(); },
				[](IClass *parent, const String value) {return cast<CValueListEditor*>(parent)->setKeyColumnTitle(value); }));
			Add(new CPropertyString(this, control, L"ValueColumnTitle", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->getValueColumnTitle(); },
				[](IClass *parent, const String value) {return cast<CValueListEditor*>(parent)->setValueColumnTitle(value); }));
			Add(new CPropertyBool(this, control, L"KeyColumnFixed", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->isKeyColumnFixed(); },
				[](IClass *parent, const bool value) {return cast<CValueListEditor*>(parent)->setKeyColumnFixed(value); }));
			Add(new CPropertyBool(this, control, L"KeysEditable", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->isKeysEditable(); },
				[](IClass *parent, const bool value) {return cast<CValueListEditor*>(parent)->setKeysEditable(value); }));
			Add(new CPropertyBool(this, control, L"KeysUnique", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->isKeysUnique(); },
				[](IClass *parent, const bool value) {return cast<CValueListEditor*>(parent)->setKeysUnique(value); }));
			Add(new CPropertyBool(this, control, L"KeysDeletable", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->isKeysDeletable(); },
				[](IClass *parent, const bool value) {return cast<CValueListEditor*>(parent)->setKeysDeletable(value); }));
			Add(new CPropertyBool(this, control, L"KeysAddable", false, nullptr,
				[](IClass *parent) {return cast<CValueListEditor*>(parent)->isKeysAddable(); },
				[](IClass *parent, const bool value) {return cast<CValueListEditor*>(parent)->setKeysAddable(value); }));
		}
	}
}