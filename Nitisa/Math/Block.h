// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/PointLocation.h"
#include "RectF.h"

namespace nitisa
{
	struct Block
	{
		RectF Rect; // Block rectangle in local coordinates(bounding rectangle)
		RectF Border; // Border widths
		RectF Radius; // Corner radiuses(left-top, right-top, right-bottom, left-bottom)
		PointLocation Location; // Which part of block should be used
	};

	bool Equals(const Block &a, const Block &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	bool NotEquals(const Block &a, const Block &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
}