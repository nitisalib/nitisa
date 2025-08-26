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
		CMainMenuPropertyList::CMainMenuPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Transform");
			Delete(L"TransformControls");
			Delete(L"Align");
			Delete(L"Size");
			Delete(L"Constraints");
			Delete(L"WantTabs");
			Delete(L"Enabled");

			Add(new CPropertyEnum(this, control, L"Align", false, AlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) { return AlignToString(cast<CMainMenu*>(parent)->getAlign()); },
				[](IClass *parent, const String value) {return cast<CMainMenu*>(parent)->setAlign(StringToAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/Align.h");
			Add(new CPropertyPointF(this, control, L"Size", false, nullptr,
				[](IClass *parent) { return cast<CMainMenu*>(parent)->getSize(); },
				[](IClass *parent, const PointF value) {return cast<CMainMenu*>(parent)->setSize(value); }))
				->setMin(0);
			Add(new CPropertyTransform(this, control, L"Transform", false,
				[](IClass *parent) { return cast<CMainMenu*>(parent)->getAlign() != Align::None; },
				[](IClass *parent) { return cast<CMainMenu*>(parent)->getTransform()->getTransform(); },
				[](IClass *parent, const Transform value) {return cast<CMainMenu*>(parent)->getTransform()->setTransform(value); }));
			Add(new CPropertyComponentImageList(this, control, L"ImageListEnabled", nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getImageListEnabled(); },
				[](IClass *parent, IImageList *value) {return cast<CMainMenu*>(parent)->setImageListEnabled(value); }));
			Add(new CPropertyComponentImageList(this, control, L"ImageListDisabled", nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getImageListDisabled(); },
				[](IClass *parent, IImageList *value) {return cast<CMainMenu*>(parent)->setImageListDisabled(value); }));
			Add(new CPropertyRectF(this, control, L"SubmenuBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setSubmenuBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"SubmenuBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setSubmenuBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"SubmenuBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CMainMenu*>(parent)->setSubmenuBorderColor(value); }));
			Add(new CPropertyRectF(this, control, L"SubmenuPadding", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setSubmenuPadding(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"SubmenuBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setSubmenuBackgroundColor(value); }));
			Add(new CPropertyColor(this, control, L"SubmenuShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setSubmenuShadowColor(value); }));
			Add(new CPropertyInteger(this, control, L"SubmenuShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CMainMenu*>(parent)->setSubmenuShadowRadius(value); }))
				->setMin(1);
			Add(new CPropertyPointF(this, control, L"SubmenuShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CMainMenu*>(parent)->setSubmenuShadowShift(value); }));
			Add(new CPropertyPointF(this, control, L"SubmenuShift", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuShift(); },
				[](IClass *parent, const PointF value) {return cast<CMainMenu*>(parent)->setSubmenuShift(value); }));
			Add(new CPropertyFloat(this, control, L"HotkeyMaxInterval", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getHotkeyMaxInterval(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setHotkeyMaxInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"SubmenuScrollHeight", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuScrollHeight(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setSubmenuScrollHeight(value); }))
				->setMin(1);
			Add(new CPropertyColor(this, control, L"SubmenuScrollArrowColorNormal", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuScrollArrowColorNormal(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setSubmenuScrollArrowColorNormal(value); }));
			Add(new CPropertyColor(this, control, L"SubmenuScrollArrowColorHovered", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuScrollArrowColorHovered(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setSubmenuScrollArrowColorHovered(value); }));
			Add(new CPropertyColor(this, control, L"SubmenuScrollArrowColorDisabled", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuScrollArrowColorDisabled(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setSubmenuScrollArrowColorDisabled(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"SubmenuDeltaScrollTimer", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuDeltaScrollTimer(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setSubmenuDeltaScrollTimer(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"SubmenuDeltaScrollWheel", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuDeltaScrollWheel(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setSubmenuDeltaScrollWheel(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"SubmenuMaxHeight", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuMaxHeight(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setSubmenuMaxHeight(value); }))
				->setMin(0);
			Add(new CPropertyGradient(this, control, L"SubmenuBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getSubmenuBackgroundGradient(); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CMainMenu*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"ScrollWidth", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getScrollWidth(); },
				[](IClass *parent, const float value) {return cast<CMainMenu*>(parent)->setScrollWidth(value); }))
				->setMin(1);
			Add(new CPropertyColor(this, control, L"ScrollArrowColorNormal", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getScrollArrowColorNormal(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setScrollArrowColorNormal(value); }));
			Add(new CPropertyColor(this, control, L"ScrollArrowColorHovered", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getScrollArrowColorHovered(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setScrollArrowColorHovered(value); }));
			Add(new CPropertyColor(this, control, L"ScrollArrowColorDisabled", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getScrollArrowColorDisabled(); },
				[](IClass *parent, const Color value) {return cast<CMainMenu*>(parent)->setScrollArrowColorDisabled(value); }));
			Add(new CPropertyPointF(this, control, L"RootSubmenuShift", false, nullptr,
				[](IClass *parent) {return cast<CMainMenu*>(parent)->getRootSubmenuShift(); },
				[](IClass *parent, const PointF value) {return cast<CMainMenu*>(parent)->setRootSubmenuShift(value); }));
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CMainMenu*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMainMenu*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CMainMenu*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CMainMenu*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CMainMenu*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CMainMenu*>(parent)->getBackgroundGradient(StringToState(state)); }));
		}

		StringArray CMainMenuPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Active" };
		}

		CMainMenu::State CMainMenuPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Active")
				return CMainMenu::State::Active;
			return CMainMenu::State::Normal;
		}

		StringArray CMainMenuPropertyList::AlignItems()
		{
			return StringArray{
				L"Align::None",
				L"Align::Top" };
		}

		Align CMainMenuPropertyList::StringToAlign(const String &align)
		{
			if (align == L"Align::Top")
				return Align::Top;
			return Align::None;
		}

		String CMainMenuPropertyList::AlignToString(const Align align)
		{
			switch (align)
			{
			case Align::Top:	return L"Align::Top";
			default:			return L"Align::None";
			}
		}
	}
}