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
		CListItemTreeViewLabelPropertyList::CListItemTreeViewLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemTreeViewLabel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemTreeViewLabel*>(parent)->setCaption(value); }));
			Add(new CPropertyInteger(this, listitem, L"IconIndex", false, nullptr,
				[](IClass *parent) {return cast<CListItemTreeViewLabel*>(parent)->getIconIndex(); },
				[](IClass *parent, const int value) {return cast<CListItemTreeViewLabel*>(parent)->setIconIndex(value); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemTreeViewLabel*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemTreeViewLabel*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemTreeViewLabel*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"IconPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getIconPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemTreeViewLabel*>(parent)->setIconPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemTreeViewLabel*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemTreeViewLabel*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemTreeViewLabel*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemTreeViewLabel*>(parent)->setColor(StringToState(state), value); }));
		}

		StringArray CListItemTreeViewLabelPropertyList::StateItems()
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

		CListItemTreeViewLabel::State CListItemTreeViewLabelPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CListItemTreeViewLabel::State::Hovered;
			if (state == L"State::Selected")
				return CListItemTreeViewLabel::State::Selected;
			if (state == L"State::SelectedHovered")
				return CListItemTreeViewLabel::State::SelectedHovered;
			if (state == L"State::Active")
				return CListItemTreeViewLabel::State::Active;
			if (state == L"State::ActiveHovered")
				return CListItemTreeViewLabel::State::ActiveHovered;
			if (state == L"State::ActiveSelected")
				return CListItemTreeViewLabel::State::ActiveSelected;
			if (state == L"State::ActiveSelectedHovered")
				return CListItemTreeViewLabel::State::ActiveSelectedHovered;
			if (state == L"State::Disabled")
				return CListItemTreeViewLabel::State::Disabled;
			return CListItemTreeViewLabel::State::Normal;
		}
	}
}