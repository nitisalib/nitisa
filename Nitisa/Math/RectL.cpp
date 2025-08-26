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
#pragma region RectL
	long long RectL::operator[](const int index) const
	{
		return Data[index];
	}

	long long &RectL::operator[](const int index)
	{
		return Data[index];
	}

	RectL::operator RectD() const
	{
		return RectD{ (double)Left, (double)Top, (double)Right, (double)Bottom };
	}

	bool RectL::is_valid() const
	{
		return Right >= Left && Bottom >= Top;
	}

	bool RectL::is_empty() const
	{
		return Right == Left && Bottom == Top;
	}

	bool RectL::is_zero() const
	{
		return Right == Left || Bottom == Top;
	}

	bool RectL::has_negative() const
	{
		return Left < 0 || Top < 0 || Right < 0 || Bottom < 0;
	}

	bool RectL::has_positive() const
	{
		return Left > 0 || Top > 0 || Right > 0 || Bottom > 0;
	}

	bool RectL::has_area() const
	{
		return Right > Left && Bottom > Top;
	}

	long long RectL::width() const
	{
		return Right - Left;
	}

	long long RectL::height() const
	{
		return Bottom - Top;
	}

	void RectL::validate()
	{
		if (Right < Left)
			Right = Left;
		if (Bottom < Top)
			Bottom = Top;
	}

	bool RectL::is_inside(const PointL &p) const
	{
		return p.X >= Left && p.X < Right && p.Y >= Top && p.Y < Bottom;
	}

	bool RectL::is_outside(const PointL &p) const
	{
		return p.X < Left || p.X >= Right || p.Y < Top || p.Y >= Bottom;
	}
#pragma endregion

