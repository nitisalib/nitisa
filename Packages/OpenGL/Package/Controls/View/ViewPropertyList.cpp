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
	namespace opengl
	{
		CViewPropertyList::CViewPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Style");
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Enabled");
			Delete(L"UseParentFont");

			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CView*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyFloat(this, control, L"TurnSpeed", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getTurnSpeed(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setTurnSpeed(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"MoveSpeed", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getMoveSpeed(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setMoveSpeed(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"MoveSlowMultiplier", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getMoveSlowMultiplier(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setMoveSlowMultiplier(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"MoveFastMultiplier", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getMoveFastMultiplier(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setMoveFastMultiplier(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"FOVStep", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getFOVStep(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setFOVStep(value); }))
				->setMin(0.001f);

			Add(new CPropertyBool(this, control, L"ShowXAxis", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->isShowXAxis(); },
				[](IClass *parent, const bool value) {return cast<CView*>(parent)->setShowXAxis(value); }));
			Add(new CPropertyBool(this, control, L"ShowYAxis", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->isShowYAxis(); },
				[](IClass *parent, const bool value) {return cast<CView*>(parent)->setShowYAxis(value); }));
			Add(new CPropertyBool(this, control, L"ShowZAxis", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->isShowZAxis(); },
				[](IClass *parent, const bool value) {return cast<CView*>(parent)->setShowZAxis(value); }));
			Add(new CPropertyPointF(this, control, L"XAxisRange", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getXAxisRange(); },
				[](IClass *parent, const PointF value) {return cast<CView*>(parent)->setXAxisRange(value); }));
			Add(new CPropertyPointF(this, control, L"YAxisRange", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getYAxisRange(); },
				[](IClass *parent, const PointF value) {return cast<CView*>(parent)->setYAxisRange(value); }));
			Add(new CPropertyPointF(this, control, L"ZAxisRange", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getZAxisRange(); },
				[](IClass *parent, const PointF value) {return cast<CView*>(parent)->setZAxisRange(value); }));
			Add(new CPropertyColor(this, control, L"XAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getXAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CView*>(parent)->setXAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"YAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getYAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CView*>(parent)->setYAxisColor(value); }));
			Add(new CPropertyColor(this, control, L"ZAxisColor", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getZAxisColor(); },
				[](IClass *parent, const Color value) {return cast<CView*>(parent)->setZAxisColor(value); }));

			Add(new CPropertyBool(this, control, L"ShowGrid", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->isShowGrid(); },
				[](IClass *parent, const bool value) {return cast<CView*>(parent)->setShowGrid(value); }));
			Add(new CPropertyFloat(this, control, L"GridXRange", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getGridXRange(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setGridXRange(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"GridZRange", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getGridZRange(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setGridZRange(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"GridStep", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getGridStep(); },
				[](IClass *parent, const float value) {return cast<CView*>(parent)->setGridStep(value); }))
				->setMin(0.001f);
			Add(new CPropertyColor(this, control, L"GridColor", false, nullptr,
				[](IClass *parent) {return cast<CView*>(parent)->getGridColor(); },
				[](IClass *parent, const Color value) {return cast<CView*>(parent)->setGridColor(value); }));
		}
	}
}