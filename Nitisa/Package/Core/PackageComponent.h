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
#include "../Interfaces/IPackageComponent.h"
#include "PackageEntity.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IComponent;
	class IEventList;
	class IListItem;
	class IPackage;
	class IPackageComponentListener;
	class IPropertyList;

	class CPackageComponent :public virtual IPackageComponent, public CPackageEntity
	{
	public:
		void Save(Variant &dest, IPropertyList *properties, IEventList *events) override;
		void Load(const Variant &src, IPropertyList *properties, IEventList *events) override;
		void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) override;
		void ExportExtra(std::wofstream &f, const String &shift, IComponent *component) override;
		bool CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageComponentListener *listener = nullptr) override; // Creates nothing. Return false

		CPackageComponent(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs
	};
}