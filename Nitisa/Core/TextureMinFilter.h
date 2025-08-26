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
	enum class TextureMinFilter // Texture minifying filtering mode
	{
		Nearest, // Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates
		Linear, // Returns the weighted average of the four texture elements that are closest to the specified texture coordinates
		NearestMipmapNearest, // Chooses the mipmap that most closely matches the size of the pixel being textured and uses the Nearest criterion (the texture element closest to the specified texture coordinates) to produce a texture value
		LinearMipmapNearest, // Chooses the mipmap that most closely matches the size of the pixel being textured and uses the Linear criterion (a weighted average of the four texture elements that are closest to the specified texture coordinates) to produce a texture value
		NearestMipmapLinear, // Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the Nearest criterion (the texture element closest to the specified texture coordinates ) to produce a texture value from each mipmap. The final texture value is a weighted average of those two values
		LinearMipmapLinear // Chooses the two mipmaps that most closely match the size of the pixel being textured and uses the Linear criterion (a weighted average of the texture elements that are closest to the specified texture coordinates) to produce a texture value from each mipmap. The final texture value is a weighted average of those two values
	};
}