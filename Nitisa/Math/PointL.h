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
#include "PointD.h"
#include <iostream>

namespace nitisa
{
	union PointL
	{
		struct
		{
			long long X;
			long long Y;
		};
		long long Data[2];

		long long operator[](const int index) const; // Get element
		long long &operator[](const int index); // Get element
		explicit operator PointD() const; // Convert to PointD
	};

	bool operator==(const PointL &a, const PointL &b); // Check if points are equal
	bool operator!=(const PointL &a, const PointL &b); // Check if points are not equal
	PointL operator+(const PointL &a, const long long value); // Add point and value
	PointL operator-(const PointL &a, const long long value); // Subtract point and value
	PointL operator/(const PointL &a, const long long value); // Divide point and value
	PointL operator*(const PointL &a, const long long value); // Multiply point and value
	PointL operator+(const long long value, const PointL &a); // Add value and point
	PointL operator-(const long long value, const PointL &a); // Subtract value and point
	PointL operator/(const long long value, const PointL &a); // Divide value and point
	PointL operator*(const long long value, const PointL &a); // Multiply value and point
	PointL &operator+=(PointL &a, const long long value); // Add value to point
	PointL &operator-=(PointL &a, const long long value); // Subtract value from point
	PointL &operator/=(PointL &a, const long long value); // Divide point on value
	PointL &operator*=(PointL &a, const long long value); // Multiply point on value
	PointL operator+(const PointL &a, const PointL &b); // Add points elements
	PointL operator-(const PointL &a, const PointL &b); // Subtract points elements
	PointL operator*(const PointL &a, const PointL &b); // Multiply point elements
	PointL operator/(const PointL &a, const PointL &b); // Divide point elements
	PointL &operator+=(PointL &a, const PointL &b); // Add elements of another point to first one
	PointL &operator-=(PointL &a, const PointL &b); // Subtract elements of another point from first one
	PointL &operator*=(PointL &a, const PointL &b); // Multiply point element to elements of another point
	PointL &operator/=(PointL &a, const PointL &b); // Divide point element on elements of another point
	PointL operator-(const PointL &a); // Unary negation
	std::wostream &operator<<(std::wostream &stream, const PointL &a); // Output as source code

	String AsSourceCode(const PointL &a);
	String ToString(const PointL &value);
	Variant ToVariant(const PointL &value);
	void FromVariant(const Variant &value, PointL &dest);
	PointL Round(const PointD &a); // Convert to integer point rounding elements
}