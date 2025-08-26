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
		CScrollBarPropertyList::CScrollBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Size");

			Add(new CPropertyFloat(this, control, L"Min", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getMin(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setMin(value); }));
			Add(new CPropertyFloat(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getMax(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setMax(value); }));
			Add(new CPropertyFloat(this, control, L"Position", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getPosition(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setPosition(value); }));
			Add(new CPropertyBool(this, control, L"Vertical", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->isVertical(); },
				[](IClass *parent, const bool value) {return cast<CScrollBar*>(parent)->setVertical(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollerSize", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerSize(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollerSize(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaSmall", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getDeltaSmall(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setDeltaSmall(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaMedium", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getDeltaMedium(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setDeltaMedium(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaLarge", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getDeltaLarge(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setDeltaLarge(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getArrowSize(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setArrowSize(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CScrollBar*>(parent)->setShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CScrollBar*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyFloat(this, control, L"StartArrowBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getStartArrowBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setStartArrowBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"StartArrowBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getStartArrowBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setStartArrowBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"StartArrowBorderColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setStartArrowBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"StartArrowBackgroundColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setStartArrowBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyGradientState(this, control, L"StartArrowBackgroundGradient", ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowBackgroundGradient(StringToElementState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"StartArrowColor1", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowColor1(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setStartArrowColor1(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"StartArrowColor2", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowColor2(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setStartArrowColor2(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"StartArrowColor3", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getStartArrowColor3(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setStartArrowColor3(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyFloat(this, control, L"EndArrowBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getEndArrowBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setEndArrowBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"EndArrowBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getEndArrowBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setEndArrowBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"EndArrowBorderColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setEndArrowBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"EndArrowBackgroundColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setEndArrowBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyGradientState(this, control, L"EndArrowBackgroundGradient", ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowBackgroundGradient(StringToElementState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"EndArrowColor1", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowColor1(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setEndArrowColor1(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"EndArrowColor2", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowColor2(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setEndArrowColor2(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"EndArrowColor3", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getEndArrowColor3(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setEndArrowColor3(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyFloat(this, control, L"ScrollerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollerBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerBorderRadius(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollerBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ScrollerBorderColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getScrollerBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setScrollerBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"ScrollerBackgroundColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getScrollerBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setScrollerBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyGradientState(this, control, L"ScrollerBackgroundGradient", ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getScrollerBackgroundGradient(StringToElementState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"ScrollerLinesBorderColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getScrollerLinesBorderColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setScrollerLinesBorderColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyColorState(this, control, L"ScrollerLinesBackgroundColor", false, ElementStateItems(), ExportPrefixType::None, L"CBuiltInScroll::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBar*>(parent)->getScrollerLinesBackgroundColor(StringToElementState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBar*>(parent)->setScrollerLinesBackgroundColor(StringToElementState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Scroll/BuiltInScroll.h");
			Add(new CPropertyPointF(this, control, L"ScrollerLinesSize", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerLinesSize(); },
				[](IClass *parent, const PointF value) {return cast<CScrollBar*>(parent)->setScrollerLinesSize(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollerLinesDistance", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerLinesDistance(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollerLinesDistance(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollerLinesBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBar*>(parent)->getScrollerLinesBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBar*>(parent)->setScrollerLinesBorderWidth(value); }))
				->setMin(0);

			// Should be after "Vertical"
			Add(new CPropertyPointF(this, control, L"Size", false, nullptr,
				[](IClass *parent) { return cast<IControl*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) {return cast<IControl*>(parent)->setSize(value); }))
				->setMin(0);
		}

		StringArray CScrollBarPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CBuiltInScroll::State CScrollBarPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInScroll::State::Hovered;
			if (state == L"State::Active")
				return CBuiltInScroll::State::Active;
			if (state == L"State::Disabled")
				return CBuiltInScroll::State::Disabled;
			return CBuiltInScroll::State::Normal;
		}

		StringArray CScrollBarPropertyList::ElementStateItems()
		{
			return StringArray{
				L"ElementState::NormalNormal",
				L"ElementState::HoveredNormal",
				L"ElementState::HoveredHovered",
				L"ElementState::ActiveNormal",
				L"ElementState::ActiveActive",
				L"ElementState::DisabledDisabled" };
		}

		CBuiltInScroll::ElementState CScrollBarPropertyList::StringToElementState(const String &state)
		{
			if (state == L"ElementState::HoveredNormal")
				return CBuiltInScroll::ElementState::HoveredNormal;
			if (state == L"ElementState::HoveredHovered")
				return CBuiltInScroll::ElementState::HoveredHovered;
			if (state == L"ElementState::ActiveNormal")
				return CBuiltInScroll::ElementState::ActiveNormal;
			if (state == L"ElementState::ActiveActive")
				return CBuiltInScroll::ElementState::ActiveActive;
			if (state == L"ElementState::DisabledDisabled")
				return CBuiltInScroll::ElementState::DisabledDisabled;
			return CBuiltInScroll::ElementState::NormalNormal;
		}
	}
}