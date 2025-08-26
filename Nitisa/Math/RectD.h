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
#include "PointD.h"
#include <iostream>

namespace nitisa
{
	union RectD
	{
		struct
		{
			double Left;
			double Top;
			double Right;
			double Bottom;
		};
		struct
		{
			PointD LeftTop;
			PointD RightBottom;
		};
		double Data[4];

		double operator[](const int index) const; // Return element
		double &operator[](const int index); // Return element

		bool is_valid(const double tolerance = ntl::Tolerance<double>) const; // Return whether right border isn't less than left and bottom isn't less than top
		bool is_empty(const double tolerance = ntl::Tolerance<double>) const; // Return whether right border is same as left and bottom is same as top
		bool is_zero(const double tolerance = ntl::Tolerance<double>) const; // Return whether either right border is same to left or bottom is same to top
		bool has_negative(const double tolerance = ntl::Tolerance<double>) const; // Whether there is a negative element
		bool has_positive(const double tolerance = ntl::Tolerance<double>) const; // Whether there is a positive element
		bool has_area(const double tolerance = ntl::Tolerance<double>) const; // Return whether rectangle has positive area
		double width() const; // Rectangle width
		double height() const; // Rectangle height
		void validate(const double tolerance = ntl::Tolerance<double>); // Make width and height not negative
		bool is_inside(const PointD &p, const double tolerance = ntl::Tolerance<double>) const; // Return whether point is inside of the rectangle
		bool is_outside(const PointD &p, const double tolerance = ntl::Tolerance<double>) const; // Return whether point is outside of the rectangle
	};

	RectD operator+(const RectD &a, const double value); // Add rect and value
	RectD operator-(const RectD &a, const double value); // Subtract rect and value
	RectD operator/(const RectD &a, const double value); // Divide rect and value
	RectD operator*(const RectD &a, const double value); // Multiply rect and value
	RectD operator+(const double value, const RectD &a); // Add value and rect
	RectD operator-(const double value, const RectD &a); // Subtract value and rect
	RectD operator/(const double value, const RectD &a); // Divide value and rect
	RectD operator*(const double value, const RectD &a); // Multiply value and rect
	RectD &operator+=(RectD &a, const double value); // Add value to rect
	RectD &operator-=(RectD &a, const double value); // Subtract value from rect
	RectD &operator/=(RectD &a, const double value); // Divide rect on value
	RectD &operator*=(RectD &a, const double value); // Multiply rect on value
	RectD operator+(const RectD &a, const RectD &b); // Find bounding rect for both rects
	RectD operator*(const RectD &a, const RectD &b); // Calculate intersection
	RectD &operator+=(RectD &a, const RectD &b); // Find bounding rect for both rects and store it in first one
	RectD &operator*=(RectD &a, const RectD &b); // Calculate intersection and store it in first one
	RectD operator+(const RectD &a, const PointD &shift); // Return moved in shift direction rect
	RectD operator-(const RectD &a, const PointD &shift); // Return moved in opposite to shift direction rect
	RectD operator*(const RectD &a, const PointD &shift); // Return scaled in shift direction rect
	RectD &operator+=(RectD &a, const PointD &shift); // Move rect in shift direction
	RectD &operator-=(RectD &a, const PointD &shift); // Move rect in direction opposite to shift
	RectD &operator*=(RectD &a, const PointD &shift); // Scale rect in shift direction
	std::wostream &operator<<(std::wostream &stream, const RectD &a); // Output as source code

	bool IsEqual(const RectD &a, const RectD &b, const double tolerance = ntl::Tolerance<double>);
	bool IsNotEqual(const RectD &a, const RectD &b, const double tolerance = ntl::Tolerance<double>);
	bool Equals(const RectD &a, const RectD &b, const double relative_tolerance = ntl::RelativeTolerance<double>);
	bool NotEquals(const RectD &a, const RectD &b, const double relative_tolerance = ntl::RelativeTolerance<double>);
	String AsSourceCode(const RectD &a);
	String ToString(const RectD &value);
	Variant ToVariant(const RectD &value);
	void FromVariant(const Variant &value, RectD &dest);
}