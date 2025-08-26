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
#include "../Image/Color.h"
#include <iostream>

namespace nitisa
{
	union BorderColor
	{
		struct
		{
			Color Left;
			Color Top;
			Color Right;
			Color Bottom;
		};
		Color Data[4];

		const Color &operator[](const int index) const // Return element
		{
			return Data[index];
		}

		Color &operator[](const int index) // Return element
		{
			return Data[index];
		}

		bool operator==(const BorderColor &b) const // Check if rects are equal
		{
			return Left == b.Left && Top == b.Top && Right == b.Right && Bottom == b.Bottom;
		}

		bool operator!=(const BorderColor &b) const // Check if rects are not equal
		{
			return Left != b.Left || Top != b.Top || Right != b.Right || Bottom != b.Bottom;
		}
	};

	std::wostream &operator<<(std::wostream &stream, const BorderColor &a); // Output as source code

	String AsSourceCode(const BorderColor &a);
	String ToString(const BorderColor &value);
	Variant ToVariant(const BorderColor &value);
	void FromVariant(const Variant &value, BorderColor &dest);
}