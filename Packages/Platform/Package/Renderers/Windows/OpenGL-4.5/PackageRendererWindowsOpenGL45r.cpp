// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace platform
	{
		CPackageRendererWindowsOpenGL45r::CPackageRendererWindowsOpenGL45r(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Windows/OpenGL/4.5/Release/Renderer.h");
		}

		String CPackageRendererWindowsOpenGL45r::getCategory()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL45r::getClassName()
		{
			return L"windows::opengl45r::CRenderer";
		}

		String CPackageRendererWindowsOpenGL45r::getTitle()
		{
			return L"Windows OpenGL 4.5 Release Renderer";
		}

		String CPackageRendererWindowsOpenGL45r::getDescription()
		{
			return L"Standard renderer for Windows platform. Require OpenGL at least 4.5 version for drawing.";
		}

		String CPackageRendererWindowsOpenGL45r::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL45r::getTechnology()
		{
			return L"OpenGL 4.5+";
		}
	}
}