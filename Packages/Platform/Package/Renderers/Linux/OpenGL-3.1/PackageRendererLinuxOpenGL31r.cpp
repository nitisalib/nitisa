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
		CPackageRendererLinuxOpenGL31r::CPackageRendererLinuxOpenGL31r(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Linux, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Linux/OpenGL/3.1/Release/Renderer.h");
		}

		String CPackageRendererLinuxOpenGL31r::getCategory()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL31r::getClassName()
		{
			return L"linux::opengl31r::CRenderer";
		}

		String CPackageRendererLinuxOpenGL31r::getTitle()
		{
			return L"Linux OpenGL 3.1 Release Renderer";
		}

		String CPackageRendererLinuxOpenGL31r::getDescription()
		{
			return L"Standard renderer for Linux platform. Require OpenGL at least 3.1 version for drawing.";
		}

		String CPackageRendererLinuxOpenGL31r::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL31r::getTechnology()
		{
			return L"OpenGL 3.1+";
		}
	}
}