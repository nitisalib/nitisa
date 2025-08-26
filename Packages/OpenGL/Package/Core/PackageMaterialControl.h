// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "Nitisa/Package/Core/PackageControl.h"

namespace nitisa
{
	class IPackage;

	namespace opengl
	{
		class CPackageMaterialControl :public CPackageControl
		{
		public:
			bool isVisible() override;
			bool isDisplayIcon() override;
			bool isTransformable() override;

			CPackageMaterialControl(IPackage *package);
		};
	}
}