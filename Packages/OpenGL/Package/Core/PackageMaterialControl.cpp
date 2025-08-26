// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#include "stdafx.h"

namespace nitisa
{
	namespace opengl
	{
		CPackageMaterialControl::CPackageMaterialControl(IPackage *package) : CPackageControl(package, L"opengl")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });
		}

		bool CPackageMaterialControl::isVisible()
		{
			return true;
		}

		bool CPackageMaterialControl::isDisplayIcon()
		{
			return true;
		}

		bool CPackageMaterialControl::isTransformable()
		{
			return false;
		}
	}
}