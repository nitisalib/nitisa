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
	enum class ShaderType
	{
		Vertex, // Vertex shader
		TessellationControl, // Tessellation control shader
		TessellationEvaluation, // Tessellation evaluation shader
		Geometry, // Geometry shader
		Fragment, // Fragment shader
		Compute // Compute shader
	};
}