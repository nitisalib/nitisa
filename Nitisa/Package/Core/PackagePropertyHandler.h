// This file is a part of Nitisa framework
// Copyright © 2021 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Releasable.h"
#include "../../Core/Strings.h"
#include "../Interfaces/IPackagePropertyHandler.h"

#pragma warning(disable: 4250)

namespace nitisa
{
	class IPackage;
	class IPropertyHandler;

	template<class PropertyHandlerClass>
	class CPackagePropertyHandler :public virtual IPackagePropertyHandler, public CReleasable
	{
	public:
		IPropertyHandler *Create() override
		{
			return new PropertyHandlerClass(m_pPackage);
		}

		CPackagePropertyHandler(
			IPackage *package, // Package to which the entity belongs
			const String &name) : // Property handler name
			CReleasable()
		{
			m_pPackage = package;
			m_sName = name;
		}
	};
}