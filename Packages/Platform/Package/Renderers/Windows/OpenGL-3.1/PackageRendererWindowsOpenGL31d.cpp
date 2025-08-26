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
		CPackageRendererWindowsOpenGL31d::CPackageRendererWindowsOpenGL31d(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Windows/OpenGL/3.1/Debug/Renderer.h");
		}

		String CPackageRendererWindowsOpenGL31d::getCategory()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL31d::getClassName()
		{
			return L"windows::opengl31d::CRenderer";
		}

		String CPackageRendererWindowsOpenGL31d::getTitle()
		{
			return L"Windows OpenGL 3.1 Debug Renderer";
		}

		String CPackageRendererWindowsOpenGL31d::getDescription()
		{
			return L"Standard renderer for Windows platform. Require OpenGL at least 3.1 version for drawing. Use for debugging only.";
		}

		String CPackageRendererWindowsOpenGL31d::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL31d::getTechnology()
		{
			return L"OpenGL 3.1+";
		}
	}
}