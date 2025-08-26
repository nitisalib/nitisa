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
#pragma region RectF
	float RectF::operator[](const int index) const
	{
		return Data[index];
	}

	float &RectF::operator[](const int index)
	{
		return Data[index];
	}

	bool RectF::is_valid(const float tolerance) const
	{
		return ntl::IsGreaterOrEqual<float>(Right, Left, tolerance) && ntl::IsGreaterOrEqual<float>(Bottom, Top, tolerance);
	}

	bool RectF::is_empty(const float tolerance) const
	{
		return ntl::IsEqual<float>(Right, Left, tolerance) && ntl::IsEqual<float>(Bottom, Top, tolerance);
	}

	bool RectF::is_zero(const float tolerance) const
	{
		return ntl::IsEqual<float>(Right, Left, tolerance) || ntl::IsEqual<float>(Bottom, Top, tolerance);
	}

	bool RectF::has_negative(const float tolerance) const
	{
		return ntl::IsLess<float>(Left, 0, tolerance) || ntl::IsLess<float>(Top, 0, tolerance) || ntl::IsLess<float>(Right, 0, tolerance) || ntl::IsLess<float>(Bottom, 0, tolerance);
	}

	bool RectF::has_positive(const float tolerance) const
	{
		return ntl::IsGreater<float>(Left, 0, tolerance) || ntl::IsGreater<float>(Top, 0, tolerance) || ntl::IsGreater<float>(Right, 0, tolerance) || ntl::IsGreater<float>(Bottom, 0, tolerance);
	}

	bool RectF::has_area(const float tolerance) const
	{
		return ntl::IsGreater<float>(Right, Left, tolerance) && ntl::IsGreater<float>(Bottom, Top, tolerance);
	}

	float RectF::width() const
	{
		return Right - Left;
	}

	float RectF::height() const
	{
		return Bottom - Top;
	}

	void RectF::validate(const float tolerance)
	{
		if (ntl::IsLess<float>(Right, Left, tolerance))
			Right = Left;
		if (ntl::IsLess<float>(Bottom, Top, tolerance))
			Bottom = Top;
	}

	bool RectF::is_inside(const PointF &p, const float tolerance) const
	{
		return
			ntl::IsGreaterOrEqual<float>(p.X, Left, tolerance) &&
			ntl::IsLess<float>(p.X, Right, tolerance) &&
			ntl::IsGreaterOrEqual<float>(p.Y, Top, tolerance) &&
			ntl::IsLess<float>(p.Y, Bottom, tolerance);
	}

	bool RectF::is_outside(const PointF &p, const float tolerance) const
	{
		return
			ntl::IsLess<float>(p.X, Left, tolerance) ||
			ntl::IsGreaterOrEqual<float>(p.X, Right, tolerance) ||
			ntl::IsLess<float>(p.Y, Top, tolerance) ||
			ntl::IsGreaterOrEqual<float>(p.Y, Bottom, tolerance);
	}
#pragma endregion

