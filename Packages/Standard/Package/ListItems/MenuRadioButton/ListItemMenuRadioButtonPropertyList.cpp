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
		CListItemMenuRadioButtonPropertyList::CListItemMenuRadioButtonPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemMenuPropertyList(package, listitem, entity)
		{
			Delete(L"Selected");

			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemMenuRadioButton*>(parent)->setCaption(value); }));
			Add(new CPropertyBool(this, listitem, L"Checked", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->isChecked(); },
				[](IClass *parent, const bool value) {return cast<CListItemMenuRadioButton*>(parent)->setChecked(value); }));
			Add(new CPropertyInteger(this, listitem, L"GroupIndex", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->getGroupIndex(); },
				[](IClass *parent, const int value) {return cast<CListItemMenuRadioButton*>(parent)->setGroupIndex(value); }))
				->setMin(-1);
			Add(new CPropertyRectF(this, listitem, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->getIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuRadioButton*>(parent)->setIconPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuRadioButton*>(parent)->setCaptionPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"HotkeyPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuRadioButton*>(parent)->getHotkeyPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuRadioButton*>(parent)->setHotkeyPadding(value); }))->
				setMin(0);
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuRadioButton*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuRadioButton*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemMenuRadioButton*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemMenuRadioButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuRadioButton*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuRadioButton*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuRadioButton*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemMenuRadioButton*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, listitem, L"IconBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuRadioButton*>(parent)->getIconBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuRadioButton*>(parent)->setIconBackgroundColor(StringToState(state), value); }));
		}

		StringArray CListItemMenuRadioButtonPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active",
				L"State::Disabled" };
		}

		CListItemMenuRadioButton::State CListItemMenuRadioButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CListItemMenuRadioButton::State::Active;
			if (state == L"State::Disabled")
				return CListItemMenuRadioButton::State::Disabled;
			return CListItemMenuRadioButton::State::Normal;
		}
	}
}