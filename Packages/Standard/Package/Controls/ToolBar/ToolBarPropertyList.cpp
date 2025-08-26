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
		CToolBarPropertyList::CToolBarPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"Font");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");
			Delete(L"Font.Monospace");
			Delete(L"Font.Distance");
			Delete(L"TransformControls");
			Delete(L"TabOrder");
			Delete(L"WantTabs");
			Delete(L"TabStop");
			Delete(L"DeactivateByTab");

			Add(new CPropertyEnum(this, control, L"AlignTo", false, AlignToItems(), ExportPrefixType::Namespace, L"IToolBar::", nullptr,
				[](IClass *parent) { return AlignToToString(cast<CToolBar*>(parent)->getAlignTo()); },
				[](IClass *parent, const String value) { return cast<CToolBar*>(parent)->setAlignTo(StringToAlignTo(value)); }))
				->AddHeaderFile(L"Standard/Controls/IToolBar.h");
			Add(new CPropertyFloat(this, control, L"Distance", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getDistance(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setDistance(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CToolBar*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CToolBar*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyBorderColor(this, control, L"BorderColor", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CToolBar*>(parent)->setBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"BackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CToolBar*>(parent)->setBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"BackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getBackgroundGradient(); }));
			Add(new CPropertyFloat(this, control, L"ScrollerSize", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getScrollerSize(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setScrollerSize(value); }))
				->setMin(1);
			Add(new CPropertyFloat(this, control, L"ScrollerArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getScrollerArrowSize(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setScrollerArrowSize(value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"ScrollerBorderWidth", false, ScrollerStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToolBar*>(parent)->getScrollerBorderWidth(StringToScrollerState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CToolBar*>(parent)->setScrollerBorderWidth(StringToScrollerState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"ScrollerBorderColor", false, ScrollerStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToolBar*>(parent)->getScrollerBorderColor(StringToScrollerState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CToolBar*>(parent)->setScrollerBorderColor(StringToScrollerState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ScrollerBackgroundColor", false, ScrollerStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToolBar*>(parent)->getScrollerBackgroundColor(StringToScrollerState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToolBar*>(parent)->setScrollerBackgroundColor(StringToScrollerState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"ScrollerBackgroundGradient", ScrollerStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToolBar*>(parent)->getScrollerBackgroundGradient(StringToScrollerState(state)); }));
			Add(new CPropertyColorState(this, control, L"ScrollerArrowColor", false, ScrollerStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CToolBar*>(parent)->getScrollerArrowColor(StringToScrollerState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CToolBar*>(parent)->setScrollerArrowColor(StringToScrollerState(state), value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ScrollDeltaTimer", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getScrollDeltaTimer(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setScrollDeltaTimer(value); }))
				->setMin(1);
			Add(new CPropertyFloat(this, control, L"ScrollDeltaWheel", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->getScrollDeltaWheel(); },
				[](IClass *parent, const float value) {return cast<CToolBar*>(parent)->setScrollDeltaWheel(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"UseMask", false, nullptr,
				[](IClass *parent) {return cast<CToolBar*>(parent)->isUseMask(); },
				[](IClass *parent, const bool value) {return cast<CToolBar*>(parent)->setUseMask(value); }));
		}

		StringArray CToolBarPropertyList::ScrollerStateItems()
		{
			return StringArray{
				L"ScrollerState::Normal",
				L"ScrollerState::Hovered",
				L"ScrollerState::Active",
				L"ScrollerState::ActiveHovered",
				L"ScrollerState::Disabled" };
		}

		CToolBar::ScrollerState CToolBarPropertyList::StringToScrollerState(const String &state)
		{
			if (state == L"ScrollerState::Hovered")
				return CToolBar::ScrollerState::Hovered;
			if (state == L"ScrollerState::Active")
				return CToolBar::ScrollerState::Active;
			if (state == L"ScrollerState::ActiveHovered")
				return CToolBar::ScrollerState::ActiveHovered;
			if (state == L"ScrollerState::Disabled")
				return CToolBar::ScrollerState::Disabled;
			return CToolBar::ScrollerState::Normal;
		}

		StringArray CToolBarPropertyList::AlignToItems()
		{
			return StringArray{
				L"AlignTo::Left",
				L"AlignTo::Right" };
		}

		String CToolBarPropertyList::AlignToToString(const IToolBar::AlignTo value)
		{
			switch (value)
			{
			case IToolBar::AlignTo::Right:	return L"AlignTo::Right";
			default:						return L"AlignTo::Left";
			}
		}

		IToolBar::AlignTo CToolBarPropertyList::StringToAlignTo(const String &value)
		{
			if (value == L"AlignTo::Right")
				return IToolBar::AlignTo::Right;
			return IToolBar::AlignTo::Left;
		}
	}
}