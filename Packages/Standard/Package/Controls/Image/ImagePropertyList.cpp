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
		CImagePropertyList::CImagePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
			Delete(L"Enabled");

			Add(new CPropertyImage(this, control, L"Image", nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getImage(); },
				[](IClass *parent) {cast<CImage*>(parent)->Update(); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CImage*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CImage*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CImage*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CImage*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CImage*>(parent)->setShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CImage*>(parent)->setShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CImage*>(parent)->setShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyMatrix(this, control, L"ImageTransform", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getImageTransform(); },
				[](IClass *parent, const Mat4f value) {return cast<CImage*>(parent)->setImageTransform(value); }));
			Add(new CPropertyFloat(this, control, L"Opacity", false, nullptr,
				[](IClass *parent) {return cast<CImage*>(parent)->getOpacity(); },
				[](IClass *parent, const float value) {return cast<CImage*>(parent)->setOpacity(value); }))
				->setMin(0)
				->setMax(1);
		}
	}
}