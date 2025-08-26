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
		CUpDownExPropertyList::CUpDownExPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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

			Add(new CPropertyFloat(this, control, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getMin(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setMin(value); }));
			Add(new CPropertyFloat(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getMax(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setMax(value); }));
			Add(new CPropertyFloat(this, control, L"Value", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getValue(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setValue(value); }));
			Add(new CPropertyFloat(this, control, L"Step", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getStep(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setStep(value); }))
				->setMin(0.000000001f);
			Add(new CPropertyControlEdit(this, control, L"AssignedTo", nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getAssignedTo(); },
				[](IClass *parent, IEdit *value) {return cast<CUpDownEx*>(parent)->setAssignedTo(value); }));
			Add(new CPropertyTransform(this, control, L"Transform", false, nullptr,
				[](IClass *parent) { return cast<CUpDownEx*>(parent)->getTransform()->getTransform(); },
				[](IClass *parent, const Transform value) {return cast<CUpDownEx*>(parent)->getTransform()->setTransform(value); }));
			Add(new CPropertyInteger(this, control, L"Signs", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getSigns(); },
				[](IClass *parent, const int value) {return cast<CUpDownEx*>(parent)->setSigns(value); }))
				->setMin(0)->setMax(9);
			Add(new CPropertyFloat(this, control, L"TimerInterval", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getTimerInterval(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setTimerInterval(value); }))
				->setMin(0.001f);

			Add(new CPropertyFloatState(this, control, L"Distance", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDistance(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CUpDownEx*>(parent)->setDistance(StringToState(state), value); }));

			Add(new CPropertyRectFState(this, control, L"UpArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setUpArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setUpArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowMiddleBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowMiddleBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setUpArrowMiddleBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowMiddleBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowMiddleBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setUpArrowMiddleBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setUpArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setUpArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDownEx*>(parent)->setUpArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"UpArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setUpArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"UpArrowArrowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getUpArrowArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDownEx*>(parent)->setUpArrowArrowColor(StringToState(state), value); }));

			Add(new CPropertyRectFState(this, control, L"DownArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setDownArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setDownArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowMiddleBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowMiddleBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setDownArrowMiddleBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowMiddleBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowMiddleBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setDownArrowMiddleBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setDownArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CUpDownEx*>(parent)->setDownArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDownEx*>(parent)->setDownArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"DownArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CUpDownEx*>(parent)->setDownArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"DownArrowArrowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CUpDownEx*>(parent)->getDownArrowArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CUpDownEx*>(parent)->setDownArrowArrowColor(StringToState(state), value); }));
			Add(new CPropertyBool(this, control, L"ChangeByDrag", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->isChangeByDrag(); },
				[](IClass *parent, const bool value) {return cast<CUpDownEx*>(parent)->setChangeByDrag(value); }));
			Add(new CPropertyFloat(this, control, L"DragShift", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getDragShift(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setDragShift(value); }));
			Add(new CPropertyFloat(this, control, L"DragScale", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getDragScale(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setDragScale(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBase", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getDragBase(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setDragBase(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBaseShift", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getDragBaseShift(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setDragBaseShift(value); }))
				->setMin(0.000001f);
			Add(new CPropertyFloat(this, control, L"DragBaseScale", false, nullptr,
				[](IClass *parent) {return cast<CUpDownEx*>(parent)->getDragBaseScale(); },
				[](IClass *parent, const float value) {return cast<CUpDownEx*>(parent)->setDragBaseScale(value); }))
				->setMin(0.000001f);
		}

		StringArray CUpDownExPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CUpDownEx::State CUpDownExPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CUpDownEx::State::Hovered;
			if (state == L"State::Active")
				return CUpDownEx::State::Active;
			if (state == L"State::Disabled")
				return CUpDownEx::State::Disabled;
			return CUpDownEx::State::Normal;
		}
	}
}