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
		CListItemLabelPropertyList::CListItemLabelPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemLabel*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemLabel*>(parent)->setCaption(value); }));
			Add(new CPropertyEnum(this, listitem, L"Align", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CListItemLabel*>(parent)->getAlign()); },
				[](IClass *parent, const String value) {return cast<CListItemLabel*>(parent)->setAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyRectF(this, listitem, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CListItemLabel*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemLabel*>(parent)->setPadding(value); }))->
				setMin(0);
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemLabel*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemLabel*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemLabel*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemLabel*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemLabel*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemLabel*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemLabel*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemLabel*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemLabel*>(parent)->setBorderColor(StringToState(state), value); }));
		}

		StringArray CListItemLabelPropertyList::StateItems()
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

		CListItemLabel::State CListItemLabelPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CListItemLabel::State::Hovered;
			if (state == L"State::Selected")
				return CListItemLabel::State::Selected;
			if (state == L"State::SelectedHovered")
				return CListItemLabel::State::SelectedHovered;
			if (state == L"State::Active")
				return CListItemLabel::State::Active;
			if (state == L"State::ActiveHovered")
				return CListItemLabel::State::ActiveHovered;
			if (state == L"State::ActiveSelected")
				return CListItemLabel::State::ActiveSelected;
			if (state == L"State::ActiveSelectedHovered")
				return CListItemLabel::State::ActiveSelectedHovered;
			if (state == L"State::Disabled")
				return CListItemLabel::State::Disabled;
			return CListItemLabel::State::Normal;
		}
	}
}