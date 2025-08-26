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
		CCustomStringGridPropertyList::CCustomStringGridPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomDrawGridPropertyList(package, control, entity)
		{
			Add(new CPropertyBool(this, control, L"ActiveCellDotted", false, nullptr,
				[](IClass *parent) {return cast<CCustomStringGrid*>(parent)->isActiveCellDotted(); },
				[](IClass *parent, const bool value) {return cast<CCustomStringGrid*>(parent)->setActiveCellDotted(value); }));
			Add(new CPropertyBool(this, control, L"DefaultCellEditable", false, nullptr,
				[](IClass *parent) {return cast<CCustomStringGrid*>(parent)->isDefaultCellEditable(); },
				[](IClass *parent, const bool value) {return cast<CCustomStringGrid*>(parent)->setDefaultCellEditable(value); }));
			Add(new CPropertyRectF(this, control, L"DefaultCellPadding", false, nullptr,
				[](IClass *parent) {return cast<CCustomStringGrid*>(parent)->getDefaultCellPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomStringGrid*>(parent)->setDefaultCellPadding(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"DefaultCellTextAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CCustomStringGrid*>(parent)->getDefaultCellTextAlign()); },
				[](IClass *parent, const String value) {return cast<CCustomStringGrid*>(parent)->setDefaultCellTextAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"DefaultCellVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CCustomStringGrid*>(parent)->getDefaultCellVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CCustomStringGrid*>(parent)->setDefaultCellVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyRectF(this, control, L"DefaultCellFixedPadding", false, nullptr,
				[](IClass *parent) {return cast<CCustomStringGrid*>(parent)->getDefaultFixedCellPadding(); },
				[](IClass *parent, const RectF value) {return cast<CCustomStringGrid*>(parent)->setDefaultFixedCellPadding(value); }))
				->setMin(0);
			Add(new CPropertyEnum(this, control, L"DefaultFixedCellTextAlign", false, TextAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return TextAlignToString(cast<CCustomStringGrid*>(parent)->getDefaultFixedCellTextAlign()); },
				[](IClass *parent, const String value) {return cast<CCustomStringGrid*>(parent)->setDefaultFixedCellTextAlign(StringToTextAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/TextAlign.h");
			Add(new CPropertyEnum(this, control, L"DefaultFixedCellVerticalAlign", false, VerticalAlignItems(), ExportPrefixType::None, L"", nullptr,
				[](IClass *parent) {return VerticalAlignToString(cast<CCustomStringGrid*>(parent)->getDefaultFixedCellVerticalAlign()); },
				[](IClass *parent, const String value) {return cast<CCustomStringGrid*>(parent)->setDefaultFixedCellVerticalAlign(StringToVerticalAlign(value)); }))
				->AddHeaderFile(L"Nitisa/Core/VerticalAlign.h");
			Add(new CPropertyColorState(this, control, L"CellBackgroundColor", false, CellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomStringGrid*>(parent)->getCellBackgroundColor(StringToCellState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomStringGrid*>(parent)->setCellBackgroundColor(StringToCellState(state), value); }));
			Add(new CPropertyColorState(this, control, L"CellColor", false, CellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomStringGrid*>(parent)->getCellColor(StringToCellState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomStringGrid*>(parent)->setCellColor(StringToCellState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"CellBackgroundGradient", CellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomStringGrid*>(parent)->getCellBackgroundGradient(StringToCellState(state)); }));
			Add(new CPropertyColorState(this, control, L"ActiveCellOutlineColor", false, ActiveCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomStringGrid*>(parent)->getActiveCellOutlineColor(StringToActiveCellState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomStringGrid*>(parent)->setActiveCellOutlineColor(StringToActiveCellState(state), value); }));
			Add(new CPropertyMaskState(this, control, L"ActiveCellOutlineMask", false, ActiveCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomStringGrid*>(parent)->getActiveCellOutlineMask(StringToActiveCellState(state)); },
				[](IClass *parent, const String &state, const unsigned int value) {return cast<CCustomStringGrid*>(parent)->setActiveCellOutlineMask(StringToActiveCellState(state), value); }));
		}

		StringArray CCustomStringGridPropertyList::CellStateItems()
		{
			return StringArray{
				L"CellState::Normal",
				L"CellState::Hovered",
				L"CellState::Focused",
				L"CellState::FocusedHovered",
				L"CellState::Selected",
				L"CellState::SelectedHovered",
				L"CellState::Active",
				L"CellState::ActiveHovered",
				L"CellState::ActiveSelected",
				L"CellState::ActiveSelectedHovered",
				L"CellState::Disabled" };
		}

		CCustomStringGrid::CellState CCustomStringGridPropertyList::StringToCellState(const String &state)
		{
			if (state == L"CellState::Hovered")
				return CCustomStringGrid::CellState::Hovered;
			if (state == L"CellState::Focused")
				return CCustomStringGrid::CellState::Focused;
			if (state == L"CellState::FocusedHovered")
				return CCustomStringGrid::CellState::FocusedHovered;
			if (state == L"CellState::Selected")
				return CCustomStringGrid::CellState::Selected;
			if (state == L"CellState::SelectedHovered")
				return CCustomStringGrid::CellState::SelectedHovered;
			if (state == L"CellState::ActiveHovered")
				return CCustomStringGrid::CellState::ActiveHovered;
			if (state == L"CellState::ActiveSelected")
				return CCustomStringGrid::CellState::ActiveSelected;
			if (state == L"CellState::ActiveSelectedHovered")
				return CCustomStringGrid::CellState::ActiveSelectedHovered;
			if (state == L"CellState::Disabled")
				return CCustomStringGrid::CellState::Disabled;
			return CCustomStringGrid::CellState::Normal;
		}

		StringArray CCustomStringGridPropertyList::ActiveCellStateItems()
		{
			return StringArray{
				L"ActiveCellState::Normal",
				L"ActiveCellState::Hovered",
				L"ActiveCellState::Selected",
				L"ActiveCellState::SelectedHovered" };
		}

		CCustomStringGrid::ActiveCellState CCustomStringGridPropertyList::StringToActiveCellState(const String &state)
		{
			if (state == L"ActiveCellState::Hovered")
				return CCustomStringGrid::ActiveCellState::Hovered;
			if (state == L"ActiveCellState::Selected")
				return CCustomStringGrid::ActiveCellState::Selected;
			if (state == L"ActiveCellState::SelectedHovered")
				return CCustomStringGrid::ActiveCellState::SelectedHovered;
			return CCustomStringGrid::ActiveCellState::Normal;
		}
	}
}