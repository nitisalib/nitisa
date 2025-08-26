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
#include <iostream>

namespace nitisa
{
	union PointF
	{
		struct
		{
			float X;
			float Y;
		};
		float Data[2];

		float operator[](const int index) const; // Get element
		float &operator[](const int index); // Get element
	};

	PointF operator+(const PointF &a, const float value); // Add point and value
	PointF operator-(const PointF &a, const float value); // Subtract point and value
	PointF operator/(const PointF &a, const float value); // Divide point and value
	PointF operator*(const PointF &a, const float value); // Multiply point and value
	PointF operator+(const float value, const PointF &a); // Add value and point
	PointF operator-(const float value, const PointF &a); // Subtract value and point
	PointF operator/(const float value, const PointF &a); // Divide value and point
	PointF operator*(const float value, const PointF &a); // Multiply value and point
	PointF &operator+=(PointF &a, const float value); // Add value to point
	PointF &operator-=(PointF &a, const float value); // Subtract value from point
	PointF &operator/=(PointF &a, const float value); // Divide point on value
	PointF &operator*=(PointF &a, const float value); // Multiply point on value
	PointF operator+(const PointF &a, const PointF &b); // Add points elements
	PointF operator-(const PointF &a, const PointF &b); // Subtract points elements
	PointF operator*(const PointF &a, const PointF &b); // Multiply point elements
	PointF operator/(const PointF &a, const PointF &b); // Divide point elements
	PointF &operator+=(PointF &a, const PointF &b); // Add elements of another point to first one
	PointF &operator-=(PointF &a, const PointF &b); // Subtract elements of another point from first one
	PointF &operator*=(PointF &a, const PointF &b); // Multiply point element to elements of another point
	PointF &operator/=(PointF &a, const PointF &b); // Divide point element on elements of another point
	PointF operator-(const PointF &a); // Unary negation
	std::wostream &operator<<(std::wostream &stream, const PointF &a); // Output as source code

	bool IsEqual(const PointF &a, const PointF &b, const float tolerance = ntl::Tolerance<float>);
	bool IsNotEqual(const PointF &a, const PointF &b, const float tolerance = ntl::Tolerance<float>);
	bool Equals(const PointF &a, const PointF &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	bool NotEquals(const PointF &a, const PointF &b, const float relative_tolerance = ntl::RelativeTolerance<float>);
	String AsSourceCode(const PointF &a);
	String ToString(const PointF &value);
	Variant ToVariant(const PointF &value);
	void FromVariant(const Variant &value, PointF &dest);
}