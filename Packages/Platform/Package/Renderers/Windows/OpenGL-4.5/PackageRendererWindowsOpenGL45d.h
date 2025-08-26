// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Core/Strings.h"
#include "Nitisa/Package/Core/PackageRenderer.h"

namespace nitisa
{
	class IPackage;

	namespace platform
	{
		class CPackageRendererWindowsOpenGL45d :public CPackageRenderer
		{
		public:
			String getCategory() override;
			String getClassName() override;
			String getTitle() override;
			String getDescription() override;
			String getReferenceUrl() override;
			String getTechnology() override;

			CPackageRendererWindowsOpenGL45d(IPackage *package);
		};
	}
}