#pragma region Operators
	RectF operator+(const RectF &a, const float value)
	{
		return RectF{ a.Left + value, a.Top + value, a.Right + value, a.Bottom + value };
	}

	RectF operator-(const RectF &a, const float value)
	{
		return RectF{ a.Left - value, a.Top - value, a.Right - value, a.Bottom - value };
	}

	RectF operator/(const RectF &a, const float value)
	{
		return RectF{ a.Left / value, a.Top / value, a.Right / value, a.Bottom / value };
	}

	RectF operator*(const RectF &a, const float value)
	{
		return RectF{ a.Left * value, a.Top * value, a.Right * value, a.Bottom * value };
	}

	RectF operator+(const float value, const RectF &a)
	{
		return RectF{ value + a.Left, value + a.Top, value + a.Right, value + a.Bottom };
	}

	RectF operator-(const float value, const RectF &a)
	{
		return RectF{ value - a.Left, value - a.Top, value - a.Right, value - a.Bottom };
	}

	RectF operator/(const float value, const RectF &a)
	{
		return RectF{ value / a.Left, value / a.Top, value / a.Right, value / a.Bottom };
	}

	RectF operator*(const float value, const RectF &a)
	{
		return RectF{ value * a.Left, value * a.Top, value * a.Right, value * a.Bottom };
	}

	RectF &operator+=(RectF &a, const float value)
	{
		a.Left += value;
		a.Top += value;
		a.Right += value;
		a.Bottom += value;
		return a;
	}

	RectF &operator-=(RectF &a, const float value)
	{
		a.Left -= value;
		a.Top -= value;
		a.Right -= value;
		a.Bottom -= value;
		return a;
	}

	RectF &operator/=(RectF &a, const float value)
	{
		a.Left /= value;
		a.Top /= value;
		a.Right /= value;
		a.Bottom /= value;
		return a;
	}

	RectF &operator*=(RectF &a, const float value)
	{
		a.Left *= value;
		a.Top *= value;
		a.Right *= value;
		a.Bottom *= value;
		return a;
	}

	RectF operator+(const RectF &a, const RectF &b)
	{
		return RectF{ ntl::Min<float>(a.Left, b.Left), ntl::Min<float>(a.Top, b.Top), ntl::Max<float>(a.Right, b.Right), ntl::Max<float>(a.Bottom, b.Bottom) };
	}

	RectF operator*(const RectF &a, const RectF &b)
	{
		return RectF{ ntl::Max<float>(a.Left, b.Left), ntl::Max<float>(a.Top, b.Top), ntl::Min<float>(a.Right, b.Right), ntl::Min<float>(a.Bottom, b.Bottom) };
	}

	RectF &operator+=(RectF &a, const RectF &b)
	{
		a.Left = ntl::Min<float>(a.Left, b.Left);
		a.Top = ntl::Min<float>(a.Top, b.Top);
		a.Right = ntl::Max<float>(a.Right, b.Right);
		a.Bottom = ntl::Max<float>(a.Bottom, b.Bottom);
		return a;
	}

	RectF &operator*=(RectF &a, const RectF &b)
	{
		a.Left = ntl::Max<float>(a.Left, b.Left);
		a.Top = ntl::Max<float>(a.Top, b.Top);
		a.Right = ntl::Min<float>(a.Right, b.Right);
		a.Bottom = ntl::Min<float>(a.Bottom, b.Bottom);
		return a;
	}

	RectF operator+(const RectF &a, const PointF &shift)
	{
		return RectF{ a.Left + shift.X, a.Top + shift.Y, a.Right + shift.X, a.Bottom + shift.Y };
	}

	RectF operator-(const RectF &a, const PointF &shift)
	{
		return RectF{ a.Left - shift.X, a.Top - shift.Y, a.Right - shift.X, a.Bottom - shift.Y };
	}

	RectF operator*(const RectF &a, const PointF &shift)
	{
		return RectF{ a.Left * shift.X, a.Top * shift.Y, a.Right * shift.X, a.Bottom * shift.Y };
	}

	RectF &operator+=(RectF &a, const PointF &shift)
	{
		a.Left += shift.X;
		a.Top += shift.Y;
		a.Right += shift.X;
		a.Bottom += shift.Y;
		return a;
	}

	RectF &operator-=(RectF &a, const PointF &shift)
	{
		a.Left -= shift.X;
		a.Top -= shift.Y;
		a.Right -= shift.X;
		a.Bottom -= shift.Y;
		return a;
	}

	RectF &operator*=(RectF &a, const PointF &shift)
	{
		a.Left *= shift.X;
		a.Top *= shift.Y;
		a.Right *= shift.X;
		a.Bottom *= shift.Y;
		return a;
	}

	std::wostream &operator<<(std::wostream &stream, const RectF &a)
	{
		stream << L"{ " << AsSourceCode(a.Left) << L", " << AsSourceCode(a.Top) << L", " << AsSourceCode(a.Right) << L", " << AsSourceCode(a.Bottom) << L" }";
		return stream;
	}
#pragma endregion

