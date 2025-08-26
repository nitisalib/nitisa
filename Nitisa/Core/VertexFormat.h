// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Aliases.h"

namespace nitisa
{
	struct VertexFormat
	{
		static const byte npos{ (byte)-1 }; // Value used as non-index(or "no index is used")

		byte Vec1fCount : 3; // Count of 1D float vectors
		byte Vec2fCount : 3; // Count of 2D float vectors
		byte Vec3fCount : 3; // Count of 3D float vectors
		byte Vec4fCount : 3; // Count of 4D float vectors
		byte Vec1iCount : 3; // Count of 1D integer vectors
		byte Vec2iCount : 3; // Count of 2D integer vectors
		byte Vec3iCount : 3; // Count of 3D integer vectors
		byte Vec4iCount : 3; // Count of 4D integer vectors

		byte TextureCoordIndex; // Index of texture coords in 2D float vectors array
		byte BitmaskCoordIndex; // Index of bitmask coords in 2D float vectors array
		byte NormalCoordIndex; // Index of normal coords in 2D float vectors array
		byte BumpCoordIndex; // Index of bump coords in 2D float vectors array
		byte Position2DIndex; // Index of position in 2D float vectors array
		byte Position3DIndex; // Index of position in 3D float vectors array
		byte Position4DIndex; // Index of position in 4D float vectors array
		byte NormalIndex; // Index of normal in 3D float vectors array
		byte ColorIndex; // Index of color in 4D float vectors array
	};
}