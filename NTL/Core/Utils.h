// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Consts.h"
#include <cmath>

namespace ntl
{
	template<class TYPE>
	constexpr TYPE Min(const TYPE a, const TYPE b) // Return minimum of two values
	{
		return a > b ? b : a;
	}

	template<class TYPE, class ... ARGS>
	constexpr TYPE Min(const TYPE a, const TYPE b, const ARGS ... other) // Return minimum of three and more values
	{
		if (a < b)
			return Min<TYPE>(a, (TYPE)other ...);
		return Min<TYPE>(b, (TYPE)other ...);
	}

	template<class TYPE>
	constexpr TYPE Max(const TYPE a, const TYPE b) // Return maximum of two values
	{
		return a < b ? b : a;
	}

	template<class TYPE, class ... ARGS>
	constexpr TYPE Max(const TYPE a, const TYPE b, const ARGS ... other) // Return maximum of three and more values
	{
		if (a > b)
			return Max<TYPE>(a, (TYPE)other ...);
		return Max<TYPE>(b, (TYPE)other ...);
	}

	template<class TYPE>
	constexpr void Swap(TYPE &a, TYPE &b) // Exchange arguments' values
	{
		TYPE c{ a };
		a = b;
		b = c;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_signed_v<TYPE>, int> Sign(const TYPE value) // Return sign of argument. -1 means value is negative. 0 means value equals to zero. 1 mean value is positive
	{
		return (value < 0) ? -1 : ((value > 0) ? 1 : 0);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_unsigned_v<TYPE>, int> Sign(const TYPE value) // Return sign of argument. 0 means value equals to zero. 1 mean value is positive
	{
		return (value > 0) ? 1 : 0;
	}

	template<class INT, class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<INT> && std::is_integral_v<TYPE>, INT> Round(const TYPE value) // Return rounded value
	{
		return (INT)value;
	}

	template<class INT, class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<INT> && std::is_floating_point_v<TYPE>, INT> Round(const TYPE value) // Return rounded value
	{
		return (value >= 0) ? INT(value + (TYPE)0.5) : INT(value - (TYPE)0.5);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_signed_v<TYPE>, TYPE> Abs(const TYPE value) // Return absolute value of the argument
	{
		return value < 0 ? (-value) : value;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_unsigned_v<TYPE>, TYPE> Abs(const TYPE value) // Return absolute value of the argument
	{
		return value;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> DegToRad(const TYPE deg) // Convert degrees to radians
	{
		return deg * Pi<TYPE> / 180;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> RadToDeg(const TYPE rad) // Convert radians to degrees
	{
		return rad * 180 / Pi<TYPE>;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Mix(const TYPE x1, const TYPE x2, const TYPE a) // Mix arguments
	{
		return x1 + a * (x2 - x1);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Clamp(const TYPE x, const TYPE min_val, const TYPE max_val) // Return x if it's between min_val and max_val. Return min_val if x is less than min_val. Return max_val if x is greater than max_val
	{
		return Max<TYPE>(min_val, Min<TYPE>(max_val, x));
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Step(const TYPE x, const TYPE edge) // Calculate step function. Return 0 if x is less than edge. Return 1 otherwise
	{
		return (x < edge) ? 0 : 1;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Smoothstep(const TYPE x, const TYPE edge0, const TYPE edge1) // Calculate smooth step function
	{
		TYPE t{ Clamp<TYPE>((x - edge0) / (edge1 - edge0), 0, 1) };
		return t * t * (3 - 2 * t);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsLess(const TYPE a, const TYPE b) // Check whether the first argument is less than the second one
	{
		return a < b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsLess(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether the first argument is less than the second one. For float values. Uses absolute comparison
	{
		return a < b - tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsLessOrEqual(const TYPE a, const TYPE b) // Check whether the first argument is less or equal to the second one
	{
		return a <= b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsLessOrEqual(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether the first argument is less or equal to the second one. For float values. Uses absolute comparison
	{
		return a <= b + tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsGreater(const TYPE a, const TYPE b) // Check whether the first argument is greater than the second one
	{
		return a > b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsGreater(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether the first argument is greater than the second one. For float values. Uses absolute comparison
	{
		return a > b + tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsGreaterOrEqual(const TYPE a, const TYPE b) // Check whether the first argument is greater or equal to the second one
	{
		return a >= b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsGreaterOrEqual(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether the first argument is greater or equal to the second one. For float values. Uses absolute comparison
	{
		return a >= b - tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TYPE a, const TYPE b) // Check whether arguments are equal
	{
		return a == b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether arguments are equal. For float values. Uses absolute comparison
	{
		return Abs<TYPE>(b - a) < tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TYPE a, const TYPE b) // Check whether arguments aren't equal
	{
		return a != b;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TYPE a, const TYPE b, const TYPE tolerance = Tolerance<TYPE>) // Check whether arguments aren't equal. For float values. Uses absolute comparison
	{
		return Abs<TYPE>(b - a) >= tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE> && std::is_signed_v<TYPE>, bool> IsNegative(const TYPE a) // Check whether argument is negative
	{
		return a < 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE>, bool> IsNegative(const TYPE a) // Check whether argument is negative
	{
		return false;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNegative(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument is negative. For float values. Uses absolute comparison
	{
		return a < -tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsNotNegative(const TYPE a) // Check whether argument isn't negative
	{
		return a >= 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotNegative(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument isn't negative. For float values. Uses absolute comparison
	{
		return a >= -tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsPositive(const TYPE a) // Check whether argument is positive(>= 0)
	{
		return a >= 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsPositive(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument is positive(>= 0). For float values. Uses absolute comparison
	{
		return a >= -tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE> && std::is_signed_v<TYPE>, bool> IsNotPositive(const TYPE a) // Check whether argument isn't positive(< 0)
	{
		return a < 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE> && std::is_unsigned_v<TYPE>, bool> IsNotPositive(const TYPE a) // Check whether argument isn't positive(< 0)
	{
		return false;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotPositive(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument isn't positive(< 0). For float values. Uses absolute comparison
	{
		return a < -tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsZero(const TYPE a) // Check whether argument is zero
	{
		return a == 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsZero(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument is zero. For float values. Uses absolute comparison
	{
		return a > -tolerance && a <= tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsNotZero(const TYPE a) // Check whether argument isn't zero
	{
		return a != 0;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotZero(const TYPE a, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument isn't zero. For float values. Uses absolute comparison
	{
		return a < -tolerance || a >= tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsBetween(const TYPE a, const TYPE min, const TYPE max) // Check whether argument is between min and max
	{
		return a >= min && a <= max;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsBetween(const TYPE a, const TYPE min, const TYPE max, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument is between min and max. For float values. Uses absolute comparison
	{
		return a >= min - tolerance && a < max + tolerance;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_integral_v<TYPE>, bool> IsNotBetween(const TYPE a, const TYPE min, const TYPE max) // Check whether argument isn't between min and max
	{
		return a < min || a > max;
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotBetween(const TYPE a, const TYPE min, const TYPE max, const TYPE tolerance = Tolerance<TYPE>) // Check whether argument isn't between min and max. For float values. Uses absolute comparison
	{
		return a < min - tolerance || a >= max + tolerance;
	}

	template<class FLOAT, class TYPE>
	std::enable_if_t<std::is_floating_point_v<FLOAT> && std::is_arithmetic_v<TYPE>, FLOAT> Difference(const TYPE a, const TYPE b) // Return relative difference between arguments
	{
		if (a == b)
			return 0;
		if (a == 0)
			return (FLOAT)Abs<TYPE>(b);
		if (b == 0)
			return (FLOAT)Abs<TYPE>(a);
		return (FLOAT)Abs<TYPE>(a - b) / (FLOAT)Max<TYPE>(Abs<TYPE>(a), Abs<TYPE>(b));
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TYPE a, const TYPE b, const FLOAT relative_tolerance) // Check whether the first argument equals to the second one. Uses relative comparison of float values
	{
		return Difference<FLOAT, TYPE>(a, b) < relative_tolerance;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TYPE a, const TYPE b, const TYPE relative_tolerance) // Check whether the first argument equals to the second one. Uses relative comparison of float values
	{
		return Difference<TYPE, TYPE>(a, b) < relative_tolerance;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TYPE a, const TYPE b, const FLOAT relative_tolerance) // Check whether the first argument isn't equal to the second one. Uses relative comparison of float values
	{
		return Difference<FLOAT, TYPE>(a, b) >= relative_tolerance;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TYPE a, const TYPE b, const TYPE relative_tolerance) // Check whether the first argument isn't equal to the second one. Uses relative comparison of float values
	{
		return Difference<TYPE, TYPE>(a, b) >= relative_tolerance;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Less(const TYPE a, const TYPE b, const FLOAT relative_tolerance) // Check whether the first argument is less than the second one. Uses relative comparison of float values
	{
		return NotEquals<FLOAT>(a, b, relative_tolerance) && a < b;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Less(const TYPE a, const TYPE b, const TYPE relative_tolerance) // Check whether the first argument is less than the second one. Uses relative comparison of float values
	{
		return NotEquals<TYPE>(a, b, relative_tolerance) && a < b;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Greater(const TYPE a, const TYPE b, const FLOAT relative_tolerance) // Check whether the first argument is greater than the second one. Uses relative comparison of float values
	{
		return NotEquals<FLOAT>(a, b, relative_tolerance) && a > b;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Greater(const TYPE a, const TYPE b, const TYPE relative_tolerance) // Check whether the first argument is greater than the second one. Uses relative comparison of float values
	{
		return NotEquals<TYPE>(a, b, relative_tolerance) && a > b;
	}

	// Return angle(in radians) between x, y and coordinate system passing through central point assuming Y - axis is from bottom to top, X - axis is from left to right, and angle is
	// measured from X axis to Y - axis(angle 0 means the point is on the X axis and x is positive; angle PI / 2 means the point is on the Y axis and y is positive; and so on)
	template<class TYPE>
	typename std::enable_if_t<std::is_floating_point_v<TYPE>, TYPE> Angle(const TYPE x, const TYPE y, const TYPE center_x, const TYPE center_y)
	{
		if (x > center_x)
		{
			if (y > center_y)
				return std::acos((x - center_x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			if (y < center_y)
				return 2 * Pi<TYPE> - std::acos((x - center_x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			return 0;
		}
		if (x < center_x)
		{
			if (y > center_y)
				return Pi<TYPE> - std::acos((center_x - x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			if (y < center_y)
				return Pi<TYPE> + std::acos((center_x - x) / std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)));
			return Pi<TYPE>;
		}
		if (y > center_y)
			return Pi<TYPE> / 2;
		if (y < center_y)
			return (TYPE)1.5 * Pi<TYPE>;
		return 0;
	}
}