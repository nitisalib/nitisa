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
		CCustomTreeViewPropertyList::CCustomTreeViewPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CControlPropertyList(package, control, entity)
		{
			Delete(L"TransformControls");
			Delete(L"WantTabs");

			Add(new CPropertyRectF(this, control, L"BorderWidth", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getBorderWidth(); },
				[](IClass *parent, const RectF value) {return cast<CCustomTreeView*>(parent)->setBorderWidth(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"BorderRadius", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getBorderRadius(); },
				[](IClass *parent, const RectF value) {return cast<CCustomTreeView*>(parent)->setBorderRadius(value); }))
				->setMin(0);
			Add(new CPropertyRectF(this, control, L"Padding", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomTreeView*>(parent)->setPadding(value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"BorderColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getBorderColor(StringToState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomTreeView*>(parent)->setBorderColor(StringToState(state), value); }));
			Add(new CPropertyColorState(this, control, L"BackgroundColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getBackgroundColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomTreeView*>(parent)->setBackgroundColor(StringToState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"BackgroundGradient", StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getBackgroundGradient(StringToState(state)); }));
			Add(new CPropertyColorState(this, control, L"ShadowColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getShadowColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomTreeView*>(parent)->setShadowColor(StringToState(state), value); }));
			Add(new CPropertyPointFState(this, control, L"ShadowShift", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getShadowShift(StringToState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomTreeView*>(parent)->setShadowShift(StringToState(state), value); }));
			Add(new CPropertyIntegerState(this, control, L"ShadowRadius", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getShadowRadius(StringToState(state)); },
				[](IClass *parent, const String &state, const int value) {return cast<CCustomTreeView*>(parent)->setShadowRadius(StringToState(state), value); }))
				->setMin(1);
			Add(new CPropertyColorState(this, control, L"CornerColor", false, StateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getCornerColor(StringToState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomTreeView*>(parent)->setCornerColor(StringToState(state), value); }));
			Add(new CPropertyFloat(this, control, L"ItemHeight", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getItemHeight(); },
				[](IClass *parent, const float value) {return cast<CCustomTreeView*>(parent)->setItemHeight(value); }));
			Add(new CPropertyPointF(this, control, L"FolderSize", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getFolderSize(); },
				[](IClass *parent, const PointF value) {return cast<CCustomTreeView*>(parent)->setFolderSize(value); }))
				->setMin(0);
			Add(new CPropertyColor(this, control, L"FolderLinesColor", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getFolderLinesColor(); },
				[](IClass *parent, const Color value) {return cast<CCustomTreeView*>(parent)->setFolderLinesColor(value); }));
			Add(new CPropertyRectFState(this, control, L"FolderBorderWidth", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderBorderWidth(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CCustomTreeView*>(parent)->setFolderBorderWidth(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyRectFState(this, control, L"FolderBorderRadius", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderBorderRadius(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CCustomTreeView*>(parent)->setFolderBorderRadius(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"FolderBorderColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderBorderColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomTreeView*>(parent)->setFolderBorderColor(StringToFolderState(state), value); }));
			Add(new CPropertyColorState(this, control, L"FolderBackgroundColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderBackgroundColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomTreeView*>(parent)->setFolderBackgroundColor(StringToFolderState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"FolderBackgroundGradient", FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderBackgroundGradient(StringToFolderState(state)); }));
			Add(new CPropertyPointFState(this, control, L"FolderSignSize", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderSignSize(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const PointF value) {return cast<CCustomTreeView*>(parent)->setFolderSignSize(StringToFolderState(state), value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"FolderSignColor", false, FolderStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomTreeView*>(parent)->getFolderSignColor(StringToFolderState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomTreeView*>(parent)->setFolderSignColor(StringToFolderState(state), value); }));
			Add(new CPropertyBool(this, control, L"Multiselect", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->isMultiselect(); },
				[](IClass *parent, const bool value) {return cast<CCustomTreeView*>(parent)->setMultiselect(value); }));
			Add(new CPropertyBool(this, control, L"Movable", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->isMovable(); },
				[](IClass *parent, const bool value) {return cast<CCustomTreeView*>(parent)->setMovable(value); }));
			Add(new CPropertyEnum(this, control, L"HScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomTreeView*>(parent)->getHScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CCustomTreeView*>(parent)->setHScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyEnum(this, control, L"VScrollVisibility", false, ScrollVisibilityItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return ScrollVisibilityToString(cast<CCustomTreeView*>(parent)->getVScrollVisibility()); },
				[](IClass *parent, const String value) {return cast<CCustomTreeView*>(parent)->setVScrollVisibility(StringToScrollVisibility(value)); }))
				->AddHeaderFile(L"Nitisa/Core/ScrollVisibility.h");
			Add(new CPropertyFloat(this, control, L"ScrollInterval", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getScrollInterval(); },
				[](IClass *parent, const float value) {return cast<CCustomTreeView*>(parent)->setScrollInterval(value); }))
				->setMin(0.001f);
			Add(new CPropertyFloat(this, control, L"ScrollDelta", false, nullptr,
				[](IClass *parent) {return cast<CCustomTreeView*>(parent)->getScrollDelta(); },
				[](IClass *parent, const float value) {return cast<CCustomTreeView*>(parent)->setScrollDelta(value); }))
				->setMin(1);
		}

		StringArray CCustomTreeViewPropertyList::StateItems()
		{
			return StringArray{
				L"State::Normal",
				L"State::Hovered",
				L"State::Focused",
				L"State::FocusedHovered",
				L"State::Disabled" };
		}

		CCustomTreeView::State CCustomTreeViewPropertyList::StringToState(const String &state)
		{
			if (state == L"State::Hovered")
				return CCustomTreeView::State::Hovered;
			if (state == L"State::Focused")
				return CCustomTreeView::State::Focused;
			if (state == L"State::FocusedHovered")
				return CCustomTreeView::State::FocusedHovered;
			if (state == L"State::Disabled")
				return CCustomTreeView::State::Disabled;
			return CCustomTreeView::State::Normal;
		}

		StringArray CCustomTreeViewPropertyList::FolderStateItems()
		{
			return StringArray{
				L"FolderState::Normal",
				L"FolderState::Hovered" };
		}

		CCustomTreeView::FolderState CCustomTreeViewPropertyList::StringToFolderState(const String &state)
		{
			if (state == L"FolderState::Hovered")
				return CCustomTreeView::FolderState::Hovered;
			return CCustomTreeView::FolderState::Normal;
		}
	}
}