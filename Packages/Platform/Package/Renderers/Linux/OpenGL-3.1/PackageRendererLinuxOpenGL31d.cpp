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
		CPackageRendererLinuxOpenGL31d::CPackageRendererLinuxOpenGL31d(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Linux, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Linux/OpenGL/3.1/Debug/Renderer.h");
		}

		String CPackageRendererLinuxOpenGL31d::getCategory()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL31d::getClassName()
		{
			return L"linux::opengl31d::CRenderer";
		}

		String CPackageRendererLinuxOpenGL31d::getTitle()
		{
			return L"Linux OpenGL 3.1 Debug Renderer";
		}

		String CPackageRendererLinuxOpenGL31d::getDescription()
		{
			return L"Standard renderer for Linux platform. Require OpenGL at least 3.1 version for drawing. Use for debugging only.";
		}

		String CPackageRendererLinuxOpenGL31d::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL31d::getTechnology()
		{
			return L"OpenGL 3.1+";
		}
	}
}