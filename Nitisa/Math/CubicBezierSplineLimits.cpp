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
	bool Equals(const CubicBezierSplineLimits &a, const CubicBezierSplineLimits &b, const float relative_tolerance)
	{
		return a.isY == b.isY && Equals(a.Spline1, b.Spline1, relative_tolerance) && Equals(a.Spline2, b.Spline2, relative_tolerance);
	}

	bool NotEquals(const CubicBezierSplineLimits &a, const CubicBezierSplineLimits &b, const float relative_tolerance)
	{
		return a.isY != b.isY || NotEquals(a.Spline1, b.Spline1, relative_tolerance) || NotEquals(a.Spline2, b.Spline2, relative_tolerance);
	}
}