#pragma region Functions
	bool IsEqual(const RectF &a, const RectF &b, const float tolerance)
	{
		return
			ntl::Abs<float>(b.Left - a.Left) < tolerance &&
			ntl::Abs<float>(b.Top - a.Top) < tolerance &&
			ntl::Abs<float>(b.Right - a.Right) < tolerance &&
			ntl::Abs<float>(b.Bottom - a.Bottom) < tolerance;
	}

	bool IsNotEqual(const RectF &a, const RectF &b, const float tolerance)
	{
		return
			ntl::Abs<float>(b.Left - a.Left) >= tolerance ||
			ntl::Abs<float>(b.Top - a.Top) >= tolerance ||
			ntl::Abs<float>(b.Right - a.Right) >= tolerance ||
			ntl::Abs<float>(b.Bottom - a.Bottom) >= tolerance;
	}

	bool Equals(const RectF &a, const RectF &b, const float relative_tolerance)
	{
		return
			ntl::Equals<float>(a.Left, b.Left, relative_tolerance) &&
			ntl::Equals<float>(a.Top, b.Top, relative_tolerance) &&
			ntl::Equals<float>(a.Right, b.Right, relative_tolerance) &&
			ntl::Equals<float>(a.Bottom, b.Bottom, relative_tolerance);
	}

	bool NotEquals(const RectF &a, const RectF &b, const float relative_tolerance)
	{
		return
			ntl::NotEquals<float>(a.Left, b.Left, relative_tolerance) ||
			ntl::NotEquals<float>(a.Top, b.Top, relative_tolerance) ||
			ntl::NotEquals<float>(a.Right, b.Right, relative_tolerance) ||
			ntl::NotEquals<float>(a.Bottom, b.Bottom, relative_tolerance);
	}

	String AsSourceCode(const RectF &a)
	{
		return L"RectF{ " + AsSourceCode(a.Left) + L", " + AsSourceCode(a.Top) + L", " + AsSourceCode(a.Right) + L", " + AsSourceCode(a.Bottom) + L" }";
	}

	String ToString(const RectF &value)
	{
		return ToStringCompact(value.Left) + L", " + ToStringCompact(value.Top) + L", " + ToStringCompact(value.Right) + L", " + ToStringCompact(value.Bottom);
	}

	Variant ToVariant(const RectF &value)
	{
		Variant result;
		result.push_back((Variant)value.Left);
		result.push_back((Variant)value.Top);
		result.push_back((Variant)value.Right);
		result.push_back((Variant)value.Bottom);
		return result;
	}

	void FromVariant(const Variant &value, RectF &dest)
	{
		dest = RectF{ (float)value.get(0), (float)value.get(1), (float)value.get(2), (float)value.get(3) };
	}

	RectF AddElements(const RectF &a, const RectF &b)
	{
		return RectF{ a.Left + b.Left, a.Top + b.Top, a.Right + b.Right, a.Bottom + b.Bottom };
	}

	RectF AddElements(const RectF &a, const RectF &b, const RectF &c)
	{
		return RectF{ a.Left + b.Left + c.Left, a.Top + b.Top + c.Top, a.Right + b.Right + c.Right, a.Bottom + b.Bottom + c.Bottom };
	}

	RectF AddElements(const RectF &a, const RectF &b, const RectF &c, const RectF &d)
	{
		return RectF{ a.Left + b.Left + c.Left + d.Left, a.Top + b.Top + c.Top + d.Top, a.Right + b.Right + c.Right + d.Right, a.Bottom + b.Bottom + c.Bottom + d.Bottom };
	}

	void TransformRect(const RectF &rect, const Mat4f &matrix, PointF &lt, PointF &rt, PointF &rb, PointF &lb)
	{
		// Left top
		Vec4f v{ rect.Left, rect.Top, 0, 1 };
		v = matrix * v;
		lt.X = v.X;
		lt.Y = v.Y;
		// Right top
		v = Vec4f{ rect.Right, rect.Top, 0, 1 };
		v = matrix * v;
		rt.X = v.X;
		rt.Y = v.Y;
		// Right bottom
		v = Vec4f{ rect.Right, rect.Bottom, 0, 1 };
		v = matrix * v;
		rb.X = v.X;
		rb.Y = v.Y;
		// Left bottom
		v = Vec4f{ rect.Left, rect.Bottom, 0, 1 };
		v = matrix * v;
		lb.X = v.X;
		lb.Y = v.Y;
	}

	RectF TransformRect(const RectF &rect, const Mat4f &matrix)
	{
		PointF lt, rt, rb, lb;
		TransformRect(rect, matrix, lt, rt, rb, lb);
		return Bound(lt, rt, rb, lb);
	}

	RectF Bound(const PointF &lt, const PointF &rt, const PointF &rb, const PointF &lb)
	{
		return RectF{
			ntl::Min<float>(lt.X, rt.X, lb.X, rb.X),
			ntl::Min<float>(lt.Y, rt.Y, lb.Y, rb.Y),
			ntl::Max<float>(lt.X, rt.X, lb.X, rb.X),
			ntl::Max<float>(lt.Y, rt.Y, lb.Y, rb.Y),
		};
	}

	bool Intersects(const RectF &rect1, const RectF &rect2, const Mat4f &matrix, const float tolerance)
	{
		PointF points[4];
		TransformRect(rect2, matrix, points[0], points[1], points[2], points[3]);
		bool outside{ true };
		for (int i = 0; i < 4; i++)
			if (ntl::IsGreaterOrEqual<float>(points[i].X, rect1.Left, tolerance))
			{
				outside = false;
				break;
			}
		if (outside)
			return false;

		outside = true;
		for (int i = 0; i < 4; i++)
			if (ntl::IsGreaterOrEqual<float>(points[i].Y, rect1.Top, tolerance))
			{
				outside = false;
				break;
			}
		if (outside)
			return false;

		outside = true;
		for (int i = 0; i < 4; i++)
			if (ntl::IsLessOrEqual<float>(points[i].X, rect1.Right, tolerance))
			{
				outside = false;
				break;
			}
		if (outside)
			return false;

		outside = true;
		for (int i = 0; i < 4; i++)
			if (ntl::IsLessOrEqual<float>(points[i].Y, rect1.Bottom, tolerance))
			{
				outside = false;
				break;
			}
		if (outside)
			return false;
		return true;
	}
#pragma endregion
}