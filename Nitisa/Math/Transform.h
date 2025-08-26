// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/RotateOrder.h"
#include "../Core/Strings.h"
#include "../Core/TransformOrder.h"
#include "../Core/Variant.h"
#include "Vec3f.h"
#include <iostream>

namespace nitisa
{
	struct Transform
	{
		union
		{
			struct
			{
				float Tx; // Translate X
				float Ty; // Translate Y
				float Tz; // Translate Z
				float Sx; // Scale X
				float Sy; // Scale Y
				float Sz; // Scale Z
				float Rx; // Rotate X
				float Ry; // Rotate Y
				float Rz; // Rotate Z
			};
			struct
			{
				Vec3f Translation;
				Vec3f Scaling;
				Vec3f Rotation;
			};
		};
		nitisa::RotateOrder RotateOrder; // Rotate order
		nitisa::TransformOrder TransformOrder; // Transform order
	};

	std::wostream &operator<<(std::wostream &stream, const Transform &a);

	bool IsEqual(const Transform &a, const Transform &b, const float tolerance = ntl::Tolerance<float>); // Check if transformations are equal
	bool IsNotEqual(const Transform &a, const Transform &b, const float tolerance = ntl::Tolerance<float>); // Check if transformations are not equal
	bool Equals(const Transform &a, const Transform &b, const float relative_tolerance = ntl::RelativeTolerance<float>); // Check if transformations are equal
	bool NotEquals(const Transform &a, const Transform &b, const float relative_tolerance = ntl::RelativeTolerance<float>); // Check if transformations are not equal
	String ToString(const Transform &value);
	Variant ToVariant(const Transform &value);
	void FromVariant(const Variant &value, Transform &dest);
	String AsSourceCode(const Transform &a);
}