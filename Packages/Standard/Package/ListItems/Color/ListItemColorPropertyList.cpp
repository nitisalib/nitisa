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
		CListItemColorPropertyList::CListItemColorPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemColor*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemColor*>(parent)->setCaption(value); }));
			Add(new CPropertyColor(this, listitem, L"Color", false, nullptr,
				[](IClass *parent) {return cast<CListItemColor*>(parent)->getColor(); },
				[](IClass *parent, const Color value) {return cast<CListItemColor*>(parent)->setColor(value); }));
			Add(new CPropertyEnum(this, listitem, L"Align", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CListItemColor*>(parent)->getAlign()); },
				[](IClass *parent, const String value) {return cast<CListItemColor*>(parent)->setAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyRectF(this, listitem, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CListItemColor*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemColor*>(parent)->setPadding(value); }))->
				setMin(0);
			Add(new CPropertyBool(this, listitem, L"TextAtRight", false, nullptr,
				[](IClass *parent) {return cast<CListItemColor*>(parent)->isTextAtRight(); },
				[](IClass *parent, const bool value) {return cast<CListItemColor*>(parent)->setTextAtRight(value); }));
			Add(new CPropertyColorState(this, listitem, L"CaptionColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemColor*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"CaptionShadowColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getCaptionShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemColor*>(parent)->setCaptionShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"CaptionShadowRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getCaptionShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemColor*>(parent)->setCaptionShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"CaptionShadowShift", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getCaptionShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemColor*>(parent)->setCaptionShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemColor*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemColor*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemColor*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemColor*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"ColorBorderWidth", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getColorBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemColor*>(parent)->setColorBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"ColorBorderRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getColorBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemColor*>(parent)->setColorBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"ColorPadding", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getColorPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemColor*>(parent)->setColorPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"ColorBorderColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemColor*>(parent)->getColorBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemColor*>(parent)->setColorBorderColor(StringToState(state), value); }));
		}

		StringArray CListItemColorPropertyList::StateItems()
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

		CListItemColor::State CListItemColorPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CListItemColor::State::Hovered;
			if (state == L"State::Selected")
				return CListItemColor::State::Selected;
			if (state == L"State::SelectedHovered")
				return CListItemColor::State::SelectedHovered;
			if (state == L"State::Active")
				return CListItemColor::State::Active;
			if (state == L"State::ActiveHovered")
				return CListItemColor::State::ActiveHovered;
			if (state == L"State::ActiveSelected")
				return CListItemColor::State::ActiveSelected;
			if (state == L"State::ActiveSelectedHovered")
				return CListItemColor::State::ActiveSelectedHovered;
			if (state == L"State::Disabled")
				return CListItemColor::State::Disabled;
			return CListItemColor::State::Normal;
		}
	}
}