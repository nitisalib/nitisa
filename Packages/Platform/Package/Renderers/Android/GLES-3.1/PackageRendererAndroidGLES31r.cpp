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
		CPackageRendererAndroidGLES31r::CPackageRendererAndroidGLES31r(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Android, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Android/GLES/3.1/Release/Renderer.h");
		}

		String CPackageRendererAndroidGLES31r::getCategory()
		{
			return L"";
		}

		String CPackageRendererAndroidGLES31r::getClassName()
		{
			return L"android::gles31r::CRenderer";
		}

		String CPackageRendererAndroidGLES31r::getTitle()
		{
			return L"Linux GLES 3.1 Release Renderer";
		}

		String CPackageRendererAndroidGLES31r::getDescription()
		{
			return L"Standard renderer for Android platform. Require GLES at least 3.1 version for drawing.";
		}

		String CPackageRendererAndroidGLES31r::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererAndroidGLES31r::getTechnology()
		{
			return L"GLES 3.1+";
		}
	}
}