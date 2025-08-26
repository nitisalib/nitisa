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
		CSpeedButtonPropertyList::CSpeedButtonPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"WantTabs");

			Add(new CPropertyInteger(this, control, L"GroupIndex", false, nullptr,
				[](IClass *parent) {return cast<CSpeedButton*>(parent)->getGroupIndex(); },
				[](IClass *parent, const int value) {return cast<CSpeedButton*>(parent)->setGroupIndex(value); }))
				->setMin(-1);
			Add(new CPropertyBool(this, control, L"Down", false, nullptr,
				[](IClass *parent) {return cast<CSpeedButton*>(parent)->isDown(); },
				[](IClass *parent, const bool value) {return cast<CSpeedButton*>(parent)->setDown(value); }));
			Add(new CPropertyRectFState(this, control, L"Padding", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getPadding(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CSpeedButton*>(parent)->setPadding(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"OuterBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getOuterBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CSpeedButton*>(parent)->setOuterBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"InnerBorderWidth", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getInnerBorderWidth(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CSpeedButton*>(parent)->setInnerBorderWidth(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CSpeedButton*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"OuterBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getOuterBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CSpeedButton*>(parent)->setOuterBorderColor(StringToState(state), value); }));
			Add(new CPropertyBorderColorState(this, control, L"InnerBorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getInnerBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CSpeedButton*>(parent)->setInnerBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSpeedButton*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyComponentImageListState(this, control, L"ImageList", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getImageList(StringToState(state)); },
				[](IClass *parent, const String &state, IImageList *value) {return cast<CSpeedButton*>(parent)->setImageList(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"IconIndex", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getIconIndex(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CSpeedButton*>(parent)->setIconIndex(StringToState(state), value); }))
				->setMin(-1);
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSpeedButton*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CSpeedButton*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CSpeedButton*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CSpeedButton*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
		}

		StringArray CSpeedButtonPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Down",
				L"State::DownHovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::FocusedDown",
				L"State::FocusedDownHovered",
				L"State::Disabled" };
		}

		CSpeedButton::State CSpeedButtonPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CSpeedButton::State::Hovered;
			if (state == L"State::Down")
				return CSpeedButton::State::Down;
			if (state == L"State::DownHovered")
				return CSpeedButton::State::DownHovered;
			if (state == L"State::Focused")
				return CSpeedButton::State::Focused;
			if (state == L"State::FocusedHovered")
				return CSpeedButton::State::FocusedHovered;
			if (state == L"State::FocusedDown")
				return CSpeedButton::State::FocusedDown;
			if (state == L"State::FocusedDownHovered")
				return CSpeedButton::State::FocusedDownHovered;
			if (state == L"State::Disabled")
				return CSpeedButton::State::Disabled;
			return CSpeedButton::State::Normal;
		}
	}
}