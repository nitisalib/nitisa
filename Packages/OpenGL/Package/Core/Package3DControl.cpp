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
		CPackage3DControl::CPackage3DControl(IPackage *package) : CPackageControl(package, L"opengl")
		{
			// Supported platforms
			AddPlatform(PlatformVersion{ PlatformType::Windows, L"", L"" });
		}

		bool CPackage3DControl::isVisible()
		{
			return true;
		}

		bool CPackage3DControl::isDisplayIcon()
		{
			return true;
		}

		bool CPackage3DControl::isTransformable()
		{
			return false;
		}
	}
}