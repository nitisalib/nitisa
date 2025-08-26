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
#pragma region Rect
	int Rect::operator[](const int index) const
	{
		return Data[index];
	}

	int &Rect::operator[](const int index)
	{
		return Data[index];
	}

	Rect::operator RectF() const
	{
		return RectF{ (float)Left, (float)Top, (float)Right, (float)Bottom };
	}

	bool Rect::is_valid() const
	{
		return Right >= Left && Bottom >= Top;
	}

	bool Rect::is_empty() const
	{
		return Right == Left && Bottom == Top;
	}

	bool Rect::is_zero() const
	{
		return Right == Left || Bottom == Top;
	}

	bool Rect::has_negative() const
	{
		return Left < 0 || Top < 0 || Right < 0 || Bottom < 0;
	}

	bool Rect::has_positive() const
	{
		return Left > 0 || Top > 0 || Right > 0 || Bottom > 0;
	}
	
	bool Rect::has_area() const
	{
		return Right > Left && Bottom > Top;
	}

	int Rect::width() const
	{
		return Right - Left;
	}

	int Rect::height() const
	{
		return Bottom - Top;
	}

	void Rect::validate()
	{
		if (Right < Left)
			Right = Left;
		if (Bottom < Top)
			Bottom = Top;
	}

	bool Rect::is_inside(const Point &p) const
	{
		return p.X >= Left && p.X < Right && p.Y >= Top && p.Y < Bottom;
	}

	bool Rect::is_outside(const Point &p) const
	{
		return p.X < Left || p.X >= Right || p.Y < Top || p.Y >= Bottom;
	}
#pragma endregion

