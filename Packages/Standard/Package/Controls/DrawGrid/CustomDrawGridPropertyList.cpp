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
		CCustomDrawGridPropertyList::CCustomDrawGridPropertyList(IPackage *package, IControl *control, IPackageEntity *entity) :
			CCustomGridPropertyList(package, control, entity)
		{
			Add(new CPropertyInteger(this, control, L"FixedColumns", false, nullptr,
				[](IClass *parent) {return cast<CCustomDrawGrid*>(parent)->getFixedColumns(); },
				[](IClass *parent, const int value) {return cast<CCustomDrawGrid*>(parent)->setFixedColumns(value); }))
				->setMin(0);
			Add(new CPropertyInteger(this, control, L"FixedRows", false, nullptr,
				[](IClass *parent) {return cast<CCustomDrawGrid*>(parent)->getFixedRows(); },
				[](IClass *parent, const int value) {return cast<CCustomDrawGrid*>(parent)->setFixedRows(value); }))
				->setMin(0);
			Add(new CPropertyColorState(this, control, L"FixedCellBackgroundColor", false, FixedCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDrawGrid*>(parent)->getFixedCellBackgroundColor(StringToFixedCellState(state)); },
				[](IClass *parent, const String &state, const Color value) {return cast<CCustomDrawGrid*>(parent)->setFixedCellBackgroundColor(StringToFixedCellState(state), value); }));
			Add(new CPropertyGradientState(this, control, L"FixedCellBackgroundGradient", FixedCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDrawGrid*>(parent)->getFixedCellBackgroundGradient(StringToFixedCellState(state)); }));
			Add(new CPropertyRectFState(this, control, L"FixedCellBorderWidth", false, FixedCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDrawGrid*>(parent)->getFixedCellBorderWidth(StringToFixedCellState(state)); },
				[](IClass *parent, const String &state, const RectF value) {return cast<CCustomDrawGrid*>(parent)->setFixedCellBorderWidth(StringToFixedCellState(state), value); }))
				->setMin(0);
			Add(new CPropertyBorderColorState(this, control, L"FixedCellBorderColor", false, FixedCellStateItems(), ExportPrefixType::NamespaceParent, L"", nullptr,
				[](IClass *parent, const String &state) {return cast<CCustomDrawGrid*>(parent)->getFixedCellBorderColor(StringToFixedCellState(state)); },
				[](IClass *parent, const String &state, const BorderColor value) {return cast<CCustomDrawGrid*>(parent)->setFixedCellBorderColor(StringToFixedCellState(state), value); }));
		}

		StringArray CCustomDrawGridPropertyList::FixedCellStateItems()
		{
			return StringArray{
				L"FixedCellState::Normal",
				L"FixedCellState::Hovered",
				L"FixedCellState::Down",
				L"FixedCellState::Disabled" };
		}

		CCustomDrawGrid::FixedCellState CCustomDrawGridPropertyList::StringToFixedCellState(const String &state)
		{
			if (state == L"FixedCellState::Hovered")
				return CCustomDrawGrid::FixedCellState::Hovered;
			if (state == L"FixedCellState::Down")
				return CCustomDrawGrid::FixedCellState::Down;
			if (state == L"FixedCellState::Disabled")
				return CCustomDrawGrid::FixedCellState::Disabled;
			return CCustomDrawGrid::FixedCellState::Normal;
		}
	}
}