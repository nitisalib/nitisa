// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Interfaces/IReleasable.h"

namespace nitisa
{
	class IPackage;
	class IPropertyHandler;

	class IPackagePropertyHandler :public virtual IReleasable
	{
	protected:
		IPackagePropertyHandler() = default;
		~IPackagePropertyHandler() = default;
		IPackagePropertyHandler(const IPackagePropertyHandler &other) = delete;
		IPackagePropertyHandler(IPackagePropertyHandler &&other) = delete;
		IPackagePropertyHandler &operator=(const IPackagePropertyHandler &other) = delete;
		IPackagePropertyHandler &operator=(IPackagePropertyHandler &&other) = delete;
	protected:
		IPackage *m_pPackage;
		String m_sName;
	public:
		IPackage* const &Package{ m_pPackage };
		String const &Name{ m_sName };

		virtual IPropertyHandler *Create() = 0; // Create new instance of property handler
	};
}