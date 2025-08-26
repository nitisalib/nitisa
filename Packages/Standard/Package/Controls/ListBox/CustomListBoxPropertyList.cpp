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
		CCustomListBoxPropertyList::CCustomListBoxPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");

			Add(new CPropertyInteger(this, control, L"ActiveIndex", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getActiveIndex(); },
				[](IClass *parent, const int value) {return cast<CCustomListBox*>(parent)->setActiveIndex(value); }));
			Add(new CPropertyBool(this, control, L"Sortable", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->isSortable(); },
				[](IClass *parent, const bool value) {return cast<CCustomListBox*>(parent)->setSortable(value); }));
			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomListBox*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CCustomListBox*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomListBox*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyFloat(this, control, L"SearchResetInterval", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getSearchResetInterval(); },
				[](IClass *parent, const float value) {return cast<CCustomListBox*>(parent)->setSearchResetInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyEnum(this, control, L"HorizontalScrollBar", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomListBox*>(parent)->getHorizontalScrollBar()); },
				[](IClass *parent, const String value) {return cast<CCustomListBox*>(parent)->setHorizontalScrollBar(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"VerticalScrollBar", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomListBox*>(parent)->getVerticalScrollBar()); },
				[](IClass *parent, const String value) {return cast<CCustomListBox*>(parent)->setVerticalScrollBar(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyInteger(this, control, L"Columns", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getColumns(); },
				[](IClass *parent, const int value) {return cast<CCustomListBox*>(parent)->setColumns(value); }))
				->setMin(1);
			Add(new CPropertyBool(this, control, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CCustomListBox*>(parent)->setMultiselect(value); }));
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CCustomListBox*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CCustomListBox*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomListBox*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomListBox*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCustomListBox*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomListBox*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomListBox*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomListBox*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomListBox*>(parent)->setCornerColor(StringToState(state), value); }));
		}

		StringArray CCustomListBoxPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CCustomListBox::State CCustomListBoxPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CCustomListBox::State::Hovered;
			if (state == L"State::Focused")
				return CCustomListBox::State::Focused;
			if (state == L"State::FocusedHovered")
				return CCustomListBox::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CCustomListBox::State::Disabled;
			return CCustomListBox::State::Normal;
		}
	}
}