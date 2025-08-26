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
		CCheckBoxPropertyList::CCheckBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Size");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyPointF(this, control, L"Size", false,
				[](IClass *parent) { return cast<CCheckBox*>(parent)->isAutoSize(); },
				[](IClass *parent) { return cast<CCheckBox*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) { return cast<CCheckBox*>(parent)->setSize(value); }))
				->setMin(0);
			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CCheckBox*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CCheckBox*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyEnum(this, control, L"Checked", false, CheckedItems(), ExportPrefixType::Namespace, L"ICheckBox::", nullptr,
				[](IClass *parent) {return CheckedToString(cast<CCheckBox*>(parent)->getChecked()); },
				[](IClass *parent, const String value) {return cast<CCheckBox*>(parent)->setChecked(StringToChecked(value)); }))
				->AddHeaderFile(L"Standard/Controls/ICheckBox.h");
			Add(new CPropertyEnum(this, control, L"ContentHorizontalAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CCheckBox*>(parent)->getContentHorizontalAlign()); },
				[](IClass *parent, const String value) {return cast<CCheckBox*>(parent)->setContentHorizontalAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"ContentVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CCheckBox*>(parent)->getContentVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CCheckBox*>(parent)->setContentVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyBool(this, control, L"IconOnRight", false, nullptr,
				[](IClass *parent) {return cast<CCheckBox*>(parent)->isIconOnRight(); },
				[](IClass *parent, const bool value) {return cast<CCheckBox*>(parent)->setIconOnRight(value); }));
			Add(new CPropertyBool(this, control, L"AutoSize", false, nullptr,
				[](IClass *parent) {return cast<CCheckBox*>(parent)->isAutoSize(); },
				[](IClass *parent, const bool value) {return cast<CCheckBox*>(parent)->setAutoSize(value); }));
			Add(new CPropertyFloat(this, control, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CCheckBox*>(parent)->getIconPadding(); },
				[](IClass *parent, const float value) {return cast<CCheckBox*>(parent)->setIconPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCheckBox*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCheckBox*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCheckBox*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCheckBox*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCheckBox*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCheckBox*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCheckBox*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCheckBox*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
		}

		StringArray CCheckBoxPropertyList::StateItems()
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

		CCheckBox::State CCheckBoxPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CCheckBox::State::Hovered;
			if (state == L"State::Focused")
				return CCheckBox::State::Focused;
			if (state == L"State::FocusedHovered")
				return CCheckBox::State::FocusedHovered;
			if (state == L"State::Active")
				return CCheckBox::State::Active;
			if (state == L"State::ActiveHovered")
				return CCheckBox::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CCheckBox::State::Disabled;
			return CCheckBox::State::Normal;
		}

		String CCheckBoxPropertyList::CheckedToString(const ICheckBox::CheckedState value)
		{
			switch (value)
			{
			case ICheckBox::CheckedState::Grayed:	return L"CheckedState::Grayed";
			case ICheckBox::CheckedState::Checked:	return L"CheckedState::Checked";
			default:								return L"CheckedState::Unchecked";
			}
		}

		ICheckBox::CheckedState CCheckBoxPropertyList::StringToChecked(const String &value)
		{
			if (value == L"CheckedState::Grayed")
				return ICheckBox::CheckedState::Grayed;
			if (value == L"CheckedState::Checked")
				return ICheckBox::CheckedState::Checked;
			return ICheckBox::CheckedState::Unchecked;
		}

		StringArray CCheckBoxPropertyList::CheckedItems()
		{
			return StringArray{
				L"CheckedState::Unchecked",
				L"CheckedState::Grayed",
				L"CheckedState::Checked" };
		}
	}
}