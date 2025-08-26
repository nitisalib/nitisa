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
	namespace standard
	{
		CUpDownPropertyList::CUpDownPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"Transform"); // Place it after "AssignedTo"
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");
			Delete(L"Align");

			Add(new CPropertyInteger(this, control, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getMin(); },
				[](IClass *parent, const int value) {return cast<CUpDown*>(parent)->setMin(value); }));
			Add(new CPropertyInteger(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getMax(); },
				[](IClass *parent, const int value) {return cast<CUpDown*>(parent)->setMax(value); }));
			Add(new CPropertyInteger(this, control, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getValue(); },
				[](IClass *parent, const int value) {return cast<CUpDown*>(parent)->setValue(value); }));
			Add(new CPropertyInteger(this, control, L"Step", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getStep(); },
				[](IClass *parent, const int value) {return cast<CUpDown*>(parent)->setStep(value); }))
				->setMin(1);
			Add(new CPropertyControlEdit(this, control, L"AssignedTo", nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getAssignedTo(); },
				[](IClass *parent, IEdit *value) {return cast<CUpDown*>(parent)->setAssignedTo(value); }));
			Add(new CPropertyTransform(this, control, L"Transform", false, nullptr,
				[](IClass *parent) { return cast<CUpDown*>(parent)->getTransform()->getTransform(); },
				[](IClass *parent, const Transform value) {return cast<CUpDown*>(parent)->getTransform()->setTransform(value); }));
			Add(new CPropertyFloat(this, control, L"TimerInterval", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getTimerInterval(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setTimerInterval(value); }))
				->setMin(0.001f);

			Add(new CPropertyFloatState(this, control, L"Distance", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDistance(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CUpDown*>(parent)->setDistance(StringToState(state), value); }));

			Add(new CPropertyRectFState(this, control, L"UpArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setUpArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setUpArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowMiddleBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowMiddleBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setUpArrowMiddleBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowMiddleBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowMiddleBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setUpArrowMiddleBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setUpArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setUpArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDown*>(parent)->setUpArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"UpArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setUpArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"UpArrowArrowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getUpArrowArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDown*>(parent)->setUpArrowArrowColor(StringToState(state), value); }));

			Add(new CPropertyRectFState(this, control, L"DownArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setDownArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setDownArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowMiddleBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowMiddleBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setDownArrowMiddleBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowMiddleBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowMiddleBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setDownArrowMiddleBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setDownArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDown*>(parent)->setDownArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDown*>(parent)->setDownArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"DownArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDown*>(parent)->setDownArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"DownArrowArrowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDown*>(parent)->getDownArrowArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDown*>(parent)->setDownArrowArrowColor(StringToState(state), value); }));
			Add(new CPropertyBool(this, control, L"ChangeByDrag", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->isChangeByDrag(); },
				[](IClass *parent, const bool value) {return cast<CUpDown*>(parent)->setChangeByDrag(value); }));
			Add(new CPropertyFloat(this, control, L"DragShift", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getDragShift(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setDragShift(value); }));
			Add(new CPropertyFloat(this, control, L"DragScale", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getDragScale(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setDragScale(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBase", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getDragBase(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setDragBase(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBaseShift", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getDragBaseShift(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setDragBaseShift(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBaseScale", false, nullptr,
				[](IClass *parent) {return cast<CUpDown*>(parent)->getDragBaseScale(); },
				[](IClass *parent, const float value) {return cast<CUpDown*>(parent)->setDragBaseScale(value); }))
				->setMin(0.000001f);
		}

		StringArray CUpDownPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CUpDown::State CUpDownPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CUpDown::State::Hovered;
			if (state == L"State::Active")
				return CUpDown::State::Active;
			if (state == L"State::Disabled")
				return CUpDown::State::Disabled;
			return CUpDown::State::Normal;
		}
	}
}