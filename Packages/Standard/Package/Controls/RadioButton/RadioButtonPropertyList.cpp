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
		CRadioButtonPropertyList::CRadioButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Size");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyPointF(this, control, L"Size", false,
				[](IClass *parent) { return cast<CRadioButton*>(parent)->isAutoSize(); },
				[](IClass *parent) { return cast<CRadioButton*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) { return cast<CRadioButton*>(parent)->setSize(value); }))
				->setMin(0);
			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CRadioButton*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyInteger(this, control, L"GroupIndex", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->getGroupIndex(); },
				[](IClass *parent, const int value) {return cast<CRadioButton*>(parent)->setGroupIndex(value); }));
			Add(new CPropertyBool(this, control, L"Checked", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->isChecked(); },
				[](IClass *parent, const bool value) {return cast<CRadioButton*>(parent)->setChecked(value); }));
			Add(new CPropertyEnum(this, control, L"ContentHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None,  L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CRadioButton*>(parent)->getContentHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CRadioButton*>(parent)->setContentHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"ContentVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CRadioButton*>(parent)->getContentVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CRadioButton*>(parent)->setContentVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyBool(this, control, L"IconOnRight", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->isIconOnRight(); },
				[](IClass *parent, const bool value) {return cast<CRadioButton*>(parent)->setIconOnRight(value); }));
			Add(new CPropertyBool(this, control, L"AutoSize", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->isAutoSize(); },
				[](IClass *parent, const bool value) {return cast<CRadioButton*>(parent)->setAutoSize(value); }));
			Add(new CPropertyFloat(this, control, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CRadioButton*>(parent)->getIconPadding(); },
				[](IClass *parent, const float value) {return cast<CRadioButton*>(parent)->setIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CRadioButton*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CRadioButton*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CRadioButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CRadioButton*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CRadioButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CRadioButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CRadioButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CRadioButton*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
		}

		StringArray CRadioButtonPropertyList::StateItems()
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

		CRadioButton::State CRadioButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CRadioButton::State::Hovered;
			if (state == L"State::Focused")
				return CRadioButton::State::Focused;
			if (state == L"State::FocusedHovered")
				return CRadioButton::State::FocusedHovered;
			if (state == L"State::Active")
				return CRadioButton::State::Active;
			if (state == L"State::ActiveHovered")
				return CRadioButton::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CRadioButton::State::Disabled;
			return CRadioButton::State::Normal;
		}
	}
}