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
#pragma region PointD
	double PointD::operator[](const int index) const
	{
		return Data[index];
	}

	double &PointD::operator[](const int index)
	{
		return Data[index];
	}
#pragma endregion

#pragma region Operators
	PointD operator+(const PointD &a, const double value)
	{
		return PointD{ a.X + value, a.Y + value };
	}

	PointD operator-(const PointD &a, const double value)
	{
		return PointD{ a.X - value, a.Y - value };
	}

	PointD operator/(const PointD &a, const double value)
	{
		return PointD{ a.X / value, a.Y / value };
	}

	PointD operator*(const PointD &a, const double value)
	{
		return PointD{ a.X * value, a.Y * value };
	}

	PointD operator+(const double value, const PointD &a)
	{
		return PointD{ value + a.X, value + a.Y };
	}

	PointD operator-(const double value, const PointD &a)
	{
		return PointD{ value - a.X, value - a.Y };
	}

	PointD operator/(const double value, const PointD &a)
	{
		return PointD{ value / a.X, value / a.Y };
	}

	PointD operator*(const double value, const PointD &a)
	{
		return PointD{ value * a.X, value * a.Y };
	}

	PointD &operator+=(PointD &a, const double value)
	{
		a.X += value;
		a.Y += value;
		return a;
	}

	PointD &operator-=(PointD &a, const double value)
	{
		a.X -= value;
		a.Y -= value;
		return a;
	}

	PointD &operator/=(PointD &a, const double value)
	{
		a.X /= value;
		a.Y /= value;
		return a;
	}

	PointD &operator*=(PointD &a, const double value)
	{
		a.X *= value;
		a.Y *= value;
		return a;
	}

	PointD operator+(const PointD &a, const PointD &b)
	{
		return PointD{ a.X + b.X, a.Y + b.Y };
	}

	PointD operator-(const PointD &a, const PointD &b)
	{
		return PointD{ a.X - b.X, a.Y - b.Y };
	}

	PointD operator*(const PointD &a, const PointD &b)
	{
		return PointD{ a.X * b.X, a.Y * b.Y };
	}

	PointD operator/(const PointD &a, const PointD &b)
	{
		return PointD{ a.X / b.X, a.Y / b.Y };
	}

	PointD &operator+=(PointD &a, const PointD &b)
	{
		a.X += b.X;
		a.Y += b.Y;
		return a;
	}

	PointD &operator-=(PointD &a, const PointD &b)
	{
		a.X -= b.X;
		a.Y -= b.Y;
		return a;
	}

	PointD &operator*=(PointD &a, const PointD &b)
	{
		a.X *= b.X;
		a.Y *= b.Y;
		return a;
	}

	PointD &operator/=(PointD &a, const PointD &b)
	{
		a.X /= b.X;
		a.Y /= b.Y;
		return a;
	}

	PointD operator-(const PointD &a)
	{
		return PointD{ -a.X, -a.Y };
	}

	std::wostream &operator<<(std::wostream &stream, const PointD &a)
	{
		stream << L"{ " << ToString(a.X) << L", " << ToString(a.Y) << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	bool IsEqual(const PointD &a, const PointD &b, const double tolerance)
	{
		return ntl::Abs<double>(b.X - a.X) < tolerance && ntl::Abs<double>(b.Y - a.Y) < tolerance;
	}

	bool IsNotEqual(const PointD &a, const PointD &b, const double tolerance)
	{
		return ntl::Abs<double>(b.X - a.X) >= tolerance || ntl::Abs<double>(b.Y - a.Y) >= tolerance;
	}

	bool Equals(const PointD &a, const PointD &b, const double relative_tolerance)
	{
		return ntl::Equals<double>(a.X, b.X, relative_tolerance) && ntl::Equals<double>(a.Y, b.Y, relative_tolerance);
	}

	bool NotEquals(const PointD &a, const PointD &b, const double relative_tolerance)
	{
		return ntl::NotEquals<double>(a.X, b.X, relative_tolerance) || ntl::NotEquals<double>(a.Y, b.Y, relative_tolerance);
	}

	String AsSourceCode(const PointD &a)
	{
		return L"PointD{ " + AsSourceCode(a.X) + L", " + AsSourceCode(a.Y) + L" }";
	}

	String ToString(const PointD &value)
	{
		return ToStringCompact(value.X) + L", " + ToStringCompact(value.Y);
	}

	Variant ToVariant(const PointD &value)
	{
		Variant result;
		result.push_back((Variant)ToString(value.X));
		result.push_back((Variant)ToString(value.Y));
		return result;
	}

	void FromVariant(const Variant &value, PointD &dest)
	{
		dest = PointD{ StringToDouble((String)value.get(0)), StringToDouble((String)value.get(1)) };
	}
#pragma endregion
}