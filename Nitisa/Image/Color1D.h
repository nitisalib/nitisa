// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "NTL/Core/Utils.h"
#include "Color.h"

namespace nitisa
{
	struct Color1D // Gradient point
	{
		float Position; // Position in range 0..1
		nitisa::Color Color; // Point color
	};

	inline bool IsEqual(const Color1D &a, const Color1D &b, const float tolerance = ntl::Tolerance<float>)
	{
		return ntl::IsEqual<float>(a.Position, b.Position, tolerance) && a.Color == b.Color;
	}

	inline bool IsNotEqual(const Color1D &a, const Color1D &b, const float tolerance = ntl::Tolerance<float>)
	{
		return ntl::IsNotEqual<float>(a.Position, b.Position, tolerance) || a.Color != b.Color;
	}
}