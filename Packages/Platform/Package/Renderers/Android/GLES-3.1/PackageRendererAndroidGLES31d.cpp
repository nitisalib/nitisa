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
		CPackageRendererAndroidGLES31d::CPackageRendererAndroidGLES31d(IPackage *package) : CPackageRenderer(package, L"platform")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Android, L"", L"" });

			// Header files
			AddHeaderFile(L"Platform/Android/GLES/3.1/Debug/Renderer.h");
		}

		String CPackageRendererAndroidGLES31d::getCategory()
		{
			return L"";
		}

		String CPackageRendererAndroidGLES31d::getClassName()
		{
			return L"android::gles30d::CRenderer";
		}

		String CPackageRendererAndroidGLES31d::getTitle()
		{
			return L"Android GLES 3.1 Debug Renderer";
		}

		String CPackageRendererAndroidGLES31d::getDescription()
		{
			return L"Standard renderer for Android platform. Require GLES at least 3.1 version for drawing. Use for debugging only.";
		}

		String CPackageRendererAndroidGLES31d::getReferenceUrl()
		{
			return L"";
		}

		String CPackageRendererAndroidGLES31d::getTechnology()
		{
			return L"GLES 3.1+";
		}
	}
}