#pragma region Operators
	bool operator==(const RectL &a, const RectL &b)
	{
		return a.Left == b.Left && a.Top == b.Top && a.Right == b.Right && a.Bottom == b.Bottom;
	}

	bool operator!=(const RectL &a, const RectL &b)
	{
		return a.Left != b.Left || a.Top != b.Top || a.Right != b.Right || a.Bottom != b.Bottom;
	}

	RectL operator+(const RectL &a, const long long value)
	{
		return RectL{ a.Left + value, a.Top + value, a.Right + value, a.Bottom + value };
	}

	RectL operator-(const RectL &a, const long long value)
	{
		return RectL{ a.Left - value, a.Top - value, a.Right - value, a.Bottom - value };
	}

	RectL operator/(const RectL &a, const long long value)
	{
		return RectL{ a.Left / value, a.Top / value, a.Right / value, a.Bottom / value };
	}

	RectL operator*(const RectL &a, const long long value)
	{
		return RectL{ a.Left * value, a.Top * value, a.Right * value, a.Bottom * value };
	}

	RectL operator+(const long long value, const RectL &a)
	{
		return RectL{ value + a.Left, value + a.Top, value + a.Right, value + a.Bottom };
	}

	RectL operator-(const long long value, const RectL &a)
	{
		return RectL{ value - a.Left, value - a.Top, value - a.Right, value - a.Bottom };
	}

	RectL operator/(const long long value, const RectL &a)
	{
		return RectL{ value / a.Left, value / a.Top, value / a.Right, value / a.Bottom };
	}

	RectL operator*(const long long value, const RectL &a)
	{
		return RectL{ value * a.Left, value * a.Top, value * a.Right, value * a.Bottom };
	}

	RectL &operator+=(RectL &a, const long long value)
	{
		a.Left += value;
		a.Top += value;
		a.Right += value;
		a.Bottom += value;
		return a;
	}

	RectL &operator-=(RectL &a, const long long value)
	{
		a.Left -= value;
		a.Top -= value;
		a.Right -= value;
		a.Bottom -= value;
		return a;
	}

	RectL &operator/=(RectL &a, const long long value)
	{
		a.Left /= value;
		a.Top /= value;
		a.Right /= value;
		a.Bottom /= value;
		return a;
	}

	RectL &operator*=(RectL &a, const long long value)
	{
		a.Left *= value;
		a.Top *= value;
		a.Right *= value;
		a.Bottom *= value;
		return a;
	}

	RectL operator+(const RectL &a, const RectL &b)
	{
		return RectL{ ntl::Min<long long>(a.Left, b.Left), ntl::Min<long long>(a.Top, b.Top), ntl::Max<long long>(a.Right, b.Right), ntl::Max<long long>(a.Bottom, b.Bottom) };
	}

	RectL operator*(const RectL &a, const RectL &b)
	{
		return RectL{ ntl::Max<long long>(a.Left, b.Left), ntl::Max<long long>(a.Top, b.Top), ntl::Min<long long>(a.Right, b.Right), ntl::Min<long long>(a.Bottom, b.Bottom) };
	}

	RectL &operator+=(RectL &a, const RectL &b)
	{
		a.Left = ntl::Min<long long>(a.Left, b.Left);
		a.Top = ntl::Min<long long>(a.Top, b.Top);
		a.Right = ntl::Max<long long>(a.Right, b.Right);
		a.Bottom = ntl::Max<long long>(a.Bottom, b.Bottom);
		return a;
	}

	RectL &operator*=(RectL &a, const RectL &b)
	{
		a.Left = ntl::Max<long long>(a.Left, b.Left);
		a.Top = ntl::Max<long long>(a.Top, b.Top);
		a.Right = ntl::Min<long long>(a.Right, b.Right);
		a.Bottom = ntl::Min<long long>(a.Bottom, b.Bottom);
		return a;
	}

	RectL operator+(const RectL &a, const PointL &shift)
	{
		return RectL{ a.Left + shift.X, a.Top + shift.Y, a.Right + shift.X, a.Bottom + shift.Y };
	}

	RectL operator-(const RectL &a, const PointL &shift)
	{
		return RectL{ a.Left - shift.X, a.Top - shift.Y, a.Right - shift.X, a.Bottom - shift.Y };
	}

	RectL operator*(const RectL &a, const PointL &shift)
	{
		return RectL{ a.Left * shift.X, a.Top * shift.Y, a.Right * shift.X, a.Bottom * shift.Y };
	}

	RectL &operator+=(RectL &a, const PointL &shift)
	{
		a.Left += shift.X;
		a.Top += shift.Y;
		a.Right += shift.X;
		a.Bottom += shift.Y;
		return a;
	}

	RectL &operator-=(RectL &a, const PointL &shift)
	{
		a.Left -= shift.X;
		a.Top -= shift.Y;
		a.Right -= shift.X;
		a.Bottom -= shift.Y;
		return a;
	}

	RectL &operator*=(RectL &a, const PointL &shift)
	{
		a.Left *= shift.X;
		a.Top *= shift.Y;
		a.Right *= shift.X;
		a.Bottom *= shift.Y;
		return a;
	}

	std::wostream &operator<<(std::wostream &stream, const RectL &a)
	{
		stream << L"{ " << a.Left << L", " << a.Top << L", " << a.Right << L", " << a.Bottom << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const RectL &a)
	{
		return L"RectL{ " + ToString(a.Left) + L", " + ToString(a.Top) + L", " + ToString(a.Right) + L", " + ToString(a.Bottom) + L" }";
	}

	String ToString(const RectL &value)
	{
		return ToString(value.Left) + L", " + ToString(value.Top) + L", " + ToString(value.Right) + L", " + ToString(value.Bottom);
	}

	Variant ToVariant(const RectL &value)
	{
		Variant result;
		result.push_back((Variant)ToString(value.Left));
		result.push_back((Variant)ToString(value.Top));
		result.push_back((Variant)ToString(value.Right));
		result.push_back((Variant)ToString(value.Bottom));
		return result;
	}

	void FromVariant(const Variant &value, RectL &dest)
	{
		dest = RectL{ StringToInt64((String)value.get(0)), StringToInt64((String)value.get(1)), StringToInt64((String)value.get(2)), StringToInt64((String)value.get(3)) };
	}

	RectL Round(const RectD &a)
	{
		return RectL{ ntl::Round<long long>(a.Left), ntl::Round<long long>(a.Top), ntl::Round<long long>(a.Right), ntl::Round<long long>(a.Bottom) };
	}
#pragma endregion
}