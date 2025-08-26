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
		CContainerPropertyList::CContainerPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TabOrder");
			Delete(L"BlockSamples");
			Delete(L"InterpolateImage");
			Delete(L"InterpolateText");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"Enabled");
			Delete(L"UseParentFont");
			Delete(L"UseParentBlockSamples");
			Delete(L"UseParentInterpolateImage");
			Delete(L"UseParentInterpolateText");

			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) { return cast<CContainer*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CContainer*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) { return cast<CContainer*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) { return cast<CContainer*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CContainer*>(parent)->setUseMask(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) { return cast<CContainer*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CContainer*>(parent)->setPadding(value); }))
				->setMin(0);
		}
	}
}