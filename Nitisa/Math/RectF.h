// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "NTL/Core/Consts.h"
#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include "Mat4f.h"
#include "PointF.h"
#include <iostream>

namespace nitisa
{
	union RectF
	{
		struct
		{
			float Left;
			float Top;
			float Right;
			float Bottom;
		};
		struct
		{
			PointF LeftTop;
			PointF RightBottom;
		};
		float Data[4];

		float operator[](const int index) const; // Return element
		float &operator[](const int index); // Return element

		bool is_valid(const float tolerance = ntl::Tolerance<float>) const; // Return whether right border isn't less than left and bottom isn't less than top
		bool is_empty(const float tolerance = ntl::Tolerance<float>) const; // Return whether right border is same as left and bottom is same as top
		bool is_zero(const float tolerance = ntl::Tolerance<float>) const; // Return whether either right border is same to left or bottom is same to top
		bool has_negative(const float tolerance = ntl::Tolerance<float>) const; // Whether there is a negative element
		bool has_positive(const float tolerance = ntl::Tolerance<float>) const; // Whether there is a positive element
		bool has_area(const float tolerance = ntl::Tolerance<float>) const; // Return whether rectangle has positive area
		float width() const; // Rectangle width
		float height() const; // Rectangle height
		void validate(const float tolerance = ntl::Tolerance<float>); // Make width and height not negative
		bool is_inside(const PointF &p, const float tolerance = ntl::Tolerance<float>) const; // Return whether point is inside of the rectangle
		bool is_outside(const PointF &p, const float tolerance = ntl::Tolerance<float>) const; // Return whether point is outside of the rectangle
	};

	RectF operator+(const RectF &a, const float value); // Add rect and value
	RectF operator-(const RectF &a, const float value); // Subtract rect and value
	RectF operator/(const RectF &a, const float value); // Divide rect and value
	RectF operator*(const RectF &a, const float value); // Multiply rect and value
	RectF operator+(const float value, const RectF &a); // Add value and rect
	RectF operator-(const float value, const RectF &a); // Subtract value and rect
	RectF operator/(const float value, const RectF &a); // Divide value and rect
	RectF operator*(const float value, const RectF &a); // Multiply value and rect
	RectF &operator+=(RectF &a, const float value); // Add value to rect
	RectF &operator-=(RectF &a, const float value); // Subtract value from rect
	RectF &operator/=(RectF &a, const float value); // Divide rect on value
	RectF &operator*=(RectF &a, const float value); // Multiply rect on value
	RectF operator+(const RectF &a, const RectF &b); // Find bounding rect for both rects
	RectF operator*(const RectF &a, const RectF &b); // Calculate intersection
	RectF &operator+=(RectF &a, const RectF &b); // Find bounding rect for both rects and store it in first one
	RectF &operator*=(RectF &a, const RectF &b); // Calculate intersection and store it in first one
	RectF operator+(const RectF &a, const PointF &shift); // Return moved in shift direction rect
	RectF operator-(const RectF &a, const PointF &shift); // Return moved in opposite to shift direction rect
	RectF operator*(const RectF &a, const PointF &shift); // Return scaled in shift direction rect
	RectF &operator+=(RectF &a, const PointF &shift); // Move rect in shift direction
	RectF &operator-=(RectF &a, const PointF &shift); // Move rect in direction opposite to shift
	RectF &operator*=(RectF &a, const PointF &shift); // Scale rect in shift direction
	std::wostream &operator<<(std::wostream &stream, const RectF &a); // Output as source code

	bool IsEqual(const RectF &a, const RectF &b, const float tolerance = ntl::Tolerance<float>);
	bool IsNotEqual(const RectF &a, const RectF &b, const float tolerance = ntl::Tolerance<float>);
	bool Equals(const RectF &a, const RectF &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	bool NotEquals(const RectF &a, const RectF &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	String AsSourceCode(const RectF &a);
	String ToString(const RectF &value);
	Variant ToVariant(const RectF &value);
	void FromVariant(const Variant &value, RectF &dest);
	RectF AddElements(const RectF &a, const RectF &b);
	RectF AddElements(const RectF &a, const RectF &b, const RectF &c);
	RectF AddElements(const RectF &a, const RectF &b, const RectF &c, const RectF &d);
	void TransformRect(const RectF &rect, const Mat4f &matrix, PointF &lt, PointF &rt, PointF &rb, PointF &lb); // Return transformed rectangle new corner points
	RectF TransformRect(const RectF &rect, const Mat4f &matrix); // Return bound rectangle of transformed rectangle
	RectF Bound(const PointF &lt, const PointF &rt, const PointF &rb, const PointF &lb); // Return bounding rectangle for transformed rectangle corners
	bool Intersects(const RectF &rect1, const RectF &rect2, const Mat4f &matrix, const float tolerance = ntl::Tolerance<float>); // Return true if rectangles are intersected. Matrix is transformation of rect2 into coordinates of rect1
}