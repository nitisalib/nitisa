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
		CTogglePropertyList::CTogglePropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.Distance");
			Delete(L"Font.Monospace");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");
			Delete(L"UseParentFont");

			Add(new CPropertyBool(this, control, L"On", false, nullptr,
				[](IClass *parent) {return cast<CToggle*>(parent)->isOn(); },
				[](IClass *parent, const bool value) {return cast<CToggle*>(parent)->setOn(value); }));
			Add(new CPropertyFloatState(this, control, L"BackgroundBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getBackgroundBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CToggle*>(parent)->setBackgroundBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BackgroundBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getBackgroundBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToggle*>(parent)->setBackgroundBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToggle*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CToggle*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToggle*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToggle*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToggle*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CToggle*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToggle*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CToggle*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
		}

		StringArray CTogglePropertyList::StateItems()
		{
			return StringArray{
				L"State::On",
				L"State::Off",
				L"State::Disabled" };
		}

		CToggle::State CTogglePropertyList::StringToState(const String &state)
		{
			if (state == L"State::On")
				return CToggle::State::On;
			if (state == L"State::Off")
				return CToggle::State::Off;
			return CToggle::State::Disabled;
		}
	}
}