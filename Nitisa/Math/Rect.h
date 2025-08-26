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
#include "Point.h"
#include "RectF.h"
#include <iostream>

namespace nitisa
{
	union Rect
	{
		struct
		{
			int Left;
			int Top;
			int Right;
			int Bottom;
		};
		struct
		{
			Point LeftTop;
			Point RightBottom;
		};
		int Data[4];
		
		int operator[](const int index) const; // Return element
		int &operator[](const int index); // Return element
		explicit operator RectF() const; // Convert to RectF
		
		bool is_valid() const; // Return whether right border isn't less than left and bottom isn't less than top
		bool is_empty() const; // Return whether right border is same as left and bottom is same as top
		bool is_zero() const; // Return whether either right border is same to left or bottom is same to top
		bool has_negative() const; // Whether there is a negative element
		bool has_positive() const; // Whether there is a positive element
		bool has_area() const; // Return whether rectangle has positive area
		int width() const; // Rectangle width
		int height() const; // Rectangle height
		void validate(); // Make width and height not negative
		bool is_inside(const Point &p) const; // Return whether point is inside of the rectangle
		bool is_outside(const Point &p) const; // Return whether point is outside of the rectangle
	};

	bool operator==(const Rect &a, const Rect &b); // Check if rects are equal
	bool operator!=(const Rect &a, const Rect &b); // Check if rects are not equal
	Rect operator+(const Rect &a, const int value); // Add rect and value
	Rect operator-(const Rect &a, const int value); // Subtract rect and value
	Rect operator/(const Rect &a, const int value); // Divide rect and value
	Rect operator*(const Rect &a, const int value); // Multiply rect and value
	Rect operator+(const int value, const Rect &a); // Add value and rect
	Rect operator-(const int value, const Rect &a); // Subtract value and rect
	Rect operator/(const int value, const Rect &a); // Divide value and rect
	Rect operator*(const int value, const Rect &a); // Multiply value and rect
	Rect &operator+=(Rect &a, const int value); // Add value to rect
	Rect &operator-=(Rect &a, const int value); // Subtract value from rect
	Rect &operator/=(Rect &a, const int value); // Divide rect on value
	Rect &operator*=(Rect &a, const int value); // Multiply rect on value
	Rect operator+(const Rect &a, const Rect &b); // Find bounding rect for both rects
	Rect operator*(const Rect &a, const Rect &b); // Calculate intersection
	Rect &operator+=(Rect &a, const Rect &b); // Find bounding rect for both rects and store it in first one
	Rect &operator*=(Rect &a, const Rect &b); // Calculate intersection and store it in first one
	Rect operator+(const Rect &a, const Point &shift); // Return moved in shift direction rect
	Rect operator-(const Rect &a, const Point &shift); // Return moved in opposite to shift direction rect
	Rect operator*(const Rect &a, const Point &shift); // Return scaled in shift direction rect
	Rect &operator+=(Rect &a, const Point &shift); // Move rect in shift direction
	Rect &operator-=(Rect &a, const Point &shift); // Move rect in direction opposite to shift
	Rect &operator*=(Rect &a, const Point &shift); // Scale rect in shift direction
	std::wostream &operator<<(std::wostream &stream, const Rect &a); // Output as source code

	String AsSourceCode(const Rect &a);
	String ToString(const Rect &value);
	Variant ToVariant(const Rect &value);
	void FromVariant(const Variant &value, Rect &dest);
	Rect Round(const RectF &a); // Convert to integer rectangle rounding elements
}