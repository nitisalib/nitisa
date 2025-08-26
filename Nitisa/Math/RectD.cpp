// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
#pragma region RectD
	double RectD::operator[](const int index) const
	{
		return Data[index];
	}

	double &RectD::operator[](const int index)
	{
		return Data[index];
	}

	bool RectD::is_valid(const double tolerance) const
	{
		return ntl::IsGreaterOrEqual<double>(Right, Left, tolerance) && ntl::IsGreaterOrEqual<double>(Bottom, Top, tolerance);
	}

	bool RectD::is_empty(const double tolerance) const
	{
		return ntl::IsEqual<double>(Right, Left, tolerance) && ntl::IsEqual<double>(Bottom, Top, tolerance);
	}

	bool RectD::is_zero(const double tolerance) const
	{
		return ntl::IsEqual<double>(Right, Left, tolerance) || ntl::IsEqual<double>(Bottom, Top, tolerance);
	}

	bool RectD::has_negative(const double tolerance) const
	{
		return ntl::IsLess<double>(Left, 0, tolerance) || ntl::IsLess<double>(Top, 0, tolerance) || ntl::IsLess<double>(Right, 0, tolerance) || ntl::IsLess<double>(Bottom, 0, tolerance);
	}

	bool RectD::has_positive(const double tolerance) const
	{
		return ntl::IsGreater<double>(Left, 0, tolerance) || ntl::IsGreater<double>(Top, 0, tolerance) || ntl::IsGreater<double>(Right, 0, tolerance) || ntl::IsGreater<double>(Bottom, 0, tolerance);
	}

	bool RectD::has_area(const double tolerance) const
	{
		return ntl::IsGreater<double>(Right, Left, tolerance) && ntl::IsGreater<double>(Bottom, Top, tolerance);
	}

	double RectD::width() const
	{
		return Right - Left;
	}

	double RectD::height() const
	{
		return Bottom - Top;
	}

	void RectD::validate(const double tolerance)
	{
		if (ntl::IsLess<double>(Right, Left, tolerance))
			Right = Left;
		if (ntl::IsLess<double>(Bottom, Top, tolerance))
			Bottom = Top;
	}

	bool RectD::is_inside(const PointD &p, const double tolerance) const
	{
		return
			ntl::IsGreaterOrEqual<double>(p.X, Left, tolerance) &&
			ntl::IsLess<double>(p.X, Right, tolerance) &&
			ntl::IsGreaterOrEqual<double>(p.Y, Top, tolerance) &&
			ntl::IsLess<double>(p.Y, Bottom, tolerance);
	}

	bool RectD::is_outside(const PointD &p, const double tolerance) const
	{
		return
			ntl::IsLess<double>(p.X, Left, tolerance) ||
			ntl::IsGreaterOrEqual<double>(p.X, Right, tolerance) ||
			ntl::IsLess<double>(p.Y, Top, tolerance) ||
			ntl::IsGreaterOrEqual<double>(p.Y, Bottom, tolerance);
	}
#pragma endregion

