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
	enum class RendererTechnology // Renderer technology
	{
		Null, // Render nowhere
		OpenGL, // OpenGL, OpenGL ES
		DirectX, // DirectX
		GDI, // GDI
		GDIPlus, // GDI+
		Software, // CPU
		Other // Another
	};
}