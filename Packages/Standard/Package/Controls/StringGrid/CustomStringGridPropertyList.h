// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "../DrawGrid/CustomDrawGridPropertyList.h"
#include "../../../Controls/StringGrid/CustomStringGrid.h"

namespace nitisa
{
	class IControl;
	class IPackage;
	class IPackageEntity;

	namespace standard
	{
		class CCustomStringGridPropertyList :public CCustomDrawGridPropertyList
		{
		private:
			static StringArray CellStateItems();
			static CCustomStringGrid::CellState StringToCellState(const String &state);
			static StringArray ActiveCellStateItems();
			static CCustomStringGrid::ActiveCellState StringToActiveCellState(const String &state);
		public:
			CCustomStringGridPropertyList(IPackage *package, IControl *control, IPackageEntity *entity);
		};
	}
}