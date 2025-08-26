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
		CListItemMenuCheckBoxPropertyList::CListItemMenuCheckBoxPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemMenuPropertyList(package, listitem, entity)
		{
			Delete(L"Selected");

			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuCheckBox*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemMenuCheckBox*>(parent)->setCaption(value); }));
			Add(new CPropertyBool(this, listitem, L"Checked", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuCheckBox*>(parent)->isChecked(); },
				[](IClass *parent, const bool value) {return cast<CListItemMenuCheckBox*>(parent)->setChecked(value); }));
			Add(new CPropertyRectF(this, listitem, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuCheckBox*>(parent)->getIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuCheckBox*>(parent)->setIconPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuCheckBox*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuCheckBox*>(parent)->setCaptionPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"HotkeyPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuCheckBox*>(parent)->getHotkeyPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuCheckBox*>(parent)->setHotkeyPadding(value); }))->
				setMin(0);
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuCheckBox*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuCheckBox*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemMenuCheckBox*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemMenuCheckBox*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuCheckBox*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuCheckBox*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuCheckBox*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemMenuCheckBox*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, listitem, L"IconBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuCheckBox*>(parent)->getIconBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuCheckBox*>(parent)->setIconBackgroundColor(StringToState(state), value); }));
		}

		StringArray CListItemMenuCheckBoxPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active",
				L"State::Disabled" };
		}

		CListItemMenuCheckBox::State CListItemMenuCheckBoxPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CListItemMenuCheckBox::State::Active;
			if (state == L"State::Disabled")
				return CListItemMenuCheckBox::State::Disabled;
			return CListItemMenuCheckBox::State::Normal;
		}
	}
}