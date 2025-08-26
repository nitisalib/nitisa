// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	namespace charts
	{
		enum class LineInterpolationPosition
		{
			Before, // Point is draw before horizontal line
			Middle, // Point is drawn at the middle of horizontal line
			After // Point is draw after horizontal line
		};
	}
}