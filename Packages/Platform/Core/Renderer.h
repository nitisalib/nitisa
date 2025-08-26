// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/RendererTechnology.h"
#include "Nitisa/Core/Version2.h"

namespace nitisa
{
	class IErrorListener;
	class IRenderer;

	class CRenderer
	{
	public:
		static IRenderer *Create(
			const RendererTechnology technology = RendererTechnology::OpenGL, // Technology to use
		#ifdef _WIN32
			const Version2 &max_version = Version2{ 4, 5 }, // Maximum native graphics version to use
		#endif
		#if defined(__linux__) && !defined(__ANDROID__)
			const Version2 &max_version = Version2{ 4, 5 }, // Maximum native graphics version to use
		#endif
		#ifdef __ANDROID__
			const Version2 &max_version = Version2{ 3, 2 }, // Maximum native graphics version to use
		#endif
			const bool double_buffered = false, // Use single or double buffering
			const int multisample_factor = 0, // Antialiasing factor
			IErrorListener *listener = nullptr, // Error listener
			const bool debug_context = false); // Whether try to create debug native graphics context
	};
}