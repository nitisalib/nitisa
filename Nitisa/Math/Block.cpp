// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	bool Equals(const Block &a, const Block &b, const float relative_tolerance)
	{
		return
			a.Location == b.Location &&
			Equals(a.Rect, b.Rect, relative_tolerance) &&
			Equals(a.Border, b.Border, relative_tolerance) &&
			Equals(a.Radius, b.Radius, relative_tolerance);
	}

	bool NotEquals(const Block &a, const Block &b, const float relative_tolerance)
	{
		return
			a.Location != b.Location ||
			NotEquals(a.Rect, b.Rect, relative_tolerance) ||
			NotEquals(a.Border, b.Border, relative_tolerance) ||
			NotEquals(a.Radius, b.Radius, relative_tolerance);
	}
}