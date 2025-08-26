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
		CPackageRendererWindowsOpenGL31r::CPackageRendererWindowsOpenGL31r(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Windows/OpenGL/3.1/Release/Renderer.h");
		}

		String CPackageRendererWindowsOpenGL31r::getCategory()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL31r::getClassName()
		{
			return L"windows::opengl31r::CRenderer";
		}

		String CPackageRendererWindowsOpenGL31r::getTitle()
		{
			return L"Windows OpenGL 3.1 Release Renderer";
		}

		String CPackageRendererWindowsOpenGL31r::getDescription()
		{
			return L"Standard renderer for Windows platform. Require OpenGL at least 3.1 version for drawing.";
		}

		String CPackageRendererWindowsOpenGL31r::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL31r::getTechnology()
		{
			return L"OpenGL 3.1+";
		}
	}
}