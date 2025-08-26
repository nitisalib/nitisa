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
		CSysPrintDialogPropertyList::CSysPrintDialogPropertyList(IPackage *package, IComponent *component, IPackageEntity *entity) :
			CComponentPropertyList(package, component, entity)
		{
			Add(new CPropertyBool(this, component, L"SelectCollate", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isSelectCollate(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setSelectCollate(value); }));
			Add(new CPropertyBool(this, component, L"SelectCurrentPage", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isSelectCurrentPage(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setSelectCurrentPage(value); }));
			Add(new CPropertyBool(this, component, L"DisablePrintToFile", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isDisablePrintToFile(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setDisablePrintToFile(value); }));
			Add(new CPropertyBool(this, component, L"HidePrintToFile", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isHidePrintToFile(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setHidePrintToFile(value); }));
			Add(new CPropertyBool(this, component, L"DisableCurrentPage", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isDisableCurrentPage(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setDisableCurrentPage(value); }));
			Add(new CPropertyBool(this, component, L"NoPageNums", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isNoPageNums(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setNoPageNums(value); }));
			Add(new CPropertyBool(this, component, L"NoSelection", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isNoSelection(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setNoSelection(value); }));
			Add(new CPropertyBool(this, component, L"SelectPageNums", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isSelectPageNums(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setSelectPageNums(value); }));
			Add(new CPropertyBool(this, component, L"SelectPrintToFile", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isSelectPrintToFile(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setSelectPrintToFile(value); }));
			Add(new CPropertyBool(this, component, L"SelectSelection", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->isSelectSelection(); },
				[](IClass *parent, const bool value) {return cast<CSysPrintDialog*>(parent)->setSelectSelection(value); }));
			Add(new CPropertyInteger(this, component, L"MinPage", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->getMinPage(); },
				[](IClass *parent, const int value) {return cast<CSysPrintDialog*>(parent)->setMinPage(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, component, L"MaxPage", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->getMaxPage(); },
				[](IClass *parent, const int value) {return cast<CSysPrintDialog*>(parent)->setMaxPage(value); }))
				->setMin(1);
			Add(new CPropertyInteger(this, component, L"MaxPageRangeCount", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->getMaxPageRangeCount(); },
				[](IClass *parent, const int value) {return cast<CSysPrintDialog*>(parent)->setMaxPageRangeCount(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, component, L"Copies", false, nullptr,
				[](IClass *parent) {return cast<CSysPrintDialog*>(parent)->getCopies(); },
				[](IClass *parent, const int value) {return cast<CSysPrintDialog*>(parent)->setCopies(value); }))
				->setMin(1);
		}
	}
}