#pragma region Operators
	bool operator==(const Rect &a, const Rect &b)
	{
		return a.Left == b.Left && a.Top == b.Top && a.Right == b.Right && a.Bottom == b.Bottom;
	}

	bool operator!=(const Rect &a, const Rect &b)
	{
		return a.Left != b.Left || a.Top != b.Top || a.Right != b.Right || a.Bottom != b.Bottom;
	}

	Rect operator+(const Rect &a, const int value)
	{
		return Rect{ a.Left + value, a.Top + value, a.Right + value, a.Bottom + value };
	}

	Rect operator-(const Rect &a, const int value)
	{
		return Rect{ a.Left - value, a.Top - value, a.Right - value, a.Bottom - value };
	}

	Rect operator/(const Rect &a, const int value)
	{
		return Rect{ a.Left / value, a.Top / value, a.Right / value, a.Bottom / value };
	}

	Rect operator*(const Rect &a, const int value)
	{
		return Rect{ a.Left * value, a.Top * value, a.Right * value, a.Bottom * value };
	}

	Rect operator+(const int value, const Rect &a)
	{
		return Rect{ value + a.Left, value + a.Top, value + a.Right, value + a.Bottom };
	}

	Rect operator-(const int value, const Rect &a)
	{
		return Rect{ value - a.Left, value - a.Top, value - a.Right, value - a.Bottom };
	}

	Rect operator/(const int value, const Rect &a)
	{
		return Rect{ value / a.Left, value / a.Top, value / a.Right, value / a.Bottom };
	}

	Rect operator*(const int value, const Rect &a)
	{
		return Rect{ value * a.Left, value * a.Top, value * a.Right, value * a.Bottom };
	}

	Rect &operator+=(Rect &a, const int value)
	{
		a.Left += value;
		a.Top += value;
		a.Right += value;
		a.Bottom += value;
		return a;
	}

	Rect &operator-=(Rect &a, const int value)
	{
		a.Left -= value;
		a.Top -= value;
		a.Right -= value;
		a.Bottom -= value;
		return a;
	}

	Rect &operator/=(Rect &a, const int value)
	{
		a.Left /= value;
		a.Top /= value;
		a.Right /= value;
		a.Bottom /= value;
		return a;
	}

	Rect &operator*=(Rect &a, const int value)
	{
		a.Left *= value;
		a.Top *= value;
		a.Right *= value;
		a.Bottom *= value;
		return a;
	}

	Rect operator+(const Rect &a, const Rect &b)
	{
		return Rect{ ntl::Min<int>(a.Left, b.Left), ntl::Min<int>(a.Top, b.Top), ntl::Max<int>(a.Right, b.Right), ntl::Max<int>(a.Bottom, b.Bottom) };
	}

	Rect operator*(const Rect &a, const Rect &b)
	{
		return Rect{ ntl::Max<int>(a.Left, b.Left), ntl::Max<int>(a.Top, b.Top), ntl::Min<int>(a.Right, b.Right), ntl::Min<int>(a.Bottom, b.Bottom) };
	}

	Rect &operator+=(Rect &a, const Rect &b)
	{
		a.Left = ntl::Min<int>(a.Left, b.Left);
		a.Top = ntl::Min<int>(a.Top, b.Top);
		a.Right = ntl::Max<int>(a.Right, b.Right);
		a.Bottom = ntl::Max<int>(a.Bottom, b.Bottom);
		return a;
	}

	Rect &operator*=(Rect &a, const Rect &b)
	{
		a.Left = ntl::Max<int>(a.Left, b.Left);
		a.Top = ntl::Max<int>(a.Top, b.Top);
		a.Right = ntl::Min<int>(a.Right, b.Right);
		a.Bottom = ntl::Min<int>(a.Bottom, b.Bottom);
		return a;
	}

	Rect operator+(const Rect &a, const Point &shift)
	{
		return Rect{ a.Left + shift.X, a.Top + shift.Y, a.Right + shift.X, a.Bottom + shift.Y };
	}

	Rect operator-(const Rect &a, const Point &shift)
	{
		return Rect{ a.Left - shift.X, a.Top - shift.Y, a.Right - shift.X, a.Bottom - shift.Y };
	}

	Rect operator*(const Rect &a, const Point &shift)
	{
		return Rect{ a.Left * shift.X, a.Top * shift.Y, a.Right * shift.X, a.Bottom * shift.Y };
	}

	Rect &operator+=(Rect &a, const Point &shift)
	{
		a.Left += shift.X;
		a.Top += shift.Y;
		a.Right += shift.X;
		a.Bottom += shift.Y;
		return a;
	}

	Rect &operator-=(Rect &a, const Point &shift)
	{
		a.Left -= shift.X;
		a.Top -= shift.Y;
		a.Right -= shift.X;
		a.Bottom -= shift.Y;
		return a;
	}

	Rect &operator*=(Rect &a, const Point &shift)
	{
		a.Left *= shift.X;
		a.Top *= shift.Y;
		a.Right *= shift.X;
		a.Bottom *= shift.Y;
		return a;
	}

	std::wostream &operator<<(std::wostream &stream, const Rect &a)
	{
		stream << L"{ " << a.Left << L", " << a.Top << L", " << a.Right << L", " << a.Bottom << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const Rect &a)
	{
		return L"Rect{ " + ToString(a.Left) + L", " + ToString(a.Top) + L", " + ToString(a.Right) + L", " + ToString(a.Bottom) + L" }";
	}

	String ToString(const Rect &value)
	{
		return ToString(value.Left) + L", " + ToString(value.Top) + L", " + ToString(value.Right) + L", " + ToString(value.Bottom);
	}

	Variant ToVariant(const Rect &value)
	{
		Variant result;
		result.push_back((Variant)value.Left);
		result.push_back((Variant)value.Top);
		result.push_back((Variant)value.Right);
		result.push_back((Variant)value.Bottom);
		return result;
	}

	void FromVariant(const Variant &value, Rect &dest)
	{
		dest = Rect{ (int)value.get(0), (int)value.get(1), (int)value.get(2), (int)value.get(3) };
	}

	Rect Round(const RectF &a)
	{
		return Rect{ ntl::Round<int>(a.Left), ntl::Round<int>(a.Top), ntl::Round<int>(a.Right), ntl::Round<int>(a.Bottom) };
	}
#pragma endregion
}