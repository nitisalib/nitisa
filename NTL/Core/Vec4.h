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
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Check whether vectors are equal. Can be used for non-float data types only
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Check whether vectors aren't equal. Can be used for non-float data types only
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator+(const TVec4<TYPE> &v, const TYPE val) // Add vector and scalar
	{
		return TVec4<TYPE>{ v.X + val, v.Y + val, v.Z + val, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator-(const TVec4<TYPE> &v, const TYPE val) // Subtract vector and scalar
	{
		return TVec4<TYPE>{ v.X - val, v.Y - val, v.Z - val, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TVec4<TYPE> &v, const TYPE val) // Multiply vector and scalar
	{
		return TVec4<TYPE>{ v.X * val, v.Y * val, v.Z * val, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator/(const TVec4<TYPE> &v, const TYPE val) // Divide vector and scalar
	{
		return TVec4<TYPE>{ v.X / val, v.Y / val, v.Z / val, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator+(const TYPE val, const TVec4<TYPE> &v) // Add scalar and vector
	{
		return TVec4<TYPE>{ val + v.X, val + v.Y, val + v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator-(const TYPE val, const TVec4<TYPE> &v) // Subtract scalar and vector
	{
		return TVec4<TYPE>{ val - v.X, val - v.Y, val - v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator*(const TYPE val, const TVec4<TYPE> &v) // Multiply scalar and vector
	{
		return TVec4<TYPE>{ val * v.X, val * v.Y, val * v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator/(const TYPE val, const TVec4<TYPE> &v) // Divide scalar and vector
	{
		return TVec4<TYPE>{ val / v.X, val / v.Y, val / v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator+=(TVec4<TYPE> &v, const TYPE val) // Add scalar to vector
	{
		v.X += val;
		v.Y += val;
		v.Z += val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator-=(TVec4<TYPE> &v, const TYPE val) // Subtract scalar from vector
	{
		v.X -= val;
		v.Y -= val;
		v.Z -= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator*=(TVec4<TYPE> &v, const TYPE val) // Multiply vector by scalar
	{
		v.X *= val;
		v.Y *= val;
		v.Z *= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator/=(TVec4<TYPE> &v, const TYPE val) // Divide vector by scalar
	{
		v.X /= val;
		v.Y /= val;
		v.Z /= val;
		return v;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator+(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Add vectors
	{
		return TVec4<TYPE>{ a.X + b.X, a.Y + b.Y, a.Z + b.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator-(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Subtract vectors
	{
		return TVec4<TYPE>{ a.X - b.X, a.Y - b.Y, a.Z - b.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> operator*(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Multiply vectors(dot product)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator/(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Divide vectors
	{
		return TVec4<TYPE>{ a.X / b.X, a.Y / b.Y, a.Z / b.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator^(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Multiply vectors(cross product)
	{
		return TVec4<TYPE>{ a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator+=(TVec4<TYPE> &a, const TVec4<TYPE> &b) // Add vector to vector
	{
		a.X += b.X;
		a.Y += b.Y;
		a.Z += b.Z;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator-=(TVec4<TYPE> &a, const TVec4<TYPE> &b) // Subtract vector from vector
	{
		a.X -= b.X;
		a.Y -= b.Y;
		a.Z -= b.Z;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator/=(TVec4<TYPE> &a, const TVec4<TYPE> &b) // Divide vector by vector
	{
		a.X /= b.X;
		a.Y /= b.Y;
		a.Z /= b.Z;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> &operator^=(TVec4<TYPE> &a, const TVec4<TYPE> &b) // Store cross product in the first vector
	{
		TYPE A{ a.Y * b.Z - a.Z * b.Y };
		TYPE B{ a.Z * b.X - a.X * b.Z };
		TYPE C{ a.X * b.Y - a.Y * b.X };
		a.X = A;
		a.Y = B;
		a.Z = C;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> operator-(const TVec4<TYPE> &v) // Return inversed vector
	{
		return TVec4<TYPE>{ -v.X, -v.Y, -v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Compare whether vectors are equal
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether vectors are equal
	{
		return IsEqual<TYPE>(a.X, b.X, tolerance) && IsEqual<TYPE>(a.Y, b.Y, tolerance) && IsEqual<TYPE>(a.Z, b.Z, tolerance) && IsEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Compare whether vectors aren't equal
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether vectors aren't equal
	{
		return IsNotEqual<TYPE>(a.X, b.X, tolerance) || IsNotEqual<TYPE>(a.Y, b.Y, tolerance) || IsNotEqual<TYPE>(a.Z, b.Z, tolerance) || IsNotEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TVec4<INT>> Round(const TVec4<TYPE> &v) // Return vector with rounded elements
	{
		return TVec4<INT>{ Round<INT, TYPE>(v.X), Round<INT, TYPE>(v.Y), Round<INT, TYPE>(v.Z), 1 };
	}

	template<class TO, class FROM>
	TVec4<TO> Convert(const TVec4<FROM> &v) // Convert to vector with another data type
	{
		return TVec4<TO>{ (TO)v.X, (TO)v.Y, (TO)v.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Mix(const TVec4<TYPE> &x, const TVec4<TYPE> &y, const TYPE a) // Mix vectors
	{
		return x + a * (y - x);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Clamp(const TVec4<TYPE> &v, const TYPE min_val, const TYPE max_val) // Return vector clamped to range
	{
		return TVec4<TYPE>{ Clamp<TYPE>(v.X, min_val, max_val), Clamp<TYPE>(v.Y, min_val, max_val), Clamp<TYPE>(v.Z, min_val, max_val), 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Clamp(const TVec4<TYPE> &v, const TVec4<TYPE> &min_val, const TVec4<TYPE> &max_val) // Return vector clamped to range
	{
		return TVec4<TYPE>{ Clamp<TYPE>(v.X, min_val.X, max_val.X), Clamp<TYPE>(v.Y, min_val.Y, max_val.Y), Clamp<TYPE>(v.Z, min_val.Z, max_val.Z), 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Step(const TVec4<TYPE> &v, const TVec4<TYPE> &edge) // Calculate step
	{
		return TVec4<TYPE>{ (v.X < edge.X) ? 0 : 1, (v.Y < edge.Y) ? 0 : 1, (v.Z < edge.Z) ? 0 : 1, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Smoothstep(const TVec4<TYPE> &v, const TVec4<TYPE> &edge0, const TVec4<TYPE> &edge1) // Calculate smooth step
	{
		return TVec4<TYPE>{ Smoothstep<TYPE>(v.X, edge0.X, edge1.X), Smoothstep<TYPE>(v.Y, edge0.Y, edge1.Y), Smoothstep<TYPE>(v.Z, edge0.Z, edge1.Z), 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Norm(const TVec4<TYPE> &v) // Return norm
	{
		return std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormSqr(const TVec4<TYPE> &v) // Return norm*norm
	{
		return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Distance(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return distance between points
	{
		return std::sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) + (a.Z - b.Z) * (a.Z - b.Z));
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> DistanceSqr(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return distance*distance between points
	{
		return (a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) + (a.Z - b.Z) * (a.Z - b.Z);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Normalize(TVec4<TYPE> &v) // Normalize vector
	{
		TYPE n{ Norm(v) };
		v.X /= n;
		v.Y /= n;
		v.Z /= n;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Normalized(const TVec4<TYPE> &v) // Return normalized vector
	{
		TYPE n{ Norm(v) };
		return TVec4<TYPE>{ v.X / n, v.Y / n, v.Z / n, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Reflect(TVec4<TYPE> &v, const TVec4<TYPE> &normal) // Reflect vector around normal
	{
		TYPE k{ 2 * (v.X * normal.X + v.Y * normal.Y + v.Z * normal.Z) };
		v.X -= k * normal.X;
		v.Y -= k * normal.Y;
		v.Z -= k * normal.Z;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Reflected(const TVec4<TYPE> &v, const TVec4<TYPE> &normal) // Return reflected around normal vector
	{
		TYPE k{ 2 * (v.X * normal.X + v.Y * normal.Y + v.Z * normal.Z) };
		return TVec4<TYPE>{ v.X - k * normal.X, v.Y - k * normal.Y, v.Z - k * normal.Z, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Refract(TVec4<TYPE> &v, const TVec4<TYPE> &normal, const TYPE eta) // Refract vector around normal
	{
		TYPE d{ v.X * normal.X + v.Y * normal.Y + v.Z * normal.Z }, k{ 1 - eta * eta * (1 - d * d) };
		if (k < 0)
		{
			v.X = 0;
			v.Y = 0;
			v.Z = 0;
		}
		else
		{
			k = eta * d + std::sqrt(k);
			v.X = v.X * eta - normal.X * k;
			v.Y = v.Y * eta - normal.Y * k;
			v.Z = v.Z * eta - normal.Z * k;
		}
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> Refracted(const TVec4<TYPE> &v, const TVec4<TYPE> &normal, const TYPE eta) // Return refracted around normal vector
	{
		TYPE d{ v.X * normal.X + v.Y * normal.Y + v.Z * normal.Z }, k{ 1 - eta * eta * (1 - d * d) };
		if (k < 0)
			return TVec4<TYPE>{ 0, 0, 0, 1 };
		k = eta * d + std::sqrt(k);
		return TVec4<TYPE>{ v.X * eta - normal.X * k, v.Y * eta - normal.Y * k, v.Z * eta - normal.Z * k, 1 };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Angle(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return angle between vectors
	{
		return std::acos((a * b) / (Norm<TYPE>(a) * Norm<TYPE>(b)));
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleNormalized(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return angle between normalized vectors
	{
		return std::acos(a * b);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleCosine(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return angle cosine between vectors
	{
		return (a * b) / (Norm<TYPE>(a) * Norm<TYPE>(b));
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleCosineNormalized(const TVec4<TYPE> &a, const TVec4<TYPE> &b) // Return angle cosine between normalized vectors
	{
		return a * b;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const FLOAT tolerance) // Check whether vectors are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.X, b.X, tolerance) && Equals<TYPE, FLOAT>(a.Y, b.Y, tolerance) && Equals<TYPE, FLOAT>(a.Z, b.Z, tolerance) && Equals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const TYPE tolerance) // Check whether vectors are equal using relative comparison
	{
		return Equals<TYPE>(a.X, b.X, tolerance) && Equals<TYPE>(a.Y, b.Y, tolerance) && Equals<TYPE>(a.Z, b.Z, tolerance) && Equals<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const FLOAT tolerance) // Check whether vectors aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.X, b.X, tolerance) || NotEquals<TYPE, FLOAT>(a.Y, b.Y, tolerance) || NotEquals<TYPE, FLOAT>(a.Z, b.Z, tolerance) || NotEquals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TVec4<TYPE> &a, const TVec4<TYPE> &b, const TYPE tolerance) // Check whether vectors aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.X, b.X, tolerance) || NotEquals<TYPE>(a.Y, b.Y, tolerance) || NotEquals<TYPE>(a.Z, b.Z, tolerance) || NotEquals<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> DegToRad(const TVec4<TYPE> &deg) // Convert vector elements in degrees to radians
	{
		return TVec4<TYPE>{ deg.X * Pi<TYPE> / 180, deg.Y * Pi<TYPE> / 180, deg.Z * Pi<TYPE> / 180, 1 };
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TVec4<TYPE>> RadToDeg(const TVec4<TYPE> &rad) // Convert vector elements in radians to degrees
	{
		return TVec4<TYPE>{ rad.X * 180 / Pi<TYPE>, rad.Y * 180 / Pi<TYPE>, rad.Z * 180 / Pi<TYPE>, 1 };
	}
}