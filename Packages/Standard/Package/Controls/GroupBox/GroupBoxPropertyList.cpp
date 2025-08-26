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
		CGroupBoxPropertyList::CGroupBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CGroupBox*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CGroupBox*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CGroupBox*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CGroupBox*>(parent)->setBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CGroupBox*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CGroupBox*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CGroupBox*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CGroupBox*>(parent)->setShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CGroupBox*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyEnum(this, control, L"CaptionAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CGroupBox*>(parent)->getCaptionAlign()); },
				[](IClass *parent, const String value) {return cast<CGroupBox*>(parent)->setCaptionAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyPointF(this, control, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const PointF value) {return cast<CGroupBox*>(parent)->setCaptionPadding(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CGroupBox*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CGroupBox*>(parent)->setUseMask(value); }));
		}
	}
}