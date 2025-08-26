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
		CListItemIconPropertyList::CListItemIconPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemIcon*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemIcon*>(parent)->setCaption(value); }));
			Add(new CPropertyFloat(this, listitem, L"IconPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemIcon*>(parent)->getIconPadding(); },
				[](IClass *parent, const float value) {return cast<CListItemIcon*>(parent)->setIconPadding(value); }))->
				setMin(0);
			Add(new CPropertyRectF(this, listitem, L"CaptionPadding", false, nullptr,
				[](IClass *parent) {return cast<CListItemIcon*>(parent)->getCaptionPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemIcon*>(parent)->setCaptionPadding(value); }))->
				setMin(0);
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemIcon*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemIcon*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemIcon*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemIcon*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemIcon*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemIcon*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemIcon*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemIcon*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemIcon*>(parent)->getBackgroundGradient(StringToState(state)); }));
		}

		StringArray CListItemIconPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Selected",
				L"State::SelectedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::ActiveSelected",
				L"State::ActiveSelectedHovered",
				L"State::Disabled" };
		}

		CListItemIcon::State CListItemIconPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CListItemIcon::State::Hovered;
			if (state == L"State::Selected")
				return CListItemIcon::State::Selected;
			if (state == L"State::SelectedHovered")
				return CListItemIcon::State::SelectedHovered;
			if (state == L"State::Active")
				return CListItemIcon::State::Active;
			if (state == L"State::ActiveHovered")
				return CListItemIcon::State::ActiveHovered;
			if (state == L"State::ActiveSelected")
				return CListItemIcon::State::ActiveSelected;
			if (state == L"State::ActiveSelectedHovered")
				return CListItemIcon::State::ActiveSelectedHovered;
			if (state == L"State::Disabled")
				return CListItemIcon::State::Disabled;
			return CListItemIcon::State::Normal;
		}
	}
}