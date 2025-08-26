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
	enum class TextureWrap
	{
		ClampToBorder, // If coordinates are outside of texture, the border color, which is { 0, 0, 0, 0 }, will be used. Default option
		ClampToEdge, // If coordinates are outside of texture, the closest border pixel value will be used
		ClampToEdgeMirrored,
		Repeat, // If coordinates are outside of texture, texture will be repeated
		RepeatMirrored // If coordinates are outside of texture, texture will be repeated and mirrored
	};
}