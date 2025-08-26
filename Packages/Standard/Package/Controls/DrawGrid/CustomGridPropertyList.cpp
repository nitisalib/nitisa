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
		CCustomGridPropertyList::CCustomGridPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");

			Add(new CPropertyBool(this, control, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setMultiselect(value); }));
			Add(new CPropertyInteger(this, control, L"Columns", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getColumns(); },
				[](IClass *parent, const int value) {return cast<CCustomGrid*>(parent)->setColumns(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"Rows", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getRows(); },
				[](IClass *parent, const int value) {return cast<CCustomGrid*>(parent)->setRows(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"VerticalScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomGrid*>(parent)->getVerticalScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CCustomGrid*>(parent)->setVerticalScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"HorizontalScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomGrid*>(parent)->getHorizontalScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CCustomGrid*>(parent)->setHorizontalScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomGrid*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomGrid*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"GridWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getGridWidth(); },
				[](IClass *parent, const float value) {return cast<CCustomGrid*>(parent)->setGridWidth(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"GridColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getGridColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomGrid*>(parent)->setGridColor(StringToState(state), value); }));
			Add(new CPropertyRectFState(this, control, L"BorderRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getBorderRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CCustomGrid*>(parent)->setBorderRadius(StringToState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomGrid*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomGrid*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCustomGrid*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomGrid*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomGrid*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomGrid*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomGrid*>(parent)->setCornerColor(StringToState(state), value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CCustomGrid*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"DefaultColumnWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getDefaultColumnWidth(); },
				[](IClass *parent, const float value) {return cast<CCustomGrid*>(parent)->setDefaultColumnWidth(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"DefaultRowHeight", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->getDefaultRowHeight(); },
				[](IClass *parent, const float value) {return cast<CCustomGrid*>(parent)->setDefaultRowHeight(value); }))
				->setMin(0);
			Add(new CPropertyBool(this, control, L"DefaultColumnResizable", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultColumnResizable(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultColumnResizable(value); }));
			Add(new CPropertyBool(this, control, L"DefaultRowResizable", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultRowResizable(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultRowResizable(value); }));
			Add(new CPropertyBool(this, control, L"DefaultColumnAutosize", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultColumnAutosize(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultColumnAutosize(value); }));
			Add(new CPropertyBool(this, control, L"DefaultRowAutosize", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultRowAutosize(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultRowAutosize(value); }));
			Add(new CPropertyBool(this, control, L"DefaultColumnEnabled", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultColumnEnabled(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultColumnEnabled(value); }));
			Add(new CPropertyBool(this, control, L"DefaultRowEnabled", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultRowEnabled(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultRowEnabled(value); }));
			Add(new CPropertyBool(this, control, L"DefaultColumnFixed", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultColumnFixed(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultColumnFixed(value); }));
			Add(new CPropertyBool(this, control, L"DefaultRowFixed", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultRowFixed(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultRowFixed(value); }));
			Add(new CPropertyBool(this, control, L"DefaultColumnOverflowHidden", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultColumnOverflowHidden(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultColumnOverflowHidden(value); }));
			Add(new CPropertyBool(this, control, L"DefaultColumnRowHidden", false, nullptr,
				[](IClass *parent) {return cast<CCustomGrid*>(parent)->isDefaultRowOverflowHidden(); },
				[](IClass *parent, const bool value) {return cast<CCustomGrid*>(parent)->setDefaultRowOverflowHidden(value); }));
		}

		StringArray CCustomGridPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CCustomGrid::State CCustomGridPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CCustomGrid::State::Hovered;
			if (state == L"State::Focused")
				return CCustomGrid::State::Focused;
			if (state == L"State::FocusedHovered")
				return CCustomGrid::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CCustomGrid::State::Disabled;
			return CCustomGrid::State::Normal;
		}
	}
}