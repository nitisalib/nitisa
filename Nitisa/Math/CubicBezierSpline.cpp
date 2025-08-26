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
	bool Equals(const CubicBezierSpline &a, const CubicBezierSpline &b, const float relative_tolerance)
	{
		return
			Equals(a.P1, b.P1, relative_tolerance) &&
			Equals(a.C1, b.C1, relative_tolerance) &&
			Equals(a.C2, b.C2, relative_tolerance) &&
			Equals(a.P2, b.P2, relative_tolerance);
	}

	bool NotEquals(const CubicBezierSpline &a, const CubicBezierSpline &b, const float relative_tolerance)
	{
		return
			NotEquals(a.P1, b.P1, relative_tolerance) ||
			NotEquals(a.C1, b.C1, relative_tolerance) ||
			NotEquals(a.C2, b.C2, relative_tolerance) ||
			NotEquals(a.P2, b.P2, relative_tolerance);
	}
}