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
#pragma region PointL
	long long PointL::operator[](const int index) const
	{
		return Data[index];
	}

	long long &PointL::operator[](const int index)
	{
		return Data[index];
	}

	PointL::operator PointD() const
	{
		return PointD{ (double)X, (double)Y };
	}
#pragma endregion

#pragma region Operators
	bool operator==(const PointL &a, const PointL &b)
	{
		return a.X == b.X && a.Y == b.Y;
	}

	bool operator!=(const PointL &a, const PointL &b)
	{
		return a.X != b.X || a.Y != b.Y;
	}

	PointL operator+(const PointL &a, const long long value)
	{
		return PointL{ a.X + value, a.Y + value };
	}

	PointL operator-(const PointL &a, const long long value)
	{
		return PointL{ a.X - value, a.Y - value };
	}

	PointL operator/(const PointL &a, const long long value)
	{
		return PointL{ a.X / value, a.Y / value };
	}

	PointL operator*(const PointL &a, const long long value)
	{
		return PointL{ a.X * value, a.Y * value };
	}

	PointL operator+(const long long value, const PointL &a)
	{
		return PointL{ value + a.X, value + a.Y };
	}

	PointL operator-(const long long value, const PointL &a)
	{
		return PointL{ value - a.X, value - a.Y };
	}

	PointL operator/(const long long value, const PointL &a)
	{
		return PointL{ value / a.X, value / a.Y };
	}

	PointL operator*(const long long value, const PointL &a)
	{
		return PointL{ value * a.X, value * a.Y };
	}

	PointL &operator+=(PointL &a, const long long value)
	{
		a.X += value;
		a.Y += value;
		return a;
	}

	PointL &operator-=(PointL &a, const long long value)
	{
		a.X -= value;
		a.Y -= value;
		return a;
	}

	PointL &operator/=(PointL &a, const long long value)
	{
		a.X /= value;
		a.Y /= value;
		return a;
	}

	PointL &operator*=(PointL &a, const long long value)
	{
		a.X *= value;
		a.Y *= value;
		return a;
	}

	PointL operator+(const PointL &a, const PointL &b)
	{
		return PointL{ a.X + b.X, a.Y + b.Y };
	}

	PointL operator-(const PointL &a, const PointL &b)
	{
		return PointL{ a.X - b.X, a.Y - b.Y };
	}

	PointL operator*(const PointL &a, const PointL &b)
	{
		return PointL{ a.X * b.X, a.Y * b.Y };
	}

	PointL operator/(const PointL &a, const PointL &b)
	{
		return PointL{ a.X / b.X, a.Y / b.Y };
	}

	PointL &operator+=(PointL &a, const PointL &b)
	{
		a.X += b.X;
		a.Y += b.Y;
		return a;
	}

	PointL &operator-=(PointL &a, const PointL &b)
	{
		a.X -= b.X;
		a.Y -= b.Y;
		return a;
	}

	PointL &operator*=(PointL &a, const PointL &b)
	{
		a.X *= b.X;
		a.Y *= b.Y;
		return a;
	}

	PointL &operator/=(PointL &a, const PointL &b)
	{
		a.X /= b.X;
		a.Y /= b.Y;
		return a;
	}

	PointL operator-(const PointL &a)
	{
		return PointL{ -a.X, -a.Y };
	}

	std::wostream &operator<<(std::wostream &stream, const PointL &a)
	{
		stream << L"{ " << a.X << L", " << a.Y << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	String AsSourceCode(const PointL &a)
	{
		return L"PointL{ " + ToString(a.X) + L", " + ToString(a.Y) + L" }";
	}

	String ToString(const PointL &value)
	{
		return ToString(value.X) + L", " + ToString(value.Y);
	}

	Variant ToVariant(const PointL &value)
	{
		Variant result;
		result.push_back((Variant)ToString(value.X));
		result.push_back((Variant)ToString(value.Y));
		return result;
	}

	void FromVariant(const Variant &value, PointL &dest)
	{
		dest = PointL{ StringToInt64((String)value.get(0)), StringToInt64((String)value.get(1)) };
	}

	PointL Round(const PointD &a)
	{
		return PointL{ ntl::Round<long long>(a.X), ntl::Round<long long>(a.Y) };
	}
#pragma endregion
}