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
#pragma region Point
	int Point::operator[](const int index) const
	{
		return Data[index];
	}

	int &Point::operator[](const int index)
	{
		return Data[index];
	}

	Point::operator PointF() const
	{
		return PointF{ (float)X, (float)Y };
	}
#pragma endregion

#pragma region Operators
	bool operator==(const Point &a, const Point &b)
	{
		return a.X == b.X && a.Y == b.Y;
	}

	bool operator!=(const Point &a, const Point &b)
	{
		return a.X != b.X || a.Y != b.Y;
	}

	Point operator+(const Point &a, const int value)
	{
		return Point{ a.X + value, a.Y + value };
	}

	Point operator-(const Point &a, const int value)
	{
		return Point{ a.X - value, a.Y - value };
	}

	Point operator/(const Point &a, const int value)
	{
		return Point{ a.X / value, a.Y / value };
	}

	Point operator*(const Point &a, const int value)
	{
		return Point{ a.X * value, a.Y * value };
	}

	Point operator+(const int value, const Point &a)
	{
		return Point{ value + a.X, value + a.Y };
	}

	Point operator-(const int value, const Point &a)
	{
		return Point{ value - a.X, value - a.Y };
	}

	Point operator/(const int value, const Point &a)
	{
		return Point{ value / a.X, value / a.Y };
	}

	Point operator*(const int value, const Point &a)
	{
		return Point{ value * a.X, value * a.Y };
	}

	Point &operator+=(Point &a, const int value)
	{
		a.X += value;
		a.Y += value;
		return a;
	}

	Point &operator-=(Point &a, const int value)
	{
		a.X -= value;
		a.Y -= value;
		return a;
	}

	Point &operator/=(Point &a, const int value)
	{
		a.X /= value;
		a.Y /= value;
		return a;
	}

	Point &operator*=(Point &a, const int value)
	{
		a.X *= value;
		a.Y *= value;
		return a;
	}

	Point operator+(const Point &a, const Point &b)
	{
		return Point{ a.X + b.X, a.Y + b.Y };
	}

	Point operator-(const Point &a, const Point &b)
	{
		return Point{ a.X - b.X, a.Y - b.Y };
	}

	Point operator*(const Point &a, const Point &b)
	{
		return Point{ a.X * b.X, a.Y * b.Y };
	}

	Point operator/(const Point &a, const Point &b)
	{
		return Point{ a.X / b.X, a.Y / b.Y };
	}

	Point &operator+=(Point &a, const Point &b)
	{
		a.X += b.X;
		a.Y += b.Y;
		return a;
	}

	Point &operator-=(Point &a, const Point &b)
	{
		a.X -= b.X;
		a.Y -= b.Y;
		return a;
	}

	Point &operator*=(Point &a, const Point &b)
	{
		a.X *= b.X;
		a.Y *= b.Y;
		return a;
	}

	Point &operator/=(Point &a, const Point &b)
	{
		a.X /= b.X;
		a.Y /= b.Y;
		return a;
	}

	Point operator-(const Point &a)
	{
		return Point{ -a.X, -a.Y };
	}

	std::wostream &operator<<(std::wostream &stream, const Point &a)
	{
		stream << L"{ " << a.X << L", " << a.Y << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const Point &a)
	{
		return L"Point{ " + ToString(a.X) + L", " + ToString(a.Y) + L" }";
	}

	String ToString(const Point &value)
	{
		return ToString(value.X) + L", " + ToString(value.Y);
	}

	Variant ToVariant(const Point &value)
	{
		Variant result;
		result.push_back((Variant)value.X);
		result.push_back((Variant)value.Y);
		return result;
	}

	void FromVariant(const Variant &value, Point &dest)
	{
		dest = Point{ (int)value.get(0), (int)value.get(1) };
	}

	Point Round(const PointF &a)
	{
		return Point{ ntl::Round<int>(a.X), ntl::Round<int>(a.Y) };
	}
#pragma endregion
}