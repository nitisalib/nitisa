// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "CubicBezierSpline.h"

namespace nitisa
{
	struct CubicBezierSplineLimits
	{
		bool isY; // Apply to Y direction if true
		CubicBezierSpline Spline1;
		CubicBezierSpline Spline2;
	};

	bool Equals(const CubicBezierSplineLimits &a, const CubicBezierSplineLimits &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	bool NotEquals(const CubicBezierSplineLimits &a, const CubicBezierSplineLimits &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
}