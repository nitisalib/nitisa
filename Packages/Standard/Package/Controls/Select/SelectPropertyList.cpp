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
		CSelectPropertyList::CSelectPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");
			Delete(L"Font.ShadowColor");
			Delete(L"Font.ShadowShift");
			Delete(L"Font.ShadowRadius");

			Add(new CPropertyString(this, control, L"Filter", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getFilter(); },
				[](IClass *parent, const String value) {return cast<CSelect*>(parent)->setFilter(value); }));
			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CSelect*>(parent)->setActiveIndex(value); }));
			Add(new CPropertyFont(this, control, L"CategoryFont", false, nullptr,
				[](IClass *parent) { return cast<CSelect*>(parent)->getCategoryFont(); },
				[](IClass *parent, IFont *value) {return cast<CSelect*>(parent)->setCategoryFont(value); }));
			Add(new CPropertyFloat(this, control, L"CategoryFont.Distance", false,
				[](IClass *parent) { return true; },
				[](IClass *parent) { return cast<CSelect*>(parent)->getCategoryFont()->Distance; },
				[](IClass *parent, const float value) { return cast<CSelect*>(parent)->getCategoryFont()->setDistance(value); }));
			Add(new CPropertyBool(this, control, L"CategoryFont.Monospace", false,
				[](IClass *parent) { return true; },
				[](IClass *parent) { return cast<CSelect*>(parent)->getCategoryFont()->Monospace; },
				[](IClass *parent, const bool value) { return cast<CSelect*>(parent)->getCategoryFont()->setMonospace(value); }));
			Add(new CPropertyBool(this, control, L"ArrowAtRight", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->isArrowAtRight(); },
				[](IClass *parent, const bool value) {return cast<CSelect*>(parent)->setArrowAtRight(value); }));
			Add(new CPropertyEnum(this, control, L"OpenDirection", false, OpenDirectionItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent) {return OpenDirectionToString(cast<CSelect*>(parent)->getOpenDirection()); },
				[](IClass *parent, const String value) {return cast<CSelect*>(parent)->setOpenDirection(StringToOpenDirection(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyEnum(this, control, L"ArrowArea", false, ArrowAreaItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent) {return ArrowAreaToString(cast<CSelect*>(parent)->getArrowArea()); },
				[](IClass *parent, const String value) {return cast<CSelect*>(parent)->setArrowArea(StringToArrowArea(value)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyFloat(this, control, L"ListWidth", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListWidth(); },
				[](IClass *parent, const float value) {return cast<CSelect*>(parent)->setListWidth(value); }));
			Add(new CPropertyFloat(this, control, L"ListMaxHeight", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListMaxHeight(); },
				[](IClass *parent, const float value) {return cast<CSelect*>(parent)->setListMaxHeight(value); }))
				->setHasMin(true);
			Add(new CPropertyFloat(this, control, L"ArrowAreaSize", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getArrowAreaSize(); },
				[](IClass *parent, const float value) {return cast<CSelect*>(parent)->setArrowAreaSize(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ArrowSize", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getArrowSize(); },
				[](IClass *parent, const float value) {return cast<CSelect*>(parent)->setArrowSize(value); }))
				->setMin(0)
				->setMax(1);
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getArrowBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setArrowBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ArrowBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getArrowBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setArrowBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setListBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListBorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setListBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"ListPadding", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListPadding(); },
				[](IClass *parent, const RectF value) {return cast<CSelect*>(parent)->setListPadding(value); }))
				->setMin(0);

			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSelect*>(parent)->setShadowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CSelect*>(parent)->setShadowShift(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			CPropertyIntegerState *pis{ new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CSelect*>(parent)->setShadowRadius(StringToState(state), value); }) };
			pis->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			pis->setMin(1);
			Add(pis);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CSelect*>(parent)->setBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSelect*>(parent)->setBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyBorderColorState(this, control, L"InputBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getInputBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CSelect*>(parent)->setInputBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyColorState(this, control, L"InputBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getInputBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSelect*>(parent)->setInputBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyGradientState(this, control, L"InputBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getInputBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyBorderColorState(this, control, L"ArrowBorderColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getArrowBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CSelect*>(parent)->setArrowBorderColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyColorState(this, control, L"ArrowBackgroundColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getArrowBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSelect*>(parent)->setArrowBackgroundColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyGradientState(this, control, L"ArrowBackgroundGradient", StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getArrowBackgroundGradient(StringToState(state)); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyColorState(this, control, L"ArrowColor", false, StateItems(), ExportPrefixType::None, L"CBuiltInSelect::", nullptr,
				[](IClass *parent, const String &state) {return cast<CSelect*>(parent)->getArrowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CSelect*>(parent)->setArrowColor(StringToState(state), value); }))
				->AddHeaderFile(L"Nitisa/BuiltInControls/Select/BuiltInSelect.h");
			Add(new CPropertyBorderColor(this, control, L"ListBorderColor", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListBorderColor(); },
				[](IClass *parent, const BorderColor value) {return cast<CSelect*>(parent)->setListBorderColor(value); }));
			Add(new CPropertyColor(this, control, L"ListBackgroundColor", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListBackgroundColor(); },
				[](IClass *parent, const Color value) {return cast<CSelect*>(parent)->setListBackgroundColor(value); }));
			Add(new CPropertyGradient(this, control, L"ListBackgroundGradient", nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListBackgroundGradient(); }));
			Add(new CPropertyColor(this, control, L"ListShadowColor", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListShadowColor(); },
				[](IClass *parent, const Color value) {return cast<CSelect*>(parent)->setListShadowColor(value); }));
			Add(new CPropertyPointF(this, control, L"ListShadowShift", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListShadowShift(); },
				[](IClass *parent, const PointF value) {return cast<CSelect*>(parent)->setListShadowShift(value); }));
			Add(new CPropertyInteger(this, control, L"ListShadowRadius", false, nullptr,
				[](IClass *parent) {return cast<CSelect*>(parent)->getListShadowRadius(); },
				[](IClass *parent, const int value) {return cast<CSelect*>(parent)->setListShadowRadius(value); }))
				->setMin(1);
		}

		StringArray CSelectPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CBuiltInSelect::State CSelectPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CBuiltInSelect::State::Hovered;
			if (state == L"State::Focused")
				return CBuiltInSelect::State::Focused;
			if (state == L"State::FocusedHovered")
				return CBuiltInSelect::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CBuiltInSelect::State::Disabled;
			return CBuiltInSelect::State::Normal;
		}

		StringArray CSelectPropertyList::OpenDirectionItems()
		{
			return StringArray{
				L"OpenDirection::Up",
				L"OpenDirection::Down",
				L"OpenDirection::Auto" };
		}

		String CSelectPropertyList::OpenDirectionToString(const CBuiltInSelect::OpenDirection value)
		{
			switch (value)
			{
			case CBuiltInSelect::OpenDirection::Down:	return L"OpenDirection::Down";
			case CBuiltInSelect::OpenDirection::Auto:	return L"OpenDirection::Auto";
			default:									return L"OpenDirection::Up";
			}
		}

		CBuiltInSelect::OpenDirection CSelectPropertyList::StringToOpenDirection(const String &value)
		{
			if (value == L"OpenDirection::Down")
				return CBuiltInSelect::OpenDirection::Down;
			if (value == L"OpenDirection::Auto")
				return CBuiltInSelect::OpenDirection::Auto;
			return CBuiltInSelect::OpenDirection::Up;
		}

		StringArray CSelectPropertyList::ArrowAreaItems()
		{
			return StringArray{
				L"ArrowArea::Absolute",
				L"ArrowArea::Height",
				L"ArrowArea::WidthPart" };
		}

		String CSelectPropertyList::ArrowAreaToString(const CBuiltInSelect::ArrowArea value)
		{
			switch (value)
			{
			case CBuiltInSelect::ArrowArea::Height:		return L"ArrowArea::Height";
			case CBuiltInSelect::ArrowArea::WidthPart:	return L"ArrowArea::WidthPart";
			default:									return L"ArrowArea::Absolute";
			}
		}

		CBuiltInSelect::ArrowArea CSelectPropertyList::StringToArrowArea(const String &value)
		{
			if (value == L"ArrowArea::Height")
				return CBuiltInSelect::ArrowArea::Height;
			if (value == L"ArrowArea::WidthPart")
				return CBuiltInSelect::ArrowArea::WidthPart;
			return CBuiltInSelect::ArrowArea::Absolute;
		}
	}
}