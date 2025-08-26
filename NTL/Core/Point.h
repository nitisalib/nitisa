// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Types.h"

namespace ntl
{
	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Check whether points are equal. Can be used for non-float data types only
	{
		return a.X == b.X && a.Y == b.Y;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Check whether points aren't equal. Can be used for non-float data types only
	{
		return a.X != b.X || a.Y != b.Y;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator+(const TPoint<TYPE> &p, const TYPE val) // Add point and scalar
	{
		return TPoint<TYPE>{ p.X + val, p.Y + val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator-(const TPoint<TYPE> &p, const TYPE val) // Subtract point and scalar
	{
		return TPoint<TYPE>{ p.X - val, p.Y - val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator*(const TPoint<TYPE> &p, const TYPE val) // Multiply point and scalar
	{
		return TPoint<TYPE>{ p.X * val, p.Y * val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator/(const TPoint<TYPE> &p, const TYPE val) // Divide point and scalar
	{
		return TPoint<TYPE>{ p.X / val, p.Y / val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator+(const TYPE val, const TPoint<TYPE> &p) // Add scalar and point
	{
		return TPoint<TYPE>{ val + p.X, val + p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator-(const TYPE val, const TPoint<TYPE> &p) // Subtract scalar and point
	{
		return TPoint<TYPE>{ val - p.X, val - p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator*(const TYPE val, const TPoint<TYPE> &p) // Multiply scalar and point
	{
		return TPoint<TYPE>{ val * p.X, val * p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator/(const TYPE val, const TPoint<TYPE> &p) // Divide scalar and point
	{
		return TPoint<TYPE>{ val / p.X, val / p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator+=(TPoint<TYPE> &p, const TYPE val) // Add scalar to point
	{
		p.X += val;
		p.Y += val;
		return p;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator-=(TPoint<TYPE> &p, const TYPE val) // Subtract scalar from point
	{
		p.X -= val;
		p.Y -= val;
		return p;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator*=(TPoint<TYPE> &p, const TYPE val) // Multiply point by scalar
	{
		p.X *= val;
		p.Y *= val;
		return p;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator/=(TPoint<TYPE> &p, const TYPE val) // Divide point by scalar
	{
		p.X /= val;
		p.Y /= val;
		return p;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator+(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Add points
	{
		return TPoint<TYPE>{ a.X + b.X, a.Y + b.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator-(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Subtract points
	{
		return TPoint<TYPE>{ a.X - b.X, a.Y - b.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator*(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Multiply points
	{
		return TPoint<TYPE>{ a.X * b.X, a.Y * b.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> operator/(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Divide points
	{
		return TPoint<TYPE>{ a.X / b.X, a.Y / b.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator+=(TPoint<TYPE> &a, const TPoint<TYPE> &b) // Add point to point
	{
		a.X += b.X;
		a.Y += b.Y;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator-=(TPoint<TYPE> &a, const TPoint<TYPE> &b) // Subtract point from point
	{
		a.X -= b.X;
		a.Y -= b.Y;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator*=(TPoint<TYPE> &a, const TPoint<TYPE> &b) // Multiply point by point
	{
		a.X *= b.X;
		a.Y *= b.Y;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> &operator/=(TPoint<TYPE> &a, const TPoint<TYPE> &b) // Divide point by point
	{
		a.X /= b.X;
		a.Y /= b.Y;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Compare whether points are equal
	{
		return a.X == b.X && a.Y == b.Y;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether points are equal
	{
		return IsEqual<TYPE>(a.X, b.X, tolerance) && IsEqual<TYPE>(a.Y, b.Y, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPoint<TYPE> &a, const TPoint<TYPE> &b) // Compare whether points aren't equal
	{
		return a.X != b.X || a.Y != b.Y;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether points aren't equal
	{
		return IsNotEqual<TYPE>(a.X, b.X, tolerance) || IsNotEqual<TYPE>(a.Y, b.Y, tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TPoint<INT>> Round(const TPoint<TYPE> &p) // Return point with rounded elements
	{
		return TPoint<INT>{ Round<INT, TYPE>(p.X), Round<INT, TYPE>(p.Y) };
	}

	template<class TO, class FROM>
	TPoint<TO> Convert(const TPoint<FROM> &p) // Convert to point with another data type
	{
		return TPoint<TO>{ (TO)p.X, (TO)p.Y };
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const FLOAT tolerance) // Check whether points are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.X, b.X, tolerance) && Equals<TYPE, FLOAT>(a.Y, b.Y, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const TYPE tolerance) // Check whether points are equal using relative comparison
	{
		return Equals<TYPE>(a.X, b.X, tolerance) && Equals<TYPE>(a.Y, b.Y, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const FLOAT tolerance) // Check whether points aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.X, b.X, tolerance) || NotEquals<TYPE, FLOAT>(a.Y, b.Y, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TPoint<TYPE> &a, const TPoint<TYPE> &b, const TYPE tolerance) // Check whether points aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.X, b.X, tolerance) || NotEquals<TYPE>(a.Y, b.Y, tolerance);
	}
}