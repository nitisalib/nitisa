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
	enum class TextureFormat
	{
		Alpha, // byte
		AlphaFloat, // float
		RGB, // 3 bytes
		RGBFloat, // 3 floats
		RGBA, // 4 bytes
		RGBAFloat, // 4 floats
		Depth, // float
		Stencil,  // byte
		DepthStencil // float, byte
	};
}