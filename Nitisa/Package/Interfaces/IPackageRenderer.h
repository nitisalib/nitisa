// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "IPackageEntity.h"

namespace nitisa
{
	class IPackageRenderer :public virtual IPackageEntity
	{
	protected:
		IPackageRenderer() = default;
		~IPackageRenderer() = default;
		IPackageRenderer(const IPackageRenderer &other) = delete;
		IPackageRenderer(IPackageRenderer &&other) = delete;
		IPackageRenderer &operator=(const IPackageRenderer &other) = delete;
		IPackageRenderer &operator=(IPackageRenderer &&other) = delete;
	public:
		virtual String getTechnology() = 0; // Return renderer technology(like "DirectX 9.0", "OpenGL 3.3", "GDI", and so on)
	};
}