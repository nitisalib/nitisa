// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	CDialogBoxPropertyList::CDialogBoxPropertyList(IPackage *package, IDialogBox *control, IPackageEntity *entity) :CControlPropertyList(package, control, entity)
	{
		Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->getBackgroundColor(); },
			[](IClass *parent, const Color value) {return cast<IDialogBox*>(parent)->setBackgroundColor(value); }));
		Add(new CPropertyString(this, control, L"Caption", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->getCaption(); },
			[](IClass *parent, const String value) {return cast<IDialogBox*>(parent)->setCaption(value); }));
		Add(new CPropertyPoint(this, control, L"ClientSize", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->getClientSize(); },
			[](IClass *parent, const Point value) {return cast<IDialogBox*>(parent)->setClientSize(value); }))
			->setMin(0);
		Add(new CPropertyEnum(this, control, L"WindowPosition", true, WindowPositionItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return WindowPositionToString(cast<IDialogBox*>(parent)->getWindowPosition()); },
			[](IClass *parent, const String value) {return cast<IDialogBox*>(parent)->setWindowPosition(StringToWindowPosition(value)); }))
			->AddHeaderFile(L"Nitisa/Core/WindowPosition.h");
		Add(new CPropertyEnum(this, control, L"State", false, WindowStateItems(), ExportPrefixType::None, L"", nullptr,
			[](IClass *parent) { return WindowStateToString(cast<IDialogBox*>(parent)->getState()); },
			[](IClass *parent, const String value) {return cast<IDialogBox*>(parent)->setState(StringToWindowState(value)); }))
			->AddHeaderFile(L"Nitisa/Core/WindowState.h");
		Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->getBorderWidth(); },
			[](IClass *parent, const RectF value) {return cast<IDialogBox*>(parent)->setBorderWidth(value); }))
			->setMin(0);
		Add(new CPropertyBool(this, control, L"HasCloseBox", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasCloseBox(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasCloseBox(value); }));
		Add(new CPropertyBool(this, control, L"HasMaximizeBox", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasMaximizeBox(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasMaximizeBox(value); }));
		Add(new CPropertyBool(this, control, L"HasMinimizeBox", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasMinimizeBox(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasMinimizeBox(value); }));
		Add(new CPropertyBool(this, control, L"HasSizeBox", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasSizeBox(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasSizeBox(value); }));
		Add(new CPropertyBool(this, control, L"HasSystemMenu", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasSystemMenu(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasSystemMenu(value); }));
		Add(new CPropertyBool(this, control, L"HasBorder", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasBorder(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasBorder(value); }));
		Add(new CPropertyBool(this, control, L"HasCaption", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->hasCaption(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setHasCaption(value); }));
		Add(new CPropertyBool(this, control, L"IsPopup", false, nullptr,
			[](IClass *parent) { return cast<IDialogBox*>(parent)->isPopup(); },
			[](IClass *parent, const bool value) {return cast<IDialogBox*>(parent)->setIsPopup(value); }));
	}
}