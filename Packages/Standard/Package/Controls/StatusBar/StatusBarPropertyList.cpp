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
		CStatusBarPropertyList::CStatusBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Align");
			Delete(L"Constraints");
			Delete(L"Size");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Enabled");

			Add(new CPropertyRectF(this, control, L"OuterBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getOuterBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CStatusBar*>(parent)->setOuterBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"InnerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getInnerBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CStatusBar*>(parent)->setInnerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CStatusBar*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"OuterBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getOuterBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CStatusBar*>(parent)->setOuterBorderColor(value); }));
			Add(new CPropertyBorderColor(this, control, L"InnerBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getInnerBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CStatusBar*>(parent)->setInnerBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CStatusBar*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CStatusBar*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CStatusBar*>(parent)->setShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CStatusBar*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyFloat(this, control, L"SeparatorWidth", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getSeparatorWidth(); },
				[](IClass *parent, const float value) {return cast<CStatusBar*>(parent)->setSeparatorWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"SeparatorColor", false, nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getSeparatorColor(); },
				[](IClass *parent, const Color value) {return cast<CStatusBar*>(parent)->setSeparatorColor(value); }));
			Add(new CPropertyGradient(this, control, L"SeparatorGradient", nullptr,
				[](IClass *parent) {return cast<CStatusBar*>(parent)->getSeparatorGradient(); }));
		}
	}
}