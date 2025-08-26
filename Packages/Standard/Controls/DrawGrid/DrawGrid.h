// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "CustomDrawGrid.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CDrawGrid :public CCustomDrawGrid
		{
		public:
			CDrawGrid(); // Create
			CDrawGrid(IForm *parent); // Create and put onto a form
			CDrawGrid(IControl *parent); // Create and put onto a parent control
		};
	}
}