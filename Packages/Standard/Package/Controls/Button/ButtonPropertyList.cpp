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
		CButtonPropertyList::CButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Caption", false, nullptr,
				[](IClass *parent) {return cast<CButton*>(parent)->getCaption(); },
				[](IClass *parent, const String value) {return cast<CButton*>(parent)->setCaption(value); }))
				->setChanged(true);
			Add(new CPropertyBool(this, control, L"Down", false, nullptr,
				[](IClass *parent) {return cast<CButton*>(parent)->isDown(); },
				[](IClass *parent, const bool value) {return cast<CButton*>(parent)->setDown(value); }));
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CButton*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CButton*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CButton*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CButton*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CButton*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CButton*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CButton*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CButton*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CButton*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyEnumState(this, control, L"ContentHorizontalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return TextAlignToString(cast<CButton*>(parent)->getContentHorizontalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CButton*>(parent)->setContentHorizontalAlign(StringToState(state), StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnumState(this, control, L"ContentVerticalAlign", false, StateItems(), ExportPrefixType::NamespaceParent, L"", VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent, const String &state) {return VerticalAlignToString(cast<CButton*>(parent)->getContentVerticalAlign(StringToState(state))); },
				[](IClass *parent, const String &state, const String value) {return cast<CButton*>(parent)->setContentVerticalAlign(StringToState(state), StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyColorState(this, control, L"CaptionColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getCaptionColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CButton*>(parent)->setCaptionColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CaptionShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getCaptionShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CButton*>(parent)->setCaptionShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"CaptionShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getCaptionShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CButton*>(parent)->setCaptionShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"CaptionShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getCaptionShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CButton*>(parent)->setCaptionShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyComponentImageListState(this, control, L"ImageList", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getImageList(StringToState(state)); },
				[](IClass *parent, const String &state, IImageList *value) {return cast<CButton*>(parent)->setImageList(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CButton*>(parent)->setIconIndex(StringToState(state), value); }));
			Add(new CPropertyFloatState(this, control, L"IconPadding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->getIconPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const float value) {return cast<CButton*>(parent)->setIconPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBoolState(this, control, L"IconOnRight", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CButton*>(parent)->isIconOnRight(StringToState(state)); },
				[](IClass *parent, const String &state, const bool value) {return cast<CButton*>(parent)->setIconOnRight(StringToState(state), value); }));
		}

		StringArray CButtonPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Active",
				L"State::ActiveHovered",
				L"State::Down",
				L"State::DownHovered",
				L"State::DownFocused",
				L"State::DownFocusedHovered",
				L"State::DownActive",
				L"State::DownActiveHovered",
				L"State::Disabled" };
		}

		CButton::State CButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CButton::State::Hovered;
			if (state == L"State::Focused")
				return CButton::State::Focused;
			if (state == L"State::FocusedHovered")
				return CButton::State::FocusedHovered;
			if (state == L"State::Active")
				return CButton::State::Active;
			if (state == L"State::ActiveHovered")
				return CButton::State::ActiveHovered;
			if (state == L"State::Down")
				return CButton::State::Down;
			if (state == L"State::DownHovered")
				return CButton::State::DownHovered;
			if (state == L"State::DownFocused")
				return CButton::State::DownFocused;
			if (state == L"State::DownFocusedHovered")
				return CButton::State::DownFocusedHovered;
			if (state == L"State::DownActive")
				return CButton::State::DownActive;
			if (state == L"State::DownActiveHovered")
				return CButton::State::DownActiveHovered;
			if (state == L"State::Disabled")
				return CButton::State::Disabled;
			return CButton::State::Normal;
		}
	}
}