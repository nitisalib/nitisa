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
		CPackageRendererLinuxOpenGL45d::CPackageRendererLinuxOpenGL45d(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Linux, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Linux/OpenGL/4.5/Debug/Renderer.h");
		}

		String CPackageRendererLinuxOpenGL45d::getCategory()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL45d::getClassName()
		{
			return L"linux::opengl45d::CRenderer";
		}

		String CPackageRendererLinuxOpenGL45d::getTitle()
		{
			return L"Linux OpenGL 4.5 Debug Renderer";
		}

		String CPackageRendererLinuxOpenGL45d::getDescription()
		{
			return L"Standard renderer for Linux platform. Require OpenGL at least 4.5 version for drawing. Use for debugging only.";
		}

		String CPackageRendererLinuxOpenGL45d::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL45d::getTechnology()
		{
			return L"OpenGL 4.5+";
		}
	}
}