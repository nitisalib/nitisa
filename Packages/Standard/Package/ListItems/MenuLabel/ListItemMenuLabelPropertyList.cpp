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
		CListItemMenuLabelPropertyList::CListItemMenuLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemMenuPropertyList(package, listitem, entity)
		{
			Delete(L"Selected");

			Add(new CPropertyRectF(this, listitem, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuLabel*>(parent)->getIconPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuLabel*>(parent)->setIconPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuLabel*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuLabel*>(parent)->setCaptionPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"HotkeyPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuLabel*>(parent)->getHotkeyPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemMenuLabel*>(parent)->setHotkeyPadding(value); }))->
				setMin(0);
			Add(new CPropertyPointF(this, listitem, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuLabel*>(parent)->getArrowSize(); },
				[](IClass *parent, const PointF value) {return cast<CListItemMenuLabel*>(parent)->setArrowSize(value); }))->
				setMin(0);
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemMenuLabel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemMenuLabel*>(parent)->setCaption(value); }));
			Add(new CPropertyIntegerState(this, listitem, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemMenuLabel*>(parent)->setIconIndex(StringToState(state), value); }))->
				setMin(-1);
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuLabel*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuLabel*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemMenuLabel*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemMenuLabel*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuLabel*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuLabel*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemMenuLabel*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemMenuLabel*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, listitem, L"ArrowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuLabel*>(parent)->setArrowColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"IconBackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemMenuLabel*>(parent)->getIconBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemMenuLabel*>(parent)->setIconBackgroundColor(StringToState(state), value); }));
		}

		StringArray CListItemMenuLabelPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active",
				L"State::Disabled" };
		}

		CListItemMenuLabel::State CListItemMenuLabelPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CListItemMenuLabel::State::Active;
			if (state == L"State::Disabled")
				return CListItemMenuLabel::State::Disabled;
			return CListItemMenuLabel::State::Normal;
		}
	}
}