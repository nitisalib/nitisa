// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "PointF.h"

namespace nitisa
{
	struct CubicBezierSpline // Describe cubic bezier spline
	{
		PointF P1; // Start point
		PointF C1; // First control point
		PointF C2; // Second control point
		PointF P2; // End point
	};

	bool Equals(const CubicBezierSpline &a, const CubicBezierSpline &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	bool NotEquals(const CubicBezierSpline &a, const CubicBezierSpline &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
}