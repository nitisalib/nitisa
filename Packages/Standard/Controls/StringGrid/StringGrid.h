// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "CustomStringGrid.h"

namespace nitisa
{
	class IControl;
	class IForm;

	namespace standard
	{
		class CStringGrid :public CCustomStringGrid
		{
		public:
			CStringGrid(); // Create
			CStringGrid(IForm *parent); // Create and place onto the form
			CStringGrid(IControl *parent); // Create and place onto the parent control
		};
	}
}