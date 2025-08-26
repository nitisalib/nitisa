// This file is a part of Nitisa framework
// Copyright © 2020 Nitisa. All rights reserved.
// Author: Dimitry Lysenko
// Site: http://nitisa.com
// Download: http://nitisa.com/downloads
// Documentation: http://nitisa.com/documentation
// License: http://nitisa.com/site/license

#pragma once

#include "../../Core/Strings.h"
#include "../../Core/Variant.h"
#include "../Interfaces/IPackageListItem.h"
#include "PackageEntity.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IPropertyList;

	class CPackageListItem :public virtual IPackageListItem, public CPackageEntity
	{
	public:
		void Save(Variant &dest, IPropertyList *properties) override;
		void Load(const Variant &src, IPropertyList *properties) override;
		void Load(const String &src, IPropertyList *properties) override;
		void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties) override;

		CPackageListItem(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs
	};
}