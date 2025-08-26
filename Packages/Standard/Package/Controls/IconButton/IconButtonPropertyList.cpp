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
		CIconButtonPropertyList::CIconButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font");
			Delete(L"Font.Distance");
			Delete(L"Font.Monospace");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CIconButton*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CIconButton*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CIconButton*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CIconButton*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CIconButton*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CIconButton*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CIconButton*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CIconButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CIconButton*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CIconButton*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyComponentImageListState(this, control, L"ImageList", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getImageList(StringToState(state)); },
				[](IClass *parent, const String &state, IImageList *value) {return cast<CIconButton*>(parent)->setImageList(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CIconButton*>(parent)->setIconIndex(StringToState(state), value); }));
			Add(new CPropertyMaskState(this, control, L"OutlineMask", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getOutlineMask(StringToState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CIconButton*>(parent)->setOutlineMask(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"OutlineColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CIconButton*>(parent)->getOutlineColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CIconButton*>(parent)->setOutlineColor(StringToState(state), value); }));
			Add(new CPropertyEnum(this, control, L"IconSize", false, IconSizeItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent) { return IconSizeToString(cast<CIconButton*>(parent)->getIconSize()); },
				[](IClass *parent, const String value) { return cast<CIconButton*>(parent)->setIconSize(StringToIconSize(value)); }));
		}

		StringArray CIconButtonPropertyList::StateItems()
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

		CIconButton::State CIconButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CIconButton::State::Hovered;
			if (state == L"State::Focused")
				return CIconButton::State::Focused;
			if (state == L"State::FocusedHovered")
				return CIconButton::State::FocusedHovered;
			if (state == L"State::Active")
				return CIconButton::State::Active;
			if (state == L"State::ActiveHovered")
				return CIconButton::State::ActiveHovered;
			if (state == L"State::Disabled")
				return CIconButton::State::Disabled;
			return CIconButton::State::Normal;
		}

		StringArray CIconButtonPropertyList::IconSizeItems()
		{
			return StringArray{
				L"IconSize::Original",
				L"IconSize::Contain",
				L"IconSize::Cover",
				L"IconSize::Stretch" };
		}

		CIconButton::IconSize CIconButtonPropertyList::StringToIconSize(const String &state)
		{
			if (state == L"IconSize::Contain")
				return CIconButton::IconSize::Contain;
			if (state == L"IconSize::Cover")
				return CIconButton::IconSize::Cover;
			if (state == L"IconSize::Stretch")
				return CIconButton::IconSize::Stretch;
			return CIconButton::IconSize::Original;
		}

		String CIconButtonPropertyList::IconSizeToString(const CIconButton::IconSize value)
		{
			switch (value)
			{
			case CIconButton::IconSize::Contain:	return L"IconSize::Contain";
			case CIconButton::IconSize::Cover:		return L"IconSize::Cover";
			case CIconButton::IconSize::Stretch:	return L"IconSize::Stretch";
			default:								return L"IconSize::Original";
			}
		}
	}
}