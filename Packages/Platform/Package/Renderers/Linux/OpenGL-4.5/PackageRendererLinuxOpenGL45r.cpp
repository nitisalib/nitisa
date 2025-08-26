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
		CPackageRendererLinuxOpenGL45r::CPackageRendererLinuxOpenGL45r(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Linux, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Linux/OpenGL/4.5/Release/Renderer.h");
		}

		String CPackageRendererLinuxOpenGL45r::getCategory()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL45r::getClassName()
		{
			return L"linux::opengl45r::CRenderer";
		}

		String CPackageRendererLinuxOpenGL45r::getTitle()
		{
			return L"Linux OpenGL 4.5 Release Renderer";
		}

		String CPackageRendererLinuxOpenGL45r::getDescription()
		{
			return L"Standard renderer for Linux platform. Require OpenGL at least 4.5 version for drawing.";
		}

		String CPackageRendererLinuxOpenGL45r::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererLinuxOpenGL45r::getTechnology()
		{
			return L"OpenGL 4.5+";
		}
	}
}