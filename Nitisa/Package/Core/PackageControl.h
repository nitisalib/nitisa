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
#include "../Interfaces/IPackageControl.h"
#include "PackageEntity.h"
#include <iostream>

#pragma warning(disable: 4250)

namespace nitisa
{
	class IComponent;
	class IControl;
	class IEventList;
	class IListItem;
	class IPackage;
	class IPackageControlListener;
	class IPropertyList;

	class CPackageControl :public virtual IPackageControl, public CPackageEntity
	{
	public:
		bool isDialogBox() override; // Return false. Should be overwritten by derived class to return true if control is correct dialog box one

		void Save(Variant &dest, IPropertyList *properties, IEventList *events) override;
		void Load(const Variant &src, IPropertyList *properties, IEventList *events) override;
		void Export(std::wofstream &f, const String &shift, const String &owner, IPropertyList *properties, IEventList *events, const String &form, const String &dialog_box) override;
		void ExportExtra(std::wofstream &f, const String &shift, IControl *control) override;
		bool CreateChild(IControl *parent, IControl **child, IPackageControlListener *listener = nullptr) override; // Creates child control if parent control is derived from IControlCreateChild
		bool CreateListItem(IComponent *component, IListItem *parent, IListItem **item, IPackageControlListener *listener = nullptr) override; // Creates nothing. Return false

		CPackageControl(
			IPackage *package, // Package to which the entity belongs
			const String &ns); // Namespace to which the entity belongs
	};
}