// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include "PointL.h"
#include "RectD.h"
#include <iostream>

namespace nitisa
{
	union RectL
	{
		struct
		{
			long long Left;
			long long Top;
			long long Right;
			long long Bottom;
		};
		struct
		{
			PointL LeftTop;
			PointL RightBottom;
		};
		long long Data[4];

		long long operator[](const int index) const; // Return element
		long long &operator[](const int index); // Return element
		explicit operator RectD() const; // Convert to RectD

		bool is_valid() const; // Return whether right border isn't less than left and bottom isn't less than top
		bool is_empty() const; // Return whether right border is same as left and bottom is same as top
		bool is_zero() const; // Return whether either right border is same to left or bottom is same to top
		bool has_negative() const; // Whether there is a negative element
		bool has_positive() const; // Whether there is a positive element
		bool has_area() const; // Return whether rectangle has positive area
		long long width() const; // Rectangle width
		long long height() const; // Rectangle height
		void validate(); // Make width and height not negative
		bool is_inside(const PointL &p) const; // Return whether point is inside of the rectangle
		bool is_outside(const PointL &p) const; // Return whether point is outside of the rectangle
	};

	bool operator==(const RectL &a, const RectL &b); // Check if rects are equal
	bool operator!=(const RectL &a, const RectL &b); // Check if rects are not equal
	RectL operator+(const RectL &a, const long long value); // Add rect and value
	RectL operator-(const RectL &a, const long long value); // Subtract rect and value
	RectL operator/(const RectL &a, const long long value); // Divide rect and value
	RectL operator*(const RectL &a, const long long value); // Multiply rect and value
	RectL operator+(const long long value, const RectL &a); // Add value and rect
	RectL operator-(const long long value, const RectL &a); // Subtract value and rect
	RectL operator/(const long long value, const RectL &a); // Divide value and rect
	RectL operator*(const long long value, const RectL &a); // Multiply value and rect
	RectL &operator+=(RectL &a, const long long value); // Add value to rect
	RectL &operator-=(RectL &a, const long long value); // Subtract value from rect
	RectL &operator/=(RectL &a, const long long value); // Divide rect on value
	RectL &operator*=(RectL &a, const long long value); // Multiply rect on value
	RectL operator+(const RectL &a, const RectL &b); // Find bounding rect for both rects
	RectL operator*(const RectL &a, const RectL &b); // Calculate intersection
	RectL &operator+=(RectL &a, const RectL &b); // Find bounding rect for both rects and store it in first one
	RectL &operator*=(RectL &a, const RectL &b); // Calculate intersection and store it in first one
	RectL operator+(const RectL &a, const PointL &shift); // Return moved in shift direction rect
	RectL operator-(const RectL &a, const PointL &shift); // Return moved in opposite to shift direction rect
	RectL operator*(const RectL &a, const PointL &shift); // Return scaled in shift direction rect
	RectL &operator+=(RectL &a, const PointL &shift); // Move rect in shift direction
	RectL &operator-=(RectL &a, const PointL &shift); // Move rect in direction opposite to shift
	RectL &operator*=(RectL &a, const PointL &shift); // Scale rect in shift direction
	std::wostream &operator<<(std::wostream &stream, const RectL &a); // Output as source code

	String AsSourceCode(const RectL &a);
	String ToString(const RectL &value);
	Variant ToVariant(const RectL &value);
	void FromVariant(const Variant &value, RectL &dest);
	RectL Round(const RectD &a); // Convert to integer rectangle rounding elements
}