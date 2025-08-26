// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "IPackageEntity.h"

namespace nitisa
{
	class IStyle;

	class IPackageStyle : public virtual IPackageEntity
	{
	protected:
		IPackageStyle() = default;
		~IPackageStyle() = default;
		IPackageStyle(const IPackageStyle &other) = delete;
		IPackageStyle(IPackageStyle &&other) = delete;
		IPackageStyle &operator=(const IPackageStyle &other) = delete;
		IPackageStyle &operator=(IPackageStyle &&other) = delete;
	public:
		// Properties
		virtual IStyle *getStyle() = 0; // Return style
	};
}