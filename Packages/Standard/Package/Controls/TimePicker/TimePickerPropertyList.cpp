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
		CTimePickerPropertyList::CTimePickerPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyInteger(this, control, L"Hour", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getHour(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setHour(value); }))
				->setMin(0)->setMax(23);
			Add(new CPropertyInteger(this, control, L"Minute", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMinute(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMinute(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyInteger(this, control, L"Second", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getSecond(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setSecond(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyInteger(this, control, L"MinHour", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMinHour(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMinHour(value); }))
				->setMin(0)->setMax(23);
			Add(new CPropertyInteger(this, control, L"MinMinute", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMinMinute(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMinMinute(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyInteger(this, control, L"MinSecond", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMinSecond(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMinSecond(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyInteger(this, control, L"MaxHour", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMaxHour(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMaxHour(value); }))
				->setMin(0)->setMax(23);
			Add(new CPropertyInteger(this, control, L"MaxMinute", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMaxMinute(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMaxMinute(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyInteger(this, control, L"MaxSecond", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getMaxSecond(); },
				[](IClass *parent, const int value) {return cast<CTimePicker*>(parent)->setMaxSecond(value); }))
				->setMin(0)->setMax(59);
			Add(new CPropertyFloat(this, control, L"TimerInterval", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->getTimerInterval(); },
				[](IClass *parent, const float value) {return cast<CTimePicker*>(parent)->setTimerInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyBool(this, control, L"ShowSeconds", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->isShowSeconds(); },
				[](IClass *parent, const bool value) {return cast<CTimePicker*>(parent)->setShowSeconds(value); }));
			Add(new CPropertyBool(this, control, L"ShowArrows", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->isShowArrows(); },
				[](IClass *parent, const bool value) {return cast<CTimePicker*>(parent)->setShowArrows(value); }));
			Add(new CPropertyBool(this, control, L"ArrowsAtRight", false, nullptr,
				[](IClass *parent) {return cast<CTimePicker*>(parent)->isArrowsAtRight(); },
				[](IClass *parent, const bool value) {return cast<CTimePicker*>(parent)->setArrowsAtRight(value); }));
			Add(new CPropertyEnum(this, control, L"ContentAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CTimePicker*>(parent)->getContentAlign()); },
				[](IClass *parent, const String value) {return cast<CTimePicker*>(parent)->setContentAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CTimePicker*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CTimePicker*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setUpArrowBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"UpArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setUpArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"UpArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setUpArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"UpArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setUpArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"UpArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setUpArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setUpArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"UpArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"UpArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setUpArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"UpArrowColor1", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowColor1(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setUpArrowColor1(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowColor2", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowColor2(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setUpArrowColor2(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"UpArrowColor3", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getUpArrowColor3(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setUpArrowColor3(StringToState(state), value); }));

			Add(new CPropertyRectFState(this, control, L"DownArrowBorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setDownArrowBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"DownArrowOuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setDownArrowOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"DownArrowInnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setDownArrowInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"DownArrowOuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setDownArrowOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"DownArrowInnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CTimePicker*>(parent)->setDownArrowInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setDownArrowBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"DownArrowBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, control, L"DownArrowPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CTimePicker*>(parent)->setDownArrowPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"DownArrowColor1", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowColor1(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setDownArrowColor1(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowColor2", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowColor2(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setDownArrowColor2(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"DownArrowColor3", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getDownArrowColor3(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setDownArrowColor3(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"ArrowDistance", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getArrowDistance(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CTimePicker*>(parent)->setArrowDistance(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ElementBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getElementBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setElementBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ElementBackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getElementBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ElementColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getElementColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CTimePicker*>(parent)->setElementColor(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CTimePicker*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CTimePicker*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
		}

		StringArray CTimePickerPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::Disabled" };
		}

		CTimePicker::State CTimePickerPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CTimePicker::State::Hovered;
			if (state == L"State::Focused")
				return CTimePicker::State::Focused;
			if (state == L"State::FocusedHovered")
				return CTimePicker::State::FocusedHovered;
			if (state == L"State::Active")
				return CTimePicker::State::Active;
			if (state == L"State::ActiveHovered")
				return CTimePicker::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CTimePicker::State::Disabled;
			return CTimePicker::State::Normal;
		}
	}
}