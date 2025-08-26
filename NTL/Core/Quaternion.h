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
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Check whether quaternions are equal. Can be used for non-float data types only
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Check whether quaternions aren't equal. Can be used for non-float data types only
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator+(const TQuaternion<TYPE> &q, const TYPE val) // Add quaternion and scalar
	{
		return TQuaternion<TYPE>{ q.X + val, q.Y + val, q.Z + val, q.W + val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator-(const TQuaternion<TYPE> &q, const TYPE val) // Subtract quaternion and scalar
	{
		return TQuaternion<TYPE>{ q.X - val, q.Y - val, q.Z - val, q.W - val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TQuaternion<TYPE> &q, const TYPE val) // Multiply quaternion and scalar
	{
		return TQuaternion<TYPE>{ q.X * val, q.Y * val, q.Z * val, q.W * val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator/(const TQuaternion<TYPE> &q, const TYPE val) // Divide quaternion and scalar
	{
		return TQuaternion<TYPE>{ q.X / val, q.Y / val, q.Z / val, q.W / val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator+(const TYPE val, const TQuaternion<TYPE> &q) // Add scalar and quaternion
	{
		return TQuaternion<TYPE>{ val + q.X, val + q.Y, val + q.Z, val + q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator-(const TYPE val, const TQuaternion<TYPE> &q) // Subtract scalar and quaternion
	{
		return TQuaternion<TYPE>{ val - q.X, val - q.Y, val - q.Z, val - q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator*(const TYPE val, const TQuaternion<TYPE> &q) // Multiply scalar and quaternion
	{
		return TQuaternion<TYPE>{ val * q.X, val * q.Y, val * q.Z, val * q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator/(const TYPE val, const TQuaternion<TYPE> &q) // Divide scalar and quaternion
	{
		return TQuaternion<TYPE>{ val / q.X, val / q.Y, val / q.Z, val / q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator+=(TQuaternion<TYPE> &q, const TYPE val) // Add scalar to quaternion
	{
		q.X += val;
		q.Y += val;
		q.Z += val;
		q.W += val;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator-=(TQuaternion<TYPE> &q, const TYPE val) // Subtract scalar form quaternion
	{
		q.X -= val;
		q.Y -= val;
		q.Z -= val;
		q.W -= val;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator*=(TQuaternion<TYPE> &q, const TYPE val) // Multiply quaternion by scalar
	{
		q.X *= val;
		q.Y *= val;
		q.Z *= val;
		q.W *= val;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator/=(TQuaternion<TYPE> &q, const TYPE val) // Divide quaternion by scalar
	{
		q.X /= val;
		q.Y /= val;
		q.Z /= val;
		q.W /= val;
		return q;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator+(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Add quaternions
	{
		return TQuaternion<TYPE>{ a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator-(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Subtract quaternions
	{
		return TQuaternion<TYPE>{ a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> operator*(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Multiply quaternions(dot product)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator^(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Multiply quaternions(cross product)
	{
		return TQuaternion<TYPE>{
			a.W * b.X + a.X * b.W + a.Y * b.Z - a.Z * b.Y,
			a.W * b.Y + a.Y * b.W + a.Z * b.X - a.X * b.Z,
			a.W * b.Z + a.Z * b.W + a.X * b.Y - a.Y * b.X,
			a.W * b.W - a.X * b.X - a.Y * b.Y - a.Z * b.Z
		};
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator+=(TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Add second quaternion to the first one
	{
		a.X += b.X;
		a.Y += b.Y;
		a.Z += b.Z;
		a.W += b.W;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator-=(TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Subtract second quaternion from the first one
	{
		a.X -= b.X;
		a.Y -= b.Y;
		a.Z -= b.Z;
		a.W -= b.W;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> &operator^=(TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Store cross product of quaternions in the first one
	{
		TYPE x{ a.W * b.X + a.X * b.W + a.Y * b.Z - a.Z * b.Y };
		TYPE y{ a.W * b.Y + a.Y * b.W + a.Z * b.X - a.X * b.Z };
		TYPE z{ a.W * b.Z + a.Z * b.W + a.X * b.Y - a.Y * b.X };
		TYPE w{ a.W * b.W - a.X * b.X - a.Y * b.Y - a.Z * b.Z };
		a.X = x;
		a.Y = y;
		a.Z = z;
		a.W = w;
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> operator-(const TQuaternion<TYPE> &v) // Return quaternion with elements having same value but inversed sign
	{
		return TQuaternion<TYPE>{ -v.X, -v.Y, -v.Z, -v.W };
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Compare whether quaternions are equal
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether quaternions are equal
	{
		return IsEqual<TYPE>(a.X, b.X, tolerance) && IsEqual<TYPE>(a.Y, b.Y, tolerance) && IsEqual<TYPE>(a.Z, b.Z, tolerance) && IsEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Compare whether quaternions aren't equal
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether quaternions aren't equal
	{
		return IsNotEqual<TYPE>(a.X, b.X, tolerance) || IsNotEqual<TYPE>(a.Y, b.Y, tolerance) || IsNotEqual<TYPE>(a.Z, b.Z, tolerance) || IsNotEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TQuaternion<INT>> Round(const TQuaternion<TYPE> &q) // Return quaternion with rounded elements
	{
		return TQuaternion<INT>{ Round<INT, TYPE>(q.X), Round<INT, TYPE>(q.Y), Round<INT, TYPE>(q.Z), Round<INT, TYPE>(q.W) };
	}

	template<class TO, class FROM>
	TQuaternion<TO> Convert(const TQuaternion<FROM> &q) // Convert to quaternion with another data type
	{
		return TQuaternion<TO>{ (TO)q.X, (TO)q.Y, (TO)q.Z, (TO)q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Conjugate(TQuaternion<TYPE> &q) // Conjugate quaternion
	{
		q.X = -q.X;
		q.Y = -q.Y;
		q.Z = -q.Z;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> Conjugated(const TQuaternion<TYPE> &q) // Return conjugated quaternion
	{
		return TQuaternion<TYPE>{ -q.X, -q.Y, -q.Z, q.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Norm(const TQuaternion<TYPE> &q) // Return norm
	{
		return std::sqrt(q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> NormSqr(const TQuaternion<TYPE> &q) // Return square norm
	{
		return q.X * q.X + q.Y * q.Y + q.Z * q.Z + q.W * q.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Normalize(TQuaternion<TYPE> &q) // Normalize quaternion
	{
		TYPE n{ Norm(q) };
		q.X /= n;
		q.Y /= n;
		q.Z /= n;
		q.W /= n;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> Normalized(const TQuaternion<TYPE> &q) // Return normalized quaternion
	{
		TYPE n{ Norm(q) };
		return TQuaternion<TYPE>{ q.X / n, q.Y / n, q.Z / n, q.W / n };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Identity(TQuaternion<TYPE> &q) // Makes identity quaternion
	{
		q.X = 0;
		q.Y = 0;
		q.Z = 0;
		q.W = 1;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, void> Inverse(TQuaternion<TYPE> &q) // Inverse quaternion
	{
		TYPE n{ NormSqr(q) };
		q.X = -q.X / n;
		q.Y = -q.Y / n;
		q.Z = -q.Z / n;
		q.W = q.W / n;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> Inversed(const TQuaternion<TYPE> &q) // Return inversed quaternion
	{
		TYPE n{ NormSqr(q) };
		return TQuaternion<TYPE>{ -q.X / n, -q.Y / n, -q.Z / n, q.W / n };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Angle(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Return angle between quaternions
	{
		return std::acos((a * b) / (Norm<TYPE>(a) * Norm<TYPE>(b)));
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleNormalized(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Return angle between normalized quaternions
	{
		return std::acos(a * b);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleCosine(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Return angle cosine between quaternions
	{
		return (a * b) / (Norm<TYPE>(a) * Norm<TYPE>(b));
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> AngleCosineNormalized(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b) // Return angle cosine between normalized quaternions
	{
		return a * b;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, TQuaternion<TYPE>> Rotate(const TQuaternion<TYPE> &v, const TQuaternion<TYPE> &axis, const TYPE angle) // Return rotated quaternion
	{
		TYPE s{ std::sin(angle / 2) };
		TQuaternion<TYPE> q1{ s * axis.X, s * axis.Y, s * axis.Z, std::cos(angle / 2) };
		TQuaternion<TYPE> q2{ -q1.X, -q1.Y, -q1.Z, q1.W };
		return q1 ^ v ^ q2;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const FLOAT tolerance) // Check whether quaternions are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.X, b.X, tolerance) && Equals<TYPE, FLOAT>(a.Y, b.Y, tolerance) && Equals<TYPE, FLOAT>(a.Z, b.Z, tolerance) && Equals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const TYPE tolerance) // Check whether quaternions are equal using relative comparison
	{
		return Equals<TYPE>(a.X, b.X, tolerance) && Equals<TYPE>(a.Y, b.Y, tolerance) && Equals<TYPE>(a.Z, b.Z, tolerance) && Equals<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const FLOAT tolerance) // Check whether quaternions aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.X, b.X, tolerance) || NotEquals<TYPE, FLOAT>(a.Y, b.Y, tolerance) || NotEquals<TYPE, FLOAT>(a.Z, b.Z, tolerance) || NotEquals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TQuaternion<TYPE> &a, const TQuaternion<TYPE> &b, const TYPE tolerance) // Check whether quaternions aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.X, b.X, tolerance) || NotEquals<TYPE>(a.Y, b.Y, tolerance) || NotEquals<TYPE>(a.Z, b.Z, tolerance) || NotEquals<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> DegToRad(const TQuaternion<TYPE> &deg) // Convert quaternion elements in degrees to radians
	{
		return TQuaternion<TYPE>{ deg.X * Pi<TYPE> / 180, deg.Y * Pi<TYPE> / 180, deg.Z * Pi<TYPE> / 180, deg.W };
	}

	template<class TYPE>
	constexpr std::enable_if_t<std::is_arithmetic_v<TYPE>, TQuaternion<TYPE>> RadToDeg(const TQuaternion<TYPE> &rad) // Convert quaternion elements in radians to degrees
	{
		return TQuaternion<TYPE>{ rad.X * 180 / Pi<TYPE>, rad.Y * 180 / Pi<TYPE>, rad.Z * 180 / Pi<TYPE>, rad.W };
	}
}