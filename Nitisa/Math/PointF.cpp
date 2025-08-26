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
#pragma region PointF
	float PointF::operator[](const int index) const
	{
		return Data[index];
	}

	float &PointF::operator[](const int index)
	{
		return Data[index];
	}
#pragma endregion

#pragma region Operators
	PointF operator+(const PointF &a, const float value)
	{
		return PointF{ a.X + value, a.Y + value };
	}

	PointF operator-(const PointF &a, const float value)
	{
		return PointF{ a.X - value, a.Y - value };
	}

	PointF operator/(const PointF &a, const float value)
	{
		return PointF{ a.X / value, a.Y / value };
	}

	PointF operator*(const PointF &a, const float value)
	{
		return PointF{ a.X * value, a.Y * value };
	}

	PointF operator+(const float value, const PointF &a)
	{
		return PointF{ value + a.X, value + a.Y };
	}

	PointF operator-(const float value, const PointF &a)
	{
		return PointF{ value - a.X, value - a.Y };
	}

	PointF operator/(const float value, const PointF &a)
	{
		return PointF{ value / a.X, value / a.Y };
	}

	PointF operator*(const float value, const PointF &a)
	{
		return PointF{ value * a.X, value * a.Y };
	}

	PointF &operator+=(PointF &a, const float value)
	{
		a.X += value;
		a.Y += value;
		return a;
	}

	PointF &operator-=(PointF &a, const float value)
	{
		a.X -= value;
		a.Y -= value;
		return a;
	}

	PointF &operator/=(PointF &a, const float value)
	{
		a.X /= value;
		a.Y /= value;
		return a;
	}

	PointF &operator*=(PointF &a, const float value)
	{
		a.X *= value;
		a.Y *= value;
		return a;
	}

	PointF operator+(const PointF &a, const PointF &b)
	{
		return PointF{ a.X + b.X, a.Y + b.Y };
	}

	PointF operator-(const PointF &a, const PointF &b)
	{
		return PointF{ a.X - b.X, a.Y - b.Y };
	}

	PointF operator*(const PointF &a, const PointF &b)
	{
		return PointF{ a.X * b.X, a.Y * b.Y };
	}

	PointF operator/(const PointF &a, const PointF &b)
	{
		return PointF{ a.X / b.X, a.Y / b.Y };
	}

	PointF &operator+=(PointF &a, const PointF &b)
	{
		a.X += b.X;
		a.Y += b.Y;
		return a;
	}

	PointF &operator-=(PointF &a, const PointF &b)
	{
		a.X -= b.X;
		a.Y -= b.Y;
		return a;
	}

	PointF &operator*=(PointF &a, const PointF &b)
	{
		a.X *= b.X;
		a.Y *= b.Y;
		return a;
	}

	PointF &operator/=(PointF &a, const PointF &b)
	{
		a.X /= b.X;
		a.Y /= b.Y;
		return a;
	}

	PointF operator-(const PointF &a)
	{
		return PointF{ -a.X, -a.Y };
	}

	std::wostream &operator<<(std::wostream &stream, const PointF &a)
	{
		stream << L"{ " << AsSourceCode(a.X) << L", " << AsSourceCode(a.Y) << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	bool IsEqual(const PointF &a, const PointF &b, const float tolerance)
	{
		return ntl::Abs<float>(b.X - a.X) < tolerance && ntl::Abs<float>(b.Y - a.Y) < tolerance;
	}

	bool IsNotEqual(const PointF &a, const PointF &b, const float tolerance)
	{
		return ntl::Abs<float>(b.X - a.X) >= tolerance || ntl::Abs<float>(b.Y - a.Y) >= tolerance;
	}

	bool Equals(const PointF &a, const PointF &b, const float relative_tolerance)
	{
		return ntl::Equals<float>(a.X, b.X, relative_tolerance) && ntl::Equals<float>(a.Y, b.Y, relative_tolerance);
	}

	bool NotEquals(const PointF &a, const PointF &b, const float relative_tolerance)
	{
		return ntl::NotEquals<float>(a.X, b.X, relative_tolerance) || ntl::NotEquals<float>(a.Y, b.Y, relative_tolerance);
	}

	String AsSourceCode(const PointF &a)
	{
		return L"PointF{ " + AsSourceCode(a.X) + L", " + AsSourceCode(a.Y) + L" }";
	}

	String ToString(const PointF &value)
	{
		return ToStringCompact(value.X) + L", " + ToStringCompact(value.Y);
	}

	Variant ToVariant(const PointF &value)
	{
		Variant result;
		result.push_back((Variant)value.X);
		result.push_back((Variant)value.Y);
		return result;
	}

	void FromVariant(const Variant &value, PointF &dest)
	{
		dest = PointF{ (float)value.get(0), (float)value.get(1) };
	}
#pragma endregion
}