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
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Check whether vectors are equal. Can be used for non-float data types only
	{
		return a.X == b.X;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Check whether vectors aren't equal. Can be used for non-float data types only
	{
		return a.X != b.X;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator+(const TVec1<TYPE> &v, const TYPE val) // Add vector and scalar
	{
		return TVec1<TYPE>{ v.X + val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator-(const TVec1<TYPE> &v, const TYPE val) // Subtract vector and scalar
	{
		return TVec1<TYPE>{ v.X - val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator*(const TVec1<TYPE> &v, const TYPE val) // Multiply vector and scalar
	{
		return TVec1<TYPE>{ v.X * val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator/(const TVec1<TYPE> &v, const TYPE val) // Divide vector and scalar
	{
		return TVec1<TYPE>{ v.X / val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator+(const TYPE val, const TVec1<TYPE> &v) // Add scalar and vector
	{
		return TVec1<TYPE>{ val + v.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator-(const TYPE val, const TVec1<TYPE> &v) // Subtract scalar and vector
	{
		return TVec1<TYPE>{ val - v.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator*(const TYPE val, const TVec1<TYPE> &v) // Multiply scalar and vector
	{
		return TVec1<TYPE>{ val * v.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator/(const TYPE val, const TVec1<TYPE> &v) // Divide scalar and vector
	{
		return TVec1<TYPE>{ val / v.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator+=(TVec1<TYPE> &v, const TYPE val) // Add scalar to vector
	{
		v.X += val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator-=(TVec1<TYPE> &v, const TYPE val) // Subtract scalar from vector
	{
		v.X -= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator*=(TVec1<TYPE> &v, const TYPE val) // Multiply vector by scalar
	{
		v.X *= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator/=(TVec1<TYPE> &v, const TYPE val) // Divide vector by scalar
	{
		v.X /= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator+(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Add vectors
	{
		return TVec1<TYPE>{ a.X + b.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator-(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Subtract vectors
	{
		return TVec1<TYPE>{ a.X - b.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> operator*(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Multiply vectors(dot product)
	{
		return a.X * b.X;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator/(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Divide vectors
	{
		return TVec1<TYPE>{ a.X / b.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator+=(TVec1<TYPE> &a, const TVec1<TYPE> &b) // Add vector to vector
	{
		a.X += b.X;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator-=(TVec1<TYPE> &a, const TVec1<TYPE> &b) // Subtract vector from vector
	{
		a.X -= b.X;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> &operator/=(TVec1<TYPE> &a, const TVec1<TYPE> &b) // Divide vector by vector
	{
		a.X /= b.X;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> operator-(const TVec1<TYPE> &v) // Return inversed vector
	{
		return TVec1<TYPE>{ -v.X };
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Compare whether vectors are equal
	{
		return a.X == b.X;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether vectors are equal
	{
		return IsEqual<TYPE>(a.X, b.X, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Compare whether vectors aren't equal
	{
		return a.X != b.X;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether vectors aren't equal
	{
		return IsNotEqual<TYPE>(a.X, b.X, tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TVec1<INT>> Round(const TVec1<TYPE> &v) // Return vector with rounded elements
	{
		return TVec1<INT>{ Round<INT, TYPE>(v.X) };
	}

	template<class TO, class FROM>
	TVec1<TO> Convert(const TVec1<FROM> &v) // Convert to vector with another data type
	{
		return TVec1<TO>{ (TO)v.X };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> Clamp(const TVec1<TYPE> &v, const TYPE min_val, const TYPE max_val) // Return vector clamped to range
	{
		return TVec1<TYPE>{ Clamp<TYPE>(v.X, min_val, max_val) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> Clamp(const TVec1<TYPE> &v, const TVec1<TYPE> &min_val, const TVec1<TYPE> &max_val) // Return vector clamped to range
	{
		return TVec1<TYPE>{ Clamp<TYPE>(v.X, min_val.X, max_val.X) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> Step(const TVec1<TYPE> &v, const TVec1<TYPE> &edge) // Calculate step
	{
		return TVec1<TYPE>{ (v.X < edge.X) ? 0 : 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> Smoothstep(const TVec1<TYPE> &v, const TVec1<TYPE> &edge0, const TVec1<TYPE> &edge1) // Calculate smooth step
	{
		return TVec1<TYPE>{ Smoothstep<TYPE>(v.X, edge0.X, edge1.X) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Norm(const TVec1<TYPE> &v) // Return norm
	{
		return Abs<TYPE>(v.X);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormSqr(const TVec1<TYPE> &v) // Return norm*norm
	{
		return v.X * v.X;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Distance(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Return distance between points
	{
		return Abs<TYPE>(a.X - b.X);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> DistanceSqr(const TVec1<TYPE> &a, const TVec1<TYPE> &b) // Return distance*distance between points
	{
		return (a.X - b.X) * (a.X - b.X);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const FLOAT tolerance) // Check whether vectors are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.X, b.X, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const TYPE tolerance) // Check whether vectors are equal using relative comparison
	{
		return Equals<TYPE>(a.X, b.X, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const FLOAT tolerance) // Check whether vectors aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.X, b.X, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TVec1<TYPE> &a, const TVec1<TYPE> &b, const TYPE tolerance) // Check whether vectors aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.X, b.X, tolerance);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> DegToRad(const TVec1<TYPE> &deg) // Convert vector elements in degrees to radians
	{
		return TVec1<TYPE>{ deg.X * Pi<TYPE> / 180 };
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec1<TYPE>> RadToDeg(const TVec1<TYPE> &rad) // Convert vector elements in radians to degrees
	{
		return TVec1<TYPE>{ rad.X * 180 / Pi<TYPE> };
	}
}