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
		CCustomDropDownPropertyList::CCustomDropDownPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Text", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getText(); },
				[](IClass *parent, const String value) {return cast<CCustomDropDown*>(parent)->setText(value); }));
			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CCustomDropDown*>(parent)->setActiveIndex(value); }));
			Add(new CPropertyBool(this, control, L"Editable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->isEditable(); },
				[](IClass *parent, const bool value) {return cast<CCustomDropDown*>(parent)->setEditable(value); }));
			Add(new CPropertyBool(this, control, L"ArrowAtRight", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->isArrowAtRight(); },
				[](IClass *parent, const bool value) {return cast<CCustomDropDown*>(parent)->setArrowAtRight(value); }));
			Add(new CPropertyBool(this, control, L"Sortable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->isSortable(); },
				[](IClass *parent, const bool value) {return cast<CCustomDropDown*>(parent)->setSortable(value); }));
			Add(new CPropertyEnum(this, control, L"OpenDirection", false, OpenDirectionItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent) {return OpenDirectionToString(cast<CCustomDropDown*>(parent)->getOpenDirection()); },
				[](IClass *parent, const String value) {return cast<CCustomDropDown*>(parent)->setOpenDirection(StringToOpenDirection(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyEnum(this, control, L"ArrowArea", false, ArrowAreaItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent) {return ArrowAreaToString(cast<CCustomDropDown*>(parent)->getArrowArea()); },
				[](IClass *parent, const String value) {return cast<CCustomDropDown*>(parent)->setArrowArea(StringToArrowArea(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyFloat(this, control, L"ArrowAreaSize", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getArrowAreaSize(); },
				[](IClass *parent, const float value) {return cast<CCustomDropDown*>(parent)->setArrowAreaSize(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ListWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListWidth(); },
				[](IClass *parent, const float value) {return cast<CCustomDropDown*>(parent)->setListWidth(value); }));
			Add(new CPropertyFloat(this, control, L"ListMaxHeight", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListMaxHeight(); },
				[](IClass *parent, const float value) {return cast<CCustomDropDown*>(parent)->setListMaxHeight(value); }))
				->setHasMin(true);
			Add(new CPropertyFloat(this, control, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getArrowSize(); },
				[](IClass *parent, const float value) {return cast<CCustomDropDown*>(parent)->setArrowSize(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getArrowBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setArrowBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getArrowBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setArrowBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setListBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setListBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListPadding", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomDropDown*>(parent)->setListPadding(value); }))
				->setMin(0);

			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomDropDown*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCustomDropDown*>(parent)->setShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColorState(this, control, L"ArrowBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setArrowBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setArrowBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"ArrowBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setArrowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColor(this, control, L"ListBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setListBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"ListBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomDropDown*>(parent)->setListBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ListBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ListShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomDropDown*>(parent)->setListShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ListShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CCustomDropDown*>(parent)->setListShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ListShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CCustomDropDown*>(parent)->setListShadowRadius(value); }))
				->setMin(1);

			Add(new CPropertyColorState(this, control, L"ShadowColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setShadowColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyPointFState(this, control, L"ShadowShiftEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowShiftEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomDropDown*>(parent)->setShadowShiftEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			pis = new CPropertyIntegerState(this, control, L"ShadowRadiusEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getShadowRadiusEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCustomDropDown*>(parent)->setShadowRadiusEditable(StringToState(state), value); });
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBorderColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setBorderColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBackgroundColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setBackgroundColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradientEditable", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getBackgroundGradientEditable(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColorState(this, control, L"ArrowBorderColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBorderColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setArrowBorderColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowBackgroundColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBackgroundColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setArrowBackgroundColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"ArrowBackgroundGradientEditable", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowBackgroundGradientEditable(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowColorEditable", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDropDown*>(parent)->getArrowColorEditable(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDropDown*>(parent)->setArrowColorEditable(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColor(this, control, L"ListBorderColorEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBorderColorEditable(); },
				[](IClass *parent, const BorderColor value) {return cast<CCustomDropDown*>(parent)->setListBorderColorEditable(value); }));
			Add(new CPropertyColor(this, control, L"ListBackgroundColorEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBackgroundColorEditable(); },
				[](IClass *parent, const Color value) {return cast<CCustomDropDown*>(parent)->setListBackgroundColorEditable(value); }));
			Add(new CPropertyGradient(this, control, L"ListBackgroundGradientEditable", nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListBackgroundGradientEditable(); }));
			Add(new CPropertyColor(this, control, L"ListShadowColorEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowColorEditable(); },
				[](IClass *parent, const Color value) {return cast<CCustomDropDown*>(parent)->setListShadowColorEditable(value); }));
			Add(new CPropertyPointF(this, control, L"ListShadowShiftEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowShiftEditable(); },
				[](IClass *parent, const PointF value) {return cast<CCustomDropDown*>(parent)->setListShadowShiftEditable(value); }));
			Add(new CPropertyInteger(this, control, L"ListShadowRadiusEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getListShadowRadiusEditable(); },
				[](IClass *parent, const int value) {return cast<CCustomDropDown*>(parent)->setListShadowRadiusEditable(value); }))
				->setMin(1);

			Add(new CPropertyFloat(this, control, L"SearchResetInterval", false, nullptr,
				[](IClass *parent) {return cast<CCustomDropDown*>(parent)->getSearchResetInterval(); },
				[](IClass *parent, const float value) {return cast<CCustomDropDown*>(parent)->setSearchResetInterval(value); }))
				->setMin(0.001f);
		}

		StringArray CCustomDropDownPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInDropDown::State CCustomDropDownPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInDropDown::State::Hovered;
			if (state == L"State::Focused")
				return CBuiltInDropDown::State::Focused;
			if (state == L"State::FocusedHovered")
				return CBuiltInDropDown::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CBuiltInDropDown::State::Disabled;
			return CBuiltInDropDown::State::Normal;
		}

		StringArray CCustomDropDownPropertyList::OpenDirectionItems()
		{
			return StringArray{
				L"OpenDirection::Up",
				L"OpenDirection::Down",
				L"OpenDirection::Auto" };
		}

		String CCustomDropDownPropertyList::OpenDirectionToString(const CBuiltInDropDown::OpenDirection value)
		{
			switch (value)
			{
			case CBuiltInDropDown::OpenDirection::Down: return L"OpenDirection::Down";
			case CBuiltInDropDown::OpenDirection::Auto: return L"OpenDirection::Auto";
			default:									return L"OpenDirection::Up";
			}
		}

		CBuiltInDropDown::OpenDirection CCustomDropDownPropertyList::StringToOpenDirection(const String &value)
		{
			if (value == L"OpenDirection::Down")
				return CBuiltInDropDown::OpenDirection::Down;
			if (value == L"OpenDirection::Auto")
				return CBuiltInDropDown::OpenDirection::Auto;
			return CBuiltInDropDown::OpenDirection::Up;
		}

		StringArray CCustomDropDownPropertyList::ArrowAreaItems()
		{
			return StringArray{
				L"ArrowArea::Absolute",
				L"ArrowArea::Height",
				L"ArrowArea::WidthPart" };
		}

		String CCustomDropDownPropertyList::ArrowAreaToString(const CBuiltInDropDown::ArrowArea value)
		{
			switch (value)
			{
			case CBuiltInDropDown::ArrowArea::Height:		return L"ArrowArea::Height";
			case CBuiltInDropDown::ArrowArea::WidthPart:	return L"ArrowArea::WidthPart";
			default:										return L"ArrowArea::Absolute";
			}
		}

		CBuiltInDropDown::ArrowArea CCustomDropDownPropertyList::StringToArrowArea(const String &value)
		{
			if (value == L"ArrowArea::Height")
				return CBuiltInDropDown::ArrowArea::Height;
			if (value == L"ArrowArea::WidthPart")
				return CBuiltInDropDown::ArrowArea::WidthPart;
			return CBuiltInDropDown::ArrowArea::Absolute;
		}
	}
}