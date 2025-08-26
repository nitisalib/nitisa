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
		CStringGrid::CStringGrid() :
			CCustomStringGrid(L"StringGrid")
		{
			setColumns(5);
			setRows(5);
			setSize(PointF{ 320, 120 });
		}

		CStringGrid::CStringGrid(IForm *parent) :CStringGrid()
		{
			setForm(parent);
		}

		CStringGrid::CStringGrid(IControl *parent) : CStringGrid()
		{
			setParent(parent);
		}
	#pragma endregion
	}
}