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
		CScrollBoxPropertyList::CScrollBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyEnum(this, control, L"VerticalScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CScrollBox*>(parent)->getVerticalScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CScrollBox*>(parent)->setVerticalScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"HorizontalScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CScrollBox*>(parent)->getHorizontalScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CScrollBox*>(parent)->setHorizontalScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CScrollBox*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CScrollBox*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CScrollBox*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyPointF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CScrollBox*>(parent)->getPadding(); },
				[](IClass *parent, const PointF value) {return cast<CScrollBox*>(parent)->setPadding(value); }))
				->setMin(0);
		}
	}
}