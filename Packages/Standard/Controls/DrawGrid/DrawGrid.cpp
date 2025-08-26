// This file is a part of Nitisa framework
// Copyright © 2019 Nitisa. All rights reserved.
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
	#pragma region Constructor & destructor
		CDrawGrid::CDrawGrid() :
			CCustomDrawGrid(L"DrawGrid")
		{
			setDefaultColumnWidth(50);
			setDefaultRowHeight(50);
			setColumns(5);
			setRows(5);
			setSize(PointF{ 320, 120 });
		}

		CDrawGrid::CDrawGrid(IForm *parent) : CDrawGrid()
		{
			setForm(parent);
		}

		CDrawGrid::CDrawGrid(IControl *parent) : CDrawGrid()
		{
			setParent(parent);
		}
	#pragma endregion
	}
}