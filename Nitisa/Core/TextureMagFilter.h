// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

namespace nitisa
{
	enum class TextureMagFilter // Texture magnification filtering mode
	{
		Nearest, // Returns the value of the texture element that is nearest (in Manhattan distance) to the specified texture coordinates
		Linear // Returns the weighted average of the texture elements that are closest to the specified texture coordinates
	};
}