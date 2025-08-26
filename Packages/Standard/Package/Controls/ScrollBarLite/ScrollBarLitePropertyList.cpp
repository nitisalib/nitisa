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
		CScrollBarLitePropertyList::CScrollBarLitePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
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
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getMin(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setMin(value); }));
			Add(new CPropertyFloat(this, control, L"Max", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getMax(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setMax(value); }));
			Add(new CPropertyFloat(this, control, L"Position", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getPosition(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setPosition(value); }));
			Add(new CPropertyBool(this, control, L"Vertical", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->isVertical(); },
				[](IClass *parent, const bool value) {return cast<CScrollBarLite*>(parent)->setVertical(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollerSize", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getScrollerSize(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setScrollerSize(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaMedium", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getDeltaMedium(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setDeltaMedium(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DeltaLarge", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getDeltaLarge(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setDeltaLarge(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CScrollBarLite*>(parent)->setShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBarLite*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CScrollBarLite*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyBool(this, control, L"BorderRound", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->isBorderRound(); },
				[](IClass *parent, const bool value) {return cast<CScrollBarLite*>(parent)->setBorderRound(value); }));
			Add(new CPropertyFloat(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBarLite*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBarLite*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyBool(this, control, L"ScrollerRound", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->isScrollerRound(); },
				[](IClass *parent, const bool value) {return cast<CScrollBarLite*>(parent)->setScrollerRound(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollerBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CScrollBarLite*>(parent)->getScrollerBorderWidth(); },
				[](IClass *parent, const float value) {return cast<CScrollBarLite*>(parent)->setScrollerBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ScrollerBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getScrollerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBarLite*>(parent)->setScrollerBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyColorState(this, control, L"ScrollerBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getScrollerBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CScrollBarLite*>(parent)->setScrollerBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");
			Add(new CPropertyGradientState(this, control, L"ScrollerBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInScrollLite::", nullptr,
				[](IClass *parent, const String &state) {return cast<CScrollBarLite*>(parent)->getScrollerBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/ScrollLite/BuiltInScrollLite.h");

			// Should be after "Vertical"
			Add(new CPropertyPointF(this, control, L"Size", false, nullptr,
				[](IClass *parent) { return cast<IControl*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) {return cast<IControl*>(parent)->setSize(value); }))
				->setMin(0);
		}

		StringArray CScrollBarLitePropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Active",
				L"State::Disabled" };
		}

		CBuiltInScrollLite::State CScrollBarLitePropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInScrollLite::State::Hovered;
			if (state == L"State::Active")
				return CBuiltInScrollLite::State::Active;
			if (state == L"State::Disabled")
				return CBuiltInScrollLite::State::Disabled;
			return CBuiltInScrollLite::State::Normal;
		}
	}
}