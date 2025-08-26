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
	union RectB
	{
		struct
		{
			bool Left;
			bool Top;
			bool Right;
			bool Bottom;
		};
		bool Data[4];

		bool operator[](const int index) const; // Return element
		bool &operator[](const int index); // Return element
	};

	bool operator==(const RectB &a, const RectB &b); // Check if rects are equal
	bool operator!=(const RectB &a, const RectB &b); // Check if rects are not equal
	std::wostream &operator<<(std::wostream &stream, const RectB &a); // Output as source code

	String AsSourceCode(const RectB &a);
	String ToString(const RectB &value);
	Variant ToVariant(const RectB &value);
	void FromVariant(const Variant &value, RectB &dest);
}