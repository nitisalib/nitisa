// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../Interfaces/IPackageRenderer.h"
#include "PackageEntity.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class CPackageRenderer :public virtual IPackageRenderer, public CPackageEntity
	{
	public:
		CPackageRenderer(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs
	};
}