#pragma region Operators
	RectD operator+(const RectD &a, const double value)
	{
		return RectD{ a.Left + value, a.Top + value, a.Right + value, a.Bottom + value };
	}

	RectD operator-(const RectD &a, const double value)
	{
		return RectD{ a.Left - value, a.Top - value, a.Right - value, a.Bottom - value };
	}

	RectD operator/(const RectD &a, const double value)
	{
		return RectD{ a.Left / value, a.Top / value, a.Right / value, a.Bottom / value };
	}

	RectD operator*(const RectD &a, const double value)
	{
		return RectD{ a.Left * value, a.Top * value, a.Right * value, a.Bottom * value };
	}

	RectD operator+(const double value, const RectD &a)
	{
		return RectD{ value + a.Left, value + a.Top, value + a.Right, value + a.Bottom };
	}

	RectD operator-(const double value, const RectD &a)
	{
		return RectD{ value - a.Left, value - a.Top, value - a.Right, value - a.Bottom };
	}

	RectD operator/(const double value, const RectD &a)
	{
		return RectD{ value / a.Left, value / a.Top, value / a.Right, value / a.Bottom };
	}

	RectD operator*(const double value, const RectD &a)
	{
		return RectD{ value * a.Left, value * a.Top, value * a.Right, value * a.Bottom };
	}

	RectD &operator+=(RectD &a, const double value)
	{
		a.Left += value;
		a.Top += value;
		a.Right += value;
		a.Bottom += value;
		return a;
	}

	RectD &operator-=(RectD &a, const double value)
	{
		a.Left -= value;
		a.Top -= value;
		a.Right -= value;
		a.Bottom -= value;
		return a;
	}

	RectD &operator/=(RectD &a, const double value)
	{
		a.Left /= value;
		a.Top /= value;
		a.Right /= value;
		a.Bottom /= value;
		return a;
	}

	RectD &operator*=(RectD &a, const double value)
	{
		a.Left *= value;
		a.Top *= value;
		a.Right *= value;
		a.Bottom *= value;
		return a;
	}

	RectD operator+(const RectD &a, const RectD &b)
	{
		return RectD{ ntl::Min<double>(a.Left, b.Left), ntl::Min<double>(a.Top, b.Top), ntl::Max<double>(a.Right, b.Right), ntl::Max<double>(a.Bottom, b.Bottom) };
	}

	RectD operator*(const RectD &a, const RectD &b)
	{
		return RectD{ ntl::Max<double>(a.Left, b.Left), ntl::Max<double>(a.Top, b.Top), ntl::Min<double>(a.Right, b.Right), ntl::Min<double>(a.Bottom, b.Bottom) };
	}

	RectD &operator+=(RectD &a, const RectD &b)
	{
		a.Left = ntl::Min<double>(a.Left, b.Left);
		a.Top = ntl::Min<double>(a.Top, b.Top);
		a.Right = ntl::Max<double>(a.Right, b.Right);
		a.Bottom = ntl::Max<double>(a.Bottom, b.Bottom);
		return a;
	}

	RectD &operator*=(RectD &a, const RectD &b)
	{
		a.Left = ntl::Max<double>(a.Left, b.Left);
		a.Top = ntl::Max<double>(a.Top, b.Top);
		a.Right = ntl::Min<double>(a.Right, b.Right);
		a.Bottom = ntl::Min<double>(a.Bottom, b.Bottom);
		return a;
	}

	RectD operator+(const RectD &a, const PointD &shift)
	{
		return RectD{ a.Left + shift.X, a.Top + shift.Y, a.Right + shift.X, a.Bottom + shift.Y };
	}

	RectD operator-(const RectD &a, const PointD &shift)
	{
		return RectD{ a.Left - shift.X, a.Top - shift.Y, a.Right - shift.X, a.Bottom - shift.Y };
	}

	RectD operator*(const RectD &a, const PointD &shift)
	{
		return RectD{ a.Left * shift.X, a.Top * shift.Y, a.Right * shift.X, a.Bottom * shift.Y };
	}

	RectD &operator+=(RectD &a, const PointD &shift)
	{
		a.Left += shift.X;
		a.Top += shift.Y;
		a.Right += shift.X;
		a.Bottom += shift.Y;
		return a;
	}

	RectD &operator-=(RectD &a, const PointD &shift)
	{
		a.Left -= shift.X;
		a.Top -= shift.Y;
		a.Right -= shift.X;
		a.Bottom -= shift.Y;
		return a;
	}

	RectD &operator*=(RectD &a, const PointD &shift)
	{
		a.Left *= shift.X;
		a.Top *= shift.Y;
		a.Right *= shift.X;
		a.Bottom *= shift.Y;
		return a;
	}

	std::wostream &operator<<(std::wostream &stream, const RectD &a)
	{
		stream << L"{ " << ToString(a.Left) << L", " << ToString(a.Top) << L", " << ToString(a.Right) << L", " << ToString(a.Bottom) << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	bool IsEqual(const RectD &a, const RectD &b, const double tolerance)
	{
		return
			ntl::Abs<double>(b.Left - a.Left) < tolerance &&
			ntl::Abs<double>(b.Top - a.Top) < tolerance &&
			ntl::Abs<double>(b.Right - a.Right) < tolerance &&
			ntl::Abs<double>(b.Bottom - a.Bottom) < tolerance;
	}

	bool IsNotEqual(const RectD &a, const RectD &b, const double tolerance)
	{
		return
			ntl::Abs<double>(b.Left - a.Left) >= tolerance ||
			ntl::Abs<double>(b.Top - a.Top) >= tolerance ||
			ntl::Abs<double>(b.Right - a.Right) >= tolerance ||
			ntl::Abs<double>(b.Bottom - a.Bottom) >= tolerance;
	}

	bool Equals(const RectD &a, const RectD &b, const double relative_tolerance)
	{
		return
			ntl::Equals<double>(a.Left, b.Left, relative_tolerance) &&
			ntl::Equals<double>(a.Top, b.Top, relative_tolerance) &&
			ntl::Equals<double>(a.Right, b.Right, relative_tolerance) &&
			ntl::Equals<double>(a.Bottom, b.Bottom, relative_tolerance);
	}

	bool NotEquals(const RectD &a, const RectD &b, const double relative_tolerance)
	{
		return
			ntl::NotEquals<double>(a.Left, b.Left, relative_tolerance) ||
			ntl::NotEquals<double>(a.Top, b.Top, relative_tolerance) ||
			ntl::NotEquals<double>(a.Right, b.Right, relative_tolerance) ||
			ntl::NotEquals<double>(a.Bottom, b.Bottom, relative_tolerance);
	}

	String AsSourceCode(const RectD &a)
	{
		return L"RectD{ " + AsSourceCode(a.Left) + L", " + AsSourceCode(a.Top) + L", " + AsSourceCode(a.Right) + L", " + AsSourceCode(a.Bottom) + L" }";
	}

	String ToString(const RectD &value)
	{
		return ToStringCompact(value.Left) + L", " + ToStringCompact(value.Top) + L", " + ToStringCompact(value.Right) + L", " + ToStringCompact(value.Bottom);
	}

	Variant ToVariant(const RectD &value)
	{
		Variant result;
		result.push_back((Variant)ToString(value.Left));
		result.push_back((Variant)ToString(value.Top));
		result.push_back((Variant)ToString(value.Right));
		result.push_back((Variant)ToString(value.Bottom));
		return result;
	}

	void FromVariant(const Variant &value, RectD &dest)
	{
		dest = RectD{ StringToDouble((String)value.get(0)), StringToDouble((String)value.get(1)), StringToDouble((String)value.get(2)), StringToDouble((String)value.get(3)) };
	}
#pragma endregion
}