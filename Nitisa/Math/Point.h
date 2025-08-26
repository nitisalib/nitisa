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
#include "PointF.h"
#include <iostream>

namespace nitisa
{
	union Point
	{
		struct
		{
			int X;
			int Y;
		};
		int Data[2];

		int operator[](const int index) const; // Get element
		int &operator[](const int index); // Get element
		explicit operator PointF() const; // Convert to PointF
	};

	bool operator==(const Point &a, const Point &b); // Check if points are equal
	bool operator!=(const Point &a, const Point &b); // Check if points are not equal
	Point operator+(const Point &a, const int value); // Add point and value
	Point operator-(const Point &a, const int value); // Subtract point and value
	Point operator/(const Point &a, const int value); // Divide point and value
	Point operator*(const Point &a, const int value); // Multiply point and value
	Point operator+(const int value, const Point &a); // Add value and point
	Point operator-(const int value, const Point &a); // Subtract value and point
	Point operator/(const int value, const Point &a); // Divide value and point
	Point operator*(const int value, const Point &a); // Multiply value and point
	Point &operator+=(Point &a, const int value); // Add value to point
	Point &operator-=(Point &a, const int value); // Subtract value from point
	Point &operator/=(Point &a, const int value); // Divide point on value
	Point &operator*=(Point &a, const int value); // Multiply point on value
	Point operator+(const Point &a, const Point &b); // Add points elements
	Point operator-(const Point &a, const Point &b); // Subtract points elements
	Point operator*(const Point &a, const Point &b); // Multiply point elements
	Point operator/(const Point &a, const Point &b); // Divide point elements
	Point &operator+=(Point &a, const Point &b); // Add elements of another point to first one
	Point &operator-=(Point &a, const Point &b); // Subtract elements of another point from first one
	Point &operator*=(Point &a, const Point &b); // Multiply point element to elements of another point
	Point &operator/=(Point &a, const Point &b); // Divide point element on elements of another point
	Point operator-(const Point &a); // Unary negation
	std::wostream &operator<<(std::wostream &stream, const Point &a); // Output as source code

	String AsSourceCode(const Point &a);
	String ToString(const Point &value);
	Variant ToVariant(const Point &value);
	void FromVariant(const Variant &value, Point &dest);
	Point Round(const PointF &a); // Convert to integer point rounding elements
}