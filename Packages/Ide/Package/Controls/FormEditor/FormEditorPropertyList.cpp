// This file is a part of Nitisa framework
// Copyright © 2022 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace ide
	{
		CFormEditorPropertyList::CFormEditorPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.Distance");
			Delete(L"Font.Monospace");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Cursor");
			Delete(L"Enabled");
			Delete(L"UseParentFont");

			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CFormEditor*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"SelectionSize", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getSelectionSize(); },
				[](IClass *parent, const float value) { return cast<CFormEditor*>(parent)->setSelectionSize(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"SelectionColor", false, SelectionStates(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CFormEditor*>(parent)->getSelectionColor(StringToSelectionState(state)); },
				[](IClass *parent, const String &state, const Color value) { return cast<CFormEditor*>(parent)->setSelectionColor(StringToSelectionState(state), value); }));
			Add(new CPropertyPointB(this, control, L"GridEnabled", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getGridEnabled(); },
				[](IClass *parent, const PointB value) { return cast<CFormEditor*>(parent)->setGridEnabled(value); }));
			Add(new CPropertyPointF(this, control, L"GridSize", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getGridSize(); },
				[](IClass *parent, const PointF value) { return cast<CFormEditor*>(parent)->setGridSize(value); }))
				->setMin(1);
			Add(new CPropertyFloat(this, control, L"GridPointSize", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getGridPointSize(); },
				[](IClass *parent, const float value) { return cast<CFormEditor*>(parent)->setGridPointSize(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"GridPointColor", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getGridPointColor(); },
				[](IClass *parent, const Color value) { return cast<CFormEditor*>(parent)->setGridPointColor(value); }));
			Add(new CPropertyBool(this, control, L"RotateGridEnabled", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->isRotateGridEnabled(); },
				[](IClass *parent, const bool value) { return cast<CFormEditor*>(parent)->setRotateGridEnabled(value); }));
			Add(new CPropertyFloat(this, control, L"RotateGridSize", false, nullptr,
				[](IClass *parent) {return ntl::RadToDeg<float>(cast<CFormEditor*>(parent)->getRotateGridSize()); },
				[](IClass *parent, const float value) { return cast<CFormEditor*>(parent)->setRotateGridSize(ntl::DegToRad<float>(value)); }))
				->setMin(1)->setMax(90);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) { return cast<CFormEditor*>(parent)->setUseMask(value); }));
			Add(new CPropertyFloat(this, control, L"RotateShift", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getRotateShift(); },
				[](IClass *parent, const float value) { return cast<CFormEditor*>(parent)->setRotateShift(value); }))
				->setMin(1);
			Add(new CPropertyFloat(this, control, L"SelectionBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getSelectionBorderWidth(); },
				[](IClass *parent, const float value) { return cast<CFormEditor*>(parent)->setSelectionBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"SelectionBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getSelectionBorderColor(); },
				[](IClass *parent, const Color value) { return cast<CFormEditor*>(parent)->setSelectionBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"SelectionBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getSelectionBackgroundColor(); },
				[](IClass *parent, const Color value) { return cast<CFormEditor*>(parent)->setSelectionBackgroundColor(value); }));
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CFormEditor*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) { return cast<CFormEditor*>(parent)->setPadding(value); }))
				->setMin(0);
		}

		StringArray CFormEditorPropertyList::SelectionStates()
		{
			return StringArray{
				L"SelectionState::Normal",
				L"SelectionState::Hovered",
				L"SelectionState::Active",
				L"SelectionState::Disabled" };
		}

		CFormEditor::SelectionState CFormEditorPropertyList::StringToSelectionState(const String &state)
		{
			if (state == L"SelectionState::Hovered")
				return CFormEditor::SelectionState::Hovered;
			if (state == L"SelectionState::Active")
				return CFormEditor::SelectionState::Active;
			if (state == L"SelectionState::Disabled")
				return CFormEditor::SelectionState::Disabled;
			return CFormEditor::SelectionState::Normal;
		}
	}
}