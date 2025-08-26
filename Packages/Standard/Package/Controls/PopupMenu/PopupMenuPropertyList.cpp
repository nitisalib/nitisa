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
	namespace standard
	{
		CPopupMenuPropertyList::CPopupMenuPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Transform");
			Delete(L"TransformControls");
			Delete(L"Align");
			Delete(L"Size");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Visible");
			Delete(L"Enabled");

			Add(new CPropertyComponentImageList(this, control, L"ImageListEnabled", nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getImageListEnabled(); },
				[](IClass *parent, IImageList *value) {return cast<CPopupMenu*>(parent)->setImageListEnabled(value); }));
			Add(new CPropertyComponentImageList(this, control, L"ImageListDisabled", nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getImageListDisabled(); },
				[](IClass *parent, IImageList *value) {return cast<CPopupMenu*>(parent)->setImageListDisabled(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CPopupMenu*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CPopupMenu*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CPopupMenu*>(parent)->setBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CPopupMenu*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CPopupMenu*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CPopupMenu*>(parent)->setShadowColor(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CPopupMenu*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CPopupMenu*>(parent)->setShadowShift(value); }));
			Add(new CPropertyPointF(this, control, L"SubmenuShift", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getSubmenuShift(); },
				[](IClass *parent, const PointF value) {return cast<CPopupMenu*>(parent)->setSubmenuShift(value); }));
			Add(new CPropertyBool(this, control, L"IgnoreHotkeys", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getIgnoreHotkeys(); },
				[](IClass *parent, const bool value) {return cast<CPopupMenu*>(parent)->setIgnoreHotkeys(value); }));
			Add(new CPropertyFloat(this, control, L"HotkeyMaxInterval", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getHotkeyMaxInterval(); },
				[](IClass *parent, const float value) {return cast<CPopupMenu*>(parent)->setHotkeyMaxInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ScrollHeight", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getScrollHeight(); },
				[](IClass *parent, const float value) {return cast<CPopupMenu*>(parent)->setScrollHeight(value); }))
				->setMin(1);
			Add(new CPropertyColor(this, control, L"ScrollArrowColorNormal", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getScrollArrowColorNormal(); },
				[](IClass *parent, const Color value) {return cast<CPopupMenu*>(parent)->setScrollArrowColorNormal(value); }));
			Add(new CPropertyColor(this, control, L"ScrollArrowColorHovered", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getScrollArrowColorHovered(); },
				[](IClass *parent, const Color value) {return cast<CPopupMenu*>(parent)->setScrollArrowColorHovered(value); }));
			Add(new CPropertyColor(this, control, L"ScrollArrowColorDisabled", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getScrollArrowColorDisabled(); },
				[](IClass *parent, const Color value) {return cast<CPopupMenu*>(parent)->setScrollArrowColorDisabled(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CPopupMenu*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"DeltaScrollTimer", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getDeltaScrollTimer(); },
				[](IClass *parent, const float value) {return cast<CPopupMenu*>(parent)->setDeltaScrollTimer(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaScrollWheel", false, nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getDeltaScrollWheel(); },
				[](IClass *parent, const float value) {return cast<CPopupMenu*>(parent)->setDeltaScrollWheel(value); }))
				->setMin(0);
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CPopupMenu*>(parent)->getBackgroundGradient(); }));
		}
	}
}