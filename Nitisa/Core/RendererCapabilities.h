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
	struct RendererCapabilities
	{
		int MaxColorAttachments; // Maximum allowed color attachments
		int MaxDrawBuffers; // Maximum allowed draw buffers
		int MaxActiveTextures; // Maximum active textures
		int MaxSamples; // Maximum samples per pixel

		RendererCapabilities() :
			MaxColorAttachments{ 0 },
			MaxDrawBuffers{ 0 },
			MaxActiveTextures{ 0 },
			MaxSamples{ 0 }
		{

		}
	};
}