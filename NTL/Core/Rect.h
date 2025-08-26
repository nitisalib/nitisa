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
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator==(const TRect<TYPE> &a, const TRect<TYPE> &b) // Check whether rectangles are equal. Can be used for non-float data types only
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> operator!=(const TRect<TYPE> &a, const TRect<TYPE> &b) // Check whether rectangles aren't equal. Can be used for non-float data types only
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator+(const TRect<TYPE> &r, const TYPE val) // Add rect and scalar
	{
		return TRect<TYPE>{ r.X + val, r.Y + val, r.Z + val, r.W + val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator-(const TRect<TYPE> &r, const TYPE val) // Subtract rect and scalar
	{
		return TRect<TYPE>{ r.X - val, r.Y - val, r.Z - val, r.W - val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator*(const TRect<TYPE> &r, const TYPE val) // Multiply rect and scalar
	{
		return TRect<TYPE>{ r.X * val, r.Y * val, r.Z * val, r.W * val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator/(const TRect<TYPE> &r, const TYPE val) // Divide rect and scalar
	{
		return TRect<TYPE>{ r.X / val, r.Y / val, r.Z / val, r.W / val };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator+(const TYPE val, const TRect<TYPE> &r) // Add scalar and rect
	{
		return TRect<TYPE>{ val + r.X, val + r.Y, val + r.Z, val + r.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator-(const TYPE val, const TRect<TYPE> &r) // Subtract scalar and rect
	{
		return TRect<TYPE>{ val - r.X, val - r.Y, val - r.Z, val - r.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator*(const TYPE val, const TRect<TYPE> &r) // Multiply scalar and rect
	{
		return TRect<TYPE>{ val * r.X, val * r.Y, val * r.Z, val * r.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator/(const TYPE val, const TRect<TYPE> &r) // Divide scalar and rect
	{
		return TRect<TYPE>{ val / r.X, val / r.Y, val / r.Z, val / r.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator+=(TRect<TYPE> &r, const TYPE val) // Add scalar to rect
	{
		r.X += val;
		r.Y += val;
		r.Z += val;
		r.W += val;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator-=(TRect<TYPE> &r, const TYPE val) // Subtract scalar from rect
	{
		r.X -= val;
		r.Y -= val;
		r.Z -= val;
		r.W -= val;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator*=(TRect<TYPE> &r, const TYPE val) // Multiply rect by scalar
	{
		r.X *= val;
		r.Y *= val;
		r.Z *= val;
		r.W *= val;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator/=(TRect<TYPE> &r, const TYPE val) // Divide rect by scalar
	{
		r.X /= val;
		r.Y /= val;
		r.Z /= val;
		r.W /= val;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator+(const TRect<TYPE> &r, const TPoint<TYPE> &p) // Return rect shifted by point
	{
		return TRect<TYPE>{ r.X + p.X, r.Y + p.Y, r.Z + p.X, r.W + p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator-(const TRect<TYPE> &r, const TPoint<TYPE> &p) // Return rect shifted by point opposite direction
	{
		return TRect<TYPE>{ r.X - p.X, r.Y - p.Y, r.Z - p.X, r.W - p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator*(const TRect<TYPE> &r, const TPoint<TYPE> &p) // Return rect scaled by point
	{
		return TRect<TYPE>{ r.X * p.X, r.Y * p.Y, r.Z * p.X, r.W * p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator/(const TRect<TYPE> &r, const TPoint<TYPE> &p) // Return rect scaled by inversed point
	{
		return TRect<TYPE>{ r.X / p.X, r.Y / p.Y, r.Z / p.X, r.W / p.Y };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator+=(TRect<TYPE> &r, const TPoint<TYPE> &p) // Shift rect by point
	{
		r.X += p.X;
		r.Y += p.Y;
		r.Z += p.X;
		r.W += p.Y;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator-=(TRect<TYPE> &r, const TPoint<TYPE> &p) // Shift rect by point opposite direction
	{
		r.X -= p.X;
		r.Y -= p.Y;
		r.Z -= p.X;
		r.W -= p.Y;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator*=(TRect<TYPE> &r, const TPoint<TYPE> &p) // Scale rect by point
	{
		r.X *= p.X;
		r.Y *= p.Y;
		r.Z *= p.X;
		r.W *= p.Y;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator/=(TRect<TYPE> &r, const TPoint<TYPE> &p) // Scale rect by inversed point
	{
		r.X /= p.X;
		r.Y /= p.Y;
		r.Z /= p.X;
		r.W /= p.Y;
		return r;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator+(const TRect<TYPE> &a, const TRect<TYPE> &b) // Return intersection of rects
	{
		return TRect<TYPE>{ Min<TYPE>(a.Left, b.Left), Min<TYPE>(a.Top, b.Top), Max<TYPE>(a.Right, b.Right), Max<TYPE>(a.Bottom, b.Bottom) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> operator*(const TRect<TYPE> &a, const TRect<TYPE> &b) // Return bounding rectangle for two rects
	{
		return TRect<TYPE>{ Max<TYPE>(a.Left, b.Left), Max<TYPE>(a.Top, b.Top), Min<TYPE>(a.Right, b.Right), Min<TYPE>(a.Bottom, b.Bottom) };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator+=(TRect<TYPE> &a, const TRect<TYPE> &b) // Makes rect equal to intersection with another one
	{
		a.Left = Min<TYPE>(a.Left, b.Left);
		a.Top = Min<TYPE>(a.Top, b.Top);
		a.Right = Max<TYPE>(a.Right, b.Right);
		a.Bottom = Max<TYPE>(a.Bottom, b.Bottom);
		return a;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TRect<TYPE>> &operator*=(TRect<TYPE> &a, const TRect<TYPE> &b) // Makes rect equal to bounding rectangle of this and another one
	{
		a.Left = Max<TYPE>(a.Left, b.Left);
		a.Top = Max<TYPE>(a.Top, b.Top);
		a.Right = Min<TYPE>(a.Right, b.Right);
		a.Bottom = Min<TYPE>(a.Bottom, b.Bottom);
		return a;
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsEqual(const TRect<TYPE> &a, const TRect<TYPE> &b) // Compare whether rects are equal
	{
		return a.X == b.X && a.Y == b.Y && a.Z == b.Z && a.W == b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEqual(const TRect<TYPE> &a, const TRect<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether rects are equal
	{
		return IsEqual<TYPE>(a.X, b.X, tolerance) && IsEqual<TYPE>(a.Y, b.Y, tolerance) && IsEqual<TYPE>(a.Z, b.Z, tolerance) && IsEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<!std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TRect<TYPE> &a, const TRect<TYPE> &b) // Compare whether rects aren't equal
	{
		return a.X != b.X || a.Y != b.Y || a.Z != b.Z || a.W != b.W;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsNotEqual(const TRect<TYPE> &a, const TRect<TYPE> &b, const TYPE tolerance = Tolerance<TYPE>) // Compare whether rects aren't equal
	{
		return IsNotEqual<TYPE>(a.X, b.X, tolerance) || IsNotEqual<TYPE>(a.Y, b.Y, tolerance) || IsNotEqual<TYPE>(a.Z, b.Z, tolerance) || IsNotEqual<TYPE>(a.W, b.W, tolerance);
	}

	template<class INT, class TYPE>
	std::enable_if_t<std::is_integral_v<INT> && std::is_arithmetic_v<TYPE>, TRect<INT>> Round(const TRect<TYPE> &r) // Return rect with rounded elements
	{
		return TRect<INT>{ Round<INT, TYPE>(r.X), Round<INT, TYPE>(r.Y), Round<INT, TYPE>(r.Z), Round<INT, TYPE>(r.W) };
	}

	template<class TO, class FROM>
	TRect<TO> Convert(const TRect<FROM> &r) // Convert to rect with another data type
	{
		return TRect<TO>{ (TO)r.X, (TO)r.Y, (TO)r.Z, (TO)r.W };
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> IsValid(const TRect<TYPE> &r) // Return whether rect's Right is greater or equal to its Left and Bottom is greater or equal to its Top
	{
		return r.Right >= r.Left && r.Bottom >= r.Top;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsValid(const TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Return whether rect's Right is greater or equal to its Left and Bottom is greater or equal to its Top
	{
		return IsGreaterOrEqual<TYPE>(r.Right, r.Left, tolerance) && IsGreaterOrEqual<TYPE>(r.Bottom, r.Top, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> IsEmpty(const TRect<TYPE> &r) // Return whether rect's Right is equal to its Left and Bottom is equal to its Top
	{
		return r.Right == r.Left && r.Bottom == r.Top;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsEmpty(const TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Return whether rect's Right is equal to its Left and Bottom is equal to its Top
	{
		return IsEqual<TYPE>(r.Right, r.Left, tolerance) && IsEqual<TYPE>(r.Bottom, r.Top, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> IsZero(const TRect<TYPE> &r) // Return whether rect's Right is equal to its Left or Bottom is equal to its Top
	{
		return r.Right == r.Left || r.Bottom == r.Top;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> IsZero(const TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Return whether rect's Right is equal to its Left or Bottom is equal to its Top
	{
		return IsEqual<TYPE>(r.Right, r.Left, tolerance) || IsEqual<TYPE>(r.Bottom, r.Top, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> HasNegative(const TRect<TYPE> &r) // Return whether there is a negative element in the rect
	{
		return r.X < 0 || r.Y < 0 || r.Z < 0 || r.W < 0;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> HasNegative(const TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Return whether there is a negative element in the rect
	{
		return IsNegative<TYPE>(r.X, tolerance) || IsNegative<TYPE>(r.Y, tolerance) || IsNegative<TYPE>(r.Z, tolerance) || IsNegative<TYPE>(r.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> HasPositive(const TRect<TYPE> &r) // Return whether there is a positive element in the rect
	{
		return r.X > 0 || r.Y > 0 || r.Z > 0 || r.W > 0;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> HasPositive(const TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Return whether there is a positive element in the rect
	{
		return IsGreater<TYPE>(r.X, 0, tolerance) || IsGreater<TYPE>(r.Y, 0, tolerance) || IsGreater<TYPE>(r.Z, 0, tolerance) || IsGreater<TYPE>(r.W, 0, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Width(const TRect<TYPE> &r) // Return rect's width
	{
		return r.Right - r.Left;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Height(const TRect<TYPE> &r) // Return rect's height
	{
		return r.Bottom - r.Top;
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TPoint<TYPE>> Size(const TRect<TYPE> &r) // Return rect's size
	{
		return TPoint<TYPE>{ r.Right - r.Left, r.Bottom - r.Top };
	}

	template<class TYPE>
	std::enable_if_t<std::is_arithmetic_v<TYPE>, TYPE> Area(const TRect<TYPE> &r) // Return rect's area(width * height)
	{
		return (r.Right - r.Left) * (r.Bottom - r.Top);
	}

	template<class TYPE>
	std::enable_if_t<std::is_integral_v<TYPE>, bool> Validate(TRect<TYPE> &r) // Makes rect valid(Right is not less then Left and Bottom is not less the Top). Return true if rect was changed
	{
		bool result{ false };
		if (r.Right < r.Left)
		{
			r.Right = r.Left;
			result = true;
		}
		if (r.Bottom < r.Top)
		{
			r.Bottom = r.Top;
			result = true;
		}
		return result;
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Validate(TRect<TYPE> &r, const TYPE tolerance = Tolerance<TYPE>) // Makes rect valid(Right is not less then Left and Bottom is not less the Top). Return true if rect was changed
	{
		bool result{ false };
		if (IsLess<TYPE>(r.Right, r.Left, tolerance))
		{
			r.Right = r.Left;
			result = true;
		}
		if (IsLess<TYPE>(r.Bottom, r.Top, tolerance))
		{
			r.Bottom = r.Top;
			result = true;
		}
		return result;
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> Equals(const TRect<TYPE> &a, const TRect<TYPE> &b, const FLOAT tolerance) // Check whether points are equal using relative comparison
	{
		return Equals<TYPE, FLOAT>(a.X, b.X, tolerance) && Equals<TYPE, FLOAT>(a.Y, b.Y, tolerance) && Equals<TYPE, FLOAT>(a.Z, b.Z, tolerance) && Equals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> Equals(const TRect<TYPE> &a, const TRect<TYPE> &b, const TYPE tolerance) // Check whether points are equal using relative comparison
	{
		return Equals<TYPE>(a.X, b.X, tolerance) && Equals<TYPE>(a.Y, b.Y, tolerance) && Equals<TYPE>(a.Z, b.Z, tolerance) && Equals<TYPE>(a.W, b.W, tolerance);
	}

	template<class TYPE, class FLOAT>
	std::enable_if_t<std::is_integral_v<TYPE> && std::is_floating_point_v<FLOAT>, bool> NotEquals(const TRect<TYPE> &a, const TRect<TYPE> &b, const FLOAT tolerance) // Check whether points aren't equal using relative comparison
	{
		return NotEquals<TYPE, FLOAT>(a.X, b.X, tolerance) || NotEquals<TYPE, FLOAT>(a.Y, b.Y, tolerance) || NotEquals<TYPE, FLOAT>(a.Z, b.Z, tolerance) || NotEquals<TYPE, FLOAT>(a.W, b.W, tolerance);
	}

	template<class TYPE>
	std::enable_if_t<std::is_floating_point_v<TYPE>, bool> NotEquals(const TRect<TYPE> &a, const TRect<TYPE> &b, const TYPE tolerance) // Check whether points aren't equal using relative comparison
	{
		return NotEquals<TYPE>(a.X, b.X, tolerance) || NotEquals<TYPE>(a.Y, b.Y, tolerance) || NotEquals<TYPE>(a.Z, b.Z, tolerance) || NotEquals<TYPE>(a.W, b.W, tolerance);
	}
}