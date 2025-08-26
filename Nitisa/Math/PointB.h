// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../Core/Strings.h"
#include "../Core/Variant.h"
#include <iostream>

namespace nitisa
{
	union PointB
	{
		struct
		{
			bool X;
			bool Y;
		};
		bool Data[2];

		bool operator[](const int index) const; // Get element
		bool &operator[](const int index); // Get element
	};

	bool operator==(const PointB &a, const PointB &b); // Check if points are equal
	bool operator!=(const PointB &a, const PointB &b); // Check if points are not equal
	std::wostream &operator<<(std::wostream &stream, const PointB &a); // Output as source code

	String AsSourceCode(const PointB &a);
	String ToString(const PointB &value);
	Variant ToVariant(const PointB &value);
	void FromVariant(const Variant &value, PointB &dest);
}