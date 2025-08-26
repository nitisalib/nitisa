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
		CDriveDropDownPropertyList::CDriveDropDownPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyControlDirectoryTree(this, control, L"DirectoryTree", nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getDirectoryTree(); },
				[](IClass *parent, IDirectoryTree *value) {return cast<CDriveDropDown*>(parent)->setDirectoryTree(value); }));
			Add(new CPropertyEnum(this, control, L"OpenDirection", false, OpenDirectionItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent) {return OpenDirectionToString(cast<CDriveDropDown*>(parent)->getOpenDirection()); },
				[](IClass *parent, const String value) {return cast<CDriveDropDown*>(parent)->setOpenDirection(StringToOpenDirection(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyEnum(this, control, L"ArrowArea", false, ArrowAreaItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent) {return ArrowAreaToString(cast<CDriveDropDown*>(parent)->getArrowArea()); },
				[](IClass *parent, const String value) {return cast<CDriveDropDown*>(parent)->setArrowArea(StringToArrowArea(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyFloat(this, control, L"ArrowAreaSize", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getArrowAreaSize(); },
				[](IClass *parent, const float value) {return cast<CDriveDropDown*>(parent)->setArrowAreaSize(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ListWidth", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListWidth(); },
				[](IClass *parent, const float value) {return cast<CDriveDropDown*>(parent)->setListWidth(value); }));
			Add(new CPropertyFloat(this, control, L"ListMaxHeight", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListMaxHeight(); },
				[](IClass *parent, const float value) {return cast<CDriveDropDown*>(parent)->setListMaxHeight(value); }))
				->setHasMin(true);
			Add(new CPropertyFloat(this, control, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getArrowSize(); },
				[](IClass *parent, const float value) {return cast<CDriveDropDown*>(parent)->setArrowSize(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getArrowBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setArrowBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getArrowBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setArrowBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setListBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setListBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListPadding", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListPadding(); },
				[](IClass *parent, const RectF value) {return cast<CDriveDropDown*>(parent)->setListPadding(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDriveDropDown*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CDriveDropDown*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CDriveDropDown*>(parent)->setShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDriveDropDown*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDriveDropDown*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColorState(this, control, L"ArrowBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getArrowBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CDriveDropDown*>(parent)->setArrowBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDriveDropDown*>(parent)->setArrowBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyGradientState(this, control, L"ArrowBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getArrowBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyColorState(this, control, L"ArrowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInDropDown::", nullptr,
				[](IClass *parent, const String &state) {return cast<CDriveDropDown*>(parent)->getArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CDriveDropDown*>(parent)->setArrowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/DropDown/BuiltInDropDown.h");
			Add(new CPropertyBorderColor(this, control, L"ListBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CDriveDropDown*>(parent)->setListBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"ListBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CDriveDropDown*>(parent)->setListBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ListBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ListShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CDriveDropDown*>(parent)->setListShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ListShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CDriveDropDown*>(parent)->setListShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ListShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CDriveDropDown*>(parent)->getListShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CDriveDropDown*>(parent)->setListShadowRadius(value); }))
				->setMin(1);
		}

		StringArray CDriveDropDownPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInDropDown::State CDriveDropDownPropertyList::StringToState(const String &state)
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

		StringArray CDriveDropDownPropertyList::OpenDirectionItems()
		{
			return StringArray{
				L"OpenDirection::Up",
				L"OpenDirection::Down" };
		}

		String CDriveDropDownPropertyList::OpenDirectionToString(const CBuiltInDropDown::OpenDirection value)
		{
			switch (value)
			{
			case CBuiltInDropDown::OpenDirection::Down: return L"OpenDirection::Down";
			default:									return L"OpenDirection::Up";
			}
		}

		CBuiltInDropDown::OpenDirection CDriveDropDownPropertyList::StringToOpenDirection(const String &value)
		{
			if (value == L"OpenDirection::Down")
				return CBuiltInDropDown::OpenDirection::Down;
			return CBuiltInDropDown::OpenDirection::Up;
		}

		StringArray CDriveDropDownPropertyList::ArrowAreaItems()
		{
			return StringArray{
				L"ArrowArea::Absolute",
				L"ArrowArea::Height",
				L"ArrowArea::WidthPart" };
		}

		String CDriveDropDownPropertyList::ArrowAreaToString(const CBuiltInDropDown::ArrowArea value)
		{
			switch (value)
			{
			case CBuiltInDropDown::ArrowArea::Height:		return L"ArrowArea::Height";
			case CBuiltInDropDown::ArrowArea::WidthPart:	return L"ArrowArea::WidthPart";
			default:										return L"ArrowArea::Absolute";
			}
		}

		CBuiltInDropDown::ArrowArea CDriveDropDownPropertyList::StringToArrowArea(const String &value)
		{
			if (value == L"ArrowArea::Height")
				return CBuiltInDropDown::ArrowArea::Height;
			if (value == L"ArrowArea::WidthPart")
				return CBuiltInDropDown::ArrowArea::WidthPart;
			return CBuiltInDropDown::ArrowArea::Absolute;
		}
	}
}