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
		CPackageRendererWindowsOpenGL45d::CPackageRendererWindowsOpenGL45d(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Windows/OpenGL/4.5/Debug/Renderer.h");
		}

		String CPackageRendererWindowsOpenGL45d::getCategory()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL45d::getClassName()
		{
			return L"windows::opengl45d::CRenderer";
		}

		String CPackageRendererWindowsOpenGL45d::getTitle()
		{
			return L"Windows OpenGL 4.5 Debug Renderer";
		}

		String CPackageRendererWindowsOpenGL45d::getDescription()
		{
			return L"Standard renderer for Windows platform. Require OpenGL at least 4.5 version for drawing. Use for debugging only.";
		}

		String CPackageRendererWindowsOpenGL45d::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererWindowsOpenGL45d::getTechnology()
		{
			return L"OpenGL 4.5+";
		}
	}
}