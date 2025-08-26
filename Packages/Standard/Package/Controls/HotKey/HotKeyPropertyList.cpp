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
		CHotKeyPropertyList::CHotKeyPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyHotkey(this, control, L"Hotkey", false, nullptr,
				[](IClass *parent) {return cast<CHotKey*>(parent)->getHotKey(); },
				[](IClass *parent, const Hotkey value) {return cast<CHotKey*>(parent)->setHotKey(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CHotKey*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CHotKey*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CHotKey*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CHotKey*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CHotKey*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CHotKey*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CHotKey*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CHotKey*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CHotKey*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CHotKey*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CHotKey*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"TextColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getTextColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CHotKey*>(parent)->setTextColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"TextShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getTextShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CHotKey*>(parent)->setTextShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"TextShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getTextShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CHotKey*>(parent)->setTextShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"TextShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CHotKey*>(parent)->getTextShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CHotKey*>(parent)->setTextShadowRadius(StringToState(state), value); }))
				->setMin(1);
		}

		StringArray CHotKeyPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CHotKey::State CHotKeyPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CHotKey::State::Hovered;
			if (state == L"State::Focused")
				return CHotKey::State::Focused;
			if (state == L"State::FocusedHovered")
				return CHotKey::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CHotKey::State::Disabled;
			return CHotKey::State::Normal;
		}
	}
}