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
	union PointD
	{
		struct
		{
			double X;
			double Y;
		};
		double Data[2];

		double operator[](const int index) const; // Get element
		double &operator[](const int index); // Get element
	};

	PointD operator+(const PointD &a, const double value); // Add point and value
	PointD operator-(const PointD &a, const double value); // Subtract point and value
	PointD operator/(const PointD &a, const double value); // Divide point and value
	PointD operator*(const PointD &a, const double value); // Multiply point and value
	PointD operator+(const double value, const PointD &a); // Add value and point
	PointD operator-(const double value, const PointD &a); // Subtract value and point
	PointD operator/(const double value, const PointD &a); // Divide value and point
	PointD operator*(const double value, const PointD &a); // Multiply value and point
	PointD &operator+=(PointD &a, const double value); // Add value to point
	PointD &operator-=(PointD &a, const double value); // Subtract value from point
	PointD &operator/=(PointD &a, const double value); // Divide point on value
	PointD &operator*=(PointD &a, const double value); // Multiply point on value
	PointD operator+(const PointD &a, const PointD &b); // Add points elements
	PointD operator-(const PointD &a, const PointD &b); // Subtract points elements
	PointD operator*(const PointD &a, const PointD &b); // Multiply point elements
	PointD operator/(const PointD &a, const PointD &b); // Divide point elements
	PointD &operator+=(PointD &a, const PointD &b); // Add elements of another point to first one
	PointD &operator-=(PointD &a, const PointD &b); // Subtract elements of another point from first one
	PointD &operator*=(PointD &a, const PointD &b); // Multiply point element to elements of another point
	PointD &operator/=(PointD &a, const PointD &b); // Divide point element on elements of another point
	PointD operator-(const PointD &a); // Unary negation
	std::wostream &operator<<(std::wostream &stream, const PointD &a); // Output as source code

	bool IsEqual(const PointD &a, const PointD &b, const double tolerance = ntl::Tolerance<double>);
	bool IsNotEqual(const PointD &a, const PointD &b, const double tolerance = ntl::Tolerance<double>);
	bool Equals(const PointD &a, const PointD &b, const double relative_tolerance = ntl::RelativeTolerance<double>);
	bool NotEquals(const PointD &a, const PointD &b, const double relative_tolerance = ntl::RelativeTolerance<double>);
	String AsSourceCode(const PointD &a);
	String ToString(const PointD &value);
	Variant ToVariant(const PointD &value);
	void FromVariant(const Variant &value, PointD &dest);
}