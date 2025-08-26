// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	struct Bitmask
	{
		unsigned int X; // Bitmask in X-direction/length
		unsigned int Y; // Bitmask in Y-direction
		bool is1D; // Whether bitmask is 1- or 2-dimentional
		bool useFormCoords; // Whether form coordinates(instead of object ones) should be used

		bool operator==(const Bitmask &b) const // Check whether bitmasks are equal
		{
			return X == b.X && Y == b.Y && is1D == b.is1D && useFormCoords == b.useFormCoords;
		}

		bool operator!=(const Bitmask &b) const // Check whether bitmasks aren't equal
		{
			return X != b.X || Y != b.Y || is1D != b.is1D || useFormCoords != b.useFormCoords;
		}
	};
}