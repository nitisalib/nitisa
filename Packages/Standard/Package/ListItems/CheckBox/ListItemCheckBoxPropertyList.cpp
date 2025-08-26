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
		CListItemCheckBoxPropertyList::CListItemCheckBoxPropertyList(IPackage *package, IListItem *listitem, IPackageEntity *entity) :
			CListItemPropertyList(package, listitem, entity)
		{
			Add(new CPropertyString(this, listitem, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CListItemCheckBox*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CListItemCheckBox*>(parent)->setCaption(value); }));
			Add(new CPropertyBool(this, listitem, L"Checked", false, nullptr,
				[](IClass *parent) {return cast<CListItemCheckBox*>(parent)->isChecked(); },
				[](IClass *parent, const bool value) {return cast<CListItemCheckBox*>(parent)->setChecked(value); }));
			Add(new CPropertyEnum(this, listitem, L"Align", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CListItemCheckBox*>(parent)->getAlign()); },
				[](IClass *parent, const String value) {return cast<CListItemCheckBox*>(parent)->setAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyRectF(this, listitem, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CListItemCheckBox*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CListItemCheckBox*>(parent)->setPadding(value); }))->
				setMin(0);
			Add(new CPropertyBool(this, listitem, L"TextAtRight", false, nullptr,
				[](IClass *parent) {return cast<CListItemCheckBox*>(parent)->isTextAtRight(); },
				[](IClass *parent, const bool value) {return cast<CListItemCheckBox*>(parent)->setTextAtRight(value); }));
			Add(new CPropertyColorState(this, listitem, L"Color", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemCheckBox*>(parent)->setColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"ShadowColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemCheckBox*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, listitem, L"ShadowRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CListItemCheckBox*>(parent)->setShadowRadius(StringToState(state), value); }))->
				setMin(1);
			Add(new CPropertyPointFState(this, listitem, L"ShadowShift", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CListItemCheckBox*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, listitem, L"BackgroundColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CListItemCheckBox*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, listitem, L"BackgroundGradient", StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyRectFState(this, listitem, L"BorderWidth", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemCheckBox*>(parent)->setBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, listitem, L"BorderRadius", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemCheckBox*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, listitem, L"BorderColor", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CListItemCheckBox*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, listitem, L"ImagePadding", false, StateItems(), ExportPrefixType::Namespace, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CListItemCheckBox*>(parent)->getImagePadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CListItemCheckBox*>(parent)->setImagePadding(StringToState(state), value); }))
				->setMin(0);
		}

		StringArray CListItemCheckBoxPropertyList::StateItems()
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

		CListItemCheckBox::State CListItemCheckBoxPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CListItemCheckBox::State::Hovered;
			if (state == L"State::Selected")
				return CListItemCheckBox::State::Selected;
			if (state == L"State::SelectedHovered")
				return CListItemCheckBox::State::SelectedHovered;
			if (state == L"State::Active")
				return CListItemCheckBox::State::Active;
			if (state == L"State::ActiveHovered")
				return CListItemCheckBox::State::ActiveHovered;
			if (state == L"State::ActiveSelected")
				return CListItemCheckBox::State::ActiveSelected;
			if (state == L"State::ActiveSelectedHovered")
				return CListItemCheckBox::State::ActiveSelectedHovered;
			if (state == L"State::Disabled")
				return CListItemCheckBox::State::Disabled;
			return CListItemCheckBox::State::Normal;
		}
	}
}